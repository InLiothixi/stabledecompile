#include <inttypes.h>

#define XXTEA_ENCRYPT   1
#define XXTEA_DECRYPT   0

typedef struct {
    uint32_t k[4];
}
xxtea_context;

#ifdef __cplusplus
extern "C" {
#endif
void xxtea_setup(xxtea_context *ctx, unsigned char key[16]);
void xxtea_crypt(xxtea_context *ctx, int mode, unsigned char *data, int len);
#ifdef __cplusplus
}
#endif
