#include "head_files.h"




void Float_to_Byte(float f, unsigned char byte[])
{
	FloatLongType fl;
	fl.fdata = f;
	byte[0] = (unsigned char)fl.ldata;
	byte[1] = (unsigned char)(fl.ldata >> 8);
	byte[2] = (unsigned char)(fl.ldata >> 16);
	byte[3] = (unsigned char)(fl.ldata >> 24);
}

void Send_Data(UART_HandleTypeDef *huart, float f)
{
	unsigned char byte[4] = {0};

	Float_to_Byte(f, byte);
	HAL_UART_Transmit(huart, (uint8_t *)&byte[0], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[1], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[2], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[3], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
}

void Send_Tail(UART_HandleTypeDef *huart)
{
	unsigned char byte[4] = {0x00, 0x00, 0x80, 0x7f};

	HAL_UART_Transmit(huart, (uint8_t *)&byte[0], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[1], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[2], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[3], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
}

 //Add Send_Date







void vodka_JustFloat_send(UART_HandleTypeDef *huart)
{

	 
//	 Send_Data(huart, (float)v_x_ball);
//	 Send_Data(huart, (float)v_y_ball);
//	 Send_Data(huart, (float)x_pid_x_out);
//	 Send_Data(huart, (float)y_pid_x_out);
	 
	 Send_Data(huart, (float)Kp_x_x);
	 Send_Data(huart, (float)Ki_x_x);
	 Send_Data(huart, (float)Kd_x_x);
 	 Send_Data(huart, (float)Kp_y_x);
	 Send_Data(huart, (float)Ki_y_x);
	 Send_Data(huart, (float)Kd_y_x);

	


	Send_Tail(huart);
}

///**example**/
// while(1)
// {
// 	vodka_JustFloat_send(&huart1);
// }



// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//	
// // 	if(huart ==&huart1) //蓝牙
// //   { 
// // 	 if(RxState ==0){
// //       USART2_RX_BUF[USART2_RX_STA++]=USART2_NewData; 					
// //       USART2_RX_STA++; 
// //       RxState = 1;			
// // 	}
// // 	 else if(RxState ==1){
// //       USART2_RX_BUF[USART2_RX_STA++]=USART2_NewData; 
// // 	 	if(USART2_RX_STA >0||USART2_RX_BUF[USART2_RX_STA-1]== 0x12)
// // 		 {

// // 			target = USART2_RX_BUF[USART2_RX_STA-3]-48;			
// // 			//num2 = USART1_RX_BUF[USART1_RX_STA-4];
// // 			//	num3 = USART1_RX_BUF[USART1_RX_STA-5];	
//				
// // 			USART2_RX_STA=0;
// // 			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
// // 			RxState=2;
//				
// // 		}	
// // 			}
//			
// // 	 if(USART2_RX_STA>(USART2_REC_LEN-1)){
// // 		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
// // 		USART2_RX_STA=0;	
// // 	  }
// // 	 else if(RxState ==2)   //接收异常
// // 	 {
// // 		USART2_RX_STA=0;
// // 		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
// // 		RxState=0;
// // 		}		
// //     }

// 		

//     if(huart ==&huart2) //openmv
//    { 
// 	 if(RxState3 ==0&&USART3_NewData==0x2C){				
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       RxState3 = 1;			
// 			}

// 	 else if(RxState3 ==1&&USART3_NewData==0x12){
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       RxState3 = 2; 
//       }

//       else if(RxState3 ==2){
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       if(USART3_RX_BUF[USART3_RX_STA-1]== 0x5B){
//       		x_ball = USART3_RX_BUF[USART3_RX_STA-5];
// 			y_ball = USART3_RX_BUF[USART3_RX_STA-3];	
// 			RxState3=3; }
//       }

//       else if(RxState3==3){
// 			USART3_RX_STA=0;
// 			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
// 			RxState3=0;

//      
//       }
//       if(USART3_RX_STA>(USART3_REC_LEN-1)){
// 		   USART3_RX_STA=0;
// 			 memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
// 			  RxState3=0;
// 			}



//    }


//  	 
//   
//  	HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART3_NewData,1);
// 	// HAL_UART_Receive_IT(&huart3, (uint8_t *)&USART2_NewData, 1); 
// 	 HAL_UART_Receive_IT(&huart3, (uint8_t *)&rx_buff, 1);  
// 	// HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
// }
