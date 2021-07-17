/*
 * MotionControl.h
 *
 *  Created on: 2021年7月6日
 *      Author: h13
 */

#ifndef SRC_MOTORCONTROL_MOTORCONTROL_H_
#define SRC_MOTORCONTROL_MOTORCONTROL_H_

#include <stdint.h>

void MotorInit(void);

void SetLeftMotorPWM_Value(int16_t value);

void SetRightMotorPWM_Value(int16_t value);

#endif /* SRC_MOTORCONTROL_MOTORCONTROL_H_ */
