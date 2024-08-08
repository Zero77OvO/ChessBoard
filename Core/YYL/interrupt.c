#include "head_files.h"



#define USART1_REC_LEN_1  200
uint8_t USART1_RX_BUF_1[USART1_REC_LEN_1];
uint16_t USART1_RX_STA_1=0;
uint8_t USART1_NewData_1;
uint8_t RxState1_1 = 0;


//格子坐标 以及格子标号
int x=0;
int y=0;
int location_chess=0;

//第六题
//三种不同状态的棋盘对比，找错误棋子的
int qizi[9] = {0}; 
int his_qizi[9] = {0}; 
int true_qizi[9] = {0}; 

//九宫格坐标
int x1=0;int y1=0;
int x2=0;int y2=0;
int x3=0;int y3=0;
int x4=0;int y4=0;
int x5=0;int y5=0;
int x6=0;int y6=0;
int x7=0;int y7=0;
int x8=0;int y8=0;
int x9=0;int y9=0;

//原点坐标
int board_x=40; int board_y=278;

//按键切换
int board_location_flag=0;
//x偏下 board_x --;
//y 偏左 board_y --;


//格子坐标 以及格子标号


#define USART1_REC_LEN_2  200
uint8_t USART1_RX_BUF_2[USART1_REC_LEN_2];
uint16_t USART1_RX_STA_2=0;
uint8_t USART1_NewData_2;
uint8_t RxState1_2 = 0; 

//九个格子的状态返回
//黑棋是 2 白棋 是 1 没棋子 是 0
int location_1=0;
int location_2=0;
int location_3=0;
int location_4=0;
int location_5=0;
int location_6=0;
int location_7=0;
int location_8=0;
int location_9=0;

#define USART1_REC_LEN_3  200
uint8_t  USART1_RX_BUF_3[USART1_REC_LEN_3];
uint16_t USART1_RX_STA_3;
uint8_t USART1_NewData_3;
uint8_t RxState1_3 = 0; 

//棋盘外黑棋
int x1_black=0;int y1_black=0;
int x2_black=0;int y2_black=0;
int x3_black=0;int y3_black=0;
int x4_black=0;int y4_black=0;
int x5_black=0;int y5_black=0;


#define USART1_REC_LEN_4  200
uint8_t  USART1_RX_BUF_4[USART1_REC_LEN_4];
uint16_t USART1_RX_STA_4;
uint8_t USART1_NewData_4;
uint8_t RxState1_4 = 0; 

//棋盘外白棋
int x1_white=0;int y1_white=0;
int x2_white=0;int y2_white=0;
int x3_white=0;int y3_white=0;
int x4_white=0;int y4_white=0;
int x5_white=0;int y5_white=0;

//接收旋转的信号，如果是1 就是往左转的，如果是2 那就是往右转的
int rorate_angle=0;

//usart2
#define USART2_REC_LEN  200
uint8_t  USART2_RX_BUF[USART2_REC_LEN];
uint16_t USART2_RX_STA;
uint8_t USART2_NewData;
uint8_t RxState2;

#define USART3_REC_LEN  200
uint8_t  USART3_RX_BUF[USART3_REC_LEN];
uint16_t USART3_RX_STA;
uint8_t USART3_NewData;
uint8_t RxState3;



//usart6 vofa
#define RXSTRSIZE 256		  
uint8_t rx_string[RXSTRSIZE]; 
uint8_t rx_cnt = 0;			  
uint8_t rx_buff;			  
uint8_t RxBuff;
unsigned char shujv[12];
int vofa_i = 0, vofa_I = 0;
float vofa_float;




//没用到
uint8_t data[] = {0x2C,0x12,1,0,0x5B};
uint8_t data_2[] = {0x2C,0x12,0,1,0x5B};




//串口的一些标志位，没用到
int  last_x1=99; int last_y1=99;

int send_time=0;

int  last_x1_black=1; int last_y1_black=1;

int send_time_black=0;

int  last_x1_white=1; int last_y1_white=1;

int send_time_white=0;


//串口接收开关，没用到
int qipan_receive_flag=0; 
int qizi_receive_flag=0; 
int qizi_receive_flag_black_white=0; 


//是否开始移动
int move_flag=0;

//是否有人作弊 第六题
int mistake_flag=0;


//好像没用到 也是定时器的过渡单位
int move_up=0;
int move_up_1=0;

//定时器flag
int Delay_flag=0;
int Delay_time=0;


//拍照延时结尾
int last_photo_flag=0;
int last_photo_time=0;

//456题的拍照延时，定时器flag
int Take_photo_Delay_flag=0;
int Take_photo_Delay_time=0;

//6题的真实棋盘拍照延时
int Qipan_true_Delay_flag=0;
int Qipan_true_Delay_time=0;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	



	//参数计算
	if(htim->Instance == TIM2)
{ 	
	
	
	key_button();

	if(x1>10&&y9>10){qipan_receive_flag=1;}

		// target_x =  ((((x5 - board_x) * 99) / 100 + ((y5 - board_y) * 6) / 100) * 120);
		// target_y =  -((((y5 - board_y) * 99) / 100 - ((x5 - board_x) * 6) / 100) * 120);

	// //棋盘运算逻辑
	// if(Topic==1){
	// 	if(key[1].single_flag==1){location_9=1;key[1].single_flag=0; }


	// 	if(key[0].single_flag==1){
	// 		// HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
	// 		//取到坐标后 直接填充到数组里锁死,顺便把棋子数量也统计了
	// 		qipan_full();
	// 		// HAL_UART_Transmit(&huart2, data, sizeof(data), HAL_MAX_DELAY);
	// 		//单次按下
	// 		if(chess_total-his_chess_total==1){ move_flag=1;}
	// 		key[0].single_flag=0; 
	// 	}
	// 	//找下个落棋点位置
	// 	deviceNextMove();
	// }

	

}




	//运动控制
	if(htim->Instance == TIM4) //20ms
	{
	

		if(Topic==1){Topic_1();}
		else if(Topic==2){Topic_2();}
		else if(Topic==3){Topic_2();}
		else if(Topic==4){Topic_4();}
		else if(Topic==5){Topic_5();}
		else if(Topic==6){Topic_6();}

		// else if(Topic==8){Topic_8();}
		// //胜利结算画面
		// if(Topic==7){

		// }

	

	
 }




}










void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
	if(huart ==&huart2) 
	{ 						
		
			
			// HAL_UART_Transmit(&huart2, data, sizeof(data), HAL_MAX_DELAY);

		// if(x1_white!=0&&y1_white!=0&&x1_black!=0&&y1_black!=0&&send_time_white<10){
		// 	send_time_white++;
		// 	HAL_UART_Transmit(&huart2, data_2, sizeof(data_2), HAL_MAX_DELAY);
		// 	qizi_receive_flag_black_white=1;

		// 		}
		
 		USART1_NewData_2=USART1_NewData_3=USART1_NewData_1;

		if(qipan_receive_flag==0){

			if(RxState1_1 ==0&&USART1_NewData_1==0xF1){
				USART1_RX_BUF_1[USART1_RX_STA_1]=USART1_NewData_1;
				RxState1_1 = 1;
								}

				else if(RxState1_1 ==1&&USART1_NewData_1==0xF2){
				USART1_RX_BUF_1[USART1_RX_STA_1++]=USART1_NewData_1;
				RxState1_1 = 2;
				}

				else if(RxState1_1 ==2){
				USART1_RX_BUF_1[USART1_RX_STA_1++]=USART1_NewData_1;
				if(USART1_RX_BUF_1[USART1_RX_STA_1-1]== 0xF3){
					
						x =  USART1_RX_BUF_1[USART1_RX_STA_1-4]*2;
						y =  USART1_RX_BUF_1[USART1_RX_STA_1-3]*2;
						location_chess =  USART1_RX_BUF_1[USART1_RX_STA_1-2];

						last_x1=x1;
						last_y1=y9;

						if(location_chess==1){x7=x;y7=y;}
						if(location_chess==2){x4=x;y4=y;}
						if(location_chess==3){x1=x;y1=y;}
						if(location_chess==4){x8=x;y8=y;}
						if(location_chess==5){x5=x;y5=y;}
						if(location_chess==6){x2=x;y2=y;}
						if(location_chess==7){x9=x;y9=y;}
						if(location_chess==8){x6=x;y6=y;}
						if(location_chess==9){x3=x;y3=y;}
	
						

						RxState1_1=3; 
						}
				}

				else if(RxState1_1==3){
						USART1_RX_STA_1=0;
						memset(USART1_RX_BUF_1,0,sizeof(USART1_RX_BUF_1));
						RxState1_1=0;
				}
				if(USART1_RX_STA_1>(USART1_REC_LEN_1-1)){
						USART1_RX_STA_1=0;
							memset(USART1_RX_BUF_1,0,sizeof(USART1_RX_BUF_1));
								RxState1_1=0;
					}
			}

		//chess
		// if(qizi_receive_flag==1){

				if(RxState1_2 ==0&&USART1_NewData_2==0x4B){
					USART1_RX_BUF_2[USART1_RX_STA_2]=USART1_NewData_2;
					RxState1_2 = 1;
								}

				else if(RxState1_2 ==1&&USART1_NewData_2==0x4C){
				USART1_RX_BUF_2[USART1_RX_STA_2++]=USART1_NewData_2;
				RxState1_2 = 2;
				}

				else if(RxState1_2==2){
				USART1_RX_BUF_2[USART1_RX_STA_2++]=USART1_NewData_2;
				if(USART1_RX_BUF_2[USART1_RX_STA_2-1]== 0x4D){



						location_7=USART1_RX_BUF_2[USART1_RX_STA_2-10];
						location_4=USART1_RX_BUF_2[USART1_RX_STA_2-9];
						location_1=USART1_RX_BUF_2[USART1_RX_STA_2-8];
						location_8=USART1_RX_BUF_2[USART1_RX_STA_2-7];
						location_5=USART1_RX_BUF_2[USART1_RX_STA_2-6];
						location_2=USART1_RX_BUF_2[USART1_RX_STA_2-5];
						location_9=USART1_RX_BUF_2[USART1_RX_STA_2-4];
						location_6=USART1_RX_BUF_2[USART1_RX_STA_2-3];
						location_3=USART1_RX_BUF_2[USART1_RX_STA_2-2];


								RxState1_2=3; }
				}
				else if(RxState1_2==3){
								USART1_RX_STA_2=0;
								memset(USART1_RX_BUF_2,0,sizeof(USART1_RX_BUF_2));
								RxState1_2=0;
				}
				if(USART1_RX_STA_2>(USART1_REC_LEN_2-1)){
							USART1_RX_STA_2=0;
								memset(USART1_RX_BUF_2,0,sizeof(USART1_RX_BUF_2));
									RxState1_2=0;
					}


// // 题三收旋转

// 				if(RxState1_3 ==0&&USART1_NewData_3==0xA1){
// 					USART1_RX_BUF_3[USART1_RX_STA_3]=USART1_NewData_3;
// 					RxState1_3 = 1;
// 								}

// 				else if(RxState1_3 ==1&&USART1_NewData_3==0xB2){
// 				USART1_RX_BUF_3[USART1_RX_STA_3++]=USART1_NewData_3;
// 				RxState1_3 = 2;
// 				}

// 				else if(RxState1_3==2){
// 				USART1_RX_BUF_3[USART1_RX_STA_3++]=USART1_NewData_3;
// 				if(USART1_RX_BUF_3[USART1_RX_STA_3-1]== 0xC3){




// 						rorate_angle=USART1_RX_BUF_3[USART1_RX_STA_3-2];



// 								RxState1_3=3; }
// 				}
// 				else if(RxState1_3==3){
// 								USART1_RX_STA_3=0;
// 								memset(USART1_RX_BUF_3,0,sizeof(USART1_RX_BUF_3));
// 								RxState1_3=0;
// 				}
// 				if(USART1_RX_STA_3>(USART1_REC_LEN_3-1)){
// 							USART1_RX_STA_3=0;
// 								memset(USART1_RX_BUF_3,0,sizeof(USART1_RX_BUF_3));
// 									RxState1_3=0;
// 					}


// //收黑棋坐标

			
// 				if(RxState1_4 ==0&&USART1_NewData_4==0x6B){
// 					USART1_RX_BUF_4[USART1_RX_STA_4]=USART1_NewData_4;
// 					RxState1_4 = 1;
// 								}

// 				else if(RxState1_4 ==1&&USART1_NewData_4==0x6C){
// 				USART1_RX_BUF_4[USART1_RX_STA_4++]=USART1_NewData_4;
// 				RxState1_4 = 2;
// 				}

// 				else if(RxState1_4==2){
// 				USART1_RX_BUF_4[USART1_RX_STA_4++]=USART1_NewData_4;
// 				if(USART1_RX_BUF_4[USART1_RX_STA_4-1]== 0x6D){




// 						x1_black=USART1_RX_BUF_4[USART1_RX_STA_4-11]*2;
// 						y1_black=USART1_RX_BUF_4[USART1_RX_STA_4-10]*2;
// 						x2_black=USART1_RX_BUF_4[USART1_RX_STA_4-9]*2;
// 						y2_black=USART1_RX_BUF_4[USART1_RX_STA_4-8]*2;
// 						x3_black=USART1_RX_BUF_4[USART1_RX_STA_4-7]*2;
// 						y3_black=USART1_RX_BUF_4[USART1_RX_STA_4-6]*2;
// 						x4_black=USART1_RX_BUF_4[USART1_RX_STA_4-5]*2;
// 						y4_black=USART1_RX_BUF_4[USART1_RX_STA_4-4]*2;
// 						x5_black=USART1_RX_BUF_4[USART1_RX_STA_4-3]*2;
// 						y5_black=USART1_RX_BUF_4[USART1_RX_STA_4-2]*2;
						
// 						last_x1_black=x1_black;
// 						last_y1_black=y1_black;
// 								RxState1_4=3; }
// 				}
// 				else if(RxState1_4==3){
// 								USART1_RX_STA_4=0;
// 								memset(USART1_RX_BUF_4,0,sizeof(USART1_RX_BUF_4));
// 								RxState1_4=0;
// 				}
// 				if(USART1_RX_STA_4>(USART1_REC_LEN_4-1)){
// 							USART1_RX_STA_4=0;
// 								memset(USART1_RX_BUF_4,0,sizeof(USART1_RX_BUF_4));
// 									RxState1_4=0;
// 					}

// 			}	

		// }
			
		

  }	
	
// 	 //bluetooth
//   	if(huart ==&huart2) 
//     { 
//   	 if(RxState2 ==0){
//         USART2_RX_BUF[USART2_RX_STA]=USART2_NewData; 					
//         USART2_RX_STA++; 
//         RxState2 = 1;			
//   	}
//   	 else if(RxState2 ==1){
//         USART2_RX_BUF[USART2_RX_STA++]=USART2_NewData; 
//   	 	if(USART2_RX_STA >0||USART2_RX_BUF[USART2_RX_STA-1]== 0x12)
//   		 {

//   			x = USART2_RX_BUF[USART2_RX_STA-3];			
//   			y = USART2_RX_BUF[USART2_RX_STA-2];
 
				
//   			USART2_RX_STA=0;
//   			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
//   			RxState2=2;
				
//   		}	
//   			}
			
//   	 if(USART2_RX_STA>(USART2_REC_LEN-1)){
//   		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
//   		USART2_RX_STA=0;	
//   	  }
//   	 else if(RxState2 ==2)  
//   	 {
//   		USART2_RX_STA=0;
//   		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
//   		RxState2=0;
//   		}		
//       }

// //openmv
//  	if(huart ==&huart3) 
//    { 
//  	 if(RxState3 ==0&&USART3_NewData==0x2C){				
//       USART3_RX_BUF[USART3_RX_STA]=USART3_NewData;
//       RxState3 = 1;			
//  			}

//  	 else if(RxState3 ==1&&USART3_NewData==0x12){
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       RxState3 = 2; 
//       }

//       else if(RxState3 ==2){
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       if(USART3_RX_BUF[USART3_RX_STA-1]== 0x5B){
				
// // 			theta=USART3_RX_BUF[USART3_RX_STA-5];
// // 			cv_x= USART3_RX_BUF[USART3_RX_STA-4];
// // 			cv_y= USART3_RX_BUF[USART3_RX_STA-3];
// // 			road_flag = USART3_RX_BUF[USART3_RX_STA-2];	
				
//  			RxState3=3; }
//       }

//       else if(RxState3==3){
//  			USART3_RX_STA=0;
//  			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
//  			RxState3=0;

     
//       }
//       if(USART3_RX_STA>(USART3_REC_LEN-1)){
//  		   USART3_RX_STA=0;
//  			 memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
//  			  RxState3=0;
//  			}



//    }

// 	if(huart ==&huart6){
// 		  uint8_t dat;
// 		  if (rx_cnt++ >= RXSTRSIZE - 1) // ???????
// 		  {
// 			  rx_cnt = 0;
// 			memset(rx_string, 0x00, sizeof(rx_string));
// 		}
// 		else
// 		{
// 			dat = rx_buff; // ???????????

// 			shujv[vofa_I++] = dat;

// 			if (dat == 0x0a)
// 			{

// 				for (vofa_i = 2, vofa_float = 0; vofa_i < vofa_I - 1; vofa_i++)
// 					vofa_float = 10 * vofa_float + (shujv[vofa_i] - '0');
// 				vofa_I = 0;

// 				if (shujv[1] == 0x3A)
// 				{
// 					switch (shujv[0])
// 					{
// 					// case 'S':my_dat.biaozhi =  shujv[2]  ; break;
// 					case 'P'://VOFA
// 						Kp_x_x= vofa_float; //keil
// 						break;
// 					case 'I':
// 						Ki_x_x = vofa_float;
// 						break;
// 					case 'D':
// 						Kd_x_x = vofa_float;
// 						break;
// 					case 'A':
// 						Kp_y_x = vofa_float;
// 						break;
// 					case 'B':
// 						Ki_y_x = vofa_float;
// 						break;
// 					case 'C':
// 						Kd_y_x = vofa_float;
// 						break;


					
// 					}
// 				}
// 			}
// 			memset(rx_string, 0x00, sizeof(rx_string)); 
// 			rx_cnt = 0;									
// 		}

//   }


	 
		
		

		
		
		
	// HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData_1,1); 
	HAL_UART_Receive_DMA(&huart2,(uint8_t *)&USART1_NewData_1,1);
	// HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART1_NewData_1,1); 
	// HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
	// HAL_UART_Receive_IT(&huart6, (uint8_t *)&rx_buff, 1); 

}



		


			
	


	

