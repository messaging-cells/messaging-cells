

/*------------------------------------------------------------

ref_out.hh

ref_out class.

--------------------------------------------------------------*/

#ifndef REFERENCE_OUT_H
#define REFERENCE_OUT_H

#include "shared.h"

//=================================================================
// ref_out

template <typename omc_t, const uint8_t*& base_ptr> 
class ref_out
{
    public:
    uint32_t    disp; // addr disp with respect to base_ptr

    ref_out() : disp(mc_null){}
    ref_out(omc_t* pt) : disp((uint16_t)((uint8_t*)pt - base_ptr)){}
	ref_out(const ref_out<omc_t, base_ptr>& kp) : disp(kp.disp){}
    ~ref_out(){ disp = mc_null; }

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
	ref_out<omc_t, base_ptr>& operator = (const ref_out<omc_t, base_ptr>& kp){
		disp = kp.disp;
		return *this;
	}

	mc_opt_sz_fn
	operator omc_t* () const {
		omc_t* pt = (omc_t*)(base_ptr + disp);
        return pt;
    }
};

#endif		// REFERENCE_OUT_H


