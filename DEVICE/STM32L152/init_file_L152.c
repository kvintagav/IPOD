/*file initialization periphery
  
*/
#include "init_file.h"
#include "stm32l1xx.h"
#include "platform_L152.h"

TIM_ICInitTypeDef       TIM_ICInitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

NVIC_InitTypeDef NVIC_InitStructure;

void init_leds(void)
{
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LD_GREEN_GPIO_PIN | LD_BLUE_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(LD_GPIO_PORT, &GPIO_InitStructure);
}
void init_rele(void)
{
		RCC_AHBPeriphClockCmd(GPIO_RELE_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = PIN_RELE1|PIN_RELE2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO_RELE, &GPIO_InitStructure);
	

  
}
void init_usb(void)
{
	RCC_AHBPeriphClockCmd(GPIO_USB_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = PIN_USB1|PIN_USB2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO_USB, &GPIO_InitStructure);
	


}

void init_ipod_detect(void)
{
	RCC_AHBPeriphClockCmd(GPIO_ipod_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_ipod_detect ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_ipod_detect, &GPIO_InitStructure);
}
void init_uart_ipod(void)
{


 /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(UART_IPOD_RCC_GPIO , ENABLE);
  
  /* Enable USART clock */
  RCC_APB2PeriphClockCmd(UART_IPOD_RCC, ENABLE);
  
 
  
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(UART_IPOD_PORT, USART_IPOD_TX_SOURCE, USART_IPOD_AF);
  
  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(UART_IPOD_PORT, USART_IPOD_RX_SOURCE, USART_IPOD_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
  GPIO_InitStructure.GPIO_Pin = UART_IPOD_TX;
  GPIO_Init(UART_IPOD_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = UART_IPOD_RX;
  GPIO_Init(UART_IPOD_PORT, &GPIO_InitStructure);
  
  /* USARTx configuration ----------------------------------------------------*/

  USART_InitStructure.USART_BaudRate = 19200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* When using Parity the word length must be configured to 9 bits */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(UART_IPOD, &USART_InitStructure);
  

    
  /* Enable USART */
	
  USART_Cmd(UART_IPOD, ENABLE);
	
};


void init_uart_host(void)
{

	RCC_AHBPeriphClockCmd(UART_EXT_RCC_GPIO, ENABLE);

	/* Enable GPIOx and AFIO clocks */
  RCC_APB1PeriphClockCmd(UART_EXT_RCC , ENABLE);
 
  
	
	USART_InitStructure.USART_BaudRate = BAUD_EXT;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART_EXT, &USART_InitStructure);
	//USART_Cmd(UART_EXT,ENABLE);
	

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = UART_EXT_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
  USART_Cmd(UART_EXT, ENABLE);
	
};


void init_timer_pwm (void)
{
	 /* --------------------------- System Clocks Configuration ---------------------*/
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /*--------------------------------- GPIO Configuration -------------------------*/
  /* GPIOA Configuration: Pin 7 */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

  /*-------------------------------- NVIC Configuration --------------------------*/
  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* TIM3 configuration: PWM Input mode ------------------------
     The external signal is connected to TIM3 CH2 pin (PA.07), 
     The Rising edge is used as active edge,
     The TIM3 CCR2 is used to compute the frequency value 
     The TIM3 CCR1 is used to compute the duty cycle value
  ------------------------------------------------------------ */

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);

  /* Input Trigger selection */
  TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);
  
  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);

  /* Enable the Master/Slave Mode */
  TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);

  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);


};


