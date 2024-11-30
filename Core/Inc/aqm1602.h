/*
 * aqm1602.h
 *
 *  Created on: Nov 30, 2024
 *      Author: sata
 */

#ifndef INC_AQM1602_H_
#define INC_AQM1602_H_

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

#define I2C_ADDR_AQM1602 (0x3e << 1)


extern void aqm1602_print(const char *str);
extern void aqm1602_init(uint8_t c);
// extern void aqm1602_move(uint8_t pos);
extern void aqm1602_pos(uint8_t raw, uint8_t col);
extern void aqm1602_clear(void);


#endif /* INC_AQM1602_H_ */
