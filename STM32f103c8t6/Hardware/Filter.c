#include "Filter.h"			//基础滤波函数
#include "math.h"


/*****************************高通、低通滤波*******************************/

double Low_Pass_Filter(Filter_t * filter,double input)
{
	double output = filter->Alpha * filter->Pre_out + (1 - filter->Alpha) * input;
	filter->Pre_out = output;
	return output;
}

double High_Pass_Filter(Filter_t* filter,double input)
{
	float output = filter->Alpha * (input - filter->Pre_in) + filter->Alpha * filter->Pre_out;
	filter->Pre_in = input;
	filter->Pre_out = output;
	return output;
}

/******************************滑动均值滤波********************************/

double Average_Filter(AVG_Flt_t * filter,double input)
{
	uint8_t i = 0;
	double sum = 0,avg = 0;
	
	filter->Data[filter->index++] = input;
	
	if(filter->index >= AVG_LEN)
	{
		filter->index = 0;
	}
	
	for(i=0;i<AVG_LEN;i++)
	{
		sum += filter->Data[i];
	}
	avg = sum / AVG_LEN;
	
	return avg;
}

/********************************中值滤波**********************************/

//比较函数，用于qsort排序
int compare(const void *a,const void *b)
{
	double da = *(const double *)a;
	double db = *(const double *)b;
	return (da > db) - (da < db);
}
double Mcdian_Filter(MEDIAN_Flt_t *filter,double input)
{
	uint8_t i = 0;
	double median = 0;
	
	//将新输入数据存入数组
	filter->Data[filter->index++] = input;
	
	//如果索引超出数组范围，则循环回数组开头
	if(filter->index >= MEDIAN_LEN)
	{
		filter->index = 0;
	}
	
	//创建一个临时数组用于排序
	double tempData[MEDIAN_LEN];
	for(i = 0;i < MEDIAN_LEN;i++)
	{
		tempData[i] = filter->Data[i];
	}
	
	//对临时数组进行排序
	qsort(tempData,MEDIAN_LEN,sizeof(double),compare);
	
	//取中值
	median = tempData[MEDIAN_LEN / 2];
	
	return median;
}

/********************************带通滤波**********************************/

/**
 * @brief 冒泡排序函数 - 整型数组
 * @param arr: 待排序的数组
 * @param n: 数组长度
 * @param ascending: 1为升序，0为降序
 */
void Bubble_Sort_Int(uint16_t *arr, uint16_t n, uint8_t ascending)
{
    uint16_t i, j;
    uint16_t temp;
    uint8_t swapped;
    
    for(i = 0; i < n - 1; i++) {
        swapped = 0;
        for(j = 0; j < n - i - 1; j++) {
            if((ascending && arr[j] > arr[j + 1]) || 
               (!ascending && arr[j] < arr[j + 1])) {
                // 交换元素
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // 如果没有交换发生，数组已经有序
        if(!swapped) break;
    }
}

float Calculate_Mean_Int(uint16_t *arr, uint8_t length)
{
    if(length == 0) return 0.0;
    
    uint16_t sum = 0;
    uint8_t i;
    
    for(i = 0; i < length; i++) {
        sum += arr[i];
    }
    
    return (float)sum / length;
}

/**
 * @brief 阈值滤波器 - 强势拒绝大突变
 * @param filter: 滤波器结构体
 * @param input: 新输入值
 * @param threshold: 突变阈值
 * @return 滤波后的值
 */

float Threshold_Filter(Threshold_Filter_t *filter, uint16_t input, uint16_t threshold)
{
    if(!filter->initialized) {
        filter->last_valid = input;
        filter->initialized = 1;
        return input;
    }
    
    double change = fabs(input - filter->last_valid);
    
    // 如果变化超过阈值，拒绝这个值
    if(change > threshold) {
        return filter->last_valid;  // 保持上一个有效值
    } else {
        filter->last_valid = input;
        return input;
    }
}

