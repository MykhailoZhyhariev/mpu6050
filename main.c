#include <avr/io.h>
#include "twi/i2c.h"
#include "lcd/lcd.h"
#include "mpu6050.h"

signed char negateTransition(signed char reg);

int main(void) {
    LCDInit(8);
    LCDClear();
    i2c_init();
    MPU6050_Init();

    mpu6050 mpu;

    while (1) {
        // MPU6050_whoAmI(&mpu);
        // LCDWriteIntXY(0,0, mpu.who, 3);

        // MPU6050_getTemp(&mpu);
        LCDWriteIntXY(0, 0, mpu.temp_h, 5);
        LCDWriteIntXY(0, 1, mpu.temp_l, 5);

        MPU6050_countTemp(&mpu);
        LCDWriteIntXY(10,0, mpu.temp, 2);

        _delay_ms(500);
    }
}
