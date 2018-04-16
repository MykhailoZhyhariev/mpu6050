/* Name: complimentary_filter.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <stdlib.h>
#include "complimentary_filter.h"

float COMPL_getFilteredAngle(float gyro, float accel) {
    return (1 - WEIGHT) * gyro + WEIGHT * accel;
}

float* COMPL_getFilteredAngles(float* gyro, float* accel, float* previous_data, unsigned char len) {
    float* ret = (float *)malloc(sizeof(float) * len);
    for (unsigned char i = 0; i < len; i++) {
        ret[i] = COMPL_getFilteredAngle(gyro[i], accel[i]);
    }
    return ret;
}
