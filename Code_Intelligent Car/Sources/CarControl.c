#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"

unsigned char pwm_temp; //正转占空比的影子
 int car_info_o=0; //记录上次车的中心位置。150这个值是不会出现的。
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
unsigned char flag_jia=0;//加减速的标志
unsigned char flag_jian=0; 
void Car_Turn_Set_v14()       //舵机来回抖动，是不停换参考行，引起的，所以参考行保持一定，然后通过调节pd餐数来控制小车运动轨迹。小车过弯抖动的情况在加入d后改善
{
    unsigned char line ,i;
    int temp_pid,dx1;
    unsigned char p ,d ;
  
  switch(flag_s_w)                        // 实际车速大于给定车速
        {
          case 0: {          // 进弯和大s弯道就在这种模式下跑
        p=12;//-(flag_speed==1?7:0);//+(flag_jian>=18?8:0);                      //p=12.d=2200,这个参数主要是为了大s切内道，但是在入弯的时候会急停下，原因，d太大，舵机大的太快，配合15的参考行
        d=1200;//-(flag_speed==1?1200:0);// +(flag_jian>=18?1000:0); 
       line=12;//+(flag_jian>=18?2:0);              //  p=dp;d=dd ;
         }
          break;
          case 1: {         //在弯
            p=dd-1;//+(flag_speed==1?2:0);  //14   //8           //6
           d=dp;//+(flag_speed==1?800:0);    //140   //160        //160 
           line=G_car_find_line;                //在弯，防止车轮掉到外面去了，所以前瞻放近
           }
          break;
          case 2: {           //直道
      p=12-(flag_speed==1?2:0);
      d=120-(flag_speed==1?60:0);
      line=17;//G_car_find_line;
           }
          break;
          case 3:{
        p=14;                //过大弯前瞻要放远，可以内切
        d=140;           //大弯
        line=17;//G_car_find_line;
             }
             break;
          case 4:{             //急弯，,目前还没有用
          p=10;
          d=100;
          line=17;//G_car_find_line; 
            }
            break; 
          case 5:{                 //十字弯
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
           if((flag_shizi_w<=30)&&(flag_shizi_w!=0))        //过十字弯程序，
              {  
               if((flag_shizi_w==1)||(shizi_l==2)||(shizi_r==2))
                    {
                  /*  if(abs(shizi_l-shizi_r)>=8)                     //靠近十字弯
                     car_info_new= ((PhotoLineInfoOld[2].center-IMAGE_COLUMN/2)+4*(shizi_r-shizi_l))/3;   //不要car_info_new+2*能够入弯 
                     else*/
                     {
                     if(flag_shizi_w==1)
                     car_info_new= (PhotoLineInfoOld[16].center-IMAGE_COLUMN/2);   //完全在十字弯里面，则把前瞻放远
                     else
                      car_info_new= car_info_o;
                      
                     }    }
                     else                                             //远离十字弯
                     car_info_new=  ((PhotoLineInfoOld[2].center-IMAGE_COLUMN/2)+2*(shizi_r-shizi_l))/3;       
             
              /*    if((flag_shizi_w==1)||(shizi_l==2)||(shizi_r==2))
                    {
                    if(abs(shizi_l-shizi_r)>=6)                     //靠近十字弯
                     car_info_new= (car_info_new+3*(shizi_r-shizi_l))/3;   //不要car_info_new+2*能够入弯 
                     else
                     car_info_new= car_info_o/2; }
                     else                                             //远离十字弯
                     car_info_new= (car_info_new+3*(shizi_r-shizi_l))/3;     
                      }    
          */ }
          if(abs(car_info_new - car_info_o)>=40) 
            {
               car_info_new = (car_info_o*14)/10;               
            }
 
       temp_pid = straight - (turn_step *car_info_new*p)/10- (turn_step *(car_info_new-car_info_o)*d)/30;   //简单pd算法     
	
		if(temp_pid >= straight+turn_max)//最大转角保护 
		{
			 PWMDTY45 = straight+turn_max;	
		}
		else if(temp_pid <= straight-turn_max2)//最大转角保护 
		{
			 PWMDTY45 = straight-turn_max2;	
		}
		else
		{
			 PWMDTY45 = temp_pid;
		}  
   car_info_o= car_info_new;
  //#############################################################################  
 /*    if(PWMDTY45>=10000)                          //往sd卡里面写入舵机的信息
    printp(uart_putchar,"t%d,",PWMDTY45);
   else
    printp(uart_putchar,"r%d,",PWMDTY45); 
 */
}



 
int lasts_ek=0;//最新的速度偏差
#define PWM_STEP 50//70//目的是不让pwm增加的太多

void set_speed_PD(void)
{
    
    int s_ek;    //速度偏差   
    int s_dek;    //速度偏差变化量
          
    int ctrl_motor;
    unsigned char  step;
    g_car_speed_old=g_car_speed_now;
    g_car_speed_now =PACNT; //实际测量的速度值
     
     
    PACNT = 0x0000;
   if(flag_s_w==1)
      step= PWM_STEP;             ///step=20;观察过弯道后轮有没有摆动
   else
      step= PWM_STEP;
   
     if(g_car_speed_now!=0) //第五轮编码器没有悬空
    {
       s_ek=(G_CAR_SPEED- g_car_speed_now);  //速度偏差
       if((s_ek)<=-20+(flag_s_w==0?10:0)-(flag_s_w==1?10:0))
      {
      PWMDTY1 = 200;
       PWMDTY0 = 0;
      return; 
       }
       s_dek=s_ek-lasts_ek;      //速度偏差变化量         
       ctrl_motor = pwm_temp;      
       ctrl_motor=ctrl_motor+(MP*s_ek)/2+MI*s_dek;
         lasts_ek=s_ek;   
     /*   if(ctrl_motor<0)              //反向制动
        {
       if(abs(ctrl_motor-pwm_temp)>=PWM_STEP)//偏差很大
         {  
         if(ctrl_motor-pwm_temp<0)           //限制减速的幅度，减轻对电机的伤害
           ctrl_motor =pwm_temp-PWM_STEP;
         }
        if(ctrl_motor<-200) 
        ctrl_motor=-200;
        
       PWMDTY1 = -ctrl_motor;
       PWMDTY0 = 0;
        pwm_temp = ctrl_motor; //正转占空比的影子    G_CAR_SPEED   
        }
         else*/
        {                                                 //正向驱动
       if(abs(ctrl_motor-pwm_temp)>=step)//偏差很大
       {
         if(ctrl_motor-pwm_temp>=0)
         ctrl_motor = pwm_temp+step;  //防止在弯道上面加速打滑，慢慢的加速
         else
           ctrl_motor =pwm_temp-PWM_STEP ;
       }
        
        if(ctrl_motor> 200)
         ctrl_motor= 200;
        if(ctrl_motor<0)
          ctrl_motor=0;
          PWMDTY1 = 0;
          PWMDTY0 = ctrl_motor;
          pwm_temp = ctrl_motor; //正转占空比的影子    G_CAR_SPEED   
         }
 
    
    }
    if((g_car_speed_old>(mid_G_CAR_SPEED+10))&&(g_car_speed_now>(mid_G_CAR_SPEED+10)))
    flag_speed=1;           //表示高速状态
    else
    flag_speed=0;              //表示低速状态
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
    //采集理论车速
 /* if(G_CAR_SPEED>=100)
    printp(uart_putchar,"+%d,",G_CAR_SPEED);//往sd卡里面写入理论速度
  else
    printp(uart_putchar,"=%d,",G_CAR_SPEED);  
  if(g_car_speed_now>=100)
    printp(uart_putchar,"l%d,",g_car_speed_now);//往sd卡里面写入实际速度
  else
    printp(uart_putchar,"s%d,",g_car_speed_now);  
 */
  
}
