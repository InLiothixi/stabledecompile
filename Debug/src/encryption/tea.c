// layout from xtea.c and code from my halo_pck_algo.h

#include "tea.h"
#include <string.h>

#ifndef GET_ULONG_BE
#define GET_ULONG_BE(n,b,i)                             \
{                                                       \
    (n) = ( (unsigned long) (b)[(i)    ] << 24 )        \
        | ( (unsigned long) (b)[(i) + 1] << 16 )        \
        | ( (unsigned long) (b)[(i) + 2] <<  8 )        \
        | ( (unsigned long) (b)[(i) + 3]       );       \
}
#endif

#ifndef PUT_ULONG_BE
#define PUT_ULONG_BE(n,b,i)                             \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif



void tea_setup(tea_context *ctx, unsigned char key[16]) {
    int i;

    memset(ctx, 0, sizeof(tea_context));

    for( i = 0; i < 4; i++ ) {
        GET_ULONG_BE( ctx->k[i], key, i << 2 );
    }
}



void tea_crypt(tea_context *ctx, int mode, unsigned char input[8], unsigned char output[8]) {
    uint32_t *k, y, z, i, sum;

    k = ctx->k;
    
    GET_ULONG_BE(y, input, 0);
    GET_ULONG_BE(z, input, 4);

    if(mode == TEA_ENCRYPT) {
        sum = 0;
        for(i = 0; i < 32; i++) {
            sum += 0x9e3779b9;
            y += ((z << 4) + k[0]) ^ (z + sum) ^ ((z >> 5) + k[1]);
            z += ((y << 4) + k[2]) ^ (y + sum) ^ ((y >> 5) + k[3]);
        }
    } else {
        sum = 0xc6ef3720;
        for(i = 0; i < 32; i++) {
            z -= ((y << 4) + k[2]) ^ (y + sum) ^ ((y >> 5) + k[3]);
            y -= ((z << 4) + k[0]) ^ (z + sum) ^ ((z >> 5) + k[1]);
            sum -= 0x9e3779b9;
        }
    }

    PUT_ULONG_BE(y, output, 0);
    PUT_ULONG_BE(z, output, 4);
}


