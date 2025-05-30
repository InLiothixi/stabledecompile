#include <inttypes.h>

#define TEA_ENCRYPT     1
#define TEA_DECRYPT     0

typedef struct {
    uint32_t k[4];
}
tea_context;

#ifdef __cplusplus
extern "C" {
#endif
void tea_setup(tea_context *ctx, unsigned char key[16]);
void tea_crypt(tea_context *ctx, int mode, unsigned char input[8], unsigned char output[8]);
#ifdef __cplusplus
}
#endif
