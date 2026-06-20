#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"
#include "stm32f10x.h"

//驱动电机io口
#define Motor_GPIO  GPIOA

#define Motor_pin1  GPIO_Pin_1			//高位
#define Motor_pin2  GPIO_Pin_2
#define Motor_pin3  GPIO_Pin_3
#define Motor_pin4  GPIO_Pin_4			//低位

void Motor_Init(void);
void F_Rotate(void);
void R_Rotate(void);
void F_Rotate_lap(void);
void R_Rotate_lap(void);

#endif

