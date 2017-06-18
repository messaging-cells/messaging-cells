

/*************************************************************

row.h

Some usefult abstract template classes and others.

--------------------------------------------------------------*/

#ifndef ROW_TEMPLATE_H
#define ROW_TEMPLATE_H

#include <new>

#include "shared.h"

template <bool> struct ILLEGAL_USE_OF_OBJECT;
template <> struct ILLEGAL_USE_OF_OBJECT<true>{};
#define OBJECT_COPY_ERROR ILLEGAL_USE_OF_OBJECT<false>()


// 'integer' must be of a signed type
typedef long			integer;
typedef integer			row_index;
typedef char			comparison;

#define CMP_FN_T(nm_fun) comparison (*nm_fun)(omc_t const & obj1, omc_t const & obj2)


#ifndef k_num_bits_byte
#define k_num_bits_byte		8
#endif

//define TOOLS_CK(prm)		DBG_CK(prm)
#define TOOLS_CK(prm)		

#define MIN_TYPE(type)		(((type)1) << (sizeof(type) * k_num_bits_byte - 1))
#define MAX_TYPE(type)		(- (MIN_TYPE(type) + 1))

#ifndef INVALID_IDX
#define INVALID_IDX		-1
#endif

#ifndef INVALID_NATURAL
#define INVALID_NATURAL		-1
#endif

#ifndef FILL_FULL_CAP
#define FILL_FULL_CAP	-100
#endif

#ifndef START_CAP
#define START_CAP 		16	// avoid mem problems (due to mem alloc, re-alloc failures)
#endif

#define SZ_ATTRIB		row<omc_t>::sz
#define CAP_ATTRIB		row<omc_t>::cap

//======================================================================
// number funcs

inline 
long
abs_long(long val){
	if(val < 0){
		val = -val;
	}
	TOOLS_CK(val >= 0);
	return val;
}

inline 
comparison 
cmp_long(long const & n1, long const & n2){ 
	if(n1 == n2){ return 0; }
	if(n1 < n2){ return -1; }
	return 1;
}

inline 
comparison 
cmp_char(char const & c1, char const & c2){ 
	if(c1 == c2){ return 0; }
	if(c1 < c2){ return -1; }
	return 1;
}

inline 
comparison 
cmp_abs_long(long const & nn1, long const & nn2){
	long n1 = abs_long(nn1); 
	long n2 = abs_long(nn2); 
	TOOLS_CK(n1 >= 0);
	TOOLS_CK(n2 >= 0);
	return cmp_long(n1, n2);
}

inline 
comparison 
cmp_integer(integer const & i1, integer const & i2){ 
	if(i1 == i2){ return 0; }
	if(i1 < i2){ return -1; }
	return 1;
}

//======================================================================
// Base types and funcs

typedef char	trinary;

template<class omc_t> static inline omc_t 
min_val(omc_t x, omc_t y) { 
	return (x < y) ? x : y; 
}

template<class omc_t> static inline omc_t 
max_val(omc_t x, omc_t y) { 
	return (x > y) ? x : y; 
}

template<class omc_t> 
static inline row_index
get_idx_of_pt(omc_t* data, omc_t* pt_obj, row_index the_size){
	row_index pt_idx = INVALID_IDX;
	if(data != mc_null){
		long pt1 = (long)data;
		long pt2 = pt1 + (sizeof(omc_t) * the_size);
		long pt3 = (long)pt_obj;
		bool in_range = (pt1 <= pt3) && (pt3 < pt2);
		bool in_place = (((pt3 - pt1) % sizeof(omc_t)) == 0);
		if(in_range && in_place){
			pt_idx = ((pt3 - pt1) / sizeof(omc_t));
		}
	}
	return pt_idx;
}

//======================================================================
// row

template<class omc_t>
class row {

protected:
	row_index sz;
	row_index cap;
	omc_t*  data;

public:
	typedef comparison (*cmp_func_t)(omc_t const & obj1, omc_t const & obj2);

	// Don't allow copying (error prone):
	// force use of referenced rows

	row<omc_t>&  operator = (row<omc_t>& other) { 
		OBJECT_COPY_ERROR; 
	}

	row(row<omc_t>& other){ 
		OBJECT_COPY_ERROR; 
	}

	// constructors
	row(row_index pm_cap = 0, omc_t* pm_data = mc_null){ 
		set_objs(pm_cap, pm_data);
	}

	~row(){
		clear(true, true);
	}

	// data opers

	const uint8_t*	get_bytes(){
		return ((uint8_t*)data);
	}

	long		get_num_bytes(){
		return (SZ_ATTRIB * sizeof(omc_t));
	}

	void set_objs(row_index pm_cap = 0, omc_t* pm_data = mc_null){
		sz = 0;
		cap = pm_cap;
		data = pm_data;
	}

	const omc_t*	get_objs(){
		return data;
	}

	long		get_num_objs(){
		return SZ_ATTRIB;
	}

	row_index	get_cap(){
		return cap;
	}

	void	clear(bool destroy = false, row_index from = 0){ 
		if(data != mc_null){
			if(destroy){ 
				for(row_index ii = from; ii < SZ_ATTRIB; ii++){ 
					pos(ii).~omc_t();
				}
			}
			SZ_ATTRIB = from;
		} 
	}

	omc_t&		pos(row_index idx){ 
		return data[idx];
	}

	void move_to(row<omc_t>& dest, bool just_init = false){ 
		if(!just_init){ 
			dest.clear(true, true); 
		}
		dest.data = data; 
		dest.sz = SZ_ATTRIB; 
		dest.cap = CAP_ATTRIB; 
		data = mc_null; 
		SZ_ATTRIB = 0; 
		CAP_ATTRIB = 0; 
	}

	void swap_with(row<omc_t>& other){ 
		omc_t*  tmp_data = other.data;
		row_index tmp_sz = other.sz;
		row_index tmp_cap = other.cap;

		other.data = data;
		other.sz = SZ_ATTRIB;
		other.cap = CAP_ATTRIB;

		data = tmp_data;
		SZ_ATTRIB = tmp_sz;
		CAP_ATTRIB = tmp_cap;
	}

	bool copy_to_c(long c_arr_sz, omc_t* c_arr){ 
		TOOLS_CK(c_arr != data);
		if(c_arr_sz != SZ_ATTRIB){
			return false;
		}
		mc_memcpy((uint8_t*)c_arr, (uint8_t*)data, row<omc_t>::sz_in_bytes());
		return true;
	}
	
	void mem_copy_to(row<omc_t>& r_cpy){ 
		TOOLS_CK(&r_cpy != this);
		r_cpy.set_cap(SZ_ATTRIB);
		mc_memcpy((uint8_t*)r_cpy.data, (uint8_t*)data, row<omc_t>::sz_in_bytes());
		r_cpy.sz = SZ_ATTRIB;
	}

	// Size operations:
	bool	ck_valid_pt(omc_t* pt_obj){ 
		row_index pt_idx = get_idx_of_pt<omc_t>(data, pt_obj, SZ_ATTRIB);
		return (pt_idx != INVALID_IDX);
	}

	void	set_cap(row_index min_cap){ 
		if(min_cap <= cap){ return; }
		bjk_abort((uint32_t)0xbad01, 0, mc_null);
	}

	row_index	sz_in_bytes(){
		return (sz * sizeof(omc_t));
	}

	bool	is_empty(){
		return (sz == 0);
	}

	void	grow(row_index min_cap){
		if(min_cap <= cap){ return; }
		bjk_abort((uint32_t)0xbad02, 0, mc_null);
	}

	row_index	size() const { 
		return sz; 
	}

	row_index	last_idx(){
		return (size() - 1);
	}

	bool		is_full() { 
		return (sz == cap); 
	}

	// Stack interface:
	void	push(const omc_t elem){ 
		if(is_full()){ 
			grow(sz + 2); 
		}
		//pos(sz) = elem;
		//pos(sz) = omc_t(elem);
		new (&pos(sz)) omc_t(elem); 
		sz++; 
	}

	omc_t&	inc_sz(){ 
		if(is_full()){ 
			grow(sz + 2);
		}
		//pos(sz) = omc_t();
		new (&pos(sz)) omc_t(); 
		sz++; 
		return last();
	}

	void	minc_sz(long num_incs){
		for(long aa = 0; aa < num_incs; aa++){
			inc_sz();
		}
	}

	void	dec_sz(){ 
		TOOLS_CK(sz > 0);
		sz--;
		pos(sz).~omc_t(); 
	}

	omc_t		pop(){ 
		TOOLS_CK(sz > 0);
		sz--; 
		omc_t tmp1 = pos(sz);
		pos(sz).~omc_t();
		return tmp1; 
	}

	omc_t&		first(){ 
		TOOLS_CK(sz > 0);
		return pos(0); 
	}

	omc_t&		last(){ 
		TOOLS_CK(sz > 0);
		return pos(sz - 1); 
	}

	void	swap(row_index idx1, row_index idx2){ 
		TOOLS_CK(is_valid_idx(idx1));
		TOOLS_CK(is_valid_idx(idx2));

		omc_t tmp1 = pos(idx1);
		pos(idx1) = pos(idx2);
		pos(idx2) = tmp1;
	}

	void	call_swap_with(row_index idx1, row_index idx2){ 
		TOOLS_CK(is_valid_idx(idx1));
		TOOLS_CK(is_valid_idx(idx2));

		omc_t& tmp1 = pos(idx1);
		omc_t& tmp2 = pos(idx2);
		tmp1.swap_with(tmp2);
	}

	omc_t	swap_pop(row_index idx){
		TOOLS_CK(is_valid_idx(idx));

		omc_t tmp1 = pos(idx);
		sz--;
		pos(idx) = pos(sz);
		pos(sz).~omc_t();
		return tmp1;
	}

	void	swapop(row_index idx){ 
		TOOLS_CK(is_valid_idx(idx));

		sz--;
		pos(idx) = pos(sz);
		pos(sz).~omc_t();
	}

	// Vector interface:

	void	fill(const omc_t elem, row_index num_fill = INVALID_IDX,
					row_index from_idx = 0)
	{ 
		if(from_idx == INVALID_IDX){
			from_idx = sz;
		} 

		if(num_fill == INVALID_IDX){
			num_fill = sz;
		} else 
		if(num_fill == FILL_FULL_CAP){
			num_fill = cap;
		} else {
			num_fill += from_idx;
		}
		set_cap(num_fill);
		row_index ii = from_idx;
		for(ii = from_idx; ((ii < sz) && (ii < num_fill)); ii++){
			pos(ii) = elem;
		}
		for(; ii < num_fill; ii++){
			push(elem);
		}
	}

	void	fill_new(row_index num_fill = INVALID_IDX){ 
		clear(true, true);
		if(num_fill == INVALID_IDX){
			num_fill = sz;
		}
		if(num_fill == FILL_FULL_CAP){
			num_fill = cap;
		}
		set_cap(num_fill);
		for(row_index ii = 0; ii < num_fill; ii++){
			inc_sz();
		}
	}

	bool	is_valid_idx(row_index idx){
		return ((idx >= 0) && (idx < sz));
	}

	omc_t&       operator [] (row_index idx)        { 
		TOOLS_CK(is_valid_idx(idx));
		return pos(idx); 
	}

	// Duplication (preferred instead):
	void copy_to(row<omc_t>& dest, 
			row_index first_ii = 0, row_index last_ii = -1,
			bool inv = false)
	{ 
		TOOLS_CK(&dest != this);
		dest.clear(true, true); 
		append_to(dest, first_ii, last_ii, inv);
	}

	void append_to(row<omc_t>& dest, 
			row_index first_ii = 0, row_index last_ii = -1,
			bool inv = false)
	{ 
		if((last_ii < 0) || (last_ii > sz)){
			last_ii = sz;
		}
		if((first_ii < 0) || (first_ii > last_ii)){
			first_ii = 0;
		}
		dest.set_cap(dest.sz + (last_ii - first_ii)); 
		row_index ii = INVALID_IDX;
		if(inv){
			for(ii = last_ii - 1; ii >= first_ii; ii--){
				TOOLS_CK(is_valid_idx(ii));
				omc_t ob = pos(ii);
				dest.push(ob);
			}
		} else {
			for(ii = first_ii; ii < last_ii; ii++){
				TOOLS_CK(is_valid_idx(ii));
				omc_t ob = pos(ii);
				dest.push(ob);
			}
		}
	}

	// sort & selec funcs

	void	selec_sort(cmp_func_t cmp_fn){
		row_index	ii, jj, best_ii;
		omc_t	tmp;
		for (ii = 0; ii < (sz - 1); ii++){
			best_ii = ii;
			for (jj = ii+1; jj < sz; jj++){
				if((*cmp_fn)(pos(jj), pos(best_ii)) < 0){
					best_ii = jj;
				}
			}
			tmp = pos(ii); 
			pos(ii) = pos(best_ii); 
			pos(best_ii) = tmp;
		}
	}

	bool	is_sorted(cmp_func_t cmp_fn){
		if(sz == 0){ return true; }
		omc_t*	lst = &(pos(0));
		for(row_index ii = 1; ii < sz; ii++){
			if((*cmp_fn)(*lst, pos(ii)) > 0){
				return false;
			}
			lst = &(pos(ii));
		}
		return true;
	}

	bool	equal_to(row<omc_t>& rw2, row_index first_ii = 0, row_index last_ii = -1){
		if((sz == 0) && (rw2.size() == 0)){
			return true;
		}
		if((last_ii < 0) && (sz != rw2.size())){
			return false;
		}
		if((last_ii < 0) || (last_ii > sz)){
			last_ii = sz;
		}
		if((first_ii < 0) || (first_ii > last_ii)){
			first_ii = 0;
		}

		if(! is_valid_idx(first_ii)){ return false; }
		if(! is_valid_idx(last_ii - 1)){ return false; }
		if(! rw2.is_valid_idx(first_ii)){ return false; }
		if(! rw2.is_valid_idx(last_ii - 1)){ return false; }

		for (row_index ii = first_ii; ii < last_ii; ii++){
			if(pos(ii) != rw2.pos(ii)){
				return false;
			}
		}
		return true;
	}

	long	equal_to_diff(cmp_func_t cmp_fn, 
				row<omc_t>& rw2, row<omc_t>* diff = mc_null, 
				row_index first_ii = 0, row_index last_ii = -1)
	{
		if((sz == 0) && (rw2.size() == 0)){
			return INVALID_IDX;
		}
		if((last_ii < 0) || (last_ii > sz)){
			last_ii = sz;
		}
		if((first_ii < 0) || (first_ii > last_ii)){
			first_ii = 0;
		}

		if(diff != mc_null){
			diff->fill_new(last_ii);
		}

		long df_pos = INVALID_IDX;
		row_index ii = INVALID_IDX;
		for (ii = first_ii; ii < last_ii; ii++){
			if(! is_valid_idx(ii)){ break; }
			if(! rw2.is_valid_idx(ii)){ break; }
			
			//if(pos(ii) != rw2.pos(ii)){
			if((*cmp_fn)(pos(ii), rw2.pos(ii)) != 0){
				if(diff != mc_null){
					//diff[ii] = pos(ii);
					diff->pos(ii) = pos(ii);
				}
				if(df_pos == INVALID_IDX){
					df_pos = ii;
				}
			}
		}
		if((ii >= 0) && (ii != last_ii)){
			df_pos = ii;
		}
		return df_pos;
	}
};


//================================================================
// row_iter

template<class omc_t>
class row_iter {
public:
	row<omc_t>& 	the_row;
	row_index		the_ref;

	row_iter(row<omc_t>& d_row) : the_row(d_row){
		the_ref = INVALID_IDX;
	}
	row_iter(row_iter& row_it): the_row(row_it.the_row){
		the_ref = INVALID_IDX;
	}
	~row_iter(){
	}

	long	size(){
		return the_row.size();
	}

	void	go_first_ref(){
		if(size() > 0){
			the_ref = 0;
		} else {
			the_ref = INVALID_IDX;
		}
	}

	void	go_last_ref(){
		if(size() > 0){
			the_ref = the_row.last_idx();
		} else {
			the_ref = INVALID_IDX;
		}
	}

	omc_t&	get_obj(){
		return the_row[the_ref]; 
	}
	
	bool 	in_null(){
		return ((the_ref < 0) || (the_ref >= size()));
	}

	void	go_next(){
		the_ref++;
	}

	void	go_prev(){
		the_ref--;
	}

	long 	get_ref(){
		return the_ref;
	}

	void 	operator ++ (){
		go_next();
	}

	void 	operator -- (){
		go_prev();
	}

	void 	operator ++ (int) { ++(*this); }

	void 	operator -- (int) { --(*this); }
};

template<class omc_t>
inline
comparison		cmp_with(row<omc_t>& set1, row<omc_t>& set2, CMP_FN_T(cmp_fn)){
	//row<omc_t> const& set1 = *this;
	if(set1.size() < set2.size()){
		return -1;
	}
	if(set1.size() > set2.size()){
		return 1;
	}
	TOOLS_CK(set1.size() == set2.size());
	for(row_index ii = 0; ii < set1.size(); ii++){
		comparison cmp_resp = (*cmp_fn)(set1.pos(ii), set2.pos(ii));
		if(cmp_resp != 0){ 
			return cmp_resp; 
		}
	}
	return 0;
}


#endif		// ROW_TEMPLATE_H

