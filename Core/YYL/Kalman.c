#include "Kalman.h"

/*************************************************************
** Function name:      MCU_Open_interrupt
** Descriptions:       卡尔曼滤波器 函数
** Input parameters:   *kfp    - 卡尔曼结构体参数
** Input parameters:   input   - 需要滤波的参数的测量值（即传感器的采集值）
** Output parameters:  卡尔曼滤波器输出值（最优值）
** Returned value:     卡尔曼滤波器输出值（最优值）
** Created by:         qkk
** Created date:       2024-01-15
*************************************************************/

float KalmanFilter(KFPType_Struct kfp, float input)
{
    //估算协方差方程：当前 估算协方差 = 上次更新 协方差 + 过程噪声协方差
    kfp->P = kfp->P + kfp->Q;
 
    //卡尔曼增益方程：当前 卡尔曼增益 = 当前 估算协方差 / （当前 估算协方差 + 测量噪声协方差）
    kfp->G = kfp->P / (kfp->P + kfp->R);
 
    //更新最优值方程：当前 最优值 = 当前 估算值 + 卡尔曼增益 * （当前 测量值 - 当前 估算值）
    kfp->Output = kfp->Output + kfp->G * (input - kfp->Output); //当前 估算值 = 上次 最优值
 
    //更新 协方差 = （1 - 卡尔曼增益） * 当前 估算协方差。
    kfp->P = (1 - kfp->G) * kfp->P;
 
     return kfp->Output;
}
