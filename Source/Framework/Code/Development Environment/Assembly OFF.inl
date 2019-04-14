#ifdef ASM_REDEFINE_and
#define and &&
#undef ASM_REDEFINE_and
#endif
#ifdef ASM_REDEFINE_or
#define or ||
#undef ASM_REDEFINE_or
#endif
#ifdef ASM_REDEFINE_not
#define not !
#undef ASM_REDEFINE_not
#endif
#ifdef ASM_REDEFINE_xor
#define xor ^
#undef ASM_REDEFINE_xor
#endif
