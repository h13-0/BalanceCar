/*
 * FastMatch.h
 *
 *  Created on: 2021Äê6ÔÂ11ÈÕ
 *      Author: h13
 */

#ifndef APP_FASTMATCH_FASTMATCH_H_
#define APP_FASTMATCH_FASTMATCH_H_
#include <String.h>
/**
 * @performance: The following performance results are the performance when Key values are matched.
 *
 * @group: Arm Cortex M3 (STM32F103), 72Mhz, Optimization: -O0.
 * @result:
 * 		Match Float:
 * 		| Time usage | Frequency |
 * 		| ---------- | --------- |
 * 		| 1.3032us   | 767.3Khz  |
 */

/**
 * @brief: Try to match key with string. If matched, it will run your code **and return**.
 * @param:
 * 		String:         Source String.
 * 		StringLength:   Length of String.
 * 		Key:            The String representation of Key.
 * 		KeyLength:      Length of Key.
 *
 * @example:
 * 		MatchKey(String, StringLength, "Enable Ble", 10, EnableBluetooth());
 *
 * 		MatchKey(String, StringLength, "Disable Ble", 11, EnableBluetooth());
 *
 * @equals:
 * 		if(StringLength == 10)
 * 		{
 * 			if(!memcmp(String, "Enable Ble", 10))
 * 			{
 * 				EnableBluetooth();
 * 				return;
 * 			}
 * 		}
 *
 * 		if(StringLength == 11)
 * 		{
 * 			if(!memcmp(String, "Disable Ble", 11))
 * 			{
 * 				EnableBluetooth();
 * 				return;
 * 			}
 * 		}
 *
 * @usage:
 * 		example:
 * 			When input params are:
 * 				String="Enable Ble"
 * 				StringLength=10
 * 			Then the following functions are executed:
 * 				EnableBluetooth();
 */
#define MatchKeyDo(String, StringLength, Key, KeyLength, Callback) \
			if(StringLength == KeyLength) \
			{ \
				if(!memcmp(String, Key, KeyLength)) \
				{ \
					Callback; \
					return; \
				} \
			}

/**
 * @brief: Generic implementation for passing nonstandard and standard variables, such as struct and Float.
 */
#define MatchKeyRaw(String, StringLength, Key, KeyLength, TargetVariable, TargetSize) \
			if(StringLength == KeyLength + TargetSize) \
			{ \
				if(!memcmp(String, Key, KeyLength)) \
				{ \
					String += KeyLength; \
					char *Target = (char *) &(TargetVariable); \
					memcpy(Target, String, TargetSize); \
					return; \
				} \
			}

/**
 * @brief: Try to match Key to Float. If matched, it will write data to your float variable **and return**.
 * @param:
 * 		String:         Source String.
 * 		StringLength:   Length of String.
 * 		Key:            The String representation of Key.
 * 		KeyLength:      Length of Key.
 * 		TargetVariable: The float Target variable.
 *
 * @usage:
 * 		if(length == 7)
 * 		{
 * 			MatchKeyValue(data, length, "AP:", 3, AnglePID.proportion);
 * 			MatchKeyValue(data, length, "TA:", 3, AnglePID.setpoint);
 * 		}
 *
 * @equals:
 * 		if(length == 7)
 * 		{
 * 			if (!memcmp(data, "AP:", 3))
 * 			{
 * 				data += 3;
 * 				char *Target = (char*) &(AnglePID.proportion);
 * 				memcpy(Target, data, 4);
 * 				return;
 * 			}
 *
 * 			if (!memcmp(data, "TA:", 3))
 *      	{
 *      		data += 3;
 *      		char *Target = (char*) &(AnglePID.setpoint);
 *      		memcpy(Target, data, 4);
 *      		return;
 *      	}
 *      }
 *
 * @note:
 * 		**The TargetVariable must be float!!!**
 * 		**To optimize efficiency, you must first manually check the String length!!!**
 *
 */

#define MatchKeyFloat(String, StringLength, Key, KeyLength, TargetFloat) MatchKeyRaw(String, StringLength, Key, KeyLength, TargetFloat, 4)

#define MatchKeyDouble(String, StringLength, Key, KeyLength, TargetDouble) MatchKeyRaw(String, StringLength, Key, KeyLength, TargetDouble, 8)

#define MatchKeyInt8_t(String, StringLength, Key, KeyLength, TargetInt8_t) MatchKeyRaw(String, StringLength, Key, KeyLength, TargetInt8_t, 1)

#define MatchKeyInt16_t(String, StringLength, Key, KeyLength, TargetInt16_t) MatchKeyRaw(String, StringLength, Key, KeyLength, TargetInt16_t, 2)

#define MatchKeyInt32_t(String, StringLength, Key, KeyLength, TargetInt32_t) MatchKeyRaw(String, StringLength, Key, KeyLength, TargetInt32_t, 3)

#define MatchKeyInt64_t(String, StringLength, Key, KeyLength, TargetInt64_t) MatchKeyRaw(String, StringLength, Key, KeyLength, TargetInt64_t, 4)

#define MatchKeyString(String, StringLength, Key, KeyLength, TargetString, TargetLength) \
			if(StringLength >= KeyLength) \
			{ \
				if(!memcmp(String, Key, KeyLength)) \
				{ \
					memset(TargetString, '0', TargetLength); \
					String += KeyLength; \
					StringLength -= KeyLength; \
					if(StringLength <= TargetLength) \
					{ \
						memcpy(TargetString, String, StringLength); \
					} else { \
						memcpy(TargetString, String, TargetLength); \
					} \
					return; \
				} \
			}


#endif /* APP_FASTMATCH_FASTMATCH_H_ */
