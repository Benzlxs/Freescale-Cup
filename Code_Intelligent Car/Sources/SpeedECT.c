#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main.h"

unsigned int pulse_=1000,new_pulse=1;          
unsigned int pulse_aver;
////////////////////////////////////////////////////////////////////
                  
//���벶׽�ܸ�Ӧ�������ϵĵ�ƽ�ı仯
//������ֵ�ƽ�仯����
//1����������ֵ�����浽���벶׽�Ĵ����У�״̬��־λ����1
//2������ж���������CPU�����ж�����

//ico2 ���벶׽�ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
void Int_ico2(void)
{
    static unsigned int temp_;
    static unsigned int pulse_old[10]={0};
    
    TFLG1_C2F = 1; //�жϵı�־λ���㣡     
    
    //�Ѽ������е�ֵ���浽ȫ�ֱ�����
    pulse_ = TC2 - temp_ ;  
    temp_  = TC2;
    
    //////////////////////////////////////////////
    //�������� �ٶȿ���
    new_pulse=1;  //���� ������
    //////////////////////////////////////////////
    pulse_old[9]=pulse_old[8];
    pulse_old[8]=pulse_old[7];
    pulse_old[7]=pulse_old[6];
    pulse_old[6]=pulse_old[5];
    pulse_old[5]=pulse_old[4];
    pulse_old[4]=pulse_old[3];
    pulse_old[3]=pulse_old[2];
    pulse_old[2]=pulse_old[1];
    pulse_old[1]=pulse_old[0];
    pulse_old[0]=pulse_;
    
    /////////////////////////////////////////////
    //ƽ���ٶ�
    pulse_aver = (pulse_old[9]+pulse_old[8]+pulse_old[7]+pulse_old[6]+pulse_old[5]+
                  pulse_old[4]+pulse_old[3]+pulse_old[2]+pulse_old[1]+pulse_old[0])/10;
}

/////////////////////////////////////////////////////////////////////
//ico0 ������  ���벶׽�ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
void Int_ico0(void)
{
    static unsigned int temp_;
    
    TFLG1_C2F = 1; //�жϵı�־λ���㣡
    temp_++;
    if(temp_>=4){PWME_PWME2 = 0;PWME_PWME3 = 0;}
    //PORTB=~temp_;
}







