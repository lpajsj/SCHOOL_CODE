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
NVIC ��ʼ��
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
			adzhi=readad1();  //ȡ����ad
			if(adzhi>umax)//��·�ж�
			{
				zhuangtai_flag=1;
				ckpxianshid("bj.bco",63488);//����
				xianshi();
			}
			else if(adzhi<umin)//��·�ж�
			{
				zhuangtai_flag=2;
				ckpxianshid("bj.bco",63488);//����
				xianshi();
			}
			else//�и��ؽ���
			{
				zhuangtai_flag=3;
				ckpxianshid("bj.bco",2024);//�������
				fuzaipz[0]=adzhi;
				dapinlv(10000);//����10K����
				SysTick_delayms(500);//0.5��ʱ
				
				adzhi=readad1();  //ȡ����ad
//				adzhi+=readad1();
//				adzhi/=2;
				if(adzhi>umax)//��·�ж�
				{
					zhuangtai_flag=1;
					ckpxianshid("bj.bco",63488);//����
					dapinlv(1000);
					SysTick_delayms(500);
					xianshi();
				}
				else if(adzhi<umin)//��·�ж�
				{
					zhuangtai_flag=2;
					ckpxianshid("bj.bco",63488);//����
					xianshi();
					dapinlv(1000);
					SysTick_delayms(500);
				}		
				else
				{
					fuzaipz[1]=adzhi;
					ckpxianshid("bj.bco",2024);//�������
					fzzlh=fuzaipanduan();//�Ƚϴ�С���ó���������
					if(fzzlq==fzzlh)
					fzzl=fzzlh;
					fzzlq=fzzlh;
					dapinlv(1000);//����1K����
					SysTick_delayms(1000);//1S��ʱ
					adzhi=readad16();
					if(adzhi>umax)//��·�ж�
					{
						zhuangtai_flag=1;
						ckpxianshid("bj.bco",63488);//����
						xianshi();
					}
					else if(adzhi<umin)//��·�ж�
					{
						zhuangtai_flag=2;
						ckpxianshid("bj.bco",63488);//����
						xianshi();
					}
					else
					{
//						s=adzhi-fuzaipz[0];
//						s=abs(s);
//						if(s<100)
//						{
						fuzaijisuan();//���㸺�ش�С
						ckpxianshid("bj.bco",2024);//�������
						xianshi();//��ʾ
						if((cflag==1)&&(lflag==1)&&(rflag==1))//������ָ��ض�����Ϣ
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
		else//�������и��ز����Ĵ�����
		{
			if(jidian_flag==0)
			{
				adzhi=readad16();
				if(adzhi>umax)//��·�ж�
				{
					zhuangtai_flag=1;
					ckpxianshid("bj.bco",63488);//����
					xianshi();
				}
				else if(adzhi<umin)//��·�ж�
				{
					zhuangtai_flag=2;
					ckpxianshid("bj.bco",63488);//����
					jidian=1;
					jidian_flag=1;
					SysTick_delayms(500);//0.5S��ʱ,�ü̵����ȶ�
				}		
				else
				{
					zhuangtai_flag=3;
					ckpxianshid("bj.bco",2024);//�������
					bianhao=lbpanduan();//����ж��ӳ���
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

