//-------------------------------------------------------------------------*
// �ļ���:  GeneralFun.h ��ͨ�ú���ͷ�ļ���                                *
// ˵  ��:  ͨ�ú���ͷ�ļ�                                                 *
//-------------------------------------------------------------------------*
#ifndef GENERALFUN_H          //��ֹ�ظ�����
#define GENERALFUN_H
  //1 ͷ�ļ�
	#include "type.h"           //���Ͷ���ͷ�ļ�
	//2 ��������
	void Delay(uint16 count);   //��ʱ
	//3 �Ĵ���λ�����궨��
    #define BSET(bit,Register) ((Register)|= (1<<(bit)))   //���üĴ�����ĳһλΪ1
    #define BCLR(bit,Register) ((Register) &= ~(1<<(bit))) //���üĴ�����ĳһλΪ0
    #define BGET(bit,Register) (((Register) >> (bit)) & 1) //�õ��Ĵ�����ĳһλ״̬  
 #endif

