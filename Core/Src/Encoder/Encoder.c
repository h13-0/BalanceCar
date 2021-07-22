/*
 * Encoder.c
 *
 *  Created on: 2021Äê7ÔÂ18ÈÕ
 *      Author: h13
 */

#include "Encoder.h"

#include <stdint.h>
#include "Clock.h"

/**
 * @group: Configs.
 * @param:
 * 		_minimumUpdateInterval:
 * 			The slowest update interval in microsecond.
 * 			When the code disk interrupt time interval is greater than this value, the counting mode will be switched.
 * 			This parameter is independent of the actual data output frequency.
 * 			The actual output frequency is 1MHz.
 * 			The accuracy of velocity measurement depends on the accuracy of clock.
 *
 * 		_symbolStableThreshold:
 * 			The lowest threshold for changing symbols.
 * 			Due to the timing error of AB phase code panel, symbol judgment is jitter, so the filtering method is _symbolStableThreshold times in a row when the same symbol is changed.
 */
#define _minimumUpdateInterval (10000)
#define _symbolStableThreshold (5)

/**
 * @brief:  Gets the current disk speed.
 * @param:
 * 		SinglePhaseEncoder_t *Encoder
 * @return:
 * 		Trigger speed per millisecond.
 */
__attribute__((always_inline)) inline float GetSinglePhaseEncoderSpeed(SinglePhaseEncoder_t *Encoder)
{
	Time_t timeDifference = GetUS() - Encoder -> LastUpdateTime;
	if(timeDifference < _minimumUpdateInterval * 3)
	{
		return ((1000.0 * (Encoder -> LatestTriggerTimes + Encoder -> TemporaryTriggerTimes)) / (_minimumUpdateInterval + timeDifference));
	} else {
		return 1000.0 / (timeDifference);
	}
}

/**
 * @brief: External interrupt to code disk.
 * @param: SinglePhaseEncoder_t *Encoder.
 */
__attribute__((always_inline)) inline void SinglePhaseEncoder_TriggerHandle(SinglePhaseEncoder_t *Encoder)
{
	Time_t timeDifference = GetUS() - Encoder -> LastUpdateTime;
	Encoder -> TemporaryTriggerTimes ++;
	if(timeDifference - Encoder -> LastUpdateTime > _minimumUpdateInterval)
	{
		Encoder -> LastUpdateTime = timeDifference;
		Encoder -> LatestTriggerTimes = Encoder -> TemporaryTriggerTimes;
		Encoder -> TemporaryTriggerTimes = 0;
	}
}

/**
 * @brief:  Gets the current disk speed.
 * @param:
 * 		DoublePhaseEncoder_t *Encoder
 * @return:
 * 		Trigger speed per millisecond.
 */
__attribute__((always_inline)) inline float GetDoublePhaseEncoderSpeed(DoublePhaseEncoder_t *Encoder)
{
	Time_t timeDifference = GetUS() - Encoder -> LastUpdateTime;
	if(Encoder -> SymbolStatus.Symbol == Positive)
	{
		if(timeDifference < _minimumUpdateInterval * 3)
		{
			return ((1000.0 * (Encoder -> LatestTriggerTimes + Encoder -> TemporaryTriggerTimes)) / (_minimumUpdateInterval + timeDifference));
		} else {
			return 1000.0 / (timeDifference);
		}
	} else {
		if(timeDifference < _minimumUpdateInterval * 3)
		{
			return ((-1000.0 * (Encoder -> LatestTriggerTimes + Encoder -> TemporaryTriggerTimes)) / (_minimumUpdateInterval + timeDifference));
		} else {
			return - 1000.0 / (timeDifference);
		}
	}
}

/**
 * @brief: External interrupt to code disk.
 * @param: DoublePhaseEncoder_t *Encoder.
 */
__attribute__((always_inline)) inline void DoublePhaseEncoderChannel1_TriggerHandle(DoublePhaseEncoder_t *Encoder)
{
	Encoder -> LatestChannel1_TriggerTime = GetUS();
	Encoder -> TemporaryTriggerTimes ++;
	Encoder -> C1C2_TriggerTimeGap = Encoder -> LatestChannel1_TriggerTime - Encoder -> LatestChannel2_TriggerTime;

	if(Encoder -> LatestChannel1_TriggerTime - Encoder -> LastUpdateTime > _minimumUpdateInterval)
	{
		Encoder -> LastUpdateTime = Encoder -> LatestChannel1_TriggerTime;
		Encoder -> LatestTriggerTimes = Encoder -> TemporaryTriggerTimes;
		Encoder -> TemporaryTriggerTimes = 0;
	}
}

__attribute__((always_inline)) inline void DoublePhaseEncoderChannel2_TriggerHandle(DoublePhaseEncoder_t *Encoder)
{
	Encoder -> LatestChannel2_TriggerTime = GetUS();
	Encoder -> C2C1_TriggerTimeGap = Encoder -> LatestChannel2_TriggerTime - Encoder -> LatestChannel1_TriggerTime;

	if(Encoder -> C1C2_TriggerTimeGap > Encoder -> C2C1_TriggerTimeGap)
	{
		if(Encoder -> SymbolStatus.Symbol == Positive)
		{
			Encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
		} else {
			if(Encoder -> SymbolStatus.StableTime > 0)
			{
				Encoder -> SymbolStatus.StableTime --;
			} else {
				Encoder -> SymbolStatus.Symbol = Positive;
				Encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
			}
		}
	} else {
		if(Encoder -> SymbolStatus.Symbol == Negative)
		{
			Encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
		} else {
			if(Encoder -> SymbolStatus.StableTime > 0)
			{
				Encoder -> SymbolStatus.StableTime --;
			} else {
				Encoder -> SymbolStatus.Symbol = Negative;
				Encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
			}
		}
	}
}
