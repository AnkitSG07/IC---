;***************************************************************************************************
;* Description:  系统初始化
;***************************************************************************************************
SYSTEM_INIT:
	CALL 		CLEAR_RAM
	CALL		GPIO_INIT
	CALL 		ADC_INIT 
	CALL 		ADC_CALIBRATION   ;ADC失调校准
	CALL 		ADC_CH_RSET
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
;**************************************************************************************************
; Function   :  GPIO_INIT
; Description:  GPIO初始化程序 
; Input      :  
; Output     :  
;**************************************************************************************************     
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
	
;************************************************************************************************** 
;* Description:  ADC初始化
;  ADC转换完成时间=采集时间+比较时间（14个ADC周期）=（ADCSPT[3:0]+1+14）*T=（7+1+14）*2us=44us
;**************************************************************************************************
ADC_INIT:
	MOV 	    A,#10000111B    ;ADC时钟选择8M/16=0.5M  
	MOV 		ADCON0,A 

	MOV 		A,#00000011B    ;选择内部基准电压2.048V做为参考电压	 
	MOV 		ADCON1,A  
	
	MOV 		A,#00100000B    ;ADC模块电路0.5mA      
	MOV 		ADCON2,A  
	
	MOV 		A,#00000000B    ;选用外部输入通道0（ADC0）
	MOV 		ADCON3,A  
	MOV 		A,#00000001B    ;AD0对应IO(P03)口作为ADC功能
	MOV 		ADCCH0,A  	
	
	BSET 		ADCEN			;使能ADC模块
	CALL		DELAY100US  	;ADC模块使能仅第一次需延时100US待模块稳定后再进行转换。
	RET
	
;**************************************************************************************************
;* Description:  ADC在失调校准后需恢复之前的配置
;**************************************************************************************************
ADC_CH_RSET:
	BCLR 		ADCVREF2
	BSET 		ADCVREF1
	BSET 		ADCVREF0       ;选择内部基准电压2.048V做为参考电压	 

	MOV 		A,#00000000B   ;选用外部输入通道0（ADC0）
	MOV 		ADCON3,A 
	RET
	
;**************************************************************************************************
;* Description:   ADC失调校准：校准量为1FH时，如果未找到1值 则找到的2值为目标值。若两者均为找到则校准量0为目标值
;**************************************************************************************************
ADC_CALIBRATION:
	;1、配置 ADC 时钟（ ADCCK ）和 采样时间周期（ADCSPT）；
	MOV 		A,#10000111B  ;0.5M@8M/16
	MOV 		ADCON0,A
	
	 ;2、配置 ADC 参考电压 ADCVREF 为内部基准； 
	BCLR 		ADCVREF2
	BSET 		ADCVREF1
	BSET 		ADCVREF0      ;011 ：选择内部基准电压2.048V做为参考电压	 
	
	;3、使能ADC (ADCEN = 1),设置输入通道为内部GND
	BSET 		ADCEN
	BSET  		ADCADDR2
	BSET  		ADCADDR1
	BCLR  		ADCADDR0   ;110选择内部特殊通道GND	
    
	;4、软件等待100us左右，即等待AD初始化稳定
	CALL		DELAY100US  
	
    ;5、启动ADC连续转换，此步骤移至"失调校准ADC单次转换处"
    ;BSET		ADCS
	
	;6、先将 ADCCALD=0  ADCCAL [3: 0]=1111
	MOV 		A,#00001111B 
	MOV			ADCON2,A 
	

	ADC_OFFSET_ADJUST2_LOOP:
    BSET        ADCCUR      ;ADCCUR=1 ADC模块电路为0.5mA
	BSET		ADCS	
	BTSNZ		ADCE		;查询CDC转换完成，完成时由硬件置0
	JMP 		$-1
	BCLR		ADCE
	BCLR		ADCS        ;必须关闭ADCE/ADCS
	NOP
	NOP
	
	MOV   		A,ADCOH
	BTSNZ  		Z
	JMP   		SET_ADCCAL
	MOV   		A,ADCOL

	SE 			#2
	JMP 		ADC_FIND_DATA1
	MOV 		A,ADCON2
	MOV 		ADC_TEMP,A
	BSET 		F_FIND2_OK
	
	ADC_FIND_DATA1:
	SE 			#1       
	JMP 		SET_ADCCAL
	RET      	 ;若找到1值则此时ADCON2值为目标校准量
	SET_ADCCAL: 
	MOV   		A,#00010000B
	AND   		A,ADCON2
	SE    		#00010000B
	JMP   		POSITIVE_ADJUST ;ADCON2[4]=0则正向校准
	JMP   		NEGATIVE_ADJUST ;ADCON2[4]=1则负向校准
	POSITIVE_ADJUST:
	MOV   		A,#00001111B ;取低4位校准量值
	AND   		A,ADCON2
	BTSZ  		Z
	BSET  		ADCCALD   ;校准量为0则负向校准	
	BTSNZ  		Z
	DECR  		ADCON2    ;校准量不为0继续递减
	JMP   		ADC_OFFSET_ADJUST2_LOOP
	NEGATIVE_ADJUST:
	MOV   		A,#00011111B ;取低5位校准量值
	AND  		A,ADCON2
	XOR   		A,#00011111B
	BTSNZ  		Z
	INCR  		ADCON2   ;校准量不为1FH继续递增
	BTSZ  		Z  
	JMP			CALIBRATION_DATA2      ;校准量为1FH时，如果未找到1值 则找到的2值为目标值。若两者均为找到则校准量0为目标值
	JMP   		ADC_OFFSET_ADJUST2_LOOP
	
	CALIBRATION_DATA2: 
    MOV         A,#00100000B    ;ADCCUR=1 ADC模块电路为0.5mA，校准量ADCCAL[3:0]=0为目标值
	BTSZ 		F_FIND2_OK
	MOV 		A,ADC_TEMP
	MOV 		ADCON2,A
	RET	

	
		
;**************************************************************************************************
;* Description:  ADC_SINGLE_PRO单次转换处理  
;**************************************************************************************************
ADC_SINGLE_PRO:
	BSET		ADCS
	BTSNZ		ADCE			;查询CDC转换完成，完成时由硬件置0
	JMP 		$-1
	NOP	
  	BCLR  		ADCE            ;先关闭ADCE/ADCS再读取ADCOX
	BCLR 		ADCS
  	NOP							;NOP延时必须保留
  
    MOV 		A,ADCOH  
    AND 		A,#0x0F
    MOV			R_ADC_H,A    	;高四位  
    MOV			A,ADCOL  
    MOV			R_ADC_L,A		;低八位  
	RET	    

;******************************************************************************  
;* Description:  ADC_CON_PRO连续转换处理  
;******************************************************************************
ADC_CON_PRO:
	BSET 		ADCEN
	BSET		GIE
	BSET		ADCIE
	CALL		DELAY100US
	BSET		ADCS	
	RET;  
    
    	
;**************************************************************************************************
;* Description:  ADC数据比较 
;	ADC0选择内部基准电压2.048V做为参考电压, ADC0输入电压 >= 1V,P00为高，反之，则P00为低 （1/2.048*4096=0x7D0）
;**************************************************************************************************
ADC_DATA_COMP:
	MOV			A,R_ADC_H
	SUB 		A,#0x07
	BTSNZ 		C 
	JMP			COMP_L
	BTSNZ		Z
	JMP 		COMP_H

	MOV 		A,R_ADC_L
	SUB 		A,#0xD0
	BTSNZ 		C
	JMP 		COMP_L
	
	COMP_H:
	BSET 		P00
	RET
	
	COMP_L:
	BCLR 		P00
	RET
	
    
;************************************************************************************************** 
;* Description:  DELAY100US
;**************************************************************************************************	
DELAY100US:  
	MOV 		A,#16		;
	MOV 		R_DELAY_T1,A 
D1L3: 
	MOV 		A,#4		;
	MOV 		R_DELAY_T2,A 
D1L2: 						;
	MOV 		A,#1 
	MOV 		R_DELAY_T3,A 	
D1L1:						
	DECSZR		R_DELAY_T3 
	JMP 		D1L1 		  ;最内层循环=3*指令周期=3*(1/(4M/2T))
	DECSZR		R_DELAY_T2 
	JMP 		D1L2 
	DECSZR		R_DELAY_T1
	JMP 		D1L3
	NOP 
	RET  	

		
    