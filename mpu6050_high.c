/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include "mpu6050.h"

void MPU6050_countTemp(mpu6050 *mpu6050) {
    mpu6050->temp = (mpu6050->temp_h << 8) + (mpu6050->temp_l + 12412);
    mpu6050->temp /= 340;
}
