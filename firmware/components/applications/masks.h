#ifndef MASKS_H_
#define MASKS_H_

#define MASK_NRF     (0x01)
#define MASK_ESP_NOW (0x02)
#define MASK_BLE     (0x03)

#define MASKED(dip, mask) ((dip &mask) == mask)

#endif /* MASKS_H_ */
