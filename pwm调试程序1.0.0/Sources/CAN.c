#include "CAN.h"

#define setReg8(RegName, val)   (RegName = (byte)(val))
//---------------------------------------------------------------------*
//函数名: CANInit                                                      *
//功  能: 初始化CAN模块                                                *
//参  数: 无                                                           *
//返  回: 无                                                           *
//说  明:                                                              *
//        (1)CAN时钟源使用芯片总线时钟，设置CAN通信频率为800KHz        *
//        (2)关闭滤波器，接收CAN总线上所有的报文                       *
//---------------------------------------------------------------------*
void CANInit(void)
{
      /* CANCTL1: CANE=1,CLKSRC=0,LOOPB=0,LISTEN=0,BORM=0,WUPM=0,SLPAK=0,INITAK=0 */
  CANCTL1 = 0x80;                      /* Set the control register */
  /* CANCTL0: RXFRM=0,RXACT=0,CSWAI=0,SYNCH=0,TIME=0,WUPE=0,SLPRQ=0,INITRQ=1 */
  CANCTL0 = 0x01;                      /* Set the control register */
 CANIDAC_IDAM = 0x00;                 /* Set the acceptance mode */
  CANIDAR0 = 0xc7;                     /* Set the acceptance code, register CANIDAR0 */
  CANIDAR1 = 0xf5;                     /* Set the acceptance code, register CANIDAR1 */
  CANIDAR2 = 0xdc;                     /* Set the acceptance code, register CANIDAR2 */
  CANIDAR3 = 0x00;                     /* Set the acceptance code, register CANIDAR3 */
  CANIDAR4 = 0xc7;                     /* Set the acceptance code, register CANIDAR4 */
  CANIDAR5 = 0xf5;                     /* Set the acceptance code, register CANIDAR5 */
  CANIDAR6 = 0xdc;                     /* Set the acceptance code, register CANIDAR6 */
  CANIDAR7 = 0x00;                     /* Set the acceptance code, register CANIDAR7 */
  CANIDMR0 = 0x00;                     /* Set the acceptance mask, register CANIDMR0 */
  CANIDMR1 = 0x18;                     /* Set the acceptance mask, register CANIDMR1 */
  CANIDMR2 = 0x00;                     /* Set the acceptance mask, register CANIDMR2 */
  CANIDMR3 = 0x00;                     /* Set the acceptance mask, register CANIDMR3 */
  CANIDMR4 = 0x00;                     /* Set the acceptance mask, register CANIDMR4 */
  CANIDMR5 = 0x18 ;                     /* Set the acceptance mask, register CANIDMR5 */
  CANIDMR6 = 0x00;                     /* Set the acceptance mask, register CANIDMR6 */
  CANIDMR7 = 0x00;                     /* Set the acceptance mask, register CANIDMR7 */
  
  /* CANBTR0: SJW1=0,SJW0=1,BRP5=0,BRP4=0,BRP3=0,BRP2=0,BRP1=1,BRP0=0 */
  CANBTR0 = 0x44;                      /* Set the device timing register */
  /* CANBTR1: SAMP=0,TSEG22=0,TSEG21=1,TSEG20=1,TSEG13=0,TSEG12=1,TSEG11=1,TSEG10=1 */
  CANBTR1 = 0x37;                      /* Set the device timing register */
  CANCTL1_CLKSRC = 0x01;               /* Select the clock source from bus clock */
  CANCTL0_INITRQ = 0x00;               /* Start device */
  while(CANCTL1_INITAK) {}   
  while(0==CANCTL0_SYNCH);         /* Wait for enable */
               
  /* CANCTL0: RXFRM=0,RXACT=0,CSWAI=0,SYNCH=0,TIME=0,WUPE=0,SLPRQ=0,INITRQ=1 */

  /* CANRFLG: WUPIF=1,CSCIF=1,RSTAT1=1,RSTAT0=1,TSTAT1=1,TSTAT0=1,OVRIF=1 */
  CANRFLG |= 0xFE;                     /* Reset error flags */
  /* CANRIER: WUPIE=0,CSCIE=1,RSTATE1=1,RSTATE0=1,TSTATE1=1,TSTATE0=1,OVRIE=0,RXFIE=1 */
  CANRIER = 0x7D;                      /* Enable interrupts */
}

//---------------------------------------------------------------------*
//函数名: CANSendMsg                                                   *
//功  能: 通过CAN模块发送一个报文                                      *
//参  数: CANMsg *sendMsgBuf 待发送的报文指针                          *
//返  回: uint8 指示是否成功发送                                       *
//说  明: 在发数据前，要定义和初始化一个报文变量，类型为CANMsg         *
//---------------------------------------------------------------------*
uint8 MSCANSendMsg(struct can_msg msg)
{

  unsigned char n_tx_buf, i;
  
  // Checks len validity
  if(msg.len > 8)
    return(0);

  // Checks synchronization to CAN bus
  if(!(CANCTL0&0x10))
    return(0);

  n_tx_buf = 0;
  do
  {
    // Looks for a free buffer
    CANTBSEL=CANTFLG;
    n_tx_buf=CANTBSEL;
  }while(!n_tx_buf); 
  
  // Write Identifier
  CANTIDR0 = (unsigned char)(msg.id>>3);
  CANTIDR1 = (unsigned char)(msg.id<<5);
  
  if(msg.RTR)
    // RTR=Recessive
    CANTIDR1 |= 0x10;
  if(msg.ext) 
    CANTIDR1_IDE = 1;
    
  // Write Data Segment
  for(i = 0; i < msg.len; i++)
    *((&CANTDSR0)+i) = msg.data[i];
    
  // Write Data Length
  CANTDLR = msg.len; 
  
  // Write Priority
  CANTTBPR = msg.prty;
  
  // Clear TXx Flag (buffer ready to transmission)
  CANTFLG = n_tx_buf;
  
  return(1);
  
}
uint8 CANSendMsg(const CANMsg *sendMsgBuf)
{
    uint8 txEmptyBuf; //空闲发送缓冲区掩码
    uint8 i;

    // 检查数据长度
    if(sendMsgBuf->dataLen > 8)
    {
        return 0;
    }
    // 检查总线时钟
    if(0==CANCTL0_SYNCH)
    {
        return 0;
    } 

    txEmptyBuf = 0;
    do
    {
        // 寻找空闲的缓冲器
        CANTBSEL=CANTFLG;
        txEmptyBuf=CANTBSEL;
    }
    while(!txEmptyBuf); 

    // 写入标识符
    if(1 == sendMsgBuf->IDE)
    {
        //扩展格式ID
        CANTIDR0 = (uint8)(sendMsgBuf->sendID>>21);
        CANTIDR1_ID15 = (uint8)(sendMsgBuf->sendID>>15);
        CANTIDR1_ID16 = (uint8)(sendMsgBuf->sendID>>16);
        CANTIDR1_ID17 = (uint8)(sendMsgBuf->sendID>>17);
        CANTIDR1_ID18 = (uint8)(sendMsgBuf->sendID>>18);
        CANTIDR1_ID19 = (uint8)(sendMsgBuf->sendID>>19);
        CANTIDR1_ID20 = (uint8)(sendMsgBuf->sendID>>20);
        CANTIDR2 = (uint8)(sendMsgBuf->sendID>>7);
        CANTIDR3 = (uint8)(sendMsgBuf->sendID<<1);
        CANTIDR1_SRR=sendMsgBuf->RTR;
        CANTIDR1_IDE=1;   
    }             
    else
    {
        //标准ID格式 
        return 0; 
    }

    //判断是否为数据帧
    if(0==sendMsgBuf->RTR  )
    {
        // 写入数据帧
        for(i = 0; i < sendMsgBuf->dataLen; i++)
        {
            *((&CANTDSR0)+i) = sendMsgBuf->data[i];
        }
        // 写入数据长度
        CANTDLR = sendMsgBuf->dataLen;         
    }
    else
    {
        //远程帧
        CANTDLR = 0;
    }

    // 写入优先级
    CANTTBPR = sendMsgBuf->priority;
    // 清TXx标志，缓冲器准备发送
    CANTFLG = txEmptyBuf;//相关位写1清零
    return 1;
}

//---------------------------------------------------------------------*
//函数名: CANGetMsg                                                    *
//功  能: 接收一个CAN模块报文                                          *
//参  数: CANMsg *reMsgBuf 接收报文缓冲区首指针                        *
//返  回: uint8 指示是否成功接收                                       *
//说  明: 接收之前先定义一个接收缓冲区，类型为CANMsg                   *
//---------------------------------------------------------------------*
uint8 CANGetMsg(CANMsg *reMsgBuf)
{
    uint8 i;
    uint32 sendIDH= 0;
    uint32 sendIDL= 0;
//    uint32 idTemp;
    // 检测接收标志
    if(!(CANRFLG&0x01))
    return 0;
  
    // 检测 CAN协议报文模式 （一般/扩展） 标识符
    // 读出标识符
    if(0 == (CANRIDR1&0x08))
    {  
         //收到标准ID格式
        return 0;
        
    } 
    else
    {
        //扩展格式ID
        sendIDH =(uint32)(CANRIDR0<<6)|
        (uint32)((CANRIDR1>>5)<<3)|
        (uint32)((CANRIDR1<<5)>>5);
        sendIDL =(uint32)(CANRIDR2<<7)|
        (uint32)(CANRIDR3>>1);   
        reMsgBuf->sendID = (sendIDH<<15) |sendIDL ;           

        reMsgBuf->RTR=CANRIDR3_RTR;
        reMsgBuf->IDE=1; 
    }

    //判断是否为数据帧
    if(0==reMsgBuf->RTR)
    {
        // 读取数据帧长度 
        reMsgBuf->dataLen = CANRDLR_DLC;

        // 读取数据
        for(i = 0; i < reMsgBuf->dataLen&&i<8; i++)
        reMsgBuf->data[i] = *((&CANRDSR0)+i);
    }
    else
    {
        //远程帧
        reMsgBuf->dataLen = 0;
    }

    // 清 RXF 标志位 (缓冲器准备接收)
    CANRFLG = 0x01;               //相关位写1清零
    
    return 1;
}