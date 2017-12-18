#include <stdio.h>
#include<string.h>
#include"global.h"

void readdata()                //函数用来读取提取图像中点和舵机电机控制信息。用来检测速度和转向控制函数
{
	char ch;
	unsigned char  i,z1,z2 ,z3,z4;
	while(1)                       //去掉第一个序号位
	{
		ch=fgetc(zz);
		if(ch==',')
			break;
	}
	
	for(i=0;i<23;i++)              //开始往存储中点的数组里面写数据
	{  
		ch=fgetc(zz);
		z1=ch-48;                   //由于从文本里面读取的都是字符型，在这里进行ASCII转化
		ch=fgetc(zz);
		if(ch==',')
			PhotoLineInfoOld[i]=z1;
		else
		{ 
			z2=ch-48;
			ch=fgetc(zz);
			if(ch==',')
			{
				PhotoLineInfoOld[i]=z1*10+z2;
			}
			else
			{
				z3=ch-48;
				PhotoLineInfoOld[i]=z1*100+z2*10+z3;
				ch=fgetc(zz);	
			}
			
		}


	}
	for(i=0;i<3;i++)
	{
		while(1)                       //读小车控制信息
		{
			ch=fgetc(zz);
			if(ch=='=')
				break;
		}
		ch=fgetc(zz);
			z1=ch-48;
		ch=fgetc(zz);
		if(ch='.')
		{
			carinfo[i]=z1;
			continue;
		}
		z2=ch-48;
		ch=fgetc(zz);
		if(ch='.')
		{
			carinfo[i]=z1*10+z2;
			continue;
		}
		z3=ch-48;
		ch=fgetc(zz);
		if(ch='.')
		{
			carinfo[i]=z1*100+z2*10+z3;
			continue;
		}
		z4=ch-48;
		carinfo[i]=z1*1000+z2*100+z3*10+z4;
		ch=fgetc(zz);
	}

}



