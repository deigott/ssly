#ifndef FT_MD5_H
#define FT_MD5_H

# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>

/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;


/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))




 typedef struct s_md5_ctx
 {
    UINT4 A;
    UINT4 B;
    UINT4 C;
    UINT4 D;
    UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];
 }              t_md5_ctx;


void md5_init(void);
void md5_update(void);
void md5_final(void);
void md5( void );

#endif