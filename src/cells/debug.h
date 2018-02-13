
// debug.h

#ifndef MC_DEBUG_H
#define MC_DEBUG_H

#define mc_c_decl extern "C"

#define MC_STRINGIFY(x) #x
#define MC_TOSTRING(x) MC_STRINGIFY(x)

#define MC_ABORT_MSG(msg) mc_cstr("ABORTING. '" msg "' at " __FILE__ "(" MC_TOSTRING(__LINE__) ")")

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

