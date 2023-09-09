/* byte_order.h */
#ifndef BYTE_ORDER_H
#define BYTE_ORDER_H


# include <stdlib.h>
# include <sys/types.h>
# include <sys/param.h>

#define IS_ALIGNED_32(p) (0 == (3 & (uintptr_t)(p)))
#define IS_ALIGNED_64(p) (0 == (7 & (uintptr_t)(p)))


#if defined(_MSC_VER) || defined(__BORLANDC__)
#define I64(x) x##ui64
#else
#define I64(x) x##ULL
#endif

void rhash_swap_copy_str_to_u64(void* to, int index, const void* from, size_t length);

# define bswap_32(x) __builtin_bswap32(x)
# define bswap_64(x) __builtin_bswap64(x)


# define be2me_32(x) bswap_32(x)
# define be2me_64(x) bswap_64(x)


# define be64_copy(to, index, from, length) rhash_swap_copy_str_to_u64((to), (index), (from), (length))

/* ROTL/ROTR macros rotate a 32/64-bit word left/right by n bits */
#define ROTL32(dword, n) ((dword) << (n) ^ ((dword) >> (32 - (n))))
#define ROTR32(dword, n) ((dword) >> (n) ^ ((dword) << (32 - (n))))
#define ROTL64(qword, n) ((qword) << (n) ^ ((qword) >> (64 - (n))))
#define ROTR64(qword, n) ((qword) >> (n) ^ ((qword) << (64 - (n))))

#endif /* BYTE_ORDER_H */