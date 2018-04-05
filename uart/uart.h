#ifndef UART_H
#define UART_H

#define FOSC 1000000
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

void USART_Init(unsigned char ubrr);

void USART_Transmit(unsigned char data);

unsigned char USART_Receive(void);

#endif
