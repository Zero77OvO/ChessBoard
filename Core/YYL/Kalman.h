#ifndef KALMAN_h
#define KALMAN_h
//代码参考自
//https://blog.csdn.net/weixin_46672094/article/details/130970409?ops_request_misc=&request_id=&biz_id=102&utm_term=%E5%8D%A1%E5%B0%94%E6%9B%BC%E6%BB%A4%E6%B3%A2c%E8%AF%AD%E8%A8%80%E5%AE%9E%E7%8E%B0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-130970409.142^v99^pc_search_result_base4&spm=1018.2226.3001.4187


#include "stdint.h"

#include <stdio.h> //库头文件

 
 
//1. 结构体类型定义
 struct KFPTypeS
{
    float P; //估算协方差
    float G; //卡尔曼增益
    float Q; //过程噪声协方差,Q增大，动态响应变快，收敛稳定性变坏
    float R; //测量噪声协方差,R增大，动态响应变慢，收敛稳定性变好
    float Output; //卡尔曼滤波器输出 
}; //Kalman Filter parameter type Struct
typedef struct KFPTypeS KFPTypeS_Struct;
typedef KFPTypeS_Struct *KFPType_Struct;
 
////2.定义卡尔曼结构体参数并初始化
//KFPTypeS kfpVar = 
//{
//    0.020, //估算协方差. 初始化值为 0.02
//    0, //卡尔曼增益. 初始化值为 0
//    0.001, //过程噪声协方差,Q增大，动态响应变快，收敛稳定性变坏. 初始化值为 0.001
//    1.000, //测量噪声协方差,R增大，动态响应变慢，收敛稳定性变好. 初始化值为 1
//    0 //卡尔曼滤波器输出. 初始化值为 0
//};
 
float KalmanFilter(KFPType_Struct kfp, float input);




#endif /* KALMAN_h */


