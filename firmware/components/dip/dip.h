#ifndef DIF_H_
#define DIF_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void dip_init(void);
uint8_t dip_read(void);

#ifdef __cplusplus
}
#endif

#endif /* DIF_H_ */
