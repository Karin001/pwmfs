//-------------------------------------------------------------------------*
//文  件  名:  isr.c （DZ60中断处理函数文件）                              *
//说      明:  中断处理函数                                                *
//本文件包含:                                                              *  
//           (1)isrDummy:  空白中断处理程序                                *
//           (2)SCI1_Recv: SCI1中断处理程序                                *
//           (3)SCI2_Recv: SCI2中断处理程序                                *
//硬件连接: 无                                                             *
//-------------------------------------------------------------------------*
//头文件

#include "isr.h"

 uint8 tflg;
 uint8 rflg;
//SCI1接收中断函数
interrupt void SCI1_Recv(void)
{    
    uint8 i;
    uint8 SerialBuff[1];     		     //存放接收数据的数组
    
    DisableInterrupts();                 //禁止总中断
    
    i = SCIReN(1,1,SerialBuff);          //等待接收1个数据
    if (i == 0) SCISendN(1,1,SerialBuff);//发送接到的数据
    
    EnableInterrupts();                  //开放总中断
}

//SCI2接收中断函数
interrupt void SCI2_Recv(void)
{    
    uint8 i;
    uint8 SerialBuff[1];     		     //存放接收数据的数组
    
    DisableInterrupts();                 //禁止总中断
    
    i = SCIReN(2,1,SerialBuff);          //等待接收1个数据
    if (i == 0) SCISendN(2,1,SerialBuff);//发送接到的数据
    
    EnableInterrupts();                  //开放总中断
}

//CAN发送中断函数
interrupt void isrCAN_Send(void)
{    
    DisableInterrupts();                 //禁止总中断
 
    EnableInterrupts();                  //开放总中断
}

//CAN接收中断函数
interrupt void isrCAN_Recv(void)
{    
    DisableInterrupts();                 //禁止总中断
       
         
      
    CANGetMsg(&g_msgGet);
    fsTest.data[0] = g_msgGet.data[0]; 
    fsable = 1;
   
    
    if((g_msgGet.sendID  == 0x18FEEE00))
      {
            
         if(g_msgGet.data[0]==0){
           TPM2C0SC &= 0xf3;
           PTDD = 0xff;
           PTDDD = 0xff; 
         }else if(g_msgGet.data[0]>=100){
           TPM2C0SC &= 0xf3;
           PTDD = 0x00;
           PTDDD = 0xff;
            
         }else {
           TPM2SC  =0x0E;   //BUS RATE=24MHZ,64DIV-375K
    TPM2C0SC=0x28; 
    TPM2CNTH=0x01;
    TPM2CNTL=0x77;    
    TPM2MOD=2500;  //PER
    //TPM2MODL=0x77;     
   
         
           TPM2C0V =  (100-g_msgGet.data[0])*25;
         }
           
         
      } 
      
    g_msgGet.data[0] = 0x00;
    EnableInterrupts();                  //开放总中断
}

//CAN错误中断函数
interrupt void isrCAN_Err(void)
{    
    DisableInterrupts();                 //禁止总中断
 
    EnableInterrupts();                  //开放总中断
}

//CAN唤醒中断函数
interrupt void isrCAN_Wu(void)
{    
    DisableInterrupts();                 //禁止总中断

    EnableInterrupts();                  //开放总中断
}

//此处为用户新定义中断处理函数的存放处


//未定义的中断处理函数,本函数不能删除
interrupt void isrDummy(void)
{
    
}
interrupt void canwrong(void)
{
   tflg = CANTFLG;
   rflg = CANRFLG; 
}
 /////////////////////////////////////////////////////////////////////////////////////////
// Timer1_overflow
// --------------------------------------------------------------------------------------
// TIMER1 Overflow Interrupt 
/////////////////////////////////////////////////////////////////////////////////////////
interrupt void irq(void){
       
       
       
          //PTFD = 0xff;
          IRQSC |= 0x04;
       
}

interrupt void Timer1_overflow (void)
{
   //定时2s
  timer_count++;
  if(timer_count>700) 
  {
      timer_off = 1;
      timer_count = 0;
  }
  
  TPM1SC &=0x7F;
    
}   
//中断处理子程序类型定义
typedef void( *ISR_func_t)(void);

//中断矢量表，如果需要定义其它中断函数，请修改下表中的相应项目
const ISR_func_t ISR_vectors[] @0xFFC0 = 
{
    isrDummy,     //Vacmp2     0x0000FFC0   模拟比较器2中断向量
    isrDummy,     //Vacmp1     0x0000FFC2   模拟比较器1中断向量
    isrDummy,     //Vcantx     0x0000FFC4   CAN发送中断向量
    isrCAN_Recv,  //Vcanrx     0x0000FFC6   CAN接收中断向量
    canwrong,     //Vcanerr    0x0000FFC8   CAN错误中断向量
    isrDummy,     //Vcanwu     0x0000FFCA   CAN唤醒中断向量
    isrDummy,     //Vrtc       0x0000FFCC   实时时钟中断向量
    isrDummy,     //Viic       0x0000FFCE   IIC控制中断向量
    isrDummy,     //Vadc       0x0000FFD0   ADC中断向量
    isrDummy,     //Vport      0x0000FFD2   端口管脚中断向量
    isrDummy,     //Vsci2tx    0x0000FFD4   SCI2发送中断向量
    SCI2_Recv,    //Vsci2rx    0x0000FFD6   SCI2接收中断向量
    isrDummy,     //Vsci2err   0x0000FFD8   SCI2错误中断向量
    isrDummy,     //Vsci1tx    0x0000FFDA   SCI1发送中断向量
    SCI1_Recv,    //Vsci1rx    0x0000FFDC   SCI1接收中断向量
    isrDummy,     //Vsci1err   0x0000FFDE   SCI1错误中断向量
    isrDummy,     //Vspi       0x0000FFE0   SPI中断向量
    isrDummy,     //Vtpm2ovf   0x0000FFE2   TPM2溢出中断向量
    isrDummy,     //Vtpm2ch1   0x0000FFE4   TPM2通道1中断向量
    isrDummy,     //Vtpm2ch0   0x0000FFE6   TPM2通道0中断向量
    Timer1_overflow,//Vtpm1ovf   0x0000FFE8   TPM1溢出中断向量
    isrDummy,     //Vtpm1ch5   0x0000FFEA   TPM1通道5中断向量
    isrDummy,     //Vtpm1ch4   0x0000FFEC   TPM1通道4中断向量
    isrDummy,     //Vtpm1ch3   0x0000FFEE   TPM1通道3中断向量
    isrDummy,     //Vtpm1ch2   0x0000FFF0   TPM1通道2中断向量
    isrDummy,     //Vtpm1ch1   0x0000FFF2   TPM1通道1中断向量         
    isrDummy,     //Vtpm1ch0   0x0000FFF4   TPM1通道0中断向量      
    isrDummy,     //Vlol       0x0000FFF6   锁定丢失中断向量                       
    isrDummy,     //Vlvd       0x0000FFF8   低压警告中断向量                    
    irq,     //Virq       0x0000FFFA   IRQ引脚中断向量                    
    isrDummy,     //Vswi       0x0000FFFC   软件中断 
    //isrDummy      //Vreset     0x0000FFFE   复位中断向量，复位源可能为看门狗，非法地址等等
};                                    
                                      
                                      
                                      
                                      
                                      
