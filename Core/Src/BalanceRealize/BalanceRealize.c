/*
 * BalanceRealize.c
 *
 *  Created on: 2021Äê7ÔÂ20ÈÕ
 *      Author: h13
 */
#include "BalanceRealize.h"
#include <stdlib.h>
#include "PIDParallelRealize.h"

#include "JustFloat.h"

static CarStatus_t carStatus = Balanceable;
static float pitch = 0;
static short az = 0;

static const float balanceAngle = -2.3;



/**
 * @group: Out of balance detection configs.
 * @param:
 */
static const float balanceAngleLimit = 30.0;
static const uint8_t outOfBalanceTimesLimit = 3;

/**
 * @group: Filed detection configs.
 * @param:
 * 		errorRangeOfAz:
 *
 */
static const short standardAccZ = 17200;
static const short errorRangeOfAz = 7800;
static const float filedLimitOfSumAz = 42000;

/**
 * @group: Rebalance detection configs.
 */
static const float rebalanceAngleLimit = 5.0;
static const uint16_t stableLimit = 300;


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

static void filedDetection(void)
{
	static float sumAz = 0;
	if(abs(az - standardAccZ) > errorRangeOfAz)
	{
		if(az > standardAccZ)
		{
			if(sumAz >= 0)
			{
				sumAz += az - standardAccZ;
				if(abs(sumAz) > filedLimitOfSumAz)
				{
					carStatus = Filed;
				}
			} else {
				sumAz = 0;
			}
		} else {
			if(sumAz <= 0)
			{
				sumAz += az - standardAccZ;
				if(abs(sumAz) > filedLimitOfSumAz)
				{
					carStatus = Filed;
				}
			} else {
				sumAz = 0;
			}
		}
	} else {
		sumAz = 0;
	}
}

static void outOfBalanceDetection(void)
{
	static uint8_t outOfBalanceTimes = 0;
	if(abs(pitch - balanceAngle) > balanceAngleLimit)
	{
		outOfBalanceTimes ++;
		if(outOfBalanceTimes >= outOfBalanceTimesLimit)
		{
			carStatus = OutOfBalance;
			outOfBalanceTimes = 0;
		}
	} else {
		outOfBalanceTimes = 0;
	}
}

static void rebalanceDetection(void)
{
	static uint16_t stableTimes = 0;
	if((abs(pitch - balanceAngle) < rebalanceAngleLimit) && (abs(az - standardAccZ) < errorRangeOfAz))
	{
		stableTimes ++;
		if(stableTimes > stableLimit)
		{
			carStatus = Balanceable;
			stableTimes = 0;
		}
	}
}

void BalanceStatusMonitor(void)
{
#ifdef PIDParallel
	BalanceStatusMonitorHandler(&pitch, &az);  //32767?
#endif
	switch(carStatus)
	{
	case Balanceable:
		outOfBalanceDetection();
		filedDetection();
		break;

	case Filed:
		rebalanceDetection();
		break;

	case OutOfBalance:
		rebalanceDetection();
		break;

	default:
		break;
	}
}

void MPU6050_InterruptHandler(void)
{
#ifdef PIDParallel
	PID_Handler();
#endif
}
