/*
 * PIDCascadeRealize.c
 *
 *  Created on: 2021��7��22��
 *      Author: h13
 */

#ifdef PIDCascade
#include "PIDCascadeRealize.h"
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

static uint8_t flag = 0;
static float speed = 0;

static float pitch = 0, roll = 0, yaw = 0;
static short gx = 0, gy = 0, gz = 0;
static short ax = 0, ay = 0, az = 0;

static float anglePID_Out = 0;
static float speedPID_Out = 0;

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

	speedPID.proportion = 0.08;
	speedPID.integration = 0.0004;
	speedPID.differention = 0.0;

	speedPID.setpoint = 0.0;

	speedPID.configs.autoResetIntegration = disable;
	speedPID.configs.limitIntegration = enable;

	speedPID.maximumAbsValueOfIntegrationOutput = 15.0;
	speedPID.maxAbsOutput = 20.0;
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

	MPU_GetAccelerometer(&ax, &ay, &az);

	if(GetCarStatus() == Balanceable)
	{
		static LowPassFilter_t filter = {0, 0.25};

		speed = LowPassFilterCalc(&filter, GetDoublePhaseEncoderSpeed(&Encoder));

		speedPID_Out = PosPID_Calc(&speedPID, speed * 100.0);

		anglePID.setpoint = GetCarBalanceAngle() + speedPID_Out;

		anglePID_Out = PosPID_CalcWithCustDiff(&anglePID, pitch, gy);

		SetLeftMotorPWM_Value(anglePID_Out);
		SetRightMotorPWM_Value(anglePID_Out);
	} else {
		anglePID._error = 0;
		anglePID._sumError = 0;
		speedPID._error = 0;
		speedPID._sumError = 0;
		SetLeftMotorPWM_Value(0);
		SetRightMotorPWM_Value(0);
	}

	updatePID_Flag();
}

void BalanceStatusMonitorHandler(float *Pitch, short *Az)
{
	waitPID_Flag();
	*Pitch = pitch;
	*Az = az;
	float data[] = {pitch, anglePID.setpoint, speed, az, anglePID_Out + speedPID_Out};
	SendJustFloatFrame(data, 5);
}


#endif /* PIDCascade */
