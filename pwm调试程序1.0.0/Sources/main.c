//-------------------------------------------------------------------------*
// 工 程 名: CAN_Recv                                                      *
// 硬件连接: 连接串口1，用于向PC发送接收到的CAN数据                        *
// 程序描述: CAN模块中断方式接收CAN总线中的数据，并将数据通过串口发送给PC  *
// 目    的: 初步掌握CAN通信的基本知识                                     *
// 说    明: CAN通信频率选择为800k,使用SCI1通信速率为9600                  *
//----------------苏州大学飞思卡尔嵌入式系统实验室2010年-------------------*

#include "Includes.h"
//在此添加全局变量定义
CANMsg g_msgGet;                    //报文接收缓冲区
CANMsg fsTest;
struct can_msg msg;
uint8 fsable = 0;
      

 
uint8 timer_off = 0;
uint16 timer_count = 0;
uint8 status = 0;
void irq_INIT(void){
  IRQSC = 0x13;
}
void PWM_INIT(void)
{
    TPM2SC  =0x0E;   //BUS RATE=24MHZ,64DIV-375K
    TPM2C0SC=0x28; 
    TPM2CNTH=0x01;
    TPM2CNTL=0x77;    
    TPM2MOD=2500;  //PER
    //TPM2MODL=0x77;     
    TPM2C0V=800;  //DTY
    //TPM2C0VL=0x00; 
}
void Tsend(void)
{
  while(CANTFLG_TXE0==0);               // 等待缓冲器空闲
      
  CANTIDR0=0x00;                        // 报文
  CANTIDR1=0x00;
  CANTIDR2=0x00;
  CANTIDR3=0x00;

  #if DATA_REMOTE==0                 // 远程帧还是数据帧
  CANIDAR1=CANIDAR1&0XEF;
  #elif DATA_REMOTE==1
  CANIDAR1=CANIDAR1|0X10;
  #endif

  #if STA_EXT==0                        // 标准帧还是扩展帧
  CANIDAR1=CANIDAR1&0XF7;
  #elif STA_EXT==1
  CANIDAR1=CANIDAR1|0X08;
  #endif
                                        // 发送的数据
  CANTDSR0=0X01;
  CANTDSR1=0X01;
  CANTDSR2=0X01;                       
  CANTDSR3=0X01;
  CANTDSR4=0x01;
  CANTDSR5=0x01;
  CANTDSR6=0x01;
  CANTDSR7=0x01;         
                                
  CANTDLR=8;                   // 数据的长度
      
  CANTBSEL=0x01;                        // 选择Tx缓冲区
        
  CANTFLG=0x01;                         // 清除CAN0TFLG标志位
}
void main(void)
{
    //1 关总中断
     //CAN发送测试
/*fsTest.IDE = 1;
fsTest.RTR = 0;
fsTest.data[0] = 1;
fsTest.data[1] = 2;
fsTest.data[2] = 3;
fsTest.data[3] = 1;
fsTest.data[4] = 2;
fsTest.data[5] = 3;
fsTest.data[6] = 1;
fsTest.data[7] = 1;
fsTest.sendID =  0x123213;
fsTest.dataLen = 8;
fsTest.priority = 0;
  */

    DisableInterrupts();
    //2 模块初始化
    MCUInit();                      //2.1 芯片初始化
    SCIInit(1,SYSTEM_CLOCK,9600);   //2.2 UART模块初始化
    CANInit();                     //2.3 CAN模块初始化
    IO_INIT();                     //2.4 IO模块初始化
    PWM_INIT();
    //TIMER1_init();
    irq_INIT();
    WATCHDOG_init();                     
    //3 开放中断                           
   // EnableSCIReInt();               //3.1开放SCI接收中断
    EnableCANReInt();               //3.2开放CAN接收中断
    EnableInterrupts();             //3.3开放总中断
    
    //4 主循环          
    CANSendMsg(&fsTest);                                                                                                   
   // SCISendN(1,sizeof(sciMsg),sciMsg);//发送"Hello! World!"   
   //PTFD = 0x00;
   while(1) {
       
           
             
             WATCHDOG();
       
   }
    
}
