//[Includes.h]总头文件-----------------------------------------------------*
//本文件包含:                                                              *  
//    主函数(main)文件中用到的头文件、外部函数声明及有关常量命名           *
//-------------------------------------------------------------------------*
#ifndef _INCLUDES_H_
#define _INCLUDES_H_

//1 头文件
//1.1 包含通用头文件
#include "MC9S08DZ60.h"       //映像寄存器地址头文件
#include "Type.h"             //类型别名定义
#include "GeneralFun.h"       //通用函数头文件
#include "MCUInit.h" 

//1.2 包含面向硬件对象头文件
#include "SCI.h"        //串口通信构件
#include "CAN.h"        //CAN总线通信构件

//2 宏定义

//2.2 MCU芯片的有关定义
#define SYSTEM_CLOCK 16                  //系统总线频率(MHz)
//3 在此添加全局变量声明


#endif