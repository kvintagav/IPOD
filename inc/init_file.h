/*

*/


#ifndef __INIT_FILE_H
#define __INIT_FILE_H



#ifdef __cplusplus
 extern "C" {
#endif 

#define LED1_EN GPIO_SetBits(LD_GPIO_PORT, LD_GREEN_GPIO_PIN);
#define LED2_EN  GPIO_SetBits(LD_GPIO_PORT, LD_BLUE_GPIO_PIN);
#define LED1_DS GPIO_ResetBits(LD_GPIO_PORT, LD_GREEN_GPIO_PIN);
#define LED2_DS  GPIO_ResetBits(LD_GPIO_PORT, LD_BLUE_GPIO_PIN);
 

#ifdef USE_STM32L152
 #include "stm32l1xx.h"
 #include "platform_L152.h"
#elif defined USE_STM32F10B
 #include "stm32f10x.h"
 #include "platform_F100.h" 
#elif defined USE_STM32F4XX
 #include "stm32f4xx.h"
 #include "platform_F400.h" 
 
#endif    

#ifdef __cplusplus
}
#endif


#endif 



void init_timer (void);
void init_timer_pwm (void);

void init_uart_ipod(void);
void init_uart_host (void);

void init_leds(void);
void init_rele(void);
void init_usb(void);
void init_ipod_detect(void);
