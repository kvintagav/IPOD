//************************************************************************//
//	LCD HD44780
//	Alex_EXE 
//	http://alex-exe.ru/category/radio/stm32/stm32-lcd-hd44780-spl
//************************************************************************//
#include "lcd-hd44780.h"


const unsigned char lcd44780_addLUT[4] = {0x80, 0xC0, 0x94, 0xD4};
unsigned char lcd44780_Address, lcd44780_Line;


 unsigned char  tabl_rus[4][16]={0x41,0x80,0x42,0x92,0x81,0x45,0x82,0x83,0x84,0x85,0x4B,0x86,0x4D,0x48,0x4F,0x87
			                       //   А,   Б,   В,   Г,   Д,   Е,   Ж,   З,   И,   Й,   К,   Л,   М,   Н,   О,   П, 
									,0x50,0x43,0x54,0x88,0xD8,0x58,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8D,0x8F,0xAC,0xAD
								   //   Р,   С,   Т,   У,   Ф,   Х,   Ц,   Ч,   Ш,   Щ,   Ъ,   Ы,   Ь,   Э,   Ю,   Я
	   								,0x41,0x80,0x42,0x92,0x81,0x45,0x82,0x83,0x84,0x85,0x4B,0x86,0x4D,0x48,0x4F,0x87
			                       //   А,   Б,   В,   Г,   Д,   Е,   Ж,   З,   И,   Й,   К,   Л,   М,   Н,   О,   П, 
									,0x50,0x43,0x54,0x88,0xD8,0x58,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8D,0x8F,0xAC,0xAD};
								   //   Р,   С,   Т,   У,   Ф,   Х,   Ц,   Ч,   Ш,   Щ,   Ъ,   Ы,   Ь,   Э,   Ю,   Я};
				/*				   
void lcd_preter (char c) 
{
	char i;
	
	switch (c) 
	{
		case C_R: 				
		set_cursor(row, 0);
		break;
		case L_F: 				
		row = (row+1)%NB_ROW;
		set_cursor(row, 0);
		break;
	default:
		{
			if ((c>0x1f) && (c<0x80)) 
			{ 
				
				write_data(c);
			}
			else //if ((c>=0xC0) && (c<=0xFF))
			{
				i=(((c & 0xf0) -0xC0)/16)&0x0f;
				write_data(tabl_rus[i ][c & 0x0F]);		
			}
		}
		break;
	}
}
*/





//************************************************************************//
GPIO_InitTypeDef lcd44780_GPIO_InitStructure;	//	структура для инициализации выводов используемых дисплеем



//	задержка
//	Input : p - величина задержки
void lcd44780_delay(unsigned int p)
{
	unsigned long i;
	for(i=0;i<(p*10);i++){}
}

//	инициализация выводов дисплея
void lcd44780_init_pins(void)
{

	#ifdef USE_STM32L152 
	RCC_AHBPeriphClockCmd(lcd44780_RCC, ENABLE);

#elif defined USE_STM32F4XX 
  RCC_AHB1PeriphClockCmd(lcd44780_RCC, ENABLE);
 
#endif 

	lcd44780_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	lcd44780_GPIO_InitStructure.GPIO_Pin = 	lcd44780_pin_E | lcd44780_pin_RS|lcd44780_pin_RW | lcd44780_pins_data;
	lcd44780_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//	выходы с открытым коллектором, нужна подвязка к +5В
	GPIO_Init(lcd44780_port, &lcd44780_GPIO_InitStructure);
}
//************************************************************************//

//	Отправка полубайта дисплею
//	Input : data - пол байта данных
void lcd44780_WriteNibble(unsigned char data)
{
	GPIO_SetBits(lcd44780_port, ((data & 0x0F))<<lcd44780_offset);
	lcd44780_delay(200);
	lcd44780_E_1;
	lcd44780_delay(100);
	lcd44780_E_0;
	GPIO_ResetBits(lcd44780_port, 0x0F<<lcd44780_offset);
}

//	Отправка байта дисплею
//	Input : data - отправляемые данные
void lcd44780_WriteByte(unsigned char data)
{
	lcd44780_WriteNibble(data >> 4);
	lcd44780_WriteNibble(data & 0x0F);
}

//	Перейти на строчку
//	Input : LineNum - номер строки
void lcd44780_GoToLine(char LineNum)
{
	lcd44780_RS_0;
	lcd44780_Address = lcd44780_addLUT[LineNum-1];
	lcd44780_WriteByte(lcd44780_Address);
	lcd44780_RS_1;
	lcd44780_Address = 0;
	lcd44780_Line = LineNum;
}

//	Очистка дисплея
void lcd44780_ClearLCD(void)
{
	lcd44780_RS_0;
	lcd44780_WriteByte(0x01);
	lcd44780_delay(1000);
	lcd44780_RS_1;
	lcd44780_GoToLine(1);
}

//	Установка курсора дисплея
//	Input : x , y - координаты курсора
void lcd44780_SetLCDPosition(char x, char y)
{
	lcd44780_RS_0;
	lcd44780_Address = lcd44780_addLUT[y] + x;
	lcd44780_WriteByte(lcd44780_Address);
	lcd44780_RS_1;
	lcd44780_Line = y+1;
}

//	Отправка символа
//	Input : c - символ
void lcd44780_ShowChar(unsigned char c)
{
	int i;	
	lcd44780_RS_1;
	if ((c>0x00) && (c<0x80)) 
			{ 
				
				lcd44780_WriteByte(c);
			}
			else //if ((c>=0xC0) && (c<=0xFF))
			{
				i=(((c & 0xf0) -0xC0)/16)&0x0f;
				lcd44780_WriteByte(tabl_rus[i ][c & 0x0F]);		
			}
	//lcd44780_WriteByte(c);
	lcd44780_Address++;
	switch (lcd44780_Address)
	{
		case 20: lcd44780_GoToLine(2); break;
		case 40: lcd44780_GoToLine(1); break;
//		case 40: lcd44780_GoToLine(3); break;
//		case 60: lcd44780_GoToLine(4); break;
//		case 80: lcd44780_GoToLine(1); break;
	}
}

//	Отправка строки
//	Input : *s - ссылка на строку (массив символов)
void lcd44780_ShowStr(unsigned char *s)
{
	while (*s != 0) lcd44780_ShowChar(*s++);
}

//	Инициализация дисплея
void lcd44780_init(void)
{
	unsigned char i;
	lcd44780_init_pins();
	lcd44780_E_0;
	lcd44780_RS_0;
	lcd44780_delay(5000);
	lcd44780_WriteNibble(0x33);
	lcd44780_WriteNibble(0x33);
	lcd44780_WriteNibble(0x33);
	lcd44780_WriteNibble(0x22);
	lcd44780_WriteByte(0x28);
	lcd44780_WriteByte(0x01);
	lcd44780_WriteByte(0x10);
	lcd44780_WriteByte(0x06);
	lcd44780_WriteByte(0x0C);
	for(i=0x40; i<0x5F; i++)
	{
		lcd44780_delay(1000);
		lcd44780_RS_0;
		lcd44780_WriteByte(i);
		lcd44780_delay(1000);
		lcd44780_ShowChar(0);
	}
	lcd44780_RS_1;
	lcd44780_ClearLCD();
}
