#include <stdio.h>
#include<string.h>
#include"global.h"

void readdata()                //����������ȡ��ȡͼ���е�Ͷ�����������Ϣ����������ٶȺ�ת����ƺ���
{
	char ch;
	unsigned char  i,z1,z2 ,z3,z4;
	while(1)                       //ȥ����һ�����λ
	{
		ch=fgetc(zz);
		if(ch==',')
			break;
	}
	
	for(i=0;i<23;i++)              //��ʼ���洢�е����������д����
	{  
		ch=fgetc(zz);
		z1=ch-48;                   //���ڴ��ı������ȡ�Ķ����ַ��ͣ����������ASCIIת��
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
		while(1)                       //��С��������Ϣ
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



