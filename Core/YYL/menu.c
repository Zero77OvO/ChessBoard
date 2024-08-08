#include "head_files.h"

int flr1_choice=0; 	

int flr1=1;
int flr1_topic=0; 
int flr1_topic_now=1;
// 1 push  2 right 3 left 4 down 5 up

void main_menu(void){

if(flr1==1){

    
    if(key[2].single_flag==1){

        flr1_topic_now+=1;  //dowm

		key[2].single_flag=0;
    }
    if(key[1].single_flag==1){

        flr1_topic_now-=1;

		key[1].single_flag=0; // up 
    }

    if(flr1_topic_now>6){flr1_topic_now=1;}
    if(flr1_topic_now<1){flr1_topic_now=6;}




    if(key[0].single_flag==1){

        switch (flr1_topic_now)
        {

            case 1: flr1_topic=1;flr1=2;break;
            case 2: flr1_topic=2;flr1=2;break;
            case 3: flr1_topic=3;flr1=2;break;
            case 4: flr1_topic=4;flr1=2;break;
            case 5: flr1_topic=5;flr1=2;break;
            case 6: flr1_topic=6;flr1=2;break;
            case 7: flr1_topic=7;flr1=2;break;

            default:
            break;
        }
			key[0].single_flag=0;	
    }
    
    LCD_ShowIntNum(90, 0, flr1_topic_now, 1, RED, BLACK, 16);
    LCD_ShowIntNum(0,0,board_x,3,RED,WHITE,16);LCD_ShowIntNum(60,0,board_y,3,RED,WHITE,16);

	if(key[4].single_flag==1){  //right

        reset_all();

        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

		key[4].single_flag=0;
    }



}

if(flr1==2){

if(flr1_topic==1){

    Topic=1;
    LCD_ShowIntNum(180, 0, Topic, 3, RED, BLACK, 16);
   
    


	if(key[4].single_flag==1){  //right

        reset_all();

        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

		key[4].single_flag=0;
    }




}

if(flr1_topic==2){

    Topic=2;


    LCD_ShowIntNum(180, 0, Topic, 3, RED, BLACK, 16);

    

    LCD_ShowIntNum(10, 30, TOPIC2_target_board, 1, RED, BLACK, 16);
    LCD_ShowIntNum(10, 50, TOPIC2_target_board1, 1, RED, BLACK, 16);
    LCD_ShowIntNum(30, 50, TOPIC2_target_board2, 1, RED, BLACK, 16);
    LCD_ShowIntNum(50, 50, TOPIC2_target_board3, 1, RED, BLACK, 16);
    LCD_ShowIntNum(70, 50, TOPIC2_target_board4, 1, RED, BLACK, 16);

    LCD_ShowIntNum(0, 70, x1, 6, RED, BLACK, 16);LCD_ShowIntNum(70, 70, x2, 6, RED, BLACK, 16);
   
    


	if(key[4].single_flag==1){  //right

        reset_all();

        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

		key[4].single_flag=0;
    }

}

if(flr1_topic==3){
    Topic=3;
    LCD_ShowIntNum(180, 0, Topic, 3, RED, BLACK, 16);
  

 

    LCD_ShowIntNum(10, 30, TOPIC2_target_board, 1, RED, BLACK, 16);
    LCD_ShowIntNum(10, 50, TOPIC2_target_board1, 1, RED, BLACK, 16);
    LCD_ShowIntNum(30, 50, TOPIC2_target_board2, 1, RED, BLACK, 16);
    LCD_ShowIntNum(50, 50, TOPIC2_target_board3, 1, RED, BLACK, 16);
    LCD_ShowIntNum(70, 50, TOPIC2_target_board4, 1, RED, BLACK, 16);


    LCD_ShowIntNum(0, 70, x1, 6, RED, BLACK, 16);LCD_ShowIntNum(70, 70, x2, 6, RED, BLACK, 16);
    
    

	if(key[4].single_flag==1){  //right

        reset_all();

        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

		key[4].single_flag=0;
    }
}

if(flr1_topic==4){
    Topic=4;
    LCD_ShowIntNum(180, 0, Topic, 3, RED, BLACK, 16);

    LCD_ShowFloatNum1(50,0,total_chess_time ,4,RED,WHITE,16);
    

    LCD_ShowIntNum(0, 0, TOPIC4_target_board, 1, RED, BLACK, 16);
    LCD_ShowIntNum(10, 30, TOPIC4_target_board1, 1, RED, BLACK, 16);

    
    LCD_ShowIntNum(0, 50, x1, 6, RED, BLACK, 16);LCD_ShowIntNum(70, 50, x2, 6, RED, BLACK, 16);





    LCD_ShowIntNum(0,90,qizi[0],1,RED,WHITE,16);LCD_ShowIntNum(20,90,qizi[1],1,RED,WHITE,16);LCD_ShowIntNum(40,90,qizi[2],1,RED,WHITE,16);
    LCD_ShowIntNum(0,110,qizi[3],1,RED,WHITE,16);LCD_ShowIntNum(20,110,qizi[4],1,RED,WHITE,16);LCD_ShowIntNum(40,110,qizi[5],1,RED,WHITE,16);
	LCD_ShowIntNum(0,130,qizi[6],1,RED,WHITE,16);LCD_ShowIntNum(20,130,qizi[7],1,RED,WHITE,16);LCD_ShowIntNum(40,130,qizi[8],1,RED,WHITE,16);

	if(key[4].single_flag==1){  //right

        reset_all();

        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

		key[4].single_flag=0;
    }
}

if(flr1_topic==5){
    Topic=5;
    LCD_ShowIntNum(180, 0, Topic, 3, RED, BLACK, 16);

    LCD_ShowFloatNum1(50,0,total_chess_time ,4,RED,WHITE,16);
    

    LCD_ShowIntNum(0, 0, TOPIC4_target_board, 1, RED, BLACK, 16);
    LCD_ShowIntNum(10, 30, TOPIC4_target_board1, 1, RED, BLACK, 16);

    
    LCD_ShowIntNum(0, 50, x1, 6, RED, BLACK, 16);LCD_ShowIntNum(70, 50, x2, 6, RED, BLACK, 16);





    LCD_ShowIntNum(0,90,qizi[0],1,RED,WHITE,16);LCD_ShowIntNum(20,90,qizi[1],1,RED,WHITE,16);LCD_ShowIntNum(40,90,qizi[2],1,RED,WHITE,16);
    LCD_ShowIntNum(0,110,qizi[3],1,RED,WHITE,16);LCD_ShowIntNum(20,110,qizi[4],1,RED,WHITE,16);LCD_ShowIntNum(40,110,qizi[5],1,RED,WHITE,16);
	LCD_ShowIntNum(0,130,qizi[6],1,RED,WHITE,16);LCD_ShowIntNum(20,130,qizi[7],1,RED,WHITE,16);LCD_ShowIntNum(40,130,qizi[8],1,RED,WHITE,16);

	if(key[4].single_flag==1){  //right

        reset_all();

        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

		key[4].single_flag=0;
    }	
}

if(flr1_topic==6){

    Topic=6;
    LCD_ShowIntNum(180, 0, Topic, 3, RED, BLACK, 16);



    LCD_ShowIntNum(0,0,board_x,3,RED,WHITE,16);LCD_ShowIntNum(60,0,board_y,3,RED,WHITE,16);

    LCD_ShowString(0,50,"Over Up ",RED,WHITE,16,0);

    LCD_ShowString(0,70,"need x++",RED,WHITE,16,0);

    LCD_ShowString(0,90,"Over Left",RED,WHITE,16,0);
    
    LCD_ShowString(0,110,"need y--",RED,WHITE,16,0);

	if(key[4].single_flag==1){  //right

        reset_all();
        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

		key[4].single_flag=0;
    }	

}



}




}

