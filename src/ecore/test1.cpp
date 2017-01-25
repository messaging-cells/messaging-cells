
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

struct cla1{
	void fun1();
	//virtual void fun1();
	~cla1();
};

void
cla1::fun1(){
	bj_in_core_shd.cpp_fun1 = 0xbb;
}

cla1::~cla1(){
	bj_in_core_shd.cpp_dcla1 = 0xdd;
}

void
cpp_main(){
	cla1 ss;
	ss.fun1();
}

