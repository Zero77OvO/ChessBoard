#include "head_files.h"

#include "tim.h"

#include "gpio.h"
/////////初始化///////////

#define servo_time 2500


//黑白棋起手
int start_black=0;
int start_white=0;

//目标棋盘
int target_board=5;

int TOPIC2_target_board=0;
int TOPIC2_target_board1=0;
int TOPIC2_target_board2=0;
int TOPIC2_target_board3=0;
int TOPIC2_target_board4=0;



int TOPIC4_target_board=0;
int TOPIC4_target_board1=0;

//题4选择第一个棋子标志

int take_choice =0;

//目标棋子
int target_chess=5;

int his_target_chess=0;
/////////初始化///////////


// //没用到 
// int move_flag_x=0;
// int move_flag_y=0;
// int move_flag_z=0;




//三个步进的移动方向
int dir_x=0;
int dir_y=0;
int dir_z=0;

//三个步进的移动距离
int step_x=0;
int step_y=0;
int step_z=0;


//分题
int Topic=999;	

//一步棋
//题目结算时 需清零
int step_move=0;

//下一步棋计时
int chess_time=0;

float total_chess_time=0.0f;

//题目中每走一步棋，数量++
int topic_step=0;





int step_t_x=0;
int step_t_y=0;
//取放动作结算时 需清零
int step_total_x=0;	
int step_total_y=0;
int step_total_z=0;	

//取放棋子动作的步骤
//取放动作结算时 需清零
int take_chess_step=0;
int release_chess_step=0;

//取放棋子动作的标志
//取放动作结算时 需清零
int take_chess_flag=0;
int release_chess_flag=0;




// 抓取&释放等待时间
//取放动作结算时 需清零
int take_time=0;
int release_time=0;

void servo_down(){ __HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1300);}
void servo_up(){   __HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 700);}

void take_it(){HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);}
void release_it(){HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);}

void light_on(){HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET);}
void light_off(){HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET);}

void theft_warning(){  HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);  }

void x_move(int move_step,int dir){

	dir_x=dir;
	
	if(dir_x==1){
		HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_SET);   //电机使能

		HAL_GPIO_WritePin(DIR_X1_GPIO_Port, DIR_X1_Pin, GPIO_PIN_SET); //方向使能

		HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(DIR_X2_GPIO_Port, DIR_X2_Pin, GPIO_PIN_SET);

		step_x++;}
	if(dir_x==2){
		HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_SET);     //电机使能
		
		HAL_GPIO_WritePin(DIR_X1_GPIO_Port, DIR_X1_Pin, GPIO_PIN_RESET); //方向使能

		HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(DIR_X2_GPIO_Port, DIR_X2_Pin, GPIO_PIN_RESET);

		step_x++;}	

	if(step_x>=move_step){
		HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_RESET); //关电机
		HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_RESET);
		
		step_x=0;

	
	//分题步骤	
		 if(step_total_x==3){step_total_x=4;}
	else if(step_total_x==2){step_total_x=3;}
	else if(step_total_x==1){step_total_x=2;}
	else if(step_total_x==0){step_total_x=1;}

	}



}

void y_move(int move_step,int dir){

	dir_y=dir;
	
	if(dir_y==1){
		HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_SET);   //电机使能
		HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, GPIO_PIN_SET); //方向使能
		step_y++;}
	if(dir_y==2){
		HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_SET);     //电机使能
		HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, GPIO_PIN_RESET); //方向使能
		step_y++;}	

	if(step_y>=move_step){


	HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET); //关电机
		
		step_y=0;
		

	
	//分题步骤	
		 if(step_total_y==3){step_total_y=4;}
	else if(step_total_y==2){step_total_y=3;}
	else if(step_total_y==1){step_total_y=2;}
	else if(step_total_y==0){step_total_y=1;}

	}

}








void z_move(int move_step,int dir){
	dir_z=dir;
	
	if(dir_z==1){
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);    //电机使能
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET); //方向使能
		step_z++;}
	if(dir_z==2){
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);    //电机使能
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);   //方向使能
		step_z++;}	

	if(step_z>=move_step){
		dir_z=0;
		step_z=0;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);  //关电机

//可能会有bug，到时候上机看看
//取放动作 需要分开

	if(take_chess_flag==1&&release_chess_flag==0){

		if(take_chess_step==2){take_chess_step=3;}

		else if(take_chess_step==0){take_chess_step=1;}

	}

	if(take_chess_flag==0&&release_chess_flag==1){

		if(release_chess_step==2){release_chess_step=3;}

		else if(release_chess_step==0){release_chess_step=1;}

	}	

	}
}


//抓棋子
void take_chess(){

	//正在抓棋子
	take_chess_flag=1;
//下放
if(take_chess_step==0){

	take_time++;
	servo_down();
	

 	if(take_time>servo_time){take_time=0;take_chess_step=1;}

}

//开磁铁
if(take_chess_step==1){
	take_time++;

	take_it();

 	if(take_time>1500){take_time=0;take_chess_step=2;}

}

//起
if(take_chess_step==2){

	take_time++;
	servo_up();

 	if(take_time>servo_time){take_time=0;take_chess_step=3;}

}
//归零
if(take_chess_step==3){

	step_total_z=1;

	take_chess_flag=0;
}


}

//放棋子
void release_chess(){

	release_chess_flag=1;
//下放
if(release_chess_step==0){

	servo_down();
	release_time++;
	if(release_time>servo_time){release_time=0;release_chess_step=1;}

}

//关磁铁
if(release_chess_step==1){

		release_it();
		release_time++;
 	if(release_time>1500){release_time=0;release_chess_step=2;}
}

//起
if(release_chess_step==2){
	servo_up();
	release_time++;
 	if(release_time>servo_time){release_time=0;release_chess_step=3;}

}

if(release_chess_step==3){

	step_total_z=2;
	release_chess_flag=0;
}



	
}



void chess_reset(){

step_move=0;
//每一个小题的 x y z 电机移动步骤
//取放动作结算时 需清零
step_total_x=0;	
step_total_y=0;
step_total_z=0;	

//取放棋子动作的步骤
//取放动作结算时 需清零
take_chess_step=0;
release_chess_step=0;

//取放棋子动作的标志
//取放动作结算时 需清零
take_chess_flag=0;
release_chess_flag=0;

// 抓取&释放等待时间
//取放动作结算时 需清零
take_time=0;
release_time=0;

//456题的拍照延时，定时器flag
Take_photo_Delay_flag=0;
Take_photo_Delay_time=0;

//6题的真实棋盘拍照延时
Qipan_true_Delay_flag=0;
Qipan_true_Delay_time=0;
}

void reset_all(){

/////////PWM/////////



//黑白棋起手
start_black=0;
start_white=0;

//目标棋盘
target_board=5;

TOPIC2_target_board=0;
TOPIC2_target_board1=0;
TOPIC2_target_board2=0;
TOPIC2_target_board3=0;
TOPIC2_target_board4=0;



TOPIC4_target_board=0;
TOPIC4_target_board1=0;

//题4选择第一个棋子标志

take_choice =0;

//目标棋子
target_chess=5;

his_target_chess=0;
/////////初始化///////////


// //没用到 
// int move_flag_x=0;
// int move_flag_y=0;
// int move_flag_z=0;




//三个步进的移动方向
dir_x=0;
dir_y=0;
dir_z=0;

//三个步进的移动距离
step_x=0;
step_y=0;
step_z=0;


//分题
Topic=999;	

//一步棋
//题目结算时 需清零
step_move=0;

//下一步棋计时
chess_time=0;

total_chess_time=0.0f;

//题目中每走一步棋，数量++
topic_step=0;





step_t_x=0;
step_t_y=0;
//取放动作结算时 需清零
step_total_x=0;	
step_total_y=0;
step_total_z=0;	

//取放棋子动作的步骤
//取放动作结算时 需清零
take_chess_step=0;
release_chess_step=0;

//取放棋子动作的标志
//取放动作结算时 需清零
take_chess_flag=0;
release_chess_flag=0;




// 抓取&释放等待时间
//取放动作结算时 需清零
take_time=0;
release_time=0;



////////chess////////

//棋子选位置时候的过渡值
move=99;

//当前棋盘中棋的数量
chess_total=0;
his_chess_total=0;
//过渡值
t=0; 

t1_black=0;
t2_white=0;
//目前黑白棋数量，认到狗之后，qipan都要清除

now_black_chess=0;
now_white_chess=0;

////////chess////////




////menu////


flr1=1;
flr1_topic=0; 
flr1_topic_now=1;
////menu////

// //topic//
// target_x=0;
// target_y=0;
// //topic//



/////////interrupt////////

//串口的一些标志位，没用到
last_x1=99; last_y1=99;

send_time=0;

last_x1_black=1; last_y1_black=1;

send_time_black=0;

last_x1_white=1;last_y1_white=1;

send_time_white=0;


//串口接收开关，没用到
qipan_receive_flag=0; 
qizi_receive_flag=0; 
qizi_receive_flag_black_white=0; 


//是否开始移动
move_flag=0;

//是否有人作弊 第六题
mistake_flag=0;


//好像没用到 也是定时器的过渡单位
move_up=0;
move_up_1=0;

//定时器flag
Delay_flag=0;
Delay_time=0;


//拍照延时结尾
last_photo_flag=0;
last_photo_time=0;

//456题的拍照延时，定时器flag
Take_photo_Delay_flag=0;
Take_photo_Delay_time=0;

//6题的真实棋盘拍照延时
Qipan_true_Delay_flag=0;
Qipan_true_Delay_time=0;



//第六题
//三种不同状态的棋盘对比，找错误棋子的
for (int i = 0; i < 9; i++) {
	qizi[i] = 0;
	true_qizi[i] = 0;
	his_qizi[i] = 0;
	}
//九宫格坐标
x1=0;y1=0;
x2=0;y2=0;
x3=0;y3=0;
x4=0;y4=0;
x5=0;y5=0;
x6=0;y6=0;
x7=0;y7=0;
x8=0;y8=0;
x9=0;y9=0;

}


