#include <stdio.h>
#include <head_files.h>



//棋子选位置时候的过渡值
int move=99;

//当前棋盘中棋的数量
int chess_total=0;
int his_chess_total=0;
//过渡值
int t=0; 

int t1_black=0;
int t2_white=0;
//目前黑白棋数量，认到狗之后，qipan都要清除

int now_black_chess=0;
int now_white_chess=0;



void printBoard(int qizi[]) {
    for (int i = 0; i < 9; i++) {
        printf("%d ", qizi[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
    printf("\n");
}

void check_Win() {

    if(location_1==2&&location_2==2&&location_3==2){Topic=99;}
    else if(location_7==2&&location_8==2&&location_9==2){Topic=99;}
    else if(location_4==2&&location_5==2&&location_6==2){Topic=99;}
    else if(location_1==2&&location_5==2&&location_9==2){Topic=99;}
    else if(location_3==2&&location_5==2&&location_7==2){Topic=99;}
    else if(location_1==2&&location_4==2&&location_7==2){Topic=99;}
    else if(location_2==2&&location_5==2&&location_8==2){Topic=99;}
    else if(location_3==2&&location_6==2&&location_9==2){Topic=99;}

}

void qipan_full(){

    if(qizi[0]==0){qizi[0]=location_1;}
    if(qizi[1]==0){qizi[1]=location_2;}
    if(qizi[2]==0){qizi[2]=location_3;}
    if(qizi[3]==0){qizi[3]=location_4;}
    if(qizi[4]==0){qizi[4]=location_5;}
    if(qizi[5]==0){qizi[5]=location_6;}
    if(qizi[6]==0){qizi[6]=location_7;}
    if(qizi[7]==0){qizi[7]=location_8;}
    if(qizi[8]==0){qizi[8]=location_9;}
    t=0;
    
    
     

    for (int i = 0; i <9; i++)
    {   
        if(qizi[i]!=0){t++;} 
    }
    chess_total=t;

    t1_black=0;
    for (int j = 0; j <9; j++)
    {   
        if(qizi[j]!=0&&qizi[j]!=1){t1_black++;} 
    }
    now_black_chess=t1_black;
    
    t2_white=0; 
    for (int k = 0; k <9; k++)
    {   
        if(qizi[k]!=0&&qizi[k]!=2){t2_white++;} 
    }
    now_white_chess=t2_white;

    

}

//记录棋盘的历史
void qipan_his(){

    his_qizi[0]=qizi[0];
    his_qizi[1]=qizi[1];
    his_qizi[2]=qizi[2];
    his_qizi[3]=qizi[3];
    his_qizi[4]=qizi[4];
    his_qizi[5]=qizi[5];
    his_qizi[6]=qizi[6];
    his_qizi[7]=qizi[7];
    his_qizi[8]=qizi[8];


}

//识别到错误后,再拍一张目前的真实棋子

void qipan_true(){

    if(true_qizi[0]==0){true_qizi[0]=location_1;}
    if(true_qizi[1]==0){true_qizi[1]=location_2;}
    if(true_qizi[2]==0){true_qizi[2]=location_3;}
    if(true_qizi[3]==0){true_qizi[3]=location_4;}
    if(true_qizi[4]==0){true_qizi[4]=location_5;}
    if(true_qizi[5]==0){true_qizi[5]=location_6;}
    if(true_qizi[6]==0){true_qizi[6]=location_7;}
    if(true_qizi[7]==0){true_qizi[7]=location_8;}
    if(true_qizi[8]==0){true_qizi[8]=location_9;}


}
//qizi是过去与现在的综合，只要出现过就保存
//his 就是 机器下完之后存的

//作弊前 /his
//1 0 2
//0 2 0
//1 0 0

//作弊后 /true

//1 0 2
//1 2 0  
//0 0 0

//qizi

//1 0 2
//1 2 0  
//1 0 0

//找出错误的棋子 移动后的位置
int find_mischess(){
    //如果棋子正确就返回-1，如果不对返回 错误棋子的格子
    if(qizi[0]!=his_qizi[0]){return 0;}
    else if(qizi[1]!=his_qizi[1]){return 1;}
    else if(qizi[2]!=his_qizi[2]){return 2;}
    else if(qizi[3]!=his_qizi[3]){return 3;}
    else if(qizi[4]!=his_qizi[4]){return 4;}
    else if(qizi[5]!=his_qizi[5]){return 5;}
    else if(qizi[6]!=his_qizi[6]){return 6;}
    else if(qizi[7]!=his_qizi[7]){return 7;}
    else if(qizi[8]!=his_qizi[8]){return 8;}
    else{return -3;}

}
//找出被移动的棋子位置
int qipan_rectify(){

    if(qizi[0]!=true_qizi[0]){return 0;}
    else if(qizi[1]!=true_qizi[1]){return 1;}
    else if(qizi[2]!=true_qizi[2]){return 2;}
    else if(qizi[3]!=true_qizi[3]){return 3;}
    else if(qizi[4]!=true_qizi[4]){return 4;}
    else if(qizi[5]!=true_qizi[5]){return 5;}
    else if(qizi[6]!=true_qizi[6]){return 6;}
    else if(qizi[7]!=true_qizi[7]){return 7;}
    else if(qizi[8]!=true_qizi[8]){return 8;}
    else{return -4;}



}

int test_Lose() {
    
    // 0 1 2
    // 3 4 5 
    // 6 7 8
    if(qizi[0]==1&&qizi[2]==1&&qizi[1]==0){return 1;}
    else if(qizi[0]==1&&qizi[1]==1&&qizi[2]==0){return 2;}
    else if(qizi[1]==1&&qizi[2]==1&&qizi[0]==0){return 0;}
    else if(qizi[3]==1&&qizi[4]==1&&qizi[5]==0){return 5;}
    else if(qizi[3]==1&&qizi[5]==1&&qizi[4]==0){return 4;}
    else if(qizi[4]==1&&qizi[5]==1&&qizi[3]==0){return 3;}
    else if(qizi[6]==1&&qizi[7]==1&&qizi[8]==0){return 8;}
    else if(qizi[6]==1&&qizi[8]==1&&qizi[7]==0){return 7;}
    else if(qizi[7]==1&&qizi[8]==1&&qizi[6]==0){return 6;}

    else if(qizi[0]==1&&qizi[3]==1&&qizi[6]==0){return 6;}
    else if(qizi[0]==1&&qizi[6]==1&&qizi[3]==0){return 3;}
    else if(qizi[3]==1&&qizi[6]==1&&qizi[0]==0){return 0;}
    else if(qizi[1]==1&&qizi[4]==1&&qizi[7]==0){return 7;}
    else if(qizi[1]==1&&qizi[7]==1&&qizi[4]==0){return 4;}
    else if(qizi[4]==1&&qizi[7]==1&&qizi[1]==0){return 1;}

    else if(qizi[2]==1&&qizi[5]==1&&qizi[8]==0){return 8;}
    else if(qizi[2]==1&&qizi[8]==1&&qizi[5]==0){return 5;}
    else if(qizi[5]==1&&qizi[8]==1&&qizi[2]==0){return 2;}

    else if(qizi[0]==1&&qizi[4]==1&&qizi[8]==0){return 8;}
    else if(qizi[0]==1&&qizi[8]==1&&qizi[4]==0){return 4;}
    else if(qizi[4]==1&&qizi[8]==1&&qizi[0]==0){return 0;} 

    else if(qizi[2]==1&&qizi[4]==1&&qizi[6]==0){return 6;}
    else if(qizi[4]==1&&qizi[6]==1&&qizi[2]==0){return 2;}
    else if(qizi[2]==1&&qizi[6]==1&&qizi[4]==0){return 4;} 

    else {return -2;} // 没有找到堵棋的地方
}

int test_Win() {
    if(qizi[0]==2&&qizi[2]==2&&qizi[1]==0){return 1;}
    else if(qizi[0]==2&&qizi[1]==2&&qizi[2]==0){return 2;}
    else if(qizi[1]==2&&qizi[2]==2&&qizi[0]==0){return 0;}

    else if(qizi[3]==2&&qizi[4]==2&&qizi[5]==0){return 5;}
    else if(qizi[3]==2&&qizi[5]==2&&qizi[4]==0){return 4;}
    else if(qizi[4]==2&&qizi[5]==2&&qizi[3]==0){return 3;}

    else if(qizi[6]==2&&qizi[7]==2&&qizi[8]==0){return 8;}
    else if(qizi[6]==2&&qizi[8]==2&&qizi[7]==0){return 7;}
    else if(qizi[7]==2&&qizi[8]==2&&qizi[6]==0){return 6;}

    else if(qizi[0]==2&&qizi[3]==2&&qizi[6]==0){return 6;}
    else if(qizi[0]==2&&qizi[6]==2&&qizi[3]==0){return 3;}
    else if(qizi[3]==2&&qizi[6]==2&&qizi[0]==0){return 0;}
    
    else if(qizi[1]==2&&qizi[4]==2&&qizi[7]==0){return 7;}
    else if(qizi[1]==2&&qizi[7]==2&&qizi[4]==0){return 4;}
    else if(qizi[4]==2&&qizi[7]==2&&qizi[1]==0){return 1;}

    else if(qizi[2]==2&&qizi[5]==2&&qizi[8]==0){return 8;}
    else if(qizi[2]==2&&qizi[8]==2&&qizi[5]==0){return 5;}
    else if(qizi[5]==2&&qizi[8]==2&&qizi[2]==0){return 2;}

    else if(qizi[0]==2&&qizi[4]==2&&qizi[8]==0){return 8;}
    else if(qizi[0]==2&&qizi[8]==2&&qizi[4]==0){return 4;}
    else if(qizi[4]==2&&qizi[8]==2&&qizi[0]==0){return 0;} 

    else if(qizi[2]==2&&qizi[4]==2&&qizi[6]==0){return 6;}
    else if(qizi[4]==2&&qizi[6]==2&&qizi[2]==0){return 2;}
    else if(qizi[2]==2&&qizi[6]==2&&qizi[4]==0){return 4;}



    else {return -1;} // 没有找到可以直接胜利的地方
}


int test_best() {
    int bestMoves[9] = {4 ,0, 2, 6, 8, 1, 3, 5, 7};
    for (int i = 0; i < 9; i++) {
        if (qizi[bestMoves[i]] == 0) {
            return bestMoves[i];
        }
    }
    return -1; // 没有找到最优的空位置
}

void deviceNextMove() {
    if(start_black==1&&start_white==0){//装置用黑棋
    if (move == 99) {
        move = test_Win();
    if (move == -1) {
        move = test_Lose();
        if (move == -2) {
            move = test_best();
        }
    }
    }
        if (move != -1&&move != -2&&move != 99) {
        target_board=move+1;
        move=99;
    }
    }

    if(start_black==0&&start_white==1){//装置用白棋
    if (move == 99) {
        move = test_Lose();
    if (move == -2) {
        move = test_Win();
        if (move == -1) {
            move = test_best();
        }
    }
    }

    if (move != -1&&move != -2&&move != 99) {
        target_board=move+1;
        move=99;
    }


    }


}






