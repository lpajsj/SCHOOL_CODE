#include "stm32f10x_conf.h"
#include "ange_usart.h"
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	printf("%s��%d�������������\n",file,line);
}
#endif
