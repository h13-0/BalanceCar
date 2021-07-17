/*
 * MotionControl.c
 *
 *  Created on: 2021年7月6日
 *      Author: h13
 */
#include "MotorControl.h"
#include "TB6612.h"
static TB6612_t motor;

void MotorInit(void)
{
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

	//TODO: brake;
}

void SetLeftMotorPWM_Value(int16_t value)
{
	TB6612SetPWMA_Value(&motor, - value);
}

void SetRightMotorPWM_Value(int16_t value)
{
	TB6612SetPWMB_Value(&motor, value);
}

