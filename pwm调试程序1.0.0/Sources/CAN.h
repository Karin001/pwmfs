//-------------------------------------------------------------------------*
//文件名:  CAN.h (CAN通信头文件)                                           *
//-------------------------------------------------------------------------*
#ifndef _CAN_H_             //防止重复定义
#define _CAM_H_
    //1 头文件
    #include <MC9S08DZ60.h>  //映像寄存器地址头文件
    #include "Type.h"        //类型别名定义
   // #include "txdebug.h"
    
    //2.1 中断宏定义
    #define EnableCANReInt()  (CANRIER |= 0x01)
     #define EnableCANTeint()  (CANTIER = 0x01)
    #define DisableCANReInt() (CANRIER &= ~0x01)
    #define DisableCANTeint() (CANRIER = 0x00)  

    //2.2 参数宏定义
    #define   SJW     3     // 同步跳转宽度 (value between 1 and 4 Tq) 
                            //位时间长度(通信频率倒数)计算公式：SYSTEM_CLOCK/BRP/(1+TSEG1+TSEG2)
    #define   BRP     8     // 波特率预分频器 (Value between 1 and 64)
    #define   TSEG1   4     // 位时间时间段1 (value between 1 and 16 Tq)
    #define   TSEG2   3     // 位时间时间段2 (value between 1 and 8 Tq)
     struct can_msg 
{
    unsigned int id;
    unsigned char ext;
    unsigned char RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;
};
    //3数据报文结构体类型定义
    typedef struct CanMsg  
    {
        uint32 sendID;  //msg发送方ID
        uint8 IDE;      //是否为扩展ID格式
        uint8 RTR;      //是否为远程帧
        uint8 data[8];  //帧数据
        uint8 dataLen;  //帧数据长度
        uint8 priority; //发送优先级
    }CANMsg;
    
    //4 CAN模块通信接口
    //---------------------------------------------------------------------*
    //函数名: CANInit                                                      *
    //功  能: 初始化CAN模块                                                *
    //参  数: 无                                                           *
    //返  回: 无                                                           *
    //说  明:                                                              *
    //        (1)CAN时钟源使用芯片总线时钟，设置CAN通信频率为800KHz        *
    //        (2)关闭滤波器，接收CAN总线上所有的报文                       *
    //---------------------------------------------------------------------*
    void CANInit(void);

    //---------------------------------------------------------------------*
    //函数名: CANSendMsg                                                   *
    //功  能: 通过CAN模块发送一个报文                                      *
    //参  数: CANMsg *sendMsgBuf 待发送的报文指针                          *
    //返  回: uint8 指示是否成功发送                                       *
    //说  明: 在发数据前，要定义和初始化一个报文变量，类型为CANMsg         *
    //---------------------------------------------------------------------*
    uint8 CANSendMsg(const CANMsg *sendMsgBuf);
    uint8 MSCANSendMsg(struct can_msg msg);
    //---------------------------------------------------------------------*
    //函数名: CANGetMsg                                                    *
    //功  能: 接收一个CAN模块报文                                          *
    //参  数: CANMsg *reMsgBuf 接收报文缓冲区首指针                        *
    //返  回: uint8 指示是否成功接收                                       *
    //说  明: 接收之前先定义一个接收缓冲区，类型为CANMsg                   *
    //---------------------------------------------------------------------*
    uint8 CANGetMsg(CANMsg *reMsgBuf);
#endif