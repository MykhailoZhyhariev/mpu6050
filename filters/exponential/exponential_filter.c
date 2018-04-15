/* Name: exponential_filter.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <stdlib.h>
#include "exponential_filter.h"

/**
 * Performs an exponential filtering of input data
 * @param  data          - input data value
 * @param  previous_data - previous data value
 * @return               filtered data
 */
float EXP_getExpFilteredAngle(float data, float previous_data) {
    return LAMBDA * data + (1 - LAMBDA) * previous_data;
}

/**
 * Performs an exponential filtering an array of input data
 * @param  data          - an array of input data
 * @param  previous_data - an array of previous data value
 * @param  len           - an array length
 * @return               an array of filtered data
 */
float* EXP_getExpFilteredAngles(float* data, float* previous_data, unsigned char len) {
    float* ret = (float *)malloc(sizeof(float) * len);
    for (unsigned char i = 0; i < len; i++) {
        ret[i] = EXP_getExpFilteredAngle(data[i], previous_data[i]);
    }
    return ret;
}
