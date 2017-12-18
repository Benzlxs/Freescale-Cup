#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main.h"




 unsigned char  g_time;
 unsigned char g_car_go = 0; //�Ƿ񷢳� 0 ��ʾ������ 1 ��ʾ����
 unsigned char g_car_show_yn = 0;//�Ƿ������ʾ����
 
 unsigned int g_car_speed_now;//С���ٶ�
 unsigned char  wide ;    //�������
 
 unsigned char G_car_find_line;
 int shu=0 ;

unsigned char  flag_dj;//��̬��̬��ֵ����

 
 
  
 void car_go_now();
 
 void  debug_show_photo();
 void car_seed_set_now_v2() ;
 


 

void main(void)           
{                        
    InterruptPrioritySet();
   	EnableInterrupts;	  
   	
 
   	HardwareInit();
 
    CarInit();
     	
    PWME_PWME0 = 0;  //����ȫ���ص�
    PWME_PWME1 = 0;	
    
    PWMDTY0 =0;
	  PWMDTY1 =0;
	  
	  PWMDTY45 = straight; 

	 
	 TFLG1_C0F=1; // �����жϱ�־ 
	 TFLG1_C1F=1; // �峡�жϱ�־   
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
               Car_Turn_Set_v14();   //ת��
               if(tingche==0) {
              if(g_time_2s<=19) {       //�Գ���ʱ��Ҫ������ȵ�������ʱ���19�ĳ�23
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
      else //����2��ȴ��У���ʱ����ʾ���ٶ����õ�
      {
            car_seed_set_now_v2(); //��ȡ���뿪�ص������Ϣ���ٶȣ���Ȧͣ��
                  	
           if(g_time_2s >=2*car_wait_time-1)//ʱ�䵽������ʼ����
           {
              for(;;) 
              {
                  if(g_car_show_yn==1)     //���������Ѿ�׼����
                  {
                      g_car_show_yn =0;      //�ȴ��³�����
                      g_car_go=1;   //��־��    
                      car_info_new =0;   
                      PWMDTY45 = straight;  
                       break;
                  } 
                }
                  car_go_now(); //�����ṩ  
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
 
         low_G_CAR_SPEED = 70; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=150;    //ʲô����Ҳû�в���  ֱ���ϱȽ��ٵ�����          
          G_car_find_line=9;                  
           dp=17;dd=100 ;
           MP= 4;MI=3; 
           flag_dj=1;        //�ɼ���̬��ֵ     
               
         if(PTM_PTM0==0) // '1'����
         {
          low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=150; //�����ٶȵĲ���     
          G_car_find_line=10;               //70���ٶȶ�Ӧ��10�Ĳο��п���          
           dp=18;dd=100 ;                 //90���ٶȶ�Ӧ14�Ĳο��У�Ҳ���ԣ�p=18,d=100;
           MP= 4;MI=3;  
           flag_dj=1;        //�ɼ���̬��ֵ     
         }
         if(PTM_PTM1==0)    // '2'����        
          {
         low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=150;   
          G_car_find_line=12;                  //���òο���
           dp=18;dd=100 ;                        //���ö���Ŀ��Ʋ���
           MP= 4;MI=3;   
          flag_dj=1;        //�ɼ���̬��ֵ     
                       //���õ���Ŀ��Ʋ���
         }

         if(PTM_PTM2==0)    // '3'����
          {
          low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=140;        
          G_car_find_line=10;              
           dp=18;dd=100  ;               
           MP= 4;MI=3;
           flag_dj=1;        //�ɼ���̬��ֵ     
                        
         } 
         if(PTM_PTM3==0)    // '4'����
          {
          low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=140;        
          G_car_find_line=11; 
            dp=18;dd=100 ;                //Ч������
           flag_dj=1;        //�ɼ���̬��ֵ     
            MP=4;MI=3; 
                                            
         } 
         if(PTM_PTM4==0)      // '5'����
         {
         low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130;   
          G_car_find_line=10;
            dp=18;dd=100 ;  
            MP=4;MI=3;                                   
            flag_dj=1;        //�ɼ���̬��ֵ     
         } 
         
         
         if(PTM_PTM5==0)      // '6'����
          { 
          low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130; 
          G_car_find_line=12;
            dp=18;dd=100 ;
            MP=4;MI=3;
           flag_dj=1;        //�ɼ���̬��ֵ     
                         
         }
    	   
 //--------------���߸����ز���---------------------------
   if(PTS_PTS3==0)  
   {
         low_G_CAR_SPEED = 80; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130;   
          G_car_find_line=10; 
            dp=18;dd=100 ; 
            MP=4;MI=3;                        
           flag_dj=0;        //�ɼ���̬��ֵ     
   }  
              
         if(PTS_PTS2==0)                      //�ڰ˸����ر���
        {
         low_G_CAR_SPEED = 90; mid_G_CAR_SPEED=110; high_G_CAR_SPEED=130;   
         G_car_find_line=12; 
          dp=18;dd=100 ; 
         MP=4;MI=3;                        
         flag_dj=0;        //���þ�̬��ֵ     
          }                            
   
        
         
}
 
 
 
 
void debug_show_photo() 
{
   unsigned char i,j;
   unsigned char *pucTemp1;
   unsigned char tempdata;
   
   //-�ر��г��ж�-------------
   TFLG1_C0F=1; // �����жϱ�־ 
	 TFLG1_C1F=1; // �峡�жϱ�־   
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
 	
 	  //-���г��ж�-------------
   TFLG1_C0F=1; // �����жϱ�־ 
	 TFLG1_C1F=1; // �峡�жϱ�־   
   TIE_C0I = 1;
   TIE_C1I = 1;	       
         
}
