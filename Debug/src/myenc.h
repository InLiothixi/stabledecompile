#include "encryption/leverage_ssc.h"
u8 *mystrchrs(u8 *str, u8 *chrs);
int readbase(u8 *data, int size, int *readn);
int unhex(u8 *in, int insz, u8 *out, int outsz);



// xor
typedef struct {
    u8      *key;
    int     keysz;
    int     keypos;
} xor_context;

void xor_setkey(xor_context *ctx, u8 *key, int keysz) {
    ctx->key    = malloc(keysz);    // "ctx->key = key" was good too
    memcpy(ctx->key, key, keysz);
    ctx->keysz  = keysz;
    ctx->keypos = 0;
}

void xor_crypt(xor_context *ctx, u8 *data, int datalen) {
    int     i;

    for(i = 0; i < datalen; i++) {
        if(ctx->keypos >= ctx->keysz) ctx->keypos = 0;
        data[i] ^= ctx->key[ctx->keypos];
        ctx->keypos++;
    }
}



// rot
typedef struct {
    u8      *key;
    int     keysz;
    int     keypos;
} rot_context;

void rot_setkey(rot_context *ctx, u8 *key, int keysz) {
    ctx->key    = malloc(keysz);    // "ctx->key = key" was good too
    memcpy(ctx->key, key, keysz);
    ctx->keysz  = keysz;
    ctx->keypos = 0;
}

void rot_crypt(rot_context *ctx, u8 *data, int datalen) {
    int     i;

    for(i = 0; i < datalen; i++) {
        if(ctx->keypos >= ctx->keysz) ctx->keypos = 0;
        data[i] += ctx->key[ctx->keypos];
        ctx->keypos++;
    }
}



// charset
typedef struct {
    u8      key[256];
} charset_context;

void charset_setkey(charset_context *ctx, u8 *key, int keysz) {
    memset(ctx->key, 0, 256);
    if(keysz <= 0) return;
    if(keysz > 256) keysz = 256;
    memcpy(ctx->key, key, keysz);
}

void charset_crypt(charset_context *ctx, u8 *data, int datalen) {
    int     i;

    for(i = 0; i < datalen; i++) {
        data[i] = ctx->key[data[i]];
    }
}



// charset2
typedef struct {
    u8      key[256];
} charset2_context;

void charset2_setkey(charset2_context *ctx, u8 *key, int keysz) {
    memset(ctx->key, 0, 256);
    if(keysz <= 0) return;
    if(keysz > 256) keysz = 256;
    memcpy(ctx->key, key, keysz);
}

void charset2_crypt(charset2_context *ctx, u8 *data, int datalen) {
    int     i,
            j,
            c;

    for(i = 0; i < datalen; i++) {
        c = data[i];
        for(j = 0; j < 256; j++) {
            if(ctx->key[j] == c) {
                c = j;
                break;
            }
        }
        data[i] = c;
    }
}



// ssc
typedef struct {
    u8      *key;
    int     keysz;
} ssc_context;

void ssc_setkey(ssc_context *ctx, u8 *key, int keysz) {
    ctx->key    = malloc(keysz);    // "ctx->key = key" was good too
    memcpy(ctx->key, key, keysz);
    ctx->keysz  = keysz;
}



// wincrypt
#ifdef WIN32
#include <wincrypt.h>

typedef struct {
    DWORD   num;
    char    *str;
} wincrypt_types;
wincrypt_types wincrypt_mspn1[] = { // blah
    { (DWORD)MS_DEF_DH_SCHANNEL_PROV,  "MS_DEF_DH_SCHANNEL_PROV" },
    { (DWORD)MS_DEF_DSS_DH_PROV,       "MS_DEF_DSS_DH_PROV" },
    { (DWORD)MS_DEF_DSS_PROV,          "MS_DEF_DSS_PROV" },
    { (DWORD)MS_DEF_PROV,              "MS_DEF_PROV" },
    { (DWORD)MS_DEF_RSA_SCHANNEL_PROV, "MS_DEF_RSA_SCHANNEL_PROV" },
    { (DWORD)MS_DEF_RSA_SIG_PROV,      "MS_DEF_RSA_SIG_PROV" },
    { (DWORD)MS_ENH_DSS_DH_PROV,       "MS_ENH_DSS_DH_PROV" },
#ifdef MS_ENH_RSA_AES_PROV
    { (DWORD)MS_ENH_RSA_AES_PROV,      "MS_ENH_RSA_AES_PROV" },
#endif
    { (DWORD)MS_ENHANCED_PROV,         "MS_ENHANCED_PROV" },
    { (DWORD)MS_SCARD_PROV,            "MS_SCARD_PROV" },
    { (DWORD)MS_STRONG_PROV,           "MS_STRONG_PROV" },
    { (DWORD)NULL,                     NULL }
};
wincrypt_types wincrypt_mspn2[] = { // blah
    { (DWORD)MS_DEF_DH_SCHANNEL_PROV,  MS_DEF_DH_SCHANNEL_PROV },
    { (DWORD)MS_DEF_DSS_DH_PROV,       MS_DEF_DSS_DH_PROV },
    { (DWORD)MS_DEF_DSS_PROV,          MS_DEF_DSS_PROV },
    { (DWORD)MS_DEF_PROV,              MS_DEF_PROV },
    { (DWORD)MS_DEF_RSA_SCHANNEL_PROV, MS_DEF_RSA_SCHANNEL_PROV },
    { (DWORD)MS_DEF_RSA_SIG_PROV,      MS_DEF_RSA_SIG_PROV },
    { (DWORD)MS_ENH_DSS_DH_PROV,       MS_ENH_DSS_DH_PROV },
#ifdef MS_ENH_RSA_AES_PROV
    { (DWORD)MS_ENH_RSA_AES_PROV,      MS_ENH_RSA_AES_PROV },
#endif
    { (DWORD)MS_ENHANCED_PROV,         MS_ENHANCED_PROV },
    { (DWORD)MS_SCARD_PROV,            MS_SCARD_PROV },
    { (DWORD)MS_STRONG_PROV,           MS_STRONG_PROV },
    { (DWORD)NULL,                     NULL }
};
wincrypt_types wincrypt_prov[] = {
    { 1,  "PROV_RSA_FULL" },
    { 2,  "PROV_RSA_SIG" },
    { 3,  "PROV_DSS" },
    { 4,  "PROV_FORTEZZA" },
    { 5,  "PROV_MS_EXCHANGE" },
    { 5,  "PROV_MS_MAIL" },
    { 6,  "PROV_SSL" },
    { 7,  "PROV_STT_MER" },
    { 8,  "PROV_STT_ACQ" },
    { 9,  "PROV_STT_BRND" },
    { 10, "PROV_STT_ROOT" },
    { 11, "PROV_STT_ISS" },
    { 12, "PROV_RSA_SCHANNEL" },
    { 13, "PROV_DSS_DH" },
    { 14, "PROV_EC_ECDSA_SIG" },
    { 15, "PROV_EC_ECNRA_SIG" },
    { 16, "PROV_EC_ECDSA_FULL" },
    { 17, "PROV_EC_ECNRA_FULL" },
    { 18, "PROV_DH_SCHANNEL" },
    { 20, "PROV_SPYRUS_LYNKS" },
    { 21, "PROV_RNG" },
    { 22, "PROV_INTEL_SEC" },
    { 24, "PROV_RSA_AES" },
    { 0,  NULL }
};
wincrypt_types wincrypt_calg[] = {
    { 0x00006603, "CALG_3DES" },
    { 0x00006609, "CALG_3DES_112" },
    { 0x00006611, "CALG_AES" },
    { 0x00006611, "CALG_AES" },
    { 0x0000660e, "CALG_AES_128" },
    { 0x0000660e, "CALG_AES_128" },
    { 0x0000660f, "CALG_AES_192" },
    { 0x0000660f, "CALG_AES_192" },
    { 0x00006610, "CALG_AES_256" },
    { 0x00006610, "CALG_AES_256" },
    { 0x0000aa03, "CALG_AGREEDKEY_ANY" },
    { 0x0000660c, "CALG_CYLINK_MEK" },
    { 0x00006601, "CALG_DES" },
    { 0x00006604, "CALG_DESX" },
    { 0x0000aa02, "CALG_DH_EPHEM" },
    { 0x0000aa01, "CALG_DH_SF" },
    { 0x00002200, "CALG_DSS_SIGN" },
    { 0x0000aa05, "CALG_ECDH" },
    { 0x0000aa05, "CALG_ECDH" },
    { 0x00002203, "CALG_ECDSA" },
    { 0x00002203, "CALG_ECDSA" },
    { 0x0000a001, "CALG_ECMQV" },
    { 0x0000800b, "CALG_HASH_REPLACE_OWF" },
    { 0x0000800b, "CALG_HASH_REPLACE_OWF" },
    { 0x0000a003, "CALG_HUGHES_MD5" },
    { 0x00008009, "CALG_HMAC" },
    { 0x0000aa04, "CALG_KEA_KEYX" },
    { 0x00008005, "CALG_MAC" },
    { 0x00008001, "CALG_MD2" },
    { 0x00008002, "CALG_MD4" },
    { 0x00008003, "CALG_MD5" },
    { 0x00002000, "CALG_NO_SIGN" },
    { 0xffffffff, "CALG_OID_INFO_CNG_ONLY" },
    { 0xfffffffe, "CALG_OID_INFO_PARAMETERS" },
    { 0x00004c04, "CALG_PCT1_MASTER" },
    { 0x00006602, "CALG_RC2" },
    { 0x00006801, "CALG_RC4" },
    { 0x0000660d, "CALG_RC5" },
    { 0x0000a400, "CALG_RSA_KEYX" },
    { 0x00002400, "CALG_RSA_SIGN" },
    { 0x00004c07, "CALG_SCHANNEL_ENC_KEY" },
    { 0x00004c03, "CALG_SCHANNEL_MAC_KEY" },
    { 0x00004c02, "CALG_SCHANNEL_MASTER_HASH" },
    { 0x00006802, "CALG_SEAL" },
    { 0x00008004, "CALG_SHA" },
    { 0x00008004, "CALG_SHA1" },
    { 0x0000800c, "CALG_SHA_256" },
    { 0x0000800c, "CALG_SHA_256" },
    { 0x0000800d, "CALG_SHA_384" },
    { 0x0000800d, "CALG_SHA_384" },
    { 0x0000800e, "CALG_SHA_512" },
    { 0x0000800e, "CALG_SHA_512" },
    { 0x0000660a, "CALG_SKIPJACK" },
    { 0x00004c05, "CALG_SSL2_MASTER" },
    { 0x00004c01, "CALG_SSL3_MASTER" },
    { 0x00008008, "CALG_SSL3_SHAMD5" },
    { 0x0000660b, "CALG_TEK" },
    { 0x00004c06, "CALG_TLS1_MASTER" },
    { 0x0000800a, "CALG_TLS1PRF" },
    { 0,          NULL }
};
typedef struct {
    HCRYPTPROV  hProv;
    HCRYPTHASH  hHash;
    HCRYPTKEY   hKey;
    u8          *mspn;
    DWORD       prov;
    DWORD       hash;
    DWORD       algo;
} wincrypt_context;

u8 *wincrypt_parameters(u8 *parameters, wincrypt_types *types, DWORD *ret) {
    DWORD   tmp;
    int     i,
            len,
            quote = 0;
    u8      *p,
            *pquote = NULL,
            *pret;

    if(!parameters) return(NULL);
    if(!parameters[0]) return(NULL);
    p = parameters;
    if((*p == '\"') || (*p == '\'')) {
        quote = 1;
        for(++p; *p; p++) {
            if((*p == '\"') || (*p == '\'')) {
                pquote = p;
                break;
            }
        }
    }
    p = mystrchrs(p, " \t,;");
    if(!p) p = parameters + strlen(parameters);
    pret = p;

    if(quote) {
        parameters++;
        p = pquote;
    }
    len = p - parameters;
    if(len <= 0) return(NULL);

    tmp = readbase(parameters, 10, NULL);
    for(i = 0; types[i].str; i++) {
        if(
            (!strnicmp(types[i].str, parameters, len) && !types[i].str[len])
         || (tmp == types[i].num)) {
            *ret = (DWORD)types[i].num;
            break;
        }
    }
    return(pret + 1);
}

int wincrypt_setkey(wincrypt_context *ctx, u8 *key, int keysz, u8 *parameters) {
    static const int    flags[] = {
                0,
                CRYPT_NEWKEYSET,
                CRYPT_MACHINE_KEYSET,
                CRYPT_MACHINE_KEYSET | CRYPT_NEWKEYSET,
                -1
            };
    int     i;
    u8      *p;

    ctx->mspn = MS_DEF_PROV;
    ctx->prov = PROV_RSA_FULL;
    ctx->hash = CALG_MD5;
    ctx->algo = CALG_RC4;

    if(parameters) {
        p = parameters;
        p = wincrypt_parameters(p, wincrypt_calg, &ctx->hash);
        p = wincrypt_parameters(p, wincrypt_calg, &ctx->algo);
        p = wincrypt_parameters(p, wincrypt_prov, &ctx->prov);
            wincrypt_parameters(p, wincrypt_mspn1, (DWORD *)&ctx->mspn);    // don't increment p
        p = wincrypt_parameters(p, wincrypt_mspn2, (DWORD *)&ctx->mspn);
    }

    for(i = 0; flags[i] >= 0; i++) {
        if(CryptAcquireContext(
            &ctx->hProv,
            NULL,
            ctx->mspn,
            ctx->prov,
            flags[i])) break;
    }
    if(flags[i] < 0) return(-1);

    if(!CryptCreateHash(
        ctx->hProv,
        ctx->hash,
        0,  //ctx->hashkey,
        0,
        &ctx->hHash)) return(-1);

    if(!CryptHashData(
        ctx->hHash,
        key,
        keysz,
        0)) return(-1);
    return(0);
}

int wincrypt_decrypt(wincrypt_context *ctx, u8 *data, int datalen) {
    DWORD   len;

    if(datalen <= 0) return(0);
    len = datalen;

    if(!CryptDeriveKey(
        ctx->hProv,
        ctx->algo,
        ctx->hHash,
        0,
        &ctx->hKey)) return(-1);

    if(!CryptDecrypt(
        ctx->hKey,
        0,
        TRUE,
        0,
        data,
        &len)) return(-1);
    return(len);
}

int wincrypt_encrypt(wincrypt_context *ctx, u8 *data, int datalen) {
    DWORD   len;

    if(datalen <= 0) return(0);
    len = datalen;

    if(!CryptDeriveKey(
        ctx->hProv,
        ctx->algo,
        ctx->hHash,
        0,
        &ctx->hKey)) return(-1);

    if(!CryptEncrypt(
        ctx->hKey,
        0,
        TRUE,
        0,
        data,
        &len,
        datalen)) return(-1);
    return(len);
}
#else
typedef struct {
} wincrypt_context;
int wincrypt_setkey(wincrypt_context *ctx, u8 *key, int keysz, u8 *parameters) {
    return(-1);
}
int wincrypt_decrypt(wincrypt_context *ctx, u8 *data, int datalen) {
    return(-1);
}
int wincrypt_encrypt(wincrypt_context *ctx, u8 *data, int datalen) {
    return(-1);
}
#endif



// CryptUnprotect (mainly for thoroughness, not for real usage)
#ifdef WIN32
#include <windows.h>
typedef struct {
    u8      *entropy;
    int     entropy_size;
} cunprot_context;
int cunprot_setkey(cunprot_context *ctx, u8 *key, int keysz) {
    if(keysz > 0) {
        ctx->entropy      = key;
        ctx->entropy_size = keysz;
    } else {
        ctx->entropy      = NULL;
        ctx->entropy_size = 0;
    }
    return(0);
}
int cunprot_decrypt(cunprot_context *ctx, u8 *data, int datalen) {
    DATA_BLOB   DataIn,
                DataEntropy,
                DataOut;
    int         ret;

    DataIn.pbData = data;
    DataIn.cbData = datalen;
    if(ctx->entropy) {
        DataEntropy.pbData = ctx->entropy;
        DataEntropy.cbData = ctx->entropy_size;
    }

    if(!CryptUnprotectData(
      &DataIn,
      NULL,
      ctx->entropy ? &DataEntropy : NULL,
      NULL,
      NULL,
      0,
      &DataOut)) {
        DataIn.pbData = malloc(datalen + 1);
        DataIn.cbData = unhex(data, datalen, DataIn.pbData, datalen);
        ret = CryptUnprotectData(
          &DataIn,
          NULL,
          ctx->entropy ? &DataEntropy : NULL,
          NULL,
          NULL,
          0,
          &DataOut);
        free(DataIn.pbData);    // free it in any case
        if(!ret) return(-1);
    }

    if(datalen > DataOut.cbData) datalen = DataOut.cbData;
    memcpy(data, DataOut.pbData, datalen);
    if(DataOut.pbData) LocalFree(DataOut.pbData);
    return(datalen);
}
int cunprot_encrypt(cunprot_context *ctx, u8 *data, int datalen) {
    DATA_BLOB   DataIn,
                DataEntropy,
                DataOut;
    int         ret;

    DataIn.pbData = data;
    DataIn.cbData = datalen;
    if(ctx->entropy) {
        DataEntropy.pbData = ctx->entropy;
        DataEntropy.cbData = ctx->entropy_size;
    }

    if(!CryptProtectData(
      &DataIn,
      L"description",
      ctx->entropy ? &DataEntropy : NULL,
      NULL,
      NULL,
      0,
      &DataOut)) {
        DataIn.pbData = malloc(datalen + 1);
        DataIn.cbData = unhex(data, datalen, DataIn.pbData, datalen);
        ret = CryptProtectData(
          &DataIn,
          L"description",
          ctx->entropy ? &DataEntropy : NULL,
          NULL,
          NULL,
          0,
          &DataOut);
        free(DataIn.pbData);
        if(!ret) return(-1);
    }

    if(datalen > DataOut.cbData) datalen = DataOut.cbData;
    memcpy(data, DataOut.pbData, datalen);
    if(DataOut.pbData) LocalFree(DataOut.pbData);
    return(datalen);
}
#else
typedef struct {
} cunprot_context;
int cunprot_setkey(cunprot_context *ctx, u8 *key, int keysz) {
    return(-1);
}
int cunprot_decrypt(cunprot_context *ctx, u8 *data, int datalen) {
    return(-1);
}
int cunprot_encrypt(cunprot_context *ctx, u8 *data, int datalen) {
    return(-1);
}
#endif


