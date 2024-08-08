// #include "Delay.h"

// //延时函数：毫秒级别
// void delay_ms(uint32_t nms)
// {
// 	uint32_t tmp;
// 	while(nms--)
// 	{
// 		SysTick->LOAD = 168000000/8/1000;	//计数初值，延时1ms
// 		SysTick->VAL = 0;					//清空当前值
// 		SysTick->CTRL |= 0x1;				//开始计数
// 		do
// 		{
// 			tmp = SysTick->CTRL;			//获取CTRL状态
// 		}while((tmp&0x1) && !(0x1<<16));
 
// 		SysTick->VAL = 0;					//清空当前值
// 		SysTick->CTRL &= 0;					//关闭计数
// 	}
// }
 
// //延时函数：微秒级别
// void delay_us(uint32_t nus)
// {
// 	uint32_t tmp;
// 	while(nus--)
// 	{
// 		SysTick->LOAD = 168000000/8/1000000;	//计数初值，延时1us
// 		SysTick->VAL = 0;					//清空当前值
// 		SysTick->CTRL |= 0x1;				//开始计数
// 		do
// 		{
// 			tmp = SysTick->CTRL;			//获取CTRL状态
// 		}while((tmp&0x1) && !(0x1<<16));
 
// 		SysTick->VAL = 0;					//清空当前值
// 		SysTick->CTRL &= 0;					//关闭计数
// 	}
 
// }

// void delaynus_tim(uint32_t nus)
// {

//     uint16_t  differ = 0xffff-nus-5;
//     //设置定时器2的技术初始值
//   __HAL_TIM_SetCounter(&htim2,differ);
//   //开启定时器
//   HAL_TIM_Base_Start(&htim2);

//   while( differ<0xffff-5)
//     {
//         differ = __HAL_TIM_GetCounter(&htim2);
//     };
//  //关闭定时器
//   HAL_TIM_Base_Stop(&htim2);
// }
// /*
//     普通定时器实现ms延时，可直接使用HAL库函数HAL_delay（）
// */
// void delay_ms_tim(uint16_t nms)
// {
//     uint32_t i;
//     for(i=0;i<nms;i++) delaynus_tim(1000);
// }

