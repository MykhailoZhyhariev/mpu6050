/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include "mpu6050.h"
#include "constants.c"
#include "twi/i2c.h"

void MPU6050_Init(void) {
    //Sets sample rate to 8000/1+7 = 1000Hz
    I2C_write(MPU6050_W, MPU6050_RA_SMPLRT_DIV, 0x07);

    //Disable FSync, 256Hz DLPF
    I2C_write(MPU6050_W, MPU6050_RA_CONFIG, 0x00);

    //Disable gyro self tests, scale of 2000 degrees/s
    I2C_write(MPU6050_W, MPU6050_RA_GYRO_CONFIG, 0b00011000);

    //Disable accel self tests, scale of +-2g, no DHPF
    I2C_write(MPU6050_W, MPU6050_RA_ACCEL_CONFIG, 0x00);

    //Freefall threshold of |0mg|
    I2C_write(MPU6050_W, MPU6050_RA_FF_THR, 0x00);

    //Freefall duration limit of 0
    I2C_write(MPU6050_W, MPU6050_RA_FF_DUR, 0x00);

    //Motion threshold of 0mg
    I2C_write(MPU6050_W, MPU6050_RA_MOT_THR, 0x00);

    //Motion duration of 0s
    I2C_write(MPU6050_W, MPU6050_RA_MOT_DUR, 0x00);

    //Zero motion threshold
    I2C_write(MPU6050_W, MPU6050_RA_ZRMOT_THR, 0x00);

    //Zero motion duration threshold
    I2C_write(MPU6050_W, MPU6050_RA_ZRMOT_DUR, 0x00);

    //Disable sensor output to FIFO buffer
    I2C_write(MPU6050_W, MPU6050_RA_FIFO_EN, 0x00);

    //AUX I2C setup
    //Sets AUX I2C to single master control, plus other config
    I2C_write(MPU6050_W, MPU6050_RA_I2C_MST_CTRL, 0x00);
    //Setup AUX I2C slaves
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV0_ADDR, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV0_REG, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV0_CTRL, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV1_ADDR, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV1_REG, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV1_CTRL, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV2_ADDR, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV2_REG, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV2_CTRL, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV3_ADDR, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV3_REG, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV3_CTRL, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV4_ADDR, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV4_REG, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV4_DO, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV4_CTRL, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV4_DI, 0x00);
    //MPU6050_RA_I2C_MST_STATUS //Read-only
    //Setup INT pin and AUX I2C pass through
    I2C_write(MPU6050_W, MPU6050_RA_INT_PIN_CFG, 0x00);
    //Enable data ready interrupt
    I2C_write(MPU6050_W, MPU6050_RA_INT_ENABLE, 0x00);

    //Slave out, dont care
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV0_DO, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV1_DO, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV2_DO, 0x00);
    I2C_write(MPU6050_W, MPU6050_RA_I2C_SLV3_DO, 0x00);
    //More slave config
    I2C_write(MPU6050_W, MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
    //Reset sensor signal paths
    I2C_write(MPU6050_W, MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
    //Motion detection control
    I2C_write(MPU6050_W, MPU6050_RA_MOT_DETECT_CTRL, 0x00);
    //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
    I2C_write(MPU6050_W, MPU6050_RA_USER_CTRL, 0x00);
    //Sets clock source to gyro reference w/ PLL
    I2C_write(MPU6050_W, MPU6050_RA_PWR_MGMT_1, 0b00000010);
    //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
    I2C_write(MPU6050_W, MPU6050_RA_PWR_MGMT_2, 0x00);
}

void MPU6050_whoAmI(mpu6050 *mpu6050) {
    i2c_start_cond();
    i2c_send_byte(MPU6050_W);
    i2c_send_byte(MPU6050_RA_WHO_AM_I);
    i2c_stop_cond();

    i2c_start_cond();
    i2c_send_byte(MPU6050_R);
    mpu6050->who = i2c_get_byte(1);
    i2c_stop_cond();
}

void MPU6050_getTemp(mpu6050 *mpu6050) {
    i2c_start_cond();
    i2c_send_byte(MPU6050_W);
    i2c_send_byte(MPU6050_RA_TEMP_OUT_H);
    i2c_stop_cond();

    i2c_start_cond();
    i2c_send_byte(MPU6050_R);
    mpu6050->temp_h = i2c_get_byte(0);
    mpu6050->temp_l = i2c_get_byte(1);
    i2c_stop_cond();
}
