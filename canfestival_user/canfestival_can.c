#include "stm32f10x.h"
#include "canfestival_can.h"
#include "canfestival.h"



/* CANOPEN�ֵ� */
//extern CO_Data slave1Objdict_Data;
extern CO_Data slave1_Data;
/* ����:	GPIO����
	 ����:	��
	 ����ֵ:��
 */
static void gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);		//��ʼ��IO
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��IO
    
}

/* ����:	�ж�Ƕ�׿���������
	 ����:	��
	 ����ֵ:��
 */
static void nvic_config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* ����CAN�����жϣ���ռ���ȼ�2����վ���ȼ�2 */
  	//NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;//????
		NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	/* ��ʼ���ж� */
	NVIC_Init(&NVIC_InitStructure);
}

/* ����:	CAN���߹���������
	 ����:	��
	 ����ֵ:��
 */
static void can_filter_config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	/* ���ù�����0�飬���óɱ�׼��ʶ���ҵ�7λ��Ϊ0ʱ���� */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;						/* ���ù�������0 */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		/* ����ģʽ */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	/* 32λģʽ */
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;					/* ��CANOpen�б�׼��ʶ���ĵ�7λ��ʾ�ڵ�ID */
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;					/* ��CANOpen��ֻ�ñ�׼��ʶ��������֡/Զ��֡���� */
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;						/* ���ڵ�IDΪ0 */
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;						/* ��׼֡ */
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;	/* ������������FIFO0 */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;					/* ʹ�ܹ����� */
	CAN_FilterInit(&CAN_FilterInitStructure);
}

/* ����:	can��������
	 ����:	��
	 ����ֵ:��
 */
void CANOpen_can_config(void)
{
	CAN_InitTypeDef CAN_InitStructure;

	/* ����IO */
	gpio_config();

	/* �ж�Ƕ�׿��������� */
	nvic_config();

	/* ����CAN����ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	/* CAN1Ĭ�ϲ��� */
	CAN_DeInit(CAN1);

	/* ���ṹ������Ĭ�ϲ��� */
	CAN_StructInit(&CAN_InitStructure);

	/* �ر�ʱ�䴥��ģʽ */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	/* �ر��Զ����߹��� */
	CAN_InitStructure.CAN_ABOM = ENABLE;
	/* �ر��Զ����� */
	CAN_InitStructure.CAN_AWUM = ENABLE;
	/* �Զ��ش� */
	CAN_InitStructure.CAN_NART = DISABLE;
	/* ��ֹFIFO���ʱ����ԭ���� */
	CAN_InitStructure.CAN_RFLM = DISABLE;
	/* �ر����ȼ�ȡ����ID */
	CAN_InitStructure.CAN_TXFP = DISABLE;
	/* ����ģʽ */
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

	/* ���ò�����:36MHz/9/(6+1+1)=500kbps */
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_1tq;
	CAN_InitStructure.CAN_Prescaler = 9;

	/* ��ʼ��CAN���� */
	CAN_Init(CAN1, &CAN_InitStructure);

	/* CAN���߹��������� */
	can_filter_config();

	/* ���չ����ж� */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

/* can���߽����жϻص����� */
//void CAN1_RX1_IRQHandler(void)
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	printf("%s","�����жϷ���");
	CanRxMsg message;
	Message Rx_Message;
	/* ������Ϣ */
	CAN_Receive(CAN1, CAN_FIFO0, &message);
	
	/* ��װcanopen���ݰ� */
	Rx_Message.cob_id = message.StdId;						/* ������ͽڵ�ID */
	Rx_Message.rtr = (message.RTR == CAN_RTR_DATA) ? 0 : 1;	/* ��ʶ������ */
	Rx_Message.len = message.DLC;							/* ���ݰ����� */
	memcpy(Rx_Message.data, message.Data, message.DLC);		/* ���� */

	/* canopen���ݰ����䴦���� */
	canDispatch(&slave1_Data, &Rx_Message);
}

/* ����:	CAN�������ݺ���
	 ����:	notused can���߶˿�
			message canopen���ݰ�
	����ֵ:	0 �ɹ�
			1 ʧ��
 */
uint8_t canSend(CAN_PORT notused, Message *message)
{
	uint32_t i = 0xFFFFFF;
	CanTxMsg TxMessage;
	uint8_t TransmitMailbox = 0;

	/* ��װCAN���ݰ� */
	TxMessage.DLC = message->len;							/* ���ݳ��� */
	memcpy(TxMessage.Data, message->data, message->len);	/* ���� */
	TxMessage.IDE = CAN_ID_STD;								/* ��׼ID */
	TxMessage.StdId = message->cob_id;						/* ��ʶ�� */
	TxMessage.RTR = (message->rtr == CAN_RTR_DATA) ? 0 : 2;	/* ����֡ */

	/* �������ݰ� */
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	/* �ȴ����ͳɹ� */
	while((CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK) && --i);

	/* �ɹ�0 ��ʱ1 */
	return (i != 0) ? 0 : 1;
} 
