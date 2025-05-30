// all the compression algorithms

#define MYALLOC_ZEROES  16  // long story, anyway keep 16 for both XmemDecompress and general padding/blocks (indeed AES uses 16 bytes)
#define ASURACMP    // comment it if the input doesn't have the first 8 bytes assigned to zsize and size
#include "compression/asura_huffboh.c"
#include "compression/lzss.h"
	#define QLZ_COMPRESSION_LEVEL 3 // lame solution to avoid to use "unsigned int" which is not supported in QuickBMS
	#define QLZ_STREAMING_BUFFER 0
#include "compression/quicklz.h"
#include "compression/unq3huff.c"
#include "compression/unrlew.h"
#include "compression/unmeng.h"
#include "compression/unlz2k.h"
#include "compression/undarksector.h"
#include "compression/un49g.h"
#include "compression/unthandor.c"
#include "compression/tzar_lzss.h"
#include "compression/lzh.h"
#include "compression/sr3c.h"
#include "compression/undk2.h"
#include "compression/stalker_lza.h"
#include "compression/puyo.c"
#include "compression/nintendo.h"
#include "lzhl/lzhl.h"
#include "compression/rdc.h"
#include "compression/ilzr.h"
#include "compression/libLZR.h"
#include "compression/mppc.c"
#include "compression/un434a.h"
int dmc2_uncompress(unsigned char *in, int insz, unsigned char *out, int outsz);
int ahuff_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int arith_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int arith1_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int arith1e_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int arithn_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int compand_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int huff_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int lzss_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int lzw12_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int lzw15v_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
int silence_ExpandMemory(unsigned char *in, int insz, unsigned char *out, int outsz);
void lzrw3a_decompress(unsigned char*,unsigned char*,int,unsigned char *,int *);
int unsqueeze(unsigned char *in, int insz, unsigned char *out, int outsz);
int d3101(unsigned char *in, int insz, unsigned char *out, int outsz);
int yuke_bpe(unsigned char *in, int insz, unsigned char *out, int outsz, int fill_outsz);
int huffman_decode_memory(const unsigned char *bufin, int bufinlen, unsigned char **bufout, int *pbufoutlen);
void HuffInit (float *myfreq);
void HuffDecode (const unsigned char *in, unsigned char *out, int inlen, int *outlen, const int maxlen);
void Huffman_Uncompress( unsigned char *in, unsigned char *out, unsigned insize, unsigned outsize );
void LZ_Uncompress( unsigned char *in, unsigned char *out, unsigned insize );
void Rice_Uncompress( void *in, void *out, unsigned insize, unsigned outsize, int format );
unsigned RLE_Uncompress( unsigned char *in, unsigned insize, unsigned char *out, unsigned outsize );
void SF_Uncompress( unsigned char *in, unsigned char *out, unsigned insize, unsigned outsize );
int Scz_Decompress_Buffer2Buffer( char *inbuffer, int N, char **outbuffer, int *M );
int szip_allow_encoding = 0;
int SZ_BufftoBuffDecompress(void *dest, size_t *destLen, const void *source, size_t sourceLen, void *param);
int unbpe2(unsigned char *in, int insz, unsigned char *out, int outsz);
int strexpand(char *dest, unsigned char *source, int maxlen, unsigned char **pairtable);
int hstest_hs_unpack(unsigned char *out, unsigned char *in, int insz);
int hstest_unpackc(unsigned char *out, unsigned char *in, int insz);
int unsixpack(unsigned char *in, int insz, unsigned char *out, int outsz);
int unashford(unsigned char *in, int insz, unsigned char *out, int outsz);
__stdcall int JCALG1_Decompress_Small(void *Source, void *Destination);
int unjam(unsigned char *in, int insz, unsigned char *out, int outsz);
int unsrank(unsigned char *in, int insz, unsigned char *out, int outsz);
int ZzUncompressBlock(unsigned char *buffer);
int sh_DecodeBlock(unsigned char *iBlock, unsigned char *oBlock, int bSize);
unsigned blz_depack(const void *source, void *destination, unsigned depacked_length);
int unpaq6(unsigned char *in, int insz, unsigned char *out, int outsz, int levelx);
int unppmdi1(unsigned char *in, int insz, unsigned char *out, int outsz);
int unppmdi1_raw(unsigned char *in, int insz, unsigned char *out, int outsz, int SaSize, int MaxOrder, int MRMethod);
int unppmdg(unsigned char *in, int insz, unsigned char *out, int outsz);
int unppmdg_raw(unsigned char *in, int insz, unsigned char *out, int outsz, int SaSize, int MaxOrder);
int unppmdj1(unsigned char *in, int insz, unsigned char *out, int outsz);
int unppmdj1_raw(unsigned char *in, int insz, unsigned char *out, int outsz, int SaSize, int MaxOrder, int CutOff);
int unshrink(unsigned char *in, int insz, unsigned char *out, int outsz);
int unquad(unsigned char *src, int srcsz, unsigned char *dst, int dstsz);
int unbalz(unsigned char *src, int srcsz, unsigned char *dst, int dstsz);
unsigned GRZip_DecompressBlock(unsigned char * Input, unsigned Size, unsigned char * Output);
int de_lzah(unsigned char *in, int insz, unsigned char *out, int obytes);
int de_lzh(unsigned char *in, int ibytes, unsigned char *out, int obytes, int bits);
int lzf_decompress(const void *const in_data, int in_len, void *out_data, int out_len);
unsigned aP_depack_safe(const void *source, unsigned srclen, void *destination, unsigned dstlen);
int bpe_expand(unsigned char *in, int insz, unsigned char *out, int outsz);
int unlzh(unsigned char *in, int insz, unsigned char *out, int outsz);
int unlzari(unsigned char *in, int insz, unsigned char *out, int outsz);
int uncompress_lzw(unsigned char *in, int insz, unsigned char *out, int outsz);
int undmc(unsigned char *in, int insz, unsigned char *out, int outsz);
int unlzx(unsigned char *in, int insz, unsigned char *out, int outsz);
int unmslzx(unsigned char *in, int insz, unsigned char *out, int outsz, int window_bits, int interval);
uint32_t unlzw(uint8_t *outbuff, uint32_t maxsize, uint8_t *in, uint32_t insize);
uint32_t unlzwx(uint8_t *outbuff, uint32_t maxsize, uint8_t *in, uint32_t insize);



#define QUICK_IN_OUT \
    unsigned char   *inl    = in + insz, \
                    *o      = out, \
                    *outl   = out + outsz;

#define lame_feof(X)    ((infile  >= infilel)  ? EOF : 0)
#define lame_getc(X)    ((infile  >= infilel)  ? EOF : (*infile++))
#define lame_putc(Y,X)  ((outfile >= outfilel) ? EOF : (*outfile++ = Y))
#define lame_fgetc      lame_getc
#define lame_fputc      lame_putc



int uncopy(unsigned char *in, int insz, unsigned char *out, int outsz) {
    if(outsz > insz) outsz = insz;
    memcpy(out, in, outsz);
    return(outsz);
}



int unlzo(u8 *in, int insz, u8 *out, int outsz, int type) {
#ifdef DISABLE_LZO
    printf("\nError: LZO support has been disabled in this build\n");
    return(-1);
#else
    lzo_uint    len;
    int         err = LZO_E_OK;

    len = outsz;
    switch(type) {
        case COMP_LZO1:  { err = lzo1_decompress(in, insz, out, &len, NULL); break; }
        case COMP_LZO1A: { err = lzo1a_decompress(in, insz, out, &len, NULL); break; }
        case COMP_LZO1B: { err = lzo1b_decompress_safe(in, insz, out, &len, NULL); break; }
        case COMP_LZO1C: { err = lzo1c_decompress_safe(in, insz, out, &len, NULL); break; }
        case COMP_LZO1F: { err = lzo1f_decompress_safe(in, insz, out, &len, NULL); break; }
        case COMP_LZO1X: {
            if(comtype_dictionary) {
                err = lzo1x_decompress_dict_safe(in, insz, out, &len, NULL, comtype_dictionary, comtype_dictionary_len);
            } else {
                err = lzo1x_decompress_safe(in, insz, out, &len, NULL);
            }
            break; }
        case COMP_LZO1Y: {
            if(comtype_dictionary) {
                err = lzo1y_decompress_dict_safe(in, insz, out, &len, NULL, comtype_dictionary, comtype_dictionary_len);
            } else {
                err = lzo1y_decompress_safe(in, insz, out, &len, NULL);
            }
            break; }
        case COMP_LZO1Z: {
            if(comtype_dictionary) {
                err = lzo1z_decompress_dict_safe(in, insz, out, &len, NULL, comtype_dictionary, comtype_dictionary_len);
            } else {
                err = lzo1z_decompress_safe(in, insz, out, &len, NULL);
            }
            break; }
        case COMP_LZO2A: { err = lzo2a_decompress_safe(in, insz, out, &len, NULL); break; }
        default: {
            printf("\nError: unsupported LZO decompression %d\n", type);
            return(-1);
            break;
        }
    }
    if((err != LZO_E_OK) && (err != LZO_E_INPUT_NOT_CONSUMED)) {
        printf("\nError: the compressed LZO input is wrong or incomplete (%d)\n", err);
        return(-1);
    }
    return(len);
#endif
}



int unucl(u8 *in, int insz, u8 *out, int outsz, int type) {
#ifdef DISABLE_UCL
    printf("\nError: UCL support has been disabled in this build\n");
    return(-1);
#else
    ucl_uint    len;
    int         err = UCL_E_OK;

    len = outsz;
    switch(type) {
        case COMP_NRV2b: { err = ucl_nrv2b_decompress_safe_8(in, insz, out, &len, NULL); break; }
        case COMP_NRV2d: { err = ucl_nrv2d_decompress_safe_8(in, insz, out, &len, NULL); break; }
        case COMP_NRV2e: { err = ucl_nrv2e_decompress_safe_8(in, insz, out, &len, NULL); break; }
        default: {
            printf("\nError: unsupported UCL decompression %d\n", type);
            return(-1);
            break;
        }
    }
    if((err != UCL_E_OK) && (err != UCL_E_INPUT_NOT_CONSUMED)) {
        printf("\nError: the compressed UCL input is wrong or incomplete (%d)\n", err);
        return(-1);
    }
    return(len);
#endif
}



#define UNZIP_BASE(NAME,WBITS) \
int NAME(u8 *in, int insz, u8 *out, int outsz) { \
    static z_stream *z  = NULL; \
    int     ret; \
    \
    if(!in && !out) { \
        if(z) { \
            inflateEnd(z); \
            free(z); \
        } \
        z = NULL; \
        return(-1); \
    } \
    \
    if(!z) { \
        z = malloc(sizeof(z_stream)); \
        if(!z) return(-1); \
        z->zalloc = Z_NULL; \
        z->zfree  = Z_NULL; \
        z->opaque = Z_NULL; \
        if(inflateInit2(z, WBITS)) { \
            printf("\nError: zlib initialization error\n"); \
            return(-1); \
        } \
    } \
    inflateReset(z); \
    \
    if(comtype_dictionary) { \
        inflateSetDictionary(z, comtype_dictionary, comtype_dictionary_len); \
    } \
    \
    z->next_in   = in; \
    z->avail_in  = insz; \
    z->next_out  = out; \
    z->avail_out = outsz; \
    ret = inflate(z, Z_FINISH); \
    if(ret != Z_STREAM_END) { \
        printf("\nError: the compressed zlib/deflate input is wrong or incomplete (%d)\n", ret); \
        return(-1); \
    } \
    return(z->total_out); \
}

UNZIP_BASE(unzip_zlib,    15)
UNZIP_BASE(unzip_deflate, -15)



int unzip_dynamic(u8 *in, int insz, u8 **ret_out, int *ret_outsz) {
    z_stream z;
    int     err,
            retsz,
            addsz,
            wbits;

    if(in[0] == 0x78) {
        wbits = 15;     // zlib
    } else {
        wbits = -15;    // deflate
    }

    z.zalloc = NULL;
    z.zfree  = NULL;
    z.opaque  = NULL;
    if(inflateInit2(&z, wbits)) {
        printf("\nError: zlib initialization error\n");
        return(-1);
    }

    addsz = insz / 4;
    if(!addsz) addsz = insz;

    retsz = 0;
    z.next_in  = in;
    z.avail_in = insz;
    for(;;) {
        z.next_out  = *ret_out + retsz;
        z.avail_out = *ret_outsz - retsz;
        err = inflate(&z, Z_FINISH);
        if(err == Z_STREAM_END) break;
        if(err == Z_OK) {
            retsz = (u8 *)z.next_out - *ret_out;
            *ret_outsz += addsz;
            *ret_out = realloc(*ret_out, *ret_outsz);
            if(!*ret_out) STD_ERR;
            continue;
        }
        inflateEnd(&z);
        printf("\nError: invalid z2 compressed data (%d)\n", err);
        return(-1);
    }

    retsz = (u8 *)z.next_out - *ret_out;
    inflateEnd(&z);
    return(retsz);
}



#ifdef WIN32    // it's a zlib with the adding of inflateBack9 which is not default
#include "compression/infback9.h"
typedef struct {
    u8      *p;
    u8      *l;
} zlib_func_t;
static unsigned zlib_inf(zlib_func_t *data, u8 **ret) {
    unsigned    len;

    *ret = data->p;
    len = data->l - data->p;
    data->p += len;
    return(len);
}
static int zlib_outf(zlib_func_t *data, u8 *buff, int len) {
    int     size;

    size = data->l - data->p;
    if((data->p + len) > data->l) return(-1);
    memcpy(data->p, buff, len);
    data->p += len;
    return(0);
}
int inflate64(u8 *in, int insz, u8 *out, int outsz) {
    static unsigned char window[65536L];  // from gun.c
    zlib_func_t myin,
                myout;
    static z_stream z;  // I don't know if inflate64 supports Reset
    int     ret;

    z.zalloc = Z_NULL;
    z.zfree  = Z_NULL;
    z.opaque = Z_NULL;
    if(inflateBack9Init(&z, window)) {
        printf("\nError: inflate64 initialization error\n");
        return(-1);
    }

    if(comtype_dictionary) {    // supported?
        inflateSetDictionary(&z, comtype_dictionary, comtype_dictionary_len);
    }

    myin.p  = in;
    myin.l  = in + insz;
    myout.p = out;
    myout.l = out + outsz;

    z.next_in   = in;
    z.avail_in  = insz;
    z.next_out  = out;
    z.avail_out = outsz;
    ret = inflateBack9(&z,
        (void *)zlib_inf,  &myin,
        (void *)zlib_outf, &myout);
    if(ret != Z_STREAM_END) {
        inflateBack9End(&z);    // reset not supported by inflate9
        printf("\nError: the compressed deflate64 input is wrong or incomplete (%d)\n", ret);
        return(-1);
    }

    outsz = myout.p - out;
    inflateBack9End(&z);
    return(outsz);
}
#else
int inflate64(u8 *in, int insz, u8 *out, int outsz) {
    printf("\nError: inflate64 is not supported on this platform\n");
    myexit(-1);
}
#endif



int unbzip2(u8 *in, int insz, u8 *out, int outsz) { // no reset in bzlib
    int     err;

    err = BZ2_bzBuffToBuffDecompress(out, &outsz, in, insz, 0, 0);
    if(err != BZ_OK) {
        printf("\nError: invalid bz2 compressed data (%d)\n", err);
        return(-1);
    }
    return(outsz);
}



int unbzip2_file(u8 *in, int insz, u8 **ret_out, int *ret_outsz) { // no reset in bzlib
    bz_stream bz;
    int     err,
            retsz,
            addsz;

    bz.bzalloc = NULL;
    bz.bzfree  = NULL;
    bz.opaque  = NULL;
    if(BZ2_bzDecompressInit(&bz, 0, 0)
      != BZ_OK) return(-1);

    addsz = insz / 4;
    if(!addsz) addsz = insz;

    retsz = 0;
    bz.next_in  = in;
    bz.avail_in = insz;
    for(;;) {
        bz.next_out  = *ret_out + retsz;
        bz.avail_out = *ret_outsz - retsz;
        err = BZ2_bzDecompress(&bz);
        if(err == BZ_STREAM_END) break;
        if(err == BZ_OK) {
            retsz = (u8 *)bz.next_out - *ret_out;
            *ret_outsz += addsz;
            *ret_out = realloc(*ret_out, *ret_outsz);
            if(!*ret_out) STD_ERR;
            continue;
        }
        BZ2_bzDecompressEnd(&bz);
        printf("\nError: invalid bz2 compressed data (%d)\n", err);
        return(-1);
    }

    retsz = (u8 *)bz.next_out - *ret_out;
    BZ2_bzDecompressEnd(&bz);
    return(retsz);
}



int unxmemlzx(u8 *in, int insz, u8 *out, int outsz) {
#ifdef WIN32
    typedef VOID*                       XMEMDECOMPRESSION_CONTEXT;
    typedef enum _XMEMCODEC_TYPE {
        XMEMCODEC_DEFAULT =             0,
        XMEMCODEC_LZX =                 1
    } XMEMCODEC_TYPE;
    typedef struct _XMEMCODEC_PARAMETERS_LZX {
        DWORD Flags;
        DWORD WindowSize;
        DWORD CompressionPartitionSize;
    } XMEMCODEC_PARAMETERS_LZX;
    HRESULT WINAPI XMemCreateDecompressionContext(
        XMEMCODEC_TYPE                  CodecType,
        CONST VOID*                     pCodecParams,
        DWORD                           Flags,
        XMEMDECOMPRESSION_CONTEXT*      pContext
    );
    HRESULT WINAPI XMemDecompress(
        XMEMDECOMPRESSION_CONTEXT       Context,
        VOID*                           pDestination,
        SIZE_T*                         pDestSize,
        CONST VOID*                     pSource,
        SIZE_T                          SrcSize
    );

    static XMEMDECOMPRESSION_CONTEXT ctx = NULL;
    static XMEMCODEC_PARAMETERS_LZX  *param = NULL;
    SIZE_T  ret;
    HRESULT hr;

    if(!ctx) {
        if(comtype_dictionary) {
            param = malloc(sizeof(XMEMCODEC_PARAMETERS_LZX));
            param->Flags = 0;
            param->WindowSize = 128 * 1024;
            param->CompressionPartitionSize = 512 * 1024;
            sscanf(comtype_dictionary, "%d %d", (int *)&param->WindowSize, (int *)&param->CompressionPartitionSize);
        }

        hr = XMemCreateDecompressionContext(
            XMEMCODEC_DEFAULT,
            param,
            0,
            &ctx);
        if(hr != S_OK) return(-1);
    }
    // XMemResetDecompressionContext is used only for the streams

    ret = outsz;
    hr = XMemDecompress(ctx, out, &ret, in, insz + MYALLOC_ZEROES);
    // + MYALLOC_ZEROES: ehmmmm long story, watch myalloc() and DMC4

    // XMemDestroyDecompressionContext(ctx);
    if(hr != S_OK) return(-1);
    return(ret);
#else
    printf("\nError: XMemDecompress is implemented only on Windows\n");
    return(-1);
#endif
}



int hex2byte(u8 *hex) {
    static const signed char hextable[256] =
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\xff\xff\xff\xff\xff\xff"
        "\xff\x0a\x0b\x0c\x0d\x0e\x0f\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\x0a\x0b\x0c\x0d\x0e\x0f\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";

    if((hextable[hex[0]] < 0) || (hextable[hex[1]] < 0)) return(-1);
    return((hextable[hex[0]] << 4) | hextable[hex[1]]);
}



// automatically does: hexadecimal, quoted printable, percentage encoding
int unhex(u8 *in, int insz, u8 *out, int outsz) {
    QUICK_IN_OUT
    int     c;

    while(in < inl) {
        c = hex2byte(in);
        if(c < 0) {
            in++;
        } else {
            if(o >= outl) return(-1);
            *o++ = c;
            in += 2;
        }
    }
    return(o - out);
}



int unbase64(u8 *in, int insz, u8 *out, int outsz) {
    int     xlen,
            a   = 0,
            b   = 0,
            c,
            step;
    u8      *limit,
            *data,
            *p;
    static const u8 base[128] = {   // supports also the Gamespy base64 and URLs
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x3e,0x00,0x3f,
        0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,
        0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x3e,0x00,0x3f,0x00,0x3f,
        0x00,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
        0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x00,0x00,0x00,0x00,0x00
    };

    if(insz < 0) insz = strlen(in);
    xlen = ((insz >> 2) * 3) + 1;    // NULL included in output for text
    if(outsz < xlen) return(-1);
    data = in;

    p = out;
    limit = data + insz;

    for(step = 0; /* data < limit */; step++) {
        do {
            if(data >= limit) {
                c = 0;
                break;
            }
            c = *data;
            data++;
            if((c == '=') || (c == '_')) {  // supports also the Gamespy base64
                c = 0;
                break;
            }
        } while(c && ((c <= ' ') || (c > 0x7f)));
        if(!c) break;

        switch(step & 3) {
            case 0: {
                a = base[c];
                break;
            }
            case 1: {
                b = base[c];
                *p++ = (a << 2)        | (b >> 4);
                break;
            }
            case 2: {
                a = base[c];
                *p++ = ((b & 15) << 4) | (a >> 2);
                break;
            }
            case 3: {
                *p++ = ((a & 3) << 6)  | base[c];
                break;
            }
        }
    }
    *p = 0;
    return(p - out);
}



int unexplode(u8 *in, int insz, u8 *out, int outsz) {
typedef struct {
    u8      *in;
    int     insz;
    int     outsz;
} explode_info_t;

unsigned explode_read(void *how, unsigned char **buf) {
    explode_info_t *explode_info;

    explode_info = (explode_info_t *)how;
    *buf = explode_info->in;
    return(explode_info->insz);
}
int explode_write(void *how, unsigned char *buf, unsigned len) {
    explode_info_t *explode_info;

    explode_info = (explode_info_t *)how;
    explode_info->outsz = len;
    return(0);
}

    explode_info_t explode_info;

    explode_info.in    = in;
    explode_info.insz  = insz;
    explode_info.outsz = -1;

    blast(explode_read, &explode_info, explode_write, &explode_info, out, outsz);
    return(explode_info.outsz);
}



int unlzma(u8 *in, int insz, u8 **ret_out, int outsz, int lzma_flags, int *full_outsz) {
void *SzAlloc(void *p, size_t size) { return(malloc(size)); }
void SzFree(void *p, void *address) { free(address); }
ISzAlloc g_Alloc = { SzAlloc, SzFree };

    CLzmaDec    lzma;
    ELzmaStatus status;
    SizeT   inlen,
            outlen;
    int     x86State,
            filter  = 0,
            propsz  = LZMA_PROPS_SIZE;
    u8      *out,
            *prop;

    if(lzma_flags & LZMA_FLAGS_EFS) {    // 2 bytes version, 2 bytes props size, props and data
        if(insz < 4) return(-1);
        propsz = in[2] | (in[3] << 8);
        in += 4;
        insz -= 4;
    }

    if(lzma_flags & LZMA_FLAGS_86_DECODER) {
        if(insz < 1) return(-1);
        filter = in[0];
        in++;
        insz--;
    }

    if(insz < propsz) return(-1);
    prop  = in;
    in   += propsz;
    inlen = insz - propsz;

    out = *ret_out;
    if(lzma_flags & LZMA_FLAGS_86_HEADER) {
        if(insz < 8) return(-1);
        outsz = in[0] | (in[1] << 8) | (in[2] << 16) | (in[3] << 24);   // 64 bit not supported yet
        if(outsz < 0) return(-1);
        myalloc(&out, outsz, full_outsz);
        *ret_out = out;
        in   += 8;
        inlen = insz - 8;
    }
    outlen = outsz;

    LzmaDec_Construct(&lzma);
    if(LzmaDec_Allocate(&lzma, prop, propsz, &g_Alloc) != SZ_OK) return(-1);
    LzmaDec_Init(&lzma);

    if(
        (LzmaDec_DecodeToBuf(&lzma, out, &outlen, in, &inlen, LZMA_FINISH_END, &status) != SZ_OK)
     || ((status != LZMA_STATUS_FINISHED_WITH_MARK) && (status != LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK))) {
        printf("\nError: the compressed LZMA input is wrong or incomplete (%d)\n", status);
        return(-1);
    }
    if(filter) {
        x86_Convert_Init(x86State);
        x86_Convert(out, outlen, 0, &x86State, 0);
    }
    LzmaDec_Free(&lzma, &g_Alloc);
    return(outlen);
}



#define LZMA2_PROPS_SIZE    1
int unlzma2(u8 *in, int insz, u8 **ret_out, int outsz, int lzma_flags, int *full_outsz) {
void *SzAlloc(void *p, size_t size) { return(malloc(size)); }
void SzFree(void *p, void *address) { free(address); }
ISzAlloc g_Alloc = { SzAlloc, SzFree };

    CLzma2Dec    lzma2;
    ELzmaStatus status;
    SizeT   inlen,
            outlen;
    int     x86State,
            filter  = 0;
    u8      *out,
            *prop;

    if(lzma_flags & LZMA_FLAGS_86_DECODER) {
        if(insz < 1) return(-1);
        filter = in[0];
        in++;
        insz--;
    }

    if(insz < LZMA2_PROPS_SIZE) return(-1);
    prop  = in;
    in   += LZMA2_PROPS_SIZE;
    inlen = insz - LZMA2_PROPS_SIZE;

    out = *ret_out;
    if(lzma_flags & LZMA_FLAGS_86_HEADER) {
        if(insz < 8) return(-1);
        outsz = in[0] | (in[1] << 8) | (in[2] << 16) | (in[3] << 24);   // 64 bit not supported yet
        if(outsz < 0) return(-1);
        myalloc(&out, outsz, full_outsz);
        *ret_out = out;
        in   += 8;
        inlen = insz - 8;
    }
    outlen = outsz;

    Lzma2Dec_Construct(&lzma2);
    if(Lzma2Dec_Allocate(&lzma2, prop[0], &g_Alloc) != SZ_OK) return(-1);
    Lzma2Dec_Init(&lzma2);

    if(
        (Lzma2Dec_DecodeToBuf(&lzma2, out, &outlen, in, &inlen, LZMA_FINISH_END, &status) != SZ_OK)
     || ((status != LZMA_STATUS_FINISHED_WITH_MARK) && (status != LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK))) {
        printf("\nError: the compressed LZMA input is wrong or incomplete (%d)\n", status);
        return(-1);
    }
    if(filter) {
        x86_Convert_Init(x86State);
        x86_Convert(out, outlen, 0, &x86State, 0);
    }
    Lzma2Dec_Free(&lzma2, &g_Alloc);
    return(outlen);
}



int ungzip(u8 *in, int insz, u8 **ret_out, int *full_outsz) {
    int     fsize = 0,
            guess_minsize;
    u8      flags,
            cm,
            *inl,
            *out;

    if(insz < 14) return(-1);
    inl = in + insz;

    guess_minsize = (insz - 12);    // blah
    if(guess_minsize) guess_minsize -= (guess_minsize / 1000);  // blah
    if(guess_minsize < 0) guess_minsize = 0;
    for(inl -= 4; inl > in; inl--) {  // lame, simple and working
        fsize = getxx(inl, 4);
        if(fsize < guess_minsize) continue;
        if(fsize > 0) break;
    }

    if((in[0] != 0x1f) && (in[1] != 0x8b)) return(-1);
    in += 2;        // id1/id2
    cm = *in++;     // cm
    flags = *in++;  // flg
    in += 4;        // mtime
    in++;           // xfl
    in++;           // os
    if(flags & 4) {
        in += 2 + (in[0] | (in[1] << 8));
        if(in >= inl) return(-1);
    }
    if(flags & 8)  in += strlen(in) + 1;
    if(flags & 16) in += strlen(in) + 1;
    if(flags & 2)  in += 2;
    if(in >= inl) return(-1);

    out = *ret_out;
    myalloc(&out, fsize, full_outsz);
    *ret_out = out;

    switch(cm) {    // based on the ZIP format, totally unrelated to the gzip format
        case 0:  fsize = uncopy(in, inl - in, out, fsize);          break;
        case 8:  fsize = unzip_deflate(in, inl - in, out, fsize);   break;
        case 1:  fsize = unshrink(in, inl - in, out, fsize);        break;
        case 6:  fsize = unexplode(in, inl - in, out, fsize);       break;
        case 9:  fsize = inflate64(in, inl - in, out, fsize);       break;
        case 12: fsize = unbzip2(in, inl - in, out, fsize);         break;
        case 14: fsize = unlzma(in, inl - in, &out, fsize, LZMA_FLAGS_EFS, &fsize); break;
        case 21: fsize = unxmemlzx(in, inl - in, out, fsize);       break;
        case 64: fsize = undarksector(in, inl - in, out, fsize, 1); break;
        case 98: fsize = unppmdi1(in, inl - in, out, fsize);        break;
        default: fsize = unzip_deflate(in, inl - in, out, fsize);   break;
    }
    return(fsize);
}



// modified from http://cvs.opensolaris.org/source/xref/onnv/onnv-gate/usr/src/uts/common/fs/zfs/lzjb.c
#define NBBY 8
#define	MATCH_BITS	6
#define	MATCH_MIN	3
#define	MATCH_MAX	((1 << MATCH_BITS) + (MATCH_MIN - 1))
#define	OFFSET_MASK	((1 << (16 - MATCH_BITS)) - 1)
#define	LEMPEL_SIZE	256

int
lzjb_decompress(u8 *s_start, u8 *d_start, size_t s_len, size_t d_len)
{
	u8 *src = s_start;
	u8 *dst = d_start;
	u8 *d_end = (u8 *)d_start + d_len;
	u8 *cpy, copymap = 0;
	int copymask = 1 << (NBBY - 1);

	while (dst < d_end) {
		if ((copymask <<= 1) == (1 << NBBY)) {
			copymask = 1;
			copymap = *src++;
		}
		if (copymap & copymask) {
			int mlen = (src[0] >> (NBBY - MATCH_BITS)) + MATCH_MIN;
			int offset = ((src[0] << NBBY) | src[1]) & OFFSET_MASK;
			src += 2;
			if ((cpy = dst - offset) < (u8 *)d_start)
				return (-1);
			while (--mlen >= 0 && dst < d_end)
				*dst++ = *cpy++;
		} else {
			*dst++ = *src++;
		}
	}
	return (dst - d_start);
}



// from ScummVM - Graphic Adventure Engine
// https://scummvm.svn.sourceforge.net/svnroot/scummvm/scummvm/tags/release-1-0-0rc1/engines/sword1/screen.cpp $
int decompressTony(u8 *src, int compSize, u8 *dest, int destsz) {
	u8 *endOfData = src + compSize;
    u8 *d = dest,
       *dl = dest + destsz;
	while (src < endOfData) {
		u8 numFlat = *src++;
		if (numFlat) {
            if((d + numFlat) > dl) return(-1);
			memset(d, *src, numFlat);
			src++;
			d += numFlat;
		}
		if (src < endOfData) {
			u8 numNoFlat = *src++;
            if((d + numNoFlat) > dl) return(-1);
			memcpy(d, src, numNoFlat);
			src += numNoFlat;
			d += numNoFlat;
		}
	}
    return(d - dest);
}
int decompressRLE7(u8 *src, int compSize, u8 *dest, int destsz) {
	u8 *compBufEnd = src + compSize;
    u8 *d = dest,
       *dl = dest + destsz;
	while (src < compBufEnd) {
		u8 code = *src++;
		if ((code > 127) || (code == 0)) {
            if(d >= dl) return(-1);
			*d++ = code;
		} else {
			code++;
            if((d + code) > dl) return(-1);
			memset(d, *src++, code);
			d += code;
		}
	}
    return(d - dest);
}
int decompressRLE0(u8 *src, int compSize, u8 *dest, int destsz) {
	u8 *srcBufEnd = src + compSize;
    u8 *d = dest,
       *dl = dest + destsz;
	while (src < srcBufEnd) {
		u8 color = *src++;
		if (color) {
            if(d >= dl) return(-1);
			*d++ = color;
		} else {
			u8 skip = *src++;
            if((d + skip) > dl) return(-1);
			memset(d, 0, skip);
			d += skip;
		}
	}
    return(d - dest);
}



// from http://rosettacode.org/wiki/Run-length_encoding#C
/*
int rle_decode(char *out, const char *in, int l)
{
  int i, tb;
  char c;
 
  for(tb=0 ; l>=0 ; l -= 2 ) {
    i = *in++;
    c = *in++;
    tb += i;
    while(i-- > 0) *out++ = c;
  }
  return tb;
}
*/

// http://www.compuphase.com/compress.htm
int unrle(unsigned char *output,unsigned char *input,int length)
{
  signed char count;
  unsigned char *o = output;

  while (length>0) {
    count=(signed char)*input++;
    if (count>0) {
      /* replicate run */
      memset(o,*input++,count);
    } else if (count<0) {
      /* literal run */
      count=(signed char)-count;
      memcpy(o,input,count);
      input+=count;
    } /* if */
    o+=count;
    length-=count;
  } /* while */
  return(o - output);
}



// must be configured
int another_rle(u8 *in, int insz, u8 *out, int outsz) {
    int     escape_chr = 0,
            i,
            o,
            c,
            n,
            lastc   = 0x80;

    if(comtype_dictionary) {
        sscanf(comtype_dictionary, "%d", &escape_chr);
    }

    for(i = o = 0; ; lastc = c) {
        if(i >= insz) break;
        c = in[i++];
        if(c == escape_chr) {
            if(i >= insz) break;
            n = in[i++];
            if(n == escape_chr) {
                if(o >= outsz) return(-1);
                out[o++] = escape_chr;
            } else {
                if((o + n) > outsz) return(-1);
                memset(out + o, lastc, n);
                o += n;
            }
        } else {
            if(o >= outsz) return(-1);
            out[o++] = c;
        }
    }
    return(o);
}



int unquicklz(u8 *in, int insz, u8 *out, int outsz) {
    static u8   *scratch = NULL;
    int     tmp;

    if(!scratch) {
        scratch = malloc(QLZ_SCRATCH_DECOMPRESS);
        if(!scratch) return(-1);
    }
    tmp = qlz_size_decompressed(in);
    if((tmp < 0) || (tmp > outsz)) return(-1);
    return(qlz_decompress(in, out, scratch));
}



// from libavcodec lcldec.c for the LossLess Codec Library
unsigned mszh_decomp(unsigned char * srcptr, int srclen, unsigned char * destptr, unsigned destsize)
{
    unsigned char *destptr_bak = destptr;
    unsigned char *destptr_end = destptr + destsize;
    unsigned char mask = 0;
    unsigned char maskbit = 0;
    unsigned ofs, cnt;

    while ((srclen > 0) && (destptr < destptr_end)) {
        if (maskbit == 0) {
            mask = *(srcptr++);
            maskbit = 8;
            srclen--;
            continue;
        }
        if ((mask & (1 << (--maskbit))) == 0) {
            if (destptr + 4 > destptr_end)
                break;
            *(int*)destptr = *(int*)srcptr;
            srclen -= 4;
            destptr += 4;
            srcptr += 4;
        } else {
            ofs = *(srcptr++);
            cnt = *(srcptr++);
            ofs += cnt * 256;
            cnt = ((cnt >> 3) & 0x1f) + 1;
            ofs &= 0x7ff;
            srclen -= 2;
            cnt *= 4;
            if (destptr + cnt > destptr_end) {
                cnt =  destptr_end - destptr;
            }
            if((destptr - ofs) < destptr_bak) return(-1);
            if((destptr + cnt) > destptr_end) return(-1);
            for (; cnt > 0; cnt--) {
                *(destptr) = *(destptr - ofs);
                destptr++;
            }
        }
    }

    return (destptr - destptr_bak);
}



int uudecode(u8 *in, int insz, u8 *out, int outsz, int xxe) {
    QUICK_IN_OUT
    int     cnt,
            c,
            m = 0;
    u8      a = 0,
            b = 0;
    static const u8 xxe_set[] = "+-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    if(!strnicmp(in, "begin", 5)) {
        while((in < inl) && (*in != '\n') && (*in != '\r')) in++;
    }

    for(cnt = -1; in < inl; in++) {
        if(*in < ' ') {
            if(!strnicmp(in + 1, "end", 3)) break;
            continue;
        }
        a = b;
        if(xxe) {
            for(b = 0; xxe_set[b]; b++) {
                if(xxe_set[b] == *in) break;
            }
            b &= 0x3f;
        } else {
            b = (*in - ' ') & 0x3f;
        }
        if(m <= 0) {
            if(!strnicmp(in, "end", 3)) break;
            cnt = -1;
        }
        if(cnt < 0) {
            m = b;
        } else {
            switch(cnt & 3) {
                case 0: c = -1;                     break;
                case 1: c = (a << 2) | (b >> 4);    break;
                case 2: c = (a << 4) | (b >> 2);    break;
                case 3: c = (a << 6) | b;           break;
                default: break;
            }
            if(c >= 0) {
                if(o >= outl) return(-1);
                *o++ = c;
                m--;
            }
        }
        cnt++;
    }
    return(o - out);
}



// partially derived from http://www.stillhq.com/svn/trunk/ascii85/decode85.c
int unascii85(u8 *in, int insz, u8 *out, int outsz) {
    QUICK_IN_OUT
    static unsigned pow85[] = { 85*85*85*85, 85*85*85, 85*85, 85, 1 };
    unsigned tuple;
    int     count,
            c;

    tuple = 0;
    count = 0;
    for(;;) {
        if(in >= inl) break;
        c = *in++;
        if(c <= ' ') continue;
        if(c == '<') {
            if(in >= inl) break;
            c = *in++;
            if(c == '~') {
                for(;;) {
                    if(in >= inl) break;
                    c = *in++;
                    if(c == 'z') {
                        if(count) break;
                        if((o + 4) > outl) return(-1);
                        *o++ = 0;
                        *o++ = 0;
                        *o++ = 0;
                        *o++ = 0;
                    } else if(c == '~') {
                        if(in >= inl) break;
                        c = *in++;
                        if(c == '>') {
                            if(count > 0) {
                                count--;
                                tuple += pow85[count];
                                if((o + count) > outl) return(-1);
                                if(count >= 1) *o++ = tuple >> 24;
                                if(count >= 2) *o++ = tuple >> 16;
                                if(count >= 3) *o++ = tuple >> 8;
                                if(count >= 4) *o++ = tuple;
                            }
                            if(in >= inl) break;
                            c = *in++;
                            break;
                        }
                    } else if(c <= ' ') {
                    } else {
                        if((c < '!') || (c > 'u')) break;
                        tuple += (c - '!') * pow85[count++];
                        if(count == 5) {
                            if((o + 4) > outl) return(-1);
                            *o++ = tuple >> 24;
                            *o++ = tuple >> 16;
                            *o++ = tuple >> 8;
                            *o++ = tuple;
                            tuple = 0;
                            count = 0;
                        }
                    }
                }
            } else {
                if((o + 2) > outl) return(-1);
                *o++ = '<';
                *o++ = c;
            }
        } else {
            if(o >= outl) return(-1);
            *o++ = c;
        }
    }
    return(o - out);
}



int unyenc(u8 *in, int insz, u8 *out, int outsz) {
    QUICK_IN_OUT
    u8      c;

    for(;;) {
        if(in >= inl) break;
        c = *in++;
        if((c == '\n') || (c == '\r')) continue;
        if(c == '=') {
            if(in >= inl) break;
            c = *in++;
            if(c == 'y') {
                while((in < inl) && (*in != '\n') && (*in != '\r')) in++;
                continue;
            }
            c -= 64;
        }
        c -= 42;
        if(o >= outl) return(-1);
        *o++ = c;
    }
    return(o - out);
}



int doomhuff(u8 *in, int insz, u8 *out, int outsz) {
    float   myfreq[256],
            t;
    int     i,
            n;
    u8      *p;

    if(comtype_dictionary) {
        p = comtype_dictionary;
        for(i = 0; i < 256; i++) {
            if(sscanf(p, "%f%n", &t, &n) != 1) break;
            myfreq[i] = t;
            for(p += n; *p; p++) {
                if(*p <= ' ') continue;
                if(*p == ',') continue;
                break;
            }
        }
        if(i < 256) {
            printf("\nError: the provided custom huffman table is incomplete (%d elements)\n", i);
            return(-1);
        }
        HuffInit(myfreq);
    } else {
        HuffInit(NULL);
    }
    HuffDecode(in, out, insz, &outsz, outsz);
    return(outsz);
}



// from Arkadi Kagan http://compressions.sourceforge.net/about.html
// converted to C by Luigi Auriemma
// I have ported only this one because the others are a mission-impossible, C++ sux
int CLZ77_Decode(unsigned char *target, long tlen, unsigned char *source, long slen) {
    static const int BITS_LEN = 4;
	long i;
	long block, len;
	long shift, border;
	unsigned char *s, *t, *p, *tl;
	unsigned char *flag;
	short *ptmp;

	t = target;
    tl = target + tlen;
	flag = source;
	block = 0;				// block - bit in single flag unsigned char
	shift = 16;				// shift offset to most significant bits
	border = 1;				// offset can`t be more then border
	for (s = source+1; (s < source+slen) && (t-target < tlen); )
	{
		if (shift > BITS_LEN)
			while (t-target >= border)
			{
				if (shift <= BITS_LEN) break;
				border = border << 1;
				shift--;
			}
		if (flag[0]&(1<<block))
		{
			ptmp = (short*)s;
			len = ((1<<shift)-1)&ptmp[0];
			p = t - (ptmp[0]>>shift) - 1;
            if((t + len) > tl) return(-1);
			for (i = 0; i < len; i++) {
				t[i] = p[i];
            }
			t += len;
			s += 2;
		} else
		{
            if(t >= tl) return(-1);
			*t++ = *s++;
			len = 1;
		}
		if (++block >= 8)
		{
			flag = s++;
			block = 0;
		}
	}
    return(t - target);
}



// http://www.ross.net/compression/download/original/old_lzrw1-a.c
int lzrw1_decompress(unsigned char *p_src_first, unsigned char *p_dst_first, unsigned src_len, int dst_len) {
    unsigned char  *p_src = p_src_first + 4,
	*p_dst = p_dst_first,
	*p_dst_end = p_dst_first + dst_len;
    unsigned char  *p_src_post = p_src_first + src_len;
    unsigned char  *p_src_max16 = p_src_first + src_len - (16 * 2);
    unsigned        control = 1;
    if (*p_src_first == 1) {	// fast_copy(p_src_first+4,p_dst_first,src_len-4);
    	memcpy(p_dst_first, p_src_first + 4, src_len - 4);
    	return (src_len - 4);
    }
    while (p_src != p_src_post) {
    	unsigned        unroll;
    	if (control == 1) {
    	    control = 0x10000 | *p_src++;
    	    control |= (*p_src++) << 8;
    	}
    	unroll = p_src <= p_src_max16 ? 16 : 1;
    	while (unroll--) {
    	    if (control & 1) {
    	    	unsigned        lenmt;
        		unsigned char  *p;
        		lenmt = *p_src++;
        		p = p_dst - (((lenmt & 0xF0) << 4) | *p_src++);
                if(p < p_dst_first) return(-1);
                if((p_dst + 3) > p_dst_end) return(-1);
        		*p_dst++ = *p++;
        		*p_dst++ = *p++;
        		*p_dst++ = *p++;
        		lenmt &= 0xF;
                if((p_dst + lenmt) > p_dst_end) return(-1);
                while (lenmt--) {
                    *p_dst++ = *p++;
                }
    	    } else {
        		if(p_dst >= p_dst_end) return(-1);
        		*p_dst++ = *p_src++;
    	    }
    	    control >>= 1;
    	}
    }
    return (p_dst - p_dst_first);
}




// modified by Luigi Auriemma
/*
 *  DHUFF.C:    Huffman Decompression Program.                            *
 *              14-August-1990    Bill Demas          Version 1.0         *
*/
int undhuff(unsigned char *in, int insz, unsigned char *out, int outsz) {
short           decomp_tree[512];
unsigned short  code[256];
unsigned char   code_length[256];

    unsigned char *inl;
    inl = in + insz;

    memset(decomp_tree, 0, sizeof(decomp_tree));
    memcpy(code, in, sizeof(code));                 in += sizeof(code);
    memcpy(code_length, in, sizeof(code_length));   in += sizeof(code_length);

   unsigned short  loop1;
   unsigned short  current_index;
   unsigned short  loop;
   unsigned short  current_node = 1;

   decomp_tree[1] = 1;

   for (loop = 0; loop < 256; loop++)
   {
      if (code_length[loop])
      {
	 current_index = 1;
	 for (loop1 = code_length[loop] - 1; loop1 > 0; loop1--)
	 {
	    current_index = (decomp_tree[current_index] << 1) +
			    ((code[loop] >> loop1) & 1);
        if(current_index > 512) return(-1);
	    if (!(decomp_tree[current_index]))
	       decomp_tree[current_index] = ++current_node;
	 }
	 decomp_tree[(decomp_tree[current_index] << 1) +
	   (code[loop] & 1)] = -loop;
      }
   }

   unsigned short  cindex = 1;
   unsigned char   curchar;
   short           bitshift;

   unsigned  charcount = 0L;

   while (charcount < outsz)
   {
      if(in >= inl) break;
      curchar = *in++;;

      for (bitshift = 7; bitshift >= 0; --bitshift)
      {
	 cindex = (cindex << 1) + ((curchar >> bitshift) & 1);

	 if (decomp_tree[cindex] <= 0)
	 {
        //if(charcount >= outsz) return(-1); // not necessary
        out[charcount] = (int) (-decomp_tree[cindex]);

	    if ((++charcount) == outsz)
               bitshift = 0;
            else
               cindex = 1;
	 }
	 else
	    cindex = decomp_tree[cindex];
      }
   }
    return(charcount);
}



// Finish submission to the Dr Dobbs contest written by Jussi Puttonen, Timo Raita and Jukka Teuhola.
int unfin(unsigned char *in, int insz, unsigned char *out, int outsz) {
#define FIN_INDEX(p1,p2) (((unsigned)(unsigned char)p1<<7)^(unsigned char)p2)
static char pcTable[32768U];
   int ci,co;            // characters (in and out)
   char p1=0, p2=0;      // previous 2 characters
   int ctr=8;            // number of characters processed for this mask
   unsigned char mask=0; // mask to mark successful predictions

int i = 0;
int o = 0;

   memset (pcTable, 32, 32768U); // space (ASCII 32) is the most used char

   for(;;) {
      if(i >= insz) break;
      ci = in[i++];
      // get mask (for 8 characters)
      mask = (unsigned char)(char)ci;

      // for each bit in the mask
      for (ctr=0; ctr<8; ctr++){
         if (mask & (1<<ctr)){
            // predicted character
            co = pcTable[FIN_INDEX(p1,p2)];
         } else {
            // not predicted character
            if(i >= insz) break;
            co = in[i++];
	    pcTable[FIN_INDEX(p1,p2)] = (char)co;
         }
         if(o >= outsz) return(-1);
         out[o++] = co;
         p1 = p2; p2 = co;
      }
   }
   return(o);
}



// Copyright (c) 2002 Chilkat Software, Inc.  All Rights Reserved
int CK_RLE_decompress(unsigned char *buf,
    int len, 
    unsigned char *out,
    int uncompressLen)
    {
    unsigned char header;
    unsigned char *outPtr = out;
    unsigned char i;
    int outSize = 0;

    while (len)
	{
	header = *buf;
	buf++;
	len--;

	if (!(header & 128))
	    {
	    // There are header+1 different bytes.
	    for (i=0; i<=header; i++)
		{
		if (outSize >= uncompressLen) return -1;
		*outPtr = *buf;
		outPtr++;
		outSize++;
		buf++;
		len--;
		}
	    }
	else
	    {
	    unsigned n = (header & 127) + 2;
	    for (i=0; i<n; i++)
		{
		if (outSize >= uncompressLen) return -1;
		*outPtr = *buf;
		outPtr++;
		outSize++;
		}
	    buf++;
	    len--;
	    }
	}

    uncompressLen = outSize;
    //return 0;
    return(uncompressLen);
    }



// this function has been created by me from scratch (based on calcc) and is NOT optimized
// note: if outsz is not of the exact size then the returned size will be padded
int multi_base_decoder(int base, int alt, u8 *in, int insz, u8 *out, int outsz, u8 *mytable) {
static const u8 big_table[256] =
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
    "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f"
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f"
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f"
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f"
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f"
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f"
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"
    "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f"
    "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f"
    "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf"
    "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf"
    "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf"
    "\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf"
    "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef"
    "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff";
static const u8 hex_table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static const u8 b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const u8 g64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]";   // gamespy
static const u8 b32_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
static const u8 z32_table[] = "ybndrfg8ejkmcpqxot1uwisza345h769";   // z-base-32
static const u8 c32_table[] = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";   // Crockford's base32
static const u8 n32_table[] = "0123456789BCDFGHJKLMNPQRSTVWXYZ.";   // Nintendo
    u64     num;
    int     i,
            block    = 0,
            blockcpy = 0;
    u8      *p;
    u8      *table = NULL;

    if(mytable) {
        table = mytable;
    } else {
        if((base > 0) && (base <= 16)) {
            table = (u8 *)hex_table;
        } else if(base == 32) {
            switch(alt) {
                case 0: table = (u8 *)b32_table;    break;
                case 1: table = (u8 *)z32_table;    break;
                case 2: table = (u8 *)hex_table;    break;
                case 3: table = (u8 *)c32_table;    break;
                case 4: table = (u8 *)n32_table;    break;
                default: break;
            }
        } else if(base == 64) {
            switch(alt) {
                case 0: table = (u8 *)b64_table;    break;
                case 1: table = (u8 *)g64_table;    break;
                default: break;
            }
        } else if(base <= 62) {
            table = (u8 *)hex_table;
        } else {
            table = (u8 *)big_table;
        }
        if(!table) return(-1);
    }

    num = 1;    // I'm sure that exists a better and simpler way but I'm stupid, sorry
    for(block = 0; num; block++) {
        num *= base;
        switch(num - 1) {
            case 0xffLL:
            case 0xffffLL:
            case 0xffffffLL:
            case 0xffffffffLL:
            case 0xffffffffffLL:
            case 0xffffffffffffLL:
            case 0xffffffffffffffLL:
            case 0xffffffffffffffffLL: {
                for(blockcpy = 0, --num; num; num >>= 8, blockcpy++);
                //num = 0;  // num is already 0
                break;
            }
            default: break;
        }
    }
    if(!(block & 1)) block--;   // if pair

    QUICK_IN_OUT

    num = 0;
    for(i = 0;; i++) {
        num *= (u64)base;
        if(in < inl) {
            p = memchr(table, *in, base);
            if(p) {
                num += (p - table);
                in++;
            } else {
                in = inl; // finish
            }
        }
        if(i >= block) {
            i = blockcpy;
            while(i--) {
                if(o >= outl) /* do NOT use return(-1) here */ break;
                *o++ = num >> (u64)(i * 8);
            }
            num = 0;
            i = -1;
            if(in >= inl) break;
        }
    }
    //*o++ = 0;
    return(o - out);
}



int unlzhlib(unsigned char *in, int insz, unsigned char *out, int outsz) {
    QUICK_IN_OUT

    void *mymalloc (unsigned n) {return malloc (n);}
    void myfree (void *p) {free (p);}
    int myread (void *p, int n) {
        if((in + n) > inl) n = inl - in;
        memcpy(p, in, n);
        in += n;
        return(n);
    }
    int mywrite (void *p, int n) {
        if((o + n) > outl) return(-1);
        memcpy(o, p, n);
        o += n;
        return(n);
    }
    lzh_melt(myread, mywrite, mymalloc, myfree, outsz);
    return(o - out);
}



/***********************************************************
*
*    rle3.c
*
*      ランレングス符号化のテスト
*      ラン長部分をマーク符号で識別する
*
***********************************************************/
//int rl3_decode(unsigned char *out, unsigned char *in, int size) {
int rl3_decode(unsigned char *in, int insz, unsigned char *out, int outsz) {
#define MINLEN   4
#define LIMIT1   240
#define LIMIT2   (256 * (256 - LIMIT1) + LIMIT1 - 1)
unsigned char mch = 'Z';
	int rpos = 0, wpos = 0;
	while (rpos < insz) {
		int c = in[rpos++];
		int i, le;
		if (c == mch) {
			/* ラン長を入力 */
			le = in[rpos++];
			if (le >= LIMIT1) {
				le = ((le - LIMIT1) << 8) + in[rpos++] + LIMIT1;
			}
			le++;
			if (le >= MINLEN)  c = in[rpos++];
            if((wpos + le) > outsz) return(-1);
			for (i = 0; i < le; i++)  out[wpos++] = c;
		} else {
            if(wpos >= outsz) return(-1);
			out[wpos++] = c;
		}
	}
	return wpos;
}



typedef struct {
    unsigned char   *o;
    unsigned char   *ol;
} sr3c_write_ctx;
static int sr3c_write(const unsigned char *bytes, size_t n, int flush, sr3c_write_ctx *wc) {
    if((wc->o + n) > wc->ol) n = wc->ol - wc->o;
    if(n <= 0) return(-1);
    memcpy(wc->o, bytes, n);
    wc->o += n;
    return(0);
}
int unsr3c(unsigned char *in, int insz, unsigned char *out, int outsz) {
    sr3c_context_t *ctx;
    sr3c_write_ctx  wc;

    wc.o  = out;
    wc.ol = out + outsz;
    ctx = sr3c_alloc((sr3c_output_f_t)sr3c_write, &wc);
    if(sr3c_uncompress(in, insz, ctx)) {
        sr3c_free(ctx);
        return(-1);
    }
    sr3c_free(ctx);
    return(wc.o - out);
}



// blah, practically the library contains both the smart and simple mode
// while the pre-compiled demo on the website uses only the smart mode
// and so it's needed to select the smart-only or smart+simple mode
int SFUnpackSeg(unsigned char *in, int insz, unsigned char *out, int outsz, int smart_only) {
    int     i   = 0,
            o   = 0,
            t,
            a,
            c,
            ident = 0;

    if(insz < 2) return(-1);
    t = in[i] | (in[i + 1] << 8);
    i += 2;
    if(!smart_only) {
        if(t <= 0xff) {
            ident = t;
            t = 0;
        }
    }
    for(;;) {
        if(t) {
            if(insz <= t) break;
            c = in[insz - 2] | (in[insz - 1] << 8);
            insz -= 2;
            c -= (i + 1);
            if((o + c) > outsz) return(-1);
            memcpy(out + o, in + i, c);
            i += c;
            o += c;
        } else {
            if(i >= insz) break;
            a = in[i++];
            if(a != ident) {
                if((o + 1) > outsz) return(-1);
                out[o++] = a;
                continue;
            }
        }
        a = in[i++];
        c = in[i++];
        if(!c) {
            c = in[i] | (in[i + 1] << 8);
            i += 2;
        }
        c++;
        if((o + c) > outsz) return(-1);
        memset(out + o, a, c);
        o += c;
    }
    if(t) {
        c = insz - i;
        if((o + c) > outsz) return(-1);
        memcpy(out + o, in + i, c);
        i += c;
        o += c;
    }
    return(o);
}
int SFUnpack(unsigned char *in, int insz, unsigned char *out, int outsz, int smart_only) {
    int     i   = 0,
            o   = 0,
            r,
            chunksz;

    for(;;) {
        if((i + 2) > insz) break;
        chunksz = in[i] | (in[i + 1] << 8);
        i += 2;
        if((i + chunksz) > insz) break;
        r = SFUnpackSeg(in + i, chunksz, out + o, outsz - o, smart_only);
        if(r < 0) break;
        i += chunksz;
        o += r;
    }
    return(o);
}



// based on the informations of Guy Ratajczak, it's just a lz77
int undarkstone(unsigned char *in, int insz, unsigned char *out, int outsz) {
    QUICK_IN_OUT
    int     i,
            j,
            flags,
            info,
            num;
    u8      *p;

    for(;;) {
        if(in >= inl) break;
        flags = *in++;
        for(i = 0; i < 8; i++) {
            if(o >= outl) break;    // needed
            if(flags & 1) {
                if(in >= inl) break;
                if(o >= outl) return(-1);
                *o++ = *in++;
            } else {
                if((in + 2) > inl) break;
                info = in[0] | (in[1] << 8);
                in += 2;
                num = 3 + (info >> 10);
                p = o - (info & 0x3ff);
                if(p < out) return(-1);
                if((o + num) > outl) return(-1);
                for(j = 0; j < num; j++) {
                    *o++ = *p++;
                }
            }
            flags >>= 1;
        }
    }
    return(o - out);
}



int sfl_block_chunked(unsigned char *in, int insz, unsigned char *out, int outsz) {
    int     chunk_zsize,
            chunk_size,
            i,
            o;

    i = 0;
    o = 0;
    while(o < outsz) {
        if((i + 2) > insz) break;
        chunk_zsize = in[i] | (in[i + 1] << 8);
        if(!chunk_zsize) break;
        i += 2;
        if((i + chunk_zsize) > insz) break;
        chunk_size = expand_block(in + i, out + o, chunk_zsize, outsz - o);
        i += chunk_zsize;
        o += chunk_size;
    }
    return(o);
}



// code from tpu: http://forum.xentax.com/viewtopic.php?p=30387#p30387
/* PRS get bit form lsb to msb, FPK get it form msb to lsb */
int prs_8ing_get_bits(int n, char *sbuf, int *sptr, int *blen)
{
    static int fbuf = 0;
   int retv;

   retv = 0;
   while(n){
      retv <<= 1;
      if((*blen)==0){
         fbuf = sbuf[*sptr];
         //if(*sptr<256)
            //{ printf("[%02x] ", fbuf&0xff); fflush(0); }
         (*sptr)++;
         (*blen) = 8;
      }

      if(fbuf&0x80)
         retv |= 1;

      fbuf <<= 1;
      (*blen) --;
      n --;
   }

   return retv;
}
int prs_8ing_uncomp(char *dbuf, int dlen, char *sbuf, int slen)
{
   int sptr;
   int dptr;
   int i, flag, len, pos;

   int blen = 0;

   sptr = 0;
   dptr = 0;
   while(sptr<slen){
      flag = prs_8ing_get_bits(1, sbuf, &sptr, &blen);
      if(flag==1){
         //if(sptr<256)
            //{ printf("%02x ", (u8)sbuf[sptr]); fflush(0); }
         if(dptr<dlen)
            dbuf[dptr++] = sbuf[sptr++];
      }else{
         flag = prs_8ing_get_bits(1, sbuf, &sptr, &blen);
         if(flag==0){
            len = prs_8ing_get_bits(2, sbuf, &sptr, &blen)+2;
            pos = sbuf[sptr++]|0xffffff00;
         }else{
            pos = (sbuf[sptr++]<<8)|0xffff0000;
            pos |= sbuf[sptr++]&0xff;
            len = pos&0x07;
            pos >>= 3;
            if(len==0){
               len = (sbuf[sptr++]&0xff)+1;
            }else{
               len += 2;
            }
         }
         //if(sptr<256)
            //{ printf("<%08x(%08x): %08x %d> \n", dptr, dlen, pos, len); fflush(0); }
         pos += dptr;
         for(i=0; i<len; i++){
            if(dptr<dlen)
               dbuf[dptr++] = dbuf[pos++];
         }
      }
   }

   return dptr;
}



// the following code has been provided by Pokan http://www.geocities.jp/pokan_chan/
//////////////////////////////////////////////////////////////
//  Decode
#define falcom_ReverseByteBits(b) ((((b)&1)<<3)|(((b)&2)<<1)|(((b)&4)>>1)|(((b)&8)>>3))
long falcom_read_bit_flags(unsigned char *buf, long *buf_off, unsigned long *bit_flags, int *bit_flags_len)
{
	(*bit_flags) |= *((unsigned short*)(buf + *buf_off)) << *bit_flags_len;
	(*bit_flags_len) += 16;
	(*buf_off) += 2;

	return 2;
}
long falcom_DecodeData(unsigned char *dst_buf, long dst_buf_size, unsigned char *src_buf, long src_buf_size)
{
	int		i, n;
	int     block_num;
	int     block_off;
	int     block_size;
	int	    bit_flags_len;
	int		copy_size;
	int		copy_off;
	long    dst_off;
	long    src_off;
	unsigned char   byte_val;
	unsigned long   bit_flags;

	n = 0;
	block_num = 0xFF;
	copy_off = 0;
	src_off = 0;
	dst_off = 0;
	while (block_num)
	{
		if (dst_off > dst_buf_size || src_off > src_buf_size) break;

		block_size = *((unsigned short*)(src_buf + src_off));
		src_off += 2; block_size -= 4;
		if (src_buf[src_off++] != 0x00) break;
		//
		bit_flags = src_buf[src_off++];
		bit_flags_len = 8;
		copy_size = 1;
		for (block_off = 0; block_off < block_size; )
		{
			if (dst_off > dst_buf_size || src_off > src_buf_size) break;
			if (bit_flags_len == 0)
			{
				block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
			}

			//	1xyyyy
			if (bit_flags & 1)
			{
				copy_size = 0;
				if (bit_flags_len == 1)
				{
					block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
				}

				if ((bit_flags >> 1) & 1)
				{
					//	11xxxxx
					if (bit_flags_len < 7)
					{
						block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
					}

					copy_off = 0;
					byte_val = src_buf[src_off++]; block_off++;
					bit_flags >>= 2; bit_flags_len -= 2;
					if (bit_flags & 1) copy_off = 0x1000;

					bit_flags >>= 1; bit_flags_len--;
					copy_off += 0x100 * falcom_ReverseByteBits(bit_flags & 0x0F);

					// 1100000xyyyy
					if ((bit_flags & 0x0F) == 0 && copy_off == 0)
					{
						if (block_off >= block_size) break;
						bit_flags >>= 4; bit_flags_len -= 4;
						if (bit_flags_len < 5)
						{
							block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
						}
						byte_val = src_buf[src_off++]; block_off++;
						copy_size = 0x0E;

						i = bit_flags & 1;
						bit_flags >>= 1; bit_flags_len--;
						copy_size += falcom_ReverseByteBits(bit_flags & 15) << (i?8:0);
						if (i)
						{
							copy_size += byte_val;
							byte_val = src_buf[src_off++]; block_off++;
						}

						bit_flags >>= 4; bit_flags_len -= 4;
						for (i = 0; i < copy_size; i++)
						{
							if (dst_off > dst_buf_size) break;
							dst_buf[dst_off++] = byte_val;
						}
						continue;
					}
					bit_flags >>= 4; bit_flags_len -= 4;

					//	<2
					if (bit_flags_len < 2)
					{
						block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
					}

					copy_size = 2;
					for (i = 0; i < 4; i++)
					{
						if (bit_flags & 1) break;
						if (src_off > src_buf_size) break;

						bit_flags >>= 1; bit_flags_len--;
						if (bit_flags_len == 0)
						{
							block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
						}
						copy_size++;
					}
					if (i == 4)
					{
						if ((bit_flags & 1) == 0)
						{
							copy_size = src_buf[src_off++] + 0x0E; block_off++;
						}
						else
						{
							if (bit_flags_len < 4)
							{
								block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
							}
							copy_size = falcom_ReverseByteBits(bit_flags & 0xF) - 2;
							bit_flags >>= 3; bit_flags_len -= 3;
						}
					}

					copy_off += byte_val;
				}
				else
				{
					//	1xxxxx
					byte_val = src_buf[src_off++]; block_off++;
					while (1)
					{
						bit_flags >>= 1; bit_flags_len--;
						if (src_off > src_buf_size) break;
						if (bit_flags_len == 0)
						{
							block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
						}
						copy_size++;
						if (copy_size > 5)
						{
							if ((bit_flags & 1) == 0)
							{
								copy_size = src_buf[src_off++] + 0x0E; block_off++;
							}
							else
							{
								if (bit_flags_len < 4)
								{
									block_off += falcom_read_bit_flags(src_buf, &src_off, &bit_flags, &bit_flags_len);
								}
								copy_size = falcom_ReverseByteBits(bit_flags & 0xF) - 2;
								bit_flags >>= 3; bit_flags_len -= 3;
							}
							break;
						}

						//	end check
						if ((bit_flags & 1) == 1) break;
					}

					copy_off = byte_val;
				}

				copy_off = dst_off - copy_off;
				for (i = 0; i < copy_size; i++)
				{
					if (dst_off > dst_buf_size) break;
					dst_buf[dst_off++] = dst_buf[copy_off++];
				}
			}
			else
			{
				dst_buf[dst_off++] = src_buf[src_off++];
				block_off++;
			}
			bit_flags >>= 1; bit_flags_len--;
		}
		i = src_buf[src_off++];

		if (n > 1 && i > block_num) i = 0;
		block_num = i;
		if (n == 0 && block_num == 0) block_num = 0xFF;
		n++;
	}

	return dst_off;
}



// from cpk_uncompress.c of hcs: http://hcs64.com/files/utf_tab04.zip
// modified by Luigi Auriemma
// Decompress compressed segments in CRI CPK filesystems
static inline unsigned short CPK_get_next_bits(unsigned char *infile, int * const offset_p, unsigned char * const bit_pool_p, int * const bits_left_p, const int bit_count)
{
    unsigned short out_bits = 0;
    int num_bits_produced = 0;
    while (num_bits_produced < bit_count)
    {
        if (0 == *bits_left_p)
        {
            *bit_pool_p = infile[*offset_p];
            *bits_left_p = 8;
            --*offset_p;
        }

        int bits_this_round;
        if (*bits_left_p > (bit_count - num_bits_produced))
            bits_this_round = bit_count - num_bits_produced;
        else
            bits_this_round = *bits_left_p;

        out_bits <<= bits_this_round;
        out_bits |=
            (*bit_pool_p >> (*bits_left_p - bits_this_round)) &
            ((1 << bits_this_round) - 1);

        *bits_left_p -= bits_this_round;
        num_bits_produced += bits_this_round;
    }

    return out_bits;
}

#define CPK_GET_NEXT_BITS(bit_count) CPK_get_next_bits(infile, &input_offset, &bit_pool, &bits_left, bit_count)

int CPK_uncompress(unsigned char *infile, int input_size, unsigned char *output_buffer, int uncompressed_size) {
    if(uncompressed_size < 0x100) return(-1);
    uncompressed_size -= 0x100; // blah, terrible algorithm or terrible implementation

    const int input_end = input_size - 0x100 - 1;
    int input_offset = input_end;
    const int output_end = 0x100 + uncompressed_size - 1;
    unsigned char bit_pool = 0;
    int bits_left = 0;
    int bytes_output = 0;
    int     i;

    if(input_size < 0x100) return(-1);
    memcpy(output_buffer, infile + input_size - 0x100, 0x100);

    while ( bytes_output < uncompressed_size )
    {
        if(input_offset < 0) break;
        if (CPK_GET_NEXT_BITS(1))
        {
            int backreference_offset =
                output_end-bytes_output+CPK_GET_NEXT_BITS(13)+3;
            int backreference_length = 3;

            // decode variable length coding for length
            enum { vle_levels = 4 };
            int vle_lens[vle_levels] = { 2, 3, 5, 8 };
            int vle_level;
            for (vle_level = 0; vle_level < vle_levels; vle_level++)
            {
                int this_level = CPK_GET_NEXT_BITS(vle_lens[vle_level]);
                backreference_length += this_level;
                if (this_level != ((1 << vle_lens[vle_level])-1)) break;
            }
            if (vle_level == vle_levels)
            {
                int this_level;
                do
                {
                    this_level = CPK_GET_NEXT_BITS(8);
                    backreference_length += this_level;
                } while (this_level == 255);
            }

            //printf("0x%08lx backreference to 0x%lx, length 0x%lx\n", output_end-bytes_output, backreference_offset, backreference_length);
            for (i=0;i<backreference_length;i++)
            {
                output_buffer[output_end-bytes_output] = output_buffer[backreference_offset--];
                bytes_output++;
            }
        }
        else
        {
            // verbatim byte
            output_buffer[output_end-bytes_output] = CPK_GET_NEXT_BITS(8);
            //printf("0x%08lx verbatim byte\n", output_end-bytes_output);
            bytes_output++;
        }
    }

    return 0x100 + bytes_output;
}



/* ----------
 * pg_lzcompress.c -
 *
 *		This is an implementation of LZ compression for PostgreSQL.
 *		It uses a simple history table and generates 2-3 byte tags
 *		capable of backward copy information for 3-273 bytes with
 *		a max offset of 4095.
 ...(cut)...
 * Copyright (c) 1999-2009, PostgreSQL Global Development Group
 *
 * $PostgreSQL: pgsql/src/backend/utils/adt/pg_lzcompress.c,v 1.34 2009/06/11 14:49:03 momjian Exp $
 * ----------
 */
int
pglz_decompress(unsigned char *in, int insz, unsigned char *out, int outsz)
{
	const unsigned char *sp;
	const unsigned char *srcend;
	unsigned char *dp;
	unsigned char *destend;

	//sp = ((const unsigned char *) source) + sizeof(PGLZ_Header);
	//srcend = ((const unsigned char *) source) + VARSIZE(source);
	//dp = (unsigned char *) dest;
	//destend = dp + source->rawsize;
    sp      = in;
    srcend  = in + insz;
    dp      = out;
    destend = out + outsz;

	while (sp < srcend && dp < destend)
	{
		/*
		 * Read one control byte and process the next 8 items (or as many as
		 * remain in the compressed input).
		 */
		unsigned char ctrl = *sp++;
		int			ctrlc;

		for (ctrlc = 0; ctrlc < 8 && sp < srcend; ctrlc++)
		{
			if (ctrl & 1)
			{
				/*
				 * Otherwise it contains the match length minus 3 and the
				 * upper 4 bits of the offset. The next following byte
				 * contains the lower 8 bits of the offset. If the length is
				 * coded as 18, another extension tag byte tells how much
				 * longer the match really was (0-255).
				 */
				int		len;
				int		off;

				len = (sp[0] & 0x0f) + 3;
				off = ((sp[0] & 0xf0) << 4) | sp[1];
				sp += 2;
				if (len == 18)
					len += *sp++;

				/*
				 * Check for output buffer overrun, to ensure we don't clobber
				 * memory in case of corrupt input.  Note: we must advance dp
				 * here to ensure the error is detected below the loop.  We
				 * don't simply put the elog inside the loop since that will
				 * probably interfere with optimization.
				 */
				if (dp + len > destend)
				{
					dp += len;
					break;
				}

				/*
				 * Now we copy the bytes specified by the tag from OUTPUT to
				 * OUTPUT. It is dangerous and platform dependent to use
				 * memcpy() here, because the copied areas could overlap
				 * extremely!
				 */
				while (len--)
				{
					*dp = dp[-off];
					dp++;
				}
			}
			else
			{
				/*
				 * An unset control bit means LITERAL BYTE. So we just copy
				 * one from INPUT to OUTPUT.
				 */
				if (dp >= destend)		/* check for buffer overrun */
					break;		/* do not clobber memory */

				*dp++ = *sp++;
			}

			/*
			 * Advance the control bit
			 */
			ctrl >>= 1;
		}
	}

	/*
	 * Check we decompressed the right amount.
	 */
	//if (dp != destend || sp != srcend)
		//return(-1); //elog(ERROR, "compressed data is corrupt");

	/*
	 * That's it.
	 */
    return(dp - out);
}



/*
Simple Compression using an LZ buffer
Part 3 Revision 1.d:
An introduction to compression on the Amiga by Adisak Pochanayon
*/
// modified by Luigi Auriemma
#define HISTORY_SIZE     4096
#define MASK_history     (HISTORY_SIZE-1)
#define MASK_upper       (0xF0)
#define MASK_lower       (0x0F)
#define SHIFT_UPPER      16
#define LSR_upper        4
#define MAX_COMP_LEN     17
unsigned char LZ_history[HISTORY_SIZE];

#define UnPackSLZ_writechar(outchar) \
{ \
  if(o >= outl) return(-1); \
  *o++ = outchar; \
  LZ_history[lzhist_offset]=outchar; lzhist_offset=(lzhist_offset+1)&MASK_history; \
}

int UnPackSLZ(unsigned char *in, int insz, unsigned char *out, int outsz) {
    QUICK_IN_OUT

  short myTAG, mycount, myoffset;
  int loop1;
  short lzhist_offset=0;

  for(;;)  // loop forever (until goto occurs to break out of loop)
    {
      if(in >= inl) break;
      myTAG=*in++;
      for(loop1=0;(loop1!=8);loop1++)
        {
          if(myTAG&0x80)
            {
              if(in >= inl) break;
              if((mycount=*in++)==0)  // Check EXIT
                { goto skip2; } // goto's are gross but it's efficient :(
              else
                {
                  if(in >= inl) break;
                  myoffset=HISTORY_SIZE-(((MASK_upper&mycount)*SHIFT_UPPER)+(*in++));
                  mycount&=MASK_lower;
                  mycount+=2;
                  while(mycount!=0)
                    {
                      UnPackSLZ_writechar(LZ_history[(lzhist_offset+myoffset)&MASK_history]);
                      mycount--;
                    }
                }
            }
          else
            { if(in >= inl) break; UnPackSLZ_writechar(*in++); }
          myTAG+=myTAG;
        }
    }
skip2:
  return(o - out);
}



int slz_triace_blah(int x, int n, int a, unsigned char **o, unsigned char *outl) {
    unsigned char   *t = *o;
    if(x < n) {
        n = (((n - x) - 1) >> 1) + 1;
        x += n * 2;
        if((t + (n * 2)) > outl) return(-1);
        while(n--) {
            *t++ = a;
            *t++ = a >> 8;
        }
        *o = t;
    }
    return(x);
}
int slz_triace(unsigned char *in, int insz, unsigned char *out, int outsz, int type) {
    QUICK_IN_OUT
    int     flag, n, x, a;

    for(flag = 0; o < outl; flag >>= 1) {
        if(!(flag & 0xff00)) {
            if(in >= inl) break;
            flag = 0xff00 | *in++;
        }
        if(flag & 1) {
            if(in >= inl) break;
            if(o >= outl) return(-1);
            *o++ = *in++;
        } else {
            if((in + 2) > inl) break;
            n = *in++;
            n |= (*in++ << 8);
            x = ((n >> 12) & 0x0f) + 3;
            n &= 0x0fff;
            if((x < 0x12) || (type != 2)) {
                if((o - n) < out) return(-1);
                if((o + x) > outl) return(-1);
                while(x--) {
                    *o = *(o - n);
                    o++;
                }
            } else {
                if(n < 0x100) {
                    if(in >= inl) break;
                    a = *in++;
                    n += 0x13;
                } else {
                    a = n & 0xff;
                    n = (((n >> 8) & 0xf) + 3);
                }
                a |= (a << 8);
                if((o - out) & 1) {
                    if(o >= outl) return(-1);
                    *o++ = a;
                    if(n & 1) {
                        n = ((n - 2) >> 1) + 1;
                        if((o + (n * 2)) > outl) return(-1);
                        while(n--) {
                            *o++ = a;
                            *o++ = a >> 8;
                        }
                    } else if((n - 1) > 1) {
                        x = slz_triace_blah(1, n - 1, a, &o, outl);
                        if(x < 0) return(-1);
                        if(x < n) {
                            if(o >= outl) return(-1);
                            *o++ = a;
                        }
                    } else if(n > 1) {
                        if(o >= outl) return(-1);
                        *o++ = a;
                    }
                } else {
                    x = slz_triace_blah(0, n - 1, a, &o, outl);
                    if(x < 0) return(-1);
                    if(x < n) {
                        if(o >= outl) return(-1);
                        *o++ = a;
                    }
                }
            }
        }
    }
    return(o - out);
}



int unlzhl(unsigned char *in, int insz, unsigned char *out, int outsz) {
    LZHL_DHANDLE hnd;
    hnd = LZHLCreateDecompressor();
    if(!LZHLDecompress(hnd, out, &outsz, in, &insz)) outsz = -1;
    LZHLDestroyDecompressor(hnd);
    return(outsz);
}



int unlzrw3(unsigned char *in, int insz, unsigned char *out, int outsz) {
    static u8   wrk_mem[4096];
    lzrw3a_decompress(wrk_mem, in, insz, out, &outsz);
    return(outsz);
}



/*
_DIFFERENTIAL COMPRESSION ALGORITHMS_
by James H. Sylvester
*/
int diffcomp(unsigned char *in, int insz, unsigned char *out, int outsz) {
    unsigned char   *infile   = in,
                    *infilel  = in + insz,
                    *outfile  = out,
                    *outfilel = out + outsz;

  const int blockfactor = 1;              /* adjust as desired */
  const int blocksize = blockfactor * 8;
  char  buffer [257] [8];             /* enter blocksize for second index */

  int   i, j;
  //FILE  *sf, *tf;        /* sourcefile & targetfile respectively */
  int   bestblock = -1;  /* best matching block in buffer */
  int   changeindex;

/* Initialize buffer with exactly same information as in PACK.C program. */
  for (i = 0; i < 256; i++)
    for (j = 0; j < blocksize; j++)
      buffer [i] [j] = i;
/* Reconstruct original data from encoded data in sourcefile. */
  while (1)  /* while true ==> stay in loop until internal exit */
  {
    if (bestblock == -1)     /* input data yet to be loaded */
    {
      bestblock = lame_getc(sf);
      if (bestblock == EOF)  /* original and encoded files had 0 bytes */
      {
        goto quit;
      }
      changeindex = lame_getc(sf);
    }
    else
    {
      bestblock = lame_getc(sf);
      if (bestblock == EOF)    /* input data ended with previous full block */
      {
        for (j = 0; j < blocksize; j++)  /* output full block */
          lame_putc(buffer [256] [j], tf);
        goto quit;
      }
      changeindex = lame_getc(sf);
      if (changeindex == EOF)  /* input data ended with unfull block */
      {
        for (j = 0; j < bestblock; j++)  /* reinterpret bestblock as  */
                                         /* last blocksize and output */
                                         /* this last, partial block  */
          lame_putc(buffer [256] [j], tf);
        goto quit;
      }
      for (j = 0; j < blocksize; j++)  /* output full block */
        lame_putc(buffer [256] [j], tf);
    }
    for (i = 0; i < blockfactor; i++)
    {
      if (i > 0)
        changeindex = lame_getc(sf);
      for (j = i*8; j < i*8+8; j++)
      {
        if (changeindex % 2 == 1)
          buffer [bestblock] [j] = lame_getc(sf);  /* directly load changes */
                                              /* into buffer bestblock */
        changeindex /= 2;
        buffer [256] [j] = buffer [bestblock] [j];  /* copy block info */
      }
    }
  }
quit:
  return(outfile - out);
}



int unlzs(unsigned char *in, int insz, unsigned char *out, int outsz, int big) {
    int     roff = 0,
            rlen = 0,
            ctype;

    ctype = RDP_MPPC_COMPRESSED | RDP_MPPC_FLUSH;
    if(big) ctype |= RDP_MPPC_BIG;
    if(mppc_expand(in, insz, ctype, &roff, &rlen) < 0) return(-1);
    if(rlen < 0) return(-1);
    if(rlen > outsz) rlen = outsz;
    memcpy(out, g_mppc_dict.hist + roff, rlen);
    return(rlen);
}



int moh_lzss(unsigned char *in, int insz, unsigned char *out, int outsz) {
    QUICK_IN_OUT
    unsigned        n,
                    x;
    unsigned char   b,
                    a;

    a = 0;
    b = 0;
    while(o < outl) {
        b <<= 1;
        if(!b) {
            if(in >= inl) break;
            a = *in++;
            b = 1;
        }
        if(a & b) {
            if(in >= inl) break;
            if(o >= outl) return(-1);
            *o++ = *in++;
        } else {
            if((in + 2) > inl) break;
            x = in[0] | (in[1] << 8);
            in += 2;
            n = ((x >> 12) & 0xf) + 3;
            if((o + n) > outl) return(-1);
            x = 0x1000 - (x & 0xfff);   // because it's already negative
            if((o - x) < out) return(-1);
            while(n--) {
                *o = *(o - x);
                o++;
            }
        }
    }
    return(o - out);
}



int moh_rle(unsigned char *in, int insz, unsigned char *out, int outsz) {
    QUICK_IN_OUT
    unsigned char   b,
                    s;

    while(o < outl) {
        if(in >= inl) break;
        s = *in++;
        if(s < 0x80) {
            s++;
            if((in + s) > inl) break;
            if((o + s) > outl) return(-1);
            while(s--) {
                *o++ = *in++;
            }
        } else {
            if(in >= inl) break;
            b = *in++;
            s = 0x101 - s;
            if((o + s) > outl) return(-1);
            while(s--) {
                *o++ = b;
            }
        }
    }
    return(o - out);
}



// by thakis (http://www.amnoid.de/gc/)
// I have not verified if this algorithm is already implemented/known with other names but I guess yes... oh well
int decodeYaz0(u8* src, int srcSize, u8* dst, int uncompressedSize)
{
typedef struct {
  int srcPos, dstPos;
} Ret;
  Ret r = { 0, 0 };
  int i;
  //int srcPlace = 0, dstPlace = 0; //current read/write positions
  
  u32 validBitCount = 0; //number of valid bits left in "code" byte
  u8 currCodeByte = 0;
  while(r.dstPos < uncompressedSize)
  {
    //read new "code" byte if the current one is used up
    if(validBitCount == 0)
    {
      currCodeByte = src[r.srcPos];
      ++r.srcPos;
      validBitCount = 8;
    }
    
    if((currCodeByte & 0x80) != 0)
    {
      //straight copy
      dst[r.dstPos] = src[r.srcPos];
      r.dstPos++;
      r.srcPos++;
      //if(r.srcPos >= srcSize)
      //  return r;
    }
    else
    {
      //RLE part
      u8 byte1 = src[r.srcPos];
      u8 byte2 = src[r.srcPos + 1];
      r.srcPos += 2;
      //if(r.srcPos >= srcSize)
      //  return r;
      
      u32 dist = ((byte1 & 0xF) << 8) | byte2;
      u32 copySource = r.dstPos - (dist + 1);

      u32 numBytes = byte1 >> 4;
      if(numBytes == 0)
      {
        numBytes = src[r.srcPos] + 0x12;
        r.srcPos++;
        //if(r.srcPos >= srcSize)
        //  return r;
      }
      else
        numBytes += 2;

      //copy run
      for(i = 0; i < numBytes; ++i)
      {
        dst[r.dstPos] = dst[copySource];
        copySource++;
        r.dstPos++;
      }
    }
    
    //use next bit from "code" byte
    currCodeByte <<= 1;
    validBitCount-=1;    
  }

  return r.dstPos;
}



int byte2hex(u8 *input, int len, u8 *output, int outlen) {
    static const u8 hex[] = "0123456789ABCDEF";
    int     i;
    u8      *o,
            *l;

    if(len < 0) len = strlen(input);
    o = output;
    l = output + outlen;
    for(i = 0; i < len; i++) {
        if((o + 2 + 1) > l) break;
        *o++ = hex[input[i] >> 4];
        *o++ = hex[input[i] & 15];
    }
    *o = 0;
    return(o - output);
}


