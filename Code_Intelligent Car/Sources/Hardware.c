#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main.h"

///////////////////////////////////////
//从拨码开关读到的设置信息，全局变量     //
///////////////////////////////////////

/******************uart_init()****************/
void uart_init(void) 
{                                   
             
  SCI0CR2_TE = 1;    //允许发送
   
  SCI0BDH=0x00;      
  
    SCI0BDL=80000000/(57600*16); //xxM   sd卡也可以用这个
  
}

/******************pwm_init()****************/
void pwm_init(void) 
{

  PWMCTL_CON45=1; // 四五两个八位的通道结合成十六位的通道从五通道输出
                  // 4高字节，5低字节；5的输出脚作为组合后的输出脚，
                  // 5的时钟选择，使能，极性控制组合后的特性。
  
  PWMCLK=0x0f; // 通道时钟选择寄存器 ,
               // 通道 2 选择时钟 SA, 通道 3 选择时钟 SB, 通道 5 (= 0)  选择时钟 A
               
  

  PWMPRCLK=0x34; // 时钟预分频寄存器 ,时钟 B 频率为 Bus Clock/8 ,时钟 A 频率为 Bus Clock/16
 
  PWMSCLA=0x06;  // SA 时钟分频寄存器 Clock SA=Clock A/(2 * PWMSCLA) = Bus Clock/(16*2*6 =96) 192
  PWMSCLB=0x06;  // SB 时钟分频寄存器 Clock SB=Clock B/(2 * PWMSCLB) = Bus Clock/(8*2*6 =96) 96
  
  
  PWMPOL=0x2f; // 通道极性寄存器 , 若通道相应位为 1 时 , 在每一个周期开始时通道输出为高 , 到达
               // 占空比时 , 输出变为低 ; 若通道相应位高为 0, 则在每一个周期开始时通道输出
               // 为低 , 到达占空比时 , 输出变为高
  

  PWMPER2=200;  // 周期设置寄存器 , 赋的数值即为每一个周期包含的时钟数 ,  bus Mhz/192
                // 脉冲数设为200时，电机 8bit 周期 0.48ms  频率为: 2khz              
  PWMDTY2=00;   // 占空比设置寄存器 , 赋的数值即为每一个周期内高电平所占的时钟数
                // 在这里占空比为 100%
  
  PWMPER3=200;
  PWMDTY3=0; // 通道 3 输出一直为低低电平 , 和通道 2 形成电压差 , 用于驱动电机
  
  
  
  PWMPER1=200;
  PWMDTY1=0; // 通道 3 输出一直为低低电平 , 和通道 2 形成电压差 , 用于驱动电机
  
  PWMPER0=200;
  PWMDTY0=0; // 通道 3 输出一直为低低电平 , 和通道 2 形成电压差 , 用于驱动电机
  


  
  
  //  4,5 选用通道5作为最后的输出，通道5默认使用时钟 A 为 8 分频 36/8MHz 
 // PWMPER45 = 55530; // 周期为 10ms,  总线时钟为：80Mhz  16分频  65000 * 0.2us=13ms         
  //PWMPER45 = 55000; // 周期为 10ms,  总线时钟为：80Mhz  16分频  65000 * 0.2us=13ms                 
  PWMDTY45 = straight;  // 为了设定占空比为 1.5ms , 直线前进
                         
  
  ////////////////////////////////////////////////////////////////
  //  PWME 通道使能寄存器
  ////////////////////////////////////////////////////////////////
  PWME=0x2c; // 通道使能寄存器 , 电机 2,3 通道 , 舵机 5 通道使能
 // PWME_PWME2 = 0;  // 关闭前进pwm
 // PWME_PWME3 = 0;
  PWME_PWME1 = 0;  // 关闭前进pwm
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
//时钟配置
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
*行场 初始化   PT0 1 初始化 
*Timer Control Register 4 (TCTL4)
*EDG3B EDG3A EDG2B EDG2A EDG1B EDG1A EDG0B EDG0A
* EDGnB EDGnA Configuration
* 0 0 Capture disabled
* 0 1 Capture on rising edges only
* 1 0 Capture on falling edges only
* 1 1 Capture on any edge (rising or falling)
/***************************行场中断初始化************************************/ 
void vinterruptsinit(void) 
{              
  // TIOS=0x00; //外部输入捕捉0,1,2,3通道
  // IOS7 IOS6 IOS5 IOS4 IOS3 IOS2 IOS1 IOS0
 // Input Capture or Output Compare Channel Configuration
//0 The corresponding channel acts as an input capture.
//1 The corresponding channel acts as an output compare.
   TIOS=0x00; //外部输入捕捉0,1,2,3通道
   
   TSCR1_TFFCA=0; // FAST FLAG CLEAR  读取即清零
 
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
 
 PACTL = 0x40;      //脉冲计数 下降沿
// Pulse Accumulators Count Registers (PACNT)
 PACNT = 0x0000;
 
    
   TSCR1_TEN=1; //timer enable    //这个语句必须要，虽然脉冲可以脱离时钟，但是系统中的时钟是不能不开启的
 
} 
/******************************************************************************
//采集口配置成输入
******************************************************************************/

void PortInit(void) 
{   
   
   DDRB=0X00;    // 端口的方向输入
  
   DDRM=0X00; //   端口M 的方向输入
   
   DDRA=0X00; //   端口A 的方向输入
   
   DDRS=0X00;  //  端口s 的方向输入
 //  DDRE_DDRE4=0;
   DDRP_DDRP2=1;
   DDRP_DDRP3=1;
  // PORTE_PE4=1;
   PTP_PTP2=1;
   PTP_PTP3=1;
}

/******************************************************************************
//电路板初始化是最基本的设置，在main中调用。
******************************************************************************/

void HardwareInit(void)
{	
  //时钟超频
	sysclock_init();
	
//	//电机用的pwm  保护舵机
	pwm_init();
	
	//串口波特率，串口选择
	uart_init();
	PIT0_Init();
}

/******************************************************************************
//车用的一些单元的初始化 , 在任务中调用。
******************************************************************************/
void CarInit(void) 
{
 
  vinterruptsinit();
   
  PortInit();

}
