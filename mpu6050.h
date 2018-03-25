/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

// signed char TEMPER_h;
// signed char TEMPER_l;
// unsigned char t;
//
// unsigned char ACCEL_xh;
// unsigned char ACCEL_xl;
// unsigned char ACCEL_yh;
// unsigned char ACCEL_yl;
// unsigned char ACCEL_zh;
// unsigned char ACCEL_zl;
// long int ACCEL_X;
// long int ACCEL_Y;
// long int ACCEL_Z;
//
// signed char ACCEL_XANGLE = 0;
// signed char ACCEL_YANGLE = 0;
// signed char ACCEL_ZANGLE = 0;
//
// unsigned char GYRO_xh;
// unsigned char GYRO_xl;
// unsigned char GYRO_yh;
// unsigned char GYRO_yl;
// unsigned char GYRO_zh;
// unsigned char GYRO_zl;
// long int GYRO_X;
// long int GYRO_Y;
// long int GYRO_Z;
//
// signed int GYRO_ANGLE_Z = 0;
//
// unsigned char who;

#ifndef MPU_6050
#define MPU_6050

typedef struct {
    unsigned char who;
    signed char temp_h, temp_l;
    signed long int temp;
} mpu6050;

void MPU6050_Init(void);

void MPU6050_whoAmI(mpu6050 *mpu6050);

void MPU6050_getTemp(mpu6050 *mpu6050);

void MPU6050_countTemp(mpu6050 *mpu6050);

#endif
