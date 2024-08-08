#include "mpuiic.h"





/**
 ****************************************************************************************************
 * @file        mpu6050_iic.c
 * @version     V1.0
 * @date        2022-06-21

 *
 ****************************************************************************************************
 */



/**
 * @brief       IIC接口延时函数，用于控制IIC读写速度
 * @param       无
 * @retval      无
 */
static inline void mpu6050_iic_delay(void)
{
    delaynus_tim(2);
}

/**
 * @brief       产生IIC起始信号
 * @param       无
 * @retval      无
 */
void MPU_IIC_Start(void)
{
    MPU6050_IIC_SDA(1);
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
}

/**
 * @brief       产生IIC停止信号
 * @param       无
 * @retval      无
 */
void MPU_IIC_Stop(void)
{
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
}

/**
 * @brief       等待IIC应答信号
 * @param       无
 * @retval      0: 应答信号接收成功
 *              1: 应答信号接收失败
 */
uint8_t MPU_IIC_Wait_Ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;
    
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    
    while (MPU6050_IIC_READ_SDA())
    {
        waittime++;
        
        if (waittime > 250)
        {
            MPU_IIC_Stop();
            rack = 1;
            break;
        }
    }
    
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
    
    return rack;
}

/**
 * @brief       产生ACK应答信号
 * @param       无
 * @retval      无
 */
void MPU_IIC_Ack(void)
{
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
}

/**
 * @brief       不产生ACK应答信号
 * @param       无
 * @retval      无
 */
void MPU_IIC_NAck(void)
{
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
}

/**
 * @brief       IIC发送一个字节
 * @param       dat: 要发送的数据
 * @retval      无
 */
void MPU_IIC_Send_Byte(uint8_t dat)
{
    uint8_t t;
    
    for (t=0; t<8; t++)
    {
        MPU6050_IIC_SDA((dat & 0x80) >> 7);
        mpu6050_iic_delay();
        MPU6050_IIC_SCL(1);
        mpu6050_iic_delay();
        MPU6050_IIC_SCL(0);
        dat <<= 1;
    }
    MPU6050_IIC_SDA(1);
}

/**
 * @brief       IIC接收一个字节
 * @param       ack: ack=1时，发送ack; ack=0时，发送nack
 * @retval      接收到的数据
 */
uint8_t MPU_IIC_Read_Byte(uint8_t ack)
{
    uint8_t i;
    uint8_t dat = 0;
    
    for (i = 0; i < 8; i++ )
    {
        dat <<= 1;
        MPU6050_IIC_SCL(1);
        mpu6050_iic_delay();
        
        if (MPU6050_IIC_READ_SDA())
        {
            dat++;
        }
        
        MPU6050_IIC_SCL(0);
        mpu6050_iic_delay();
    }
    
    if (ack == 0)
    {
        MPU_IIC_NAck();
    }
    else
    {
        MPU_IIC_Ack();
    }

    return dat;
}

/**
 * @brief       初始化IIC接口
 * @param       无
 * @retval      无
 */
void MPU_IIC_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能SCL、SDA引脚GPIO的时钟 */
    MPU6050_IIC_SCL_GPIO_CLK_ENABLE();
    MPU6050_IIC_SDA_GPIO_CLK_ENABLE();
    
    /* 初始化SCL引脚 */
    gpio_init_struct.Pin    = MPU6050_IIC_SCL_GPIO_PIN;  /* SCL引脚 */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;          /* 推挽输出 */
    gpio_init_struct.Pull   = GPIO_PULLUP;                  /* 上拉 */
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;         /* 高速 */
    HAL_GPIO_Init(MPU6050_IIC_SCL_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化SDA引脚 */
    gpio_init_struct.Pin    = MPU6050_IIC_SDA_GPIO_PIN;  /* SDA引脚 */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_OD;          /* 开漏输出 */
    HAL_GPIO_Init(MPU6050_IIC_SDA_GPIO_PORT, &gpio_init_struct);
    
    MPU_IIC_Stop();
}


/*
 * @description: MPU IIC 延时2us函数
 * 	72为工作主频，2为时间 4为指令运行周期
 * @return 
 
 
 // 6 clk 7 sda

 void MPU_SDA_IN(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//先使能外设IO portc时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
 
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStructure.Pull= GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
   // __HAL_RCC_I2C2_CLK_ENABLE();
}
 
void MPU_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//先使能外设IO portc时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
 
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
   //	__HAL_RCC_I2C2_CLK_ENABLE();
} 

void MPU_IIC_Delay(void)
{  //delay_us(2);
	delaynus_tim(2);
	uint32_t Delay = 2 * 168/2;
	do
	{
		__NOP();
	} while (Delay--);
	
}

// 初始化IIC
void MPU_IIC_Init(void)
{
	;
}
// 产生IIC起始信号
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT(); // sda线输出
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); // START:when CLK is high,DATA change form high to low
	MPU_IIC_Delay();
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // 钳住I2C总线，准备发送或接收数据
}
// 产生IIC停止信号
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT(); // sda线输出
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); // STOP:when CLK is high DATA change form low to high
	MPU_IIC_Delay();
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET); // 发送I2C总线结束信号
	MPU_IIC_Delay();
	MPU_IIC_Delay();
}
// 等待应答信号到来
// 返回值：1，接收应答失败
//         0，接收应答成功
uint8_t MPU_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime = 0;
	MPU_SDA_IN(); // SDA设置为输入
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	while (MPU_READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // 时钟输出0
	return 0;
}
// 产生ACK应答
void MPU_IIC_Ack(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	MPU_SDA_OUT();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
}
// 不产生ACK应答
void MPU_IIC_NAck(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	MPU_SDA_OUT();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
}
// IIC发送一个字节
// 返回从机有无应答
// 1，有应答
// 0，无应答
void MPU_IIC_Send_Byte(uint8_t txd)
{
	uint8_t t;
	MPU_SDA_OUT();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // 拉低时钟开始数据传输
	for (t = 0; t < 8; t++)
	{
		if ((txd & 0x80) >> 7)
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
		txd <<= 1;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		MPU_IIC_Delay();
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
		MPU_IIC_Delay();
	}
}
// 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	MPU_SDA_IN(); // SDA设置为输入
	for (i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
		MPU_IIC_Delay();
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		receive <<= 1;
		if (MPU_READ_SDA)
			receive++;
		MPU_IIC_Delay();
	}
	if (!ack)
		MPU_IIC_NAck(); // 发送nACK
	else
		MPU_IIC_Ack(); // 发送ACK
	return receive;
}
*/

