


#define D_        30     // ΢�ֿ���
#define  straight  10080 //+350 //ֱ�ߵ�SteerPWM Ҳ���� 1.5ms     
                          // Clock A = bus/16
#define  turn_max  1760  //840    //���ת�Ƕ�Ӧ��PWMֵ  ����1620 7430
#define  turn_max2 1850  //840
#define  IMAGE_COLUMN 107
#define turn_step  (turn_max*2)/IMAGE_COLUMN ///35 //1750/53 //(2*turn_max)/(IMAGE_COLUMN+5)   //   //
#define MP 3 //5
#define MI 2
#define PWM_STEP 70  //Ŀ���ǲ���pwm���ӵ�̫��

	FILE  *zz;
    FILE  *ff;   

unsigned char pwm_temp; //��תռ�ձȵ�Ӱ��
int car_info_old=150; //��¼�ϴγ�������λ�á�150���ֵ�ǲ�����ֵġ�
int car_info_new=58; 
unsigned int G_CAR_SPEED=0;
unsigned int   G_CAR_SPEED_temp=0;
unsigned char PhotoLineInfoOld[23];  
unsigned char G_car_find_line=8;
char carinfo[3];
