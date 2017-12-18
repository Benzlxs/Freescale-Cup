#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"


volatile unsigned int counter_column=0; // ĞĞ¼ÆÊı
 
 
unsigned char uca_Buffer2[IMAGE_ROW][IMAGE_COLUMN];  
unsigned char *p_addr_Buffer1[IMAGE_ROW];
unsigned char  flag_yj ;              //´¦ÀíÔ¶½üµÄ±êÖ¾   
 unsigned char camera_set_y[IMAGE_ROW] ={
8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,87,90,93,96,99,102,104,106,108,110,112,114,116,118,121,124,126,128,130,132
}   ;
 /*{
8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,87,90,93,96,99,102,104,106,108,110,112,114,116,118,121,124,126,128,130,132
}                                         */
 unsigned char camera_set[IMAGE_ROW] ={                   
8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,99,102,105,108,111,114,117,120,123,126,129,132,135,138,141,144,147
} ;  
 /*{
8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,87,90,93,96,99,102,104,106,108,110,112,114,116,118,121,124,126,128,130,132
}*/  ;  //ÊµÑé²âµÃ
/* {
4,13,21,28,34,40,45,50,57,63,70,75,78,81,84,86,88,90,93,96,99,102,106,108,110,112,114,116,118,121,124,126,128,130
}  ;  //ÊµÑé²âµÃ*/  ; 
//ËÙ¶È¿ØÖÆÊ±Ê¹ÓÃµÄ±äÁ¿  
	 unsigned char flag_j_w;
	 unsigned char flag_j_sum;
	 unsigned char flag_g;
	 unsigned char flag_shizi_sum=0; 
	 unsigned char tingzhi_xian;
	 unsigned char tingzhi_sum;
	 unsigned char tingche=0;
	 unsigned char flag_zd=0;          //Ö±µÀµÄ±êÖ¾Î»,ÔÚ³ÌĞò¿ªÊ¼µÄÊ±ºòĞèÒª°ÑÕâ¸öÖµ¸³0
	 unsigned char  flag_shizi_w=0;   //Ê®×ÖÍäµÄ±êÖ¾¿
   unsigned char G_CAR_SPEED_old;   //¼ÇÂ¼ÉÏ´ÎµÄËÙ¶È
   unsigned char    flag_s_w=0;
   unsigned char *puca_BufferProcess=&uca_Buffer2[0][0];
   char  g_all_wandao_qulv;
   char  g_all_wandao_qulv_old ;
 struct photolineinfo  PhotoLineInfoOld[IMAGE_ROW];
unsigned char   flag_yj=0   ;           //²É¼¯Ô¶½üµÄ±êÖ¾ 
unsigned char   zhidao=0;
unsigned int     xcs_maxphoto ;
unsigned int    xcs_maxphoto1=110;
extern unsigned char pwm_temp; //Õı×ªÕ¼¿Õ±ÈµÄÓ°×Ó
unsigned char car_info_old=53;
unsigned char paochu=0;
unsigned char shizi_r;
unsigned char shizi_l;
unsigned char  light_value=0;
unsigned char g_time_2s=0; //2Ãë·¢³µ±êÖ¾
unsigned char   time_2s_counter = 0;
unsigned char   light_sum;
unsigned char   g_line_yn  =0;
unsigned char   flag_shizi_old=0;
unsigned int    high_G_CAR_SPEED;
unsigned char  shizi_old=0;
unsigned int    mid_G_CAR_SPEED;
unsigned char   ruwan_time=0;//ÈëÍäµÄ±êÖ¾Î» 
#define Max_zero  8

struct photolineinfotemp 
{
       int center;   //zhong xin    >=600
       unsigned char number;    // hei dian shu mu
};

 //////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////
 char car_pos[4];  ////Æ«²îµÄÎ»ÖÃ        22
void Get_photo_quanzhongBH(void) 
{

  	char i,j;
    char trace;
    unsigned char flag_z=0;//ÊÇ²»ÊÇĞ¡³µ¿ÉÒÔÖ±ÏßÍ¨¹ıµÄ±êÖ¾
    int temp,	center_sum_all,	center_counter,center_;  
    char startline,endline; 
    unsigned char *pucTemp;
    unsigned char z=0,s;//·Ö±ğ¼ÇÂ¼ºÚÏßºÍ°×ÏßµÄ¿í¶È
    int fangcha1_p,fangcha1_s,fangcha2_p,fangcha2_s;
    char car_pos[4];
      flag_s_w=0;           //ÈüµÀµÄÀàĞÍ
      if((flag_j_sum>=2)||((flag_g<=38)&&(flag_g>=20))) //¸Õ¸ÕÈëÍäµÄ×´Ì¬
      {
        flag_s_w=0;
        G_CAR_SPEED=low_G_CAR_SPEED;
        if(flag_j_sum>=4)           //ÍêÈ«ÈëÍä
          { 
             ruwan_time++;
             
              if(ruwan_time<=26)        //´Ó¿ªÊ¼ÈëÍä£¬Ğ¡³µÃ¿´ÎĞĞÊ»5cm£¬ÈëÍäĞèÒª1.2mµÄ¾àÀë
            {
            G_CAR_SPEED=low_G_CAR_SPEED;
            }
              else
              {
                 flag_s_w=1;
                G_CAR_SPEED= G_CAR_SPEED_old+2;               //ÔÚÍäµÀÀïÃæÂıÂıµÄ¼ÓËÙ
                if(G_CAR_SPEED>=mid_G_CAR_SPEED)
                G_CAR_SPEED=mid_G_CAR_SPEED;
              }
          } 
      }
    else  
    {  
     int yya,ys;
     int xys,xs;
     int aa,bb;
     int f_z;
     int sum_all;
     int temp_ss ;
     unsigned char z;
      j=0;
    startline = 0;
    
     ruwan_time=0;        //½øÈëÖ±µÀ¸øÍäµÀ±íÊ¾¸ø0
     fangcha1_p=0;
     fangcha1_s=0;
     fangcha2_p=0;
     fangcha2_s=0;
            
     for(j=0;j<4;j++) 
      { 

           car_pos[j]=100; 
      }
      
        trace = 4;//g_all_new_line/4;
        for(j=0;j<4;j++)    // first---
        { 
              endline =0;
            	center_sum_all=0;
        	    center_counter =0;
        
        	     
              for(i=startline; i<IMAGE_ROW-2;i++)       //¼ÆËãÕû·ùÍ¼µÄÇúÂÊ
              {
                  if(PhotoLineInfoOld[IMAGE_ROW-2-i].number!=0)
                   {
                      
                      temp = IMAGE_COLUMN/2- PhotoLineInfoOld[IMAGE_ROW-9-i].center;
            					center_sum_all += temp *(abs(temp));
            					center_counter += abs(temp);  //abs ÎªÈ¨ÖØ×¢Òâ£¬È¨ÖØ¿ÉÄÜÎª0£¡£¡£¡£¡£¡£¡£¡
                     ///------·Ã²é-----½ô²é1 ºÍ3------
                      if(j==1)  //Õı2 ĞĞ
                      {
                        fangcha1_p +=  (temp*temp); 
                        fangcha1_s +=  (temp);
                      }
                      if(j==3) // Õı4 ĞĞ¡£
                       {
                        fangcha2_p += (temp*temp); 
                        fangcha2_s += (temp);
                      }
                    //-------·Ã²é-------------
          					  endline++; //ÓĞĞ§ĞĞ¼ÆÊı	
                  }
                  if(endline==trace) {
                   startline = i+1;
                    goto out1; 
                  }
             }
    out1:;
            if(endline!=0) 
            {  if(center_counter!=0)
              car_pos[j]= center_sum_all/center_counter; 
              else
               car_pos[j]= 0; 
            }
        }   
        
 //-----------------------------------------------

//------------------ÅĞ¶ÏÊÇ²»ÊÇÖ±Ïß.ÕâÀïÒ»¶¨Òª±£Ö¤£¬Ê¶±ğµÄÕıÈ·ÍäµÀ£¬Ö±µÀ¡££¡£¡£¡£¡£¡£¡£¡£¡£¡£¡
       if(car_pos[0]!=100&&car_pos[1]!=100&&car_pos[2]!=100&&car_pos[3]!=100) 
      {

        //---±±º½Ëã·¨ x = ay + b;                                                               
         yya=ys=0;
         xys=xs=0;
         //×¼±¸¹¤×÷¾ÍĞ÷¡£
         ys =trace*trace;
         yya = 0+ys + 4*ys +9*ys;
         ys =  6*trace;
         xs = car_pos[0] + car_pos[1]+ car_pos[2]+car_pos[3];
         xys =trace*( car_pos[0]*0+1*car_pos[1]+ 2*car_pos[2]+3*car_pos[3]); 
         //---¿ªÊ¼¼ÆËã a b 
         f_z = 4*yya - ys*ys; 
       
         if(f_z!=0) 
         {  
             aa=  (4*xys-xs*ys)/f_z;
             bb=  (xs*yya - xys*ys)/f_z;
            // g_all_wandao = (4*xys-xs*ys);//aa;
              sum_all =0;
            // sum_a2 = 0;
            // sum_a4 =0;
			  for(i=0;i<4;i++) 
			  {
              //temp_ss =trace*(4*xys-xs*ys)*i/f_z + bb -car_pos[i];
              temp_ss =trace*aa*i + bb -car_pos[i];
              sum_all += temp_ss*temp_ss;

             }
           
          /* */ 
           //7-18 ±¾´ÎÒıÈëÇúÂÊ £¬Õâ¸ö¾ø¶ÔÖµÔ½´óËµÃ÷Ô½Íä¡£ Í¨¹ı·Å´óºóËû´Ó0-30 
         g_all_wandao_qulv = (10*(4*xys-xs*ys))/f_z;
	     }
	   }
    G_CAR_SPEED=high_G_CAR_SPEED-2*abs(g_all_wandao_qulv);      // ÄÜ¹ıÊ®×ÖÍäµÀÁË£¬ÕâÀïµÄ¿ØËÙÊÇ²»ÊÇÒª¸Ä±ä
    if(abs(g_all_wandao_qulv)<=5)
      flag_s_w=2;
     else
      flag_s_w=3;
     if(G_CAR_SPEED<=mid_G_CAR_SPEED)
     G_CAR_SPEED=mid_G_CAR_SPEED;
    
    for(j=0;j<IMAGE_ROW;j++) 
    {
        if(abs(PhotoLineInfoOld[j].center-IMAGE_COLUMN/2)>20+(j<32?25:0))    //20ºÍ30»¹ĞèÒª²âÊÔ      //Ğ¡³µÄÜÖ±ÏßÍ¨¹ıµÄÈüµÀ
         {
         flag_z=1;
         break;
         }
       }
          
        if(flag_z==0)
        {
         flag_s_w=6;
       //  G_CAR_SPEED=high_G_CAR_SPEED;
        }
   }
   if((flag_shizi_w!=0)&&(flag_shizi_w<=30))
    {   
       flag_s_w=5;                   //±íÊ¾Ê®×ÖÍä 
      G_CAR_SPEED=low_G_CAR_SPEED+10;                         
   /*   if(flag_s_w==0)
      G_CAR_SPEED=low_G_CAR_SPEED;              //Ê®×ÖÍäÈç¼±Íä
      if(flag_s_w==6)
      G_CAR_SPEED=low_G_CAR_SPEED+20;    */       //Ê®×ÖÍä³öÍä
  }
  G_CAR_SPEED_old= G_CAR_SPEED;   
      
      
 //*******************************************Í£Ö¹Ïß     
   if(g_time_2s>=30)
   { 
   i=0;
   for(j=0;j<16;j++)                                //ÊÇ·ñ¿ªÊ¶±ğÍ£Ö¹Ïß¹¦ÄÜµÄÌõ¼ş
   {
   if(abs(PhotoLineInfoOld[j].center-PhotoLineInfoOld[0].center)>6)
     {
        i=1;
         break; 
      }
    }
        if(i==0)
         PITCFLMT_PITE = 1;
        else
         PITCFLMT_PITE = 0;
   } else
   {
   PITCFLMT_PITE = 0;//¹Øµô¼ì²éÍ£Ö¹ÏßµÄ¹¦ÄÜ
   }
 
}  
/*
*******************************************************************************
*          Í¼Ïñ2Öµ»¯ 
* ºÚ1 °×0
*
*******************************************************************************
*/                                                                        
// #define xcs_maxphoto 110
 

void  Photo_Make01(void)
{       
  unsigned i,j;   
  unsigned char caiji[10]={1,8,15,21,25,30,32,34,36,38 };                  
  unsigned char  a , yuzhi[20] ,max=0,min=255  ;
  unsigned char *pucTemp;
  if(flag_dj==1)                    //¶¯Ì¬ãĞÖµ²É¼¯
{   xcs_maxphoto=0;                                 //1£¬3£,7£,10£,13£,17£,20£,23£,26£,29£,32£,35£,58
for(i=1,a=0;i<IMAGE_ROW;i=i+2)            //1,5,9,13,17,21,25,29,33,37//10 ²É¼¯Õâ¼¸ĞĞ£¬È»ºóÇóÆäÆ½¾ùãĞÖµ
  {                                            //1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39
  yuzhi[a]=trends_threshold(i);
  xcs_maxphoto+= yuzhi[a];          //ãĞÖµµÄ×ÜºÍ
  a++;
  }  
 /* for(i=0,a=0;i<IMAGE_ROW;i++) {
   if(i=caiji[a]) {
    yuzhi[a]=trends_threshold(i);
    xcs_maxphoto+= yuzhi[a]; 
     a++;
   }} */      
 for(a=0;a<20; a++)                  //Çó×î´óÓë×îĞ¡ãĞÖµ
   {
        if( yuzhi[a]>=max)
          {
              max=yuzhi[a];
          }
          if(yuzhi[a]<=min)
          {
              min=yuzhi[a];
           }
    } 
  xcs_maxphoto=(xcs_maxphoto-max-min)/18;
  if( xcs_maxphoto>=130)
   xcs_maxphoto=130;
  if( xcs_maxphoto<=80)
   xcs_maxphoto=80; 
  xcs_maxphoto=(xcs_maxphoto+xcs_maxphoto1)/2;
  xcs_maxphoto1=xcs_maxphoto;
  }
   else
    xcs_maxphoto=115;//¾²Ì¬ãĞÖµµ½ÏÖ³¡Ö®ºóÈ¥µ÷½Ú¡£
 for(i=0;i<IMAGE_ROW;i++)
  {   
  for(j=0; j<IMAGE_COLUMN; j++) 
          {
                           
             pucTemp=puca_BufferProcess+i*IMAGE_COLUMN+j;
        
              if(xcs_maxphoto!=0) 
              {
               *pucTemp= (*pucTemp<=xcs_maxphoto)?1:0;
              }
          }     
   }   
 //#############################################################################  
/*    if(g_car_go==1)
    { if(xcs_maxphoto>=100)                          //Íùsd¿¨ÀïÃæĞ´Èë¶æ»úµÄĞÅÏ¢
    printp(uart_putchar,"d%d,",xcs_maxphoto);
   else
    printp(uart_putchar,"x%d,",xcs_maxphoto); } */
 //########################################################################  
}

  trends_threshold(unsigned char kk)
 {
     unsigned int i, j,zmax=0,zmin=255,zbmax=0,zbmin=255,zamax=0,zamin=255,t0,t1,za,zb;
      unsigned char *pucTemp;
      pucTemp=puca_BufferProcess+kk*IMAGE_COLUMN;   
         for(j=0;j<IMAGE_COLUMN;pucTemp++,j++)
         {
            if(*pucTemp<=190)
            {
             if(*pucTemp>zmax)
             {
                 zmax=*pucTemp;
             }
             if(*pucTemp<zmin)
             {
                 zmin=*pucTemp;
             }}
         } 
         
     t0=(zmax+zmin)/2;
         while(1)
         {   
            pucTemp=puca_BufferProcess+kk*IMAGE_COLUMN;  
                 for(j=0;j<IMAGE_COLUMN;pucTemp++,j++)
                 {
                    if(*pucTemp<=190)
                    {
                     if(*pucTemp>=t0)
                     {
                         if(*pucTemp>zamax)
                         {
                             zamax=*pucTemp;
                         }
                         if(*pucTemp<zamin)
                         {
                             zamin=*pucTemp;
                         }
                     }
                     else
                     {
                         if(*pucTemp>zbmax)
                         {
                             zbmax=*pucTemp;
                         }
                         if(*pucTemp<zbmin)
                         {
                             zbmin=*pucTemp;
                         }
                     }
                  }
             }
           
             za=(zamax+zamin)/2;
             zb=(zbmax+zbmin)/2;
             t1=(za+zb)/2;
              if(t1=t0)//if(abs(t1-t0)<=1)
               break;
             else
               t0=t1;
         }
  
   return t1;
     }

 #define PHOTO_LINE_K 3/5
 
 #define MIN_WHITE_POT    5 //°×µãµÄ×îĞ¡ÊıÄ¿ ,Èç¹û°×µãÔÚ±ßÔµÄÇÃ´ËûµÄµãµÄ¸öÊı¿ÉÄÜ»áĞ¡
 
 

void  Photo_GetCenter_old(void ) 
{
 struct 	photolineinfotemp      tempinfo[Max_zero];
 unsigned  char  i, j , k;
 unsigned char temp_index;
 unsigned char *pucTemp;
 unsigned char counter=0;
 unsigned char staticcenter; 
  char   find_r_l;
  char   find_over;
  //¿ØÖÆËã·¨Ê±ºò»áÓÃµ½µÄ±äÁ¿¸ø³õÖµ
  flag_j_w=0;
  flag_j_sum=0;
  flag_shizi_w=0;
  flag_shizi_sum=0;
  flag_g=0;
  shizi_r=0;
  shizi_l=0;
 //@@@@@@@@@@@@@@@@@@@@@@@2222222
  
  for(i=0;i<Max_zero;i++) 
  {
	  tempinfo[i].center =0;
	  tempinfo[i].number =0;      
  }
  
  for(i=0;i<IMAGE_ROW;i++) 
  {
    PhotoLineInfoOld[i].center=0;
    PhotoLineInfoOld[i].number = 0;
  }
 
  staticcenter = 200;     //Õâ¸öÖµ×î´óÎª255
 //---------×¼È·µÄÕÒ³öµÚ1£¬2ĞĞµÄÖĞĞÄ×ø±ê---------Ö»ÕÒ2ĞĞ¡£·ñÔò¾ÍËãÊÇ°×µã11111
   for(i=0;i<2;i++)
     {
     if( car_info_old>IMAGE_COLUMN/2)         //ÓµÓĞ¼ÇÒä¹¦ÄÜ£¬½è¼øÉÏÒ»³¡²É¼¯µÄÖĞµãµÄÎ»ÖÃ
       {     
         counter=0;
        pucTemp= puca_BufferProcess+i*IMAGE_COLUMN+IMAGE_COLUMN-1;//  ´Ó×ó±ß¿ªÊ¼Ñ°ÕÒ
                  
       for(j=IMAGE_COLUMN; j>0; j--,pucTemp--) //--ĞèÒª×¢ÒâµÄµØ·½Îª£¬Ã¿ĞĞµÄÇ°10ÁĞ¶¼ÊÇ·Ñµã£¬¶¼²»ÄÜÒª¡£
            {
                 temp_index =  i*Max_zero/2+counter;                         //ÅÅ³ıÈüµÀÖĞ¼äÒ»¸öºÚµãµÄ¸ÉÈÅ                      
                  if(((*pucTemp)==0)||(((*pucTemp)==1)&&(*(pucTemp+1)==0)&&((pucTemp+1-(puca_BufferProcess+(i)*IMAGE_COLUMN))<IMAGE_COLUMN)))          //Ê¶±ğ°×µã     
                       {
                             tempinfo[temp_index ].center+=j-1;
                             tempinfo[temp_index ].number+=1;
                              if((tempinfo[temp_index ].number>=IMAGE_COLUMN-2)&&(flag_shizi_old!=0))//¹ıÊ®×ÖÍä
                             {
                               PhotoLineInfoOld[0].center =car_info_old;
                               PhotoLineInfoOld[1].center=PhotoLineInfoOld[0].center;
                               staticcenter =  PhotoLineInfoOld[0].center;
                               flag_shizi_w=1;
                               goto out5;
                             }
                     
                        }            
                    else 
                       {  
                           if(tempinfo[temp_index ].number>=8) {    
                                 counter++;  
                           }
                             
                            else     //²»µ½2¸öµã¡£°Ñ·ÑµãÈ¥µô
                              {
                              tempinfo[temp_index ].number=0;
                              tempinfo[temp_index ].center=0;
                              }
                              
                           if(counter>=Max_zero/2-1)
                               counter=Max_zero/2-1;
                         }                                   
                                       	            
            }         
        
       }
       else
       {
           counter=0;
       pucTemp= puca_BufferProcess+i*IMAGE_COLUMN;      //´ÓÓÒ±ß¿ªÊ¼Ñ°ÕÒ
                  
       for(j=0; j<IMAGE_COLUMN; j++,pucTemp++) //--ĞèÒª×¢ÒâµÄµØ·½Îª£¬Ã¿ĞĞµÄÇ°10ÁĞ¶¼ÊÇ·Ñµã£¬¶¼²»ÄÜÒª¡£
            {
                 temp_index =  i*Max_zero/2+counter;                 //ÅÅ³ıÈüµÀÖĞ¼äÒ»¸öºÚµãµÄ¸ÉÈÅ                              
                  if((( *pucTemp)==0 )||((*(pucTemp)==1)&&(*(pucTemp+1)==0)&&((pucTemp+1-(puca_BufferProcess+(i)*IMAGE_COLUMN))<IMAGE_COLUMN)))         //Ê¶±ğ°×µã     
                       {
                             tempinfo[temp_index ].center+=j;
                             tempinfo[temp_index ].number+=1;
                             if((tempinfo[temp_index ].number>=IMAGE_COLUMN-2)&&(flag_shizi_old!=0))//¹ıÊ®×ÖÍä
                             {
                               PhotoLineInfoOld[0].center =car_info_old;
                               PhotoLineInfoOld[1].center=PhotoLineInfoOld[0].center;
                               staticcenter =  PhotoLineInfoOld[0].center;
                               flag_shizi_w=1;
                               goto out5;
                             }
                        }            
                    else 
                       {  
                           if(tempinfo[temp_index ].number>=8) { //4  //ÅÅ³ıÈüµÀÖĞ¼äÒ»¸öºÚµãµÄ¸ÉÈÅ
                                 counter++;  
                           }
                             
                            else     //²»µ½2¸öµã¡£°Ñ·ÑµãÈ¥µô
                              {  
                              tempinfo[temp_index ].number=0;
                              tempinfo[temp_index ].center=0;
                              }
                              
                           if(counter>=Max_zero/2-1)
                               counter=Max_zero/2-1;
                         }                                   
                                       	            
            }         
        } 
        }  
        
          //¿ªÊ¼±È½ÏÕâ2ĞĞµÄÖĞĞÄµãÊÇ·ñÏà¿¿
                for(i=0;i<Max_zero/2;i++) 
                {
                  if(tempinfo[i].number!=0) 
                  {                                                                                                                          //20 15
                       if(abs((tempinfo[i].center)/(tempinfo[i].number) /*- IMAGE_COLUMN/2*/-car_info_old)<=25+(((flag_shizi_old==1)||(shizi_old==1))?10:0))//28  20Á½¸öÖĞĞÄµãºÜ¿¿½ü?
                       {
                         goto out1;
                       }
                       
                  }    
                }           
            out1:;    
                if(i!=Max_zero/2) //ÕÒµ½ÁË
                 {
                    PhotoLineInfoOld[0].center=tempinfo[i].center/tempinfo[i].number;
                    PhotoLineInfoOld[0].number=tempinfo[i].number;
                    staticcenter =  PhotoLineInfoOld[0].center;//È¡µ¹ÊıµÚ1ĞĞ
                    for(j=0;j<Max_zero/2;j++)
                    if(tempinfo[Max_zero/2+j].number!=0)
                    {
					   	if(abs((tempinfo[Max_zero/2+j].center)/(tempinfo[Max_zero/2+j].number)/* - IMAGE_COLUMN/2*/-staticcenter )<=5) //28
                     { 
						        PhotoLineInfoOld[1].center=tempinfo[Max_zero/2+j].center/tempinfo[Max_zero/2+j].number;
                      PhotoLineInfoOld[1].number=tempinfo[Max_zero/2+j].number;
						          j=Max_zero/2;
                    } 
					}
					else{
                    PhotoLineInfoOld[1].center= PhotoLineInfoOld[0].center;
                    PhotoLineInfoOld[1].number=PhotoLineInfoOld[0].number;
                    }                                                                                                                      //(flag_shizi_w==1)&&(flag_shizi_old2==1)
                 } 
                 else//Ö»ÄÜ°Ñµ¹ÊıµÚ2ĞĞµ±×÷±ê×¼¿´Ò»¿´    ÔİÊ±ÌÔÌ­µÚ 1ĞĞ
                 {
					           for(j=0;j<Max_zero/2;j++) 
                     if(tempinfo[Max_zero/2+j].number!=0) 
                       if(abs((tempinfo[Max_zero/2+j].center)/(tempinfo[Max_zero/2+j].number)-car_info_old)<=25+((flag_shizi_old==1)||(shizi_old==1))?10:0)//28  20 Á½¸öÖĞĞÄµãºÜ¿¿½ü?
                       {
						   PhotoLineInfoOld[1].center=tempinfo[Max_zero/2+j].center/tempinfo[Max_zero/2+j].number;
                           PhotoLineInfoOld[1].number=tempinfo[Max_zero/2+j].number;
                    
                            PhotoLineInfoOld[0].center= PhotoLineInfoOld[1].center;
                            PhotoLineInfoOld[0].number=PhotoLineInfoOld[1].number;
                           staticcenter =  PhotoLineInfoOld[0].center;//È¡µ¹ÊıµÚ1ĞĞ   }
                 }
                 }                     
   if(staticcenter==200)   //µ½ÕâÀïĞ¡³µÕæµÄÍêÈ«ÅÜ·ÇÁË£¬Ã»ÓĞ¾ÈÁË. ´Ë³¡Îª°×
   { 
   paochu++;
  if(paochu>=2){
   paochu=0;
   staticcenter=IMAGE_COLUMN/2;
   } else
      return;
   }
 //-------------------------------
 //-------×ßµ½ÁËÕâÀïËµÃ÷Ò»ÇĞÕı³£-¿ªÊ¼È·¶¨ÆäËûµÄĞĞÖĞĞÄ--------------
 //- Éè¼ÆË¼ÏëÎª£º Ê£ÏÂĞĞµÄ²Î¿¼µã¶¼²Î¿¼ 1 2 Á½ĞĞµÄÖĞĞÄµãÀ´×ö£¬
 //-ÕâÑùµÄÄ¿µÄÎª¼õÉÙÔËËãÁ¿
 
  find_r_l = PhotoLineInfoOld[1].center-PhotoLineInfoOld[0].center ;

  out5:;//¹ıÊ®×ÖÍä
 
//--------------------------------ÈıÊ®ĞĞµÄ´óÑ­»·¡£Ô­À´²»ÄÜ"i--" -------------------
  for(i=2;i<IMAGE_ROW;i++)    
   {
         pucTemp=puca_BufferProcess+(i)*IMAGE_COLUMN; 
         if(*(pucTemp+staticcenter)==0)  //µ±Ç°Õâ¸öµãÎª°×µã
           {
                PhotoLineInfoOld[i].center+=staticcenter;
                PhotoLineInfoOld[i].number++;
                   
                  for(j=staticcenter+1;j<IMAGE_COLUMN;j++)             // j<staticcenter+PHOTO_BLACK_WIDTH&&
                  {
                       if(*(pucTemp+j)==0)  //ÓĞ°×µã
                      {
                         PhotoLineInfoOld[i].center+=j;
                         PhotoLineInfoOld[i].number++;
                      } 
                      else          //È¥µôÍ¼ÏñÖĞ¼äÒ»¸ö¸ÉÈÅµã
                      { 
					    if(*(pucTemp+j+1)==0&&(j+1)<IMAGE_COLUMN)
					          {
                         PhotoLineInfoOld[i].center+=j;
                         PhotoLineInfoOld[i].number++;
                      } 
                      else
						         break; 
                                          //ÓÒ±ßÑ°µã½áÊø
                  }
                  }
                 
                  
                  for(k=staticcenter;k>0; k--)                        //j>temp_index&&
                  {
                       if(*(pucTemp+k-1)==0)  //ÓĞ°×µãÔÚÕâÀïÓÃk-1ÊÇÎªÁË½ÚÔ¼¿Õ¼ä£¬²»È»kÒª¶¨Òå³É·ûºÅ±äÁ¿
                      {
                         PhotoLineInfoOld[i].center+=k-1;
                         PhotoLineInfoOld[i].number++;
                      } 
                      else 
					            { 
				          		 if(*(pucTemp+k-2)==0&&(k-1)>0) 
					             	 {
                         PhotoLineInfoOld[i].center+=k-1;
                         PhotoLineInfoOld[i].number++;
					          	   } 
                      else
                          break; 
						           } //×ó±ß±ßÑ°µã½áÊø
						         }
				   //**************************    //Ê®×ÖÍä
                  if(j==IMAGE_COLUMN){
                   if(PhotoLineInfoOld[i].center/PhotoLineInfoOld[i].number<53)   //¸ù¾İÕı³£µÄÍäµÀÖĞĞÄµãµÄÎ»ÖÃÀ´ÅĞ¶Ï
                     PhotoLineInfoOld[i].center=PhotoLineInfoOld[i].number*(53);
                      if(shizi_l==0)
                       shizi_l=i;                           //Ê®×ÖÍäµÄÓÒ¼ç
                     } 
                  //*********************
                 //*********************** ***Ê®×ÖÍä
                 if(k==0){            
                 if(PhotoLineInfoOld[i].center/PhotoLineInfoOld[i].number>(53))
                   PhotoLineInfoOld[i].center=PhotoLineInfoOld[i].number*(53);
                     if(shizi_r==0)
                       shizi_r=i;                            //Ê®×ÖÍäµÄ×ó¼ç
                 }
                 //***********************************Èç¹ûÓÃÕâÖÖ·½·¨À´¹ıÊ®×ÖÍä£¬Ôò×ªÏòÏß²»ÄÜÓÃµÚÒ»¶şĞĞ
				 if(k==0&&j==IMAGE_COLUMN)
				 {
                    PhotoLineInfoOld[i].center=PhotoLineInfoOld[i-1].center*IMAGE_COLUMN; 
                   if(flag_shizi_w==0)
                      flag_shizi_w=i;
                   flag_shizi_sum++;
                            
				 }
		 }           
//----------------µ±Ç°Õâ¸öµãÎªbaiµã-------------------------------------
        else    //µ±Ç°Õâ¸öµãÎªºÚµã
             {
                  find_over = 1;//±íÊ¾Ñ°ÕÒ½áÊø
                if(find_r_l>0) 
                {
                  for(j=staticcenter+1;j<staticcenter+12&&j<IMAGE_COLUMN;j++) 
                    {
                         if(*(pucTemp+j)==0)  //ÓĞ°×µã
                        {
							 PhotoLineInfoOld[i].center+=j;
							 PhotoLineInfoOld[i].number++;
                            find_over = 0;//±íÊ¾Ñ°ÕÒ½áÊø
                        } 
                        else    //Åöµ½°×µã¾ÍÍË³öÁË
                       {                             //ÔÚÕâÀïÊôÓÚÉÙÊıÇé¿ö£¬ÏÈ²»¼ÓÈ¥¸ÉÈÅ³ÌĞò
                        if(find_over==0)
                        break;   //ÓÒ±ßÑ°µã½áÊø
                       }
                    
                    }
                     if(PhotoLineInfoOld[i].number>=2)  // ´ËĞĞÓĞºÚµã
                        {
                          goto out2; //ÕÒµ½Å¶ÁË 
                       }
                       PhotoLineInfoOld[i].number = 0;
                       PhotoLineInfoOld[i].center =0;
                
                }
                if(find_r_l<0)     //ÓÒÃæÃ»ÓĞÕÒµ½¡£    
                  {
                        find_over = 1;//±íÊ¾Ñ°ÕÒ½áÊø
                      for(j=staticcenter;j>staticcenter-12&&j>=1;j--) 
                      {
						           if(*(pucTemp+j-1)==0)  //ÓĞºÚµã
                          {
                             PhotoLineInfoOld[i].center+=j-1;
                             PhotoLineInfoOld[i].number++;
                              find_over = 0;//±íÊ¾Ñ°ÕÒ½áÊø
                          } 
                          else    //Åöµ½°×µã¾ÍÍË³öÁË
                          {
                              if(find_over==0)
                              break;   //ÓÒ±ßÑ°µã½áÊø
                         }
                      } 
                       if(PhotoLineInfoOld[i].number>=2)  // ´ËĞĞÓĞºÚµã
                          {
                              goto out2; //ÕÒµ½Å¶ÁË 
                          } 
                      PhotoLineInfoOld[i].number = 0;
                      PhotoLineInfoOld[i].center =0;
                      
                  }   
                 
               if (find_r_l==0)
                  {
                     PhotoLineInfoOld[i].number=PhotoLineInfoOld[i-1].number;
						         PhotoLineInfoOld[i].center=PhotoLineInfoOld[i-1].center;
                     goto out3;
			             }	
            
                } 
            

  out2:;
     if(PhotoLineInfoOld[i].number!=0)  // ´ËĞĞÓĞºÚµã
        {
          PhotoLineInfoOld[i].center=PhotoLineInfoOld[i].center/PhotoLineInfoOld[i].number; 
        }
         else
          {  
		  	 flag_j_w=1;
	//		 flag_j_sum=i;
          if(find_r_l>0){
			  for(;i<IMAGE_ROW;i++)
			  {   flag_j_sum++;
				  PhotoLineInfoOld[i].center=IMAGE_COLUMN-1;
				if(abs(PhotoLineInfoOld[i].center-PhotoLineInfoOld[i-1].center)>4)     //10)
               PhotoLineInfoOld[i].center=PhotoLineInfoOld[i-1].center;
			  }
			 }
        if(find_r_l<0)
		  {
			  for(;i<IMAGE_ROW;i++)
			  {  
			         flag_j_sum++;
				  PhotoLineInfoOld[i].center=0;
                
			   if(abs(PhotoLineInfoOld[i].center-PhotoLineInfoOld[i-1].center)>4)     //10)
               PhotoLineInfoOld[i].center=PhotoLineInfoOld[i-1].center;
          }
		  }
		 }      
       
out3:;                                                                          //¹ıÊ®×ÖÍä£¬ÕâÖÖ¼ì²âµÄµ÷½Ú·Å¿í
   	if(abs(PhotoLineInfoOld[i].center-PhotoLineInfoOld[i-1].center)>4+((((shizi_old==1)||(flag_shizi_old==1)||(flag_shizi_w==1))&&(i<=20))?30:0))//24)
        {
       PhotoLineInfoOld[i].center=PhotoLineInfoOld[i-1].center;
           if(flag_g==0)
           flag_g=i;
        }
       if(PhotoLineInfoOld[i].number!=0&&PhotoLineInfoOld[i-1].number!=0)
         find_r_l = PhotoLineInfoOld[i].center-PhotoLineInfoOld[i-1].center;
	   if(find_r_l==0)
	       find_r_l = PhotoLineInfoOld[i-1].center-PhotoLineInfoOld[i-2].center;    
          staticcenter = PhotoLineInfoOld[i].center;

   }   
  
 shizi_old=flag_shizi_old;  
 flag_shizi_old=flag_shizi_w;
 car_info_old=PhotoLineInfoOld[4].center ;
 //Ïòsd¿¨ÀïÃæĞ´ÈëÃ¿Ò»·ùÍ¼ÏñµÄ×ªÏò²Î¿¼ĞĞµÄÖĞµãÖµ
 //#####################################################################################
 /*if(g_car_go==1)
  printp(uart_putchar,"z%d,",PhotoLineInfoOld[2].center );  
*/
}



/*
***************************************************************************************************      
*  ³¡ÖĞ¶Ï´¦Àí
*¹¦ÄÜ£º a ¿ªÆôÁËÍ¼Ïñ2Öµ»¯µÄÈÎÎñtask1
*       b ÖØĞÂ¿ªÆôÁËĞĞÖĞ¶Ï¡£Õâ¸öÒªÇåĞĞÖĞ¶ÏµÄ±êÖ¾
*       c ²É¼¯ĞĞÊıµÄ¸´Î»
************************************************************************************************** 
*/
unsigned int  jiange_m=0;    //ÊÇ²»ÊÇ¼ä¸ô(jiange)ÁË8ĞĞ
unsigned char jiange_speed =0;
unsigned char g_photo_over=0;
unsigned char g_speed_set = 0;

unsigned char chang_count = 0;   //²âÊÔĞĞ³¡ĞÅºÅÊÇ·ñ½Ó¶Ô
unsigned char speed_get_time = 0;//ËÙ¶È²É¼¯Ê±¼äËõĞ¡Ò»°ë
extern unsigned char g_car_go ; //ÊÇ·ñ·¢³µ 0 ±íÊ¾²»·¢³µ 1 ±íÊ¾·¢³µ


#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
void  Port1_interrupt(void) 
 {  
    
     //²âÊÔĞĞ³¡ĞÅºÅÊÇ·ñ½Ó¶Ô
      if(chang_count++>=50) 
      {
       chang_count =0;
      }
      
      TFLG1_C1F=1; // Çå³¡ÖĞ¶Ï±êÖ¾ 

       
      jiange_m=0;  //ĞĞÊıÇåÁã
       
       if(g_time_2s<130&&time_2s_counter++>6) 
       {
          time_2s_counter = 0;
          g_time_2s++;
       }


 //--------Ìí¼ÓËÙ¶È²É¼¯------------------------------
// if(g_car_go==1) //¶¯Á¦ÒÑ¾­Ìá¹©£¬¿ªÊ¼×ö¿ØÖÆ 
//       set_speed_PD();
//--------Ìí¼ÓËÙ¶È²É¼¯----------------------------------
 
       TFLG1_C0F=1; // ÇåĞĞÖĞ¶Ï±êÖ¾ --×¢ÒâÕâ¸öÊÇ±ØĞëµÄ¡£ÇĞ¼Ç£¡£¡£¡£¡£¡£¡£¡£¡
       TIE_C0I =1;// ĞĞÖĞ¶Ï  
       TFLG1_C1F=1; // Çå³¡ÖĞ¶Ï±êÖ¾ 
       

} 

/*
*****************************ĞĞÖĞ¶Ï*********************************************************************
**    NALÖÆ£¬Ã¿Ãë25Ö¡£¬Ò»Ö¡Á½³¡£¬ÄÇÃ´Ã¿Ãë¾ÍÓĞ50³¡¡£ÒâÎ¶×Å20MS¾ÍÓĞÒ»·ùÍ¼Ïñ²úÉú¡£
*Ô­Àí £º356x 292 pixels£¬Àí½âÎª£ºÓĞ292ĞĞ£¬Ò»ĞĞÓĞ356¸öµã¡£  2
*      ±¾ÏµÍ³ÖĞËùÀûÓÃµÄĞĞÊıÎª£º  5*image_row = ĞĞ£¬ÄÇÃ´Ê£ÏÂµÄĞĞÊıÎª110 Ê£ÏÂµÄÊ±¼äÎª 20*110/292 =  7ms
*      ÔÙ¼ÓÉÏ³¡ÏûÒşÊ±¼ä£¬ÄÇÃ´
*      ±¾°æ±¾ĞĞÖĞ¶ÏÖĞ¼ÓÉÏÁË ·¢ËÍĞÅºÅ¡£ÊÔÑéÍ¨¹ı¡
*×¢Òâ£ºÔÚÔñÊ±ÄÉÈë²Ù×÷ÏµÍ³µÄÖĞ¶ÏÖĞ£¬³ÌĞòÖĞ²»ÒªÓĞ¾Ö²¿±äÁ¿£¡£¡ÇĞ¼Ç£¬·ñÔòÊ±¼ä²»È·¶¨¡£
************************* *******************************************************************************
*/

unsigned char hang_i=0; //ĞĞÖĞ¶ÏÀïÃæÓÃµÄ¼ÇÂ¼Ã¿ĞĞµãµÄ¸öÊıµÄ±äÁ¿
#define JIANGE_HANG 3  //Õâ¸öÊı¾İ±ØĞë´óÓÚ3      µ±È»Ò²²»ÄÜÌ«´ó
unsigned char  jiange_speednow =0;
unsigned char *chang_pucTemp=NULL;


 //ico2 ÊäÈë²¶×½ÖĞ¶Ï
 
 unsigned char speed_cesu_num =  0;
 
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
 void   Port0_interrupt(void) 
{
 
  if(flag_speed==1)                 //¸ßËÙ×´Ì¬ÊĞ³¡·ÅÔ¶Ğ©
   {
    if(jiange_m == camera_set[jiange_speednow ])
  {
      chang_pucTemp=puca_BufferProcess+jiange_speednow*IMAGE_COLUMN ;
              for(hang_i=0;hang_i<2;hang_i++) 
                *(chang_pucTemp+hang_i)= PORTA;
                *(chang_pucTemp+0)= PORTA;
              
               for(hang_i=0;hang_i<IMAGE_COLUMN;hang_i++) 
               {
                *(chang_pucTemp+hang_i)= PORTA;
                               }
               
           jiange_speednow++;  //¼ÇÂ¼ºÚÏßµÄÊıÄ¿
        if(jiange_speednow >= IMAGE_ROW){
           jiange_speednow=0;
           g_car_show_yn = 1;//¿ÉÒÔÏÔÊ¾£¬¿ÉÒÔ´¦ÀíÕâ³¡Êı¾İÁË   
            TIE_C0I = 0;
        }
    } 
   } else
   {
    if(jiange_m == camera_set_y[jiange_speednow ])
  {
      chang_pucTemp=puca_BufferProcess+jiange_speednow*IMAGE_COLUMN ;
              for(hang_i=0;hang_i<2;hang_i++) 
                *(chang_pucTemp+hang_i)= PORTA;
                *(chang_pucTemp+0)= PORTA;
              
               for(hang_i=0;hang_i<IMAGE_COLUMN;hang_i++) 
               {
                *(chang_pucTemp+hang_i)= PORTA;
                               }
               
           jiange_speednow++;  //¼ÇÂ¼ºÚÏßµÄÊıÄ¿
        if(jiange_speednow >= IMAGE_ROW){
           jiange_speednow=0;
           g_car_show_yn = 1;//¿ÉÒÔÏÔÊ¾£¬¿ÉÒÔ´¦ÀíÕâ³¡Êı¾İÁË   
            TIE_C0I = 0;
        }
    } 
   }
      
    jiange_m++;
    TFLG1_C0F = 1; 
    
       
}   
