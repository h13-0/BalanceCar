/*
 * Fliter.c
 *
 *  Created on: 2021Äê7ÔÂ19ÈÕ
 *      Author: h13
 */
#include "Filter.h"

float LowPassFilterCalc(LowPassFilter_t *Filter, float Current)
{
	Filter -> LastOutPut = Filter -> FilterCoefficient * Current + (1 - Filter -> FilterCoefficient) * Filter -> LastOutPut;
	return Filter -> LastOutPut;
}
