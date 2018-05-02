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
float _MPU6050_countAccelAngle(float a, float b, float c) {
    return 57.295 * atan(-a / sqrt(pow(b, 2) + pow(c,2)));
}

/**
 * [_MPU6050_countGyroAngle description]
 * @param  previous_data - angles that has benn counted on previous iteration
 * @param  data          - gyroscope data
 * @param  delta         - the time that passed between the measurements
 * @return               calculated angle
 */
float _MPU6050_countGyroAngle(float previous_data, int data, int delta) {
    return previous_data + data * delta * 0.001;
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
float* MPU6050_getAccelAngles(void) {
    int* accel = MPU6050_getAccel();
    float *accel_angle = (float *)malloc(sizeof(float) * 3);
    accel_angle[0] = _MPU6050_countAccelAngle(accel[0], accel[1], accel[2]);
    accel_angle[1] = _MPU6050_countAccelAngle(accel[1], accel[0], accel[2]);
    accel_angle[2] = _MPU6050_countAccelAngle(accel[2], accel[0], accel[1]);

    return accel_angle;
}

/**
 * Counts the deviation angles of the MPU6050 module from the accelerometer data on the axes x, y, z
 * @param  previous_data - angles that has benn counted on previous iteration
 * @param  delta         - the time that passed between the measurements
 * @return               an array of the calculated angles
 */
float* MPU6050_getGyroAngles(float* previous_data, int delta) {
    int* gyro = MPU6050_getGyro();
    float *gyro_angle = (float *)malloc(sizeof(float) * 3);
    for (unsigned char i = 0; i < 3; i++) {
        gyro_angle[i] = _MPU6050_countGyroAngle(previous_data[i], gyro[i], delta);
    }
    return gyro_angle;
}

/**
 * Carries out the filtration of calculated angles
 * @param  previous_data - a previous values array of data
 * @param  filter_func   - a function that filters a data
 * @return               an array of filtered data
 */
float* MPU6050_getFilteredAngles(
    float *previous_data,
    float* (* filter_func)(float* accel, float* gyro, float* previous_data, unsigned char len)
) {
    // Obtain the angles calculated from the accelerometer data
    float* accel = MPU6050_getAccelAngles();

    // Obtain the angles calculated from the gyroscope data
    float* gyro = MPU6050_getGyroAngles(previous_data, 200);

    // Use callback function and return an array of filtered data
    return filter_func(accel, gyro, previous_data, 3);
}
