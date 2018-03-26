#include <avr/io.h>
#include "twi/i2c.h"
#include "lcd/lcd.h"
#include "mpu6050.h"

int negateTransition(int value, char pos);

int main(void) {
    LCDInit(8);
    LCDClear();
    i2c_init();
    MPU6050_Init();

    mpu6050 mpu;

    while (1) {
        MPU6050_getAccel(&mpu);

        _delay_ms(250);
    }
}

int negateTransition(int value, char pos) {
    if (value > 0) {
        LCDWriteStringXY(pos, 0, "+");
        return value;
    }

    LCDWriteStringXY(pos, 0, "-");
    return -(value);
}
