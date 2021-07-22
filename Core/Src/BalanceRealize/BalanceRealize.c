/*
 * BalanceRealize.c
 *
 *  Created on: 2021Äê7ÔÂ20ÈÕ
 *      Author: h13
 */
#include "BalanceRealize.h"

#include "PIDParallelRealize.h"

static CarStatus_t carStatus = Balanceable;
static float pitch = 0, yaw = 0;
static short gy = 0;

static const float balanceAngle = -2.3;

void BalanceMethodInit(void)
{
#ifdef PIDParallel
	PID_Init();
#endif
}

__attribute__((always_inline)) inline CarStatus_t GetCarStatus(void)
{
	return carStatus;
}

__attribute__((always_inline)) inline float GetCarBalanceAngle(void)
{
	return balanceAngle;
}

void BalanceStatusMonitor(void)
{
#ifdef PIDParallel
	BalanceStatusMonitorHandler(&pitch, &yaw, &gy);
#endif
}

void MPU6050_InterruptHandler(void)
{
#ifdef PIDParallel
	PID_Handler();
#endif
}
