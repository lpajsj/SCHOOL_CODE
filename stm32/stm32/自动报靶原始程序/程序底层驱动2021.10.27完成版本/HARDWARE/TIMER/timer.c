#include "timer.h"
#include "led.h"
#include "usart.h"
#include "MultiRotor_systime.H"

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器1、3、4!

TIM_ICInitTypeDef  TIM1_ICInitStructure;

void TIM1_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);						//使能TIM1时钟
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  				//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);                       //?????
  //GPIO_AFIODeInit();
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM1 , ENABLE);							//PC6完全重映射
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;  //PE0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //PC 悬空输入  
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);						   //PE9 悬空输入 
	GPIO_ResetBits(GPIOE,GPIO_Pin_11);						 //PE11 悬空输入 
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);						 //PE13 悬空输入 
	GPIO_ResetBits(GPIOE,GPIO_Pin_14);						 //PE14 悬空输入 
	
	//初始化定时器1 TIM1	 
	TIM_TimeBaseStructure.TIM_Period = arr; 														//设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 													//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 						//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  				//TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 										//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
//初始化TIM1输入捕获参数
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_2; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);


	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_3; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM1_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	
	//中断分组初始化
	 NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  									//TIM3中断
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  				//先占优先级2级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  								//从优先级0级
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 										//IRQ通道被使能
	 NVIC_Init(&NVIC_InitStructure);  																	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

//	 TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断	|TIM_IT_CC1  |TIM_IT_CC3
	 TIM_Cmd(TIM1,ENABLE ); 	//使能定时器1
}

TIM_ICInitTypeDef  TIM3_ICInitStructure;

void TIM3_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);						//使能TIM3时钟
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  				//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);                       //?????
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);                       //?????	
  //GPIO_AFIODeInit();
//  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3 , ENABLE);							//PC6完全重映射
	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;  //PA0 清除之前设置  
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //PC 悬空输入  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PC 悬空输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PC 悬空输入  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);						 //PC6 悬空输入       PA6
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);						 //PC7 悬空输入       PA7
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);						 //PC8 悬空输入       PB0
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);						 //PC9 悬空输入       PB1
	
	
	//初始化定时器3 TIM3	 
	TIM_TimeBaseStructure.TIM_Period = arr; 														//设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 													//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 						//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  				//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 										//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
//初始化TIM3输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM3_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM3_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);


	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM3_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM3_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	
	//中断分组初始化
	 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  									//TIM3中断
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  				//先占优先级2级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  								//从优先级0级
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 										//IRQ通道被使能
	 NVIC_Init(&NVIC_InitStructure);  																	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

	 TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3
}

TIM_ICInitTypeDef  TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr,u16 psc)
{	 
//	TIM_ICInitTypeDef  TIM4_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);						//使能TIM4时钟
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  				//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);                       //?????
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);                       //?????
//  GPIO_AFIODeInit();
  GPIO_PinRemapConfig(GPIO_Remap_TIM4 , ENABLE);							//PD12\13\14\15重映射
//	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //PC 悬空输入  
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);						 //PC6 悬空输入 
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);						 //PC7 悬空输入 
	GPIO_ResetBits(GPIOD,GPIO_Pin_14);						 //PC8 悬空输入 
	GPIO_ResetBits(GPIOD,GPIO_Pin_15);						 //PC9 悬空输入 
	
	
	//初始化定时器4 TIM4	 
	TIM_TimeBaseStructure.TIM_Period = arr; 														//设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 													//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 						//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  				//TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 										//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
//初始化TIM4输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);


	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; 									//CC1S=01 	选择输入端 IC1映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;				//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 		//映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 						//配置输入分频,不分频 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;														//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	
	//中断分组初始化
	 NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  									//TIM4中断
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  				//先占优先级3级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  								//从优先级0级
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 										//IRQ通道被使能
	 NVIC_Init(&NVIC_InitStructure);  																	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

//	 TIM_Cmd(TIM4,ENABLE ); 	//使能定时器4
}


u8  TIM1CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM1CH1_CAPTURE_VAL;	  //输入捕获值

u8  TIM1CH2_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM1CH2_CAPTURE_VAL;	  //输入捕获值
 
u8  TIM1CH3_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM1CH3_CAPTURE_VAL;	  //输入捕获值

u8  TIM1CH4_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM1CH4_CAPTURE_VAL;	  //输入捕获值

u8 TIM1_state4;				//TIM1_state1,TIM1_state2,TIM1_state3,
u16 time1count6,time1count7;	//time1count0,time1count1,time1count2,time1count3,time1count4,time1count5,
u16 test4;			//test1,test2,test3,
u16 fq1;
u8 fq_ABC;
//定时器1中断服务程序	 
void TIM1_CC_IRQHandler(void)
{
	//TIM1_CH1
	 if(TIM_GetITStatus(TIM1,TIM_IT_CC1)!=RESET)  
   {  
      TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);  
			TIM1CH1_CAPTURE_STA++;
   }
	 //TIM1_CH2
	 if(TIM_GetITStatus(TIM1,TIM_IT_CC2)!=RESET)  
   {  
      TIM_ClearITPendingBit(TIM1, TIM_IT_CC2); 
			TIM1CH2_CAPTURE_STA++;
   }
	 //TIM1_CH3
	  if(TIM_GetITStatus(TIM1,TIM_IT_CC3)!=RESET)  
	 {  
		 TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);   
		 TIM1CH3_CAPTURE_STA++;
		}
	//TIM1_CH4
	 if(TIM_GetITStatus(TIM1,TIM_IT_CC4)!=RESET)  
   {  
       TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);   
       if(TIM1_state4==0)   
       {  
           TIM1_state4=1;  
           time1count6=TIM_GetCapture4(TIM1);        
       }  
       else if(TIM1_state4==1)  
       {  
           TIM1_state4=0; 
					 TIM1CH4_CAPTURE_STA=1;
           time1count7=TIM_GetCapture4(TIM1);     
           if(time1count6<time1count7)  
           {  
                 test4=time1count7-time1count6;             
           }  
           else if(time1count6>time1count7)  
           {  
                 test4=(0xffff-time1count6)+time1count7;  
           }  
           else test4=0;  		 
           fq1=1000000/test4;       //邮箱流量计脉冲     
       }  
   } 
			
	TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位		
}

u8  TIM3CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM3CH1_CAPTURE_VAL;	  //输入捕获值

u8  TIM3CH2_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM3CH2_CAPTURE_VAL;	  //输入捕获值
 
u8  TIM3CH3_CAPTURE_STA;	  //输入捕获状态		    				
u16	TIM3CH3_CAPTURE_VAL;	  //输入捕获值

u8  TIM3CH4_CAPTURE_STA;	  //输入捕获状态		    				
u16	TIM3CH4_CAPTURE_VAL;	  //输入捕获值

//u8 TIM3_state3,TIM3_state4;
//u16 timecount,timecount1,timecount2,timecount3;
//u16 test;
u16 duty1,duty2,duty3,duty4;	//占空比,ms50cnt
u8 duty_OK,TIM3_IRQ_count;		
extern u16 ms50cnt;
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 
	//TIM3_CH1
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
		{	
			TIM3CH1_CAPTURE_VAL++;
			TIM3_IRQ_count=(duty_OK&0x01);
			if(TIM3_IRQ_count!=0x01)
			{
				duty1=TIM_GetCapture1(TIM3);
				if(duty_OK==0)
					{
						ms50cnt=0;
					}
				duty_OK|=0x01;
			}
			else;;
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update);
		}
	//TIM3_CH2
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
		{	   
			TIM3CH2_CAPTURE_VAL++;
			TIM3_IRQ_count=(duty_OK&0x02);
			if(TIM3_IRQ_count!=0x02)
			{
				duty2=TIM_GetCapture2(TIM3);
				
				if(duty_OK==0)
					{
						ms50cnt=0;
					}
				duty_OK|=0x02;
			}
			else;;
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update);
		}
		//TIM3_CH3
	if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
		{	    
			TIM3CH3_CAPTURE_VAL++;
			TIM3_IRQ_count=(duty_OK&0x04);
			if(TIM3_IRQ_count!=0x04)
			{
				duty3=TIM_GetCapture3(TIM3);
				
				if(duty_OK==0)
					{
						ms50cnt=0;
					}
				duty_OK|=0x04;
			}
			else;;
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC3|TIM_IT_Update);
 	}
	//TIM3_CH4
	if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
		{	   
			TIM3CH4_CAPTURE_VAL++;
			TIM3_IRQ_count=(duty_OK&0x08);			
			if(TIM3_IRQ_count!=0x08)
			{
				duty4=TIM_GetCapture4(TIM3);
				
				if(duty_OK==0)
					{
						ms50cnt=0;
						
					}
				duty_OK|=0x08;
			}
			else;;
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC4|TIM_IT_Update);
		}
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4); //清除中断标志位		
}

u8  TIM4CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM4CH1_CAPTURE_VAL;	  //输入捕获值

u8  TIM4CH2_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM4CH2_CAPTURE_VAL;	  //输入捕获值
 
u8  TIM4CH3_CAPTURE_STA;	  //输入捕获状态		    				
u16	TIM4CH3_CAPTURE_VAL;	  //输入捕获值

u8  TIM4CH4_CAPTURE_STA;	  //输入捕获状态		    				
u16	TIM4CH4_CAPTURE_VAL;	  //输入捕获值

static u8 TIM4_state1,TIM4_state2,TIM4_state3,TIM4_state4;
//u8 TIM4_sta1,TIM4_sta2,TIM4_sta3,TIM4_sta4;
static u16 timecount0,timecount1,timecount2,timecount3,timecount4,timecount5;//,timecount6,timecount7
u16 test1,test2,test3,test4;;
u16 duty5;	//占空比
u16 fq2,fq3,fq4;				  			//频率

void TIM4_IRQHandler(void)
{
	//TIM4_CH1
	 if(TIM_GetITStatus(TIM4,TIM_IT_CC1)!=RESET)  
   {  
       TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);   
       if(TIM4_state1==0)   
       {  
           TIM4_state1=1;  
           timecount0=TIM_GetCapture1(TIM4);        
       }  
       else if(TIM4_state1==1)  
       {  
           TIM4_state1=0; 
					 TIM4CH1_CAPTURE_STA++;
           timecount1=TIM_GetCapture1(TIM4);     
           if(timecount0<timecount1)  
           {  
                 test1=timecount1-timecount0;             
           }  
           else if(timecount0>timecount1)  
           {  
                 test1=(0xffff-timecount0)+timecount1;  
           }  
           else test1=0;  		 
           fq2=1000000/test1;            
       }  
   } 
	 
	 //TIM4_CH2
	 if(TIM_GetITStatus(TIM4,TIM_IT_CC2)!=RESET)  
   {  
       TIM_ClearITPendingBit(TIM4, TIM_IT_CC2); 
       if(TIM4_state2==0)   
       {  
           TIM4_state2=1;  
           timecount2=TIM_GetCapture2(TIM4);        
       }  
       else if(TIM4_state2==1)  
       {  
					 TIM4_state2=0;  
					 TIM4CH2_CAPTURE_STA++;
           timecount3=TIM_GetCapture2(TIM4);     
           if(timecount2<timecount3)  
           {  
                 test2=timecount3-timecount2;             
           }  
           else if(timecount2>timecount3)  
           {  
                 test2=(0xffff-timecount2)+timecount3;  
           }  
           else test2=0; 
           fq3=1000000/test2;
					 
       }  
   }
	//TIM4_CH3
	 if(TIM_GetITStatus(TIM4,TIM_IT_CC3)!=RESET)  
   {  
       TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);   
       if(TIM4_state3==0)   
       {  
           TIM4_state3=1;  
           timecount4=TIM_GetCapture3(TIM4);        
       }  
       else if(TIM4_state3==1)  
       {  
					 TIM4_state3=0;  
					 TIM4CH3_CAPTURE_STA++;
           timecount5=TIM_GetCapture3(TIM4);     
           if(timecount4<timecount5)  
           {  
                 test3=timecount5-timecount4;             
           }  
           else if(timecount4>timecount5)  
           {  
                 test3=(0xffff-timecount4)+timecount5;  
           }  
           else test3=0;  		 
           fq4=1000000/test3;            
       }  
   }
	 //TIM4_CH4
	if((TIM4CH4_CAPTURE_STA&0x80)==0)										//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{	    
			if(TIM4CH4_CAPTURE_STA&0x40)										//已经捕获到高电平了
			{
				if((TIM4CH4_CAPTURE_STA&0X3F)==0x3f)					//高电平太长了
				{
					TIM4CH4_CAPTURE_STA|=0x80;									//标记成功捕获了一次
					TIM4CH4_CAPTURE_VAL=0xffff;
				}
				else TIM4CH4_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)			//捕获1发生捕获事件
		{	
			if(TIM4CH4_CAPTURE_STA&0x40)										//捕获到一个下降沿 		
			{	  			
				TIM4CH4_CAPTURE_STA|=0x80;										//标记成功捕获到一次高电平脉宽
				TIM4CH4_CAPTURE_VAL=TIM_GetCapture4(TIM4);
		   	TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  																					//还未开始,第一次捕获上升沿
			{
				TIM4CH4_CAPTURE_STA=0;												//清空
				TIM4CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);
				TIM4CH4_CAPTURE_STA|=0x40;										//标记捕获到了上升沿
		   	TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			 
 	}
	 
	 
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位	
}


/*
2ms一次
*/

void time(void)										//测量发电机信号频率
{
//	static u8 cnt=0;
//	static u8 sta=0x00;
//	static u8 status=0x00;
//	static u8 TIM1CH1_ERR_counter,TIM1CH2_ERR_counter,TIM1CH3_ERR_counter;
//	u32 temp1=0,temp2=0,temp3=0,temp4=0,temp5=0;
//	switch(status)
//	{
//		case 0x00:     //time1
//				switch (sta)
//				{
//					case 0x00: 
//							TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断	|TIM_IT_CC1  |TIM_IT_CC3
//							TIM1CH1_CAPTURE_STA=0;//TIM1_state1=0;
//							TIM1CH2_CAPTURE_STA=0;//TIM1_state2=0;
//							TIM1CH3_CAPTURE_STA=0;//TIM1_state3=0;
//							TIM1CH4_CAPTURE_STA=0;TIM1_state4=0;
//							cnt=0; sta=0x01;
//						break;    
//					case 0x01: 
//							cnt++;
//							if(cnt>=20) 
//							{
//								if(TIM1CH1_CAPTURE_STA>=2)
//								{
//									TIM1CH1_ERR_counter=0;
//									fq_ABC&=0xfe;
//								}
//								else
//								{
//									TIM1CH1_ERR_counter++;
//									if(TIM1CH1_ERR_counter>=3)
//									{	
//										TIM1CH1_ERR_counter=0;
//										fq_ABC|=0x01;
//									}
//									else ;;
//								}
//								
//								if(TIM1CH2_CAPTURE_STA>=2)
//								{
//									TIM1CH2_ERR_counter=0;
//									fq_ABC&=0xfd;
//								}
//								else
//								{
//									TIM1CH2_ERR_counter++;
//									if(TIM1CH2_ERR_counter>=3)
//									{	
//										TIM1CH2_ERR_counter=0;
//										fq_ABC|=0x02;
//									}
//									else ;;
//								}
//								
//								if(TIM1CH3_CAPTURE_STA>=2)
//								{
//									TIM1CH3_ERR_counter=0;
//									fq_ABC&=0xfb;
//								}
//								else
//								{
//									TIM1CH3_ERR_counter++;
//									if(TIM1CH3_ERR_counter>=3)
//									{	
//										TIM1CH3_ERR_counter=0;
//										fq_ABC|=0x04;
//									}
//									else ;;
//								}
//								if(TIM1CH4_CAPTURE_STA==0)fq1=0;else ;;
//								TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);			//允许更新中断 ,允许CC1IE捕获中断	|TIM_IT_CC1  |TIM_IT_CC3
//								cnt=0; 
//								sta=0x00;
//								status=0x01;	
//							}
//						break;
//					default : break;
//			}
//			break;
//		case 0x01:				 //time3
//				switch (sta)
//				{
//					case 0x00: 
//							TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断
//							TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);			//关闭更新中断 ,关闭CC1IE捕获中断	
//							//	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断	

//							if(TIM3CH1_CAPTURE_STA&0x80)								//成功捕获到了一次上升沿
//							{
//								temp1=TIM3CH1_CAPTURE_STA&0x3f;
//								temp1*=65536;													//溢出时间总和
//								temp1+=TIM3CH1_CAPTURE_VAL;						//得到总的高电平时间
//								duty1=temp1;
//								TIM3CH1_CAPTURE_STA=0;								//开启下一次捕获
//								TIM3CH1_CAPTURE_VAL=0;
//							}
//							else duty1=0;
//							cnt=0; sta=0x01;
//						break;    
//					case 0x01: 
//							cnt++;
//							if(cnt>=5) 
//							{
//									TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断
//									TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC3|TIM_IT_CC4,DISABLE);			//允许更新中断 ,允许CC1IE捕获中断	

//									if(TIM3CH2_CAPTURE_STA&0x80)								//成功捕获到了一次上升沿
//											{
//												temp2=TIM3CH2_CAPTURE_STA&0x3f;
//												temp2*=65536;													//溢出时间总和
//												temp2+=TIM3CH2_CAPTURE_VAL;						//得到总的高电平时间
//												duty2=temp2;
//												TIM3CH2_CAPTURE_STA=0;								//开启下一次捕获
//												TIM3CH2_CAPTURE_VAL=0;
//											}
//											else duty2=0;
//								cnt=0; sta=0x02;
//							}
//						break;
//					case 0x02: 
//							cnt++;
//							if(cnt>=5) 
//							{
//									TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断
//									TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC4,DISABLE);			//允许更新中断 ,允许CC1IE捕获中断	
//									if(TIM3CH3_CAPTURE_STA&0x80)								//成功捕获到了一次上升沿
//											{
//												temp3=TIM3CH3_CAPTURE_STA&0x3f;
//												temp3*=65536;													//溢出时间总和
//												temp3+=TIM3CH3_CAPTURE_VAL;						//得到总的高电平时间
//												duty3=temp3;
//												TIM3CH3_CAPTURE_STA=0;								//开启下一次捕获
//												TIM3CH3_CAPTURE_VAL=0;
//											}
//											else duty3=0;
//								cnt=0; sta=0x03;
//							}
//						break;
//					case 0x03: 
//							cnt++;
//							if(cnt>=5) 
//							{
//									TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断
//									TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,DISABLE);			//允许更新中断 ,允许CC1IE捕获中断	
//									if(TIM3CH4_CAPTURE_STA&0x80)								//成功捕获到了一次上升沿
//											{
//												temp4=TIM3CH4_CAPTURE_STA&0x3f;
//												temp4*=65536;													//溢出时间总和
//												temp4+=TIM3CH4_CAPTURE_VAL;						//得到总的高电平时间
//												duty4=temp4;
//												TIM3CH4_CAPTURE_STA=0;								//开启下一次捕获
//												TIM3CH4_CAPTURE_VAL=0;
//											}
//											else duty4=0;
//								cnt=0; sta=0x04;
//							}
//						break;
//					case 0x04:
//							cnt++;
//							if(cnt>=5) 
//							{
//								TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);			//关闭更新中断 ,关闭CC1IE捕获中断
//								cnt=0; 
//								sta=0x00;
//								status=0x02;
//							}
//						break;
//					default : break;
//				}
//			break;

//		case 0x02:      //time4
//				switch (sta)
//				{
//					case 0x00: 
//							cnt++;
//							TIM_Cmd(TIM4,ENABLE);
//							TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,ENABLE);
//							TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC4,DISABLE);
//							TIM4CH1_CAPTURE_STA=0;
//							TIM4CH2_CAPTURE_STA=0;
//							TIM4CH3_CAPTURE_STA=0;
//							TIM4_state1=0;
//							TIM4_state2=0;
//							TIM4_state3=0;
//							sta=0x01;
//						break;  
//					case 0x01:
//							cnt++;
//							if(cnt>=20) 
//							{
//								if(TIM4CH1_CAPTURE_STA==0)fq2=0;
//								if(TIM4CH2_CAPTURE_STA==0)fq3=0;
//								if(TIM4CH3_CAPTURE_STA==0)fq4=0;
//								TIM4_state1=0;
//								TIM4_state2=0;
//								TIM4_state3=0;
//								TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3,DISABLE);			//关闭更新中断 ,关闭CC1IE捕获中断
//								cnt=0; sta=0x02;
//							}
//						break;
//					case 0x02: 
//							TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC4,ENABLE);			//允许更新中断 ,允许CC1IE捕获中断	|
//							TIM4CH4_CAPTURE_STA=0;
//							TIM4CH4_CAPTURE_VAL=0;
//							cnt=0; sta=0x03;
//					case 0x03:
//							cnt++;
//							if(cnt>=5)
//							{
//								if(TIM4CH4_CAPTURE_STA&0x80)								//成功捕获到了一次上升沿
//								{
//									temp5=TIM3CH4_CAPTURE_STA&0x3f;
//									temp5*=65536;													//溢出时间总和
//									temp5+=TIM4CH4_CAPTURE_VAL;						//得到总的高电平时间
//									duty5=temp5;
//								}
//								else duty5=0;
//								cnt=0;sta=0x00;
//								status=0x00;
//								TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);
//								TIM_Cmd(TIM4,DISABLE);
//							}
//						break;
//					default : break;
//				}
//				break;
//			default : break;
//		}				
}



