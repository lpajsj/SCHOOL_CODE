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
//结构体学习
https://blog.csdn.net/as480133937/article/details/83473208?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~aggregatepage~first_rank_ecpm_v1~rank_v31_ecpm-1-83473208.pc_agg_new_rank&utm_term=%E7%BB%93%E6%9E%84%E4%BD%93%E6%88%90%E5%91%98%E4%B8%8D%E6%8C%89%E9%A1%BA%E5%BA%8F%E5%88%9D%E5%A7%8B%E5%8C%96&spm=1000.2123.3001.4430
#endif

