;*****************************************************
;公司名称 		: 湖南品腾电子科技有限公司
;文件名		    : TOUCH_DEMO
;作者     		: PTKJ
;创建时间 		: 2022-02-22 
;修改时间 		: 2025-11-20
;版本号 		    : V1.7

;功能描述：
		; TOUCH0 ~ TOUCH7  触摸输入	P00  触摸输出
		; P0.0口无触摸输出低电平，有触摸输出PWM（40K）
;*****************************************************
include ".\CORE\PT8M2302.INC"
include ".\lib\TOUCH_SET.INC"  
include ".\lib\TOUCH.INC" 
include FUNCTION.INC 
                                                                   
              
		ORG       	0x000   
		CALL	  	SYSTEM_INIT
		JMP       	MAIN  

        ORG     	0008H
        JMP    	 	LOW_INTERRUPT      ;低优先级
        ORG    	 	0018H
        JMP    	 	HIGH_INTERRUPT     ;高优先级        
;***************************************************************************************************
;* Description:  中断函数入口     
;***************************************************************************************************
LOW_INTERRUPT:
        ;添加低优先级中断处理代码
		BCLR 		DPAGE0
        BTSZ		THIF
		JMP			TOUCH_INT						;TOUCH中断框架不可省略
		BTSZ		T0IF
		JMP			T0_INT							;TIMER0中断
    	BTSZ		T1IF
		JMP			T1_INT							;TIMER1中断
    	RETI
    						
		T0_INT:
		BCLR		T0IF
		JMP		    KEY_SCAN                         ;4MS进入一次

		T1_INT:
		BCLR		T1IF
		RETI
			
		TOUCH_INT:   
		BCLR		THIF
		RETI

HIGH_INTERRUPT:		
		;添加高优先级中断处理代码
		BCLR 		DPAGE0
		
		RETI


;***************************************************************************************************
;* Description:  主程序
;***************************************************************************************************					       
MAIN: 
		CLRWDT
        CALL 		TOUCH							;获取TOUCH值
		CALL		SLEEP							;休眠
		JMP			MAIN
;***************************************************************************************************
;* Description:  包含文件
;***************************************************************************************************		
include ".\FUNCTION.asm"
include ".\CORE\CORE.asm"  
include "PT8M2302_TOUCH_V1.11_251119.asm"  		;请至官网下载最新的TOUCH库，并进行替换   
               
    END
 
 
 
