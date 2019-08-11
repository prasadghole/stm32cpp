/*
 * UART.cpp
 * Author: 20006401
 */

#include "Uart.h"

Uart::Uart() : m_uartinstance(USART3) , baudrate(115200), bits(8), parity(0), stopbit(1), flowcontrol(0)
{
}

bool Uart::Initialize()
{
	return this->Init(this->m_uartinstance,this->baudrate,this->bits,this->parity,this->stopbit,this->flowcontrol);
}

bool Uart::Init(USART_TypeDef * instance, uint32_t baudrate,uint32_t bits,uint32_t parity, uint32_t stopbit,uint32_t flowcontrol)
{
	bool bretVal = true;

	/* (1) Enable GPIO clock and configures the USART pins *********************/

	  /* Enable the peripheral clock of GPIO Port */
	  USARTx_GPIO_CLK_ENABLE();

	  /* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
	  LL_GPIO_SetPinMode(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_MODE_ALTERNATE);
	  USARTx_SET_TX_GPIO_AF();
	  LL_GPIO_SetPinSpeed(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	  LL_GPIO_SetPinOutputType(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	  LL_GPIO_SetPinPull(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_PULL_UP);

	  /* Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up */
	  LL_GPIO_SetPinMode(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_MODE_ALTERNATE);
	  USARTx_SET_RX_GPIO_AF();
	  LL_GPIO_SetPinSpeed(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	  LL_GPIO_SetPinOutputType(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	  LL_GPIO_SetPinPull(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_PULL_UP);

	  /* (2) Enable USART peripheral clock and clock source ***********************/
	  USARTx_CLK_ENABLE();

	  /* Set clock source */
	  USARTx_CLK_SOURCE();

	  /* (3) Configure USART functional parameters ********************************/

	  LL_USART_SetTransferDirection(instance, LL_USART_DIRECTION_TX_RX);

	  /* 8 data bit, 1 start bit, 1 stop bit, no parity */
	  LL_USART_ConfigCharacter(instance, LL_USART_DATAWIDTH_8B, parity, stopbit);

	  LL_USART_SetBaudRate(instance, SystemCoreClock/APB_Div, LL_USART_OVERSAMPLING_16, baudrate);

	  /* (4) Enable USART *********************************************************/
	  LL_USART_Enable(instance);

	 return bretVal;
}

bool Uart::Transmit(uint8_t * buffer) {

	bool bretVal = true;
	 LL_USART_TransmitData8(this->m_uartinstance, buffer[0]);

	  return bretVal;
}
