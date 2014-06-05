/*file initialization periphery
  
*/
//#include "init_file.h"

#include "init_file.h"
 

#ifdef USE_STM32L152 
  #include "init_file_L152.c"
#elif defined USE_STM32F10B 
  #include "init_file_F100.c"
#elif defined USE_STM32F4XX 
  #include "init_file_F400.c"
#endif 
