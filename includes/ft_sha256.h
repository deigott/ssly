#ifndef FT_SHA256_H
# define FT_SHA256_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>


# define uchar unsigned char
# define uint unsigned int

# define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - (c)) ++b; a += c;
# define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
# define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
# define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
# define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
# define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))


typedef struct  s_sha256_ctx{
	uchar data[64];
	uint datalen;
	uint bitlen[2];
	uint state[8];
    char *string;
    unsigned char hash[32];
}               t_sha256_ctx;

void    sha256_init();
void    sha256_transform();
void    sha256_update(uchar *data, uint len);
void    sha256_final();
void    sha256();

#endif