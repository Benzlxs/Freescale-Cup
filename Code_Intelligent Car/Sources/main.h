
//all the global defines should be in this .h file
//all the global variables should be defined in this .h file with EXT
//all the global function should be declared in this .h file
#ifndef XiaoLiang_MAIN_H        
 //-------------------ͼ��ɼ�������-------��ʼ---------------------------
#define  IMAGE_ROW     40    // < v9008  10
#define  IMAGE_COLUMN  107// 87//110-23 // 86//87
 
                  
                                         
#define D_        30     // ΢�ֿ���
#define  straight  10000//280//9880//10080 //+350 //ֱ�ߵ�SteerPWM Ҳ���� 1.5ms   //10280,10380
                         // Clock A = bus/16
#define  turn_max  1840//1760  //840    //���ת�Ƕ�Ӧ��PWMֵ  ����1620 7430
#define  turn_max2 1850  //840

#define turn_step  (turn_max*2)/IMAGE_COLUMN ///35 //1750/53 //(2*turn_max)/(IMAGE_COLUMN+5)   //   //


extern  unsigned char g_time_2s; //2�뷢����־
   
extern int pos_; //ƫ�� ȫ�ֱ���   
extern unsigned char pwm_temp; //��תռ�ձȵ�Ӱ�� 
 
     
 
void uart_init(void);
void uart_putchar(unsigned char ch);
void HardwareInit(void);
void CarInit(void);
 
void delay(long j);
void printp(void (*PortToPut)(), char* ctrl, ...);


#define car_wait_time    10      //ͣ���ȴ���ʱ��

// #define MP 4
 // #define MI 3
extern unsigned char MP ;
extern unsigned char MI;
 
extern unsigned char flag_speed;  
extern unsigned char dp;
extern unsigned char dd;
extern unsigned char flag_g;
extern unsigned char flag_shizi_sum ;
#define temp_xcs_maxphoto 112 // ͼ��2ֵ���ķ�ֵ
 
extern  volatile unsigned int counter_column; // �м���
//ͼ�����ݻ��� -------------------
//extern unsigned char uca_Buffer1[IMAGE_ROW][IMAGE_COLUMN];       //�����ﶨ��ȫ�ֱ���ʱ���ܸ�ֵ
extern unsigned char uca_Buffer2[IMAGE_ROW][IMAGE_COLUMN];  
/*extern unsigned char camera_set_y[IMAGE_ROW]={
4,13,21,28,34,40,45,50,57,63,70,75,78,81,84,86,88,90,93,96,99,102,106,108,110,112,114,116,118,121,124,126,128
}  ;  //ʵ����
extern unsigned char camera_set_j[IMAGE_ROW]={
  2,7,12,17,21,25,28,31,34,37,40,43,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,85
}   ;         */
  
//ָ��ǰ�ɼ����ݲ��������׵�ַ��ָ�� --

//extern volatile unsigned char *pucTemp;
//�ٶȿ���ʱ���õ��ı���
extern   unsigned char flag_j_w;
extern	 unsigned char flag_s_w;
extern   unsigned char flag_zd;
extern   unsigned char flag_shizi_w;
extern   unsigned char flag_j_sum;
extern   unsigned char tingzhi_xian;
extern   unsigned char tingzhi_sum;
extern   unsigned char  tingche;
extern   unsigned int  xcs_maxphoto ;
//ָ��ǰ�ɼ����ݲ��������׵�ַ��ָ��
extern   unsigned char   wide ;      //ֱ�����
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    
//ָ��ǰ�������ݲ��������׵�ַ��ָ��
extern unsigned char *puca_BufferProcess;
extern char  g_all_wandao_qulv;
 
extern unsigned char  g_car_go;

struct photolineinfo 
{
       int   center;   //zhong xin 
      unsigned char number;    // hei dian shu mu
};


extern struct photolineinfo  PhotoLineInfoOld[IMAGE_ROW];
//-------------------ͼ��ɼ�������-------��ʼ---------------------------
 
  //-------------------��ʾͼ��ɼ�������-------��ʼ---------------------------
 extern  unsigned char g_car_show_yn ;//�Ƿ������ʾ����
 
 
  //-------------------��ʾͼ��ɼ�������-------��ʼ---------------------------
 
extern unsigned int g_car_speed_now;
 extern unsigned char G_car_find_line;

extern int car_info_new; 

extern unsigned int G_CAR_SPEED;
extern unsigned  int high_G_CAR_SPEED;
extern unsigned  int  mid_G_CAR_SPEED; 
extern unsigned int   low_G_CAR_SPEED;
 
extern unsigned char shizi_r;
extern  unsigned char  shizi_l;
extern  unsigned char  light_value;
extern  unsigned char light_sum;
extern  unsigned char  flag_dj;


#endif



 
  