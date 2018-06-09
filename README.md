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

To initialize, you must use the `MPU6050_Init`.

To get temperature register value you should use `MPU6050_getTemp`.

To get accelerometer registers values you should use `MPU6050_getAccel`.

To get gyroscope registers values you should use `MPU6050_getGyro`.

To get temperature value in degrees Celsius you should use `MPU6050_countTemp`.

To get temperature value in degrees Celsius you should use `MPU6050_countTemp`.

To get accelerometer angles values you should use `MPU6050_getAccelAngles`.

To get gyroscope angles values you should use `MPU6050_getGyroAngles`.

Filtration accelerometer and gyroscope angles
---------------------------------------------

Coming soon....


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
