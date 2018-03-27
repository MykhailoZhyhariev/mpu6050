#include <avr/io.h>
#include "twi/i2c.h"
#include "lcd/lcd.h"
#include "mpu6050.h"


int main(void) {
    LCDInit(8);
    LCDClear();
    i2c_init();
    MPU6050_Init();

    mpu6050 mpu;

    while (1) {
        MPU6050_whoAmI(&mpu);
        LCDWriteIntXY(0, 0, mpu.who, 3);

        MPU6050_countTemp(&mpu);
        LCDWriteIntXY(5, 0, mpu.temp, 2);

        // MPU6050_getAccel(&mpu);
        //
        // LCDWriteIntXY(0, 0, mpu.accel_x, 5);
        // LCDWriteIntXY(6, 0, mpu.accel_y, 5);
        // LCDWriteIntXY(0, 1, mpu.accel_z, 5);

        // MPU6050_getGyro(&mpu);
        //
        // LCDWriteIntXY(0, 0, mpu.gyro_x, 5);
        // LCDWriteIntXY(6, 0, mpu.gyro_y, 5);
        // LCDWriteIntXY(0, 1, mpu.gyro_z, 5);

        _delay_ms(250);
    }
}
