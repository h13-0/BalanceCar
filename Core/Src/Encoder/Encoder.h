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
 * @brief: Typedef struct for single phase encoder.
 * @note:
 * 		Just a variable that stores disk data without manual assignment.
 * 		When defining, manually define it as 0.
 * 			Such as:
 * 				SinglePhaseEncoder_t encoder = { 0 };
 */
typedef struct
{
	Time_t         LastUpdateTime;
	uint16_t       LatestTriggerTimes;
	uint16_t       TemporaryTriggerTimes;
} SinglePhaseEncoder_t;

/**
 * @brief:  Gets the current disk speed.
 * @param:
 * 		SinglePhaseEncoder_t *Encoder
 * @return:
 * 		Trigger speed per millisecond.
 */
float GetSinglePhaseEncoderSpeed(SinglePhaseEncoder_t *Encoder);

/**
 * @brief: External interrupt to code disk.
 * @param: SinglePhaseEncoder_t *Encoder.
 */
void SinglePhaseEncoder_TriggerHandle(SinglePhaseEncoder_t *Encoder);

/**
 * @brief: Typedef struct for double phase encoder.
 * @note:
 * 		Just a variable that stores disk data without manual assignment.
 * 		When defining, manually define it as 0.
 * 			Such as:
 * 				DoublePhaseEncoder_t encoder = { 0 };
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
} DoublePhaseEncoder_t;

/**
 * @brief:  Gets the current disk speed.
 * @param:
 * 		DoublePhaseEncoder_t *Encoder
 * @return:
 * 		Trigger speed per millisecond.
 */
float GetDoublePhaseEncoderSpeed(DoublePhaseEncoder_t *Encoder);

/**
 * @brief: External interrupt to code disk.
 * @param: DoublePhaseEncoder_t *Encoder.
 */
void DoublePhaseEncoderChannel1_TriggerHandle(DoublePhaseEncoder_t *Encoder);

void DoublePhaseEncoderChannel2_TriggerHandle(DoublePhaseEncoder_t *Encoder);

#endif /* SRC_ENCODER_ENCODER_H_ */
