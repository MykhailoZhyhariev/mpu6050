/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#ifndef MPU_6050
#define MPU_6050

// Structure that containing all measured variables
typedef struct {
    // "whoAmI" register value
    unsigned char who;

    // High and low value of temperature registers
    unsigned char temp_h, temp_l;
    // Temperature in degrees Celsius
    float temp;

    // High and low value of accelerometer registers of X, Y and Z axises
    unsigned char accel_xh, accel_xl;
    unsigned char accel_yh, accel_yl;
    unsigned char accel_zh, accel_zl;
    // Combined values of registers for X, Y, Z axises
    unsigned int accel_x, accel_y, accel_z;

    // High and low value of gyroscope registers of X, Y and Z axises
    unsigned char gyro_xh, gyro_xl;
    unsigned char gyro_yh, gyro_yl;
    unsigned char gyro_zh, gyro_zl;
    // Combined values of registers for X, Y, Z axises
    unsigned int gyro_x, gyro_y, gyro_z;
} mpu6050;

// Initialise and set teh settings MPU6050
void MPU6050_Init(void);

// Returning a value of "whoAmI" register MPU6050
void MPU6050_whoAmI(mpu6050 *mpu6050);

// Getting a value of temperature registers MPU6050
void MPU6050_getTemp(mpu6050 *mpu6050);

// Getting a value of accelerometer registers MPU6050
void MPU6050_getAccel(mpu6050 *mpu6050);

// Getting a value of gyroscope registers MPU6050
void MPU6050_getGyro(mpu6050 *mpu6050);

// computing the temperature in degrees Celsius
void MPU6050_countTemp(mpu6050 *mpu6050);

#endif
