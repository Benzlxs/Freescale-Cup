#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main.h"

unsigned int pulse_=1000,new_pulse=1;          
unsigned int pulse_aver;
////////////////////////////////////////////////////////////////////
                  
//输入捕捉能感应到引脚上的电平的变化
//如果发现电平变化，则：
//1、计数器的值被保存到输入捕捉寄存器中，状态标志位被置1
//2、如果中断允许，则向CPU发出中断请求

//ico2 输入捕捉中断
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
void Int_ico2(void)
{
    static unsigned int temp_;
    static unsigned int pulse_old[10]={0};
    
    TFLG1_C2F = 1; //中断的标志位清零！     
    
    //把计数器中的值保存到全局变量中
    pulse_ = TC2 - temp_ ;  
    temp_  = TC2;
    
    //////////////////////////////////////////////
    //立即进行 速度控制
    new_pulse=1;  //脉冲 更新了
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
    //平均速度
    pulse_aver = (pulse_old[9]+pulse_old[8]+pulse_old[7]+pulse_old[6]+pulse_old[5]+
                  pulse_old[4]+pulse_old[3]+pulse_old[2]+pulse_old[1]+pulse_old[0])/10;
}

/////////////////////////////////////////////////////////////////////
//ico0 起跑线  输入捕捉中断
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
void Int_ico0(void)
{
    static unsigned int temp_;
    
    TFLG1_C2F = 1; //中断的标志位清零！
    temp_++;
    if(temp_>=4){PWME_PWME2 = 0;PWME_PWME3 = 0;}
    //PORTB=~temp_;
}







