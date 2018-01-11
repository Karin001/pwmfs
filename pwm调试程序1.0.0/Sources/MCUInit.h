//--------------------------------------------------------------------------*
// 文件名: MCUInit.h                                                        *
// 说  明: DZ60系统初始化头文件                                             *
//--------------------------------------------------------------------------*

#ifndef  MCUINIT_H
#define  MCUINIT_H
    
    //1 头文件
    #include "MC9S08DZ60.h"    //映像寄存器地址头文件

    //2 宏定义
    #define EnableInterrupts() asm("CLI")  //开放总中断
    #define DisableInterrupts()  asm("SEI")  //禁止总中断

    //3 函数声明
    void MCUInit(void);        //芯片初始化
    void IO_INIT(void);
    void TIMER1_init(void);
    void WATCHDOG_init(void);
    void WATCHDOG(void);
#endif