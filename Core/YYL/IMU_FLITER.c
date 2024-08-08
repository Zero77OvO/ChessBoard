#include "head_files.h"

short aacx, aacy, aacz;    // 加速度计
short gyrox, gyroy, gyroz; // 角速度计


typedef struct Angles
{
    float pitch;
    float roll;
    float yaw;
} eulerianAngles_t;
float gx0, gy0, gz0;
float a_x, a_y, a_z, g_x, g_y, g_z = 0;
float AX, AY, AZ, GX, GY, GZ = 0;
float AX_old, AY_old, AZ_old = 0;
#define new_weight 0.65f
#define old_weight 0.35f
float GX_Zero = -62;
float GY_Zero = -32;
float GZ_Zero = -3;
void IMUFliter()
{
    int i;
    float acc[3] = {0}, gyro[3] = {0};

    for (i = 0; i < 3; i++)
    {
        GetImuMsg();
        acc[0] += aacx;
        acc[1] += aacy;
        acc[2] += aacz;
        gyro[0] += gyrox;
        gyro[1] += gyroy;
        gyro[2] += gyroz;
    }
    gx0 = gyro[0] / 3.0f; // 调试陀螺仪静止系数用
    gy0 = gyro[1] / 3.0f;
    gz0 = gyro[2] / 3.0f;

    AX = acc[0] / 3.0f;
    AY = acc[1] / 3.0f;
    AZ = acc[2] / 3.0f;
		
    GX = gx0 - GX_Zero; // 去零漂之后的陀螺仪采集值
    GY = gy0 - GY_Zero;
    GZ = gz0 - GZ_Zero;

    g_x = GX * 0.001063686f; // 常数等于3.14/180/16.5
    g_y = GY * 0.001063686f;
    g_z = GZ * 0.001063686f;
    a_x = AX * new_weight + AX_old * old_weight;
    a_y = AY * new_weight + AY_old * old_weight;
    a_z = AZ * new_weight + AZ_old * old_weight;

    AX_old = a_x;
    AY_old = a_y;
    AZ_old = a_z;
}
/****************************姿态解算融合***************************/
/* 姿态解算融合
输入参数gx，gy，gz分别对应三个轴的角速度，单位是弧度/秒
输入参数ax，ay，az分别对应三个轴的加速度数据，
由于加速度的噪声较大，在读取的时候该数据是采用低通滤波
*/
#define delta_T 0.01f       // 5ms计算一次//0.005f
float I_ex, I_ey, I_ez;      // 误差积分
eulerianAngles_t eulerAngle; // 欧拉角
float param_Kp = 8.0;        // 加速度计的收敛速率比例增益,太大跟随会近似加速度计抖动，太小无法跟随  //50
float param_Ki = 0.2;        // 陀螺仪收敛速率的积分增益 0.2
float q0 = 1;                // 初始四元数定义
float q1, q2, q3 = 0;
void IMU_AHRSupdate_noMagnetic(float gx, float gy, float gz, float ax, float ay, float az) // 四元数求取
{
    float halfT = 0.5f * delta_T;
    float vx, vy, vz; // 当前的机体坐标系上的重力单位向量
    float ex, ey, ez; // 四元数计算值与加速度计测量值的误差
    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    //        float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    //        float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;

    // 对加速度数据进行归一化 得到单位加速度
    // 加速度计测出来的重力向量是ax、ay、az
    float norm = invSqrt(ax * ax + ay * ay + az * az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

    // 这里的vx、vy、vz，其实就是用上一次姿态（四元数）换算出来的在当前的坐标系上的重力单位向量。
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    // 它们之间的误差向量，就是上次姿态和加速度计测出来的姿态之间的误差。
    ex = ay * vz - az * vy;
    ey = az * vx - ax * vz;
    ez = ax * vy - ay * vx;

    // 用叉乘误差来做PI修正陀螺零偏，
    // 通过调节 param_Kp，param_Ki 两个参数，可以控制加速度计修正陀螺仪积分姿态的速度。
    I_ex += delta_T * ex;
    I_ey += delta_T * ey;
    I_ez += delta_T * ez;
    gx = gx + param_Kp * ex + param_Ki * I_ex;
    gy = gy + param_Kp * ey + param_Ki * I_ey;
    gz = gz + param_Kp * ez + param_Ki * I_ez;

    /*到此为止，使用加速度计数据对陀螺仪数据的修正已经完成，这就是姿态解算中的深度融合*/
    /*下面就是四元数微分方程，使用修正后的陀螺仪数据对时间积分，得到当前姿态（四元数表示）。然后进行四元数的单位化处理。*/

    // 四元数微分方程，其中halfT为测量周期的1/2，gx gy gz为陀螺仪角速度，以下都是已知量，这里使用了一阶龙哥库塔求解四元数微分方程
    q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

    norm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 = q0 * norm;
    q1 = q1 * norm;
    q2 = q2 * norm;
    q3 = q3 * norm;
}
/****************************快速计算1/sqrt(x)的函数***************************/
float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

/****************************四元数获取欧拉角***************************/
float Trans[3] = {0,0,0};
void Angle_get(void)
{
    IMUFliter();
    IMU_AHRSupdate_noMagnetic(g_x, g_y, g_z, a_x, a_y, a_z); // 获取四元数

    // 根据四元数方向余弦阵和欧拉角的转换关系，把四元数转换成欧拉角
    eulerAngle.pitch = -asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;                                    // pitch   57.3=180/3.14
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3;      // roll
    eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 57.3; // yaw
    Trans[0] = eulerAngle.pitch;
    Trans[1] = eulerAngle.roll;
    Trans[2] = eulerAngle.yaw;
}
void GetImuMsg()
{
    MPU_Get_Accelerometer(&aacx, &aacy, &aacz); // 得到加速度
    MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  // 得到角速度
}

