#include "head_files.h"

// uint8_t KEY(void)
// {
// 	uint8_t a=0;
// 	int temp=0;
// 	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==0)//按键判断                
// 			{
// 				HAL_Delay(20);     //延时消抖
// 				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==0)
// 					{
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						HAL_Delay(10);
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==0){}  //等待按键松开
// 						a=2;
// 					}
// 			}
			 
// 	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0)//按键判断            
// 			{
// 				HAL_Delay(20);
// 				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0)
// 					{
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						HAL_Delay(10);
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0){}
// 						a=3;
// 					}
// 			}

// 	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0)//按键判断             
// 			{
// 				HAL_Delay(20);
// 				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0)
// 					{
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						HAL_Delay(10);
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0){}
// 						a=4;
// 					}	
// 			}
			
// 	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==0)//按键判断            
// 			{
// 				HAL_Delay(20);
// 				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==0)
// 					{
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						HAL_Delay(10);
// 						// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 						while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==0){}
// 						a=5;
// 					}	
// 			}
// 			if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==0)//按键判断          WK_UP
// 			{
// 				HAL_Delay(20);
// 				// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 				HAL_Delay(10);
// 				// HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
// 				while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==0)
// 				{
// 					temp+=20;
// 					HAL_Delay(20);
// 					if(temp==2500)
// 					{
// 						HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_2);
// 						HAL_Delay(10);
// 						HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_2);
// 					}
// 				}
// 				if(temp>=5){a=1;temp=0;}
						
			
// 			}		
			
// 	return a;
// }
struct keys key[5] = {0};
// 1 push  2 right 3 left 4 down 5 up
void key_button(){
	
		key[0].key_sta = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
		key[1].key_sta = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
		key[2].key_sta = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
		key[3].key_sta = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
		key[4].key_sta = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);

	
		for (int i = 0; i < 5; i++)
		{
			switch (key[i].judge_sta)
			{
			case 0:
			{
				if (key[i].key_sta == 0)
				{
					key[i].judge_sta = 1;
					key[i].key_time = 0;
					
				}
			}
			break;

			case 1:
			{
				if (key[i].key_sta == 0)
				{
					key[i].judge_sta = 2;
				}
				else
					key[i].judge_sta = 0;
			}
			break;

			case 2:
			{
				if (key[i].key_sta == 1)
				{

					key[i].judge_sta = 0;
					if (key[i].key_time < 70)
					{
						key[i].single_flag = 1;
					}
				}
				else
				{
					key[i].key_time++;
					if (key[i].key_time > 70)
					{
						key[i].long_flag = 1;
					}
				}
			}
			break;
			}
		}

	}
