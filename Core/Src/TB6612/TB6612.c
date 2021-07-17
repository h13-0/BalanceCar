/*
 * TB6612.c
 *
 *  Created on: 2021年6月26日
 *      Author: h13
 */
#include "TB6612.h"

#include <stddef.h>

void TB6612Init(TB6612_t *TB6612)
{
	LL_TIM_CC_EnableChannel(TB6612 -> TimPort, TB6612 -> PWMA_Channel);
	LL_TIM_CC_EnableChannel(TB6612 -> TimPort, TB6612 -> PWMB_Channel);

	if(IS_TIM_REPETITION_COUNTER_INSTANCE(TB6612 -> TimPort))
	{
		LL_TIM_EnableAllOutputs(TB6612 -> TimPort);
	}

	LL_TIM_EnableCounter(TB6612 -> TimPort);

	LL_GPIO_ResetOutputPin(TB6612 -> AIN1Port, TB6612 -> AIN1Pin);
	LL_GPIO_ResetOutputPin(TB6612 -> AIN2Port, TB6612 -> AIN2Pin);
	LL_GPIO_ResetOutputPin(TB6612 -> BIN1Port, TB6612 -> BIN1Pin);
	LL_GPIO_ResetOutputPin(TB6612 -> BIN2Port, TB6612 -> BIN2Pin);
}

void TB6612SetPWMA_Value(TB6612_t *TB6612, int16_t value)
{
	uint16_t finalValue = 0;

	if (value > 0) {
		LL_GPIO_ResetOutputPin(TB6612 -> AIN1Port, TB6612 -> AIN1Pin);
		LL_GPIO_SetOutputPin(TB6612 -> AIN2Port, TB6612 -> AIN2Pin);

		if(value < TB6612 -> MaxPWM_Value)
		{
			finalValue = value + TB6612 -> DeadZone;
		}else {
			finalValue = TB6612 -> MaxPWM_Value;
		}
	} else if(value == 0) {
		LL_GPIO_ResetOutputPin(TB6612 -> AIN1Port, TB6612 -> AIN1Pin);
		LL_GPIO_ResetOutputPin(TB6612 -> AIN2Port, TB6612 -> AIN2Pin);
	} else {
		LL_GPIO_SetOutputPin(TB6612 -> AIN1Port, TB6612 -> AIN1Pin);
		LL_GPIO_ResetOutputPin(TB6612 -> AIN2Port, TB6612 -> AIN2Pin);

		if(value > (- TB6612 -> MaxPWM_Value))
		{
			finalValue = - value + TB6612 -> DeadZone;
		}else{
			finalValue = TB6612 -> MaxPWM_Value;
		}
	}

	switch(TB6612 -> PWMA_Channel)
	{
	case LL_TIM_CHANNEL_CH1:
		LL_TIM_OC_SetCompareCH1(TB6612 -> TimPort, finalValue);
		break;
	case LL_TIM_CHANNEL_CH2:
		LL_TIM_OC_SetCompareCH2(TB6612 -> TimPort, finalValue);
		break;
	case LL_TIM_CHANNEL_CH3:
		LL_TIM_OC_SetCompareCH3(TB6612 -> TimPort, finalValue);
		break;
	case LL_TIM_CHANNEL_CH4:
		LL_TIM_OC_SetCompareCH4(TB6612 -> TimPort, finalValue);
		break;
	default:
		break;
	}
	return;
}

void TB6612SetPWMB_Value(TB6612_t *TB6612, int16_t value)
{
	uint16_t finalValue = 0;

	if (value > 0) {
		LL_GPIO_ResetOutputPin(TB6612 -> BIN1Port, TB6612 -> BIN1Pin);
		LL_GPIO_SetOutputPin(TB6612 -> BIN2Port, TB6612 -> BIN2Pin);

		if(value < TB6612 -> MaxPWM_Value)
		{
			finalValue = value + TB6612 -> DeadZone;
		}else {
			finalValue = TB6612 -> MaxPWM_Value;
		}
	} else if(value == 0) {
		LL_GPIO_ResetOutputPin(TB6612 -> BIN1Port, TB6612 -> BIN1Pin);
		LL_GPIO_ResetOutputPin(TB6612 -> BIN2Port, TB6612 -> BIN2Pin);
	} else {
		LL_GPIO_SetOutputPin(TB6612 -> BIN1Port, TB6612 -> BIN1Pin);
		LL_GPIO_ResetOutputPin(TB6612 -> BIN2Port, TB6612 -> BIN2Pin);

		if(value > (- TB6612 -> MaxPWM_Value))
		{
			finalValue = - value + TB6612 -> DeadZone;
		}else{
			finalValue = TB6612 -> MaxPWM_Value;
		}
	}

	switch(TB6612 -> PWMB_Channel)
	{
	case LL_TIM_CHANNEL_CH1:
		LL_TIM_OC_SetCompareCH1(TB6612 -> TimPort, finalValue);
		break;
	case LL_TIM_CHANNEL_CH2:
		LL_TIM_OC_SetCompareCH2(TB6612 -> TimPort, finalValue);
		break;
	case LL_TIM_CHANNEL_CH3:
		LL_TIM_OC_SetCompareCH3(TB6612 -> TimPort, finalValue);
		break;
	case LL_TIM_CHANNEL_CH4:
		LL_TIM_OC_SetCompareCH4(TB6612 -> TimPort, finalValue);
		break;
	default:
		break;
	}
	return;
}

void TB6612Brake(TB6612_t *TB6612)
{
	LL_GPIO_SetOutputPin(TB6612 -> BIN1Port, TB6612 -> BIN1Pin);
	LL_GPIO_SetOutputPin(TB6612 -> BIN2Port, TB6612 -> BIN2Pin);
}
