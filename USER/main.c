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
 ALIENTEK精英STM32开发板实验25
 CAN 实验   
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 


 int main(void)
 {	 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		delay_init();
		uart_init(115200);//串口初始化后才能printf,波特率必须匹配 
    
		 TIMConfig(TIM3,2000,72);//配置定时器
		 NVIC_Configuration();//设置CAN接受中断
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
//		 printf("%s","准备收集");
//	writeNetworkDict(&slave1_Data,2,0x6060,0,size,uint8,sendData,0);
////	while(getWriteResultNetworkDict(&slave1_Data,1,&abortCode)!=SDO_FINISHED)
////	{}
//			while(1)
	{
//		if (CAN_MessagePending(CAN1,CAN_FIFO0)!=0){
//			printf("%s","得到信息");
//		CAN_Receive(CAN1,CAN_FIFO0,&RXMessage);
//			printf("%s","收集到信息");
//		writeNetworkDict(&slave1_Data,2,0x6060,0,size,uint8,sendData,0);
//	while(getWriteResultNetworkDict(&slave1_Data,1,&abortCode)!=SDO_FINISHED)
//	{}
//			printf("%s","完成发送");
//		}
	}
}



