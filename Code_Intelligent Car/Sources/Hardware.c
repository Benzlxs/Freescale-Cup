#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main.h"

///////////////////////////////////////
//�Ӳ��뿪�ض�����������Ϣ��ȫ�ֱ���     //
///////////////////////////////////////

/******************uart_init()****************/
void uart_init(void) 
{                                   
             
  SCI0CR2_TE = 1;    //������
   
  SCI0BDH=0x00;      
  
    SCI0BDL=80000000/(57600*16); //xxM   sd��Ҳ���������
  
}

/******************pwm_init()****************/
void pwm_init(void) 
{

  PWMCTL_CON45=1; // ����������λ��ͨ����ϳ�ʮ��λ��ͨ������ͨ�����
                  // 4���ֽڣ�5���ֽڣ�5���������Ϊ��Ϻ������ţ�
                  // 5��ʱ��ѡ��ʹ�ܣ����Կ�����Ϻ�����ԡ�
  
  PWMCLK=0x0f; // ͨ��ʱ��ѡ��Ĵ��� ,
               // ͨ�� 2 ѡ��ʱ�� SA, ͨ�� 3 ѡ��ʱ�� SB, ͨ�� 5 (= 0)  ѡ��ʱ�� A
               
  

  PWMPRCLK=0x34; // ʱ��Ԥ��Ƶ�Ĵ��� ,ʱ�� B Ƶ��Ϊ Bus Clock/8 ,ʱ�� A Ƶ��Ϊ Bus Clock/16
 
  PWMSCLA=0x06;  // SA ʱ�ӷ�Ƶ�Ĵ��� Clock SA=Clock A/(2 * PWMSCLA) = Bus Clock/(16*2*6 =96) 192
  PWMSCLB=0x06;  // SB ʱ�ӷ�Ƶ�Ĵ��� Clock SB=Clock B/(2 * PWMSCLB) = Bus Clock/(8*2*6 =96) 96
  
  
  PWMPOL=0x2f; // ͨ�����ԼĴ��� , ��ͨ����ӦλΪ 1 ʱ , ��ÿһ�����ڿ�ʼʱͨ�����Ϊ�� , ����
               // ռ�ձ�ʱ , �����Ϊ�� ; ��ͨ����Ӧλ��Ϊ 0, ����ÿһ�����ڿ�ʼʱͨ�����
               // Ϊ�� , ����ռ�ձ�ʱ , �����Ϊ��
  

  PWMPER2=200;  // �������üĴ��� , ������ֵ��Ϊÿһ�����ڰ�����ʱ���� ,  bus Mhz/192
                // ��������Ϊ200ʱ����� 8bit ���� 0.48ms  Ƶ��Ϊ: 2khz              
  PWMDTY2=00;   // ռ�ձ����üĴ��� , ������ֵ��Ϊÿһ�������ڸߵ�ƽ��ռ��ʱ����
                // ������ռ�ձ�Ϊ 100%
  
  PWMPER3=200;
  PWMDTY3=0; // ͨ�� 3 ���һֱΪ�͵͵�ƽ , ��ͨ�� 2 �γɵ�ѹ�� , �����������
  
  
  
  PWMPER1=200;
  PWMDTY1=0; // ͨ�� 3 ���һֱΪ�͵͵�ƽ , ��ͨ�� 2 �γɵ�ѹ�� , �����������
  
  PWMPER0=200;
  PWMDTY0=0; // ͨ�� 3 ���һֱΪ�͵͵�ƽ , ��ͨ�� 2 �γɵ�ѹ�� , �����������
  


  
  
  //  4,5 ѡ��ͨ��5��Ϊ���������ͨ��5Ĭ��ʹ��ʱ�� A Ϊ 8 ��Ƶ 36/8MHz 
 // PWMPER45 = 55530; // ����Ϊ 10ms,  ����ʱ��Ϊ��80Mhz  16��Ƶ  65000 * 0.2us=13ms         
  //PWMPER45 = 55000; // ����Ϊ 10ms,  ����ʱ��Ϊ��80Mhz  16��Ƶ  65000 * 0.2us=13ms                 
  PWMDTY45 = straight;  // Ϊ���趨ռ�ձ�Ϊ 1.5ms , ֱ��ǰ��
                         
  
  ////////////////////////////////////////////////////////////////
  //  PWME ͨ��ʹ�ܼĴ���
  ////////////////////////////////////////////////////////////////
  PWME=0x2c; // ͨ��ʹ�ܼĴ��� , ��� 2,3 ͨ�� , ��� 5 ͨ��ʹ��
 // PWME_PWME2 = 0;  // �ر�ǰ��pwm
 // PWME_PWME3 = 0;
  PWME_PWME1 = 0;  // �ر�ǰ��pwm
  PWME_PWME0 = 0;
 
}
/**********uart_putchar()****************/
void uart_putchar(unsigned char ch)
{
  
 
  //  com0
  while(!(SCI0SR1&0x80))
  {}         
  SCI0DRL=ch; 

    
}
/******************************************************************************
//ʱ������
******************************************************************************/
void sysclock_init(void) 
{
        
  CLKSEL=0x00;
  PLLCTL_PLLON=1;   //turn on PLL
  
  SYNR =0xc0 | 0x09;  //80M                     
  REFDV=0x80 | 0x01;
 
   

  
  POSTDIV=0x00;       //pllclock=2*16*(1+SYNR)/(1+REFDV)=xxMHz;
  
  while(CRGFLG_LOCK!=1);//Wait Till VCO Run Stable
  CLKSEL_PLLSEL=0x01;//PLLCLK Enabled,Bus Clock=PLLCLK/2=24M 
  //System clocks are derived from PLLCLK (Bus Clock = PLLCLK / 2)
   
  //FCLKDIV=0x0F;//Flash Clock Divide Factor 16M/16=1M
}
/******************************************************************************
*                 m9sxs128
*�г� ��ʼ��   PT0 1 ��ʼ�� 
*Timer Control Register 4 (TCTL4)
*EDG3B EDG3A EDG2B EDG2A EDG1B EDG1A EDG0B EDG0A
* EDGnB EDGnA Configuration
* 0 0 Capture disabled
* 0 1 Capture on rising edges only
* 1 0 Capture on falling edges only
* 1 1 Capture on any edge (rising or falling)
/***************************�г��жϳ�ʼ��************************************/ 
void vinterruptsinit(void) 
{              
  // TIOS=0x00; //�ⲿ���벶׽0,1,2,3ͨ��
  // IOS7 IOS6 IOS5 IOS4 IOS3 IOS2 IOS1 IOS0
 // Input Capture or Output Compare Channel Configuration
//0 The corresponding channel acts as an input capture.
//1 The corresponding channel acts as an output compare.
   TIOS=0x00; //�ⲿ���벶׽0,1,2,3ͨ��
   
   TSCR1_TFFCA=0; // FAST FLAG CLEAR  ��ȡ������
 
   TCTL4_EDG0B = 0;   //Capture on rising edges only
   TCTL4_EDG0A = 1;
   
   TCTL4_EDG1B = 1;   //Capture on falling edges only
   TCTL4_EDG1A = 0;
  

   TIE_C0I = 0;
   TIE_C1I = 0;
   TIE_C2I = 0;
 // 16-Bit Pulse Accumulator Control Register (PACTL) 
 //  PAEN PAMOD PEDGE CLK1 CLK0 PAOVI PAI
 //  1 Pulse Accumulator system enabled.   
 //  0 Event counter mode.  
 //  0 Falling edges on IOC7 pin cause the count to be incremented.  
 
 PACTL = 0x40;      //������� �½���
// Pulse Accumulators Count Registers (PACNT)
 PACNT = 0x0000;
 
    
   TSCR1_TEN=1; //timer enable    //���������Ҫ����Ȼ�����������ʱ�ӣ�����ϵͳ�е�ʱ���ǲ��ܲ�������
 
} 
/******************************************************************************
//�ɼ������ó�����
******************************************************************************/

void PortInit(void) 
{   
   
   DDRB=0X00;    // �˿ڵķ�������
  
   DDRM=0X00; //   �˿�M �ķ�������
   
   DDRA=0X00; //   �˿�A �ķ�������
   
   DDRS=0X00;  //  �˿�s �ķ�������
 //  DDRE_DDRE4=0;
   DDRP_DDRP2=1;
   DDRP_DDRP3=1;
  // PORTE_PE4=1;
   PTP_PTP2=1;
   PTP_PTP3=1;
}

/******************************************************************************
//��·���ʼ��������������ã���main�е��á�
******************************************************************************/

void HardwareInit(void)
{	
  //ʱ�ӳ�Ƶ
	sysclock_init();
	
//	//����õ�pwm  �������
	pwm_init();
	
	//���ڲ����ʣ�����ѡ��
	uart_init();
	PIT0_Init();
}

/******************************************************************************
//���õ�һЩ��Ԫ�ĳ�ʼ�� , �������е��á�
******************************************************************************/
void CarInit(void) 
{
 
  vinterruptsinit();
   
  PortInit();

}
