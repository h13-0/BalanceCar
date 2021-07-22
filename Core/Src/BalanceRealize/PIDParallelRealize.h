/*
 * PIDRealize.h
 *
 *  Created on: 2021,7,2,
 *      Author: h13
 */

#ifndef SRC_BALANCEREALIZE_PIDPARALLELREALIZE_H_
#define SRC_BALANCEREALIZE_PIDPARALLELREALIZE_H_

void PID_Init(void);

void PID_Handler(void);

void BalanceStatusMonitorHandler(float *Pitch, short *Ay);

#endif /* SRC_BALANCEREALIZE_PIDPARALLELREALIZE_H_ */
