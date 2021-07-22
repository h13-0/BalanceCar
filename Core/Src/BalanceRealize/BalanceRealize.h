/*
 * BalanceRealize.h
 *
 *  Created on: 2021Äê7ÔÂ20ÈÕ
 *      Author: h13
 */

#ifndef SRC_BALANCEREALIZE_BALANCEREALIZE_H_
#define SRC_BALANCEREALIZE_BALANCEREALIZE_H_

void BalanceMethodInit(void);

void BalanceStatusMonitor(void);

typedef enum
{
	Balanceable = 0,
	Filed = 1,
	OutOfBalance = 2,
} CarStatus_t;

CarStatus_t GetCarStatus(void);

float GetCarBalanceAngle(void);

void MPU6050_InterruptHandler(void);

#endif /* SRC_BALANCEREALIZE_BALANCEREALIZE_H_ */
