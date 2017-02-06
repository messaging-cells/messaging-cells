
#include <cstdlib>
#include <new>

#include "global.h"
#include "trace.h"
#include "test1.h"

/*
void * operator new(size_t sz) noexcept {
	return 0;
}

void operator delete(void *pt) noexcept {
}

void * operator new[](size_t sz) noexcept {
	return operator new(sz);
}

void operator delete[](void *pt) noexcept {
	operator delete(pt);
}

void * operator new(size_t sz, std::nothrow_t) noexcept {
	return operator new(sz);
}

void operator delete(void *pt, std::nothrow_t) noexcept {
	operator delete(pt);
}*/

typedef uint8_t bj_actor_id_t;

#define bj_actor_id(cls) BJ_ACT_##cls

#define bj_actor_set_id(cls) \
	bj_all_actor_ids_arr[bj_actor_id(cls)] = as_pt_char("{" #cls "}");


#define as_pt_char(the_str) (const_cast<char *>(the_str))

enum bj_all_actor_ids {
	bj_actor_id(core_actor),
	bj_actor_id(receiver_actor),
	bj_tot_actor_ids
};

char* bj_all_actor_ids_arr[bj_tot_actor_ids];

void bj_init_all_actor_ids(){
	bj_actor_set_id(core_actor);
	bj_actor_set_id(receiver_actor);
};

class core_actor{
public:
	bj_actor_id_t id;
	void fun1();
	//virtual void fun1();
	~core_actor();
};

void
core_actor::fun1(){
	bj_in_core_shd.cpp_fun1 = 0xbb;
}

core_actor::~core_actor(){
	bj_in_core_shd.cpp_dcla1 = 0xdd;
}

void
cpp_main(){
	core_actor ss;
	ss.fun1();
}

