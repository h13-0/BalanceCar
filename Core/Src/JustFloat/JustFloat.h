#ifndef _JUSTFLOAT_H_
#define _JUSTFLOAT_H_

#include <stdint.h>

#ifdef STM32F407xx
#include "stm32f4xx_ll_usart.h"
#endif

#if defined(STM32F103xB) || defined(STM32F103xC) || defined(STM32F103xD) || defined(STM32F103xE)
#include "stm32f1xx_ll_usart.h"
#endif

void SetJustFloatPort(USART_TypeDef *USARTx);

/**
 * @brief: Send one frame to VOFA+
 */
void SendJustFloatFrame(float data[], uint8_t len);

#endif
