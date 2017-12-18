#include <stdio.h>
#include<string.h>
#include "math.h"
#include "global.h"

void readdata(void);
void Car_Turn_Set_v14(void);
void set_speed_PD(void)  ;


void main()
{
    
	zz=fopen("D:\\采集中点.txt","r");
	ff=fopen("D:\\得到控制数据.txt","w") ;
	if(zz==NULL)
	{
		printf("无法打开文本文件!");
		return;
	}
	do 
	{
	readdata();                //读取数据，相当于单片机里面的中断功能
    Car_Turn_Set_v14();           //单片机里面控制程序
    set_speed_PD()  ;
     fprintf(ff,"一次控制结束\n");
	} while (	PhotoLineInfoOld[0]>=0);
	fclose(zz);
}
