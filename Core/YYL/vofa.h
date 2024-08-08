#ifndef _VOFA_H_
#define _VOFA_H_

#include "head_files.h"



typedef union
{
	float fdata;
	unsigned long ldata;
} FloatLongType;



void vodka_JustFloat_send(UART_HandleTypeDef *huart);
#endif
