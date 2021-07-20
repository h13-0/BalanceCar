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
extern PositionPID_t SpeedPID;

void PIDAdjust(uint8_t *data, uint8_t len)
{
	MatchKeyFloat(data, len, "AP:", 3, AnglePID.proportion);
	MatchKeyFloat(data, len, "AI:", 3, AnglePID.integration);
	MatchKeyFloat(data, len, "AD:", 3, AnglePID.differention);
	MatchKeyFloat(data, len, "AT:", 3, AnglePID.setpoint);
	MatchKeyFloat(data, len, "AMI:", 4, AnglePID.maximumAbsValueOfIntegrationOutput);

	MatchKeyFloat(data, len, "SP:", 3, SpeedPID.proportion);
	MatchKeyFloat(data, len, "SI:", 3, SpeedPID.integration);
	MatchKeyFloat(data, len, "SD:", 3, SpeedPID.differention);
	MatchKeyFloat(data, len, "SMI:", 4, SpeedPID.maximumAbsValueOfIntegrationOutput);
}

#endif
