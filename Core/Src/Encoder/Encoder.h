/*
 * Encoder.h
 *
 *  Created on: 2021Äê7ÔÂ18ÈÕ
 *      Author: h13
 */

#ifndef SRC_ENCODER_ENCODER_H_
#define SRC_ENCODER_ENCODER_H_

#include "Clock.h"

/**
 * @group: Platform APIs.
 */
#define Time_t mtime_t
#define GetUS  GetCurrentTimeMicrosecond

/**
 * Just Symbol.
 */
typedef enum
{
	Negative = 0,
	Positive = 1,
} Symbol_t;

/**
 * @brief: Symbol Status.
 */
typedef struct
{
	Symbol_t Symbol    : 1;
	uint8_t StableTime : 7;
} SymbolStatus_t;

/**
 * @brief: Typedef struct for Bipolar encoder.
 */
typedef struct
{
	Time_t         LatestChannel1_TriggerTime;
	Time_t         LatestChannel2_TriggerTime;
	Time_t         C1C2_TriggerTimeGap;
	Time_t         C2C1_TriggerTimeGap;
	Time_t         LastUpdateTime;
	uint16_t       LatestTriggerTimes;
	uint16_t       TemporaryTriggerTimes;
	SymbolStatus_t SymbolStatus;
} BipolarEncoder_t;

float GetBipolarEncoderSpeed(BipolarEncoder_t *encoder);

void BipolarEncoderChannel1_TriggerHandle(BipolarEncoder_t *encoder);

void BipolarEncoderChannel2_TriggerHandle(BipolarEncoder_t *encoder);

#endif /* SRC_ENCODER_ENCODER_H_ */
