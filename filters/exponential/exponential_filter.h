/* Name: exponential_filter.h
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#ifndef EXP_FILTER
#define EXP_FILTER

// Filtration coefficient
#define LAMBDA 0.5

/**
 * Performs an exponential filtering of input data
 * @param  data          - input data value
 * @param  previous_data - previous data value
 * @return               filtered data
 */
float EXP_getFilteredAngle(float accel, float previous_data);

/**
 * Performs an exponential filtering an array of input data
 * @param  data          - an array of input data
 * @param  previous_data - an array of previous data value
 * @param  len           - an array length
 * @return               an array of filtered data
 */
float* EXP_getFilteredAngles(float* accel, float* gyro, float* previous_data, unsigned char len);


#endif
