/* Settings board for project clock_ipod or ACCOMODOMETER

*/

/* settings display*/
#define lcd44780_port					GPIOC
#define lcd44780_pin_RS				GPIO_Pin_6
#define lcd44780_pin_RW				GPIO_Pin_7
#define lcd44780_pin_E				GPIO_Pin_8
#define lcd44780_pins_data		GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12
#define lcd44780_RCC					RCC_AHBPeriph_GPIOC
#define lcd44780_offset 			12

#define lcd44780_RS_1 GPIO_SetBits(lcd44780_port, lcd44780_pin_RS);
#define lcd44780_E_1  GPIO_SetBits(lcd44780_port, lcd44780_pin_E);
#define lcd44780_RW_1 GPIO_SetBits(lcd44780_port, lcd44780_pin_RW);
#define lcd44780_RS_0 GPIO_ResetBits(lcd44780_port, lcd44780_pin_RS);
#define lcd44780_E_0  GPIO_ResetBits(lcd44780_port, lcd44780_pin_E);
#define lcd44780_RW_0  GPIO_ResetBits(lcd44780_port, lcd44780_pin_RW);




/* IR settings */
#define IR_RCC_TIM RCC_APB1Periph_TIM2
#define IR_RCC_PORT RCC_AHBPeriph_GPIOB
//gpio PB.3
#define IR_GPIO    GPIO_Pin_3
#define IR_PORT    GPIOB
#define IR_GPIO_SOURCE GPIO_PinSource2
#define IR_GPIO_AF_TIMER GPIO_AF_TIM2
#define IR_IRQ TIM2_IRQn
#define TIM_CHANNEL2 TIM_Channel_2
#define TIM_CHANNEL1 TIM_Channel_1

#define IR_TIM TIM2


/* LED settings*/

/* UART settings for IPOD*/
#define BAUD_IPOD 19200
#define UART_IPOD USART1
#define UART_IPOD_PORT GPIOA
#define UART_IPOD_TX GPIO_Pin_9
#define UART_IPOD_RX GPIO_Pin_10
#define UART_IPOD_RCC RCC_APB2Periph_USART1
#define UART_IPOD_RCC_GPIO   RCC_AHBPeriph_GPIOA       
#define USART_IPOD_TX_SOURCE GPIO_PinSource9
#define USART_IPOD_RX_SOURCE GPIO_PinSource10
#define USART_IPOD_AF GPIO_AF_USART1




/* UART settings for EXT control*/


#define BAUD_EXT 115200
#define UART_EXT USART2
#define UART_EXT_PORT GPIOA
#define UART_EXT_TX GPIO_Pin_2
#define UART_EXT_RX GPIO_Pin_3
#define UART_EXT_RCC_GPIO          RCC_AHBPeriph_GPIOA
#define UART_EXT_RCC        RCC_APB1Periph_USART2
#define UART_EXT_IRQ USART2_IRQn

/*LEDS*/

/*RELE*/
#define GPIO_RELE_RCC RCC_AHBPeriph_GPIOA
#define GPIO_RELE GPIOA
#define PIN_RELE1 GPIO_Pin_8
#define PIN_RELE2 GPIO_Pin_11
	
	
/*USB*/
#define GPIO_USB_RCC RCC_AHBPeriph_GPIOA
#define GPIO_USB GPIOA
#define PIN_USB1 GPIO_Pin_13
#define PIN_USB2 GPIO_Pin_12

/*IPOD DETECT*/
#define GPIO_ipod_RCC RCC_AHBPeriph_GPIOB
#define GPIO_ipod_detect GPIOB
#define GPIO_Pin_ipod_detect GPIO_Pin_4

/* BUTTON settings */

