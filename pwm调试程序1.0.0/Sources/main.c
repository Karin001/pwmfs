//-------------------------------------------------------------------------*
// �� �� ��: CAN_Recv                                                      *
// Ӳ������: ���Ӵ���1��������PC���ͽ��յ���CAN����                        *
// ��������: CANģ���жϷ�ʽ����CAN�����е����ݣ���������ͨ�����ڷ��͸�PC  *
// Ŀ    ��: ��������CANͨ�ŵĻ���֪ʶ                                     *
// ˵    ��: CANͨ��Ƶ��ѡ��Ϊ800k,ʹ��SCI1ͨ������Ϊ9600                  *
//----------------���ݴ�ѧ��˼����Ƕ��ʽϵͳʵ����2010��-------------------*

#include "Includes.h"
//�ڴ����ȫ�ֱ�������
CANMsg g_msgGet;                    //���Ľ��ջ�����
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
  while(CANTFLG_TXE0==0);               // �ȴ�����������
      
  CANTIDR0=0x00;                        // ����
  CANTIDR1=0x00;
  CANTIDR2=0x00;
  CANTIDR3=0x00;

  #if DATA_REMOTE==0                 // Զ��֡��������֡
  CANIDAR1=CANIDAR1&0XEF;
  #elif DATA_REMOTE==1
  CANIDAR1=CANIDAR1|0X10;
  #endif

  #if STA_EXT==0                        // ��׼֡������չ֡
  CANIDAR1=CANIDAR1&0XF7;
  #elif STA_EXT==1
  CANIDAR1=CANIDAR1|0X08;
  #endif
                                        // ���͵�����
  CANTDSR0=0X01;
  CANTDSR1=0X01;
  CANTDSR2=0X01;                       
  CANTDSR3=0X01;
  CANTDSR4=0x01;
  CANTDSR5=0x01;
  CANTDSR6=0x01;
  CANTDSR7=0x01;         
                                
  CANTDLR=8;                   // ���ݵĳ���
      
  CANTBSEL=0x01;                        // ѡ��Tx������
        
  CANTFLG=0x01;                         // ���CAN0TFLG��־λ
}
void main(void)
{
    //1 �����ж�
     //CAN���Ͳ���
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
    //2 ģ���ʼ��
    MCUInit();                      //2.1 оƬ��ʼ��
    SCIInit(1,SYSTEM_CLOCK,9600);   //2.2 UARTģ���ʼ��
    CANInit();                     //2.3 CANģ���ʼ��
    IO_INIT();                     //2.4 IOģ���ʼ��
    PWM_INIT();
    //TIMER1_init();
    irq_INIT();
    WATCHDOG_init();                     
    //3 �����ж�                           
   // EnableSCIReInt();               //3.1����SCI�����ж�
    EnableCANReInt();               //3.2����CAN�����ж�
    EnableInterrupts();             //3.3�������ж�
    
    //4 ��ѭ��          
    CANSendMsg(&fsTest);                                                                                                   
   // SCISendN(1,sizeof(sciMsg),sciMsg);//����"Hello! World!"   
   //PTFD = 0x00;
   while(1) {
       
           
             
             WATCHDOG();
       
   }
    
}
