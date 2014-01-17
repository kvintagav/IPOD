/*
include different platform 
*/
#ifdef STM32L1XX_MD 
  #include "platform_L152.h"
#elif defined STM32F10X_MD 
  #include "platform_F100.h"
#elif defined STM32F4XX 
  #include "platform_F400.h"
#endif 
