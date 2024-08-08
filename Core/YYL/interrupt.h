#ifndef _INTERRUPT_H
#define _INTERRUPT_H


//k210

#define USART1_REC_LEN_1  200
extern uint8_t USART1_RX_BUF_1[USART1_REC_LEN_1];
extern uint16_t USART1_RX_STA_1;
extern uint8_t USART1_NewData_1;
extern uint8_t RxState1_1 ;

#define USART1_REC_LEN_2  200
extern uint8_t USART1_RX_BUF_2[USART1_REC_LEN_2];
extern uint16_t USART1_RX_STA_2;
extern uint8_t USART1_NewData_2;
extern uint8_t RxState1_2 ; 

#define USART1_REC_LEN_3  200
extern uint8_t  USART1_RX_BUF_3[USART1_REC_LEN_3];
extern uint16_t USART1_RX_STA_3;
extern uint8_t USART1_NewData_3;
extern uint8_t RxState1_3; 

extern int qipan_receive_flag; 
extern int qizi_receive_flag; 


extern int x1;extern int y1;
extern int x2;extern int y2;
extern int x3;extern int y3;
extern int x4;extern int y4;
extern int x5;extern int y5;
extern int x6;extern int y6;
extern int x7;extern int y7;
extern int x8;extern int y8;
extern int x9;extern int y9;

extern int board_x; 
extern int board_y;
extern int board_location_flag;


extern int location_1;
extern int location_2;
extern int location_3;
extern int location_4;
extern int location_5;
extern int location_6;
extern int location_7;
extern int location_8;
extern int location_9;

extern int qizi[9]; 
//历史棋子
extern int his_qizi[9]; 

extern int true_qizi[9];


//第三题旋转信号
extern int rorate_angle;

//延迟计时
extern  int Delay_time;
extern  int Delay_flag; 

extern int Take_photo_Delay_flag;
extern int Take_photo_Delay_time;

//6题的真实棋盘拍照延时
extern int Qipan_true_Delay_flag;
extern int Qipan_true_Delay_time;

//拍照延时结尾
extern int last_photo_flag;
extern int last_photo_time;

//usart传坐标
extern int  last_x1; extern int last_y1;

extern int send_time;


extern int  last_x1_black; extern int last_y1_black;

extern int send_time_black;

extern int  last_x1_white; extern int last_y1_white;

extern int send_time_white;

//串口接收开关
extern int qipan_receive_flag; 
extern int qizi_receive_flag; 

extern int qizi_receive_flag_black_white; 
//是否开始移动
extern int move_flag;


//是否有人作弊

extern int mistake_flag;

//应该是过渡参数
extern int move_up;
extern int move_up_1;




//usart2 bluetooth
#define USART2_REC_LEN  200
extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];
extern uint16_t USART2_RX_STA;
extern uint8_t USART2_NewData;
extern uint8_t RxState2; 





//usart3 openmv
#define USART3_REC_LEN  200
extern uint8_t  USART3_RX_BUF[USART3_REC_LEN];
extern uint16_t USART3_RX_STA;
extern uint8_t USART3_NewData;
extern uint8_t RxState3; 




//usart6 vofa
#define RXSTRSIZE 256		  
extern uint8_t rx_string[RXSTRSIZE]; 
extern uint8_t rx_cnt;			  
extern uint8_t rx_buff;			  
extern uint8_t RxBuff;
extern unsigned char shujv[12];
extern int vofa_i, vofa_I;
extern float vofa_float;






#define MAX_POINTS 10 
extern int x_history[MAX_POINTS];
extern int y_history[MAX_POINTS];
extern int num_points;  // 当前历史坐标数
#endif
