/*
 * App.c
 *
 *  Created on: 2021年6月25日
 *      Author: h13
 */
#include "App.h"

#include "stm32f1xx.h"

#include "TB6612.h"

#include "inv_mpu.h"

#include "SerialPrintf.h"

#include "Clock.h"

int App(void)

{
	ClockInit();

	TB6612_t motor;

	motor.TimPort = TIM4;
	motor.PWMA_Channel = LL_TIM_CHANNEL_CH1;
	motor.PWMB_Channel = LL_TIM_CHANNEL_CH2;

	motor.AIN1Port = GPIOB;
	motor.AIN1Pin  = LL_GPIO_PIN_15;

	motor.AIN2Port = GPIOB;
	motor.AIN2Pin  = LL_GPIO_PIN_14;

	motor.BIN1Port = GPIOB;
	motor.BIN1Pin  = LL_GPIO_PIN_13;

	motor.BIN2Port = GPIOB;
	motor.BIN2Pin  = LL_GPIO_PIN_12;

	motor.DeadZone = 0;
	motor.MaxPWM_Value = 1000;

	TB6612Init(&motor);

	TB6612SetPWMA_Value(&motor, 500);

	SetSerialPrintfTarget(USART2);

	while(1)
	{
		LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
		SleepMicrosecond(1);
		LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
		SleepMicrosecond(2);
		LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
		SleepMicrosecond(3);
		LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
		SleepMicrosecond(4);
		LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
		SleepMicrosecond(5);
		LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
		SleepMicrosecond(6);
	}


	return 0;
}
