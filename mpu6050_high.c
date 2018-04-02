/* Name: mpu6050_high.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include "mpu6050.h"

/**
 * Computing the temperature in degrees Celsius
 * @return      temperature in degrees Celsius
 */
float MPU6050_countTemp(void) {
    // Getting the values of temp_high and temp_l registers
    int temp_reg = MPU6050_getTemp();

    // Computing the temperature in degrees Celsius
    return temp_reg / 340 + 36.53;
}
