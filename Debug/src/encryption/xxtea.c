// original code from http://en.wikipedia.org/wiki/XXTEA
#include "xxtea.h"
#include <string.h>

#define DELTA 0x9e3779b9
#define MX (((z>>5)^(y<<2)) + ((y>>3)^(z<<4))) ^ ((sum^y) + (k[(p&3)^e] ^ z));



void xxtea_setup(xxtea_context *ctx, unsigned char key[16]) {
    int i;

    memset(ctx, 0, sizeof(xxtea_context));

    for( i = 0; i < 4; i++ ) {
        ctx->k[i] = key[i << 2];
    }
}



void xxtea_crypt(xxtea_context *ctx, int mode, unsigned char *data, int len) {
    uint32_t *v, *k, y, z, sum;
    unsigned p, rounds, e;
    int     n;

    v = (uint32_t *)data;
    n = len / 4;
    k = ctx->k;
    if(mode == XXTEA_ENCRYPT) {
        rounds = 6 + 52/n;
        sum = 0;
        z = v[n-1];
        do {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for (p=0; p<n-1; p++) {
                y = v[p+1], z = v[p] += MX;
            }
            y = v[0];
            z = v[n-1] += MX;
        } while (--rounds);
    } else {
        rounds = 6 + 52/n;
        sum = rounds*DELTA;
        y = v[0];
        do {
            e = (sum >> 2) & 3;
            for (p=n-1; p>0; p--) {
                z = v[p-1], y = v[p] -= MX;
            }
            z = v[n-1];
            y = v[0] -= MX;
            sum -= DELTA;
        //} while(sum);
        } while (--rounds);
    }
}


