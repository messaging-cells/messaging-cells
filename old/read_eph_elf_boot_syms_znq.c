
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <elf.h>

#include "shared.h"
#include "booter.h"


const char* mch_link_script_syms_names[] = {
BJH_STR_EXTER_CODE_SIZE,
BJH_STR_EXTER_LOAD_SIZE,
BJH_STR_EXTER_DATA_SIZE,
BJH_STR_EXTER_ALLOC_SIZE,

BJH_STR_EXTER_ORIG,
BJH_STR_EXTER_CODE_ORIG,
BJH_STR_EXTER_LOAD_ORIG,
BJH_STR_EXTER_DATA_ORIG,
BJH_STR_EXTER_ALLOC_ORIG,

NULL
};

void get_syms_addrs(const void *file, int addrs_sz, void** syms_addrs);

int16_t 
mch_find_link_script_name(const char* nam){
	const char** nams = mch_link_script_syms_names;
	int16_t aa = -1;
	for(aa = 0; aa < BJH_TOT_LOAD_SYMS; aa++){
		if(nams[aa] == NULL){
			aa = -1;
			break;
		}
		if(strcmp(nams[aa], nam) == 0){
			break;
		}
	}
	return aa;
}

void*
mch_find_link_script_addr(const char* nam, int addrs_sz, void** syms_addrs){
	int16_t idx = mch_find_link_script_name(nam);
	void* addr = NULL;
	if(idx < addrs_sz){
		addr = syms_addrs[idx];
	}
	return addr;
}

int mch_read_eph_elf_syms(const char *elf_nm, int addrs_sz, void** syms_addrs)
{
	int          fd;
	struct stat  st;
	void        *file;
	
	const char** nams = mch_link_script_syms_names;
	if(nams[BJH_TOT_LOAD_SYMS] != NULL){
		printf("CODE_ERROR: mch_read_eph_elf_syms. BAD DEFINED BJH_TOT_LOAD_SYMS\n");
		return 1;
	}
	//memset(syms_addrs, 0, addrs_sz * sizeof(void*));

	fd = open(elf_nm, O_RDONLY);
	if (fd == -1) {
		printf("ERROR: Can't open elf file \"%s\".\n", elf_nm);
		return 1;
	}

	if (fstat(fd, &st) == -1) {
		printf("ERROR: Can't stat elf file \"%s\".\n", elf_nm);
		close(fd);
		return 1;
    }

	file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED) {
		printf("ERROR: Can't mmap elf file \"%s\".\n", elf_nm);
		close(fd);
		return 1;
    }

	get_syms_addrs(file, addrs_sz, syms_addrs);

	/*
	printf("SYMS_ADDDRS=[\n");
	for(int kk = 0; kk < BJH_TOT_LOAD_SYMS; kk++){
		if(kk == addrs_sz){
			break;
		}
		if(syms_addrs[kk] == mc_null){
			break;
		}
		printf("%s = %p\n", nams[kk], syms_addrs[kk]);
	}
	printf("]\n");
	*/

	munmap(file, st.st_size);
	close(fd);
	return 0;
}

void 
get_syms_addrs(const void *file, int addrs_sz, void** syms_addrs)
{
	uint16_t ii;
	uint16_t kk;
	//size_t jj;
	Elf32_Ehdr *ehdr;
	//Elf32_Phdr *phdr;
	Elf32_Shdr *shdr;
	//Elf32_Shdr *sh_strtab;
	//const char *strtab;
	uint8_t *src = (uint8_t *) file;

	ehdr = (Elf32_Ehdr *) &src[0];
	//phdr = (Elf32_Phdr *) &src[ehdr->e_phoff];
	shdr = (Elf32_Shdr *) &src[ehdr->e_shoff];
	int shnum = ehdr->e_shnum;

	//sh_strtab = &shdr[ehdr->e_shstrndx];
	//strtab = (char *) &src[sh_strtab->sh_offset];
	
	memset(syms_addrs, 0, addrs_sz * sizeof(void*));

	int16_t num_filled = 0;
	for (ii = 0; ii < shnum; ii++) {
		if(num_filled == addrs_sz){
			break;
		}
		
		//const char* nm = &strtab[shdr[ii].sh_name];
		//printf("Section %s  ii=%d offset=%d\n", nm, ii, shdr[ii].sh_offset);
		if(shdr[ii].sh_type == SHT_SYMTAB){
			//printf("SHT_SYMTAB\n");

			Elf32_Shdr *strs_shdr = &shdr[shdr[ii].sh_link];
			const char *strs_tab = (char *) &src[strs_shdr->sh_offset];
			
			Elf32_Word sz = shdr[ii].sh_size;
			Elf32_Word esz = shdr[ii].sh_entsize;
			
			if(esz > 0){
				Elf32_Word nument = sz/esz;
				Elf32_Sym *symtab = (Elf32_Sym *) &src[shdr[ii].sh_offset];
				
				for(kk = 0; kk < nument; kk++){
					const char* nm2 = &strs_tab[symtab[kk].st_name];
					void *addr = (void *)(symtab[kk].st_value);

					if(nm2 == NULL){
						continue;
					}
					if(addr == NULL){
						continue;
					}
					
					int16_t idx = mch_find_link_script_name(nm2);
					if(idx < addrs_sz){
						if(syms_addrs[idx] == 0){
							syms_addrs[idx] = addr;
							num_filled++;
						}
					}
					if(num_filled == addrs_sz){
						break;
					}
					
					/*if(symtab[kk].st_name != 0){
						printf("\t -------------------------------\n");
						printf("\t nm2=%s\n", nm2);
						printf("\t st_name=%d\n", symtab[kk].st_name);
						printf("\t st_value=0x%08x\n", symtab[kk].st_value);
						//printf("\t st_size=%d\n", symtab[kk].st_size);
						//printf("\t st_info=%u\n", symtab[kk].st_info);
						//printf("\t st_other=%u\n", symtab[kk].st_other);
						//printf("\t st_shndx=%d\n", symtab[kk].st_shndx);
					}*/
				}
			}
		}
	}

}

