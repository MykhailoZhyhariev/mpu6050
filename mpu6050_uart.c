#include <util/delay.h>
#include "uart/uart.h"
#include "mpu6050.h"

void MPU6050_FewBytesTransmit(int data, unsigned char bytes) {
    for (unsigned char i = 0; i < bytes - 1; i++) {
        USART_Transmit((unsigned char)(data >> (8 * (bytes - i - 1))));
    }
    _delay_ms(50);
    USART_Transmit((unsigned char)data);
    _delay_ms(50);
}

void MPU6050_arrayTransmit(int* arr, unsigned char len) {
    for (unsigned char i = 0; i < len; i++) {
        int data = arr[i];

        if (data < 0) {
            data = -(data);
            MPU6050_FewBytesTransmit(MINUS, 2);
        } else {
            MPU6050_FewBytesTransmit(PLUS, 2);
        }

        MPU6050_FewBytesTransmit(data, 2);
    }
}

void MPU6050_dataTransmit(int id, int* data) {
    MPU6050_FewBytesTransmit(START, 2);

    unsigned char len = 3;

    switch (id) {
        case ACCEL:
            MPU6050_FewBytesTransmit(ACCEL, 2);
            break;

        case GYRO:
            MPU6050_FewBytesTransmit(GYRO, 2);
            break;

        case TEMP:
            len = 1;
            MPU6050_FewBytesTransmit(TEMP, 2);
            break;
    }

    MPU6050_arrayTransmit(data, len);
}
