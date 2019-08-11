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

	  /* Disable USART prior modifying configuration registers */
	  /* Note: Commented as corresponding to Reset value */
	  // LL_USART_Disable(USARTx_INSTANCE);

	  /* TX/RX direction */
	  LL_USART_SetTransferDirection(USARTx_INSTANCE, LL_USART_DIRECTION_TX_RX);

	  /* 8 data bit, 1 start bit, 1 stop bit, no parity */
	  LL_USART_ConfigCharacter(USARTx_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

	  /* No Hardware Flow control */
	  /* Reset value is LL_USART_HWCONTROL_NONE */
	  // LL_USART_SetHWFlowCtrl(USARTx_INSTANCE, LL_USART_HWCONTROL_NONE);

	  /* Oversampling by 16 */
	  /* Reset value is LL_USART_OVERSAMPLING_16 */
	  // LL_USART_SetOverSampling(USARTx_INSTANCE, LL_USART_OVERSAMPLING_16);

	  /* Set Baudrate to 115200 using APB frequency set to 216000000/APB_Div Hz */
	  /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
	  /* Ex :
	      Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance

	      In this example, Peripheral Clock is expected to be equal to 216000000/APB_Div Hz => equal to SystemCoreClock/APB_Div
	  */
	  LL_USART_SetBaudRate(USARTx_INSTANCE, SystemCoreClock/APB_Div, LL_USART_OVERSAMPLING_16, 115200);

	  /* (4) Enable USART *********************************************************/
	  LL_USART_Enable(USARTx_INSTANCE);

	 return bretVal;
}

bool Uart::Transmit(uint8_t * buffer) {

	bool bretVal = true;
	 LL_USART_TransmitData8(this->m_uartinstance, buffer[0]);

	  return bretVal;
}
