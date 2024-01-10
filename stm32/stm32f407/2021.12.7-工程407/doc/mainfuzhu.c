// GPIO初始化
//		GPIO_InitTypeDef GPIO_InitStructure;
//		/*开启LED相关的GPIO外设时钟*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
//		/*选择要控制的GPIO引脚*/
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
//		/*设置引脚模式为通用推挽输出*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//		/*设置引脚速率为50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		/*调用库函数，初始化GPIO*/
//		GPIO_Init(GPIOA, &GPIO_InitStructure);	

/*
EXTI
相关寄存器

*/
#if 0
STM32F407 只有 FSMC 功能，但是使用的固件库里面有 FMC 和 FSMC 的功能，如果这两个文件
都同时编译的话，那么就会出错，所以我们选择把 FMC 在工程里面屏蔽掉，就不编译。同时，固
件库里面还有 DMA2D 和 LTDC 的库，但是 F407 都没有这两个功能，所以我们也选择把这两个
文件从工程里面屏蔽掉
#endif
#if 0

#endif

