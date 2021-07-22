/*
 * BalanceRealize.c
 *
 *  Created on: 2021Äê7ÔÂ20ÈÕ
 *      Author: h13
 */
#include "BalanceRealize.h"
#include <stdlib.h>
#include <stdint.h>

#if defined(PIDParallel)
#include "PIDParallelRealize.h"
#elif defined(PIDCascade)
#include "PIDCascadeRealize.h"
#else
#error "Please set the balancing implementation mode."
#endif

/**
 * @brief: Vehicle mechanical balance Angle.
 */
static const float balanceAngle = -2.3;

/**
 * @group: Functions management.
 */
#define Enable   1
#define Disabble 0
#define OutOfBalanceDetection Enable

#if(OutOfBalanceDetection == Enable)
/**
 * @group: Out of balance detection configs.
 * @param:
 */
static const float balanceAngleLimit = 30.0;
static const uint8_t outOfBalanceTimesLimit = 3;
#endif

/**
 * @group: Filed detection configs.
 * @param:
 * 		standardAccZ:      The standard acceleration of the car on the z-axis at the balance angle.
 * 		errorRangeOfAz:    Z-axis acceleration error interval of the trolley during attitude adjustment.
 *		filedLimitOfSumAz: The judgment threshold of "Filed" and "BalanceAble".
 */
static const short standardAccZ = 17200;
static const short errorRangeOfAz = 7800;
static const float filedLimitOfSumAz = 42000;

/**
 * @group: Rebalance detection configs.
 * @param:
 * 		rebalanceAngleLimit: The Angle floating range when the car returns from others states to the "BalanceAble" state.
 * 		stableLimit:         The limit of times of the car satisfies the rebalance conditions.
 */
static const float rebalanceAngleLimit = 5.0;
static const uint16_t stableLimit = 300;

static CarStatus_t carStatus = Balanceable;
static float pitch = 0;
static short az = 0;

void BalanceMethodInit(void)
{
#if defined(PIDParallel) || defined(PIDCascade)
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

#if(OutOfBalanceDetection == Enable)
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
#endif

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
	BalanceStatusMonitorHandler(&pitch, &az);
	switch(carStatus)
	{
	case Balanceable:
#if(OutOfBalanceDetection == Enable)
		outOfBalanceDetection();
#endif
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
#if defined(PIDParallel) || defined(PIDCascade)
	PID_Handler();
#endif
}
