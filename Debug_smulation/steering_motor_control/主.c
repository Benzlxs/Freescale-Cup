#include <stdio.h>
#include<string.h>
#include "math.h"
#include "global.h"

void readdata(void);
void Car_Turn_Set_v14(void);
void set_speed_PD(void)  ;


void main()
{
    
	zz=fopen("D:\\�ɼ��е�.txt","r");
	ff=fopen("D:\\�õ���������.txt","w") ;
	if(zz==NULL)
	{
		printf("�޷����ı��ļ�!");
		return;
	}
	do 
	{
	readdata();                //��ȡ���ݣ��൱�ڵ�Ƭ��������жϹ���
    Car_Turn_Set_v14();           //��Ƭ��������Ƴ���
    set_speed_PD()  ;
     fprintf(ff,"һ�ο��ƽ���\n");
	} while (	PhotoLineInfoOld[0]>=0);
	fclose(zz);
}
