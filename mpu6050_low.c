/* Name: mpu6050_low.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <stdlib.h>
#include "mpu6050.h"

/**
 * Move pointer to register
 * @param reg register address [hex]
 */
void _MPU6050_moveToReg(u8 reg) {
    I2C_start();
    I2C_send(MPU6050_W);
    I2C_send(reg);
    I2C_stop();
}

/**
 * Getting the value from a register
 * @param  reg register address [hex]
 * @param  len number of bytes of the register
 * @return     register value
 */
s32 _MPU6050_getRegValue(u8 reg, u8 len) {
    _MPU6050_moveToReg(reg);

    I2C_start();
    I2C_send(MPU6050_R);

    s32 value = 0;
    for (u8 i = 0; i < len - 1; i++) {
        value += I2C_get(0) << 8;
    }
    value += I2C_get(1);

    I2C_stop();

    return value;
}

/**
 * Writing value to the register
 * @param reg   register address [hex]
 * @param value value to write
 */
void _MPU6050_writeToReg(u8 reg, u8 value) {
    I2C_start();
    I2C_send(MPU6050_W);
    I2C_send(reg);
    I2C_send(value);
    I2C_stop();
}

/**
 * Getting an array of registers values
 * @param  reg - register address [hex]
 * @param  len - number of bytes of the register
 * @return     the array of values
 */
s32* _MPU6050_getArrValues(u8 reg, u8 len) {
    // Create array
    s32 *arr = (s32 *)malloc(len * sizeof(s32));

    // Getting values of registers
    for (u8 i = 0; i < len; i++) {
        arr[i] = _MPU6050_getRegValue(reg + i * 2, 2);
    }

    return arr;
}

/**
 * Initialize and set the settings MPU6050
 */
void MPU6050_Init(void) {
    // I2C Initialize
    I2C_init();

    //Sets sample rate to 8000/1+7 = 1000Hz
    _MPU6050_writeToReg(SMPLRT_DIV, 0x07);

    //Disable FSync, 256Hz DLPF
    _MPU6050_writeToReg(CONFIG, 0x00);

    //Disable gyro self tests, scale of 2000 degrees/s
    _MPU6050_writeToReg(GYRO_CONFIG, 0b00011000);

    //Disable accel self tests, scale of +-2g, no DHPF
    _MPU6050_writeToReg(ACCEL_CONFIG, 0x00);

    //Freefall threshold of |0mg|
    _MPU6050_writeToReg(FF_THR, 0x00);

    //Freefall duration limit of 0
    _MPU6050_writeToReg(FF_DUR, 0x00);

    //Motion threshold of 0mg
    _MPU6050_writeToReg(MOT_THR, 0x00);

    //Motion duration of 0s
    _MPU6050_writeToReg(MOT_DUR, 0x00);

    //Zero motion threshold
    _MPU6050_writeToReg(ZRMOT_THR, 0x00);

    //Zero motion duration threshold
    _MPU6050_writeToReg(ZRMOT_DUR, 0x00);

    //Disable sensor output to FIFO buffer
    _MPU6050_writeToReg(FIFO_EN, 0x00);

    //AUX I2C setup
    //Sets AUX I2C to single master control, plus other config
    _MPU6050_writeToReg(I2C_MST_CTRL, 0x00);
    //Setup AUX I2C slaves
    _MPU6050_writeToReg(I2C_SLV0_ADDR, 0x00);
    _MPU6050_writeToReg(I2C_SLV0_REG, 0x00);
    _MPU6050_writeToReg(I2C_SLV0_CTRL, 0x00);
    _MPU6050_writeToReg(I2C_SLV1_ADDR, 0x00);
    _MPU6050_writeToReg(I2C_SLV1_REG, 0x00);
    _MPU6050_writeToReg(I2C_SLV1_CTRL, 0x00);
    _MPU6050_writeToReg(I2C_SLV2_ADDR, 0x00);
    _MPU6050_writeToReg(I2C_SLV2_REG, 0x00);
    _MPU6050_writeToReg(I2C_SLV2_CTRL, 0x00);
    _MPU6050_writeToReg(I2C_SLV3_ADDR, 0x00);
    _MPU6050_writeToReg(I2C_SLV3_REG, 0x00);
    _MPU6050_writeToReg(I2C_SLV3_CTRL, 0x00);
    _MPU6050_writeToReg(I2C_SLV4_ADDR, 0x00);
    _MPU6050_writeToReg(I2C_SLV4_REG, 0x00);
    _MPU6050_writeToReg(I2C_SLV4_DO, 0x00);
    _MPU6050_writeToReg(I2C_SLV4_CTRL, 0x00);
    _MPU6050_writeToReg(I2C_SLV4_DI, 0x00);
    //I2C_MST_STATUS //Read-only
    //Setup INT pin and AUX I2C pass through
    _MPU6050_writeToReg(INT_PIN_CFG, 0x00);
    //Enable data ready interrupt
    _MPU6050_writeToReg(INT_ENABLE, 0x00);

    //Slave out, dont care
    _MPU6050_writeToReg(I2C_SLV0_DO, 0x00);
    _MPU6050_writeToReg(I2C_SLV1_DO, 0x00);
    _MPU6050_writeToReg(I2C_SLV2_DO, 0x00);
    _MPU6050_writeToReg(I2C_SLV3_DO, 0x00);
    //More slave config
    _MPU6050_writeToReg(I2C_MST_DELAY_CTRL, 0x00);
    //Reset sensor signal paths
    _MPU6050_writeToReg(SIGNAL_PATH_RESET, 0x00);
    //Motion detection control
    _MPU6050_writeToReg(MOT_DETECT_CTRL, 0x00);
    //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
    _MPU6050_writeToReg(USER_CTRL, 0x00);
    //Sets clock source to gyro reference w/ PLL
    _MPU6050_writeToReg(PWR_MGMT_1, 0b00000010);
    //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
    _MPU6050_writeToReg(PWR_MGMT_2, 0x00);
}

/**
 * Returning a value of "whoAmI" register MPU6050
 * @return  "whoAmI" register value
 */
u8 MPU6050_whoAmI(void) {
    // Getting value of "whoAmI" register
    return _MPU6050_getRegValue(WHO_AM_I, 1);
}

/**
 * Getting a value of temperature registers MPU6050
 * @return  temperature register value
 */
s32 MPU6050_getTemp(void) {
    // Getting value of temperature register
    return _MPU6050_getRegValue(TEMP_OUT_H, 2);
}

/**
 * Getting a value of accelerometer registers MPU6050
 * @return  the array of accelerometer registers values
 */
s32* MPU6050_getAccel(void) {
    // Getting value of accelerometer registers for X, Y and Z axises
    return _MPU6050_getArrValues(ACCEL_XOUT_H, 3);
}

/**
 * Getting a value of gyroscope registers MPU6050
 * @return  the array of gyroscope registers values
 */
s32* MPU6050_getGyro(void) {
    // Getting value of gyroscope registers for X, Y and Z axises
    return _MPU6050_getArrValues(GYRO_XOUT_H, 3);
}
