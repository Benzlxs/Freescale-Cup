#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main.h"




 unsigned char  g_time;
 unsigned char g_car_go = 0; //是否发车 0 表示不发车 1 表示发车
 unsigned char g_car_show_yn = 0;//是否可以显示数据
 
 unsigned int g_car_speed_now;//小车速度
 unsigned char  wide ;    //赛道宽度
 
 unsigned char G_car_find_line;
 int shu=0 ;

unsigned char  flag_dj;//动态静态阈值调节

 
 
  
 void car_go_now();
 
 void  debug_show_photo();
 void car_seed_set_now_v2() ;
 


 

void main(void)           
{                        
    InterruptPrioritySet();
   	EnableInterrupts;	  
   	
 
   	HardwareInit();
 
    CarInit();
     	
    PWME_PWME0 = 0;  //动力全部关掉
    PWME_PWME1 = 0;	
    
    PWMDTY0 =0;
	  PWMDTY1 =0;
	  
	  PWMDTY45 = straight; 

	 
	 TFLG1_C0F=1; // 清行中断标志 
	 TFLG1_C1F=1; // 清场中断标志   
   TIE_C0I = 1;
   TIE_C1I = 1;
 
   g_car_go=0;
	 g_car_show_yn =0;      
	    	      
  for(;;)   
  {                         
       _FEED_COP(); 

      if(g_car_go==1) 
      {
          if(g_car_show_yn==1)     
          {
             g_car_show_yn =0;       
             Photo_Make01();            
             Photo_GetCenter_old();                                
             Get_photo_quanzhongBH();
               Car_Turn_Set_v14();   //转向
               if(tingche==0) {
              if(g_time_2s<=19) {       //试车的时候不要这个，等到比赛的时候把19改成23
                PWMDTY1 = 0;
                PWMDTY0 =200;
              } else
                set_speed_PD();
               }  
              else
              {            
                 PWME_PWME0 = 0;
                 PWME_PWME1 = 0;
                 flag_s_w=7;
              } 
          
          } 
      }//------------------------------------------------------------------end if(g_car_go==1)
      else //还在2秒等待中，做时间显示，速度设置等
      {
            car_seed_set_now_v2(); //读取薄码开关的相关信息，速度，几圈停车
                  	
           if(g_time_2s >=2*car_wait_time-1)//时间到。。开始发车
           {
              for(;;) 
              {
                  if(g_car_show_yn==1)     //本场数据已经准备好
                  {
                      g_car_show_yn =0;      //等待下场数据
                      g_car_go=1;   //标志打开    
                      car_info_new =0;   
                      PWMDTY45 = straight;  
                       break;
                  } 
                }
                  car_go_now(); //动力提供  
           }
   
      } 
  }  
   
} 

 void car_go_now() 
 {
    PWME_PWME0 = 1;
    PWME_PWME1 = 1; 
   
 }
 
 
void car_seed_set_now_v2() 
{
 
         low_G_CAR_SPEED = 70; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=150;    //什么薄码也没有拨上  直线上比较少的赛道          
          G_car_find_line=9;                  
           dp=17;dd=100 ;
           MP= 4;MI=3; 
           flag_dj=1;        //采集动态阈值     
               
         if(PTM_PTM0==0) // '1'拨上
         {
          low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=150; //设置速度的参数     
          G_car_find_line=10;               //70的速度对应，10的参考行可以          
           dp=18;dd=100 ;                 //90的速度对应14的参考行，也可以，p=18,d=100;
           MP= 4;MI=3;  
           flag_dj=1;        //采集动态阈值     
         }
         if(PTM_PTM1==0)    // '2'拨上        
          {
         low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=150;   
          G_car_find_line=12;                  //设置参考行
           dp=18;dd=100 ;                        //设置舵机的控制参数
           MP= 4;MI=3;   
          flag_dj=1;        //采集动态阈值     
                       //设置电机的控制参数
         }

         if(PTM_PTM2==0)    // '3'拨上
          {
          low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=140;        
          G_car_find_line=10;              
           dp=18;dd=100  ;               
           MP= 4;MI=3;
           flag_dj=1;        //采集动态阈值     
                        
         } 
         if(PTM_PTM3==0)    // '4'拨上
          {
          low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=140;        
          G_car_find_line=11; 
            dp=18;dd=100 ;                //效果不错
           flag_dj=1;        //采集动态阈值     
            MP=4;MI=3; 
                                            
         } 
         if(PTM_PTM4==0)      // '5'拨上
         {
         low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130;   
          G_car_find_line=10;
            dp=18;dd=100 ;  
            MP=4;MI=3;                                   
            flag_dj=1;        //采集动态阈值     
         } 
         
         
         if(PTM_PTM5==0)      // '6'拨上
          { 
          low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130; 
          G_car_find_line=12;
            dp=18;dd=100 ;
            MP=4;MI=3;
           flag_dj=1;        //采集动态阈值     
                         
         }
    	   
 //--------------第七个开关拨上---------------------------
   if(PTS_PTS3==0)  
   {
         low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130;   
          G_car_find_line=10; 
            dp=18;dd=100 ; 
            MP=4;MI=3;                        
           flag_dj=0;        //采集动态阈值     
   }  
              
         if(PTS_PTS2==0)                      //第八个开关薄码
        {
         low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130;   
         G_car_find_line=12; 
          dp=18;dd=100 ; 
         MP=4;MI=3;                        
         flag_dj=0;        //采用静态阈值     
          }                            
   
        
         
}
 
 
 
 
void debug_show_photo() 
{
   unsigned char i,j;
   unsigned char *pucTemp1;
   unsigned char tempdata;
   
   //-关闭行场中断-------------
   TFLG1_C0F=1; // 清行中断标志 
	 TFLG1_C1F=1; // 清场中断标志   
   TIE_C0I = 0;
   TIE_C1I = 0;
   
 
    
    if(g_car_go==1)  {  
 
 for(i=0;i<IMAGE_ROW;i++) //20  
          {  
          
                 
                  pucTemp1=puca_BufferProcess+(i)*IMAGE_COLUMN;

                for(j=0;j<IMAGE_COLUMN; j++ )
                 {
                  
                    
                     
                   printp(uart_putchar,"%d",*(pucTemp1+j));    
                 
                  
                     
                 }
     //     printp(uart_putchar,"      %d", PhotoLineInfoOld[i].center-IMAGE_COLUMN/2 );    
        	printp(uart_putchar,"\n");
        	printp(uart_putchar,"\n");          

          } 
   shu++;      
   printp(uart_putchar,"%da",shu );   
 	printp(uart_putchar,"\n"); 
 	printp(uart_putchar,"\n");  }
 	
 	  //-打开行场中断-------------
   TFLG1_C0F=1; // 清行中断标志 
	 TFLG1_C1F=1; // 清场中断标志   
   TIE_C0I = 1;
   TIE_C1I = 1;	       
         
}
