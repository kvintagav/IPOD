//************************************************************************//
//	LCD HD44780
//	Alex_EXE 
//	http://alex-exe.ru/category/radio/stm32/stm32-lcd-hd44780-spl
//************************************************************************//
//#include "stm32l1xx.h" 
#include "main.h"
#include "platform_config.h"

//************************************************************************//

//	задержка
//	Input : p - величина задержки
void lcd44780_delay(unsigned int p);

//	Очистка дисплея
void lcd44780_ClearLCD(void);

//	Установка курсора дисплея
//	Input : x , y - координаты курсора
void lcd44780_SetLCDPosition(char x, char y);

//	Отправка символа
//	Input : c - символ
void lcd44780_ShowChar(unsigned char c);

//	Отправка строки
//	Input : *s - ссылка на строку (массив символов)
void lcd44780_ShowStr(unsigned char *s);

//	инициализация выводов дисплея
void lcd44780_init_pins(void);

//	Инициализация дисплея
void lcd44780_init(void);
