// GPIO��ʼ��
//		GPIO_InitTypeDef GPIO_InitStructure;
//		/*����LED��ص�GPIO����ʱ��*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
//		/*ѡ��Ҫ���Ƶ�GPIO����*/
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
//		/*��������ģʽΪͨ���������*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//		/*������������Ϊ50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//		/*���ÿ⺯������ʼ��GPIO*/
//		GPIO_Init(GPIOA, &GPIO_InitStructure);	

/*
EXTI
��ؼĴ���

*/
#if 0
STM32F407 ֻ�� FSMC ���ܣ�����ʹ�õĹ̼��������� FMC �� FSMC �Ĺ��ܣ�����������ļ�
��ͬʱ����Ļ�����ô�ͻ������������ѡ��� FMC �ڹ����������ε����Ͳ����롣ͬʱ����
�������滹�� DMA2D �� LTDC �Ŀ⣬���� F407 ��û�����������ܣ���������Ҳѡ���������
�ļ��ӹ����������ε�
#endif
#if 0

#endif

