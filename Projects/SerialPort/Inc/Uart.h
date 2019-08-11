/*
 * Uart.h
 * Author: 20006401
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stdio.h"

class Uart {
public:
	Uart();
	bool Inialize(void);
	bool Transmit(uint8_t * buffer);
private:
	USART_TypeDef * m_uartinstance;
	//Temporaty to initialize using HAL we will get rid of it by using CMSIS API
	//
	UART_HandleTypeDef UartHandle;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_UART_H_ */
