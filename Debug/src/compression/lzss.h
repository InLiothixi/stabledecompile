// by Luigi Auriemma
// partially derived from the original code of Okumura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unlzss(unsigned char *src, int srclen, unsigned char *dst, int dstlen) {
    int EI = 12;    /* typically 10..13 */
    int EJ = 4;     /* typically 4..5 */
    int P  = 2;     /* If match length <= P then output one character */
    int N;
    int F;
    int rless = P;  // in some rare implementations it could be 0
    int init_chr = ' ';

    static int slide_winsz = 0;
    static unsigned char *slide_win = NULL;
    unsigned char *dststart = dst;
    unsigned char *srcend = src + srclen;
    unsigned char *dstend = dst + dstlen;
    int  i, j, k, r, c;
    unsigned flags;

    if(comtype_dictionary && (comtype_dictionary_len > 0)) {
        sscanf(comtype_dictionary, "%d %d %d %d %d", &EI, &EJ, &P, &rless, &init_chr);
    }
    N = 1 << EI;
    F = 1 << EJ;

    if(N > slide_winsz) {
        slide_win   = realloc(slide_win, N);
        if(!slide_win) return(-1);
        slide_winsz = N;
    }
    memset(slide_win, init_chr, N);

    dst = dststart;
    srcend = src + srclen;
    r = (N - F) - rless;
    N--;
    F--;

    for(flags = 0;; flags >>= 1) {
        if(!(flags & 0x100)) {
            if(src >= srcend) break;
            flags = *src++;
            flags |= 0xff00;
        }
        if(flags & 1) {
            if(src >= srcend) break;
            c = *src++;
            if(dst >= dstend) return(-1);
            *dst++ = c;
            slide_win[r] = c;
            r = (r + 1) & N;
        } else {
            if(src >= srcend) break;
            i = *src++;
            if(src >= srcend) break;
            j = *src++;
            i |= ((j >> EJ) << 8);
            j  = (j & F) + P;
            for(k = 0; k <= j; k++) {
                c = slide_win[(i + k) & N];
                if(dst >= dstend) return(-1);
                *dst++ = c;
                slide_win[r] = c;
                r = (r + 1) & N;
            }
        }
    }

    return(dst - dststart);
}
