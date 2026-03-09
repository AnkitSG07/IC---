

R_DELAY_T1			EQU			    0X00
R_DELAY_T2			EQU				0X01
R_DELAY_T3			EQU				0X02

R_ADC_H				EQU				0X03
R_ADC_L				EQU				0X04

ADC_TEMP 			EQU 			0x05  ;ADC初始化时中间变量，用户代码可以使用该地址
FLAG1				EQU 			0x06
	#define 	  F_CAL_POSITIVE	FLAG1,0  ;正向校准
	#define		  F_CAL_NEGATIVE 	FLAG1,1  ;反向校准
	#define 	  F_CAL_ONCE		FLAG1,2  ;首次数据判断确定方向
	#define		  F_FIND2_OK		FLAG1,3





