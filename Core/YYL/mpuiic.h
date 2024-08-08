#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "head_files.h"


/*
// IO方向设置
//#define MPU_SDA_IN()  {GPIOB->CRH&=0XFFFF0FF;GPIOB->CRH|=((uint32_t)8<<12);}
//#define MPU_SDA_OUT() {GPIOB->CRH&=0XFFFF0FF;GPIOB->CRH|=((uint32_t)3<<12);}

 void MPU_SDA_IN(void);
 void MPU_SDA_OUT(void);

// IO操作函数
// #define MPU_IIC_SCL PBout(10)                             // SCL
// #define MPU_IIC_SDA PBout(11)                             // SDA
#define MPU_READ_SDA HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) // 输入SDA
*/
// IIC所有操作函数





/* 引脚定义 */
#define MPU6050_IIC_SCL_GPIO_PORT            GPIOB
#define MPU6050_IIC_SCL_GPIO_PIN             GPIO_PIN_10
#define MPU6050_IIC_SCL_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define MPU6050_IIC_SDA_GPIO_PORT            GPIOB
#define MPU6050_IIC_SDA_GPIO_PIN             GPIO_PIN_11
#define MPU6050_IIC_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* IO操作 */
#define MPU6050_IIC_SCL(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_SDA(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_READ_SDA()               HAL_GPIO_ReadPin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN)

/* 操作函数 */
//void mpu6050_iic_start(void);                /* 产生IIC起始信号 */
//void mpu6050_iic_stop(void);                 /* 产生IIC停止信号 */
//uint8_t mpu6050_iic_wait_ack(void);          /* 等待IIC应答信号 */
//void mpu6050_iic_ack(void);                  /* 产生ACK应答信号 */
//void mpu6050_iic_nack(void);                 /* 不产生ACK应答信号 */
//void mpu6050_iic_send_byte(uint8_t dat);     /* IIC发送一个字节 */
//uint8_t mpu6050_iic_read_byte(uint8_t ack);  /* IIC接收一个字节 */
//void mpu6050_iic_init(void);                 /* 初始化IIC接口 */
																								
																								
//void MPU_IIC_Delay(void);                // MPU IIC延时函数
void MPU_IIC_Init(void);                 // 初始化IIC的IO口
void MPU_IIC_Start(void);                // 发送IIC开始信号
void MPU_IIC_Stop(void);                 // 发送IIC停止信号
void MPU_IIC_Send_Byte(uint8_t txd);          // IIC发送一个字节
uint8_t MPU_IIC_Read_Byte(unsigned char ack); // IIC读取一个字节
uint8_t MPU_IIC_Wait_Ack(void);               // IIC等待ACK信号
void MPU_IIC_Ack(void);                  // IIC发送ACK信号
void MPU_IIC_NAck(void);                 // IIC不发送ACK信号

void IMPU_IC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);


#endif
