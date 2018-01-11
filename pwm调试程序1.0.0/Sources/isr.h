//-------------------------------------------------------------------------*
// 文件名: Isr.h                                                           *
// 说  明: 中断头文件,本文件包含:                                          *            
//         所有中断函数头文件、外部函数声明及有关常量命名                  *
//-------------------------------------------------------------------------*
#ifndef ISR_H
#define ISR_H

  //1 头文件
  //1.1 包含通用头文件
  #include "MC9S08DZ60.h"       //映像寄存器地址头文件
  #include "Type.h"             //类型别名定义
  #include "MCUInit.h"          //芯片初始化头文件
  //1.2 包含面向硬件对象头文件  
  #include "SCI.h"              //SCI串行通信头文件
  #include "CAN.h"

  //2 在此添加引用全局变量声明
  extern CANMsg g_msgGet;
  extern CANMsg fsTest;
  extern uint8 fsable;
  extern uint16 timer_count;
  extern uint8 timer_off;
  extern uint8 status; 
#endif