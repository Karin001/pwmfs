//-------------------------------------------------------------------------*
// 文件名:  GeneralFun.h （通用函数头文件）                                *
// 说  明:  通用函数头文件                                                 *
//-------------------------------------------------------------------------*
#ifndef GENERALFUN_H          //防止重复定义
#define GENERALFUN_H
  //1 头文件
	#include "type.h"           //类型定义头文件
	//2 函数声明
	void Delay(uint16 count);   //延时
	//3 寄存器位操作宏定义
    #define BSET(bit,Register) ((Register)|= (1<<(bit)))   //设置寄存器中某一位为1
    #define BCLR(bit,Register) ((Register) &= ~(1<<(bit))) //设置寄存器中某一位为0
    #define BGET(bit,Register) (((Register) >> (bit)) & 1) //得到寄存器中某一位状态  
 #endif

