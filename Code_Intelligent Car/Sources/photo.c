#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"


volatile unsigned int counter_column=0; // �м���
 
 
unsigned char uca_Buffer2[IMAGE_ROW][IMAGE_COLUMN];  
unsigned char *p_addr_Buffer1[IMAGE_ROW];
unsigned char  flag_yj ;              //����Զ���ı�־   
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
}*/  ;  //ʵ����
/* {
4,13,21,28,34,40,45,50,57,63,70,75,78,81,84,86,88,90,93,96,99,102,106,108,110,112,114,116,118,121,124,126,128,130
}  ;  //ʵ����*/  ; 
//�ٶȿ���ʱʹ�õı���  
	 unsigned char flag_j_w;
	 unsigned char flag_j_sum;
	 unsigned char flag_g;
	 unsigned char flag_shizi_sum=0; 
	 unsigned char tingzhi_xian;
	 unsigned char tingzhi_sum;
	 unsigned char tingche=0;
	 unsigned char flag_zd=0;          //ֱ���ı�־λ,�ڳ���ʼ��ʱ����Ҫ�����ֵ��0
	 unsigned char  flag_shizi_w=0;   //ʮ����ı�־�
   unsigned char G_CAR_SPEED_old;   //��¼�ϴε��ٶ�
   unsigned char    flag_s_w=0;
   unsigned char *puca_BufferProcess=&uca_Buffer2[0][0];
   char  g_all_wandao_qulv;
   char  g_all_wandao_qulv_old ;
 struct photolineinfo  PhotoLineInfoOld[IMAGE_ROW];
unsigned char   flag_yj=0   ;           //�ɼ�Զ���ı�־ 
unsigned char   zhidao=0;
unsigned int     xcs_maxphoto ;
unsigned int    xcs_maxphoto1=110;
extern unsigned char pwm_temp; //��תռ�ձȵ�Ӱ��
unsigned char car_info_old=53;
unsigned char paochu=0;
unsigned char shizi_r;
unsigned char shizi_l;
unsigned char  light_value=0;
unsigned char g_time_2s=0; //2�뷢����־
unsigned char   time_2s_counter = 0;
unsigned char   light_sum;
unsigned char   g_line_yn  =0;
unsigned char   flag_shizi_old=0;
unsigned int    high_G_CAR_SPEED;
unsigned char  shizi_old=0;
unsigned int    mid_G_CAR_SPEED;
unsigned char   ruwan_time=0;//����ı�־λ 
#define Max_zero  8

struct photolineinfotemp 
{
       int center;   //zhong xin    >=600
       unsigned char number;    // hei dian shu mu
};

 //////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////
 char car_pos[4];  ////ƫ���λ��        22
void Get_photo_quanzhongBH(void) 
{

  	char i,j;
    char trace;
    unsigned char flag_z=0;//�ǲ���С������ֱ��ͨ���ı�־
    int temp,	center_sum_all,	center_counter,center_;  
    char startline,endline; 
    unsigned char *pucTemp;
    unsigned char z=0,s;//�ֱ��¼���ߺͰ��ߵĿ��
    int fangcha1_p,fangcha1_s,fangcha2_p,fangcha2_s;
    char car_pos[4];
      flag_s_w=0;           //����������
      if((flag_j_sum>=2)||((flag_g<=38)&&(flag_g>=20))) //�ո������״̬
      {
        flag_s_w=0;
        G_CAR_SPEED=low_G_CAR_SPEED;
        if(flag_j_sum>=4)           //��ȫ����
          { 
             ruwan_time++;
             
              if(ruwan_time<=26)        //�ӿ�ʼ���䣬С��ÿ����ʻ5cm��������Ҫ1.2m�ľ���
            {
            G_CAR_SPEED=low_G_CAR_SPEED;
            }
              else
              {
                 flag_s_w=1;
                G_CAR_SPEED= G_CAR_SPEED_old+2;               //��������������ļ���
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
    
     ruwan_time=0;        //����ֱ���������ʾ��0
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
        
        	     
              for(i=startline; i<IMAGE_ROW-2;i++)       //��������ͼ������
              {
                  if(PhotoLineInfoOld[IMAGE_ROW-2-i].number!=0)
                   {
                      
                      temp = IMAGE_COLUMN/2- PhotoLineInfoOld[IMAGE_ROW-9-i].center;
            					center_sum_all += temp *(abs(temp));
            					center_counter += abs(temp);  //abs ΪȨ��ע�⣬Ȩ�ؿ���Ϊ0��������������
                     ///------�ò�-----����1 ��3------
                      if(j==1)  //��2 ��
                      {
                        fangcha1_p +=  (temp*temp); 
                        fangcha1_s +=  (temp);
                      }
                      if(j==3) // ��4 �С�
                       {
                        fangcha2_p += (temp*temp); 
                        fangcha2_s += (temp);
                      }
                    //-------�ò�-------------
          					  endline++; //��Ч�м���	
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

//------------------�ж��ǲ���ֱ��.����һ��Ҫ��֤��ʶ�����ȷ�����ֱ������������������������
       if(car_pos[0]!=100&&car_pos[1]!=100&&car_pos[2]!=100&&car_pos[3]!=100) 
      {

        //---�����㷨 x = ay + b;                                                               
         yya=ys=0;
         xys=xs=0;
         //׼������������
         ys =trace*trace;
         yya = 0+ys + 4*ys +9*ys;
         ys =  6*trace;
         xs = car_pos[0] + car_pos[1]+ car_pos[2]+car_pos[3];
         xys =trace*( car_pos[0]*0+1*car_pos[1]+ 2*car_pos[2]+3*car_pos[3]); 
         //---��ʼ���� a b 
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
           //7-18 ������������ ���������ֵԽ��˵��Խ�䡣 ͨ���Ŵ������0-30 
         g_all_wandao_qulv = (10*(4*xys-xs*ys))/f_z;
	     }
	   }
    G_CAR_SPEED=high_G_CAR_SPEED-2*abs(g_all_wandao_qulv);      // �ܹ�ʮ������ˣ�����Ŀ����ǲ���Ҫ�ı�
    if(abs(g_all_wandao_qulv)<=5)
      flag_s_w=2;
     else
      flag_s_w=3;
     if(G_CAR_SPEED<=mid_G_CAR_SPEED)
     G_CAR_SPEED=mid_G_CAR_SPEED;
    
    for(j=0;j<IMAGE_ROW;j++) 
    {
        if(abs(PhotoLineInfoOld[j].center-IMAGE_COLUMN/2)>20+(j<32?25:0))    //20��30����Ҫ����      //С����ֱ��ͨ��������
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
       flag_s_w=5;                   //��ʾʮ���� 
      G_CAR_SPEED=low_G_CAR_SPEED+10;                         
   /*   if(flag_s_w==0)
      G_CAR_SPEED=low_G_CAR_SPEED;              //ʮ�����缱��
      if(flag_s_w==6)
      G_CAR_SPEED=low_G_CAR_SPEED+20;    */       //ʮ�������
  }
  G_CAR_SPEED_old= G_CAR_SPEED;   
      
      
 //*******************************************ֹͣ��     
   if(g_time_2s>=30)
   { 
   i=0;
   for(j=0;j<16;j++)                                //�Ƿ�ʶ��ֹͣ�߹��ܵ�����
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
   PITCFLMT_PITE = 0;//�ص����ֹͣ�ߵĹ���
   }
 
}  
/*
*******************************************************************************
*          ͼ��2ֵ�� 
* ��1 ��0
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
  if(flag_dj==1)                    //��̬��ֵ�ɼ�
{   xcs_maxphoto=0;                                 //1��3�,7�,10�,13�,17�,20�,23�,26�,29�,32�,35�,58
for(i=1,a=0;i<IMAGE_ROW;i=i+2)            //1,5,9,13,17,21,25,29,33,37//10 �ɼ��⼸�У�Ȼ������ƽ����ֵ
  {                                            //1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39
  yuzhi[a]=trends_threshold(i);
  xcs_maxphoto+= yuzhi[a];          //��ֵ���ܺ�
  a++;
  }  
 /* for(i=0,a=0;i<IMAGE_ROW;i++) {
   if(i=caiji[a]) {
    yuzhi[a]=trends_threshold(i);
    xcs_maxphoto+= yuzhi[a]; 
     a++;
   }} */      
 for(a=0;a<20; a++)                  //���������С��ֵ
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
    xcs_maxphoto=115;//��̬��ֵ���ֳ�֮��ȥ���ڡ�
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
    { if(xcs_maxphoto>=100)                          //��sd������д��������Ϣ
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
 
 #define MIN_WHITE_POT    5 //�׵����С��Ŀ ,����׵��ڱ�Ե��ô���ĵ�ĸ������ܻ�С
 
 

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
  //�����㷨ʱ����õ��ı�������ֵ
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
 
  staticcenter = 200;     //���ֵ���Ϊ255
 //---------׼ȷ���ҳ���1��2�е���������---------ֻ��2�С���������ǰ׵�11111
   for(i=0;i<2;i++)
     {
     if( car_info_old>IMAGE_COLUMN/2)         //ӵ�м��书�ܣ������һ���ɼ����е��λ��
       {     
         counter=0;
        pucTemp= puca_BufferProcess+i*IMAGE_COLUMN+IMAGE_COLUMN-1;//  ����߿�ʼѰ��
                  
       for(j=IMAGE_COLUMN; j>0; j--,pucTemp--) //--��Ҫע��ĵط�Ϊ��ÿ�е�ǰ10�ж��Ƿѵ㣬������Ҫ��
            {
                 temp_index =  i*Max_zero/2+counter;                         //�ų������м�һ���ڵ�ĸ���                      
                  if(((*pucTemp)==0)||(((*pucTemp)==1)&&(*(pucTemp+1)==0)&&((pucTemp+1-(puca_BufferProcess+(i)*IMAGE_COLUMN))<IMAGE_COLUMN)))          //ʶ��׵�     
                       {
                             tempinfo[temp_index ].center+=j-1;
                             tempinfo[temp_index ].number+=1;
                              if((tempinfo[temp_index ].number>=IMAGE_COLUMN-2)&&(flag_shizi_old!=0))//��ʮ����
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
                             
                            else     //����2���㡣�ѷѵ�ȥ��
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
       pucTemp= puca_BufferProcess+i*IMAGE_COLUMN;      //���ұ߿�ʼѰ��
                  
       for(j=0; j<IMAGE_COLUMN; j++,pucTemp++) //--��Ҫע��ĵط�Ϊ��ÿ�е�ǰ10�ж��Ƿѵ㣬������Ҫ��
            {
                 temp_index =  i*Max_zero/2+counter;                 //�ų������м�һ���ڵ�ĸ���                              
                  if((( *pucTemp)==0 )||((*(pucTemp)==1)&&(*(pucTemp+1)==0)&&((pucTemp+1-(puca_BufferProcess+(i)*IMAGE_COLUMN))<IMAGE_COLUMN)))         //ʶ��׵�     
                       {
                             tempinfo[temp_index ].center+=j;
                             tempinfo[temp_index ].number+=1;
                             if((tempinfo[temp_index ].number>=IMAGE_COLUMN-2)&&(flag_shizi_old!=0))//��ʮ����
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
                           if(tempinfo[temp_index ].number>=8) { //4  //�ų������м�һ���ڵ�ĸ���
                                 counter++;  
                           }
                             
                            else     //����2���㡣�ѷѵ�ȥ��
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
        
          //��ʼ�Ƚ���2�е����ĵ��Ƿ��࿿
                for(i=0;i<Max_zero/2;i++) 
                {
                  if(tempinfo[i].number!=0) 
                  {                                                                                                                          //20 15
                       if(abs((tempinfo[i].center)/(tempinfo[i].number) /*- IMAGE_COLUMN/2*/-car_info_old)<=25+(((flag_shizi_old==1)||(shizi_old==1))?10:0))//28  20�������ĵ�ܿ���?
                       {
                         goto out1;
                       }
                       
                  }    
                }           
            out1:;    
                if(i!=Max_zero/2) //�ҵ���
                 {
                    PhotoLineInfoOld[0].center=tempinfo[i].center/tempinfo[i].number;
                    PhotoLineInfoOld[0].number=tempinfo[i].number;
                    staticcenter =  PhotoLineInfoOld[0].center;//ȡ������1��
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
                 else//ֻ�ܰѵ�����2�е�����׼��һ��    ��ʱ��̭�� 1��
                 {
					           for(j=0;j<Max_zero/2;j++) 
                     if(tempinfo[Max_zero/2+j].number!=0) 
                       if(abs((tempinfo[Max_zero/2+j].center)/(tempinfo[Max_zero/2+j].number)-car_info_old)<=25+((flag_shizi_old==1)||(shizi_old==1))?10:0)//28  20 �������ĵ�ܿ���?
                       {
						   PhotoLineInfoOld[1].center=tempinfo[Max_zero/2+j].center/tempinfo[Max_zero/2+j].number;
                           PhotoLineInfoOld[1].number=tempinfo[Max_zero/2+j].number;
                    
                            PhotoLineInfoOld[0].center= PhotoLineInfoOld[1].center;
                            PhotoLineInfoOld[0].number=PhotoLineInfoOld[1].number;
                           staticcenter =  PhotoLineInfoOld[0].center;//ȡ������1��   }
                 }
                 }                     
   if(staticcenter==200)   //������С�������ȫ�ܷ��ˣ�û�о���. �˳�Ϊ��
   { 
   paochu++;
  if(paochu>=2){
   paochu=0;
   staticcenter=IMAGE_COLUMN/2;
   } else
      return;
   }
 //-------------------------------
 //-------�ߵ�������˵��һ������-��ʼȷ��������������--------------
 //- ���˼��Ϊ�� ʣ���еĲο��㶼�ο� 1 2 ���е����ĵ�������
 //-������Ŀ��Ϊ����������
 
  find_r_l = PhotoLineInfoOld[1].center-PhotoLineInfoOld[0].center ;

  out5:;//��ʮ����
 
//--------------------------------��ʮ�еĴ�ѭ����ԭ������"i--" -------------------
  for(i=2;i<IMAGE_ROW;i++)    
   {
         pucTemp=puca_BufferProcess+(i)*IMAGE_COLUMN; 
         if(*(pucTemp+staticcenter)==0)  //��ǰ�����Ϊ�׵�
           {
                PhotoLineInfoOld[i].center+=staticcenter;
                PhotoLineInfoOld[i].number++;
                   
                  for(j=staticcenter+1;j<IMAGE_COLUMN;j++)             // j<staticcenter+PHOTO_BLACK_WIDTH&&
                  {
                       if(*(pucTemp+j)==0)  //�а׵�
                      {
                         PhotoLineInfoOld[i].center+=j;
                         PhotoLineInfoOld[i].number++;
                      } 
                      else          //ȥ��ͼ���м�һ�����ŵ�
                      { 
					    if(*(pucTemp+j+1)==0&&(j+1)<IMAGE_COLUMN)
					          {
                         PhotoLineInfoOld[i].center+=j;
                         PhotoLineInfoOld[i].number++;
                      } 
                      else
						         break; 
                                          //�ұ�Ѱ�����
                  }
                  }
                 
                  
                  for(k=staticcenter;k>0; k--)                        //j>temp_index&&
                  {
                       if(*(pucTemp+k-1)==0)  //�а׵���������k-1��Ϊ�˽�Լ�ռ䣬��ȻkҪ����ɷ��ű���
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
						           } //��߱�Ѱ�����
						         }
				   //**************************    //ʮ����
                  if(j==IMAGE_COLUMN){
                   if(PhotoLineInfoOld[i].center/PhotoLineInfoOld[i].number<53)   //����������������ĵ��λ�����ж�
                     PhotoLineInfoOld[i].center=PhotoLineInfoOld[i].number*(53);
                      if(shizi_l==0)
                       shizi_l=i;                           //ʮ������Ҽ�
                     } 
                  //*********************
                 //*********************** ***ʮ����
                 if(k==0){            
                 if(PhotoLineInfoOld[i].center/PhotoLineInfoOld[i].number>(53))
                   PhotoLineInfoOld[i].center=PhotoLineInfoOld[i].number*(53);
                     if(shizi_r==0)
                       shizi_r=i;                            //ʮ��������
                 }
                 //***********************************��������ַ�������ʮ���䣬��ת���߲����õ�һ����
				 if(k==0&&j==IMAGE_COLUMN)
				 {
                    PhotoLineInfoOld[i].center=PhotoLineInfoOld[i-1].center*IMAGE_COLUMN; 
                   if(flag_shizi_w==0)
                      flag_shizi_w=i;
                   flag_shizi_sum++;
                            
				 }
		 }           
//----------------��ǰ�����Ϊbai��-------------------------------------
        else    //��ǰ�����Ϊ�ڵ�
             {
                  find_over = 1;//��ʾѰ�ҽ���
                if(find_r_l>0) 
                {
                  for(j=staticcenter+1;j<staticcenter+12&&j<IMAGE_COLUMN;j++) 
                    {
                         if(*(pucTemp+j)==0)  //�а׵�
                        {
							 PhotoLineInfoOld[i].center+=j;
							 PhotoLineInfoOld[i].number++;
                            find_over = 0;//��ʾѰ�ҽ���
                        } 
                        else    //�����׵���˳���
                       {                             //��������������������Ȳ���ȥ���ų���
                        if(find_over==0)
                        break;   //�ұ�Ѱ�����
                       }
                    
                    }
                     if(PhotoLineInfoOld[i].number>=2)  // �����кڵ�
                        {
                          goto out2; //�ҵ�Ŷ�� 
                       }
                       PhotoLineInfoOld[i].number = 0;
                       PhotoLineInfoOld[i].center =0;
                
                }
                if(find_r_l<0)     //����û���ҵ���    
                  {
                        find_over = 1;//��ʾѰ�ҽ���
                      for(j=staticcenter;j>staticcenter-12&&j>=1;j--) 
                      {
						           if(*(pucTemp+j-1)==0)  //�кڵ�
                          {
                             PhotoLineInfoOld[i].center+=j-1;
                             PhotoLineInfoOld[i].number++;
                              find_over = 0;//��ʾѰ�ҽ���
                          } 
                          else    //�����׵���˳���
                          {
                              if(find_over==0)
                              break;   //�ұ�Ѱ�����
                         }
                      } 
                       if(PhotoLineInfoOld[i].number>=2)  // �����кڵ�
                          {
                              goto out2; //�ҵ�Ŷ�� 
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
     if(PhotoLineInfoOld[i].number!=0)  // �����кڵ�
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
       
out3:;                                                                          //��ʮ���䣬���ּ��ĵ��ڷſ�
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
 //��sd������д��ÿһ��ͼ���ת��ο��е��е�ֵ
 //#####################################################################################
 /*if(g_car_go==1)
  printp(uart_putchar,"z%d,",PhotoLineInfoOld[2].center );  
*/
}



/*
***************************************************************************************************      
*  ���жϴ���
*���ܣ� a ������ͼ��2ֵ��������task1
*       b ���¿��������жϡ����Ҫ�����жϵı�־
*       c �ɼ������ĸ�λ
************************************************************************************************** 
*/
unsigned int  jiange_m=0;    //�ǲ��Ǽ��(jiange)��8��
unsigned char jiange_speed =0;
unsigned char g_photo_over=0;
unsigned char g_speed_set = 0;

unsigned char chang_count = 0;   //�����г��ź��Ƿ�Ӷ�
unsigned char speed_get_time = 0;//�ٶȲɼ�ʱ����Сһ��
extern unsigned char g_car_go ; //�Ƿ񷢳� 0 ��ʾ������ 1 ��ʾ����


#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
void  Port1_interrupt(void) 
 {  
    
     //�����г��ź��Ƿ�Ӷ�
      if(chang_count++>=50) 
      {
       chang_count =0;
      }
      
      TFLG1_C1F=1; // �峡�жϱ�־ 

       
      jiange_m=0;  //��������
       
       if(g_time_2s<130&&time_2s_counter++>6) 
       {
          time_2s_counter = 0;
          g_time_2s++;
       }


 //--------����ٶȲɼ�------------------------------
// if(g_car_go==1) //�����Ѿ��ṩ����ʼ������ 
//       set_speed_PD();
//--------����ٶȲɼ�----------------------------------
 
       TFLG1_C0F=1; // �����жϱ�־ --ע������Ǳ���ġ��мǣ���������������
       TIE_C0I =1;// ���ж�  
       TFLG1_C1F=1; // �峡�жϱ�־ 
       

} 

/*
*****************************���ж�*********************************************************************
**    NAL�ƣ�ÿ��25֡��һ֡��������ôÿ�����50������ζ��20MS����һ��ͼ�������
*ԭ�� ��356x 292 pixels�����Ϊ����292�У�һ����356���㡣  2
*      ��ϵͳ�������õ�����Ϊ��  5*image_row = �У���ôʣ�µ�����Ϊ110 ʣ�µ�ʱ��Ϊ 20*110/292 =  7ms
*      �ټ��ϳ�����ʱ�䣬��ô
*      ���汾���ж��м����� �����źš�����ͨ���
*ע�⣺����ʱ�������ϵͳ���ж��У������в�Ҫ�оֲ����������мǣ�����ʱ�䲻ȷ����
************************* *******************************************************************************
*/

unsigned char hang_i=0; //���ж������õļ�¼ÿ�е�ĸ����ı���
#define JIANGE_HANG 3  //������ݱ������3      ��ȻҲ����̫��
unsigned char  jiange_speednow =0;
unsigned char *chang_pucTemp=NULL;


 //ico2 ���벶׽�ж�
 
 unsigned char speed_cesu_num =  0;
 
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
 void   Port0_interrupt(void) 
{
 
  if(flag_speed==1)                 //����״̬�г���ԶЩ
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
               
           jiange_speednow++;  //��¼���ߵ���Ŀ
        if(jiange_speednow >= IMAGE_ROW){
           jiange_speednow=0;
           g_car_show_yn = 1;//������ʾ�����Դ����ⳡ������   
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
               
           jiange_speednow++;  //��¼���ߵ���Ŀ
        if(jiange_speednow >= IMAGE_ROW){
           jiange_speednow=0;
           g_car_show_yn = 1;//������ʾ�����Դ����ⳡ������   
            TIE_C0I = 0;
        }
    } 
   }
      
    jiange_m++;
    TFLG1_C0F = 1; 
    
       
}   
