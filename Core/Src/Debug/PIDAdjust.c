/*
 * PIDAdjust.c
 *
 *  Created on: 2021, 6, 30.
 *      Author: h13
 */
#ifdef DEBUG

#include "PIDAdjust.h"
#include "FastMatch.h"
#include "PID.h"

extern PositionPID_t AnglePID;

void PIDAdjust(uint8_t *data, uint8_t len)
{
	MatchKeyFloat(data, len, "AP:", 3, AnglePID.proportion);
	MatchKeyFloat(data, len, "AI:", 3, AnglePID.integration);
	MatchKeyFloat(data, len, "AD:", 3, AnglePID.differention);
	MatchKeyFloat(data, len, "AT:", 3, AnglePID.setpoint);
	MatchKeyFloat(data, len, "AMI:", 4, AnglePID.maximumAbsValueOfIntegrationOutput);
}

#endif
