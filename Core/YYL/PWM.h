#ifndef __PWM_H
#define __PWM_H
 
//黑白棋起手
extern int start_black;
extern int start_white;

//目标棋盘
extern int target_board;

//目标棋子
extern int target_chess;
//历史目标棋子
extern int his_target_chess;
// //没用到 
// extern int move_flag_x;
// extern int move_flag_y;
// extern int move_flag_z;




//三个步进的移动方向
extern int dir_x;
extern int dir_y;
extern int dir_z;

//三个步进的移动距离
extern int step_x;
extern int step_y;
extern int step_z;

//取放棋子的步骤标志
//题目结算需清零
extern int take_chess_step;
extern int release_chess_step;

//分题
extern int Topic;

//走一步棋
//题目结算时 需清零
extern int step_move;

//下一步棋的时间
extern int chess_time;

extern float total_chess_time;

//步进基点
extern int board_x;
extern int board_y;

//题目结算时 需清零
extern int step_total_x;	
extern int step_total_y;
extern int step_total_z;	

//取放棋子动作的步骤
//取放动作结算时 需清零
extern int take_chess_step;
extern int release_chess_step;

//取放棋子动作的标志
//取放动作结算时 需清零
extern int take_chess_flag;
extern int release_chess_flag;



//抓取&释放等待时间
//取放动作结算时 需清零
extern int take_time;
extern int release_time;


//题目中每走一步棋，数量++
extern int topic_step;

//题2 指定方格

extern int TOPIC2_target_board;
extern int TOPIC2_target_board1;
extern int TOPIC2_target_board2;
extern int TOPIC2_target_board3;
extern int TOPIC2_target_board4;

extern int TOPIC4_target_board;
extern int TOPIC4_target_board1;
//题四选格子

extern int take_choice;

void servo_up(void);
void servo_down(void);

void take_chess(void);
void release_chess(void);
void chess_reset(void);

void take_it(void);
void release_it(void);

void light_on(void);
void light_off(void);
void theft_warning(void);

void x_move(int move_step,int dir);
void y_move(int move_step,int dir);
void z_move(int move_step,int dir);

void reset_all(void);
#endif





