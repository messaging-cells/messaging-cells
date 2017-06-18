

/*------------------------------------------------------------

kptr.hh

kptr class.

--------------------------------------------------------------*/

#ifndef CORE_POINTER_H
#define CORE_POINTER_H

#include "shared.h"

//=================================================================
// kptr

template <typename omc_t, const uint8_t*& base_ptr> class kptr
{
    public:
    uint16_t    disp; // addr disp with respect to base_ptr

    kptr() : disp(mc_null){}
    kptr(omc_t* pt) : disp((uint16_t)((uint8_t*)pt - base_ptr)){}
	kptr(const kptr<omc_t, base_ptr>& kp) : disp(kp.disp){}
    ~kptr(){ disp = mc_null; }

	mc_opt_sz_fn
    omc_t& operator* (){
		omc_t* pt = (omc_t*)(base_ptr + disp);
        return *pt;
    }

	mc_opt_sz_fn
    omc_t* operator-> (){
		omc_t* pt = (omc_t*)(base_ptr + disp);
        return pt;
    }

	mc_opt_sz_fn
	kptr<omc_t, base_ptr>& operator = (const kptr<omc_t, base_ptr>& kp){
		disp = kp.disp;
		return *this;
	}

	mc_opt_sz_fn
	operator omc_t* () const {
		omc_t* pt = (omc_t*)(base_ptr + disp);
        return pt;
    }
};

#endif		// CORE_POINTER_H


