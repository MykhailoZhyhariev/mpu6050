/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include "mpu6050.h"
#include "constants.c"
#include "twi/i2c.h"
#include "lcd/lcd.h"

/**
 * Move pointer to register
 * @param reg register address [hex]
 */
void _MPU6050_moveToReg(unsigned char reg) {
    i2c_start_cond();
    i2c_send_byte(MPU6050_W);
    i2c_send_byte(reg);
    i2c_stop_cond();
}

/**
 * Getting the value from a register
 * @param  reg register address [hex]
 * @param  len number of bytes of the register
 * @return     register value
 */
int _MPU6050_getRegValue(unsigned char reg, unsigned char len) {
    _MPU6050_moveToReg(reg);

    i2c_start_cond();
    i2c_send_byte(MPU6050_R);

    int value = 0;
    for (unsigned char i = 0; i < len - 1; i++) {
        value += i2c_get_byte(0) << 8;
    }
    value += i2c_get_byte(1);

    i2c_stop_cond();

    return value;
}

/**
 * Writing value to the register
 * @param reg   register address [hex]
 * @param value value to write
 */
void _MPU6050_writeToReg(unsigned char reg, unsigned char value) {
    i2c_start_cond();
    i2c_send_byte(MPU6050_W);
    i2c_send_byte(reg);
    i2c_send_byte(value);
    i2c_stop_cond();
}

/**
 * Initialise and set the settings MPU6050
 */
void MPU6050_Init(void) {
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
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_whoAmI(mpu6050 *mpu6050) {
    mpu6050->who = _MPU6050_getRegValue(WHO_AM_I, 1);
}

/**
 * Getting a value of temperature registers MPU6050
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_getTemp(mpu6050 *mpu6050) {
    // Getting value of temperature register
    mpu6050->temp_reg = _MPU6050_getRegValue(TEMP_OUT_H, 2);
}

/**
 * Getting a value of accelerometer registers MPU6050
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_getAccel(mpu6050 *mpu6050) {
    // Getting value of accelerometer registers for X, Y and Z axises
    mpu6050->accel_x = _MPU6050_getRegValue(ACCEL_XOUT_H, 2);
    mpu6050->accel_y = _MPU6050_getRegValue(ACCEL_YOUT_H, 2);
    mpu6050->accel_z = _MPU6050_getRegValue(ACCEL_ZOUT_H, 2);
}

/**
 * Getting a value of gyroscope registers MPU6050
 * @param mpu6050 - structure that containing all measured variables
 */
void MPU6050_getGyro(mpu6050 *mpu6050) {
    // Getting value of gyroscope registers for X, Y and Z axises
    mpu6050->gyro_x = _MPU6050_getRegValue(GYRO_XOUT_H, 2);
    mpu6050->gyro_y = _MPU6050_getRegValue(GYRO_YOUT_H, 2);
    mpu6050->gyro_z = _MPU6050_getRegValue(GYRO_ZOUT_H, 2);
}
