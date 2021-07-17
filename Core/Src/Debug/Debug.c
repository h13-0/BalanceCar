/*
 * Debug.c
 *
 *  Created on: 2021, 7, 12
 *      Author: h13
 */

#ifdef DEBUG
#include "Debug.h"
#include <stdint.h>

#include "SimpleProtocolPraise.h"
#include "PIDAdjust.h"

/**
 * @brief: Debug handler.
 * @param: Debug Port raw data.
 */
__attribute__((always_inline)) inline void DebugHandler(uint8_t data)
{
	static uint8_t buffer[32] = { '\0' };
	static uint8_t len = 0;
	GeneratePraiseWithSuffixMethod(data, "\r\n", 2, buffer, 32, len, PIDAdjust(buffer, len - 2));
}

#endif
