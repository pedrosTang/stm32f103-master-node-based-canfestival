#include "canfestival_timer.h"

// ���溯������������canfestival��ΨһӲ����ʱ��TIM14,
// �����������Ҫ���������н��е���,Ȼ������β�Ҳ��TIM1



void TIMConfig(TIM_TypeDef* TIMx, uint16_t TIM_Period, uint16_t TIM_Prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInitTypeDef	 TIM_BaseInitStructure;
	
	//TIM_RepetitionCounter(TIM1_RCR)=0��ÿ��������������������¼�
	TIM_DeInit(TIMx);//��ʼ�� TIM1�Ĵ���
	/*��Ƶ�����ڼ��㹫ʽ��
	Prescaler = (TIMxCLK / TIMx counter clock) - 1;
	Period = (TIMx counter clock / TIM3 output clock) - 1
	TIMx counter clock Ϊ������Ҫ�� TXM �Ķ�ʱ��ʱ��*/
	TIM_BaseInitStructure.TIM_Period = TIM_Period-1;//�������ֲ��֪��TIM1�� TIM8Ϊ16λ�Զ�װ��
	/*�� system_stm32f4xx.c �����õ� APB2 Prescaler = 2 ,��֪
	*APB1ʱ��Ϊ168M/2*2,��Ϊ��� APB1��Ƶ��Ϊ1����ʱʱ�� x2*/
	TIM_BaseInitStructure.TIM_Prescaler = TIM_Prescaler-1;//��ƵΪ10K
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseInitStructure.TIM_CounterMode =  TIM_CounterMode_Up;//���ϼ���
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIMx, &TIM_BaseInitStructure);

	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    
//    TIM_ClearFlag(TIMx, uint16_t TIM_FLAG);
	//ʹ��TIM1�ж�Դ
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
	//TIM1�ܿ��أ�����
	TIM_Cmd(TIMx, ENABLE);//ʹ�� TIM1��ʱ��
}



void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
		
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;    	    //�����¼�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;    //��ռ���ȼ�0  ԭʼ0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //��Ӧ���ȼ�1   ԭʼ1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж�
    NVIC_Init(&NVIC_InitStructure);                             //д������

}


// canfestival ��ʱ�� timer14��ʱ��
void TIM3_IRQHandler(void)
{
		//static int16_t NumDispatch=0;
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
    {
//				NumDispatch++;
//				printf("%d",NumDispatch);
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���ж�
        TimeDispatch(); // canfestival�Ŀ�
    }	
}



void setTimer(TIMEVAL value)
{
	TIM3->ARR = TIM3->CNT + value;
}


TIMEVAL getElapsedTime(void)
{
	return TIM3->CNT;
} 
