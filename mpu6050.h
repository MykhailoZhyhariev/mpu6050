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

    // Combined (high and low) value of temperature register
    unsigned int temp_reg;
    // Temperature in degrees Celsius
    float temp;

    // Combined (high and low) values of accelerometer registers for X, Y, Z axises
    unsigned int accel_x, accel_y, accel_z;

    // Combined (high and low) values of registers for X, Y, Z axises
    unsigned int gyro_x, gyro_y, gyro_z;
} mpu6050;

void _MPU6050_moveToReg(unsigned char reg);

// Getting the value from a register
int _MPU6050_getRegValue(unsigned char reg, unsigned char len);

// Writing value to the register
void _MPU6050_writeToReg(unsigned char reg, unsigned char value);

// Initialise and set the settings MPU6050
void MPU6050_Init(void);

// Returning a value of "whoAmI" register MPU6050
void MPU6050_whoAmI(mpu6050 *mpu6050);

// Getting a value of temperature registers MPU6050
void MPU6050_getTemp(mpu6050 *mpu6050);

// Getting a value of accelerometer registers MPU6050
void MPU6050_getAccel(mpu6050 *mpu6050);

// Getting a value of gyroscope registers MPU6050
void MPU6050_getGyro(mpu6050 *mpu6050);

// Computing the temperature in degrees Celsius
void MPU6050_countTemp(mpu6050 *mpu6050);

#endif
