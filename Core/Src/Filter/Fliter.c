/*
 * Fliter.c
 *
 *  Created on: 2021��7��19��
 *      Author: h13
 */
#include "Filter.h"

float LowPassFilterCalc(LowPassFilter_t *Filter, float Current)
{
	Filter -> LastOutPut = Filter -> FilterCoefficient * Current + (1 - Filter -> FilterCoefficient) * Filter -> LastOutPut;
	return Filter -> LastOutPut;
}
