#ifndef _CHESS_H_
#define _CHESS_H_




//棋子选位置时候的过渡值
extern int move;

//当前棋盘中棋的数量
extern int chess_total;
extern int his_chess_total;
//过渡值
extern int t;

//当前棋盘黑白棋的数量
extern int t1_black;
extern int t2_white;
extern int now_black_chess;
extern int now_white_chess;

void qipan_true(void);
void qipan_his(void);


void qipan_full(void);

//找出被移动的棋子位置，移动之前
int qipan_rectify(void);
//找出错误的棋子 移动后的位置
int find_mischess(void);


void check_Win(void);
int test_Lose(void);
int test_Win(void); 
int test_best(void);
void deviceNextMove(void);


#endif
