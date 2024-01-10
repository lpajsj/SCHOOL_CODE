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
NVIC 初始化
void ange_extinvicinit()
{
	NVIC_InitTypeDef nvicinit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvicinit.NVIC_IRQChannel=ange_EXTI_IRQn;
	nvicinit.NVIC_IRQChannelPreemptionPriority=1;
	nvicinit.NVIC_IRQChannelSubPriority=1;
	nvicinit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicinit);
}
#endif
#if 0
if(cflag==0||lflag==0||rflag==0)
		{
			adzhi=readad1();  //取两次ad
			if(adzhi>umax)//开路判断
			{
				zhuangtai_flag=1;
				ckpxianshid("bj.bco",63488);//报警
				xianshi();
			}
			else if(adzhi<umin)//短路判断
			{
				zhuangtai_flag=2;
				ckpxianshid("bj.bco",63488);//报警
				xianshi();
			}
			else//有负载接入
			{
				zhuangtai_flag=3;
				ckpxianshid("bj.bco",2024);//清除报警
				fuzaipz[0]=adzhi;
				dapinlv(10000);//产生10K正弦
				SysTick_delayms(500);//0.5延时
				
				adzhi=readad1();  //取两次ad
//				adzhi+=readad1();
//				adzhi/=2;
				if(adzhi>umax)//开路判断
				{
					zhuangtai_flag=1;
					ckpxianshid("bj.bco",63488);//报警
					dapinlv(1000);
					SysTick_delayms(500);
					xianshi();
				}
				else if(adzhi<umin)//短路判断
				{
					zhuangtai_flag=2;
					ckpxianshid("bj.bco",63488);//报警
					xianshi();
					dapinlv(1000);
					SysTick_delayms(500);
				}		
				else
				{
					fuzaipz[1]=adzhi;
					ckpxianshid("bj.bco",2024);//清除报警
					fzzlh=fuzaipanduan();//比较大小，得出负载种类
					if(fzzlq==fzzlh)
					fzzl=fzzlh;
					fzzlq=fzzlh;
					dapinlv(1000);//产生1K正弦
					SysTick_delayms(1000);//1S延时
					adzhi=readad16();
					if(adzhi>umax)//开路判断
					{
						zhuangtai_flag=1;
						ckpxianshid("bj.bco",63488);//报警
						xianshi();
					}
					else if(adzhi<umin)//短路判断
					{
						zhuangtai_flag=2;
						ckpxianshid("bj.bco",63488);//报警
						xianshi();
					}
					else
					{
//						s=adzhi-fuzaipz[0];
//						s=abs(s);
//						if(s<100)
//						{
						fuzaijisuan();//计算负载大小
						ckpxianshid("bj.bco",2024);//清除报警
						xianshi();//显示
						if((cflag==1)&&(lflag==1)&&(rflag==1))//如果三种负载都有信息
						{
							jisuanf();
							f0_1=(u16)f0;
							FirstDate=0xdcba;
							STMFLASH_Write(Ur_Date_ADDR,&ur,1);		
							STMFLASH_Write(f0_Date_ADDR,&f0_1,1);	
							STMFLASH_Write(Write_Date_Flag_ADDR,&FirstDate,1);								
						}
//					  }
					}
				}
			}
		}
		else//这里是有负载参数的代码了
		{
			if(jidian_flag==0)
			{
				adzhi=readad16();
				if(adzhi>umax)//开路判断
				{
					zhuangtai_flag=1;
					ckpxianshid("bj.bco",63488);//报警
					xianshi();
				}
				else if(adzhi<umin)//短路判断
				{
					zhuangtai_flag=2;
					ckpxianshid("bj.bco",63488);//报警
					jidian=1;
					jidian_flag=1;
					SysTick_delayms(500);//0.5S延时,让继电器稳定
				}		
				else
				{
					zhuangtai_flag=3;
					ckpxianshid("bj.bco",2024);//清除报警
					bianhao=lbpanduan();//类别判断子程序
					xianshi();
				}				
			}
			else
			{
				adzhi=readad16();
				if(adzhi<umax60)
				{
					duanlujuli(adzhi);
					xianshi();
					
				}
				else
				{
					jidian=0;
					jidian_flag=0;					
				}
			}
		}
  }
#endif

