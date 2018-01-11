//-------------------------------------------------------------------------*
//文件名:  SCI.h (串行通信头文件)                                          *
//-------------------------------------------------------------------------*
#ifndef _SCI_H_             //防止重复定义
#define _SCI_H_
    //1 头文件
    #include <MC9S08DZ60.h>  //映像寄存器地址头文件
    #include "Type.h"        //类型别名定义
    //2 中断宏定义
    #define EnableSCIReInt()  SCI1C2 |=  (1 << 5)  //令SCC2.5=1,开放SCI接收中断
    #define DisableSCIReInt() SCI1C2 &= ~(1 << 5)  //令SCC2.5=0,禁止SCI接收中断 

    //3 外用SCI通信函数声明
    //---------------------------------------------------------------------*
    //函数名: SCIInit                                                      *
    //功  能: 初始化SCIx模块。x代表1，2                                    *
    //参  数: uint8 SCINo: 第SCINo个SCI模块。其中SCINo取值为1，2           *
    //                     如果SCINo大于2，则认为是2                       *
    //        uint8 sysclk: 系统总线时钟，以MHz为单位                      *
    //        uint16 baud:   波特率，如 4800，9600，19200，3840            *
    //                      其他的波特率在MC9SO8DZ60的评估板上没有测试过， *
    //                      若要使用该函数，请自行测试，一般来说，速度慢一 *
    //                      点，通信会更稳定                               *
    //返  回: 无                                                           *
    //说  明: SCINo=1表示使用SCI1模块，依此类推。                          *
    //---------------------------------------------------------------------*
    void SCIInit(uint8 SCINo, uint8 sysclk, uint16 baud);

    //---------------------------------------------------------------------*
    //函数名: SCISend1                                                     *
    //功  能: 串行发送1个字节                                              *
    //参  数: uint8 SCINo: 第SCINo个SCI模块，其中SCINo取值为1，2           *
    //        uint8 ch:    要发送的字节                                    *
    //返  回: 无                                                           *
    //说  明: SCINo=1表示使用SCI1模块，依此类推                            *
    //---------------------------------------------------------------------*
    void SCISend1(uint8 SCINo, uint8 ch);

    //---------------------------------------------------------------------*
    //函数名: SCISendN                                                     *
    //功  能: 串行发送N个字节                                              *
    //参  数: uint8 SCINo: 第SCINo个SCI模块，其中SCINo取值为1，2           *
    //        uint8 n:      发送的字节数                                   *
    //        uint8 ch[]:   待发送的数据                                   *
    //返  回: 无                                                           *
    //说  明: SCINo=1表示使用SCI1模块，依此类推                            *
    //        调用了SCISend1函数                                           *
    //---------------------------------------------------------------------*
    void SCISendN(uint8 SCINo, uint8 n, uint8 ch[]);

    //---------------------------------------------------------------------*
    //函数名: SCIRe1                                                       *
    //功  能: 从串口接收1个字节的数据                                      *
    //参  数: uint8 SCINo: 第SCINo个SCI模块，其中SCINo取值为1，2           *
    //返  回: 接收到的数(若接收失败，返回0xff)                             *
    //        uint8 *p:     接收成功标志的指针(0表示成功，1表示不成功)     *
    //说  明: 参数*p带回接收标志，*p = 0，收到数据；*p = 1，未收到数据     *
    //说  明: SCINo=1表示使用SCI1模块，依此类推                            *
    //---------------------------------------------------------------------*
    uint8 SCIRe1(uint8 SCINo, uint8 *p);

    //---------------------------------------------------------------------*
    //函数名: SCIReN                                                       *
    //功  能: 从串口接收N个字节的数据                                      *
    //参  数: uint8 SCINo: 第SCINo个SCI模块，其中SCINo取值为1，2           *
    //        uint8 n:      要接收的字节数                                 *
    //        uint8 ch[]:   存放接收数据的数组                             *
    //返  回: 接收标志= 0 接收成功，= 1 接收失败                           *
    //说  明: SCINo=1表示使用SCI1模块，依此类推                            *
    //        调用了SCIRe1函数                                             *
    //---------------------------------------------------------------------*
    uint8 SCIReN(uint8 SCINo, uint8 n, uint8 ch[]);

    //---------------------------------------------------------------------*
    //函数名: SCISendString                                                *
    //功  能: 串口传输字符串                                               *
    //参  数: uint8 SCINo: 第SCINo个SCI模块，其中SCINo取值为1，2           *
    //        char *p: 要传输的字符串的指针                                *
    //返  回: 无                                                           *
    //说  明: 字符串以'\0'结束                                             *
    //        调用了SCISend1 函数                                          *
    //---------------------------------------------------------------------*
    void SCISendString(uint8 SCINo,char *p);


    //4 寄存器有关的宏定义
    //示例波特率的宏定义
    #define UART_BAUD                     9600     //波特率值
    //标志位掩码的定义
    //控制寄存器1各个位的掩码
    #define DZ60_SCI_CTR1_LOOPS           (0x80)   //SCI控制寄存器1循环模式选择掩码
    #define DZ60_SCI_CTR1_WAIT            (0x40)   //SCI控制寄存器1等待模式选择掩码
    #define DZ60_SCI_CTR1_RECV_SOURCE     (0x20)   //SCI控制寄存器1接收器信号源选择掩码
    #define DZ60_SCI_CTR1_DATA_MODE       (0x10)   //SCI控制寄存器1帧格式选择掩码
    #define DZ60_SCI_CTR1_WAKEUP          (0x08)   //SCI控制寄存器1接收器唤醒模式选择掩码
    #define DZ60_SCI_CTR1_IDLE            (0x04)   //SCI控制寄存器1空闲线类型选择掩码
    #define DZ60_SCI_CTR1_PARITY_ENABLE   (0x02)   //SCI控制寄存器1奇偶校验使能掩码
    #define DZ60_SCI_CTR1_PARITY_TYPE     (0x01)   //SCI控制寄存器1奇偶校验类型选择掩码
    //控制寄存器2各个位的掩码
    #define DZ60_SCI_CTR2_TRANSINT_ENABLE (0x80)   //SCI控制寄存器2发送中断使能选择掩码
    #define DZ60_SCI_CTR2_SEND_ENABLE     (0x40)   //SCI控制寄存器2发送完成中断使能选择掩码
    #define DZ60_SCI_CTR2_RECVINT_ENABLE  (0x20)   //SCI控制寄存器2接收中断使能选择掩码
    #define DZ60_SCI_CTR2_IDLE            (0x10)   //SCI控制寄存器2空闲线中断使能选择掩码
    #define DZ60_SCI_CTR2_TRANS_ENABLE    (0x08)   //SCI控制寄存器2发送器使能选择掩码
    #define DZ60_SCI_CTR2_RECV_ENABLE     (0x04)   //SCI控制寄存器2接收器使能选择掩码
    #define DZ60_SCI_CTR2_WAKEUP          (0x02)   //SCI控制寄存器2接收器唤醒控制选择掩码
    #define DZ60_SCI_CTR2_SEND_BREAK      (0x01)   //SCI控制寄存器2中止符发送使能选择掩码
    //状态寄存器1各个位的掩码
    #define DZ60_SCI_S1_TRANS_EMPTY       (0x80)   //SCI状态寄存器1发送数据寄存器空标志位掩码
    #define DZ60_SCI_S1_TRANS_COMPLETE    (0x40)   //SCI状态寄存器1发送完成标志位掩码
    #define DZ60_SCI_S1_RECV_FULL         (0x20)   //SCI状态寄存器1接收数据寄存器满标志位掩码
    #define DZ60_SCI_S1_IDLE              (0x10)   //SCI状态寄存器1空闲线标志位掩码
    #define DZ60_SCI_S1_RECV_OVERRUN      (0x08)   //SCI状态寄存器1接收溢出标志位掩码
    #define DZ60_SCI_S1_NOISE             (0x04)   //SCI状态寄存器1噪声标志位掩码
    #define DZ60_SCI_S1_FRAM_ERROR        (0x02)   //SCI状态寄存器1帧格式错误标志位掩码
    #define DZ60_SCI_S1_PARITY_ERROR      (0x01)   //SCI状态寄存器1奇偶校验错误标志位掩码

    //DZ60的SCI模块相关寄存器的定义
    //x=1表示SCI1模块 x=2表示SCI2模块
    //SCI的各寄存器定义,其中x=1表示SCI1端口,依此类推
    //波特率高位寄存器
    #define DZ60_SCI_BDH(x)  (*(vuint8 *)(0x00000038+(x-1)*8))
    //波特率低位寄存器
    #define DZ60_SCI_BDL(x)  (*(vuint8 *)(0x00000039+(x-1)*8))
    //控制寄存器1
    #define DZ60_SCI_C1(x)   (*(vuint8 *)(0x0000003A+(x-1)*8))
    //控制寄存器2
    #define DZ60_SCI_C2(x)   (*(vuint8 *)(0x0000003B+(x-1)*8))
    //状态寄存器1
    #define DZ60_SCI_S1(x)   (*(vuint8 *)(0x0000003C+(x-1)*8))
    //状态寄存器2
    #define DZ60_SCI_S2(x)   (*(vuint8 *)(0x0000003D+(x-1)*8))
    //控制寄存器3
    #define DZ60_SCI_C3(x)   (*(vuint8 *)(0x0000003E+(x-1)*8))
    //数据寄存器
    #define DZ60_SCI_D(x)    (*(vuint8 *)(0x0000003F+(x-1)*8))

#endif