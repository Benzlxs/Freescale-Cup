#include <stdio.h>
#include<string.h>
#include"global.h"
#include "math.h"



void Car_Turn_Set_v14() 
{
    
    int temp_pid,dx1,PWMDTY45;
	

	if( PhotoLineInfoOld[G_car_find_line]>= 0)
	{
		car_info_new =(PhotoLineInfoOld[ G_car_find_line]-IMAGE_COLUMN/2);
		//--------�˲��㷨--------------
		if(abs(car_info_new - car_info_old)>=40) 
		{
			
			car_info_new = (car_info_old*14)/10;
			
		}
		
		/*  */
		dx1= (turn_step *abs(car_info_new)*19)/10;//�򵥵�p����
        // dx1= (turn_step *abs(car_info_new));
	}
	
	else 
	{
        car_info_new = car_info_old;
        dx1= (turn_step *abs(car_info_new)*4)/2;//�򵥵�p����
	}
    
	
    if(car_info_new >=0) 
	{
		temp_pid = straight -(dx1);///2;     //< v4.0    +dx1; 
		// PORTB = 0XFF;
		
	}
    else
	{
		temp_pid = straight + (dx1);  //v4.0 -dx1;
		
		//  PORTB = 0XAA;
		
	}
	
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
	
	//	PWMDTY45 = straight;
	car_info_old= car_info_new;
	fprintf(ff,"%d",PWMDTY45);                //�ѵõ�����Ϣ�����뵽�ļ�����
	if(PWMDTY45==carinfo[1])
		fprintf(ff,"   same\n");
	else
		fprintf(ff,"  not \n");
}




int lasts_ek=0;//���µ��ٶ�ƫ��
  
void set_speed_PD(void)
{
    int s_ek;    //�ٶ�ƫ��   
    int s_dek;    //�ٶ�ƫ��仯��
	int PWMDTY0;
    int ctrl_motor;
	int PACNT ;
    int g_car_speed_now;


	PACNT=carinfo[2];
    g_car_speed_now =PACNT; //ʵ�ʲ������ٶ�ֵ
    PACNT = 0x0000;
    // 
//	PORTB =~g_car_speed_now;    //�˴����Բ��Ա������Ƿ���������
	
	
    //if(g_car_speed_now!=0) //�����ֱ�����û������
    {
		
		s_ek=(G_CAR_SPEED- g_car_speed_now);  //�ٶ�ƫ��
		s_dek=s_ek-lasts_ek;      //�ٶ�ƫ��仯��
		
		ctrl_motor = pwm_temp;
		
        ctrl_motor=ctrl_motor+(MP*s_ek)/2+MI*s_dek;
		lasts_ek=s_ek;
		
        if(ctrl_motor< 35) ctrl_motor=35;//;//15
        if(ctrl_motor> 200) ctrl_motor= 200;
        
		
		if(abs(ctrl_motor-pwm_temp)>=PWM_STEP)//ƫ��ܴ�
		{
			if(ctrl_motor-pwm_temp>=0)
				ctrl_motor = pwm_temp+PWM_STEP;
			else
				ctrl_motor =pwm_temp-PWM_STEP;
		}
        
        if(ctrl_motor< 35) ctrl_motor=35;//;//15
        if(ctrl_motor> 200) ctrl_motor= 200;
		
		PWMDTY0 = ctrl_motor;//0;//
        
		pwm_temp = ctrl_motor; //��תռ�ձȵ�Ӱ��    G_CAR_SPEED
    }
	fprintf(ff,"%d",PWMDTY0);
	if(PWMDTY0==carinfo[3])
		fprintf(ff," same\n");
	else
		fprintf(ff,"  not\n");
	
}



