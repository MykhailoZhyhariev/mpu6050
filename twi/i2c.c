#include <util/delay.h>
#include "i2c.h"

volatile unsigned char i2c_frame_error = 0;

void i2c_stop_cond(void) {
	I2C_DDR |= _BV(SCL);
	I2C_DELAY
	I2C_DDR |= _BV(SDA);
	I2C_DELAY

	I2C_DDR &= ~_BV(SCL);
	I2C_DELAY
	I2C_DDR &= ~_BV(SDA);
	I2C_DELAY

	i2c_frame_error = 0;

	if ((I2C_PIN & _BV(SDA)) == 0) i2c_frame_error++;
	if ((I2C_PIN & _BV(SCL)) == 0) i2c_frame_error++;

	I2C_DELAY
	I2C_DELAY
	I2C_DELAY
	I2C_DELAY
}

void i2c_init(void) {
	I2C_DDR &= ~_BV(SDA);
	I2C_DDR &= ~_BV(SCL);

	I2C_PORT &= ~_BV(SDA);
	I2C_PORT &= ~_BV(SCL);

	i2c_stop_cond();
}

void i2c_start_cond(void)	{
	I2C_DDR |= _BV(SDA);
	I2C_DELAY
	I2C_DDR |= _BV(SCL);
	I2C_DELAY
}

void i2c_restart_cond(void)	{
	I2C_DDR &= ~_BV(SDA);
	I2C_DELAY
	I2C_DDR &= ~_BV(SCL);
	I2C_DELAY

	I2C_DDR |= _BV(SDA);
	I2C_DELAY
	I2C_DDR |= _BV(SCL);
	I2C_DELAY
}

unsigned char i2c_send_byte(unsigned char data)	{
	unsigned char i;
	unsigned char ack = 1;

	for (i = 0; i < 8; i++) {
		if ((data & 0x80) == 0x00) I2C_DDR |= _BV(SDA);
		else I2C_DDR &= ~_BV(SDA);

		I2C_DELAY
		I2C_DDR &= ~_BV(SCL);

		I2C_DELAY
		I2C_DDR |= _BV(SCL);

		data = data << 1;
	}

	I2C_DDR &= ~_BV(SDA);
	I2C_DELAY

	I2C_DDR &= ~_BV(SCL);
	I2C_DELAY

	if ((I2C_PIN&_BV(SDA))==_BV(SDA)) ack = 1;
	else ack = 0;

	I2C_DDR |= _BV(SCL);

	return ack;
}

unsigned char i2c_get_byte(unsigned char last_byte)	{
	unsigned char i, res = 0;
	I2C_DDR &= ~_BV(SDA);

	for (i = 0; i < 8; i++) {
		res = res << 1;

		I2C_DDR &= ~_BV(SCL);
		I2C_DELAY

		if ((I2C_PIN & _BV(SDA)) == _BV(SDA)) res = res | 0x01;

		I2C_DDR |= _BV(SCL);
		I2C_DELAY
	}

	if (last_byte == 0) I2C_DDR |= _BV(SDA);
	else I2C_DDR &= ~_BV(SDA);

	I2C_DELAY
	I2C_DDR &= ~_BV(SCL);

	I2C_DELAY
	I2C_DDR |= _BV(SCL);

	I2C_DELAY
	I2C_DDR &= ~_BV(SDA);

	return res;
}
