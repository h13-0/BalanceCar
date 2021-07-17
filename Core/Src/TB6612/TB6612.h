/*
 * TB6612.h
 *
 *  Created on: 2021年6月26日
 *      Author: h13
 */

#ifndef SRC_TB6612_TB6612_H_
#define SRC_TB6612_TB6612_H_

#include <stdint.h>

#if defined(STM32F103xB) || defined(STM32F103xC) || defined(STM32F103xD) || defined(STM32F103xE)
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#endif

typedef struct
{
	/***PWM Configs***/
	TIM_TypeDef *TimPort;
	uint32_t PWMA_Channel;
	uint32_t PWMB_Channel;

	/***GPIO Configs***/
	GPIO_TypeDef *AIN1Port;
	uint32_t AIN1Pin;
	GPIO_TypeDef *AIN2Port;
	uint32_t AIN2Pin;
	GPIO_TypeDef *BIN1Port;
	uint32_t BIN1Pin;
	GPIO_TypeDef *BIN2Port;
	uint32_t BIN2Pin;

	/***Motor Configs***/
	uint16_t MaxPWM_Value;
	uint16_t DeadZone;
} TB6612_t;

void TB6612Init(TB6612_t *TB6612);

void TB6612SetPWMA_Value(TB6612_t *TB6612, int16_t value);

void TB6612SetPWMB_Value(TB6612_t *TB6612, int16_t value);

void TB6612Brake(TB6612_t *TB6612);

#endif /* SRC_TB6612_TB6612_H_ */
