/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Templates/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.1.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "main.h"
#include "ipod.h"
#include "platform_config.h"
#include "stdbool.h"
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
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}
/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
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
};
/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2  interrupt request.

*******************************************************************************/
void TIM2_IRQHandler(void)
{
	//uint8_t i;
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	if( TIM_GetFlagStatus(IR_TIM, TIM_FLAG_CC2))
	{
		time = TIM_GetCapture2(IR_TIM);//read tim_cnt 
		if ((time>0x2000))//&&(time<5000)) //if start bit number=0
		{
			  step=0;
				number=0;
				byte=0;
				ir_rx_buffer[byte]=0x00;
		}	
	/*	else	if (time>5000)
		{
				dy_command(prev_com);
				number=0;	
		}	
	 */ else 
		{
				if (time>0x1100)
				{
					buffer[number]=1;
					ir_rx_buffer[byte]=(1<<step)+ir_rx_buffer[byte];
				}
				else 
				{
					buffer[number]=0;
				}
				step++;
				if (step>=8) 
				{
					byte++;
					ir_rx_buffer[byte]=0x00;
					step=0;
					if (byte==4) 
					{
						dy_command(ir_rx_buffer[2]);
					//	prev_com=ir_rx_buffer[2];
					}
				}
	
				
	  }
  	timer[number]=time;
		number++;		
	}
	
};

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
// if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
 // {
    /* Clear the RTC Second interrupt */
   // RTC_ClearITPendingBit(RTC_IT_SEC);

    /* Toggle LED1 */
 //   STM_EVAL_LEDToggle(LED1);

    /* Enable time update */
  //  TimeDisplay = 1;

    /* Wait until last write operation on RTC registers has finished */
   // RTC_WaitForLastTask();
    
 // }


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
// TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
