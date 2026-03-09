;-------------------IO引脚定义-----------------------------------; 
;					    __________	
;	         TH5/P15 --|1.      16|-- P16/TH6/AD3		
;			 TH4/P14 --|2       15|-- P17/TH7/AD4		
;			 TH3/P13 --|3       14|-- P04/TH8/PWM3
;		 AD2/TH2/P12 --|4       13|-- P03/TH9/PWM4
;		 AD1/TH1/P11 --|5       12|-- VDD
;		 AD0/TH0/P10 --|6       11|-- P02/TH10/PWM2/INT1
;	   VREF/CMOD/P05 --|7       10|-- P01/TH11/PWM1/INT1
;		         VSS --|8________9|-- P00/PWM0/INT0		
;-----------------------------------------------------------------  


;-------------------RAM定义---------------------------------;
;默认RAM可用范围：0X00~0X3F
;未开滑条功能：   0x40~0x43可用
SLEEP_TIME_1			EQU				0X00						
SLEEP_TIME_2			EQU				0X01

TOUCH_KEY_RESET_TIME_1	EQU				0X00						;复用
TOUCH_KEY_RESET_TIME_2	EQU				0X01						;复用

		
R_FLAG1					EQU				0X02
		#DEFINE  F_GOTO_SLEEP		  R_FLAG1,5 	  
		#DEFINE  F_KEY_RELEASE	      R_FLAG1,6 			 
		#DEFINE  F_KEY_PRESS		  R_FLAG1,7 			  


EDATL_TEMP				EQU				0X03