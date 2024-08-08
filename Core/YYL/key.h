#ifndef _KEY_H_
#define _KEY_H_

#include "stdbool.h"

#include "main.h"
extern uint8_t KEY(void);
void key_button(void);

struct keys
{
	unsigned char judge_sta;
	bool key_sta;
	bool single_flag;
	bool long_flag;
	unsigned int key_time;
};

extern struct keys key[5];
#endif
