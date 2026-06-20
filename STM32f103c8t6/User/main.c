#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HX711.h"
#include "usart.h"						//调试可以用
#include "sys.h" 
#include "Key.h"
#include "Timer.h"
#include "motor.h"
#include "Filter.h"


MEDIAN_Flt_t med_filter;				//中值滤波

//uint8_t KeyNum;						//按键值

uint32_t correct = 0;
uint32_t sum = 0;
uint32_t Weight = 0,Last_Weight = 0,result = 0;
uint16_t real_weight = 0;

uint8_t flag[] = {0,0,0};
uint8_t count[] = {0,0,0};
uint8_t R_count = 0,F_count = 0;		//合格数  不合格数

uint8_t acceptance_line = 47;			//合格线，自定义，这里47g一下合格，47g以上不合格
uint8_t upper_limit = 200;				//称重上限可修改0-5kg

int main(void)
{
	/*延时100ms，观察现象*/
	Delay_ms(100);
	/*初始化*/
	OLED_Init();
	Init_HX711pin();
	Motor_Init();
	
	NVIC_Configuration(); 
	Timer_Init();
	
	Get_Maopi();				//称毛皮重量
	Delay_ms(400);
	Delay_ms(400);
	Get_Maopi();				//重新获取毛皮重量

	
	OLED_Update();
	
	OLED_ShowString(35, 0, "称重分拣", OLED_8X16);
	OLED_ShowString(0, 48, "合格:", OLED_8X16);
	OLED_ShowNum(40, 48, R_count, 2, OLED_8X16);//合格数量
	OLED_ShowString(58, 48, "不合格:", OLED_8X16);
	OLED_ShowNum(113, 48, F_count, 2, OLED_8X16);//不合格数量
	OLED_ShowString(35, 24, "称重:", OLED_8X16);
	OLED_ShowChar(100,24,'g',OLED_8X16);
	
	/*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
	OLED_Update();
	/*延时100ms，观察现象*/
	Delay_ms(100);
	for(uint8_t i = 0;i<10;i++){
		Get_Weight();
		sum += Weight_Shiwu;
	}
	correct = sum / 10;  //均值滤波：毛皮质量
	
	while (1)
	{
		Delay_ms(10);
		
		Get_Weight();				//重新获取重量
		if(Weight_Shiwu >= correct)
		{
			Weight = Weight_Shiwu - correct;
		}else{
			Weight = correct - Weight_Shiwu;
		}
		result = Mcdian_Filter(&med_filter,Weight);				//滤波防止大范围跳动
		real_weight = (uint16_t)(result*10/36);
		if(real_weight > upper_limit)real_weight = Last_Weight;	//限制质量小于upper_limit g
		
		OLED_ShowNum(75, 24, real_weight, 3, OLED_8X16);//合格数量
		OLED_Update();
		
		Delay_ms(10);
		
		if(flag[0]==2){									//合格
			flag[0] = 7;								//使flag[0]失效，这里的数字7随便给的，只要大于3即可，确保之触发一次
			R_count =R_count + 1;
			OLED_ShowNum(40, 48, R_count, 2, OLED_8X16);	//合格数量
			OLED_Update();								//oled更新
			F_Rotate_lap();								//电机顺时针转一圈
		}else if(flag[0]==3){							//不合格
			flag[0] = 7;
			F_count =F_count + 1;
			OLED_ShowNum(113, 48, F_count, 2, OLED_8X16);//不合格数量
			OLED_Update();								//oled更新
			R_Rotate_lap();								//电机顺时针转一圈
		}
		Last_Weight = real_weight; 						//记忆
		
		OLED_Update();									//oled更新
	}
}
/*为了确保每次放上砝码只会输出一次值，防止一直跳变*/
void Weight_Tick(void)
{
	if(real_weight <3){							//大于3g算做开始称重
		flag[0] = 0;
		for(uint8_t i = 1;i < 3;i ++){
			count[i] = 0;
			flag[i] = 0;
		}
	}else if(real_weight > 3 && real_weight < acceptance_line){
		flag[1] = 1;
		if(flag[0] == 0){
			flag[0] = 1;
		}
		count[1] ++;
	}else if(real_weight > acceptance_line && real_weight < upper_limit){
		flag[2] = 1;
		if(flag[0] == 0){
			flag[0] = 1;
		}
		count[2] ++;
	}
	for(uint8_t i = 2;i > 0;i --){		//反向加高大质量优先级，防止测量时大质量滤波使从小到大过程判断错误
		if(flag[i] && (count[i]==5) && (flag[0] == 1)){
			count[i] = 0;
			flag[i] = 0;
			flag[0] = i+1;				//一次测量，只触发一次
		}
	}
}

void TIM2_IRQHandler(void)				//定时中断测量，可以加入按键
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Weight_Tick();
//		Key_Tick();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

