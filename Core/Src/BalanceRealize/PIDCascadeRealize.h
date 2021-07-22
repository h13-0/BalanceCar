/*
 * PIDCascadeRealize.h
 *
 *  Created on: 2021��7��22��
 *      Author: h13
 */
#ifdef PIDCascade

#ifndef SRC_BALANCEREALIZE_PIDCASCADEREALIZE_H_
#define SRC_BALANCEREALIZE_PIDCASCADEREALIZE_H_

void PID_Init(void);

void PID_Handler(void);

void BalanceStatusMonitorHandler(float *Pitch, short *Ay);

#endif /* SRC_BALANCEREALIZE_PIDCASCADEREALIZE_H_ */

#endif /* PIDCascade */
