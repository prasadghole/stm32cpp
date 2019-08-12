/*
 * Uart.h
 * Author: 20006401
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_system.h"
#include "stm32f7xx_ll_utils.h"
#include "stm32f7xx_ll_cortex.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_exti.h"
#include "stm32f7xx_ll_usart.h"
#include "stm32f7xx_ll_pwr.h"


namespace stm32f767 {

enum UsartInstance {
	UART_1 = 0,
	UART_3 = 1
};

class UsartSettings{
	public:
		UsartSettings()
		{
			this->m_baudrate = 115200;
			this->m_bits = 8;
			this->m_parity = 0;
			this->m_stopbit = 1;
			this->m_flowcontrol = 0;

		}
		UsartSettings(uint32_t baudrate, uint32_t bits, uint32_t parity, uint32_t stopbit, uint32_t flowcontrol):
						m_baudrate(baudrate), m_bits(bits),m_parity(parity),m_stopbit(stopbit),m_flowcontrol(flowcontrol)
		{}

		uint32_t m_baudrate;
		uint32_t m_bits;
		uint32_t m_parity;
		uint32_t m_stopbit;
		uint32_t m_flowcontrol;

};
class UsartConfig {
	public:
		UsartConfig(USART_TypeDef * instance, uint32_t bus,uint32_t usartclock, uint32_t gpioclock,GPIO_TypeDef * txport , uint32_t txpin,GPIO_TypeDef * rxport, uint32_t rxpin,uint32_t clockdiv) :
			m_instance(instance),
			m_bus(bus),
			m_usartclock(usartclock),
			m_gpioclock(gpioclock),
			m_txport(txport),
			m_txpin(txpin),
			m_rxport(rxport),
			m_rxpin(rxpin),
			m_clockdiv(clockdiv)
			 {}
	
		USART_TypeDef * m_instance;
		uint32_t m_bus;
		uint32_t m_usartclock;
		uint32_t m_gpioclock;
		GPIO_TypeDef * m_txport;
		uint32_t m_txpin;
		GPIO_TypeDef * m_rxport;
		uint32_t m_rxpin;
		uint32_t m_clockdiv;
};

class Usart {
public:
	Usart() = default;
	Usart(UsartInstance instance, UsartSettings  settings);

	bool Initialize();
	bool Transmit(uint8_t * buffer);

private:
	UsartConfig  m_config;
	UsartSettings m_settings;

	bool Init(USART_TypeDef * instance, uint32_t baudrate,uint32_t bits,uint32_t parity, uint32_t stopbit,uint32_t flowcontrol);
};



/* Define used to enable Virtual Com Port use :
     USE_VCP_CONNECTION == 0
       USART1 instance is used. (TX on PA.09, RX on PA.10)
       (requires wiring USART1 TX/Rx Pins to PC connection (could be achieved thanks to a USB to UART adapter)
     USE_VCP_CONNECTION == 1
       USART3 instance is used. (TX on PD.08, RX on PD.09)
       (please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled
       on HW board in order to support Virtual Com Port)
*/
#define USE_VCP_CONNECTION       1

/* Private definitions covering GPIO clock and USART pins
   depending on selected USART instance. */
#if (USE_VCP_CONNECTION == 0)

/* USART1 instance is used. (TX on PA.09, RX on PA.10)
   (requires wiring USART1 TX/Rx Pins to USB to UART adapter) */
#define USARTx_INSTANCE               USART1
#define USARTx_CLK_ENABLE()           LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define USARTx_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2)

#define USARTx_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)   /* Enable the peripheral clock of GPIOA */
#define USARTx_TX_PIN                 LL_GPIO_PIN_9
#define USARTx_TX_GPIO_PORT           GPIOA
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_10
#define USARTx_RX_GPIO_PORT           GPIOA
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7)
#define APB_Div 2

#else

/* USART3 instance is used. (TX on PD.08, RX on PD.09)
   (please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled
    on HW board in order to support Virtual Com Port) */
#define USARTx_INSTANCE               USART3
#define USARTx_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3)
#define USARTx_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1)

#define USARTx_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD)   /* Enable the peripheral clock of GPIOD */
#define USARTx_TX_PIN                 LL_GPIO_PIN_8
#define USARTx_TX_GPIO_PORT           GPIOD
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_8, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_9
#define USARTx_RX_GPIO_PORT           GPIOD
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define APB_Div 4

#endif /* (USE_VCP_CONNECTION == 0) */


#define USER_BUTTON_PIN                         LL_GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT                   GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC)
#define USER_BUTTON_EXTI_LINE                   LL_EXTI_LINE_13
#define USER_BUTTON_EXTI_IRQn                   EXTI15_10_IRQn
#define USER_BUTTON_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(USER_BUTTON_EXTI_LINE)
#define USER_BUTTON_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(USER_BUTTON_EXTI_LINE)
#define USER_BUTTON_SYSCFG_SET_EXTI()           do {                                                                     \
                                                  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                  \
                                                  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);  \
                                                } while(0)
#define USER_BUTTON_IRQHANDLER                  EXTI15_10_IRQHandler

}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_UART_H_ */
