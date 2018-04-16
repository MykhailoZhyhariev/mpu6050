/* Name: complimentary_filter.h
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#ifndef COMPLIMENTARY_FILTER
#define COMPLIMENTARY_FILTER

// Filtration coefficient
#define WEIGHT 0.1

float COMPL_getFilteredAngle(float gyro, float accel);

float* COMPL_getFilteredAngles(float* gyro, float* accel, float* previous_data, unsigned char len);


#endif
