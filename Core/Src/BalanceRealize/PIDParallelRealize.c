
/*
 * PIDRealize.c
 *
 *  Created on: 2021,7,2
 *      Author: h13
 */
#ifdef PIDParallel

#include "PIDParallelRealize.h"
#include <stdlib.h>
#include "BalanceRealize.h"
#include "PID.h"
#include "inv_mpu.h"
#include "JustFloat.h"
#include "MotorControl.h"
#include "Clock.h"
#include "Encoder.h"
#include "Filter.h"

#ifdef DEBUG
PositionPID_t AnglePID;
PositionPID_t SpeedPID;
#define anglePID AnglePID
#define speedPID SpeedPID
#else
static PositionPID_t anglePID;
static PositionPID_t speedPID;
#endif

DoublePhaseEncoder_t Encoder = { 0 };

static float pitch, roll, yaw;
static short gx, gy, gz;
static float anglePID_Out;
static float speedPID_Out;
static uint8_t flag = 0;
static float speed = 0;

void PID_Init(void)
{
	anglePID.proportion = -48.0;
	anglePID.integration = -1.83;
	anglePID.differention = 0.05;

	anglePID.setpoint = GetCarBalanceAngle();

	anglePID.configs.autoResetIntegration = disable;
	anglePID.configs.limitIntegration = enable;

	anglePID.maximumAbsValueOfIntegrationOutput = 500.0;
	anglePID.maxAbsOutput = 725.0;

	speedPID.proportion = -1.16;
	speedPID.integration = -0.058;
	speedPID.differention = 2.26;

	speedPID.setpoint = 0.0;

	speedPID.configs.autoResetIntegration = disable;
	speedPID.configs.limitIntegration = enable;

	speedPID.maximumAbsValueOfIntegrationOutput = 500.0;
	speedPID.maxAbsOutput = 725.0;
}

void updatePID_Flag(void)
{
	flag = 1;
}

void waitPID_Flag(void)
{
	while(!flag);
	flag = 0;
}

void PID_Handler(void)
{
	MPU_DMP_GetEularAngle(&pitch, &roll, &yaw);  //pitch

	MPU_GetGyroscope(&gx, &gy, &gz);   		     //gy

	if(GetCarStatus() == Balanceable)
	{
		static LowPassFilter_t filter = {0, 0.25};

		speed = LowPassFilterCalc(&filter, GetDoublePhaseEncoderSpeed(&Encoder));

		speedPID_Out = PosPID_Calc(&speedPID, speed * 100.0);

		anglePID_Out = PosPID_CalcWithCustDiff(&anglePID, pitch, gy);

		SetLeftMotorPWM_Value(anglePID_Out + speedPID_Out);
		SetRightMotorPWM_Value(anglePID_Out + speedPID_Out);
	} else {
		SetLeftMotorPWM_Value(0);
		SetRightMotorPWM_Value(0);
	}

	updatePID_Flag();
}

void BalanceStatusMonitorHandler(float *Pitch, float *Yaw, short *Gy)
{
	waitPID_Flag();
	*Pitch = pitch;
	*Yaw = yaw;
	*Gy = gy;
	float data[] = {pitch, anglePID.setpoint, speed, speedPID.proportion, anglePID_Out + speedPID_Out};
	SendJustFloatFrame(data, 5);
}

#endif
