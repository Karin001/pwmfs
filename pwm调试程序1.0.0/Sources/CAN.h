//-------------------------------------------------------------------------*
//�ļ���:  CAN.h (CANͨ��ͷ�ļ�)                                           *
//-------------------------------------------------------------------------*
#ifndef _CAN_H_             //��ֹ�ظ�����
#define _CAM_H_
    //1 ͷ�ļ�
    #include <MC9S08DZ60.h>  //ӳ��Ĵ�����ַͷ�ļ�
    #include "Type.h"        //���ͱ�������
   // #include "txdebug.h"
    
    //2.1 �жϺ궨��
    #define EnableCANReInt()  (CANRIER |= 0x01)
     #define EnableCANTeint()  (CANTIER = 0x01)
    #define DisableCANReInt() (CANRIER &= ~0x01)
    #define DisableCANTeint() (CANRIER = 0x00)  

    //2.2 �����궨��
    #define   SJW     3     // ͬ����ת��� (value between 1 and 4 Tq) 
                            //λʱ�䳤��(ͨ��Ƶ�ʵ���)���㹫ʽ��SYSTEM_CLOCK/BRP/(1+TSEG1+TSEG2)
    #define   BRP     8     // ������Ԥ��Ƶ�� (Value between 1 and 64)
    #define   TSEG1   4     // λʱ��ʱ���1 (value between 1 and 16 Tq)
    #define   TSEG2   3     // λʱ��ʱ���2 (value between 1 and 8 Tq)
     struct can_msg 
{
    unsigned int id;
    unsigned char ext;
    unsigned char RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;
};
    //3���ݱ��Ľṹ�����Ͷ���
    typedef struct CanMsg  
    {
        uint32 sendID;  //msg���ͷ�ID
        uint8 IDE;      //�Ƿ�Ϊ��չID��ʽ
        uint8 RTR;      //�Ƿ�ΪԶ��֡
        uint8 data[8];  //֡����
        uint8 dataLen;  //֡���ݳ���
        uint8 priority; //�������ȼ�
    }CANMsg;
    
    //4 CANģ��ͨ�Žӿ�
    //---------------------------------------------------------------------*
    //������: CANInit                                                      *
    //��  ��: ��ʼ��CANģ��                                                *
    //��  ��: ��                                                           *
    //��  ��: ��                                                           *
    //˵  ��:                                                              *
    //        (1)CANʱ��Դʹ��оƬ����ʱ�ӣ�����CANͨ��Ƶ��Ϊ800KHz        *
    //        (2)�ر��˲���������CAN���������еı���                       *
    //---------------------------------------------------------------------*
    void CANInit(void);

    //---------------------------------------------------------------------*
    //������: CANSendMsg                                                   *
    //��  ��: ͨ��CANģ�鷢��һ������                                      *
    //��  ��: CANMsg *sendMsgBuf �����͵ı���ָ��                          *
    //��  ��: uint8 ָʾ�Ƿ�ɹ�����                                       *
    //˵  ��: �ڷ�����ǰ��Ҫ����ͳ�ʼ��һ�����ı���������ΪCANMsg         *
    //---------------------------------------------------------------------*
    uint8 CANSendMsg(const CANMsg *sendMsgBuf);
    uint8 MSCANSendMsg(struct can_msg msg);
    //---------------------------------------------------------------------*
    //������: CANGetMsg                                                    *
    //��  ��: ����һ��CANģ�鱨��                                          *
    //��  ��: CANMsg *reMsgBuf ���ձ��Ļ�������ָ��                        *
    //��  ��: uint8 ָʾ�Ƿ�ɹ�����                                       *
    //˵  ��: ����֮ǰ�ȶ���һ�����ջ�����������ΪCANMsg                   *
    //---------------------------------------------------------------------*
    uint8 CANGetMsg(CANMsg *reMsgBuf);
#endif