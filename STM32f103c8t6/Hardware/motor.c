#include "motor.h"
#include "Delay.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Motor_pin1 | Motor_pin2 |Motor_pin3 |Motor_pin4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void F_Rotate(void)
{
	/*0x01*/
	Motor_GPIO->BRR = Motor_pin1;
	Motor_GPIO->BRR = Motor_pin2;
	Motor_GPIO->BRR = Motor_pin3;
	Motor_GPIO->BSRR = Motor_pin4;
	Delay_ms(2);
	/*0x02*/
	Motor_GPIO->BRR = Motor_pin1;
	Motor_GPIO->BRR = Motor_pin2;
	Motor_GPIO->BSRR = Motor_pin3;
	Motor_GPIO->BRR = Motor_pin4;
	Delay_ms(2);
	/*0x04*/
	Motor_GPIO->BRR = Motor_pin1;
	Motor_GPIO->BSRR = Motor_pin2;
	Motor_GPIO->BRR = Motor_pin3;
	Motor_GPIO->BRR = Motor_pin4;
	Delay_ms(2);
	/*0x08*/
	Motor_GPIO->BSRR = Motor_pin1;
	Motor_GPIO->BRR = Motor_pin2;
	Motor_GPIO->BRR = Motor_pin3;
	Motor_GPIO->BRR = Motor_pin4;
	Delay_ms(2);
}

void R_Rotate(void)
{
	/*0x08*/
	Motor_GPIO->BSRR = Motor_pin1;
	Motor_GPIO->BRR = Motor_pin2;
	Motor_GPIO->BRR = Motor_pin3;
	Motor_GPIO->BRR = Motor_pin4;
	Delay_ms(2);
	/*0x04*/
	Motor_GPIO->BRR = Motor_pin1;
	Motor_GPIO->BSRR = Motor_pin2;
	Motor_GPIO->BRR = Motor_pin3;
	Motor_GPIO->BRR = Motor_pin4;
	Delay_ms(2);
	/*0x02*/
	Motor_GPIO->BRR = Motor_pin1;
	Motor_GPIO->BRR = Motor_pin2;
	Motor_GPIO->BSRR = Motor_pin3;
	Motor_GPIO->BRR = Motor_pin4;
	Delay_ms(2);
	/*0x01*/
	Motor_GPIO->BRR = Motor_pin1;
	Motor_GPIO->BRR = Motor_pin2;
	Motor_GPIO->BRR = Motor_pin3;
	Motor_GPIO->BSRR = Motor_pin4;
	Delay_ms(2);
}

void F_Rotate_lap(void)
{
	for(uint16_t j = 0; j < 512;j++){
		F_Rotate();
	}
}

void R_Rotate_lap(void)
{
	for(uint16_t k = 0; k < 512;k++){
		R_Rotate();
	}
}

//unsigned char F_Rotation[4]={0x01,0x02,0x04,0x08};//正转表格

//for(uint8_t i=0;i<4;i++)      //4相
//{
//	P1=F_Rotation[i];  //输出对应的相 可以自行换成反转表格
//	Delay(500);        //改变这个参数可以调整电机转速
//}

