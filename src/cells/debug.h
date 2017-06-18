
// debug.h

#ifndef MC_DEBUG_H
#define MC_DEBUG_H

#define mc_c_decl extern "C"

#ifdef __cplusplus
mc_c_decl {
#endif

#ifdef FULL_DEBUG
#	define MC_DBG(prm) prm
#else
#	define MC_DBG(prm) /**/ 
#endif

#define MC_MARK_USED(X)  ((void)(&(X)))

#ifdef __cplusplus
}
#endif

#endif // MC_DEBUG_H

