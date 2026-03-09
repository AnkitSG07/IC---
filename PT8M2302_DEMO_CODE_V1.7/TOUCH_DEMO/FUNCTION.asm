;***************************************************************************************************  
;* Description:  按键扫描  
;***************************************************************************************************
KEY_SCAN:
		MOV			A,#0
		SE			KEY_STATE_H
		JMP			SEND_INT
		SE			KEY_STATE_L
		JMP			SEND_INT
		
		BCLR		PWM0EN
		JMP			SLEEP_DELAY
		
		SEND_INT:	
		BSET		PWM0EN
		JMP			TOUCH_KEY_RESET

;*****************************************************4S进入休眠  													
SLEEP_DELAY:
		BTSZ		F_GOTO_SLEEP
		RETI
		BTSZ		F_KEY_PRESS
		CLR			TOUCH_KEY_RESET_TIME_1
		BTSZ		F_KEY_PRESS
		CLR			TOUCH_KEY_RESET_TIME_2
		BSET		F_KEY_RELEASE
		BCLR		F_KEY_PRESS
		
		
		INCSZR		SLEEP_TIME_1								;(4*256)*4=4096ms		4S 进入休眠
		RETI
	    INCSZR		SLEEP_TIME_2 
	    BTSNZ		SLEEP_TIME_2,2 
	    RETI 
	    CLR			SLEEP_TIME_2 
		BSET		F_GOTO_SLEEP
		RETI		
;*****************************************************16S触摸获取基值  													
TOUCH_KEY_RESET:	
		BTSZ		F_KEY_RELEASE	
		CLR			SLEEP_TIME_1
		BTSZ		F_KEY_RELEASE
		CLR			SLEEP_TIME_2
		BSET		F_KEY_PRESS
		BCLR		F_KEY_RELEASE	
							
		INCSZR 		TOUCH_KEY_RESET_TIME_1  
		RETI  
		INCSZR		TOUCH_KEY_RESET_TIME_2     
		BTSNZ		TOUCH_KEY_RESET_TIME_2,4					;(256*4)*16=16384ms     16S进入超时处理  
		RETI  
		CLR			TOUCH_KEY_RESET_TIME_2  
		MOV			A,#OPTION_TOUCH_CHANNEL_SEL_L
		MOV			TH_KEY_EXPIRE_L,A
		MOV			A,#OPTION_TOUCH_CHANNEL_SEL_H
		MOV			TH_KEY_EXPIRE_H,A
		RETI														
;***************************************************************************************************  
;* Description:    睡眠 
;***************************************************************************************************  
SLEEP:  
		BTSNZ		F_GOTO_SLEEP
		RET
        BTSZ     	LP_AL
        JMP      	SLEEP_1
        BCLR     	LP_EN
		BCLR		F_GOTO_SLEEP
        RET
		SLEEP_1:
        BSET     	LP_EN
        BCLR     	CDCLDO
		BSET 		WDTSEL  //代码选项区应设为144ms
        STOP
		BSET     	CDCLDO
		BCLR 		WDTSEL
		RET	
		
    

				
;***************************************************************************************************
;* Description:  系统初始化
;***************************************************************************************************
SYSTEM_INIT:
		CALL 		CLEAR_RAM
		CALL		GPIO_INIT
		CALL		TIMER0_INIT
		CALL		PWM_INIT 	    
		CALL 		WDT_INIT
		CALL		SET_INIT_VALUE
		BSET		GIE  
		RET		
  
;***************************************************************************************************
;* Description:  系统初值
;***************************************************************************************************
SET_INIT_VALUE:

		RET	    
    
    
	    
        
    
    
    
    
    
    
    
    
    
