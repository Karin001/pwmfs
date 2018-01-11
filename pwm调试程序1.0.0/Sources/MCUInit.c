//--------------------------------------------------------------------------*
// 文件名:  MCUInit.c (DZ60系统初始化子程序)                                *
// 说  明: 系统初始化设置,设置MCGC1和MCGC2寄存器,SOPT1和SOPT2寄存器设置,由外*
//         部晶振f = 4MHz,产生内部总线时钟频率f = 16MHz                     *
//--------------------------------------------------------------------------*
#include "MCUInit.h"    //映像寄存器地址头文件

void MCUInit(void)
{
/* disable COP */
  SOPT1 = 0x00;     /* disable COP, enable stop mode */

  /* Init Clock, Use PLL Engaged External mode, from 8MHz crystal -> 16 MHz bus */  
  MCGC2 = 0x36;
  while (!MCGSC_OSCINIT);

  MCGC1 = 0xB8;
  while (!MCGSC_IREFST);       
  while(MCGSC_CLKST != 2);
  
  MCGC1 = 0x90;
  MCGC3 = 0x44;
  while(!MCGSC_PLLST);

  while (!MCGSC_LOCK);

  MCGC1 = 0x10;
  while(MCGSC_CLKST != 3);
  
  MCGC2_BDIV = 0; 
}
void IO_INIT(void)
{

    PTED  =0x00;  //  Hignt 
    PTEDD =0xFF;  //   out LED 
    PTFD = 0xFF;
    PTFDD = 0XFF;
    
}
void TIMER1_init(void) 
{
// Timer1 Overflow every 3ms
  TPM1MODH = 0xc3;
  TPM1MODL = 0x50;
  
  // Enable Interrupt Overflow Timer1 and 
  // select bus clock as clock source. Prescaler Divisor = 1
  TPM1SC = 0x48;
}  
void WATCHDOG_init() 
{
    SOPT1 = 0xc0;
    SOPT2 = 0x00;
}

void WATCHDOG()
{
 
      SRS = 0x55;                         /* Reset watchdog counter write 55, AA */
      SRS = 0xAA;
}