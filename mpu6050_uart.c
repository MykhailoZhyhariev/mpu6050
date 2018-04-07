#include <util/delay.h>
#include <math.h>
#include "uart/uart.h"
#include "mpu6050.h"


void MPU6050_twoBytesTransmit(int data) {
    USART_Transmit((data >> 8) & 0xFF);
    USART_Transmit(data & 0xFF);
}

void MPU6050_arrayTransmit(int* arr, unsigned char len) {
    for (unsigned char i = 0; i < len; i++) {
        int data = arr[i];
        if (data < 0) {
            MPU6050_twoBytesTransmit(MINUS);
            data = -(data);
        } else {
            MPU6050_twoBytesTransmit(PLUS);
        }

        MPU6050_twoBytesTransmit(data);
    }
}

void MPU6050_dataTransmit(int id, int* data) {
    MPU6050_twoBytesTransmit(START);

    unsigned char len = 3;

    switch (id) {
        case ACCEL:
            MPU6050_twoBytesTransmit(ACCEL);
            break;

        case GYRO:
            MPU6050_twoBytesTransmit(GYRO);
            break;

        case TEMP:
            len = 1;
            MPU6050_twoBytesTransmit(TEMP);
            break;
    }

    MPU6050_arrayTransmit(data, len);
}
