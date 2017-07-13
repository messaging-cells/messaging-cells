
//----------------------------------------------------------------------------
/*! \file log.h

\brief Defines log functions and macros.

*/

#ifndef MC_LOGS_H
#define MC_LOGS_H

#include <inttypes.h>

#include "attribute.h"

#ifdef __cplusplus
mc_c_decl {
#endif

enum mc_out_omc_type_def {
	MC_OUT_LOG,
	MC_OUT_PRT,
	MC_OUT_MSG
};
typedef enum mc_out_omc_type_def mc_out_type_t;

enum mc_type_def {
	MC_CHR,
	MC_I8,
	MC_I16,
	MC_I32,
	MC_UI8,
	MC_UI16,
	MC_UI32,
	MC_X8,
	MC_X16,
	MC_X32
};
typedef enum mc_type_def mc_type_t;

//======================================================================
// log messages

void
mck_aux_sout(char* msg, mc_out_type_t outt) mc_external_code_ram;

//! Logs a string in this core log file
mc_inline_fn void
mck_slog(char* msg){
	mck_aux_sout(msg, MC_OUT_LOG);
}

//! Sames as \ref mck_slog but it does a const_cast<char*> for you so you can use directly it in c++.
#define	mck_slog2(msg) mck_slog(mc_cstr(msg))

//! Prints a string to stdout in the host.
mc_inline_fn void
mck_sprt(char* msg){
	mck_aux_sout(msg, MC_OUT_PRT);
}

//! Sames as \ref mck_sprt but it does a const_cast<char*> for you so you can use directly it in c++.
#define	mck_sprt2(msg) mck_sprt(mc_cstr(msg))

void
mck_aux_iout(uint32_t vv, mc_out_type_t outt, mc_type_t tt) mc_external_code_ram;

//! Logs an int32_t in this core log file
mc_inline_fn void
mck_ilog(int32_t vv){
	mck_aux_iout(vv, MC_OUT_LOG, MC_I32);
}

//! Logs an uint32_t in this core log file
mc_inline_fn void
mck_ulog(uint32_t vv){
	mck_aux_iout(vv, MC_OUT_LOG, MC_UI32);
}

//! Logs an uint32_t as a hexadecimal in this core log file
mc_inline_fn void
mck_xlog(uint32_t vv){
	mck_aux_iout(vv, MC_OUT_LOG, MC_X32);
}

//! Prints an int32_t to stdout in the host.
mc_inline_fn void
mck_iprt(int32_t vv){
	mck_aux_iout(vv, MC_OUT_PRT, MC_I32);
}

//! Prints an uint32_t to stdout in the host.
mc_inline_fn void
mck_uprt(uint32_t vv){
	mck_aux_iout(vv, MC_OUT_PRT, MC_UI32);
}

//! Prints an uint32_t as a hexadecimal to stdout in the host.
mc_inline_fn void
mck_xprt(uint32_t vv){
	mck_aux_iout(vv, MC_OUT_PRT, MC_X32);
}

#ifdef __cplusplus
}
#endif

#endif // MC_LOGS_H

