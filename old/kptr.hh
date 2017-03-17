

/*------------------------------------------------------------

kptr.hh

kptr class.

--------------------------------------------------------------*/

#ifndef CORE_POINTER_H
#define CORE_POINTER_H

#include "shared.h"

//=================================================================
// kptr

template <typename obj_t, const uint8_t*& base_ptr> class kptr
{
    public:
    uint16_t    disp; // addr disp with respect to base_ptr

    kptr() : disp(bj_null){}
    kptr(obj_t* pt) : disp((uint16_t)((uint8_t*)pt - base_ptr)){}
	kptr(const kptr<obj_t, base_ptr>& kp) : disp(kp.disp){}
    ~kptr(){ disp = bj_null; }

	bj_opt_sz_fn
    obj_t& operator* (){
		obj_t* pt = (obj_t*)(base_ptr + disp);
        return *pt;
    }

	bj_opt_sz_fn
    obj_t* operator-> (){
		obj_t* pt = (obj_t*)(base_ptr + disp);
        return pt;
    }

	bj_opt_sz_fn
	kptr<obj_t, base_ptr>& operator = (const kptr<obj_t, base_ptr>& kp){
		disp = kp.disp;
		return *this;
	}

	bj_opt_sz_fn
	operator obj_t* () const {
		obj_t* pt = (obj_t*)(base_ptr + disp);
        return pt;
    }
};

#endif		// CORE_POINTER_H


