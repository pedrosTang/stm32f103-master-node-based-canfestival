#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
//#include "lcd.h"
#include "usart.h"	 
#include "canfestival_can.h" 
 #include "canfestival_timer.h" 
  #include "canfestival_master.h" 
//		#include "sync_dic.h" 
/************************************************
 ALIENTEK��ӢSTM32������ʵ��25
 CAN ʵ��   
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
 


 int main(void)
 {	 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		delay_init();
		uart_init(115200);//���ڳ�ʼ�������printf,�����ʱ���ƥ�� 
    
		 TIMConfig(TIM3,2000,72);//���ö�ʱ��
		 NVIC_Configuration();//����CAN�����ж�
		 CANOpen_can_config();

     setNodeId(&slave1_Data,0x01);  
     setState(&slave1_Data,Initialisation);
     setState(&slave1_Data,Preparing);
     setState(&slave1_Data,Operational);
		//printf("%s",slave1_Data->CurrentCommunicationState.csSDO);
			 
//	   unsigned long abortCode=0;
//     char size=4;
//     char sendData[4]={0};
//     
//     sendData[0]=0x03;
//     sendData[1]=0x03;
//     sendData[2]=0x03;
//     sendData[3]=0x03;
//		 
//	 CanRxMsg  RXMessage;
//		 printf("%s","׼���ռ�");
//	writeNetworkDict(&slave1_Data,2,0x6060,0,size,uint8,sendData,0);
////	while(getWriteResultNetworkDict(&slave1_Data,1,&abortCode)!=SDO_FINISHED)
////	{}
//			while(1)
	{
//		if (CAN_MessagePending(CAN1,CAN_FIFO0)!=0){
//			printf("%s","�õ���Ϣ");
//		CAN_Receive(CAN1,CAN_FIFO0,&RXMessage);
//			printf("%s","�ռ�����Ϣ");
//		writeNetworkDict(&slave1_Data,2,0x6060,0,size,uint8,sendData,0);
//	while(getWriteResultNetworkDict(&slave1_Data,1,&abortCode)!=SDO_FINISHED)
//	{}
//			printf("%s","��ɷ���");
//		}
	}
}



