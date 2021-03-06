#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"


volatile unsigned int counter_column=0; // 行计数
 
 
unsigned char uca_Buffer2[IMAGE_ROW][IMAGE_COLUMN];  
unsigned char *p_addr_Buffer1[IMAGE_ROW];
unsigned char  flag_yj ;              //处理远近的标志   
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
}*/  ;  //实验测得
/* {
4,13,21,28,34,40,45,50,57,63,70,75,78,81,84,86,88,90,93,96,99,102,106,108,110,112,114,116,118,121,124,126,128,130
}  ;  //实验测得*/  ; 
//速度控制时使用的变量  
	 unsigned char flag_j_w;
	 unsigned char flag_j_sum;
	 unsigned char flag_g;
	 unsigned char flag_shizi_sum=0; 
	 unsigned char tingzhi_xian;
	 unsigned char tingzhi_sum;
	 unsigned char tingche=0;
	 unsigned char flag_zd=0;          //直道的标志位,在程序开始的时候需要把这个值赋0
	 unsigned char  flag_shizi_w=0;   //十字弯的标志�
   unsigned char G_CAR_SPEED_old;   //记录上次的速度
   unsigned char    flag_s_w=0;
   unsigned char *puca_BufferProcess=&uca_Buffer2[0][0];
   char  g_all_wandao_qulv;
   char  g_all_wandao_qulv_old ;
 struct photolineinfo  PhotoLineInfoOld[IMAGE_ROW];
unsigned char   flag_yj=0   ;           //采集远近的标志 
unsigned char   zhidao=0;
unsigned int     xcs_maxphoto ;
unsigned int    xcs_maxphoto1=110;
extern unsigned char pwm_temp; //正转占空比的影子
unsigned char car_info_old=53;
unsigned char paochu=0;
unsigned char shizi_r;
unsigned char shizi_l;
unsigned char  light_value=0;
unsigned char g_time_2s=0; //2秒发车标志
unsigned char   time_2s_counter = 0;
unsigned char   light_sum;
unsigned char   g_line_yn  =0;
unsigned char   flag_shizi_old=0;
unsigned int    high_G_CAR_SPEED;
unsigned char  shizi_old=0;
unsigned int    mid_G_CAR_SPEED;
unsigned char   ruwan_time=0;//入弯的标志位 
#define Max_zero  8

struct photolineinfotemp 
{
       int center;   //zhong xin    >=600
       unsigned char number;    // hei dian shu mu
};

 //////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////
 char car_pos[4];  ////偏差的位置        22
void Get_photo_quanzhongBH(void) 
{

  	char i,j;
    char trace;
    unsigned char flag_z=0;//是不是小车可以直线通过的标志
    int temp,	center_sum_all,	center_counter,center_;  
    char startline,endline; 
    unsigned char *pucTemp;
    unsigned char z=0,s;//分别记录黑线和白线的宽度
    int fangcha1_p,fangcha1_s,fangcha2_p,fangcha2_s;
    char car_pos[4];
      flag_s_w=0;           //赛道的类型
      if((flag_j_sum>=2)||((flag_g<=38)&&(flag_g>=20))) //刚刚入弯的状态
      {
        flag_s_w=0;
        G_CAR_SPEED=low_G_CAR_SPEED;
        if(flag_j_sum>=4)           //完全入弯
          { 
             ruwan_time++;
             
              if(ruwan_time<=26)        //从开始入弯，小车每次行驶5cm，入弯需要1.2m的距离
            {
            G_CAR_SPEED=low_G_CAR_SPEED;
            }
              else
              {
                 flag_s_w=1;
                G_CAR_SPEED= G_CAR_SPEED_old+2;               //在弯道里面慢慢的加速
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
    
     ruwan_time=0;        //进入直道给弯道表示给0
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
        
        	     
              for(i=startline; i<IMAGE_ROW-2;i++)       //计算整幅图的曲率
              {
                  if(PhotoLineInfoOld[IMAGE_ROW-2-i].number!=0)
                   {
                      
                      temp = IMAGE_COLUMN/2- PhotoLineInfoOld[IMAGE_ROW-9-i].center;
            					center_sum_all += temp *(abs(temp));
            					center_counter += abs(temp);  //abs 为权重注意，权重可能为0！！！！！！！
                     ///------访查-----紧查1 和3------
                      if(j==1)  //正2 行
                      {
                        fangcha1_p +=  (temp*temp); 
                        fangcha1_s +=  (temp);
                      }
                      if(j==3) // 正4 行。
                       {
                        fangcha2_p += (temp*temp); 
                        fangcha2_s += (temp);
                      }
                    //-------访查-------------
          					  endline++; //有效行计数	
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

//------------------判断是不是直线.这里一定要保证，识别的正确弯道，直道。！！！！！！！！！！
       if(car_pos[0]!=100&&car_pos[1]!=100&&car_pos[2]!=100&&car_pos[3]!=100) 
      {

        //---北航算法 x = ay + b;                                                               
         yya=ys=0;
         xys=xs=0;
         //准备工作就绪。
         ys =trace*trace;
         yya = 0+ys + 4*ys +9*ys;
         ys =  6*trace;
         xs = car_pos[0] + car_pos[1]+ car_pos[2]+car_pos[3];
         xys =trace*( car_pos[0]*0+1*car_pos[1]+ 2*car_pos[2]+3*car_pos[3]); 
         //---开始计算 a b 
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
           //7-18 本次引入曲率 ，这个绝对值越大说明越弯。 通过放大后他从0-30 
         g_all_wandao_qulv = (10*(4*xys-xs*ys))/f_z;
	     }
	   }
    G_CAR_SPEED=high_G_CAR_SPEED-2*abs(g_all_wandao_qulv);      // 能过十字弯道了，这里的控速是不是要改变
    if(abs(g_all_wandao_qulv)<=5)
      flag_s_w=2;
     else
      flag_s_w=3;
     if(G_CAR_SPEED<=mid_G_CAR_SPEED)
     G_CAR_SPEED=mid_G_CAR_SPEED;
    
    for(j=0;j<IMAGE_ROW;j++) 
    {
        if(abs(PhotoLineInfoOld[j].center-IMAGE_COLUMN/2)>20+(j<32?25:0))    //20和30还需要测试      //小车能直线通过的赛道
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
       flag_s_w=5;                   //表示十字弯 
      G_CAR_SPEED=low_G_CAR_SPEED+10;                         
   /*   if(flag_s_w==0)
      G_CAR_SPEED=low_G_CAR_SPEED;              //十字弯如急弯
      if(flag_s_w==6)
      G_CAR_SPEED=low_G_CAR_SPEED+20;    */       //十字弯出弯
  }
  G_CAR_SPEED_old= G_CAR_SPEED;   
      
      
 //*******************************************停止线     
   if(g_time_2s>=30)
   { 
   i=0;
   for(j=0;j<16;j++)                                //是否开识别停止线功能的条件
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
   PITCFLMT_PITE = 0;//关掉检查停止线的功能
   }
 
}  
/*
*******************************************************************************
*          图像2值化 
* 黑1 白0
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
  if(flag_dj==1)                    //动态阈值采集
{   xcs_maxphoto=0;                                 //1，3�,7�,10�,13�,17�,20�,23�,26�,29�,32�,35�,58
for(i=1,a=0;i<IMAGE_ROW;i=i+2)            //1,5,9,13,17,21,25,29,33,37//10 采集这几行，然后求其平均阈值
  {                                            //1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39
  yuzhi[a]=trends_threshold(i);
  xcs_maxphoto+= yuzhi[a];          //阈值的总和
  a++;
  }  
 /* for(i=0,a=0;i<IMAGE_ROW;i++) {
   if(i=caiji[a]) {
    yuzhi[a]=trends_threshold(i);
    xcs_maxphoto+= yuzhi[a]; 
     a++;
   }} */      
 for(a=0;a<20; a++)                  //求最大与最小阈值
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
    xcs_maxphoto=115;//静态阈值到现场之后去调节。
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
    { if(xcs_maxphoto>=100)                          //往sd卡里面写入舵机的信息
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
 
 #define MIN_WHITE_POT    5 //白点的最小数目 ,如果白点在边缘那么他的点的个数可能会小
 
 

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
  //控制算法时候会用到的变量给初值
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
 
  staticcenter = 200;     //这个值最大为255
 //---------准确的找出第1，2行的中心坐标---------只找2行。否则就算是白点11111
   for(i=0;i<2;i++)
     {
     if( car_info_old>IMAGE_COLUMN/2)         //拥有记忆功能，借鉴上一场采集的中点的位置
       {     
         counter=0;
        pucTemp= puca_BufferProcess+i*IMAGE_COLUMN+IMAGE_COLUMN-1;//  从左边开始寻找
                  
       for(j=IMAGE_COLUMN; j>0; j--,pucTemp--) //--需要注意的地方为，每行的前10列都是费点，都不能要。
            {
                 temp_index =  i*Max_zero/2+counter;                         //排除赛道中间一个黑点的干扰                      
                  if(((*pucTemp)==0)||(((*pucTemp)==1)&&(*(pucTemp+1)==0)&&((pucTemp+1-(puca_BufferProcess+(i)*IMAGE_COLUMN))<IMAGE_COLUMN)))          //识别白点     
                       {
                             tempinfo[temp_index ].center+=j-1;
                             tempinfo[temp_index ].number+=1;
                              if((tempinfo[temp_index ].number>=IMAGE_COLUMN-2)&&(flag_shizi_old!=0))//过十字弯
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
                             
                            else     //不到2个点。把费点去掉
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
       pucTemp= puca_BufferProcess+i*IMAGE_COLUMN;      //从右边开始寻找
                  
       for(j=0; j<IMAGE_COLUMN; j++,pucTemp++) //--需要注意的地方为，每行的前10列都是费点，都不能要。
            {
                 temp_index =  i*Max_zero/2+counter;                 //排除赛道中间一个黑点的干扰                              
                  if((( *pucTemp)==0 )||((*(pucTemp)==1)&&(*(pucTemp+1)==0)&&((pucTemp+1-(puca_BufferProcess+(i)*IMAGE_COLUMN))<IMAGE_COLUMN)))         //识别白点     
                       {
                             tempinfo[temp_index ].center+=j;
                             tempinfo[temp_index ].number+=1;
                             if((tempinfo[temp_index ].number>=IMAGE_COLUMN-2)&&(flag_shizi_old!=0))//过十字弯
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
                           if(tempinfo[temp_index ].number>=8) { //4  //排除赛道中间一个黑点的干扰
                                 counter++;  
                           }
                             
                            else     //不到2个点。把费点去掉
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
        
          //开始比较这2行的中心点是否相靠
                for(i=0;i<Max_zero/2;i++) 
                {
                  if(tempinfo[i].number!=0) 
                  {                                                                                                                          //20 15
                       if(abs((tempinfo[i].center)/(tempinfo[i].number) /*- IMAGE_COLUMN/2*/-car_info_old)<=25+(((flag_shizi_old==1)||(shizi_old==1))?10:0))//28  20两个中心点很靠近?
                       {
                         goto out1;
                       }
                       
                  }    
                }           
            out1:;    
                if(i!=Max_zero/2) //找到了
                 {
                    PhotoLineInfoOld[0].center=tempinfo[i].center/tempinfo[i].number;
                    PhotoLineInfoOld[0].number=tempinfo[i].number;
                    staticcenter =  PhotoLineInfoOld[0].center;//取倒数第1行
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
                 else//只能把倒数第2行当作标准看一看    暂时淘汰第 1行
                 {
					           for(j=0;j<Max_zero/2;j++) 
                     if(tempinfo[Max_zero/2+j].number!=0) 
                       if(abs((tempinfo[Max_zero/2+j].center)/(tempinfo[Max_zero/2+j].number)-car_info_old)<=25+((flag_shizi_old==1)||(shizi_old==1))?10:0)//28  20 两个中心点很靠近?
                       {
						   PhotoLineInfoOld[1].center=tempinfo[Max_zero/2+j].center/tempinfo[Max_zero/2+j].number;
                           PhotoLineInfoOld[1].number=tempinfo[Max_zero/2+j].number;
                    
                            PhotoLineInfoOld[0].center= PhotoLineInfoOld[1].center;
                            PhotoLineInfoOld[0].number=PhotoLineInfoOld[1].number;
                           staticcenter =  PhotoLineInfoOld[0].center;//取倒数第1行   }
                 }
                 }                     
   if(staticcenter==200)   //到这里小车真的完全跑非了，没有救了. 此场为白
   { 
   paochu++;
  if(paochu>=2){
   paochu=0;
   staticcenter=IMAGE_COLUMN/2;
   } else
      return;
   }
 //-------------------------------
 //-------走到了这里说明一切正常-开始确定其他的行中心--------------
 //- 设计思想为： 剩下行的参考点都参考 1 2 两行的中心点来做，
 //-这样的目的为减少运算量
 
  find_r_l = PhotoLineInfoOld[1].center-PhotoLineInfoOld[0].center ;

  out5:;//过十字弯
 
//--------------------------------三十行的大循环。原来不能"i--" -------------------
  for(i=2;i<IMAGE_ROW;i++)    
   {
         pucTemp=puca_BufferProcess+(i)*IMAGE_COLUMN; 
         if(*(pucTemp+staticcenter)==0)  //当前这个点为白点
           {
                PhotoLineInfoOld[i].center+=staticcenter;
                PhotoLineInfoOld[i].number++;
                   
                  for(j=staticcenter+1;j<IMAGE_COLUMN;j++)             // j<staticcenter+PHOTO_BLACK_WIDTH&&
                  {
                       if(*(pucTemp+j)==0)  //有白点
                      {
                         PhotoLineInfoOld[i].center+=j;
                         PhotoLineInfoOld[i].number++;
                      } 
                      else          //去掉图像中间一个干扰点
                      { 
					    if(*(pucTemp+j+1)==0&&(j+1)<IMAGE_COLUMN)
					          {
                         PhotoLineInfoOld[i].center+=j;
                         PhotoLineInfoOld[i].number++;
                      } 
                      else
						         break; 
                                          //右边寻点结束
                  }
                  }
                 
                  
                  for(k=staticcenter;k>0; k--)                        //j>temp_index&&
                  {
                       if(*(pucTemp+k-1)==0)  //有白点在这里用k-1是为了节约空间，不然k要定义成符号变量
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
						           } //左边边寻点结束
						         }
				   //**************************    //十字弯
                  if(j==IMAGE_COLUMN){
                   if(PhotoLineInfoOld[i].center/PhotoLineInfoOld[i].number<53)   //根据正常的弯道中心点的位置来判断
                     PhotoLineInfoOld[i].center=PhotoLineInfoOld[i].number*(53);
                      if(shizi_l==0)
                       shizi_l=i;                           //十字弯的右肩
                     } 
                  //*********************
                 //*********************** ***十字弯
                 if(k==0){            
                 if(PhotoLineInfoOld[i].center/PhotoLineInfoOld[i].number>(53))
                   PhotoLineInfoOld[i].center=PhotoLineInfoOld[i].number*(53);
                     if(shizi_r==0)
                       shizi_r=i;                            //十字弯的左肩
                 }
                 //***********************************如果用这种方法来过十字弯，则转向线不能用第一二行
				 if(k==0&&j==IMAGE_COLUMN)
				 {
                    PhotoLineInfoOld[i].center=PhotoLineInfoOld[i-1].center*IMAGE_COLUMN; 
                   if(flag_shizi_w==0)
                      flag_shizi_w=i;
                   flag_shizi_sum++;
                            
				 }
		 }           
//----------------当前这个点为bai点-------------------------------------
        else    //当前这个点为黑点
             {
                  find_over = 1;//表示寻找结束
                if(find_r_l>0) 
                {
                  for(j=staticcenter+1;j<staticcenter+12&&j<IMAGE_COLUMN;j++) 
                    {
                         if(*(pucTemp+j)==0)  //有白点
                        {
							 PhotoLineInfoOld[i].center+=j;
							 PhotoLineInfoOld[i].number++;
                            find_over = 0;//表示寻找结束
                        } 
                        else    //碰到白点就退出了
                       {                             //在这里属于少数情况，先不加去干扰程序
                        if(find_over==0)
                        break;   //右边寻点结束
                       }
                    
                    }
                     if(PhotoLineInfoOld[i].number>=2)  // 此行有黑点
                        {
                          goto out2; //找到哦了 
                       }
                       PhotoLineInfoOld[i].number = 0;
                       PhotoLineInfoOld[i].center =0;
                
                }
                if(find_r_l<0)     //右面没有找到。    
                  {
                        find_over = 1;//表示寻找结束
                      for(j=staticcenter;j>staticcenter-12&&j>=1;j--) 
                      {
						           if(*(pucTemp+j-1)==0)  //有黑点
                          {
                             PhotoLineInfoOld[i].center+=j-1;
                             PhotoLineInfoOld[i].number++;
                              find_over = 0;//表示寻找结束
                          } 
                          else    //碰到白点就退出了
                          {
                              if(find_over==0)
                              break;   //右边寻点结束
                         }
                      } 
                       if(PhotoLineInfoOld[i].number>=2)  // 此行有黑点
                          {
                              goto out2; //找到哦了 
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
     if(PhotoLineInfoOld[i].number!=0)  // 此行有黑点
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
       
out3:;                                                                          //过十字弯，这种检测的调节放宽
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
 //向sd卡里面写入每一幅图像的转向参考行的中点值
 //#####################################################################################
 /*if(g_car_go==1)
  printp(uart_putchar,"z%d,",PhotoLineInfoOld[2].center );  
*/
}



/*
***************************************************************************************************      
*  场中断处理
*功能： a 开启了图像2值化的任务task1
*       b 重新开启了行中断。这个要清行中断的标志
*       c 采集行数的复位
************************************************************************************************** 
*/
unsigned int  jiange_m=0;    //是不是间隔(jiange)了8行
unsigned char jiange_speed =0;
unsigned char g_photo_over=0;
unsigned char g_speed_set = 0;

unsigned char chang_count = 0;   //测试行场信号是否接对
unsigned char speed_get_time = 0;//速度采集时间缩小一半
extern unsigned char g_car_go ; //是否发车 0 表示不发车 1 表示发车


#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
void  Port1_interrupt(void) 
 {  
    
     //测试行场信号是否接对
      if(chang_count++>=50) 
      {
       chang_count =0;
      }
      
      TFLG1_C1F=1; // 清场中断标志 

       
      jiange_m=0;  //行数清零
       
       if(g_time_2s<130&&time_2s_counter++>6) 
       {
          time_2s_counter = 0;
          g_time_2s++;
       }


 //--------添加速度采集------------------------------
// if(g_car_go==1) //动力已经提供，开始做控制 
//       set_speed_PD();
//--------添加速度采集----------------------------------
 
       TFLG1_C0F=1; // 清行中断标志 --注意这个是必须的。切记！！！！！！！！
       TIE_C0I =1;// 行中断  
       TFLG1_C1F=1; // 清场中断标志 
       

} 

/*
*****************************行中断*********************************************************************
**    NAL制，每秒25帧，一帧两场，那么每秒就有50场。意味着20MS就有一幅图像产生。
*原理 ：356x 292 pixels，理解为：有292行，一行有356个点。  2
*      本系统中所利用的行数为：  5*image_row = 行，那么剩下的行数为110 剩下的时间为 20*110/292 =  7ms
*      再加上场消隐时间，那么
*      本版本行中断中加上了 发送信号。试验通过�
*注意：在择时纳入操作系统的中断中，程序中不要有局部变量！！切记，否则时间不确定。
************************* *******************************************************************************
*/

unsigned char hang_i=0; //行中断里面用的记录每行点的个数的变量
#define JIANGE_HANG 3  //这个数据必须大于3      当然也不能太大
unsigned char  jiange_speednow =0;
unsigned char *chang_pucTemp=NULL;


 //ico2 输入捕捉中断
 
 unsigned char speed_cesu_num =  0;
 
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
#pragma TRAP_PROC
 void   Port0_interrupt(void) 
{
 
  if(flag_speed==1)                 //高速状态市场放远些
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
               
           jiange_speednow++;  //记录黑线的数目
        if(jiange_speednow >= IMAGE_ROW){
           jiange_speednow=0;
           g_car_show_yn = 1;//可以显示，可以处理这场数据了   
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
               
           jiange_speednow++;  //记录黑线的数目
        if(jiange_speednow >= IMAGE_ROW){
           jiange_speednow=0;
           g_car_show_yn = 1;//可以显示，可以处理这场数据了   
            TIE_C0I = 0;
        }
    } 
   }
      
    jiange_m++;
    TFLG1_C0F = 1; 
    
       
}   
