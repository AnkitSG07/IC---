;***************************************************************************************************
;* Description:  系统初始化
;***************************************************************************************************
SYSTEM_INIT:
	CALL 		CLEAR_RAM
	CALL		GPIO_INIT
	CALL 		TIMER1_INIT 
	BCLR		WDTEN  
    RET
        
;***************************************************************************************************
;* Description:  清RAM
;***************************************************************************************************
CLEAR_RAM: 
	CLR 		MPH0
    MOV       	A,#0x00
    MOV       	MPL0,A
    
CLEAR_RAM1:
    CLR       	IAR0
    INCR      	MPL0
    MOV       	A,MPL0
    SE 			#0xF0
    JMP 		CLEAR_RAM1
    RET   
    
;******************************************************************************
; Function   :  GPIO_Init
; Description:  GPIO初始化程序 
; Input      :  
; Output     :  
;******************************************************************************        
GPIO_INIT:     
	CLR			P0					;输出初始为0 	
	CLR			P0OD				;1为使能开漏
	MOV			A,#00000000B		;1为输入	 0为输出
	MOV			P0OE,A		
    MOV			A,#11111111B		;0为使能上拉  默认 1
	MOV			P0PH,A
	MOV			A,#00000000B		;1为使能下拉  默认 0	
	MOV			P0PD,A				
    MOV			A,#00000000B		;1为使能唤醒   
	MOV			P0WK,A			
	
    CLR			P1					;输出初始为0 
	CLR			P1OD				;1为使能开漏
	MOV			A,#00000000B		;1为输入	 0为输出
	MOV			P1OE,A		
    MOV			A,#11111111B		;0为使能上拉  默认 1
	MOV			P1PH,A
	MOV			A,#00000000B		;1为使能下拉  默认 0	
	MOV			P1PD,A				
    MOV			A,#00000000B		;1为使能唤醒   
	MOV			P1WK,A	    
	RET     
	
;***************************************************************************************************
;* Description: TIMER1_INIT初始化程序 
;***************************************************************************************************   
TIMER1_INIT: 
	;1、配置时钟源选择T1CKS:不分频；
    BCLR		T1FS2 
    BCLR		T1FS1
    BCLR		T1FS0   
    
    ;2、配置T1OVR，输出PWM频率 = 80000/(0X3FF-0x338+1) = 40k  
    MOV			A,#0x38 
    MOV			T1OVRL,A
    MOV 		A,#0x03
    MOV 		T1OVRH,A
    
    ;配置T1Dx，输出PWM占空比 = (0x39B-0x338+1)/（0x3FF-0x338+1）=1/2；
    MOV			A,#0x9B   
    MOV 		T1D0L,A
    MOV 		T1D1L,A
    MOV 		T1D2L,A
    MOV 		T1D3L,A
    MOV 		T1D4L,A

    MOV 		A,#0x03
    MOV 		T1D0H,A
    MOV 		T1D1H,A
    MOV 		T1D2H,A
    MOV 		T1D3H,A
    MOV			T1D4H,A
    
	;3、配置 PWMxS,先输出高电平，占空比为高电平宽度；
    MOV 		A,#00000000B
    MOV 		T1CON2,A
    
    ;4、使能 PWMxEN；
    BSET		PWM0EN
    BSET 		PWM1EN
    BSET 		PWM2EN        
    BSET 		PWM3EN   
	BSET 		PWM4EN  
   
    ;5、使能 Timer1；
    BSET		T1EN    
    ;只打开PWM   按以上配置即可 
                                                                          
    BSET		T1IE     ;20k     50us中断一次
    BSET		GIE
    ;IPEN默认为低 即禁止中断优先级
    ;当需开启T1中断时，也需要开启全局中断	
    
    RET  
       
  