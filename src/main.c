/**
  ******************************************************************************
  * project IPOD Control for smart home   
  * author  Kazakov Andrey
  * version V1.0
  * date    16-December-2013
  * brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lcd-hd44780.h"
#include "image.h"

#ifdef USE_STM32L152 
 #include "stm32l1xx.h"
 #include "stm32l1xx_it.h"
#elif defined USE_STM32F10B 
 #include "stm32f10x.h"
 #include "stm32f10x_it.h"
#elif defined USE_STM32F4XX 
 #include "stm32f4xx.h"
 #include "stm32f4xx_it.h"
#endif 

 
//#include "rtc.h"

#include "ipod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "RTC_L152.h"

char uart_rx_buf[lenght_usart]; 

//RTC_t RTC_R;							 

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))
/*
RTC_DateTypeDef DateStruct;
RTC_AlarmTypeDef AlarmStruct;
RTC_TimeTypeDef TimeStruct;
*/
uint8_t mode=0x00;  //mode work gadget
bool ipod_work;    // ipod  on or off
bool play_stop;
bool simple_mode; 
bool ipod_detect;

int main(void)
{

#ifdef DEBUG
  debug();
#endif
  
#ifdef STM32L1XX_MD //home dock station
  init_timer_pwm();
  init_uart_ipod();
  init_uart_host();
	lcd44780_init();
	lcd44780_SetLCDPosition(0,0);
  
  
  init_rele();
  init_usb();
  init_ipod_detect();


#else  //work accomodometer
   init_uart_ipod();
   init_uart_host();
	// init_leds();
	// SWITCH_2();
	SWITCH_4();
#endif 
	
//	rtc_init();
//	rtc_settime (&RTC_R);				/* Set time */
	
	send_str(UART_EXT,"\r\nIPOD-control ver1.0\r");
	send_str(UART_EXT,"\nCPU: STM32L152RC CORTEX M3\r ");
	send_str(UART_EXT,"\nipod> ");
	
//	LED1_EN;
	
	while(1)
	{
	 
	#ifdef STM32L1XX_MD //home dock station
		if ((ipod_detect==0)&&  (GPIO_ReadInputDataBit(GPIO_ipod_detect, GPIO_Pin_ipod_detect)==1))
		{
			SWITCH_2();
			ipod_detect=1;
		}
		else if ((ipod_detect==1)&&  (GPIO_ReadInputDataBit(GPIO_ipod_detect, GPIO_Pin_ipod_detect)==0))
		{
			ipod_detect=0;
		}
	#else
//CHANGE_MODE();
	delay(1000000);  
//	SWITCH_4();
	delay(1000000);  
//GET_MODE() ;
	GET_MAX_SCREEN();
//delay(10000000); 
		
 
  delay(10000000); 
  send_image(1);


	#endif
	


	}
	
}




/*dy_command-response command frop DY
*/
void dy_command(uint8_t BYTE)
{
	if (mode==MODE_IPOD)  //if mode ipod 
	{	
		switch(BYTE)
		{	
			case DY_SLEEP :
				if (ipod_work==1) 
				{
					IPOD_OFF();
					ipod_work=0;
				}	
				else  
				{
					IPOD_ON();
					ipod_work=1;
				}	
			break;
			case DY_HOME :
				MENU_BUTTON();
				BUTTON_RELEASE();
			break;
			case DY_MODE :
				 mode=MODE_CLK;

			break;
			case DY_CLOCK :
				 SCROLL_CCW();
				 BUTTON_RELEASE();
			break;
			case DY_SEL : 
				 CENTER_BUTTON();
				 BUTTON_RELEASE();
			break;
			case DY_EQ :
				 SCROLL_CW();
				 BUTTON_RELEASE();
			break;
			case DY_BACK :
				SKIP_BACK();
				BUTTON_RELEASE();
			break;
			case DY_NEXT :
				SKIP_FORWARD();
				BUTTON_RELEASE();
			break;
			case DY_START :
				if (play_stop==1)
				{
					PAUSE();
					play_stop=0;
				}				
				else 
				{
					PLAY();
					play_stop=1;
				}
			break;
			case DY_DOWN :
				VOL_DOWN ();
				BUTTON_RELEASE();
			break;
			case DY_UP :
				 VOL_UP ();
				 BUTTON_RELEASE();
			break;
			case DY_0 :
			break;
			case DY_1 :
				PREV_ALBUM();
				BUTTON_RELEASE();
			break;
			case DY_2 :
			break;
			case DY_3 :
				NEXT_ALBUM();
				BUTTON_RELEASE();
			break;
			case DY_4 :
				PREV_PLAYLIST();
				BUTTON_RELEASE();				
			break;
			case DY_5 :
			break;
			case DY_6 :
				NEXT_PLAYLIST();   
				BUTTON_RELEASE();
			break;
			case DY_7 :
			break;
			case DY_8 :
			break;
			case DY_9 :
			break;
			default:
			break;
			

		 }
	}	
	else if (mode==MODE_CLK)
	{
		switch(BYTE)
		{
			case DY_MODE :
				 mode=MODE_IPOD;

			break;
		}
	}	
}


void write_com(void) //processing command from uart2(host)
{
	if (strncmp(uart_rx_buf,"simple",6)==0)
	{		simple_mode=1;
	}	
	else if (strncmp(uart_rx_buf,"help",4)==0)
	{
			send_str(UART_EXT,"\nipod> ");
	  	send_str(UART_EXT,"\n1-BUTTON_RELEASE\r");
			send_str(UART_EXT,"\n2-PLAY_PAUSE\r");
			send_str(UART_EXT,"\n3-VOL_UP\r");
			send_str(UART_EXT,"\n4-VOL_DOWN\r");
			send_str(UART_EXT,"\n5-SKIP_FORWARD\r");
			send_str(UART_EXT,"\n6-SKIP_BACK\r");
			send_str(UART_EXT,"\n7-PREV_ALBUM\r");
			send_str(UART_EXT,"\n8-STOP_PLAY\r");
			send_str(UART_EXT,"\n9-PLAY\r");
			send_str(UART_EXT,"\nw-PAUSE\r");
			send_str(UART_EXT,"\ne-TOGGLE_MUTE\r");
			send_str(UART_EXT,"\nr-NEXT_PLAYLIST\r");
			send_str(UART_EXT,"\nt-PREV_PLAYLIST\r");
			send_str(UART_EXT,"\ny-TOGGLE_SHUFFLE\r");
			send_str(UART_EXT,"\nu-TOGGLE_REPEAT\r");
			send_str(UART_EXT,"\ni-IPOD_OFF\r");
			send_str(UART_EXT,"\no-IPOD_ON\r");
			send_str(UART_EXT,"\np-MENU_BUTTON\r");
			send_str(UART_EXT,"\ns-CENTER_BUTTON\r");
			send_str(UART_EXT,"\nd-SCROLL_CCW\r");
			send_str(UART_EXT,"\nf-SCROLL_CW\r");
			send_str(UART_EXT,"\nq-OUT_SIMOLE_MODE\r");
		}

	send_str(UART_EXT,"\nipod> ");
	
}


void send_to_uart(USART_TypeDef* USARTx,char data)
{
	//while(!(USARTx->SR & USART_SR_TC));
	USART_SendData(USARTx,(uint8_t)data);
	 while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
  {}
}
void send_str(USART_TypeDef* USARTx,char * string) 
{
	int i=0;
	while(string[i]) 
	{
		send_to_uart(USARTx,string[i]);
		i++;
	}
}
void delay(int nCount)
{
  	for(; nCount!= 0;nCount--);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */

void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
