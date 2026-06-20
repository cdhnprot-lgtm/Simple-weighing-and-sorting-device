#ifndef Filter_H
#define Filter_H

#include "sys.h"

/*****************************高通、低通滤波*******************************/

typedef struct{
	float Alpha;
	double Pre_out;
	double Pre_in;
}Filter_t;

double Low_Pass_Filter(Filter_t * filter,double input);
double High_Pass_Filter(Filter_t * filter,double input);

/******************************滑动均值滤波********************************/

#define AVG_LEN 20

typedef struct{
	double Data[AVG_LEN];
	uint8_t index;
}AVG_Flt_t;

double Average_Filter(AVG_Flt_t * filter,double input);

/********************************中值滤波**********************************/

#define MEDIAN_LEN 25  //定义中值滤波的窗口长度

typedef struct
{
	double Data[MEDIAN_LEN];
	uint8_t index;
}MEDIAN_Flt_t;

double Mcdian_Filter(MEDIAN_Flt_t *filter,double input);

/********************************带通滤波**********************************/

void Bubble_Sort_Int(uint16_t *arr, uint16_t n, uint8_t ascending);
float Calculate_Mean_Int(uint16_t *arr, uint8_t length);

typedef struct {
    double last_valid;
    uint8_t initialized;
} Threshold_Filter_t;


float Threshold_Filter(Threshold_Filter_t *filter, uint16_t input, uint16_t threshold);

#endif




