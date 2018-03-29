/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include "mpu6050.h"
#include "mpu6050_constants.h"
#include <wiringPiI2C.h>

/**
 * Initialise and set the settings MPU6050
 * @return  [fd] - pointer on device file
 */
int MPU6050_Init(void) {

    int fd = wiringPiI2CSetupInterface(MPU6050, 0x68);

    //Sets sample rate to 8000/1+7 = 1000Hz
    wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x07);

    //Disable FSync, 256Hz DLPF
    wiringPiI2CWriteReg8(fd, CONFIG, 0x00);

    //Disable gyro self tests, scale of 2000 degrees/s
    wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 0b00011000);

    //Disable accel self tests, scale of +-2g, no DHPF
    wiringPiI2CWriteReg8(fd, ACCEL_CONFIG, 0x00);

    //Freefall threshold of |0mg|
    wiringPiI2CWriteReg8(fd, FF_THR, 0x00);

    //Freefall duration limit of 0
    wiringPiI2CWriteReg8(fd, FF_DUR, 0x00);

    //Motion threshold of 0mg
    wiringPiI2CWriteReg8(fd, MOT_THR, 0x00);

    //Motion duration of 0s
    wiringPiI2CWriteReg8(fd, MOT_DUR, 0x00);

    //Zero motion threshold
    wiringPiI2CWriteReg8(fd, ZRMOT_THR, 0x00);

    //Zero motion duration threshold
    wiringPiI2CWriteReg8(fd, ZRMOT_DUR, 0x00);

    //Disable sensor output to FIFO buffer
    wiringPiI2CWriteReg8(fd, FIFO_EN, 0x00);

    //AUX I2C setup
    //Sets AUX I2C to single master control, plus other config
    wiringPiI2CWriteReg8(fd, I2C_MST_CTRL, 0x00);
    //Setup AUX I2C slaves
    wiringPiI2CWriteReg8(fd, I2C_SLV0_ADDR, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV0_REG, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV0_CTRL, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV1_ADDR, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV1_REG, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV1_CTRL, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV2_ADDR, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV2_REG, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV2_CTRL, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV3_ADDR, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV3_REG, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV3_CTRL, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV4_ADDR, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV4_REG, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV4_DO, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV4_CTRL, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV4_DI, 0x00);
    //I2C_MST_STATUS //Read-only
    //Setup INT pin and AUX I2C pass through
    wiringPiI2CWriteReg8(fd, INT_PIN_CFG, 0x00);
    //Enable data ready interrupt
    wiringPiI2CWriteReg8(fd, INT_ENABLE, 0x00);

    //Slave out, dont care
    wiringPiI2CWriteReg8(fd, I2C_SLV0_DO, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV1_DO, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV2_DO, 0x00);
    wiringPiI2CWriteReg8(fd, I2C_SLV3_DO, 0x00);
    //More slave config
    wiringPiI2CWriteReg8(fd, I2C_MST_DELAY_CTRL, 0x00);
    //Reset sensor signal paths
    wiringPiI2CWriteReg8(fd, SIGNAL_PATH_RESET, 0x00);
    //Motion detection control
    wiringPiI2CWriteReg8(fd, MOT_DETECT_CTRL, 0x00);
    //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
    wiringPiI2CWriteReg8(fd, USER_CTRL, 0x00);
    //Sets clock source to gyro reference w/ PLL
    wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0b00000010);
    //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
    wiringPiI2CWriteReg8(fd, PWR_MGMT_2, 0x00);

    return fd;
}

/**
 * Returning a value of "whoAmI" register MPU6050
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_whoAmI(mpu6050 *mpu6050) {
    mpu6050->who = wiringPiI2CReadReg16(mpu6050->fd, WHO_AM_I);
}

/**
 * Getting a value of temperature registers MPU6050
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_getTemp(mpu6050 *mpu6050) {
    // Getting value of temperature register
    mpu6050->temp_reg = wiringPiI2CReadReg16(mpu6050->fd, TEMP_OUT_H);
}

/**
 * Getting a value of accelerometer registers MPU6050
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_getAccel(mpu6050 *mpu6050) {
    // Getting value of accelerometer registers for X, Y and Z axises
    mpu6050->accel_x = wiringPiI2CReadReg16(mpu6050->fd, ACCEL_XOUT_H);
    mpu6050->accel_y = wiringPiI2CReadReg16(mpu6050->fd, ACCEL_YOUT_H);
    mpu6050->accel_z = wiringPiI2CReadReg16(mpu6050->fd, ACCEL_ZOUT_H);
}

/**
 * Getting a value of gyroscope registers MPU6050
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_getGyro(mpu6050 *mpu6050) {
    // Getting value of gyroscope registers for X, Y and Z axises
    mpu6050->gyro_x = wiringPiI2CReadReg16(mpu6050->fd, GYRO_XOUT_H);
    mpu6050->gyro_y = wiringPiI2CReadReg16(mpu6050->fd, GYRO_YOUT_H);
    mpu6050->gyro_z = wiringPiI2CReadReg16(mpu6050->fd, GYRO_ZOUT_H);
}
