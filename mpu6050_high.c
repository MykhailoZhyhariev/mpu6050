/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include "mpu6050.h"

/**
 * computing the temperature in degrees Celsius
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_countTemp(mpu6050 *mpu6050) {
    // getting the values of temp_high and temp_l registers
    MPU6050_getTemp(mpu6050);

    // computing the temperature in degrees Celsius
    mpu6050->temp = (mpu6050->temp_reg / 340) + 36.53;
}
