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
    INT_CFDATA6=6;//����PT1�ж����ȼ�Ϊ6
    INT_CFADDR=0xE0;
    INT_CFDATA7=7;//����PT0�ж����ȼ�Ϊ7
   // INT_CFADDR=0xF0;
   // INT_CFDATA3=4;//����SWI�ж����ȼ�Ϊ4
    INT_CFADDR=0x70;
    INT_CFDATA5=5;//����PIT0�ж����ȼ�Ϊ5
}
  void PIT0_Init(void){
    PITCFLMT_PITE = 0;//�ض�ʱ����ʹ��
    PITMTLD0 = 80-1;//����8λʱ��������ֵ//һ�����ȡһ�¹��ܵ�ֵ
    PITLD0 = 1000-1;//����16λ������ֵ
    //����=(PITMTLD0=1)*(PITLD0+1)/fBUS
    PITMUX_PMUX0 = 0;//16λ��ʱ������ʱ��0
    PITINTE_PINTE0 = 1;//ͨ��0�жϿ�
    PITCE_PCE0 = 1;//ͨ��0ʹ��
  //  PITCFLMT_PITE = 1;//ʹ��PIT
}                                                                                               