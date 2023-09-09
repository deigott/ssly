#ifndef ssly_FT_WHIRLPOOL_H
#define ssly_FT_WHIRLPOOL_H

#define whirlpool_block_size 64

#include <string.h>
#include <stdio.h>
#include "byte_order.h"

/* algorithm context */
typedef struct s_whirlpool_ctx
{
    uint64_t hash[8];    /* 512-bit algorithm internal hashing state */
    unsigned char message[whirlpool_block_size]; /* 512-bit buffer to hash */

    /* Note: original algorithm uses 256-bit counter, allowing to hash up to
       2^256 bits sized message. For optimization, we use here 64-bit counter,
       thus reducing maximal message size to 2^64 bits = 2 Exbibytes = 2^21 TiB)
    */
    uint64_t length;     /* number of processed bytes */
    char        *string;
    unsigned char result[512];
}           t_whirlpool_ctx;

/* hash functions */

void    whirlpool_init();
void    whirlpool_update(const unsigned char* msg, size_t size);
void    whirlpool_final();
void    whirlpool( void );

#endif //ssly_FT_WHIRLPOOL_H
