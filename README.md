Description
------------

The MPU-6050 is the world’s first integrated 6-axis MotionTracking device that combines a 3-axis gyroscope, 3-axis accelerometer, and a Digital Motion ProcessorTM (DMP) all in a small 4x4x0.9mm package.

Here is a small library for work with MPU6050.

Supported devices:
-   AVR microcontrollers;
-   orangePi;
-   raspberryPi;
-   etc...


Initialize and usage
--------------------

- `MPU6050_Init` - Initialize and set the settings MPU6050;

- `MPU6050_whoAmI` - Returning a value of "whoAmI" register MPU6050;

- `MPU6050_getTemp` - Getting a value of temperature registers MPU6050;

- `MPU6050_getAccel` - Getting a value of accelerometer registers MPU6050;

- `MPU6050_getGyro` - Getting a value of gyroscope registers MPU6050;

- `MPU6050_countTemp` - Computing the temperature in degrees Celsius;

- `MPU6050_getGyroAngles` - Counts the deviation angles of the MPU6050 module from the accelerometer data on the axes x, y, z;

- `MPU6050_getAccelAngles` - Counts the deviation angles of the MPU6050 module from the accelerometer data on the axes x, y, z.


Custom variable type
--------------------

Library use `stdint.h` variable types.

```
#include <stdint.h>

// Signed custom variables types
typedef int8_t      s8;
typedef int16_t     s16;
typedef int32_t     s32;

// Unsigned custom variables types
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
```


Data transmit/receive protocol
------------------------------

In `mpu6050.h` file you can specify the path to the I2C library.

```
// Path to I2C library. You can specify your path.
#include "twi/i2c.h"
```

You also can specify you own I2C functions:

```
/**
 * I2C functions name. You can use your own functions.
 * init     - initializing I2C protocol.
 * start    - start condition
 * stop     - stop condition
 * send     - sends the one-byte value. Takes "unsigned char" value as param.
 * get      - receives the one-byte value. Pass "1" if it's the last byte
 */
#define I2C_init()      (i2c_init())
#define I2C_start()     (i2c_start_cond())
#define I2C_stop()      (i2c_stop_cond())
#define I2C_send(x)     (i2c_send_byte(x))
#define I2C_get(x)      (i2c_get_byte(x))
```


Filtration accelerometer and gyroscope angles
---------------------------------------------

You should use `MPU6050_getFilteredAngles` function.

`MPU6050_getFilteredAngles` take `previous_data` and `filter_func` as params and return an array on filtered values.

`float* filter_func` is a callback function that take:

1) `float* accel` - an array of unfiltered accelerometer data;

2) `float* gyro` - an array of unfiltered gyroscope data;

3) `float* previous_data` - an array of previous filtered data;

4) `u8 len` - an arrays length;

If you need to filter only one vector (only accelerometer or only gyroscope) you can use `NULL` instead of an array pointer.

Small example of filtering value.

```
// Filtration coefficient
#define LAMBDA  0.5

/**
 * Performs an exponential filtering of input data
 * @param  data          - input data value
 * @param  previous_data - previous data value
 * @return               filtered data
 */
float EXP_getFilteredAngle(float accel, float previous_data) {
    return LAMBDA * accel + (1 - LAMBDA) * previous_data;
}

/**
 * Performs an exponential filtering an array of input data
 * @param  data          - an array of input data
 * @param  previous_data - an array of previous data value
 * @param  len           - an array length
 * @return               an array of filtered data
 */
float* EXP_getFilteredAngles(float* accel, float* gyro, float* previous_data, unsigned char len) {
    float* ret = (float *)malloc(sizeof(float) * len);
    for (unsigned char i = 0; i < len; i++) {
        ret[i] = EXP_getFilteredAngle(accel[i], previous_data[i]);
    }
    return ret;
}

int main(void) {
  // Some code...

  // Allocating memory for an array
  float* filtered_accel = (float *)malloc(sizeof(float) * 3);
  for (u8 i = 0; i < 3; i++) filtered_accel[i] = 0;

  while(1) {
    // Getting filtered accelerometer data
    filtered_accel = MPU6050_getFilteredAngles(filtered_accel, EXP_getFilteredAngles);

    // Waiting 500ms before doing next measured
    _delay_ms(500);
  }
}
```
