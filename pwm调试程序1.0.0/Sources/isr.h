//-------------------------------------------------------------------------*
// �ļ���: Isr.h                                                           *
// ˵  ��: �ж�ͷ�ļ�,���ļ�����:                                          *            
//         �����жϺ���ͷ�ļ����ⲿ�����������йس�������                  *
//-------------------------------------------------------------------------*
#ifndef ISR_H
#define ISR_H

  //1 ͷ�ļ�
  //1.1 ����ͨ��ͷ�ļ�
  #include "MC9S08DZ60.h"       //ӳ��Ĵ�����ַͷ�ļ�
  #include "Type.h"             //���ͱ�������
  #include "MCUInit.h"          //оƬ��ʼ��ͷ�ļ�
  //1.2 ��������Ӳ������ͷ�ļ�  
  #include "SCI.h"              //SCI����ͨ��ͷ�ļ�
  #include "CAN.h"

  //2 �ڴ��������ȫ�ֱ�������
  extern CANMsg g_msgGet;
  extern CANMsg fsTest;
  extern uint8 fsable;
  extern uint16 timer_count;
  extern uint8 timer_off;
  extern uint8 status; 
#endif