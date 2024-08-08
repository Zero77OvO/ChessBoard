// #include "head_files.h"


// int overflow_L=0;
// int overflow_R=0;


// MOTOR motor;

// int motor_speed_L(void)

// {   motor.speed_L_last=motor.speed_L;


//     motor.speed_L = __HAL_TIM_GET_COUNTER(&htim3)+overflow_L*60000;
    
//     motor.speed_L_OUT =  motor.speed_L-motor.speed_L_last;
//     return motor.speed_L_OUT;
// }

// int motor_speed_R(void)

// {   motor.speed_R_last=motor.speed_R;


//     motor.speed_R = __HAL_TIM_GET_COUNTER(&htim1)+overflow_R*60000;

//     motor.speed_R_OUT = motor.speed_R-motor.speed_R_last;
//     return motor.speed_R_OUT;
// }

// void motor_set_L(int pwm)
// {
//     // 限幅
//        if (pwm > 8000)
//            pwm = 8000;
//     // 输出
//     if (pwm > 0)
//     {
//         __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm);


//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
//     }
//     else
//     {
//         __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, -pwm);

//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
//     }
// }

// void motor_set_R(int pwm)
// {
//     // 限幅
//        if (pwm > 8000)
//            pwm = 8000;
//     // 输出
//     if (pwm > 0)
//     {

//         __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
//     }
//     else
//     {

//         __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, -pwm);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
//     }
// }

// void motor_run()
// {
//     // stop
//     if (motor.flag_stop == 1)
//     {
//         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
//     }
//     // run
//     if (motor.flag_stop == 0)
//     {
//         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
//     }
// }
