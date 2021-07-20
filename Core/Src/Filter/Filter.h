/*
 * Filter.h
 *
 *  Created on: 2021Äê7ÔÂ19ÈÕ
 *      Author: h13
 */

#ifndef SRC_FILTER_FILTER_H_
#define SRC_FILTER_FILTER_H_

typedef struct
{
	float LastOutPut;
	float FilterCoefficient;
} LowPassFilter_t;

float LowPassFilterCalc(LowPassFilter_t *Filter, float Current);

#endif /* SRC_FILTER_FILTER_H_ */
