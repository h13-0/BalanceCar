/*
 * App.c
 *
 *  Created on: 2021,6,25
 *      Author: h13
 */
#include "App.h"

#include "stm32f1xx.h"

#include "MotorControl.h"
#include "inv_mpu.h"

#include "SerialPrintf.h"
#include "JustFloat.h"

#include "Clock.h"

#include "PIDRealize.h"

int App(void)

{
	ClockInit();

	MotorInit();

	SetSerialPrintfTarget(USART2);
	SetJustFloatPort(USART2);

	MPU_Error_t ret = MPU_DMP_Init(I2C2, 100);
	while(ret != MPU_OK)
	{
		printf("MPU Init error with code: %d\r\n", ret);
		SleepMillisecond(400);
		ret = MPU_DMP_Init(I2C2, 100);
	}

	PID_Init();
	set_int_enable(1);

	while(1)
	{
		ReportPID_Status();
		SleepMillisecond(1);
	}


	return 0;
}
