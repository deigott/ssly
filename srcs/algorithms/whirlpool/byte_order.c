#include "byte_order.h"

/**
 * Copy a memory block with changed byte order.
 * The byte order is changed from little-endian 64-bit integers
 * to big-endian (or vice-versa).
 *
 * @param to     the pointer where to copy memory block
 * @param index  the index to start writing from
 * @param from   the source block to copy
 * @param length length of the memory block
 */
void rhash_swap_copy_str_to_u64(void* to, int index, const void* from, size_t length)
{
    /* if all pointers and length are 64-bits aligned */
    if ( 0 == (( (uintptr_t)to | (uintptr_t)from | (uintptr_t)index | length ) & 7) ) {
        /* copy aligned memory block as 64-bit integers */
        const uint64_t* src = (const uint64_t*)from;
        const uint64_t* end = (const uint64_t*)((const char*)src + length);
        uint64_t* dst = (uint64_t*)((char*)to + index);
        while (src < end) *(dst++) = bswap_64( *(src++) );
    } else {
        const char* src = (const char*)from;
        for (length += index; (size_t)index < length; index++) ((char*)to)[index ^ 7] = *(src++);
    }
}
