//-------------------------------------------------------------------------*
//��  ��  ��:  isr.c ��DZ60�жϴ������ļ���                              *
//˵      ��:  �жϴ�����                                                *
//���ļ�����:                                                              *  
//           (1)isrDummy:  �հ��жϴ������                                *
//           (2)SCI1_Recv: SCI1�жϴ������                                *
//           (3)SCI2_Recv: SCI2�жϴ������                                *
//Ӳ������: ��                                                             *
//-------------------------------------------------------------------------*
//ͷ�ļ�

#include "isr.h"

 uint8 tflg;
 uint8 rflg;
//SCI1�����жϺ���
interrupt void SCI1_Recv(void)
{    
    uint8 i;
    uint8 SerialBuff[1];     		     //��Ž������ݵ�����
    
    DisableInterrupts();                 //��ֹ���ж�
    
    i = SCIReN(1,1,SerialBuff);          //�ȴ�����1������
    if (i == 0) SCISendN(1,1,SerialBuff);//���ͽӵ�������
    
    EnableInterrupts();                  //�������ж�
}

//SCI2�����жϺ���
interrupt void SCI2_Recv(void)
{    
    uint8 i;
    uint8 SerialBuff[1];     		     //��Ž������ݵ�����
    
    DisableInterrupts();                 //��ֹ���ж�
    
    i = SCIReN(2,1,SerialBuff);          //�ȴ�����1������
    if (i == 0) SCISendN(2,1,SerialBuff);//���ͽӵ�������
    
    EnableInterrupts();                  //�������ж�
}

//CAN�����жϺ���
interrupt void isrCAN_Send(void)
{    
    DisableInterrupts();                 //��ֹ���ж�
 
    EnableInterrupts();                  //�������ж�
}

//CAN�����жϺ���
interrupt void isrCAN_Recv(void)
{    
    DisableInterrupts();                 //��ֹ���ж�
       
         
      
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
    EnableInterrupts();                  //�������ж�
}

//CAN�����жϺ���
interrupt void isrCAN_Err(void)
{    
    DisableInterrupts();                 //��ֹ���ж�
 
    EnableInterrupts();                  //�������ж�
}

//CAN�����жϺ���
interrupt void isrCAN_Wu(void)
{    
    DisableInterrupts();                 //��ֹ���ж�

    EnableInterrupts();                  //�������ж�
}

//�˴�Ϊ�û��¶����жϴ������Ĵ�Ŵ�


//δ������жϴ�����,����������ɾ��
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
   //��ʱ2s
  timer_count++;
  if(timer_count>700) 
  {
      timer_off = 1;
      timer_count = 0;
  }
  
  TPM1SC &=0x7F;
    
}   
//�жϴ����ӳ������Ͷ���
typedef void( *ISR_func_t)(void);

//�ж�ʸ���������Ҫ���������жϺ��������޸��±��е���Ӧ��Ŀ
const ISR_func_t ISR_vectors[] @0xFFC0 = 
{
    isrDummy,     //Vacmp2     0x0000FFC0   ģ��Ƚ���2�ж�����
    isrDummy,     //Vacmp1     0x0000FFC2   ģ��Ƚ���1�ж�����
    isrDummy,     //Vcantx     0x0000FFC4   CAN�����ж�����
    isrCAN_Recv,  //Vcanrx     0x0000FFC6   CAN�����ж�����
    canwrong,     //Vcanerr    0x0000FFC8   CAN�����ж�����
    isrDummy,     //Vcanwu     0x0000FFCA   CAN�����ж�����
    isrDummy,     //Vrtc       0x0000FFCC   ʵʱʱ���ж�����
    isrDummy,     //Viic       0x0000FFCE   IIC�����ж�����
    isrDummy,     //Vadc       0x0000FFD0   ADC�ж�����
    isrDummy,     //Vport      0x0000FFD2   �˿ڹܽ��ж�����
    isrDummy,     //Vsci2tx    0x0000FFD4   SCI2�����ж�����
    SCI2_Recv,    //Vsci2rx    0x0000FFD6   SCI2�����ж�����
    isrDummy,     //Vsci2err   0x0000FFD8   SCI2�����ж�����
    isrDummy,     //Vsci1tx    0x0000FFDA   SCI1�����ж�����
    SCI1_Recv,    //Vsci1rx    0x0000FFDC   SCI1�����ж�����
    isrDummy,     //Vsci1err   0x0000FFDE   SCI1�����ж�����
    isrDummy,     //Vspi       0x0000FFE0   SPI�ж�����
    isrDummy,     //Vtpm2ovf   0x0000FFE2   TPM2����ж�����
    isrDummy,     //Vtpm2ch1   0x0000FFE4   TPM2ͨ��1�ж�����
    isrDummy,     //Vtpm2ch0   0x0000FFE6   TPM2ͨ��0�ж�����
    Timer1_overflow,//Vtpm1ovf   0x0000FFE8   TPM1����ж�����
    isrDummy,     //Vtpm1ch5   0x0000FFEA   TPM1ͨ��5�ж�����
    isrDummy,     //Vtpm1ch4   0x0000FFEC   TPM1ͨ��4�ж�����
    isrDummy,     //Vtpm1ch3   0x0000FFEE   TPM1ͨ��3�ж�����
    isrDummy,     //Vtpm1ch2   0x0000FFF0   TPM1ͨ��2�ж�����
    isrDummy,     //Vtpm1ch1   0x0000FFF2   TPM1ͨ��1�ж�����         
    isrDummy,     //Vtpm1ch0   0x0000FFF4   TPM1ͨ��0�ж�����      
    isrDummy,     //Vlol       0x0000FFF6   ������ʧ�ж�����                       
    isrDummy,     //Vlvd       0x0000FFF8   ��ѹ�����ж�����                    
    irq,     //Virq       0x0000FFFA   IRQ�����ж�����                    
    isrDummy,     //Vswi       0x0000FFFC   ����ж� 
    //isrDummy      //Vreset     0x0000FFFE   ��λ�ж���������λԴ����Ϊ���Ź����Ƿ���ַ�ȵ�
};                                    
                                      
                                      
                                      
                                      
                                      
