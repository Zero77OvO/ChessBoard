#ifndef _DELAY_H_
#define _DELAY_H_
#include "head_files.h"
 
void delay_ms(uint32_t nms);
 
void delay_us(uint32_t nus);
 
void delaynus_tim(uint32_t nus); 

void delay_ms_tim(uint16_t nms);
#endif
