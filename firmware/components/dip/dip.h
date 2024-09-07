#ifndef DIF_H_
#define DIF_H_

#include <stdint.h>

void    dip_init(void);
uint8_t dip_read(void);
bool    dip_has_changed(void);

#endif /* DIF_H_ */
