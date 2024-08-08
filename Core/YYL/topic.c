#include "head_files.h"

#define motor_time_x 3500
#define motor_time_y 3000

#define maichong_x 60
#define maichong_y 60

#define center_x 6000
#define center_y 7000


#define chess_time_total 500
#define rotary_angle 3.9

#define cos 99
#define sin 6

//坐标计算的pwm
int target_x=0;
int target_y=0;

void Topic_1(){


		start_black=1;
		start_white=0;

		target_chess=5;
		target_board=5;

        move_flag=1;
		
			if(move_flag==1){
				light_on();

			
				chess_time++;
				if(chess_time>chess_time_total){
				total_chess_time+=0.1f;
				chess_time=0;
					
				}
				if(step_move==0){ 
				{	
						//正常对弈
						if(mistake_flag==0){
							//那我黑棋起手如何呢
							if(start_black==1&&start_white==0){
								
								
								if(target_chess==5&&step_total_x==0){x_move(center_x,2);}
								
								if(target_chess==5&&step_total_y==0){y_move(center_y+7400,2);}
							}
						}
						}
				}
				
				//取
				if (step_total_x==1&&step_total_y==1&&step_total_z==0){step_move=1;}

					if (step_move==1&&step_total_z==0)
					{
						take_chess();

					}

					if (step_total_x==1&&step_total_y==1&&step_total_z==1) {step_move=2;}
				

				//归位 或者不归位
				if (step_move==2)
				{	
						//取放动作结算
						take_chess_step=0;
						release_chess_step=0;
						Delay_time++;
						

							//那我黑棋起手如何呢
							if(start_black==1&&start_white==0){

							if(target_chess==5&&step_total_x==1&&Delay_time>5000){x_move(center_x,1);}


							if(target_chess==5&&step_total_y==1){y_move(center_y+7400,1);}


							}


						
						}

				


				if (step_total_x==2&&step_total_y==2&&step_total_z==1&&step_move!=3){Delay_time=0;step_move=3;}
				//移
				if (step_move==3)
				{   Delay_time++;


										
                        if(Delay_time>chess_time_total){
						if(target_board==5&&step_total_x==2){
							// x_move(center_x,2);
							target_x =  ((((x5-board_x)*cos)/100+((y5 - board_y) * sin) / 100) * maichong_x);
							x_move(target_x, 2);
							}

                        }
						if(Delay_time>chess_time_total){
						if(target_board==5&&step_total_y==2){
							// y_move(center_y,2);
							target_y =  -((((y5 - board_y) * cos) / 100 - ((x5 - board_x) * sin) / 100) * maichong_y);
							y_move(target_y, 2);
							}
						}
				}


				//放
				if (step_total_x==3&&step_total_y==3&&step_total_z==1&&step_move!=4){Delay_time=0;step_move=4;}
				if (step_move==4&&step_total_z==1)
				{	
						release_chess();
				}

				//回
				if (step_total_x==3&&step_total_y==3&&step_total_z==2){step_move=5;}
				if (step_move==5)
				{	
						//取放动作结算
						take_chess_step=0;
						release_chess_step=0;
					
						if(target_board==5&&step_total_x==3)
						{
							x_move(target_x, 1);
							// x_move(center_x, 1);
						}
						if(target_board==5&&step_total_y==3){

							// y_move(center_y,1);
							y_move(target_y, 1);
							
							}


				}
					//走完一步棋子后结算画面
					if(step_total_x==4&&step_total_y==4){

						light_off();

						HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_RESET); //关电机
						HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET); 

						chess_reset();

						move_flag=0;

						flr1=1;
						flr1_topic=0;          
						flr1_topic_now=1;
						Topic=888;

						LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

						}
				}
	

}
































void Topic_2(){

	if(TOPIC2_target_board>9){

		TOPIC2_target_board=1;

		}

	if(key[1].single_flag==1){
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		
		TOPIC2_target_board++;

		key[1].single_flag=0;
	}

		if(key[0].single_flag==1){

			if(TOPIC2_target_board1==0){

				TOPIC2_target_board1=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			else if(TOPIC2_target_board2==0){

				TOPIC2_target_board2=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			else if(TOPIC2_target_board3==0){

				TOPIC2_target_board3=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			else if(TOPIC2_target_board4==0){

				TOPIC2_target_board4=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			

			key[0].single_flag=0;
		}


		if(topic_step==0){


			target_chess=4;
			target_board=TOPIC2_target_board1;

			start_black=1;
			start_white=0;
			if(target_board!=0&&TOPIC2_target_board4!=0){
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
		}

		if(topic_step==1){
			target_chess=5;
			target_board=TOPIC2_target_board2;

			start_black=1;
			start_white=0;
			if(target_board!=0&&TOPIC2_target_board4!=0){
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
			
		}

		if(topic_step==2){

			target_chess=4;
			target_board=TOPIC2_target_board3;

			start_black=0;
			start_white=1;
			if(target_board!=0&&TOPIC2_target_board4!=0){
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
			
		}

		if(topic_step==3){

			target_chess=5;
			target_board=TOPIC2_target_board4;

			start_black=0;
			start_white=1;
			if(target_board!=0&&TOPIC2_target_board4!=0){					
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
			
		}


	if(move_flag==1&&TOPIC2_target_board4!=0){

		
		chess_time++;
		if(chess_time>chess_time_total){
		total_chess_time+=0.1f;
		chess_time=0;
		}	
		
		if(step_move==0){ 
		{	
				//正常对弈
				
					//那我黑棋起手如何呢
					if(start_black==1&&start_white==0){

						if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
					else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
					else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
					else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
					else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

						if(target_chess==1&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==2&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==3&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==4&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==5&&step_total_y==0){y_move(center_y+7400,2);}
					}

					//白棋起手
					if(start_black==0&&start_white==1){

						if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
					else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
					else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
					else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
					else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

						if(target_chess==1&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==2&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==3&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==4&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==5&&step_total_y==0){y_move(center_y-7400,2);}
					}
				

				}



		}
		
		//取
			if (step_total_x==1&&step_total_y==1&&step_total_z==0){step_move=1;}

				if (step_move==1&&step_total_z==0){take_chess();}

			if (step_total_x==1&&step_total_y==1&&step_total_z==1) {step_move=2;}
		

		//归位 或者不归位
		if (step_move==2)
		{	
				//取放动作结算
				take_chess_step=0;
				release_chess_step=0;

				//那我黑棋起手如何呢
				if(start_black==1&&start_white==0){

					if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					if(target_chess==1&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y+7400,1);}
				}

				//白棋起手
				if(start_black==0&&start_white==1){

					if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					if(target_chess==1&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y-7400,1);}
				}

				}

		


		if (step_total_x==2&&step_total_y==2&&step_total_z==1){step_move=3;}
		
		//移
		if (step_move==3)
		{
				

			Delay_time++;
		

			if (target_board==6&& step_total_x==2) {

				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x,2);}

			} else if (target_board == 5 && step_total_x == 2) {

				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 4 && step_total_x == 2) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);

			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 7 && step_total_x == 2) {

				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {

				x_move(target_x, 2);}

			} else if (target_board == 8 && step_total_x == 2) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);

			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 9 && step_total_x == 2) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 1 && step_total_x == 2) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 2 && step_total_x == 2) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 3 && step_total_x == 2) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
		}
		

		

			if (target_board == 1 && step_total_y == 2) {

				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {

				y_move(target_y, 2);}

			} else if (target_board == 2 && step_total_y == 2) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}


			} else if (target_board == 3 && step_total_y == 2) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}

			} else if (target_board == 4 && step_total_y == 2) {

				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}

			} else if (target_board == 5 && step_total_y == 2) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 6 && step_total_y == 2) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}

			} else if (target_board == 7 && step_total_y == 2) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}


			} else if (target_board == 8 && step_total_y == 2) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}

			} else if (target_board == 9 && step_total_y == 2) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			}

			//角度

                // Delay_time++;
                // if(Delay_time>motor_time_x){
			
				// 	if(target_board==7&&step_total_x==2){x_move(center_x-2500,1);}
				// else if(target_board==4&&step_total_x==2){x_move(center_x,1);}
				// else if(target_board==1&&step_total_x==2){x_move(center_x+2500,1);}
				// else if(target_board==8&&step_total_x==2){x_move(center_x-2500,1);}
				// else if(target_board==5&&step_total_x==2){x_move(center_x,1);}
				// else if(target_board==2&&step_total_x==2){x_move(center_x+2500,1);}
				// else if(target_board==9&&step_total_x==2){x_move(center_x-2500,1);}
				// else if(target_board==sin&&step_total_x==2){x_move(center_x,1);}
				// else if(target_board==3&&step_total_x==2){x_move(center_x+2500,1);}
                // }
				// if(Delay_time>motor_time_y){
				// 	 if(target_board==7&&step_total_y==2){y_move(center_y+2500,1);}
				// else if(target_board==4&&step_total_y==2){y_move(center_y+2500,1);}
				// else if(target_board==1&&step_total_y==2){y_move(center_y+2500,1);}
				// else if(target_board==8&&step_total_y==2){y_move(center_y,1);}
				// else if(target_board==5&&step_total_y==2){y_move(center_y,1);}
				// else if(target_board==2&&step_total_y==2){y_move(center_y,1);}
				// else if(target_board==9&&step_total_y==2){y_move(center_y-2500,1);}
				// else if(target_board==sin&&step_total_y==2){y_move(center_y-2500,1);}
				// else if(target_board==3&&step_total_y==2){y_move(center_y-2500,1);}
				// }



		}


		//放
		if (step_total_x==3&&step_total_y==3&&step_total_z==1&&step_move!=4){Delay_time=0;step_move=4;}
		if (step_move==4&&step_total_z==1)
		{       
			
				release_chess();


		}

		//回
		if (step_total_x==3&&step_total_y==3&&step_total_z==2){step_move=5;}
		if (step_move==5)
		{	
				//取放动作结算
				take_chess_step=0;
				release_chess_step=0;
               
			//坐标
                
			
		Delay_time++;
		if (Delay_time > motor_time_x) {
			if (target_board==6&& step_total_x==3) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				x_move(target_x,1);
			} else if (target_board == 5 && step_total_x == 3) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				x_move(target_x, 1);
			} else if (target_board == 4 && step_total_x == 3) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
				x_move(target_x, 1);
			} else if (target_board == 7 && step_total_x == 3) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				x_move(target_x, 1);
			} else if (target_board == 8 && step_total_x == 3) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				x_move(target_x, 1);
			} else if (target_board == 9 && step_total_x == 3) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				x_move(target_x, 1);
			} else if (target_board == 1 && step_total_x == 3) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				x_move(target_x, 1);
			} else if (target_board == 2 && step_total_x == 3) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				x_move(target_x, 1);
			} else if (target_board == 3 && step_total_x == 3) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				x_move(target_x, 1);
		}
		}

		if (Delay_time > motor_time_y) {
			if (target_board == 1 && step_total_y == 3) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 2 && step_total_y == 3) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 3 && step_total_y == 3) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 4 && step_total_y == 3) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 5 && step_total_y == 3) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 6 && step_total_y == 3) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 7 && step_total_y == 3) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 8 && step_total_y == 3) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			} else if (target_board == 9 && step_total_y == 3) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				y_move(target_y, 1);
			}
		}




			//角度

                // Delay_time++;
                // if(Delay_time>motor_time_x){
			
				// 	if(target_board==7&&step_total_x==3){x_move(center_x-2500,1);}
				// else if(target_board==4&&step_total_x==3){x_move(center_x,1);}
				// else if(target_board==1&&step_total_x==3){x_move(center_x+2500,1);}
				// else if(target_board==8&&step_total_x==3){x_move(center_x-2500,1);}
				// else if(target_board==5&&step_total_x==3){x_move(center_x,1);}
				// else if(target_board==2&&step_total_x==3){x_move(center_x+2500,1);}
				// else if(target_board==9&&step_total_x==3){x_move(center_x-2500,1);}
				// else if(target_board==6&&step_total_x==3){x_move(center_x,1);}
				// else if(target_board==3&&step_total_x==3){x_move(center_x+2500,1);}
                // }
				// if(Delay_time>motor_time_y){
				// 	 if(target_board==7&&step_total_y==3){y_move(center_y+2500,1);}
				// else if(target_board==4&&step_total_y==3){y_move(center_y+2500,1);}
				// else if(target_board==1&&step_total_y==3){y_move(center_y+2500,1);}
				// else if(target_board==8&&step_total_y==3){y_move(center_y,1);}
				// else if(target_board==5&&step_total_y==3){y_move(center_y,1);}
				// else if(target_board==2&&step_total_y==3){y_move(center_y,1);}
				// else if(target_board==9&&step_total_y==3){y_move(center_y-2500,1);}
				// else if(target_board==6&&step_total_y==3){y_move(center_y-2500,1);}
				// else if(target_board==3&&step_total_y==3){y_move(center_y-2500,1);}
				// }
		}
			//走完一步棋子后结算画面
			if(step_total_x==4&&step_total_y==4){

                move_flag=0;
				//清空计时
				chess_time=0;
				total_chess_time=0;
				light_off();

                Delay_time=0;

				HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_RESET); //关电机
				HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET); 


				step_move=0;

				chess_reset();
				topic_step++;
				if(topic_step==4){Topic=88;}
				
				
					}
		}

}
    




























void Topic_3(){

	if(TOPIC2_target_board>9){

		TOPIC2_target_board=1;

		}

	if(key[1].single_flag==1){
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		
		TOPIC2_target_board++;

		key[1].single_flag=0;
	}

		if(key[0].single_flag==1){

			if(TOPIC2_target_board1==0){

				TOPIC2_target_board1=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			else if(TOPIC2_target_board2==0){

				TOPIC2_target_board2=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			else if(TOPIC2_target_board3==0){

				TOPIC2_target_board3=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			else if(TOPIC2_target_board4==0){

				TOPIC2_target_board4=TOPIC2_target_board;
				TOPIC2_target_board=1;
			}
			

			key[0].single_flag=0;
		}


		if(topic_step==0){


			target_chess=4;
			target_board=TOPIC2_target_board1;

			start_black=1;
			start_white=0;
			if(target_board!=0&&TOPIC2_target_board4!=0){
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
		}

		if(topic_step==1){
			target_chess=5;
			target_board=TOPIC2_target_board2;

			start_black=1;
			start_white=0;
			if(target_board!=0&&TOPIC2_target_board4!=0){
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
			
		}

		if(topic_step==2){

			target_chess=4;
			target_board=TOPIC2_target_board3;

			start_black=0;
			start_white=1;
			if(target_board!=0&&TOPIC2_target_board4!=0){
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
			
		}

		if(topic_step==3){

			target_chess=5;
			target_board=TOPIC2_target_board4;

			start_black=0;
			start_white=1;
			if(target_board!=0&&TOPIC2_target_board4!=0){					
					chess_time=0;
					total_chess_time=0;
					light_off();
					move_flag=1;}
			
		}


	if(move_flag==1&&TOPIC2_target_board4!=0){

		
		chess_time++;
		if(chess_time>chess_time_total){
		total_chess_time+=0.1f;
		chess_time=0;
		}	
		
		if(step_move==0){ 
		{	
				//正常对弈
				
					//那我黑棋起手如何呢
					if(start_black==1&&start_white==0){

						if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
					else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
					else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
					else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
					else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

						if(target_chess==1&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==2&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==3&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==4&&step_total_y==0){y_move(center_y+7400,2);}
					else if(target_chess==5&&step_total_y==0){y_move(center_y+7400,2);}
					}

					//白棋起手
					if(start_black==0&&start_white==1){

						if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
					else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
					else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
					else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
					else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

						if(target_chess==1&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==2&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==3&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==4&&step_total_y==0){y_move(center_y-7400,2);}
					else if(target_chess==5&&step_total_y==0){y_move(center_y-7400,2);}
					}
				

				}



		}
		
		//取
			if (step_total_x==1&&step_total_y==1&&step_total_z==0){step_move=1;}

				if (step_move==1&&step_total_z==0){take_chess();}

			if (step_total_x==1&&step_total_y==1&&step_total_z==1) {step_move=2;}
		

		//归位 或者不归位
		if (step_move==2)
		{	
				//取放动作结算
				take_chess_step=0;
				release_chess_step=0;

				//那我黑棋起手如何呢
				if(start_black==1&&start_white==0){

					if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					if(target_chess==1&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y+7400,1);}
				}

				//白棋起手
				if(start_black==0&&start_white==1){

					if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					if(target_chess==1&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y-7400,1);}
				}

				}

		


		if (step_total_x==2&&step_total_y==2&&step_total_z==1){step_move=3;}
		
		//移
		if (step_move==3)
		{
				// 到目标棋盘 
				Delay_time++;
		

			if (target_board==6&& step_total_x==2) {

				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x,2);}

			} else if (target_board == 5 && step_total_x == 2) {

				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 4 && step_total_x == 2) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);

			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 7 && step_total_x == 2) {

				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {

				x_move(target_x, 2);}

			} else if (target_board == 8 && step_total_x == 2) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);

			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 9 && step_total_x == 2) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 1 && step_total_x == 2) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 2 && step_total_x == 2) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}

			} else if (target_board == 3 && step_total_x == 2) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
		}
		

		

			if (target_board == 1 && step_total_y == 2) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {

				y_move(target_y, 2);}

			} else if (target_board == 2 && step_total_y == 2) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}


			} else if (target_board == 3 && step_total_y == 2) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}

			} else if (target_board == 4 && step_total_y == 2) {

				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}

			} else if (target_board == 5 && step_total_y == 2) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 6 && step_total_y == 2) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}

			} else if (target_board == 7 && step_total_y == 2) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}


			} else if (target_board == 8 && step_total_y == 2) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}

			} else if (target_board == 9 && step_total_y == 2) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			}


		}



		}






		//放
		if (step_total_x==3&&step_total_y==3&&step_total_z==1&&step_move!=4){Delay_time=0;step_move=4;}
		if (step_move==4&&step_total_z==1)
		{       
			
				release_chess();


		}

		//回
		if (step_total_x==3&&step_total_y==3&&step_total_z==2){step_move=5;}
		if (step_move==5)
		{	
				//取放动作结算
				take_chess_step=0;
				release_chess_step=0;
                

				Delay_time++;
		

			if (target_board==6&& step_total_x==2) {

				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x,1);}

			} else if (target_board == 5 && step_total_x == 2) {

				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);
				}
			} else if (target_board == 4 && step_total_x == 2) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);

			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}

			} else if (target_board == 7 && step_total_x == 2) {

				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {

				x_move(target_x, 1);}

			} else if (target_board == 8 && step_total_x == 2) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);

			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}

			} else if (target_board == 9 && step_total_x == 2) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}

			} else if (target_board == 1 && step_total_x == 2) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);
				}
			} else if (target_board == 2 && step_total_x == 2) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}

			} else if (target_board == 3 && step_total_x == 2) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);

				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
		}
		

		

			if (target_board == 1 && step_total_y == 2) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {

				y_move(target_y, 1);}

			} else if (target_board == 2 && step_total_y == 2) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}


			} else if (target_board == 3 && step_total_y == 2) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}

			} else if (target_board == 4 && step_total_y == 2) {

				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}

			} else if (target_board == 5 && step_total_y == 2) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 6 && step_total_y == 2) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}

			} else if (target_board == 7 && step_total_y == 2) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}


			} else if (target_board == 8 && step_total_y == 2) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}

			} else if (target_board == 9 && step_total_y == 2) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);

				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			}





		}
			//走完一步棋子后结算画面
			if(step_total_x==4&&step_total_y==4){

                move_flag=0;
				//清空计时
				chess_time=0;
				total_chess_time=0;
				light_off();

                Delay_time=0;

				HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_RESET); //关电机
				HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET); 


				step_move=0;

				chess_reset();
				topic_step++;
				if(topic_step==4){Topic=88;}
				
				
					}
		}
    
























void Topic_4(){
		
//题4 对弈一手如何呢
		start_black=1;start_white=0;

	if(take_choice==0){
		if(TOPIC4_target_board>9){

				TOPIC4_target_board=1;

				}

		if(key[1].single_flag==1){
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			
			TOPIC4_target_board++;

			key[1].single_flag=0;
		}

			if(key[0].single_flag==1){

				if(TOPIC4_target_board1==0){

					TOPIC4_target_board1=TOPIC4_target_board;
					TOPIC4_target_board=1;
				}

				key[0].single_flag=0;
			}


			if(topic_step==0){

				target_chess=5;
				target_board=TOPIC4_target_board1;

				start_black=1;
				start_white=0;
				if(target_board!=0&&TOPIC4_target_board1!=0)
				{

					//清空计时
					chess_time=0;
					total_chess_time=0;

					light_off();
					move_flag=1;

					take_choice=1;
					}
			}		
		
}


	if(take_choice==1){
		//按键按下 开始拍 棋子 图
		if(key[2].single_flag==1){
			
			//人走之后，拍一张照
			Take_photo_Delay_flag=1;



			//清空计时
			chess_time=0;
			total_chess_time=0;

			light_off();

			//单次按下
			key[2].single_flag=0; 
		}

		if (Take_photo_Delay_flag == 1) {
				Take_photo_Delay_time++;

			if(Take_photo_Delay_time<5000){

		 	//取到坐标后 直接填充到数组里锁死,顺便把棋子数量也统计了
				qipan_full();
				HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			}

			else{
				Take_photo_Delay_time = 0;
				Take_photo_Delay_flag=0;
				
					//装置白棋起手
					if(start_black==0&&start_white==1){
						//拍照之后 如果黑棋没有比白棋多一的话，就说明偷棋了
						if(now_black_chess<now_white_chess&&chess_total>=2){

							mistake_flag=1;

							//拍真实棋盘，拍完倒计时然后进行动
							Qipan_true_Delay_flag = 1;
						}
						//正常弈棋 
						else{
							//找下个落棋点位置
							target_board=findBestMove(qizi)+1;
							//作弊标志位
							mistake_flag=0;
							//电机驱动标志位
							move_flag=1;
						}
							}
							
					//装置黑棋起手
					if(start_black==1&&start_white==0){
					//拍照之后 如果黑棋没有跟白棋数量相等的话，就说明偷棋了
						if(now_black_chess>now_white_chess&&chess_total>=2){
							mistake_flag=1;
							//拍真实棋盘，拍完倒计时然后进行动
							Qipan_true_Delay_flag = 1;
						}
						//正常弈棋 
						else{
							//找下个落棋点位置
							target_board=findBestMove(qizi)+1;
							//作弊标志位
							mistake_flag=0;
							//电机驱动标志位
							move_flag=1;

						} 
						}
				  }

				}

			//有偷棋的
			if (Qipan_true_Delay_flag == 1) {
				Qipan_true_Delay_time++;
				if (Qipan_true_Delay_time < 5000) {

					qipan_true();//拍一张目前的棋盘
				} 
				else {
					his_target_chess=target_chess;
					Qipan_true_Delay_time = 0;
					Qipan_true_Delay_flag = 0;
					if(mistake_flag==1){
					target_chess=find_mischess()+1;//找出错误的棋子 即被移动的棋子现位置
					target_board=qipan_rectify()+1;//找出被移动的棋子位置 即被移动的棋子原位置
					}
					move_flag=1;
				}
		}	
		

	}
	// //X轴  1 是往下 2 往上 
	// //Y轴  1 是往右 2 往左

	//移
	if(move_flag==1){

		if(last_photo_flag==0){
			chess_time++;

			if(chess_time>chess_time_total){
			total_chess_time+=0.1f;
			chess_time=0;
			}
	}
       if(step_move==0) 
	   {	
			//正常对弈
			if(mistake_flag==0){
				//那我黑棋起手如何呢
				if(start_black==1&&start_white==0){

					 if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
				else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
				else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
				else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
				else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

					 if(target_chess==1&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==2&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==3&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==4&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==5&&step_total_y==0){y_move(center_y+7400,2);}
				}

				//白棋起手
				if(start_black==0&&start_white==1){

					 if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
				else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
				else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
				else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
				else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

					 if(target_chess==1&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==2&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==3&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==4&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==5&&step_total_y==0){y_move(center_y-7400,2);}
				}
			}
			//有狗
			if(mistake_flag==1){

                Delay_time++;
			if (target_chess==6&& step_total_x==0) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,2);}
			} else if (target_chess == 5 && step_total_x == 0) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_chess == 4 && step_total_x == 0) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 7 && step_total_x == 0) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess== 8 && step_total_x == 0) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 9 && step_total_x == 0) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 1 && step_total_x == 0) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_chess == 2 && step_total_x == 0) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 3 && step_total_x == 0) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
		}
		
			if (target_chess == 1 && step_total_y == 0) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 2 && step_total_y == 0) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 3 && step_total_y == 0) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 4 && step_total_y == 0) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}
			} else if (target_chess == 5 && step_total_y == 0) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 6 && step_total_y == 0) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 7 && step_total_y == 0) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}
			} else if (target_chess == 8 && step_total_y == 0) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 9 && step_total_y == 0) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			}

			}




	   }
	   
	//取
		if (step_total_x==1&&step_total_y==1&&step_total_z==0){Delay_time=0;step_move=1;}

       if (step_move==1&&step_total_z==0)
	   {	
			
		
			take_chess();

	   }

		if (step_total_x==1&&step_total_y==1&&step_total_z==1) {step_move=2;}
	  

	//归位 或者不归位
       if (step_move==2)
	   {	
			//取放动作结算
			take_chess_step=0;
			release_chess_step=0;

			if(mistake_flag==0){

				//那我黑棋起手如何呢
				if(start_black==1&&start_white==0){

					 if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					 if(target_chess==1&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y+7400,1);}
				}

				//白棋起手
				if(start_black==0&&start_white==1){
					
					 if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					 if(target_chess==1&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y-7400,1);}
				}
			}
			//有狗
			if(mistake_flag==1){

               Delay_time++;
			if (target_chess==6&& step_total_x==1) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,1);}
			} else if (target_chess == 5 && step_total_x == 1) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);
				}
			} else if (target_chess == 4 && step_total_x == 1) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 7 && step_total_x == 1) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 8 && step_total_x == 1) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 9 && step_total_x == 1) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 1 && step_total_x == 1) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 2 && step_total_x == 1) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 3 && step_total_x == 1) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
		}
		

			if (target_chess == 1 && step_total_y == 1) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 2 && step_total_y == 1) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 3 && step_total_y == 1) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 4 && step_total_y == 1) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_chess == 5 && step_total_y == 1) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 6 && step_total_y == 1) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 7 && step_total_y == 1) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_chess == 8 && step_total_y == 1) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 9 && step_total_y == 1) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			}

			}



			}

	   


	if (step_total_x==2&&step_total_y==2&&step_total_z==1&&step_move!=3){Delay_time=0;step_move=3;}
	   
	//移
       if (step_move==3)
	   {
			// 到目标棋盘 
	// if(step_total_x==0){x_move(center_x+(tar-now)*120,2);}
	// if(step_total_y==0){y_move(center_y-(tar-now)*120,2);}
				
                Delay_time++;
		

			if (target_board==6&& step_total_x==2) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,2);}
			} else if (target_board == 5 && step_total_x == 2) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 4 && step_total_x == 2) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 7 && step_total_x == 2) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 8 && step_total_x == 2) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 9 && step_total_x == 2) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 1 && step_total_x == 2) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 2 && step_total_x == 2) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 3 && step_total_x == 2) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
		}
		

		

			if (target_board == 1 && step_total_y == 2) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}

			} else if (target_board == 2 && step_total_y == 2) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 3 && step_total_y == 2) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 4 && step_total_y == 2) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}

			} else if (target_board == 5 && step_total_y == 2) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 6 && step_total_y == 2) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 7 && step_total_y == 2) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}
			} else if (target_board == 8 && step_total_y == 2) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 9 && step_total_y == 2) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			}


	   }


	//放
	if (step_total_x==3&&step_total_y==3&&step_total_z==1&&step_move!=4){Delay_time=0;step_move=4;}
       if (step_move==4&&step_total_z==1)
	   {    
		
			release_chess();


	   }

	//回
	if (step_total_x==3&&step_total_y==3&&step_total_z==2){step_move=5;}
       if (step_move==5)
	   {	
			//取放动作结算
			take_chess_step=0;
			release_chess_step=0;
		
               Delay_time++;
			if (target_board==6&& step_total_x==3) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,1);}
			} else if (target_board == 5 && step_total_x == 3) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);
				}
			} else if (target_board == 4 && step_total_x == 3) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 7 && step_total_x == 3) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 8 && step_total_x == 3) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 9 && step_total_x == 3) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 1 && step_total_x == 3) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 2 && step_total_x == 3) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 3 && step_total_x == 3) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
		}
		

			if (target_board == 1 && step_total_y == 3) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 2 && step_total_y == 3) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 3 && step_total_y == 3) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 4 && step_total_y == 3) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_board == 5 && step_total_y == 3) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 6 && step_total_y == 3) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 7 && step_total_y == 3) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_board == 8 && step_total_y == 3) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 9 && step_total_y == 3) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			}
	   }
		//走完一步棋子后结算画面
		if(step_total_x==4&&step_total_y==4){


			last_photo_flag=1;
            Delay_time=0;
			

			light_on();


			HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_RESET); //关电机
			HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET); 





			his_chess_total=chess_total;
			step_move=0;
			
			//机器 放完棋子 拍一张照 
			if(last_photo_flag==1){

				last_photo_time++;

				//存个档先，存的是机器结束 人走棋 之前的图片
				qipan_full();
			}
			if(last_photo_time>3000){

				move_flag=0;

				qipan_his();

				
				last_photo_flag=0;
				last_photo_time=0;


				if(mistake_flag==1){  
					mistake_flag=0;  
					Qipan_true_Delay_flag=0;
					Qipan_true_Delay_time=0;

					now_black_chess=0;
					now_white_chess=0;

					target_chess=his_target_chess+1;
					
					for (int i = 0; i < 9; i++) {
						qizi[i] = 0;
						true_qizi[i] = 0;
						his_qizi[i] = 0;
						}

					
						}
				target_chess--;
				chess_reset();
			}
			

			
			


			

			// step_move++;
			
			
			

				}

	}



}

    






















void Topic_5(){
		
//题5 对弈一手如何呢
		start_black=0;start_white=1;
		
		//有偷棋的

		//按键按下 开始拍 棋子 图
		if(key[2].single_flag==1){
			
			//人走之后，拍一张照
			Take_photo_Delay_flag=1;
			// Take_photo_Delay_time=0;

			//清空计时
			chess_time=0;
			total_chess_time=0;

			light_off();

			//单次按下
			key[2].single_flag=0; 
		}

		if (Take_photo_Delay_flag == 1) {
				Take_photo_Delay_time++;

			if(Take_photo_Delay_time<5000){

		 	//取到坐标后 直接填充到数组里锁死,顺便把棋子数量也统计了
				qipan_full();
				HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			}

			else{
				Take_photo_Delay_time = 0;
				Take_photo_Delay_flag=0;
				
					//装置白棋起手
					if(start_black==0&&start_white==1){
						//拍照之后 如果黑棋没有比白棋多一的话，就说明偷棋了
						if(now_black_chess<now_white_chess&&chess_total>=2){

							mistake_flag=1;

							//拍真实棋盘，拍完倒计时然后进行动
							Qipan_true_Delay_flag = 1;
						}
						//正常弈棋 
						else{
							//找下个落棋点位置
							target_board=findBestMove(qizi)+1;
							//作弊标志位
							mistake_flag=0;
							//电机驱动标志位
							move_flag=1;
						}
							}
							
					//装置黑棋起手
					if(start_black==1&&start_white==0){
					//拍照之后 如果黑棋没有跟白棋数量相等的话，就说明偷棋了
						if(now_black_chess>now_white_chess&&chess_total>=2){
							mistake_flag=1;
							//拍真实棋盘，拍完倒计时然后进行动
							Qipan_true_Delay_flag = 1;
						}
						//正常弈棋 
						else{
							//找下个落棋点位置
							target_board=findBestMove(qizi)+1;
							//作弊标志位
							mistake_flag=0;
							//电机驱动标志位
							move_flag=1;

						}
						} 
				 }

				}
			if (Qipan_true_Delay_flag == 1) {
				Qipan_true_Delay_time++;
				if (Qipan_true_Delay_time < 5000) {

					qipan_true();//拍一张目前的棋盘
				} 
				else {
					his_target_chess=target_chess;
					Qipan_true_Delay_time = 0;
					Qipan_true_Delay_flag = 0;
					if(mistake_flag==1){
					target_chess=find_mischess()+1;//找出错误的棋子 即被移动的棋子现位置
					target_board=qipan_rectify()+1;//找出被移动的棋子位置 即被移动的棋子原位置
					}
					move_flag=1;
				}
		}	
		


	// //X轴  1 是往下 2 往上 
	// //Y轴  1 是往右 2 往左

	//移
	if(move_flag==1){
		
		if(last_photo_flag==0){
		chess_time++;

		if(chess_time>chess_time_total){
		total_chess_time+=0.1f;
		chess_time=0;
		}
		}
       if(step_move==0) 
	   {	
			//正常对弈
			if(mistake_flag==0){
				//那我黑棋起手如何呢
				if(start_black==1&&start_white==0){

					 if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
				else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
				else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
				else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
				else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

					 if(target_chess==1&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==2&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==3&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==4&&step_total_y==0){y_move(center_y+7400,2);}
				else if(target_chess==5&&step_total_y==0){y_move(center_y+7400,2);}
				}

				//白棋起手
				if(start_black==0&&start_white==1){

					 if(target_chess==1&&step_total_x==0){x_move(center_x+4000,2);}
				else if(target_chess==2&&step_total_x==0){x_move(center_x+2000,2);}
				else if(target_chess==3&&step_total_x==0){x_move(center_x,2);}
				else if(target_chess==4&&step_total_x==0){x_move(center_x-2000,2);}
				else if(target_chess==5&&step_total_x==0){x_move(center_x-4000,2);}

					 if(target_chess==1&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==2&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==3&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==4&&step_total_y==0){y_move(center_y-7400,2);}
				else if(target_chess==5&&step_total_y==0){y_move(center_y-7400,2);}
				}
			}
			//有狗
			if(mistake_flag==1){

                 Delay_time++;
			if (target_chess==6&& step_total_x==0) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,2);}
			} else if (target_chess == 5 && step_total_x == 0) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_chess == 4 && step_total_x == 0) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 7 && step_total_x == 0) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 8 && step_total_x == 0) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 9 && step_total_x == 0) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 1 && step_total_x == 0) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_chess == 2 && step_total_x == 0) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_chess == 3 && step_total_x == 0) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
		}
		
			if (target_chess == 1 && step_total_y == 0) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 2 && step_total_y == 0) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 3 && step_total_y == 0) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 4 && step_total_y == 0) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}
			} else if (target_chess == 5 && step_total_y == 0) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 6 && step_total_y == 0) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 7 && step_total_y == 0) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}
			} else if (target_chess == 8 && step_total_y == 0) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_chess == 9 && step_total_y == 0) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			}

			}





	   }
	   
	//取
		if (step_total_x==1&&step_total_y==1&&step_total_z==0){Delay_time=0;step_move=1;}

       if (step_move==1&&step_total_z==0)
	   {	
			
		
			take_chess();

	   }

		if (step_total_x==1&&step_total_y==1&&step_total_z==1) {step_move=2;}
	  

	//归位 或者不归位
       if (step_move==2)
	   {	
			//取放动作结算
			take_chess_step=0;
			release_chess_step=0;

			if(mistake_flag==0){

				//那我黑棋起手如何呢
				if(start_black==1&&start_white==0){

					 if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					 if(target_chess==1&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y+7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y+7400,1);}
				}

				//白棋起手
				if(start_black==0&&start_white==1){
					
					 if(target_chess==1&&step_total_x==1){x_move(center_x+4000,1);}
				else if(target_chess==2&&step_total_x==1){x_move(center_x+2000,1);}
				else if(target_chess==3&&step_total_x==1){x_move(center_x,1);}
				else if(target_chess==4&&step_total_x==1){x_move(center_x-2000,1);}
				else if(target_chess==5&&step_total_x==1){x_move(center_x-4000,1);}

					 if(target_chess==1&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==2&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==3&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==4&&step_total_y==1){y_move(center_y-7400,1);}
				else if(target_chess==5&&step_total_y==1){y_move(center_y-7400,1);}
				}
			}
			//有狗
			if(mistake_flag==1){

                 Delay_time++;
			if (target_chess==6&& step_total_x==1) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,1);}
			} else if (target_chess == 5 && step_total_x == 1) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);
				}
			} else if (target_chess == 4 && step_total_x == 1) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 7 && step_total_x == 1) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 8 && step_total_x == 1) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 9 && step_total_x == 1) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 1 && step_total_x == 1) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);
				}
			} else if (target_chess == 2 && step_total_x == 1) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_chess == 3 && step_total_x == 1) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
		}
		
			if (target_chess == 1 && step_total_y == 1) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 2 && step_total_y == 1) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 3 && step_total_y == 1) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 4 && step_total_y == 1) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_chess == 5 && step_total_y == 1) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 6 && step_total_y == 1) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 7 && step_total_y == 1) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_chess == 8 && step_total_y == 1) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_chess == 9 && step_total_y == 1) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			}

			}



			}

	   


	if (step_total_x==2&&step_total_y==2&&step_total_z==1&&step_move!=3){Delay_time=0;step_move=3;}
	   
	//移
       if (step_move==3)
	   {
			// 到目标棋盘 
	// if(step_total_x==0){x_move(center_x+(tar-now)*120,2);}
	// if(step_total_y==0){y_move(center_y-(tar-now)*120,2);}
				
                 Delay_time++;
			if (target_board==6&& step_total_x==2) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,2);}
			} else if (target_board == 5 && step_total_x == 2) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 4 && step_total_x == 2) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 7 && step_total_x == 2) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 8 && step_total_x == 2) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 9 && step_total_x == 2) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 1 && step_total_x == 2) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);
				}
			} else if (target_board == 2 && step_total_x == 2) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
			} else if (target_board == 3 && step_total_x == 2) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 2);}
		}
		
			if (target_board == 1 && step_total_y == 2) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 2 && step_total_y == 2) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 3 && step_total_y == 2) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 4 && step_total_y == 2) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}
			} else if (target_board == 5 && step_total_y == 2) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 6 && step_total_y == 2) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 7 && step_total_y == 2) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,2);}
			} else if (target_board == 8 && step_total_y == 2) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			} else if (target_board == 9 && step_total_y == 2) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 2);}
			}


	   }


	//放
	if (step_total_x==3&&step_total_y==3&&step_total_z==1&&step_move!=4){Delay_time=0;step_move=4;}
       if (step_move==4&&step_total_z==1)
	   {    
		
			release_chess();


	   }

	//回
	if (step_total_x==3&&step_total_y==3&&step_total_z==2){step_move=5;}
       if (step_move==5)
	   {	
			//取放动作结算
			take_chess_step=0;
			release_chess_step=0;
		
                Delay_time++;
			if (target_board==6&& step_total_x==3) {
				target_x=((((x6-board_x)*cos)/100+((y6-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,1);}
			} else if (target_board == 5 && step_total_x == 3) {
				target_x = ((((x5-board_x)*cos)/100+((y5-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x,1);
				}
			} else if (target_board == 4 && step_total_x == 3) {
				target_x =((((x4-board_x)*cos)/100 + ((y4-board_y)*sin)/100) *maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 7 && step_total_x == 3) {
				target_x =((((x7-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 8 && step_total_x == 3) {
				target_x = ((((x8 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
			if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 9 && step_total_x == 3) {
				target_x =  ((((x9 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 1 && step_total_x == 3) {
				target_x =((((x1-board_x)*cos) / 100 + ((y7-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);
				}
			} else if (target_board == 2 && step_total_x == 3) {
				target_x = ((((x2 - board_x)*cos)/100+((y8-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
			} else if (target_board == 3 && step_total_x == 3) {
				target_x =  ((((x3 -board_x)*cos)/100+((y9-board_y)*sin)/100)*maichong_x);
				if (Delay_time > motor_time_x) {
				x_move(target_x, 1);}
		}
		
			if (target_board == 1 && step_total_y == 3) {
				target_y =-((((y1-board_y)*cos)/100-((x1-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 2 && step_total_y == 3) {
				target_y =-((((y2 - board_y)*cos)/100-((x2-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 3 && step_total_y == 3) {
				target_y =-((((y3-board_y)*cos)/100-((x3-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 4 && step_total_y == 3) {
				target_y =-((((y4 - board_y)*cos)/100-((x4-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_board == 5 && step_total_y == 3) {
				target_y =-((((y5-board_y)*cos)/100-((x5-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 6 && step_total_y == 3) {
				target_y =-((((y6 - board_y)*cos)/100-((x6-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 7 && step_total_y == 3) {
				target_y =-((((y7-board_y)*cos)/100-((x7-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y,1);}
			} else if (target_board == 8 && step_total_y == 3) {
				target_y =-((((y8 - board_y)*cos)/100-((x8-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			} else if (target_board == 9 && step_total_y == 3) {
				target_y =-((((y9-board_y)*cos)/100-((x9-board_x)*sin)/100)*maichong_y);
				if (Delay_time > motor_time_y) {
				y_move(target_y, 1);}
			}

	   }
		//走完一步棋子后结算画面
				if(step_total_x==4&&step_total_y==4){


			last_photo_flag=1;
            Delay_time=0;
			

			light_on();


			HAL_GPIO_WritePin(EN_X1_GPIO_Port, EN_X1_Pin, GPIO_PIN_RESET); //关电机
			HAL_GPIO_WritePin(EN_X2_GPIO_Port, EN_X2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET); 





			his_chess_total=chess_total;
			step_move=0;
			
			//机器 放完棋子 拍一张照 
			if(last_photo_flag==1){

				last_photo_time++;

				//存个档先，存的是机器结束 人走棋 之前的图片
				qipan_full();
			}
			if(last_photo_time>3000){

				move_flag=0;

				qipan_his();

				
				last_photo_flag=0;
				last_photo_time=0;


				if(mistake_flag==1){  
					mistake_flag=0;  
					Qipan_true_Delay_flag=0;
					Qipan_true_Delay_time=0;

					now_black_chess=0;
					now_white_chess=0;

					target_chess=his_target_chess+1;
					
					for (int i = 0; i < 9; i++) {
						qizi[i] = 0;
						true_qizi[i] = 0;
						his_qizi[i] = 0;
						}

					
						}
				target_chess--;
				chess_reset();
			}
			

			
			


			

			// step_move++;
			
			
			

				}

	}


    
}




















//调参
void Topic_6(){



	if(key[3].single_flag==1){ 	

		if(board_location_flag==0){
        board_x+=1;  
		}

		else{

		board_y+=1;

		}

		key[3].single_flag=0;
    }
	

    if(key[1].single_flag==1){

		if(board_location_flag==0){
        board_x-=1;
		}

		else {

		board_y-=1;

		}

		key[1].single_flag=0; 
    }


    if(key[2].single_flag==1){

		board_location_flag++;

		if(board_location_flag>1){

			board_location_flag=0;
		}
		key[2].single_flag=0;
    }





}


void Topic_8(){

	if(step_total_x==0){x_move(center_x,2);}
	if(step_total_y==0){y_move(center_y,2);}



}

    

