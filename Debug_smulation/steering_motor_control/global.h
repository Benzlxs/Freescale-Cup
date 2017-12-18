


#define D_        30     // 微分控制
#define  straight  10080 //+350 //直走的SteerPWM 也即是 1.5ms     
                          // Clock A = bus/16
#define  turn_max  1760  //840    //最大转角对应的PWM值  广西1620 7430
#define  turn_max2 1850  //840
#define  IMAGE_COLUMN 107
#define turn_step  (turn_max*2)/IMAGE_COLUMN ///35 //1750/53 //(2*turn_max)/(IMAGE_COLUMN+5)   //   //
#define MP 3 //5
#define MI 2
#define PWM_STEP 70  //目的是不让pwm增加的太多

	FILE  *zz;
    FILE  *ff;   

unsigned char pwm_temp; //正转占空比的影子
int car_info_old=150; //记录上次车的中心位置。150这个值是不会出现的。
int car_info_new=58; 
unsigned int G_CAR_SPEED=0;
unsigned int   G_CAR_SPEED_temp=0;
unsigned char PhotoLineInfoOld[23];  
unsigned char G_car_find_line=8;
char carinfo[3];
