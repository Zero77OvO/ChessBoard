#ifndef __MOTOR_H
#define __MOTOR_H



typedef struct
{
    int flag_stop;
    int speed_L;
    int speed_R;
    int speed_L_last;
    int speed_R_last;
    int speed_L_OUT;
    int speed_R_OUT;
    /* data */
}MOTOR;


extern MOTOR motor;
int motor_speed_L(void);
int motor_speed_R(void);

void motor_set_L(int pwm);
void motor_set_R(int pwm);
void motor_run(void);

void motor_set_L(int pwm);
void motor_set_R(int pwm);

extern int overflow_L;
extern int overflow_R;
#endif
