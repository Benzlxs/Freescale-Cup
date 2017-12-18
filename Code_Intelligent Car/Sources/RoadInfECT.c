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

int pos_=0; //ƫ�� ȫ�ֱ���
unsigned int MySysTime=0,rt=0;
///////////////////////////////////
int pos_v_de=1;   // ƫ�� ���ƶ� ����
unsigned int timer_1=0; //ʱ����
unsigned int pos_time=10; //ƫ���ͣ��ʱ��
int pos_old=0;
///////////////////////////////////
unsigned char AD_debug[15][9]={0}; //����ʱ�� �ɼ�����ad

//·���ɼ� Xms �ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 66 timer_RoadInfoCollect_ms(void)
{
    static unsigned int temp_ = 0;
    static unsigned char Snumber = 1; //�봫������Ӧ��
    static unsigned char step_=2;     //
    static unsigned int IntTime[6] = {20,90,12,20,20,200}; //  ��ʱ�εĶ�ʱֵ
    static unsigned char AD_[15][9]={0}; //����ʱ�� �ɼ�����ad
    int i,j,temp;
    int T_sum=0; //����֮��
    int ad_sum;    //��������ad֮��
    unsigned char num_on=0;
    char i_sum;
    char door_L=0,door_R=0,door_L_=0,door_R_=0; //�����������ܳ��ֵ�����
    unsigned char a,b;
    static unsigned int sensor_pr[15]=
    {
        28,30,38,
        38,38,38,
        38,38,38,
        38,38,38,
        38,30,28,
    };
    PITTF_PTF0=1;//���жϱ�־λ
    
    if(Snumber >=1 && Snumber <= 15) 
    {
        PORTA=Snumber-1;
        if(step_==1)
        {
            PITLD0 = IntTime[step_-1];
            PITFLT_PFLT0=1; 
            /*
            while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_[Snumber-1][0] = ATD0DR0;  //��ȡת���Ľ��
	          AD_debug[Snumber-1][0] = ATD0DR0;  //��ȡת���Ľ��
	          while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_debug[Snumber-1][1] = ATD0DR0;  //��ȡת���Ľ��
	          AD_[Snumber-1][1] = ATD0DR0;  //��ȡת���Ľ��
	          while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_debug[Snumber-1][2] = ATD0DR0;  //��ȡת���Ľ��
	          AD_[Snumber-1][2] = ATD0DR0;  //��ȡת���Ľ��
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
            while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
  	        AD_[Snumber-1][3] = ATD0DR0;  //��ȡת���Ľ��
	          AD_debug[Snumber-1][3] = ATD0DR0;  //��ȡת���Ľ��
	          while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_[Snumber-1][4] = ATD0DR0;  //��ȡת���Ľ��
	          AD_debug[Snumber-1][4] = ATD0DR0;  //��ȡת���Ľ��
	          while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_[Snumber-1][5] = ATD0DR0;  //��ȡת���Ľ��
	          AD_debug[Snumber-1][5] = ATD0DR0;  //��ȡת���Ľ��
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
            while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_[Snumber-1][6] = ATD0DR0;  //��ȡת���Ľ��
	          AD_debug[Snumber-1][6] = ATD0DR0;  //��ȡת���Ľ��
	          while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_[Snumber-1][7] = ATD0DR0;  //��ȡת���Ľ��
            AD_debug[Snumber-1][7] = ATD0DR0;  //��ȡת���Ľ��
	          while(!ATD0STAT2_CCF0);   //�ȴ�ת������   
	          AD_[Snumber-1][8] = ATD0DR0;  //��ȡת���Ľ��
	          AD_debug[Snumber-1][8] = ATD0DR0;  //��ȡת���Ľ��
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
	      //���жϴ����ļ�������2ms һ�� ��Ϊϵͳ������������ �ṩʱ�� ��ʶ
	      MySysTime++;
	      if(MySysTime==65000){MySysTime=0;}
        
        // ����ƫ��
        // ���� sensor_[]  sensor[]
        for(i=0; i<=14; i++)
        {
            //temp = (AD_[i][6]+AD_[i][7]+AD_[i][8])  //�ضϺ��ֵ
            //       - (AD_[i][3]+AD_[i][4]+AD_[i][5]);    //�����е�ֵ
            sensor_ad_h[i] = (AD_[i][3]+AD_[i][4]+AD_[i][5]); //�����е�ֵ
            //sensor_ad_l[i] = (AD_[i][6]+AD_[i][7]+AD_[i][8]); //�ضϺ��ֵ
            //sensor_ad[i] = temp;   // ��ֵ��  ������-����ֵ
            
            // �Զ���ȡ���  ��Сֵ
            if(i_start <= 14 && i_start >= 2)
            {
              
                if(sensor_ad_h[i]>=sensor_max_min[i][0]) //���ϵĸ��¼�ֵ
                {
                    sensor_max_min[i][0] =  sensor_ad_h[i]; //����
                }
                if(sensor_ad_h[i]<=sensor_max_min[i][1]) //���ϵĸ��¼�ֵ
                {
                    sensor_max_min[i][1] = sensor_ad_h[i];  //���� 
                }

            }
          
            if(sensor_ad_h[i]<=sensor_max_min[i][1])//��С�ı���
            {
                sensor_ad_h[i]=sensor_max_min[i][1];
            }
            if(sensor_ad_h[i]>=sensor_max_min[i][0])//����ı���
            {
                sensor_ad_h[i]=sensor_max_min[i][0];  
            }
            //  ����ɰٷֱ� ת���ɣ�  0~100 
            sensor_[i] = (     100*(sensor_ad_h[i]-sensor_max_min[i][1])
                              /(sensor_max_min[i][0]-sensor_max_min[i][1])  );              
        }
        //δʹ�õ�            
        sensor_[1]=0;sensor_[3]=0;
        //sensor_[5]=0;sensor_[7]=0;sensor_[9]=0;
        sensor_[11]=0;sensor_[13]=0;   
        /////////////////////////////////////////////////////////////////////
	      //  ��õ�ǰ��λ��ƫ��  >>  pos
	      //  (-)|(+) ������Ч������λ�ã� lƫΪ��, rƫ��ʱ��Ϊ��
	      //  14 13 12 11 10 9 8 7 6 5 4 3 2 1 0  ˳�� 15 > 1
	      // -14-13-12-11-10-9-8-7-6-5-4-3-2-1 0 +1+2+3+4+5+6+7+8+9+10+11+ ... +100
	      /////////////////////////////////////////////////////////////////////

	      for(i=0; i<=14; i++) // �����������·�
	      {
		        //��ֵԽСԽ��ȫ, ԽС�����ĵ��ֱ��Խ�󣬶Ժ���Խ���� 
		        if(sensor_[i]>=sensor_pr[i]+20){sensor[i]=1;}     //����  ס��
		        else                           {sensor[i]=0;}     //��ɢ�� �� ���ڷֱ��м��ֵ
	      }
	      /////////////////////////////////////////////////////////
        num_on = 0;//���ѹ�ߴ������ĸ��� num_on,
	      i_sum =0;//ѹ�ߴ������ı��(0~14)֮��
	      
	      //���  ���  �˲�
	      
	      door_L = 7+4 - pos_/2;
	      door_R = 7-4 - pos_/2;
	      if(door_L>14){door_L=14;}
	      if(door_R< 0){door_R=0;}
	      
	      ////////////////////////////////////////
        //����  �Գ� λ��  ��  ���� ���� ��
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
             if(sensor[i]==0x01)//��һ��ѹ�� ����=1
		         {
		             b++;
		         }
        }
        ////////////////////////////////////////
        for(i=door_R; i<=door_L; i++)
	      //for(i=0; i<=14; i++)
	      {
		        if(sensor[i]==0x01)//��һ��ѹ�� ����=1
		        {
			         num_on = num_on + 1;   //ѹ�ߴ������ĸ���
			         i_sum  = i_sum + (7-i);    //ѹ�ߴ������ı��(0~14)֮��
		        }
	      }
	      if(num_on!=0) //��⵽�д�����ѹ��
	      {
 			      if((10*b)/(door_L_-door_R_-a+1) >= 5 && PTS_PTS2==0) //��ֵ�� �ذ� �кܴ�Ĺ�ϵ ������������
 			      {
 			          pos_ = pos_old;
 			      }
 			      else
 			      {
 			          pos_ = (2*i_sum)/num_on;  //����
 			          /*
 			          if(num_on>=5 && abs(pos_)<=4)  //���� �� �ڿ�
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
	      else//û��һ��ѹ�ߣ����ܷɣ�������һ�ε�λ�á�
	      {
		        pos_ = pos_; //�Ǿ�̬����         
	      }
	      

	      ////////////////////////////////////////////////////////////////////////////////
        //     ��¼ʱ��            ƫ��ͣ��ʱ��
        ////////////////////////////////////////////////////////////////////////////////
        
	      timer_1++; //�ɼ���������Ϣ��ʱ����
	      
	      if(pos_ != pos_old) //�����仯��������һ��λ�õ��������ڡ�ƫ���ٶȣ�����
	      {
            //����������ڣ�����һ��λ��ͣ����ʱ��
		        pos_time = timer_1;
   
		        //�����������ڣ������ƫ���ٶ�
		        if(timer_1 <= D_)
		        { 
			          //��ȡ
                pos_time = timer_1;
		        } 
		        else 
		        {
		            pos_time = D_ ; //�����������̫������Ϊƫ���ٶȺ���
		        }
            //��֤ʱ����û��Խ����
		        timer_1 = 0;//���¿�ʼ��ʱ
		        //////////////////////////////////////////////////////////////////
		        //////////////////////////////////////////////////////////////////
		        //�ж�ƫ���ٶȵķ���

		        if(pos_old==0 && pos_!=0 )   //��������ƫ�ƣ�ƫ���ٶȼӴ�
		        {
			          if(pos_ > 0)//���ҹ�,
			          {
			  	          pos_v_de = 1;
			          }
			          else        //����գ�
			          {
			  	          pos_v_de = 1;
			          }
		        }
	  	      else if(pos_old >0 && pos_>=0) //λ���Ҳ�,ƫ��Ϊ��ֵ�����ҹ�,
		        {
			          if(pos_>pos_old)//ƫ������
			          {
				            pos_v_de = 1;
			          }
			          else               //ƫ���С
			          {
				            pos_v_de = -1; //ƫ���ڼ�С�����ʵ��ĵ�С��ֵ
			          }
		        }
		        else if(pos_old <0 && pos_<=0) //λ����࣬ƫ��Ϊ��ֵ������գ�
		        {
			          if(pos_>pos_old)//ƫ���С
			          {
				            pos_v_de = -1; //ƫ���ڼ�С��
			          }
			          else               //ƫ������
			          {
				            pos_v_de = 1;
			          }
		        }
	      }
        pos_old = pos_;     
    }
           
}