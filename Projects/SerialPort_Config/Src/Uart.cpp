/*
 * UART.cpp
 * Author: 20006401
 */

#include "Uart.h"

static stm32f767::UsartConfig UsartConfigurations[] = {
					stm32f767::UsartConfig(USART1,
							LL_RCC_USART1_CLKSOURCE_PCLK2,
							LL_APB2_GRP1_PERIPH_USART1 ,
							LL_AHB1_GRP1_PERIPH_GPIOA,
							GPIOA,
							LL_GPIO_PIN_9,
							GPIOA,
							LL_GPIO_PIN_10,
							2u
					),
					stm32f767::UsartConfig(USART3,
							LL_RCC_USART3_CLKSOURCE_PCLK1,
							LL_APB1_GRP1_PERIPH_USART3 ,
							LL_AHB1_GRP1_PERIPH_GPIOD,
							GPIOD,
							LL_GPIO_PIN_8,
							GPIOD,
							LL_GPIO_PIN_9,
							4u
					),
					};


stm32f767::Usart::Usart( UsartInstance instance, UsartSettings  settings): m_config(UsartConfigurations[instance]),m_settings(settings)
{
}

bool stm32f767::Usart::Initialize()
{
	return this->Init(this->m_config.m_instance,this->m_settings.m_baudrate,this->m_settings.m_bits,this->m_settings.m_parity,this->m_settings.m_stopbit,this->m_settings.m_flowcontrol);
}

bool stm32f767::Usart::Init(USART_TypeDef * instance, uint32_t baudrate,uint32_t bits,uint32_t parity, uint32_t stopbit,uint32_t flowcontrol)
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

bool stm32f767::Usart::Transmit(uint8_t * buffer) {

	bool bretVal = true;
	 LL_USART_TransmitData8(this->m_config.m_instance, buffer[0]);

	  return bretVal;
}
