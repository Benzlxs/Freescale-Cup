 #include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"

   #pragma CODE_SEG __NEAR_SEG  NON_BANKED 
 void interrupt 66 PIT0 (void)
  {
  unsigned char i;
  light_sum=0;
  light_value=PORTB  ; 
  for(i=0;i<8;i++)
  {
  if((light_value&0x01)==0)
     light_sum++;
  light_value=light_value>>1;
  }
  if(light_sum>=3)
     tingche=1;
 
   PITTF_PTF0=1;
 }
 #pragma CODE_SEG DEFAULT 
 void InterruptPrioritySet(void){
    INT_CFADDR=0xE0;
    INT_CFDATA6=6;//设置PT1中断优先级为6
    INT_CFADDR=0xE0;
    INT_CFDATA7=7;//设置PT0中断优先级为7
   // INT_CFADDR=0xF0;
   // INT_CFDATA3=4;//设置SWI中断优先级为4
    INT_CFADDR=0x70;
    INT_CFDATA5=5;//设置PIT0中断优先级为5
}
  void PIT0_Init(void){
    PITCFLMT_PITE = 0;//关定时器总使能
    PITMTLD0 = 80-1;//设置8位时基计数初值//一毫秒读取一下光电管的值
    PITLD0 = 1000-1;//设置16位计数初值
    //周期=(PITMTLD0=1)*(PITLD0+1)/fBUS
    PITMUX_PMUX0 = 0;//16位定时器连接时基0
    PITINTE_PINTE0 = 1;//通道0中断开
    PITCE_PCE0 = 1;//通道0使能
  //  PITCFLMT_PITE = 1;//使能PIT
}                                                                                               