//--------------------------------------------------------------------------*
// �ļ���: MCUInit.h                                                        *
// ˵  ��: DZ60ϵͳ��ʼ��ͷ�ļ�                                             *
//--------------------------------------------------------------------------*

#ifndef  MCUINIT_H
#define  MCUINIT_H
    
    //1 ͷ�ļ�
    #include "MC9S08DZ60.h"    //ӳ��Ĵ�����ַͷ�ļ�

    //2 �궨��
    #define EnableInterrupts() asm("CLI")  //�������ж�
    #define DisableInterrupts()  asm("SEI")  //��ֹ���ж�

    //3 ��������
    void MCUInit(void);        //оƬ��ʼ��
    void IO_INIT(void);
    void TIMER1_init(void);
    void WATCHDOG_init(void);
    void WATCHDOG(void);
#endif