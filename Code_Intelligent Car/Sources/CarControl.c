#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"

unsigned char pwm_temp; //��תռ�ձȵ�Ӱ��
 int car_info_o=0; //��¼�ϴγ�������λ�á�150���ֵ�ǲ�����ֵġ�
int car_info_new=58; 
unsigned int G_CAR_SPEED=0;
unsigned int   low_G_CAR_SPEED=0;
unsigned char dp;//=19;
unsigned char dd;//=10;
unsigned char  jieshu=0;
unsigned char MP;
unsigned char MI;
unsigned char g_car_speed_old;
unsigned char flag_speed;
unsigned char flag_jia=0;//�Ӽ��ٵı�־
unsigned char flag_jian=0; 
void Car_Turn_Set_v14()       //������ض������ǲ�ͣ���ο��У�����ģ����Բο��б���һ����Ȼ��ͨ������pd����������С���˶��켣��С�����䶶��������ڼ���d�����
{
    unsigned char line ,i;
    int temp_pid,dx1;
    unsigned char p ,d ;
  
  switch(flag_s_w)                        // ʵ�ʳ��ٴ��ڸ�������
        {
          case 0: {          // ����ʹ�s�����������ģʽ����
        p=12;//-(flag_speed==1?7:0);//+(flag_jian>=18?8:0);                      //p=12.d=2200,���������Ҫ��Ϊ�˴�s���ڵ��������������ʱ��ἱͣ�£�ԭ��d̫�󣬶�����̫�죬���15�Ĳο���
        d=1200;//-(flag_speed==1?1200:0);// +(flag_jian>=18?1000:0); 
       line=12;//+(flag_jian>=18?2:0);              //  p=dp;d=dd ;
         }
          break;
          case 1: {         //����
            p=dd-1;//+(flag_speed==1?2:0);  //14   //8           //6
           d=dp;//+(flag_speed==1?800:0);    //140   //160        //160 
           line=G_car_find_line;                //���䣬��ֹ���ֵ�������ȥ�ˣ�����ǰհ�Ž�
           }
          break;
          case 2: {           //ֱ��
      p=12-(flag_speed==1?2:0);
      d=120-(flag_speed==1?60:0);
      line=17;//G_car_find_line;
           }
          break;
          case 3:{
        p=14;                //������ǰհҪ��Զ����������
        d=140;           //����
        line=17;//G_car_find_line;
             }
             break;
          case 4:{             //���䣬,Ŀǰ��û����
          p=10;
          d=100;
          line=17;//G_car_find_line; 
            }
            break; 
          case 5:{                 //ʮ����
          p=16;
          d=0;//p=14,d=130 
          line=13;//G_car_find_line;
          }
          break;
          case 6:
          {
           p=12-(flag_speed==1?6:0),
           d=100-(flag_speed==1?50:0);
           line=G_car_find_line;
          }
          break;
               } 
               if(tingche==1)
               {
                  p=12;
                 d=10;
                line=8; 
               }
 
          if(flag_s_w!=6)
          {  
             car_info_new=(PhotoLineInfoOld[line+2].center-IMAGE_COLUMN/2);         //14
             car_info_new+=(PhotoLineInfoOld[line].center-IMAGE_COLUMN/2);        //13
             car_info_new+=(PhotoLineInfoOld[line-1].center-IMAGE_COLUMN/2);        //12
             car_info_new+=(PhotoLineInfoOld[line+1].center-IMAGE_COLUMN/2);        //15
             car_info_new=car_info_new/4; 
   
          } else
          {
             car_info_new=(2*(PhotoLineInfoOld[2].center-IMAGE_COLUMN/2)+3*(PhotoLineInfoOld[18].center-IMAGE_COLUMN/2)+4*(PhotoLineInfoOld[31].center-IMAGE_COLUMN/2))/9;         //14
          }
           if((flag_shizi_w<=30)&&(flag_shizi_w!=0))        //��ʮ�������
              {  
               if((flag_shizi_w==1)||(shizi_l==2)||(shizi_r==2))
                    {
                  /*  if(abs(shizi_l-shizi_r)>=8)                     //����ʮ����
                     car_info_new= ((PhotoLineInfoOld[2].center-IMAGE_COLUMN/2)+4*(shizi_r-shizi_l))/3;   //��Ҫcar_info_new+2*�ܹ����� 
                     else*/
                     {
                     if(flag_shizi_w==1)
                     car_info_new= (PhotoLineInfoOld[16].center-IMAGE_COLUMN/2);   //��ȫ��ʮ�������棬���ǰհ��Զ
                     else
                      car_info_new= car_info_o;
                      
                     }    }
                     else                                             //Զ��ʮ����
                     car_info_new=  ((PhotoLineInfoOld[2].center-IMAGE_COLUMN/2)+2*(shizi_r-shizi_l))/3;       
             
              /*    if((flag_shizi_w==1)||(shizi_l==2)||(shizi_r==2))
                    {
                    if(abs(shizi_l-shizi_r)>=6)                     //����ʮ����
                     car_info_new= (car_info_new+3*(shizi_r-shizi_l))/3;   //��Ҫcar_info_new+2*�ܹ����� 
                     else
                     car_info_new= car_info_o/2; }
                     else                                             //Զ��ʮ����
                     car_info_new= (car_info_new+3*(shizi_r-shizi_l))/3;     
                      }    
          */ }
          if(abs(car_info_new - car_info_o)>=40) 
            {
               car_info_new = (car_info_o*14)/10;               
            }
 
       temp_pid = straight - (turn_step *car_info_new*p)/10- (turn_step *(car_info_new-car_info_o)*d)/30;   //��pd�㷨     
	
		if(temp_pid >= straight+turn_max)//���ת�Ǳ��� 
		{
			 PWMDTY45 = straight+turn_max;	
		}
		else if(temp_pid <= straight-turn_max2)//���ת�Ǳ��� 
		{
			 PWMDTY45 = straight-turn_max2;	
		}
		else
		{
			 PWMDTY45 = temp_pid;
		}  
   car_info_o= car_info_new;
  //#############################################################################  
 /*    if(PWMDTY45>=10000)                          //��sd������д��������Ϣ
    printp(uart_putchar,"t%d,",PWMDTY45);
   else
    printp(uart_putchar,"r%d,",PWMDTY45); 
 */
}



 
int lasts_ek=0;//���µ��ٶ�ƫ��
#define PWM_STEP 50//70//Ŀ���ǲ���pwm���ӵ�̫��

void set_speed_PD(void)
{
    
    int s_ek;    //�ٶ�ƫ��   
    int s_dek;    //�ٶ�ƫ��仯��
          
    int ctrl_motor;
    unsigned char  step;
    g_car_speed_old=g_car_speed_now;
    g_car_speed_now =PACNT; //ʵ�ʲ������ٶ�ֵ
     
     
    PACNT = 0x0000;
   if(flag_s_w==1)
      step= PWM_STEP;             ///step=20;�۲�����������û�аڶ�
   else
      step= PWM_STEP;
   
     if(g_car_speed_now!=0) //�����ֱ�����û������
    {
       s_ek=(G_CAR_SPEED- g_car_speed_now);  //�ٶ�ƫ��
       if((s_ek)<=-20+(flag_s_w==0?10:0)-(flag_s_w==1?10:0))
      {
      PWMDTY1 = 200;
       PWMDTY0 = 0;
      return; 
       }
       s_dek=s_ek-lasts_ek;      //�ٶ�ƫ��仯��         
       ctrl_motor = pwm_temp;      
       ctrl_motor=ctrl_motor+(MP*s_ek)/2+MI*s_dek;
         lasts_ek=s_ek;   
     /*   if(ctrl_motor<0)              //�����ƶ�
        {
       if(abs(ctrl_motor-pwm_temp)>=PWM_STEP)//ƫ��ܴ�
         {  
         if(ctrl_motor-pwm_temp<0)           //���Ƽ��ٵķ��ȣ�����Ե�����˺�
           ctrl_motor =pwm_temp-PWM_STEP;
         }
        if(ctrl_motor<-200) 
        ctrl_motor=-200;
        
       PWMDTY1 = -ctrl_motor;
       PWMDTY0 = 0;
        pwm_temp = ctrl_motor; //��תռ�ձȵ�Ӱ��    G_CAR_SPEED   
        }
         else*/
        {                                                 //��������
       if(abs(ctrl_motor-pwm_temp)>=step)//ƫ��ܴ�
       {
         if(ctrl_motor-pwm_temp>=0)
         ctrl_motor = pwm_temp+step;  //��ֹ�����������ٴ򻬣������ļ���
         else
           ctrl_motor =pwm_temp-PWM_STEP ;
       }
        
        if(ctrl_motor> 200)
         ctrl_motor= 200;
        if(ctrl_motor<0)
          ctrl_motor=0;
          PWMDTY1 = 0;
          PWMDTY0 = ctrl_motor;
          pwm_temp = ctrl_motor; //��תռ�ձȵ�Ӱ��    G_CAR_SPEED   
         }
 
    
    }
    if((g_car_speed_old>(mid_G_CAR_SPEED+10))&&(g_car_speed_now>(mid_G_CAR_SPEED+10)))
    flag_speed=1;           //��ʾ����״̬
    else
    flag_speed=0;              //��ʾ����״̬
    if(abs(g_car_speed_old-g_car_speed_now)>6)
    { if(g_car_speed_old>g_car_speed_now)
    {  flag_jia=0;
       flag_jian++;  
     } else
      {
      flag_jia++;
      flag_jian=0;
      }} else
      {
      flag_jia=0;
      flag_jian=0;
      }
    
   //##########################################################################
    //�ɼ����۳���
 /* if(G_CAR_SPEED>=100)
    printp(uart_putchar,"+%d,",G_CAR_SPEED);//��sd������д�������ٶ�
  else
    printp(uart_putchar,"=%d,",G_CAR_SPEED);  
  if(g_car_speed_now>=100)
    printp(uart_putchar,"l%d,",g_car_speed_now);//��sd������д��ʵ���ٶ�
  else
    printp(uart_putchar,"s%d,",g_car_speed_now);  
 */
  
}
