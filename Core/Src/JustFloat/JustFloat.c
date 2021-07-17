#include "JustFloat.h"

static USART_TypeDef *port = USART1;

void SetJustFloatPort(USART_TypeDef *USARTx)
{
	port = USARTx;
}

void SendJustFloatFrame(float data[], uint8_t len) {
	uint8_t *hexPtr = (uint8_t*) data;
	for (uint8_t index = 0; index < len * 4; index++) {
		while (LL_USART_IsActiveFlag_TC(port) == RESET);
		LL_USART_TransmitData8(port, *hexPtr);
		hexPtr++;
	}

	while (LL_USART_IsActiveFlag_TC(port) == RESET);
	LL_USART_TransmitData8(port, 0x00);

	while (LL_USART_IsActiveFlag_TC(port) == RESET);
	LL_USART_TransmitData8(port, 0x00);

	while (LL_USART_IsActiveFlag_TC(port) == RESET);
	LL_USART_TransmitData8(port, 0x80);

	while (LL_USART_IsActiveFlag_TC(port) == RESET);
	LL_USART_TransmitData8(port, 0x7f);
}
