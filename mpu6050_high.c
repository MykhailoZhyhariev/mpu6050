/* Name: mpu6050_high.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <math.h>
#include <stdlib.h>
#include "mpu6050.h"

/**
 * Counts the deviation angle of the MPU6050 module from the accelerometer data
 * @param  a - accelerometer data on the axes x, y, z
 * @param  b - accelerometer data on the axes x, y, z
 * @param  c - accelerometer data on the axes x, y, z
 * @return   calculated angle
 */
float _MPU6050_countAngle(float a, float b, float c) {
    return 57.295 * atan(-a / sqrt(pow(b, 2) + pow(c,2)));
}

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

/**
 * Counts the deviation angles of the MPU6050 module from the accelerometer data on the axes x, y, z
 * @return an array of the calculated angles
 */
float* MPU_getAccelAngle(void) {
    int* accel = MPU6050_getAccel();
    float *accel_angle = (float *)malloc(sizeof(float) * 3);
    accel_angle[0] = _MPU6050_countAngle(accel[0], accel[1], accel[2]);
    accel_angle[1] = _MPU6050_countAngle(accel[1], accel[0], accel[2]);
    accel_angle[2] = _MPU6050_countAngle(accel[2], accel[0], accel[1]);

    return accel_angle;
}
