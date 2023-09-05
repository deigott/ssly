#include "ssly.h"


uint k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

void sha256_transform()
{
	uint a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (g_ssly->sha256_ctx->data[j] << 24) | (g_ssly->sha256_ctx->data[j + 1] << 16) | (g_ssly->sha256_ctx->data[j + 2] << 8) | (g_ssly->sha256_ctx->data[j + 3]);
	for (; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = g_ssly->sha256_ctx->state[0];
	b = g_ssly->sha256_ctx->state[1];
	c = g_ssly->sha256_ctx->state[2];
	d = g_ssly->sha256_ctx->state[3];
	e = g_ssly->sha256_ctx->state[4];
	f = g_ssly->sha256_ctx->state[5];
	g = g_ssly->sha256_ctx->state[6];
	h = g_ssly->sha256_ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	g_ssly->sha256_ctx->state[0] += a;
	g_ssly->sha256_ctx->state[1] += b;
	g_ssly->sha256_ctx->state[2] += c;
	g_ssly->sha256_ctx->state[3] += d;
	g_ssly->sha256_ctx->state[4] += e;
	g_ssly->sha256_ctx->state[5] += f;
	g_ssly->sha256_ctx->state[6] += g;
	g_ssly->sha256_ctx->state[7] += h;
}

void sha256_init()
{
    g_ssly->sha256_ctx = (t_sha256_ctx *)malloc(sizeof(t_sha256_ctx) * 1);
    if (g_ssly->sha256_ctx == NULL)
		show_errors("ssly: error can't allocate\n", EXIT_FAILURE);
	g_ssly->sha256_ctx->datalen = 0;
	g_ssly->sha256_ctx->bitlen[0] = 0;
	g_ssly->sha256_ctx->bitlen[1] = 0;
	g_ssly->sha256_ctx->state[0] = 0x6a09e667;
	g_ssly->sha256_ctx->state[1] = 0xbb67ae85;
	g_ssly->sha256_ctx->state[2] = 0x3c6ef372;
	g_ssly->sha256_ctx->state[3] = 0xa54ff53a;
	g_ssly->sha256_ctx->state[4] = 0x510e527f;
	g_ssly->sha256_ctx->state[5] = 0x9b05688c;
	g_ssly->sha256_ctx->state[6] = 0x1f83d9ab;
	g_ssly->sha256_ctx->state[7] = 0x5be0cd19;

    g_ssly->sha256_ctx->string = NULL;
}

void sha256_update(uchar *data, uint len)
{
	for (uint i = 0; i < len; ++i) {
		g_ssly->sha256_ctx->data[g_ssly->sha256_ctx->datalen] = data[i];
		g_ssly->sha256_ctx->datalen++;
		if (g_ssly->sha256_ctx->datalen == 64) {
			sha256_transform();
			DBL_INT_ADD(g_ssly->sha256_ctx->bitlen[0], g_ssly->sha256_ctx->bitlen[1], 512);
			g_ssly->sha256_ctx->datalen = 0;
		}
	}
}

void sha256_final()
{
	uint i = g_ssly->sha256_ctx->datalen;

	if (g_ssly->sha256_ctx->datalen < 56) {
		g_ssly->sha256_ctx->data[i++] = 0x80;
		while (i < 56)
			g_ssly->sha256_ctx->data[i++] = 0x00;
	}
	else {
		g_ssly->sha256_ctx->data[i++] = 0x80;
		while (i < 64)
			g_ssly->sha256_ctx->data[i++] = 0x00;
		sha256_transform();
		memset(g_ssly->sha256_ctx->data, 0, 56);
	}

	DBL_INT_ADD(g_ssly->sha256_ctx->bitlen[0], g_ssly->sha256_ctx->bitlen[1], g_ssly->sha256_ctx->datalen * 8);
	g_ssly->sha256_ctx->data[63] = g_ssly->sha256_ctx->bitlen[0];
	g_ssly->sha256_ctx->data[62] = g_ssly->sha256_ctx->bitlen[0] >> 8;
	g_ssly->sha256_ctx->data[61] = g_ssly->sha256_ctx->bitlen[0] >> 16;
	g_ssly->sha256_ctx->data[60] = g_ssly->sha256_ctx->bitlen[0] >> 24;
	g_ssly->sha256_ctx->data[59] = g_ssly->sha256_ctx->bitlen[1];
	g_ssly->sha256_ctx->data[58] = g_ssly->sha256_ctx->bitlen[1] >> 8;
	g_ssly->sha256_ctx->data[57] = g_ssly->sha256_ctx->bitlen[1] >> 16;
	g_ssly->sha256_ctx->data[56] = g_ssly->sha256_ctx->bitlen[1] >> 24;
	sha256_transform();

	for (i = 0; i < 4; ++i) {
		g_ssly->sha256_ctx->hash[i] = (g_ssly->sha256_ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		g_ssly->sha256_ctx->hash[i + 4] = (g_ssly->sha256_ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		g_ssly->sha256_ctx->hash[i + 8] = (g_ssly->sha256_ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		g_ssly->sha256_ctx->hash[i + 12] = (g_ssly->sha256_ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		g_ssly->sha256_ctx->hash[i + 16] = (g_ssly->sha256_ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		g_ssly->sha256_ctx->hash[i + 20] = (g_ssly->sha256_ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		g_ssly->sha256_ctx->hash[i + 24] = (g_ssly->sha256_ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		g_ssly->sha256_ctx->hash[i + 28] = (g_ssly->sha256_ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}