#pragma once
#include "main.h"
#include <stdint.h>
#include <stdbool.h>


//The default address of the AS5600 is 0x36(7 bit), but the HAL requires 8 bit address,
//so a left shift is performed, where the LSB is the operation indicator
//0 = write, 1 = read
//Additionally, the correct format when working with bit manipulation always use unsigned
#define AS5600_I2C_ADDR (0x36U << 1)

//AS5600 Registers (8 bit)
#define AS5600_ZMCO 			0x00 	//not sure if used
#define AS5600_CONF_H			0x07	//MSB config
#define AS5600_CONF_L			0x08	//LSB config
#define AS5600_STATUS			0x0B	//b5=MD,b4=ML,b3=MH
#define AS5600_RAW_ANGLE_H		0x0C	//MSB Raw angle measurement (4 bit)
#define AS5600_RAW_ANGLE_L		0x0D	//LSB Raw angle measurement (8 bit)
#define AS5600_ANGLE_H			0x0E	//MSB Scaled angle (4 bit)
#define AS5600_ANGLE_L			0x0F	//LSB Scaled angle (8 bit)

//AS5600 Status bits
#define AS5600_STATUS_MAG_DET  	(1U << 5)
#define AS5600_STATUS_MAG_LP	(1U << 4)
#define AS5600_STATUS_MAG_HP 	(1U << 3)

//AS5600 Read Raw angle Prototype
//requires pointer to I2C_HandleTypeDef, register address and pointer to var to store at,
//returns a bool to notify if op was successful
bool as5600_read_u8(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *val);

//AS5600 Write Raw angle Prototype
bool as5600_write_u8(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t val);

//AS5600 Read Raw Angle Prototype
bool as5600_read_raw_angle(I2C_HandleTypeDef *hi2c, uint16_t *ticks4600);

//AS5600 Read Angle Prototype
bool as5600_read_angle(I2C_HandleTypeDef *hi2c, uint16_t *ticks4600);

//AS5600 Read Angle Prototype
bool as5600_read_status(I2C_HandleTypeDef *hi2c, uint8_t *status);

//Convertion functions to work with degrees and radians
//static and inline used to keep function local(avoid linker error) and to
//allow compiler to replace function call with function body
static inline float as5600_ticks_to_deg(uint16_t ticks4096){
	return(ticks4096 *(360.0f / 4096.0f));
}

static inline float as5600_ticks_to_rad(uint16_t ticks4096){
	return(ticks4096 *(6.283158307179586f / 4096.0f));
}
