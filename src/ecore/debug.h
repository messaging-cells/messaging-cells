
// debug.h

#ifndef BJ_DEBUG_H
#define BJ_DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef FULL_DEBUG
#	define BJ_DBG(prm) prm
#else
#	define BJ_DBG(prm) /**/ 
#endif

#define BJ_MARK_USED(X)  ((void)(&(X)))

#ifdef __cplusplus
}
#endif

#endif // BJ_DEBUG_H

