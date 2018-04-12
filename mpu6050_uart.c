/* Name: mpu6050_uart.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <util/delay.h>
#include <math.h>
#include "uart/uart.h"
#include "mpu6050.h"

/**
 * Transmiting two bytes using UART interface
 * @param data - two-byte value for Transmiting
 */
void MPU6050_twoBytesTransmit(int data) {
    // Transmiting high byte of data
    USART_Transmit((data >> 8) & 0xFF);
    // Transmiting low byte of data
    USART_Transmit(data & 0xFF);
}

/**
 * Transmiting an array of two-byte digits using UART interface
 * @param arr - an array of two-byte digits
 * @param len - length of array
 */
void MPU6050_arrayTransmit(int* arr, unsigned char len) {
    for (unsigned char i = 0; i < len; i++) {
        int data = arr[i];
        // If the data variable is less than zero, invert it and transmiting the "minus" identifier
        if (data < 0) {
            MPU6050_twoBytesTransmit(MINUS);
            data = -(data);
        } else {
            // Else transmiting "plus" identifier
            MPU6050_twoBytesTransmit(PLUS);
        }

        // Transmiting data
        MPU6050_twoBytesTransmit(data);
    }
}

/**
 * Transmiting MPU6050 data
 * @param id   data type identifier
 * @param data - two-byte value for Transmiting
 */
void MPU6050_dataTransmit(int id, int* data) {
    // Transmiting "start" identifier
    MPU6050_twoBytesTransmit(START);

    // Data array length
    unsigned char len = 3;

    switch (id) {
        // If it data from accelerometer transmiting "accel" identifier
        case ACCEL:
            MPU6050_twoBytesTransmit(ACCEL);
            break;

        // If it data from gyroscope transmiting "gyro" identifier
        case GYRO:
            MPU6050_twoBytesTransmit(GYRO);
            break;

        // If it data from temperature transmiting "temp" identifier
        case TEMP:
            // Set length is one because the temperature is one two-bytes digit
            len = 1;
            MPU6050_twoBytesTransmit(TEMP);
            break;
    }

    // Transmiting data array
    MPU6050_arrayTransmit(data, len);
}
