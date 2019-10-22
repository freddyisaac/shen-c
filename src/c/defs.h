#ifndef defs_h
#define defs_h

#ifdef __sgi
#ifdef __mips
#define INLINE static inline
#define EXTERN extern
#endif
#endif // __sgi

// test for gcc > 4.2.0
// I think that the inline semantics changed
// somewhere after 4.1

#ifdef  __GNUC__
#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

#if GCC_VERSION >= 40100
#define INLINE inline
#define EXTERN extern

#endif
#endif


#endif /* defs.h */

