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

__attribute__((always_inline)) inline float GetBipolarEncoderSpeed(BipolarEncoder_t *encoder)
{
	Time_t timeDifference = GetUS() - encoder -> LastUpdateTime;
	if(encoder -> SymbolStatus.Symbol == Positive)
	{
		if(timeDifference < _minimumUpdateInterval * 3)
		{
			return ((1000.0 * (encoder -> LatestTriggerTimes + encoder -> TemporaryTriggerTimes)) / (_minimumUpdateInterval + timeDifference));
		} else {
			return 1000.0 / (timeDifference);
		}
	} else {
		if(timeDifference < _minimumUpdateInterval * 3)
		{
			return ((-1000.0 * (encoder -> LatestTriggerTimes + encoder -> TemporaryTriggerTimes)) / (_minimumUpdateInterval + timeDifference));
		} else {
			return - 1000.0 / (timeDifference);
		}
	}
}

__attribute__((always_inline)) inline void BipolarEncoderChannel1_TriggerHandle(BipolarEncoder_t *encoder)
{
	encoder -> LatestChannel1_TriggerTime = GetUS();
	encoder -> TemporaryTriggerTimes ++;
	encoder -> C1C2_TriggerTimeGap = encoder -> LatestChannel1_TriggerTime - encoder -> LatestChannel2_TriggerTime;

	if(encoder -> LatestChannel1_TriggerTime - encoder -> LastUpdateTime > _minimumUpdateInterval)
	{
		encoder -> LastUpdateTime = encoder -> LatestChannel1_TriggerTime;
		encoder -> LatestTriggerTimes = encoder -> TemporaryTriggerTimes;
		encoder -> TemporaryTriggerTimes = 0;
	}
}

__attribute__((always_inline)) inline void BipolarEncoderChannel2_TriggerHandle(BipolarEncoder_t *encoder)
{
	encoder -> LatestChannel2_TriggerTime = GetUS();
	encoder -> C2C1_TriggerTimeGap = encoder -> LatestChannel2_TriggerTime - encoder -> LatestChannel1_TriggerTime;

	if(encoder -> C1C2_TriggerTimeGap > encoder -> C2C1_TriggerTimeGap)
	{
		if(encoder -> SymbolStatus.Symbol == Positive)
		{
			encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
		} else {
			if(encoder -> SymbolStatus.StableTime > 0)
			{
				encoder -> SymbolStatus.StableTime --;
			} else {
				encoder -> SymbolStatus.Symbol = Positive;
				encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
			}
		}
	} else {
		if(encoder -> SymbolStatus.Symbol == Negative)
		{
			encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
		} else {
			if(encoder -> SymbolStatus.StableTime > 0)
			{
				encoder -> SymbolStatus.StableTime --;
			} else {
				encoder -> SymbolStatus.Symbol = Negative;
				encoder -> SymbolStatus.StableTime = _symbolStableThreshold;
			}
		}
	}
}
