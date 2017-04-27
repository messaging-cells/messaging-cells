
// log.h

#ifndef BJ_LOGS_H
#define BJ_LOGS_H

#include <inttypes.h>

#include "attribute.h"

#ifdef __cplusplus
bj_c_decl {
#endif

enum bj_out_obj_type_def {
	BJ_OUT_LOG,
	BJ_OUT_PRT,
	BJ_OUT_MSG
};
typedef enum bj_out_obj_type_def bj_out_type_t;

enum bj_type_def {
	BJ_CHR,
	BJ_I8,
	BJ_I16,
	BJ_I32,
	BJ_UI8,
	BJ_UI16,
	BJ_UI32,
	BJ_X8,
	BJ_X16,
	BJ_X32
};
typedef enum bj_type_def bj_type_t;

//======================================================================
// log messages

void
bjk_aux_sout(char* msg, bj_out_type_t outt) bj_external_code_ram;

bj_inline_fn void
bjk_slog(char* msg){
	bjk_aux_sout(msg, BJ_OUT_LOG);
}

#define	bjk_slog2(msg) bjk_slog(as_pt_char(msg))

bj_inline_fn void
bjk_sprt(char* msg){
	bjk_aux_sout(msg, BJ_OUT_PRT);
}

#define	bjk_sprt2(msg) bjk_sprt(as_pt_char(msg))

void
bjk_aux_iout(uint32_t vv, bj_out_type_t outt, bj_type_t tt) bj_external_code_ram;

bj_inline_fn void
bjk_ilog(int32_t vv){
	bjk_aux_iout(vv, BJ_OUT_LOG, BJ_I32);
}

bj_inline_fn void
bjk_ulog(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_LOG, BJ_UI32);
}

bj_inline_fn void
bjk_xlog(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_LOG, BJ_X32);
}

bj_inline_fn void
bjk_iprt(int32_t vv){
	bjk_aux_iout(vv, BJ_OUT_PRT, BJ_I32);
}

bj_inline_fn void
bjk_uprt(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_PRT, BJ_UI32);
}

bj_inline_fn void
bjk_xprt(uint32_t vv){
	bjk_aux_iout(vv, BJ_OUT_PRT, BJ_X32);
}

#ifdef __cplusplus
}
#endif

#endif // BJ_LOGS_H

