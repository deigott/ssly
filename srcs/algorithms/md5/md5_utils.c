#include "ssly.h"


static uint32_t S[] = {
   7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
   5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
   4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
   6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static uint32_t K[] = {
   0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
   0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
   0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
   0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
   0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
   0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
   0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
   0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
   0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
   0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
   0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
   0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
   0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
   0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
   0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
   0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

/*
 * Padding used to make the size (in bits) of the input congruent to 448 mod 512
 */
static uint8_t PADDING[] = {
   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


/*
 * Rotates a 32-bit word left by n bits
 */
uint32_t rotateLeft(uint32_t x, uint32_t n){
    return (x << n) | (x >> (32 - n));
}

void  md5_init(void)
{
    g_ssly->md5_ctx = (t_md5_ctx *)malloc(sizeof(t_md5_ctx) * 1);
    if (g_ssly->md5_ctx == NULL)
        show_errors("ft_ssl: error can't allocate\n", EXIT_FAILURE);
    if (g_ssly)
    g_ssly->md5_ctx->size = (uint64_t)0;

    g_ssly->md5_ctx->buffer[0] = (uint32_t)A;
    g_ssly->md5_ctx->buffer[1] = (uint32_t)B;
    g_ssly->md5_ctx->buffer[2] = (uint32_t)C;
    g_ssly->md5_ctx->buffer[3] = (uint32_t)D;
    g_ssly->md5_ctx->string = NULL;
    return ;   
}

void  md5_algo(uint32_t *input)
{
    uint32_t AA;
    uint32_t BB;
    uint32_t CC;
    uint32_t DD;
    uint32_t E;
    unsigned int j;
    uint32_t temp;

    AA = g_ssly->md5_ctx->buffer[0];
    BB = g_ssly->md5_ctx->buffer[1];
    CC = g_ssly->md5_ctx->buffer[2];
    DD = g_ssly->md5_ctx->buffer[3];
    for(unsigned int i = 0; i < 64; ++i){
        if (i < 16)
        {
                E = F(BB, CC, DD);
                j = i;
        }
        else if (i < 32)
        {
                E = G(BB, CC, DD);
                j = ((i * 5) + 1) % 16;
        }
        else if (i < 48)
        {
                E = H(BB, CC, DD);
                j = ((i * 3) + 5) % 16;
        }
        else
        {
                E = I(BB, CC, DD);
                j = (i * 7) % 16;
        }

        temp = DD;
        DD = CC;
        CC = BB;
        BB = BB + rotateLeft(AA + E + K[i] + input[j], S[i]);
        AA = temp;
    }

    g_ssly->md5_ctx->buffer[0] += AA;
    g_ssly->md5_ctx->buffer[1] += BB;
    g_ssly->md5_ctx->buffer[2] += CC;
    g_ssly->md5_ctx->buffer[3] += DD;
    return ;
}

void  md5_update(uint8_t *buffer, size_t input_len)
{
    uint32_t input[16];
    unsigned int offset;


    offset = g_ssly->md5_ctx->size % 64;

    g_ssly->md5_ctx->size += (uint64_t) input_len;
    // Copy each byte in input_buffer into the next space in our context input
    for(unsigned int i = 0; i < input_len; ++i){
        g_ssly->md5_ctx->input[offset++] = (uint8_t)*(buffer + i);

        // If we've filled our context input, copy it into our local array input
        // then reset the offset to 0 and fill in a new buffer.
        // Every time we fill out a chunk, we run it through the algorithm
        // to enable some back and forth between cpu and i/o
        if(offset % 64 == 0){
            for(unsigned int j = 0; j < 16; ++j){
                // Convert to little-endian
                // The local variable `input` our 512-bit chunk separated into 32-bit words
                // we can use in calculations
                input[j] = (uint32_t)(g_ssly->md5_ctx->input[(j * 4) + 3]) << 24 |
                           (uint32_t)(g_ssly->md5_ctx->input[(j * 4) + 2]) << 16 |
                           (uint32_t)(g_ssly->md5_ctx->input[(j * 4) + 1]) <<  8 |
                           (uint32_t)(g_ssly->md5_ctx->input[(j * 4)]);
            }
            md5_algo(input);
            offset = 0;
        }
    }
}

void  md5_final(void)
{
    uint32_t input[16];
    unsigned int offset;
    unsigned int padding_length;
    
    offset = g_ssly->md5_ctx->size % 64;
    padding_length = offset < 56 ? 56 - offset : (56 + 64) - offset;

    // Fill in the padding and undo the changes to size that resulted from the update
    md5_update(PADDING, padding_length);
    g_ssly->md5_ctx->size -= (uint64_t)padding_length;

    // Do a final update (internal to this function)
    // Last two 32-bit words are the two halves of the size (converted from bytes to bits)
    for(unsigned int j = 0; j < 14; ++j){
        input[j] = (uint32_t)(g_ssly->md5_ctx->input[(j * 4) + 3]) << 24 |
                   (uint32_t)(g_ssly->md5_ctx->input[(j * 4) + 2]) << 16 |
                   (uint32_t)(g_ssly->md5_ctx->input[(j * 4) + 1]) <<  8 |
                   (uint32_t)(g_ssly->md5_ctx->input[(j * 4)]);
    }
    input[14] = (uint32_t)(g_ssly->md5_ctx->size * 8);
    input[15] = (uint32_t)((g_ssly->md5_ctx->size * 8) >> 32);

    md5_algo(input);

    // Move the result into digest (convert from little-endian)
    for(unsigned int i = 0; i < 4; ++i){
        g_ssly->md5_ctx->digest[(i * 4) + 0] = (uint8_t)((g_ssly->md5_ctx->buffer[i] & 0x000000FF));
        g_ssly->md5_ctx->digest[(i * 4) + 1] = (uint8_t)((g_ssly->md5_ctx->buffer[i] & 0x0000FF00) >>  8);
        g_ssly->md5_ctx->digest[(i * 4) + 2] = (uint8_t)((g_ssly->md5_ctx->buffer[i] & 0x00FF0000) >> 16);
        g_ssly->md5_ctx->digest[(i * 4) + 3] = (uint8_t)((g_ssly->md5_ctx->buffer[i] & 0xFF000000) >> 24);
    }
}
