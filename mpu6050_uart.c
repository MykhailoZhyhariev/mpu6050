/* Name: mpu6050_uart.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <util/delay.h>
#include <math.h>
#include "uart/uart.h"
#include "mpu6050.h"

/**
 * Transmit two bytes using UART interface
 * @param data - two-byte value for transmit
 */
void MPU6050_twoBytesTransmit(int data) {
    // Transmit high byte of data
    USART_Transmit((data >> 8) & 0xFF);
    // Transmit low byte of data
    USART_Transmit(data & 0xFF);
}

/**
 * Transmit an array of two-byte digits using UART interface
 * @param arr - an array of two-byte digits
 * @param len - length of array
 */
void MPU6050_arrayTransmit(int* arr, unsigned char len) {
    for (unsigned char i = 0; i < len; i++) {
        // Create a мфкшф
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
