/* Name: mpu6050_uart.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "uart/uart.h"
#include "mpu6050.h"

/**
 * Transmitting two bytes using UART interface
 * @param data - two-byte value for Transmitting
 */
void MPU6050_twoBytesTransmit(int data) {
    // Transmitting high byte of data
    USART_Transmit((data >> 8) & 0xFF);
    // Transmitting low byte of data
    USART_Transmit(data & 0xFF);
}

/**
 * Receiving two bytes using UART interface
 * @return    received two-bytes data
 */
int MPU6050_twoBytesReceive(void) {
    int data = USART_Receive() << 8;
    data |= USART_Receive();
    return data;
}

/**
 * Transmitting an array of two-byte digits using UART interface
 * @param arr - an array of two-byte digits
 * @param len - length of array
 */
void MPU6050_arrayTransmit(int* arr, unsigned char len) {
    for (unsigned char i = 0; i < len; i++) {
        int data = arr[i];
        // If the data variable is less than zero, invert it and transmitting the "minus" identifier
        if (data < 0) {
            MPU6050_twoBytesTransmit(MINUS);
            data = -(data);
        } else {
            // Else transmitting "plus" identifier
            MPU6050_twoBytesTransmit(PLUS);
        }

        // Transmitting data
        MPU6050_twoBytesTransmit(data);
    }
}

/**
 * Transmitting MPU6050 data
 * @param id   data type identifier
 * @param data - two-byte value for Transmitting
 */
void MPU6050_dataTransmit(int id, int* data) {
    // Transmitting "start" identifier
    MPU6050_twoBytesTransmit(START);

    // Data array length
    unsigned char len = 3;

    switch (id) {
        // If it data from accelerometer transmitting "accel" identifier
        case ACCEL:
            MPU6050_twoBytesTransmit(ACCEL);
            break;

        // If it data from gyroscope transmitting "gyro" identifier
        case GYRO:
            MPU6050_twoBytesTransmit(GYRO);
            break;

        // If it data from temperature transmitting "temp" identifier
        case TEMP:
            // Set length is one because the temperature is one two-bytes digit
            len = 1;
            MPU6050_twoBytesTransmit(TEMP);
            break;
    }

    // Transmitting data array
    MPU6050_arrayTransmit(data, len);
}

/**
 * Transmitting data according to received id
 * @return data according to received id
 */
int* MPU6050_dataReceive() {
    // Creating a data array
    int* data = NULL;

    // Receiving two-bytes id
    int id = MPU6050_twoBytesReceive();
    switch (id) {
        case ACCEL:
            // Getting accelerometer data
            data = MPU6050_getAccel();
            // Transmitting data
            MPU6050_dataTransmit(id, data);
            break;

        case GYRO:
            // Getting gyroscope data
            data = MPU6050_getGyro();
            // Transmitting data
            MPU6050_dataTransmit(id, data);
            break;

        case TEMP:
            // Getting temperature data
            data = (int *)MPU6050_getTemp();
            // Transmitting data
            MPU6050_dataTransmit(id, data);
            break;
    }

    return data;
}
