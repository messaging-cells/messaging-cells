

/*------------------------------------------------------------

ref_out.hh

ref_out class.

--------------------------------------------------------------*/

#ifndef REFERENCE_OUT_H
#define REFERENCE_OUT_H

#include "shared.h"

//=================================================================
// ref_out

template <typename obj_t, const uint8_t*& base_ptr> 
class ref_out
{
    public:
    uint32_t    disp; // addr disp with respect to base_ptr

    ref_out() : disp(bj_null){}
    ref_out(obj_t* pt) : disp((uint16_t)((uint8_t*)pt - base_ptr)){}
	ref_out(const ref_out<obj_t, base_ptr>& kp) : disp(kp.disp){}
    ~ref_out(){ disp = bj_null; }

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
	ref_out<obj_t, base_ptr>& operator = (const ref_out<obj_t, base_ptr>& kp){
		disp = kp.disp;
		return *this;
	}

	bj_opt_sz_fn
	operator obj_t* () const {
		obj_t* pt = (obj_t*)(base_ptr + disp);
        return pt;
    }
};

#endif		// REFERENCE_OUT_H


