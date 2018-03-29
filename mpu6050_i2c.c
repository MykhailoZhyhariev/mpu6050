/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include "mpu6050.h"
#include "mpu6050_constants.h"
#include "twi/i2c.h"

/**
 * Move pointer to register
 * @param reg register address [hex]
 */
void _MPU6050_moveToReg(unsigned char reg) {
    i2c_start_cond();
    i2c_send_byte(MPU6050_W);
    i2c_send_byte(reg);
    i2c_stop_cond();
}

/**
 * Getting the value from a register
 * @param  reg register address [hex]
 * @param  len number of bytes of the register
 * @return     register value
 */
int _MPU6050_getRegValue(unsigned char reg, unsigned char len) {
    _MPU6050_moveToReg(reg);

    i2c_start_cond();
    i2c_send_byte(MPU6050_R);

    int value = 0;
    for (unsigned char i = 0; i < len - 1; i++) {
        value += i2c_get_byte(0) << 8;
    }
    value += i2c_get_byte(1);

    i2c_stop_cond();

    return value;
}

/**
 * Writing value to the register
 * @param reg   register address [hex]
 * @param value value to write
 */
void _MPU6050_writeToReg(unsigned char reg, unsigned char value) {
    i2c_start_cond();
    i2c_send_byte(MPU6050_W);
    i2c_send_byte(reg);
    i2c_send_byte(value);
    i2c_stop_cond();
}
