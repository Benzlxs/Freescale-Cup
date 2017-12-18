#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"


unsigned char slow_=0;
unsigned char sensor[15]=             
{
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0
};                      
unsigned int sensor_[15]=
{
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0
};
int sensor_ad[15];
unsigned int sensor_ad_h[15];
unsigned int sensor_ad_l[15];
unsigned int sensor_max_min[15][2]=
{
45,1900, //0      
45,1900,         
45,1900, //2
45,1900,
45,1900, //4
45,1900, //5
45,1900, //6
45,1900, //7
45,1900, //8
45,1900, //9
45,1900, //10
45,1900,
45,1900, //12
45,1900,
45,1900, //14

};

int pos_=0; //偏差 全局变量
unsigned int MySysTime=0,rt=0;
///////////////////////////////////
int pos_v_de=1;   // 偏差 的移动 方向
unsigned int timer_1=0; //时间轴
unsigned int pos_time=10; //偏差的停留时间
int pos_old=0;
///////////////////////////////////
unsigned char AD_debug[15][9]={0}; //三个时段 采集到的ad

//路况采集 Xms 中断
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 66 timer_RoadInfoCollect_ms(void)
{
    static unsigned int temp_ = 0;
    static unsigned char Snumber = 1; //与传感器对应。
    static unsigned char step_=2;     //
    static unsigned int IntTime[6] = {20,90,12,20,20,200}; //  各时段的定时值
    static unsigned char AD_[15][9]={0}; //三个时段 采集到的ad
    int i,j,temp;
    int T_sum=0; //力矩之和
    int ad_sum;    //传感器的ad之和
    unsigned char num_on=0;
    char i_sum;
    char door_L=0,door_R=0,door_L_=0,door_R_=0; //黑线连续可能出现的区域
    unsigned char a,b;
    static unsigned int sensor_pr[15]=
    {
        28,30,38,
        38,38,38,
        38,38,38,
        38,38,38,
        38,30,28,
    };
    PITTF_PTF0=1;//清中断标志位
    
    if(Snumber >=1 && Snumber <= 15) 
    {
        PORTA=Snumber-1;
        if(step_==1)
        {
            PITLD0 = IntTime[step_-1];
            PITFLT_PFLT0=1; 
            /*
            while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_[Snumber-1][0] = ATD0DR0;  //读取转换的结果
	          AD_debug[Snumber-1][0] = ATD0DR0;  //读取转换的结果
	          while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_debug[Snumber-1][1] = ATD0DR0;  //读取转换的结果
	          AD_[Snumber-1][1] = ATD0DR0;  //读取转换的结果
	          while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_debug[Snumber-1][2] = ATD0DR0;  //读取转换的结果
	          AD_[Snumber-1][2] = ATD0DR0;  //读取转换的结果
	          */
        }
        if(step_==2)
        {
            PITLD0 = IntTime[step_-1];
            PITFLT_PFLT0=1; 
            //PORTE_PE3=1;  //led_==on;
        }
        if(step_==3)
        {
            PITLD0 = IntTime[step_-1];
            PITFLT_PFLT0=1; 
            while(!ATD0STAT2_CCF0);   //等待转换结束   
  	        AD_[Snumber-1][3] = ATD0DR0;  //读取转换的结果
	          AD_debug[Snumber-1][3] = ATD0DR0;  //读取转换的结果
	          while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_[Snumber-1][4] = ATD0DR0;  //读取转换的结果
	          AD_debug[Snumber-1][4] = ATD0DR0;  //读取转换的结果
	          while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_[Snumber-1][5] = ATD0DR0;  //读取转换的结果
	          AD_debug[Snumber-1][5] = ATD0DR0;  //读取转换的结果
	          //PORTE_PE3=0;  //led_==off;
	          
	          
	          Snumber = Snumber+1;
	          
            if(Snumber == 2){Snumber = 3;}
            if(Snumber == 4){Snumber = 5;}
            if(Snumber == 12){Snumber = 13;}
            if(Snumber == 14){Snumber = 15;}
            
        }
        if(step_==4)
        {
            PITLD0 = IntTime[step_-1];
            PITFLT_PFLT0=1; 
        }
        if(step_==5)
        {
            PITLD0 = IntTime[step_-1];
            PITFLT_PFLT0=1; 
            /*
            while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_[Snumber-1][6] = ATD0DR0;  //读取转换的结果
	          AD_debug[Snumber-1][6] = ATD0DR0;  //读取转换的结果
	          while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_[Snumber-1][7] = ATD0DR0;  //读取转换的结果
            AD_debug[Snumber-1][7] = ATD0DR0;  //读取转换的结果
	          while(!ATD0STAT2_CCF0);   //等待转换结束   
	          AD_[Snumber-1][8] = ATD0DR0;  //读取转换的结果
	          AD_debug[Snumber-1][8] = ATD0DR0;  //读取转换的结果
	          */
	          /*
	          Snumber = Snumber+1;
	          
            if(Snumber == 2){Snumber = 3;}
            if(Snumber == 4){Snumber = 5;}
            if(Snumber == 12){Snumber = 13;}
            if(Snumber == 14){Snumber = 15;}
            */
        }
        step_=step_+1;
        if(step_>=4){step_=2;}
            
    }
    if(Snumber == 16)
    {
        PORTA = 0xff;
        
        PITLD0 = IntTime[5];
        PITFLT_PFLT0=1;    
        
        Snumber = 1;
        /////////////////////////////////////////////////////////////////////////////
	      //进中断次数的计数器，2ms 一次 ，为系统处理其他事物 提供时间 标识
	      MySysTime++;
	      if(MySysTime==65000){MySysTime=0;}
        
        // 计算偏差
        // 计算 sensor_[]  sensor[]
        for(i=0; i<=14; i++)
        {
            //temp = (AD_[i][6]+AD_[i][7]+AD_[i][8])  //关断后的值
            //       - (AD_[i][3]+AD_[i][4]+AD_[i][5]);    //发射中的值
            sensor_ad_h[i] = (AD_[i][3]+AD_[i][4]+AD_[i][5]); //发射中的值
            //sensor_ad_l[i] = (AD_[i][6]+AD_[i][7]+AD_[i][8]); //关断后的值
            //sensor_ad[i] = temp;   // 差值：  环境光-发射值
            
            // 自动获取最大  最小值
            if(i_start <= 14 && i_start >= 2)
            {
              
                if(sensor_ad_h[i]>=sensor_max_min[i][0]) //不断的更新极值
                {
                    sensor_max_min[i][0] =  sensor_ad_h[i]; //黑线
                }
                if(sensor_ad_h[i]<=sensor_max_min[i][1]) //不断的更新极值
                {
                    sensor_max_min[i][1] = sensor_ad_h[i];  //白线 
                }

            }
          
            if(sensor_ad_h[i]<=sensor_max_min[i][1])//过小的保护
            {
                sensor_ad_h[i]=sensor_max_min[i][1];
            }
            if(sensor_ad_h[i]>=sensor_max_min[i][0])//过大的保护
            {
                sensor_ad_h[i]=sensor_max_min[i][0];  
            }
            //  换算成百分比 转化成：  0~100 
            sensor_[i] = (     100*(sensor_ad_h[i]-sensor_max_min[i][1])
                              /(sensor_max_min[i][0]-sensor_max_min[i][1])  );              
        }
        //未使用的            
        sensor_[1]=0;sensor_[3]=0;
        //sensor_[5]=0;sensor_[7]=0;sensor_[9]=0;
        sensor_[11]=0;sensor_[13]=0;   
        /////////////////////////////////////////////////////////////////////
	      //  获得当前的位移偏差  >>  pos
	      //  (-)|(+) 可用有效传感器位置， l偏为负, r偏的时候为正
	      //  14 13 12 11 10 9 8 7 6 5 4 3 2 1 0  顺序 15 > 1
	      // -14-13-12-11-10-9-8-7-6-5-4-3-2-1 0 +1+2+3+4+5+6+7+8+9+10+11+ ... +100
	      /////////////////////////////////////////////////////////////////////

	      for(i=0; i<=14; i++) // 传感器的正下方
	      {
		        //此值越小越安全, 越小看到的点的直径越大，对黑线越敏感 
		        if(sensor_[i]>=sensor_pr[i]+20){sensor[i]=1;}     //晚上  住处
		        else                           {sensor[i]=0;}     //离散开 ， 利于分辨中间的值
	      }
	      /////////////////////////////////////////////////////////
        num_on = 0;//获得压线传感器的个数 num_on,
	      i_sum =0;//压线传感器的标号(0~14)之和
	      
	      //求出  宽度  滤波
	      
	      door_L = 7+4 - pos_/2;
	      door_R = 7-4 - pos_/2;
	      if(door_L>14){door_L=14;}
	      if(door_R< 0){door_R=0;}
	      
	      ////////////////////////////////////////
        //计算  对称 位置  的  窗口 重量 ！
        door_R_ = 14-door_L; 
        door_L_ = 14-door_R;
	      ///////////////////////////////////////
	      a=0;
        for(i=door_R_; i<=door_L_; i++)
        {
             if(i==1 || i==3 || i==11 || i==13){a++;}
        }
        b=0;    
        for(i=door_R_; i<=door_L_; i++)
        {
             if(sensor[i]==0x01)//有一个压线 黑线=1
		         {
		             b++;
		         }
        }
        ////////////////////////////////////////
        for(i=door_R; i<=door_L; i++)
	      //for(i=0; i<=14; i++)
	      {
		        if(sensor[i]==0x01)//有一个压线 黑线=1
		        {
			         num_on = num_on + 1;   //压线传感器的个数
			         i_sum  = i_sum + (7-i);    //压线传感器的标号(0~14)之和
		        }
	      }
	      if(num_on!=0) //监测到有传感器压线
	      {
 			      if((10*b)/(door_L_-door_R_-a+1) >= 5 && PTS_PTS2==0) //此值与 地板 有很大的关系 ！！！！！！
 			      {
 			          pos_ = pos_old;
 			      }
 			      else
 			      {
 			          pos_ = (2*i_sum)/num_on;  //重心
 			          /*
 			          if(num_on>=5 && abs(pos_)<=4)  //三角 或 腾空
 			          {
 			              slow_=1;  
 			              pos_ = 0; 
 			          }
 			          else
 			          {
 			              slow_=0;   
 			          }
 			          */
 			      }
	      }
	      else//没有一个压线，则跑飞，保持上一次的位置。
	      {
		        pos_ = pos_; //是静态变量         
	      }
	      

	      ////////////////////////////////////////////////////////////////////////////////
        //     记录时间            偏差停留时间
        ////////////////////////////////////////////////////////////////////////////////
        
	      timer_1++; //采集传感器信息的时间轴
	      
	      if(pos_ != pos_old) //产生变化，计算上一个位置的生存周期、偏移速度，方向
	      {
            //获得生存周期，即上一个位置停留的时间
		        pos_time = timer_1;
   
		        //根据生存周期，计算出偏差速度
		        if(timer_1 <= D_)
		        { 
			          //获取
                pos_time = timer_1;
		        } 
		        else 
		        {
		            pos_time = D_ ; //如果生存周期太长，认为偏移速度很慢
		        }
            //保证时间轴没有越界误差！
		        timer_1 = 0;//重新开始计时
		        //////////////////////////////////////////////////////////////////
		        //////////////////////////////////////////////////////////////////
		        //判断偏差速度的方向，

		        if(pos_old==0 && pos_!=0 )   //从中心线偏移，偏差速度加大
		        {
			          if(pos_ > 0)//需右拐,
			          {
			  	          pos_v_de = 1;
			          }
			          else        //需左拐，
			          {
			  	          pos_v_de = 1;
			          }
		        }
	  	      else if(pos_old >0 && pos_>=0) //位于右侧,偏差为正值，需右拐,
		        {
			          if(pos_>pos_old)//偏差增大
			          {
				            pos_v_de = 1;
			          }
			          else               //偏差减小
			          {
				            pos_v_de = -1; //偏差在减小，可适当的调小此值
			          }
		        }
		        else if(pos_old <0 && pos_<=0) //位于左侧，偏差为负值，需左拐，
		        {
			          if(pos_>pos_old)//偏差减小
			          {
				            pos_v_de = -1; //偏差在减小，
			          }
			          else               //偏差增大
			          {
				            pos_v_de = 1;
			          }
		        }
	      }
        pos_old = pos_;     
    }
           
}