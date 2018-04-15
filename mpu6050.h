/* Name: mpu6050.h
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#ifndef MPU_6050
#define MPU_6050

/**
 *  I2C FUNCTIONS
 */

/**
 * Move pointer to register
 * @param reg register address [hex]
 */
void _MPU6050_moveToReg(unsigned char reg);

/**
 * Getting the value from a register
 * @param  reg - register address [hex]
 * @param  len - number of bytes of the register
 * @return     register value
 */
int _MPU6050_getRegValue(unsigned char reg, unsigned char len);

/**
 * Writing value to the register
 * @param reg   - register address [hex]
 * @param value - value to write
 */
void _MPU6050_writeToReg(unsigned char reg, unsigned char value);

/**
 * LOW LEVEL FUNCTIONS
 */

/**
 * Getting an array of registers values
 * @param  reg - register address [hex]
 * @param  len - number of bytes of the register
 * @return     the array of values
 */
int* _MPU6050_getArrValues(unsigned char reg, unsigned char length);

/**
 * Initialise and set the settings MPU6050
 */
void MPU6050_Init(void);

/**
 * Returning a value of "whoAmI" register MPU6050
 * @return  "whoAmI register value"
 */
unsigned char MPU6050_whoAmI(void);

/**
 * Getting a value of temperature registers MPU6050
 * @return  temperature register value
 */
int MPU6050_getTemp(void);

/**
 * Getting a value of accelerometer registers MPU6050
 * @return  the array of accelerometer registers values
 */
int* MPU6050_getAccel(void);

/**
 * Getting a value of gyroscope registers MPU6050
 * @return  the array of gyroscope registers values
 */
int* MPU6050_getGyro(void);

/**
 * HIGH LEVEL FUNCTIONS
 */

/**
 * Computing the temperature in degrees Celsius
 * @return      temperature in degrees Celsius
 */
float MPU6050_countTemp(void);

/**
 * Counts the deviation angle of the MPU6050 module from the accelerometer data
 * @param  a - accelerometer data on the axes x, y, z
 * @param  b - accelerometer data on the axes x, y, z
 * @param  c - accelerometer data on the axes x, y, z
 * @return   calculated angle
 */
float _MPU6050_countAngle(float a, float b, float c);

/**
 * Counts the deviation angles of the MPU6050 module from the accelerometer data on the axes x, y, z
 * @return an array of the calculated angles
 */
float* MPU_getAccelAngles(void);

float* MPU_getFilteredAngles(float *previous_data, float* (* filter_func)(float* data, float* previous_data, unsigned char len));

/**
 * UART FUNCTIONS
 */

// Identifiers
#define START 33000

#define MINUS 33001
#define PLUS  33002

#define ACCEL 33003
#define GYRO  33004
#define TEMP  33005

/**
 * Transmiting two bytes using UART interface
 * @param data - two-byte value for transmit
 */
void MPU6050_twoBytesTransmit(int data);

/**
 * Transmiting an array of two-byte digits using UART interface
 * @param arr - an array of two-byte digits
 * @param len - length of array
 */
void MPU6050_arrayTransmit(int* arr, unsigned char len);

/**
 * Transmiting MPU6050 data
 * @param id   data type identifier
 * @param data - two-byte value for transmit
 */
void MPU6050_dataTransmit(int id, int* data);

#endif
