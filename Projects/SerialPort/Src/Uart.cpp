/*
 * UART.cpp
 * Author: 20006401
 */

#include "Uart.h"


Uart::Uart() : m_uartinstance(USART3)
{
}

bool Uart::Inialize(void) {
	bool bretVal = true;

	UartHandle.Instance = this->m_uartinstance;

	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    /* Initialization Error */
		  bretVal = false;
	  }

	 return bretVal;
}

bool Uart::Transmit(uint8_t * buffer) {

	bool bretVal = true;
	  HAL_UART_Transmit(&UartHandle, buffer, 1, 0xFFFF);

	  return bretVal;
}
