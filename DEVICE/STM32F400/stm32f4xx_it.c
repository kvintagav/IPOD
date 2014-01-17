/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides all exceptions handler and peripherals interrupt
  *          service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"
#include "stdbool.h"
#include "ipod.h"
#include "platform_config.h"
#define IR_START_LENGTH	1600
#define IR_ONE_LENGTH	600
#define MAX_IR	60
volatile uint8_t ir_rx_buffer[5];
volatile uint8_t prev_com;
volatile bool buffer[MAX_IR];
extern bool simple_mode; 
int timer[MAX_IR];
uint16_t time;
uint8_t step;
uint16_t number;
uint8_t	 byte;
extern char uart_rx_buf[lenght_usart]; 
uint8_t uart_rx_bit; 
extern char uart_rx_buf_ipod[lenght_usart]; 
uint8_t uart_rx_bit_ipod; 

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles usart2 from ipod and responsin command .
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	char uart_data;
	if (UART_EXT->SR & USART_SR_RXNE) 
	{
		
		uart_data=UART_EXT->DR; 
		send_to_uart(UART_EXT,uart_data);
		uart_rx_buf[uart_rx_bit]=uart_data; 
		uart_rx_bit++; 
		if (simple_mode==1) //if simple mode - 1 sim1vol with keypad 
		{
			if (uart_rx_buf[0]=='q') simple_mode=0;	//if key byte end simple mode
			else 
			{	
				command_ipod(uart_rx_buf[0]);
				uart_rx_bit=0;
			}
		}
		else	
		{	
			if(uart_data=='\r') 
			{
				write_com();
				memset(uart_rx_buf, 0, sizeof(uart_rx_buf)); 
				uart_rx_bit=0;
			//	send_str("\n");
			}
		}
	}
}
/**
  * @brief   This function handles usart3 from ipod and responsin command .
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
	char uart_data;
	if (UART_IPOD->SR & USART_SR_RXNE) 
	{
		
		uart_data=UART_IPOD->DR; 
	
		uart_rx_buf_ipod[uart_rx_bit_ipod]=uart_data; 
		uart_rx_bit_ipod++; 
	/*
		if(uart_data==HEADER2) 
		{
		//	write_com();
			memset(uart_rx_buf_ipod, 0, sizeof(uart_rx_buf_ipod)); 
			uart_rx_bit_ipod=0;
		
		}
		*/
		if ((uart_rx_bit_ipod>2) &&((uart_rx_bit_ipod-4)==uart_rx_buf_ipod[2]))
		{
			resp_ipod();	
			memset(uart_rx_buf_ipod, 0, sizeof(uart_rx_buf_ipod)); 
			uart_rx_bit_ipod=0;
		
		}
		
	}
}
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
 
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
