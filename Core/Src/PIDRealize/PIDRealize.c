/*
 * PIDRealize.c
 *
 *  Created on: 2021,7,2
 *      Author: h13
 */
#include "PIDRealize.h"
#include "PID.h"
#include "inv_mpu.h"
#include "JustFloat.h"
#include "MotorControl.h"
#include "Clock.h"

#ifdef DEBUG
PositionPID_t AnglePID;
#define anglePID AnglePID
#elif
static PositionPID_t anglePID;
#endif

static float pitch, roll, yaw;
static short gx, gy, gz;
static float anglePID_Out;
static uint8_t flag = 0;

void PID_Init(void)
{
	anglePID.proportion = 0.0;
	anglePID.integration = 0.0;
	anglePID.differention = 0.0;

	anglePID.setpoint = -3.5;//-2.3;

	anglePID.configs.autoResetIntegration = enable;
	anglePID.configs.limitIntegration = enable;

	anglePID.maximumAbsValueOfIntegrationOutput = 500.0;
	anglePID.maxAbsOutput = 1000.0;
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

void PIDHandler(void)
{
	MPU_DMP_GetEularAngle(&pitch, &roll, &yaw);  //pitch

	MPU_GetGyroscope(&gx, &gy, &gz);   		     //gy

	anglePID_Out = PosPID_CalcWithCustDiff(&anglePID, pitch, gy);

	SetLeftMotorPWM_Value(anglePID_Out);
	SetRightMotorPWM_Value(anglePID_Out);
	updatePID_Flag();
}

void ReportPID_Status(void)
{
	waitPID_Flag();
	float data[] = {pitch, anglePID._sumError, anglePID.setpoint};
	SendJustFloatFrame(data, 3);
}
