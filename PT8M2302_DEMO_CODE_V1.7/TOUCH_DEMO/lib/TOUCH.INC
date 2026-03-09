;###################################################################################################
;    FileName:   TOUCH.inc
;    Author:
;    Company:    PT
;    Version:    V1.10
;
;    请勿修改此文件！！！！！！！！
;###################################################################################################
#ifndef TOUCH_INC
#define TOUCH_INC
    ;===================================================================================================
    ;调试输出参数配置: DEBUG_DATA_OUT, DEBUG_AVG_DATA_OUT, DEBUG_BASE_DATA_OUT 可任意组合
    ;    开启此功能时会在现有的触摸库RAM空间上增加四个RAM．注意RAM分配
    ;      UART_SEND_DATA, CHECK_SUM, UART_SEND_BIT_CNT, UART_DELAY_T1
    ;    DEBUG_DATA_OUT: 触摸转换数据
    ;    DEBUG_AVG_DATA_OUT: 触摸数据平均值
    ;    DEBUG_BASE_DATA_OUT: 触摸基值数据
    #define DEBUG_DATA_OUT                   0
    #define DEBUG_AVG_DATA_OUT               0
    #define DEBUG_BASE_DATA_OUT              0

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;触摸库包含UART调试代码使能;
    ;    使用自定义UART发送程序需要注意中断问题是否打断UART发送
    #define OPT_DBG_UART_CODE_IN_LIB         1
    ;UART TX输出引脚选择,　库程序不配置调试脚属性，
    ;需用户自动配置此引脚属性
    #define DEBUG_CLIB_UART_TX               P0,1
    ;UART调试Baud Rate参数配置, 此参数不能大于255; Default NOP0+NOP1=0
    ;  (BAUDRATE_DELAY * (3+NOP0+NOP1) + 12) * 指令时间
    ;    CPUCLK |  9600 | 19200 | 38400
    ;      4M   |  134  |  65   |  31
    ;      2M   |   64  |  30   |  13
    ;      1M   |   30  |  13   |   4
    #define DEBUG_CLIB_BAUDRATE_DELAY        31
    ;===================================================================================================
    ;更低BaudRate时需要使能以下参数
    ;Tx发送延时模块增加1条指令周期, 有效值0,1
    #ifndef OPT_DBG_CLIB_BAUDRATE_NOP0
    #define OPT_DBG_CLIB_BAUDRATE_NOP0       0
    #endif
    ;Tx发送延时模块增加1条指令周期, 有效值0,1
    #ifndef OPT_DBG_CLIB_BAUDRATE_NOP1
    #define OPT_DBG_CLIB_BAUDRATE_NOP1       0
    #endif
    ;===================================================================================================
    ;#define OPT_I2C_MASK_DBGOUT    ;if define than I2C_SEND_FLAG must be define: 1 mask dbg output, 0 normal
    ;===================================================================================================
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;水位检测调试输出
    ;#define DEBUG_WATER_DATA_OUT
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;滑条调试输出
    ;DIFF  DELTA  LOC   OUTPUT顺序
    ;  0     0     0     wheel output
    ;  1     0     0     DIFF
    ;  1     1     0     DIFF,DELTA
    ;  1     1     1     DIFF,DELTA,LOC
    ;  1     0     1     DIFF,LOC
    ;  0     1     0     DELTA
    ;  0     1     1     DELTA,LOC
    ;  0     0     1     LOC
    ;#define DEBUG_WHEEL_DIFF_OUT
    ;#define DEBUG_WHEEL_DELTA_OUT
    ;#define DEBUG_WHEEL_LOCATION_OUT
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;#define DEBUG_BASE_VALUE_OUT   ;lable(0x80) will be add for Base value output
    ;#define LP_DEBUG_DATA_OUT
    ;#define DEBUG_KEY_THR_NOISE_THR_OUT
    ;#define DEBUG_8DIFF_STORE_EN
    #define OPT_R_WATER_SDATA_ENABLE     0
    #define OPT_TH_BASE_VALUE_NO_UPDATE  0
    ;===================================================================================================
    ;滑条1 预研功能,暂未开放
    #define OPTION_TH_WHEEL_NUM1         0x00   ;滑条通道数(设置为0-1无滑条，2=3通道，3=4通道……, 滑条最小需要3个通道)
                                                ;如果起始通道+滑条通道数>TOUCH使能通道数，则滑条通道数被强制设置为：
                                                ;TOUCH通道数-起始通道数
    #define OPTION_WHEEL_START_POSITION1 0x00   ;滑条通道(零点位置)逻辑起始位置
                                                ;例-1:
                                                ;#define OPTION_WHEEL_START_POSITION  0x00
                                                ;OPTION_TOUCH_CHANNEL_SEL_L   00111111B    即TOUCH0(P1.0)为滑条起点
                                                ;例-2:
                                                ;#define OPTION_WHEEL_START_POSITION  0x01
                                                ;OPTION_TOUCH_CHANNEL_SEL_L   00111110B    即TOUCH2(P1.2)为滑条起点
    #define OPTION_WHEEL_RESOLUTION1     0xFF   ;滑条级数设置(0xFF = 共256级,有效值：16~255)
    #define OPTION_WHEEL_SWITCH1         0x01   ;1=设置为滑条(首尾相连)或圆环，0=为滑条(首尾不相连)。
    #define OPTION_WHEEL_THRESHOLD1      0x18   ;滑条阈值(值越小灵敏度越高)(有效值：0x10~0xF0)
    ;===================================================================================================
    ;disable AUTO_THRESHOLD and AUTO_SCAN_TIME, Set different debounce for ref channel
    ;#define OPTION_REF_CHECK
    ;===================================================================================================
    ;扫描时间自动调整功能,滑条功能使能时自动屏蔽此功能, 默认按键响应时间参数配置为100ms,
    ;按键进入与退出消抖次数会自动计算
    #define AUTO_SCAN_TIME
    ;===================================================================================================
    #if (OPTION_TH_WHEEL_NUM != 0)
        #define OPTION_SCAN_TIME         0x00   ;普通通模式扫描次数 0 = 1次扫描， 1 = 2次扫描……
    #else
        #define OPTION_SCAN_TIME         0x03   ;普通通模式扫描次数 0 = 1次扫描， 1 = 2次扫描……
    #endif
    #define OPTION_BS_SCAN_TIME          0x04   ;基值扫描次数
    ;--------------------------------------------------
    ;AUTO_SCAN_TIME active than below parameter will be replaced.
    #ifdef OPTION_REF_CHECK
        #define OPTION_KEY_IN_DEBONCE    0x04   ;按键进入消抖次数 0 = 1次， 1 = 2次　...
    #else
        #define OPTION_KEY_IN_DEBONCE    0x03   ;按键进入消抖次数 0 = 1次， 1 = 2次　...
    #endif
    #define OPTION_KEY_OUT_DEBONCE       0x00   ;按键退出消抖次数 1 = 1次， 2 = 2次　...
    ;--------------------------------------------------
    ;those parameter will not be replaced.
    #define OPTION_MAX_DEBOUNCE          0x04   ;最大值持续N7~N0次后状态跳转到TH_STATE_0重新获取基值  ;v1.6 0x02 to 0x04
    #define OPTION_PMIDDLE_UPDATA        0x64   ;中间值持续N7~N0次后基值减NOISE_THRESHOLD, 消抖次数大能保证慢速靠近时触摸能响应
    #define OPTION_NMIDDLE_UPDATA        0x08   ;中间值持续N7~N0次后基值加NOISE_THRESHOLD             ;V1.6 0x04 to 0x08
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #define OPTION_SLP_SCAN_TIME         0x00   ;低功耗扫描次数, 不能修改!!!
    ;===================================================================================================
    ;Tow Thread for touch channel. TH_THRESHOLD_TOW_SEL = 1 use new Threshold or use the threshold set in TOUCH_SET.inc
    ;#define TOW_THRESHOLD_FOR_ONE_CHANNEL
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;TOUCH0
    #define OPTION_CFG_CHANNEL_0_10       0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH1
    #define OPTION_CFG_CHANNEL_1_10       0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH2
    #define OPTION_CFG_CHANNEL_2_10       0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH3
    #define OPTION_CFG_CHANNEL_3_10       0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH4
    #define OPTION_CFG_CHANNEL_4_10       0x0330;0x0D50 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH5
    #define OPTION_CFG_CHANNEL_5_10       0x0330;0x0D44 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH6
    #define OPTION_CFG_CHANNEL_6_10       0x0F4F;0x0F4F ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH7
    #define OPTION_CFG_CHANNEL_7_10       0x061E;0x061E ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH8
    #define OPTION_CFG_CHANNEL_8_10       0x0E48;0x0E48 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH9
    #define OPTION_CFG_CHANNEL_9_10       0x0621;0x0621 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH10
    #define OPTION_CFG_CHANNEL_A_10       0x093E;0x093E ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;TOUCH11
    #define OPTION_CFG_CHANNEL_B_10       0x0D41;0x0D41 ;高8位：噪声阈值， 低8位：触摸阈值

    ;===================================================================================================
    ;RAM_TH_SIX_THRESHOLD_SEL,　只允许以下值，其它值会导致与预期结果不符
    ;    0x00: 默认阈值; 0x01: Group 1; 0x02: Group 2;
    ;    0x04: Group 3; 0x08: Group 4; 0x10: Group 5;
    #define OPT_SIX_THRESHOLD_FOR_ONE_CHANNEL   0
    #if  OPT_SIX_THRESHOLD_FOR_ONE_CHANNEL
        #ifdef AUTO_THRESHOLD
            #undefine AUTO_THRESHOLD
        #endif
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;Group 1 for Threshold
    #define OPTION_CFG_CHANNEL_0_1        0x0110;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_1_1        0x0110;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_2_1        0x0110;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_3_1        0x0110;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_4_1        0x0110;0x0D50 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_5_1        0x0110;0x0D44 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_6_1        0x011F;0x0F4F ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_7_1        0x011E;0x061E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_8_1        0x0118;0x0E48 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_9_1        0x0111;0x0621 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_A_1        0x011E;0x093E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_B_1        0x0111;0x0D41 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;Group 2 for Threshold
    #define OPTION_CFG_CHANNEL_0_2        0x0220;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_1_2        0x0220;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_2_2        0x0220;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_3_2        0x0220;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_4_2        0x0220;0x0D50 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_5_2        0x0220;0x0D44 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_6_2        0x022F;0x0F4F ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_7_2        0x022E;0x061E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_8_2        0x0228;0x0E48 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_9_2        0x0221;0x0621 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_A_2        0x022E;0x093E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_B_2        0x0221;0x0D41 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;Group 3 for Threshold
    #define OPTION_CFG_CHANNEL_0_3        0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_1_3        0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_2_3        0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_3_3        0x0330;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_4_3        0x0330;0x0D50 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_5_3        0x0330;0x0D44 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_6_3        0x033F;0x0F4F ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_7_3        0x033E;0x061E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_8_3        0x0338;0x0E48 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_9_3        0x0331;0x0621 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_A_3        0x033E;0x093E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_B_3        0x0331;0x0D41 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;Group 4 for Threshold
    #define OPTION_CFG_CHANNEL_0_4        0x0440;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_1_4        0x0440;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_2_4        0x0440;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_3_4        0x0440;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_4_4        0x0440;0x0D50 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_5_4        0x0440;0x0D44 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_6_4        0x044F;0x0F4F ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_7_4        0x044E;0x061E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_8_4        0x0448;0x0E48 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_9_4        0x0441;0x0621 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_A_4        0x044E;0x093E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_B_4        0x0441;0x0D41 ;高8位：噪声阈值， 低8位：触摸阈值
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;Group 5 for Threshold
    #define OPTION_CFG_CHANNEL_0_5        0x0550;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_1_5        0x0550;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_2_5        0x0550;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_3_5        0x0550;0x0650 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_4_5        0x0550;0x0D50 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_5_5        0x0550;0x0D44 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_6_5        0x055F;0x0F4F ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_7_5        0x055E;0x061E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_8_5        0x0558;0x0E48 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_9_5        0x0551;0x0621 ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_A_5        0x055E;0x093E ;高8位：噪声阈值， 低8位：触摸阈值
    #define OPTION_CFG_CHANNEL_B_5        0x0551;0x0D41 ;高8位：噪声阈值， 低8位：触摸阈值
    ;===================================================================================================
    ;开启TOUCH_STATE_TOUCH_AGAIN功能后此参数(OPTION_WIND_ALG)支持此功能，Total channel <　8
    ;   二次触摸算法：同时支持标准触摸退出与二次触摸退出；不开启则仅支持二次退出，不支持标准触摸退出
    ;   注意：同时开启TOUCH_STATE_TOUCH_AGAIN,　OPTION_WIND_ALG　且有效触摸通道大于8个，会导致内存溢出．
    ;#define OPTION_WIND_ALG
    #define OPTION_WIND_BASE_UP_DB    0x04
    #define OPTION_WIND_OUT_DB        0x08
    ;===================================================================================================
    ;OPT_PANEL_COVER_CH 参数与此相关
    ;#define OPT_PANEL_COVER_PWRON
    #ifdef OPT_PANEL_COVER_PWRON
        #define  OPT_PANEL_COVER_DB       0x80
    #endif
    ;===================================================================================================
    ;滑条配置参数
    ;#define OPTION_WHEEL_LOC_BACKWARD          ;backward the wheel location
    ;#define OPTION_WHEEL_LOC_BACKWARD1         ;backward the wheel location
    ;--------------------------------------------------
    #define OPTION_WHEEL_DIFF_DEC_NOICE         ;dec noice for all channel
    #define OPTION_DIRECTION_DEBOUNCE_EN
    #define OPTION_WHEEL_WHINDOWS        0x08
    #define OPTION_WHEEL_IN_DEBOUNCE     0x08
    #define OPTION_WHEEL_SETP_DEBOUNCE   0x08
    #define OPTION_WHEEL_DIR_DEBOUNCE    0x06
    #define OPTION_WHEEL_RELEASE_NOISE   0x05
    ;屏蔽滑条通道按键有效超长按键检测功能
    ;#define OPTION_WHEEL_LONGKEY_MASK
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;滑条阈值
    ;滑条0有效(进入)阈值
    #define OPTION_WHEEL_FIRST_THRESHOLD_H ((OPTION_WHEEL_THRESHOLD)/256)
    #define OPTION_WHEEL_FIRST_THRESHOLD_L ((OPTION_WHEEL_THRESHOLD)%256)
    ;滑条0有效(继续滑动)阈值
    #define OPTION_WHEEL_THRESHOLD_H       (OPTION_WHEEL_THRESHOLD/256)
    #define OPTION_WHEEL_THRESHOLD_L       (OPTION_WHEEL_THRESHOLD%256)
    ;滑条0两端通道增加阈值(首尾不相联滑条)
    #define OPTION_SLIDER_BOTHENDS_THRESHOLD (0)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;滑条1有效(进入)阈值
    #define OPTION_WHEEL_FIRST_THRESHOLD_H1 ((OPTION_WHEEL_THRESHOLD1)/256)
    #define OPTION_WHEEL_FIRST_THRESHOLD_L1 ((OPTION_WHEEL_THRESHOLD1)%256)
    ;滑条1有效(继续滑动)阈值
    #define OPTION_WHEEL_THRESHOLD_H1       (OPTION_WHEEL_THRESHOLD1/256)
    #define OPTION_WHEEL_THRESHOLD_L1       (OPTION_WHEEL_THRESHOLD1%256)
    ;滑条1两端通道增加阈值(首尾不相联滑条)
    #define OPTION_SLIDER_BOTHENDS_THRESHOLD1 (0)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;#define OPT_WHEEL_RELEASE_CHECK
    #ifdef OPT_WHEEL_RELEASE_CHECK
        #define  OPT_WHEEL_RELEASE_THRESHOLD   0x80
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;Wheel Revise function.
    ;#define OPT_WHEEL_REVISE_FUNCTION
    #ifdef OPT_WHEEL_REVISE_FUNCTION
        ;100: 实际乘1; 90:实际乘0.9; 63:实际乘0.64; 
        #define  OPT_WHEEL_REVISE_CH0    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH1    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH2    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH3    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH4    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH5    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH6    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH7    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH8    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CH9    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CHA    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CHB    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CHC    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CHD    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CHE    100    ;有效值<=100
        #define  OPT_WHEEL_REVISE_CHF    100    ;有效值<=100
        
        #define  OPT_WHEEL_RCH0    (OPT_WHEEL_REVISE_CH0 * 255 / 100)
        #define  OPT_WHEEL_RCH1    (OPT_WHEEL_REVISE_CH1 * 255 / 100)
        #define  OPT_WHEEL_RCH2    (OPT_WHEEL_REVISE_CH2 * 255 / 100)
        #define  OPT_WHEEL_RCH3    (OPT_WHEEL_REVISE_CH3 * 255 / 100)
        #define  OPT_WHEEL_RCH4    (OPT_WHEEL_REVISE_CH4 * 255 / 100)
        #define  OPT_WHEEL_RCH5    (OPT_WHEEL_REVISE_CH5 * 255 / 100)
        #define  OPT_WHEEL_RCH6    (OPT_WHEEL_REVISE_CH6 * 255 / 100)
        #define  OPT_WHEEL_RCH7    (OPT_WHEEL_REVISE_CH7 * 255 / 100)
        #define  OPT_WHEEL_RCH8    (OPT_WHEEL_REVISE_CH8 * 255 / 100)
        #define  OPT_WHEEL_RCH9    (OPT_WHEEL_REVISE_CH9 * 255 / 100)
        #define  OPT_WHEEL_RCHA    (OPT_WHEEL_REVISE_CHA * 255 / 100)
        #define  OPT_WHEEL_RCHB    (OPT_WHEEL_REVISE_CHB * 255 / 100)
        #define  OPT_WHEEL_RCHC    (OPT_WHEEL_REVISE_CHC * 255 / 100)
        #define  OPT_WHEEL_RCHD    (OPT_WHEEL_REVISE_CHD * 255 / 100)
        #define  OPT_WHEEL_RCHE    (OPT_WHEEL_REVISE_CHE * 255 / 100)
        #define  OPT_WHEEL_RCHF    (OPT_WHEEL_REVISE_CHF * 255 / 100) 
        ;;Diff = Value * OPT_WHEEL_RCHx / 255
        ;#define  OPT_WHEEL_RCH0    255;
        ;#define  OPT_WHEEL_RCH1    255;
        ;#define  OPT_WHEEL_RCH2    255;
        ;#define  OPT_WHEEL_RCH3    255;
        ;#define  OPT_WHEEL_RCH4    255;
        ;#define  OPT_WHEEL_RCH5    255;
        ;#define  OPT_WHEEL_RCH6    255;
        ;#define  OPT_WHEEL_RCH7    255;
        ;#define  OPT_WHEEL_RCH8    255;
        ;#define  OPT_WHEEL_RCH9    255;
        ;#define  OPT_WHEEL_RCHA    255;
        ;#define  OPT_WHEEL_RCHB    255;
        ;#define  OPT_WHEEL_RCHC    255;
        ;#define  OPT_WHEEL_RCHD    255;
        ;#define  OPT_WHEEL_RCHE    255;
        ;#define  OPT_WHEEL_RCHF    255;
    #endif
    ;===================================================================================================
    ;充电时间配置
    ; 4.7 nf =  10us     |     10 nf =  20us
    ;  15 nf =  30us     |     22 nf =  41us
    ;  33 nf =  64us     |    100 nf = 200us
    ; 200 nf = 400us
    ;#define OPTION_CMOD_CHARGE_CNT       0x30
    ;CMOD预充电时间(1=1*N  FF=255*N  N@8M 2T =1.5us,N@8M 4T =3.0us) 0x42=100us CMOD电容最大50nf
    ;#define OPTION_CMOD_CHARGE_CNT       0x42
    ;CMOD预充电时间(1=1*N  FF=255*N  N@8M 2T =1.5us,N@8M 4T =3.0us) 0x50=120us CMOD电容最大60nf
    ;#define OPTION_CMOD_CHARGE_CNT       0x50
    ;CMOD预充电时间(1=1*N  FF=255*N  N@8M 2T =1.5us,N@8M 4T =3.0us) 0x86=201us CMOD电容最大100nf
    ;#define OPTION_CMOD_CHARGE_CNT       0x80
    ;CMOD预充电时间(1=1*N  FF=255*N  N@8M 2T =1.5us,N@8M 4T =3.0us) 0xFF=382us CMOD电容最大200nf
    ;#define OPTION_CMOD_CHARGE_CNT       0xFF
    #define OPTION_CMOD_CHARGE_CNT       0x60
    ;===================================================================================================
    ;IRC16M should be define for 2305
    ;#define IRC16M
    #ifdef  IRC16M
        ;===================================================================================================
        ; OPTION_CDC_THCKS  THCKS     @SYSCLK16M |   OPTION_CDC_THCKS  THCKS       @SYSCLK16M
        ;   0x00:           SYSCLK/4  4M        |       0x04:         SYSCLK/16     1M
        ;   0x01:           SYSCLK/4  4M        |       0x05:         SYSCLK/32   500K
        ;   0x02:           SYSCLK/4  4M        |       0x06:         SYSCLK/64   250K
        ;   0x03:           SYSCLK/8  2M        |       0x07:         SYSCLK/128  125K
        ;   说明：CDC时钟最快为4MHz, THCKS需配合SYSCLK的频率大小进行选择。
        #define OPTION_CDC_THCKS             0x02; ;4M @SYSCLK16M
    #else
        ;===================================================================================================
        ; OPTION_CDC_THCKS  THCKS     @SYSCLK8M |   OPTION_CDC_THCKS  THCKS       @SYSCLK8M
        ;   0x00:           SYSCLK/2  4M        |       0x04:         SYSCLK/16   500k
        ;   0x01:           SYSCLK/2  4M        |       0x05:         SYSCLK/32   250K
        ;   0x02:           SYSCLK/4  2M        |       0x06:         SYSCLK/64   125K
        ;   0x03:           SYSCLK/8  1M        |       0x07:         SYSCLK/128 62.6K
        ;   说明：CDC时钟最快为4MHz, THCKS需配合SYSCLK的频率大小进行选择。
        ;#define OPTION_CDC_THCKS             0x01; ;4M @SYSCLK8M
        #define OPTION_CDC_THCKS             0x01
    #endif
    ;===================================================================================================
    ;   0x00       1/6VCHarge
    ;   0x01       2/6VCHarge
    ;   0x02       3/6VCHarge
    ;   0x03       4/6VCHarge
    #define OPTION_CDCVREF    0x02
    ;un-used
    #define OPTION_CDCCMP     0x03
    ;===================================================================================================
    ;===================================================================================================
    ;触摸复用LED时使用
    ;#define OPT_TH_LED_FUNCTION
    ;===================================================================================================
    ;#define OPT_TH_REF_NEW_THR_EN
    #define OPT_TH_REF_NEW_THR_VALUE     32
    ;===================================================================================================
    ;Ref channel active than reset all channels
    #define OPTION_REFCH_ACITVE_RESET    1
    ;===================================================================================================
    ;un-used option---------------
    ;低功耗唤醒通道设置
    ;1:有效  0：无效    若所有通道全设为0，则所有使能通道均能唤醒
    #define OPTION_LP_CHANNEL_SEL_L      00000000B
    #define OPTION_LP_CHANNEL_SEL_H      00000000B
    ;===================================================================================================
    ;un-used option---------------
    ;1, open all touch channels
    ;2, open wheel function
    ;#define DEBUG_WHEEL_TEST_FUNCTION  ;for software setting wheel option
    ;V1.8 power on speed up base update; if low power mode enable than enable this function.
    ;#define  OPT_PWR_ON_SPEED_UP_BASE
    #define  OPT_PWR_ON_PMIDDLE_UP_DB     0x04
    ;===================================================================================================
    ;un-used option---------------
    ;#define OPT_TH_SCAN_MAX_MIN_CHECK
    ;#define OPT_TH_MAX_MIN_DIFF             0x80
    #if (OPTION_SCAN_TIME < 3)
        #ifdef OPT_TH_SCAN_MAX_MIN_CHECK
            #undefine OPT_TH_SCAN_MAX_MIN_CHECK
        #endif
    #endif
    ;===================================================================================================
    ;un-used option---------------
    ;P2303   12ch, un-used
    ;P2302   13ch
    ;#define P101C
    ;===================================================================================================
    ;un-used option---------------
    #define OPTION_OUT_MODE              0x00   ;单/多键模式选择 (0:允许多键 1:多键抑制)
    ;===========================================================================================================
    ;;
    #ifdef OPTION_TOUCH_EMC_OPTIMIZE
    #define SYS_CDC_THCKS                (0x07&(OPTION_CDC_THCKS + 1))*2
    #else
    #define SYS_CDC_THCKS                (0x07&OPTION_CDC_THCKS)*2
    #endif
    #define CDC_THCKS    ((SYS_CDC_THCKS)&0x0E)
    #define CDC_THCON    (0x80+((SYS_CDC_THCKS)&0x0E))
    #define CDC_LP_THCON (0x80+((SYS_CDC_THCKS+0x02)&0x0E))
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #ifdef OPT_CS_ENABLE
        #undefine CDC_THCKS
        #undefine CDC_THCON
        #undefine CDC_LP_THCON
        #define CDC_THCKS    ((SYS_CDC_THCKS)&0x0E)
        #define CDC_THCON    (0x00+((SYS_CDC_THCKS)&0x0E))
        #define CDC_LP_THCON (0x00+((SYS_CDC_THCKS+0x02)&0x0E))
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #define OPTION_THCON1     ( OPTION_CDCVREF + ( OPTION_CDCCMP << 4 ) )
    ;===================================================================================================
    ;if define OPTION_REF_CHECK than disable AUTO_THRESHOLD
    #ifdef  OPTION_REF_CHECK
        #ifdef AUTO_THRESHOLD
            #undefine AUTO_THRESHOLD
        #endif
    #endif
    #define OPTION_REF_IN_DEBOUNCE_TIME    0x02
    #define OPTION_REF_OUT_DEBOUNCE_TIME   0x02
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #ifdef AUTO_THRESHOLD
        ;自补偿参考通道触摸阈值等级，有效值(5~7); 此项使能，阈值定义则无效
        ; 5=2^5=32   参考通道的触摸阈值为32
        ; 6=2^6=64   参考通道的触摸阈值为64
        ; 7=2^7=128  参考通道的触摸阈值为128
        #ifndef OPTION_TOUCH_REF_GRADE
        #define OPTION_TOUCH_REF_GRADE   7      ;如果值>7或<5 则参数通道的值强制设置为64
        #endif
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;if define OPTION_REF_CHECK than force enable Reference channel and check REF Channel Threshold
    #ifdef OPTION_REF_CHECK
        #undefine OPTION_CHANNEL_SEL_H
        #define OPTION_CHANNEL_SEL_H     (OPTION_TOUCH_CHANNEL_SEL_H | 00010000B)
    #endif
    #ifndef OPTION_CFG_CHANNEL_12_0
        #define OPTION_CFG_CHANNEL_C_0  0x0620
    #else
        #define OPTION_CFG_CHANNEL_C_0  OPTION_CFG_CHANNEL_12_0
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #ifdef  TOW_THRESHOLD_FOR_ONE_CHANNEL
        #ifdef  AUTO_THRESHOLD
            #undefine AUTO_THRESHOLD
        #endif
    #endif
    ;===================================================================================================
    ;un-used
    #define OPTION_TOUCH_REF_CH_SEL_L    00000000B
    #define OPTION_TOUCH_REF_CH_SEL_H    00000000B
    ;===================================================================================================
    ;水位检测 -- 暂未开放
    #define  OPTION_TH_WATER_NUM            0   ;水位检测通道数(设置为0无水位，1=1通道，2=2通道, ……)
    #define  OPTION_WATER_START_POSITION    0   ;水位通道逻辑起始位置
                                                ;例-1:
                                                ;#define OPTION_WATER_START_POSITION  0x00
                                                ;OPTION_TOUCH_CHANNEL_SEL_L   00111111B    即TOUCH0(P1.0)为水位起点
                                                ;例-2:
                                                ;#define OPTION_WATER_START_POSITION  0x01
                                                ;OPTION_TOUCH_CHANNEL_SEL_L   00111110B    即TOUCH2(P1.2)为水位起点
    #define  OPTION_WATER_DEBOUNCE_NU       0x10;水位检测消抖次数; 值越小水位响应越快，值越大水位响应越慢
    ;注意：以下检测值非通道计数值，需要通过辅助工具体获取！！！！！！
    ;;;;有水门限值
    #define  OPTION_WATER_CH0            700
    #define  OPTION_WATER_CH1            700
    #define  OPTION_WATER_CH2            700
    #define  OPTION_WATER_CH3            700
    #define  OPTION_WATER_CH4            700
    #define  OPTION_WATER_CH5            700
    #define  OPTION_WATER_CH6            700
    #define  OPTION_WATER_CH7            700
    #define  OPTION_WATER_CH8            700
    #define  OPTION_WATER_CH9            700
    #define  OPTION_WATER_CH10           700
    #define  OPTION_WATER_CH11           700
    ;;;;无水门限值
    #define  OPTION_NOWATER_CH0          300
    #define  OPTION_NOWATER_CH1          300
    #define  OPTION_NOWATER_CH2          300
    #define  OPTION_NOWATER_CH3          300
    #define  OPTION_NOWATER_CH4          300
    #define  OPTION_NOWATER_CH5          300
    #define  OPTION_NOWATER_CH6          300
    #define  OPTION_NOWATER_CH7          300
    #define  OPTION_NOWATER_CH8          300
    #define  OPTION_NOWATER_CH9          300
    #define  OPTION_NOWATER_CH10         300
    #define  OPTION_NOWATER_CH11         300
    ;===================================================================================================
    ;ref ch config
    #ifdef P101C
        #define OPTION_CHANNEL_SEL_L   OPTION_TOUCH_CHANNEL_SEL_L
        #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H & 00001111B)
        ;#ifdef AUTO_THRESHOLD
        ;    #define OPTION_TOUCH_REF_CH_SEL_L    00000000B
        ;    #define OPTION_TOUCH_REF_CH_SEL_H    00000000B
        ;#endif
    #else
        #define OPTION_CHANNEL_SEL_L   OPTION_TOUCH_CHANNEL_SEL_L
        #ifdef AUTO_THRESHOLD
            #if (OPTION_TOUCH_REF_GRADE == 7)
                #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H | 00010000B)
                #undefine OPTION_TOUCH_REF_CH_SEL_L
                #undefine OPTION_TOUCH_REF_CH_SEL_H
                #define OPTION_TOUCH_REF_CH_SEL_L    00000000B
                #define OPTION_TOUCH_REF_CH_SEL_H    00010000B
            #else
                #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H & 00001111B)
            #endif
        #else
            #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H & 00001111B)
        #endif
        #ifdef OPTION_TH_WATER_NUM
            #if (OPTION_TH_WATER_NUM > 0)
                #undefine OPTION_CHANNEL_SEL_H
                #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H | 00010000B)
            #endif
        #endif
        ;#ifdef OPTION_TH_WATER_EN
        ;    #if(OPTION_TH_WATER_EN != 0)
        ;        #undefine OPTION_CHANNEL_SEL_H
        ;        #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H | 00010000B)
        ;    #endif
        ;#endif
        ;#ifdef DEBUG_DATA_OUT
        #if DEBUG_DATA_OUT
            #undefine    OPTION_CHANNEL_SEL_H
            #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H & 00001111B)
            #ifdef DEBUG_WATER_DATA_OUT
                #undefine    DEBUG_WATER_DATA_OUT
            #endif
        #endif
        ;#ifdef DEBUG_BASE_DATA_OUT
        #if (DEBUG_BASE_DATA_OUT)
            #undefine    OPTION_CHANNEL_SEL_H
            #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H & 00001111B)
            #ifdef DEBUG_WATER_DATA_OUT
                #undefine    DEBUG_WATER_DATA_OUT
            #endif
        #endif
        #ifdef DEBUG_KEY_THR_NOISE_THR_OUT
            #undefine    OPTION_CHANNEL_SEL_H
            #define OPTION_CHANNEL_SEL_H   (OPTION_TOUCH_CHANNEL_SEL_H & 00001111B)
        #endif
    #endif

    ;=====================================================================================
    #if (!(DEBUG_DATA_OUT | DEBUG_AVG_DATA_OUT | DEBUG_BASE_DATA_OUT))
    ;#ifndef DEBUG_BASE_DATA_OUT
    ;#ifndef DEBUG_DATA_OUT
    ;#ifndef DEBUG_AVG_DATA_OUT
    #if (OPT_DBG_UART_CODE_IN_LIB)
    #undefine OPT_DBG_UART_CODE_IN_LIB
    #define OPT_DBG_UART_CODE_IN_LIB         0
    #endif
    ;#endif
    ;#endif
    ;#endif
    #endif
    ;===================================================================================================
    ;扫描时间自动调整功能,滑条功能使能时自动屏蔽此功能
    ;#define AUTO_SCAN_TIME
    ;if define OPTION_REF_CHECK than disable AUTO_SCAN_TIME
    #ifdef OPTION_REF_CHECK
        #ifdef AUTO_SCAN_TIME
            #undefine AUTO_SCAN_TIME
        #endif
    #endif
    #if (OPTION_TH_WHEEL_NUM != 0)
        #undefine AUTO_SCAN_TIME
    #endif
    #ifdef AUTO_SCAN_TIME
        ;必需>= 40000 us
        #define OPTION_KEY_RESPONSE_TIME    100000
    #endif
    ;===================================================================================================
    ;如果使能Touch中断功能，在中断处理函数里面必需清除THIF标志位。
    ;使能此功能，低功耗转换时功耗更低.
    ;#define TH_LP_IDLE_EN
    ;===================================================================================================
    ;如果使能Touch中断功能，在中断处理函数里面必需清除THIF标志位。
    ;使能此功能，Touch转换过程中会进入IDLE状态.
    ;#define TH_IDLE_EN
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;阈值定义
    ;;;触摸阈值=15> X <255
    ;;;释放阈值=触摸阈值*0.75
    ;;;噪声阈值=触摸阈值*0.2
    #ifdef  TH_IDLE_EN
        #define TH_IDLE_SET  1
    #else
        #define TH_IDLE_SET  0
    #endif
    ;===================================================================================================
    ;镜子灯支持使能。使能后无自适应, 扫描次数默认为4次可通过MIRROR_SCAN_TIME参数修改; 上电无触摸延时可通过BASE_GET_WAIT与BASE_WAIT_TIME设置
    ;#define MIRROR_ENABLE
    #ifdef  MIRROR_ENABLE
        #define MIRROR_SCAN_TIME         0x03
    #endif
    #ifdef  MIRROR_ENABLE
        #define  BASE_GET_WAIT            ;定义时功能有效，不定义无此功能
    #endif

    #ifdef  MIRROR_ENABLE
        #ifdef  AUTO_THRESHOLD
            #undefine AUTO_THRESHOLD
        #endif
    #endif
    ;===================================================================================================
    ;上电触摸正常工作延时。 在芯片上电后给定等待时间内对触摸扫描数据不做任何处理，直接丢弃。
    ;#define  BASE_GET_WAIT
    #ifdef  BASE_GET_WAIT
        #define  BASE_WAIT_TIME   0x02    ;等待时间 0x01 = 触摸库调用间隔时间*256*0x01, 0x02 = 触摸库调用间隔时间*256*0x02, 有效值0x01~0xFF
    #endif
    ;===================================================================================================
    ;low power mode min threshold value
    #define OPTION_LP_THRESHOLD_MIN_VALUE       3
    ;AUTO_THRESHOLD 自动阈值模式下, LP_THR_AUTO_EN = 1 则低功耗唤醒阈值自动生成，否则低功耗阈值为配置的阈值
    #define LP_THR_AUTO_EN                      1
    ;===================================================================================================
    ;;低功耗, GP Scan
    #define MIN_POWER_MODE
    ;===================================================================================================
    ;Removed -- un-used
    ;标准片Touch 接地检测使能
    ;#define STD_THGND_CHECK_EN
    #ifdef STD_THGND_CHECK_EN
        #define STD_GND_EN  1
    #else
        #define STD_GND_EN  0
    #endif
        ;1, set TH_CHL_EN and TH_CHH_EN.(设置连接到地的脚为0, 其它脚为１)
        ;2, TH_CHL_EN 与 TH_CHH_EN为第一页的寄存器
    ;===================================================================================================
    ;Removed -- un-used
    ;Scan space for EMC
    ;#define TH_EMC_SCAN_EN
    #define OPTION_TH_SPACE              0x0F  ;两次扫描之间的时间间隔(0x01~0x0F)
    ;;;;;;
    ;#ifdef TH_EMC_SCAN_EN
    ;    #define EMC_THCKS_CHANGE_EN                ;EMC优化
    ;#endif
    ;===================================================================================================
    ;#define HIGH_PENETRATING_EN                ;高灵敏度
    #define OPTION_CFG_CHANNEL_A_0  OPTION_CFG_CHANNEL_10_0
    #define OPTION_CFG_CHANNEL_B_0  OPTION_CFG_CHANNEL_11_0

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; Do not change following items
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;===========================================================================================================
    #ifdef AUTO_THRESHOLD
        #define AUTO_TH_EN   1
    #else
        #define AUTO_TH_EN   0
    #endif
    ;===========================================================================================================
    #ifdef MIN_POWER_MODE
        #define MIN_POWER_EN  1
    #else
        #define MIN_POWER_EN  0
    #endif
    ;===================================================================================================
    #ifdef TOUCH_STATE_TOUCH_AGAIN
        #define STATE_E_TH 1
    #else
        ;No define TOUCH_STATE_TOUCH_AGAIN than disalbe OPTION_WIND_ALG
        #ifdef OPTION_WIND_ALG
            #undefine OPTION_WIND_ALG
        #endif
        #define STATE_E_TH 0
    #endif
    ;===========================================================================================================
    #ifdef  TH_LP_IDLE_EN
        #ifdef  TH_IDLE_EN
            #define TH_LP_IDLE_SET  0
        #else
            #define TH_LP_IDLE_SET  1
        #endif
    #else
        #define TH_LP_IDLE_SET  0
    #endif
    ;===================================================================================================
    #ifdef  MIRROR_ENABLE
    #ifdef  AUTO_SCAN_TIME
        #undefine AUTO_SCAN_TIME
    #endif
    #endif
    ;===========================================================================================================
    ;Get enable Touch channels
    #ifdef P101C
        #define TH_CH_COU0               ((OPTION_CHANNEL_SEL_H & 0x01)       +((OPTION_CHANNEL_SEL_H & 0x02)/ 0x02))
        #define TH_CH_COU1   (TH_CH_COU0+((OPTION_CHANNEL_SEL_H & 0x04)/ 0x04)+((OPTION_CHANNEL_SEL_H & 0x08)/ 0x08))
        #define TH_CH_COU2   (TH_CH_COU1+ (OPTION_CHANNEL_SEL_L & 0x01)       +((OPTION_CHANNEL_SEL_L & 0x02)/ 0x02))
        #define TH_CH_COU3   (TH_CH_COU2+((OPTION_CHANNEL_SEL_L & 0x04)/ 0x04)+((OPTION_CHANNEL_SEL_L & 0x08)/ 0x08))
        #define TH_CH_COU4   (TH_CH_COU3+((OPTION_CHANNEL_SEL_L & 0x10)/ 0x10)+((OPTION_CHANNEL_SEL_L & 0x20)/ 0x20))
        #define TH_CH_COU    (TH_CH_COU4+((OPTION_CHANNEL_SEL_L & 0x40)/ 0x40)+((OPTION_CHANNEL_SEL_L & 0x80)/ 0x80))
    #else
        #define TH_CH_COU5              (((OPTION_CHANNEL_SEL_H & 0x10)/ 0x10)+((OPTION_CHANNEL_SEL_H & 0x20)/ 0x20))
        #define TH_CH_COU6   (TH_CH_COU5+((OPTION_CHANNEL_SEL_H & 0x40)/ 0x40)+((OPTION_CHANNEL_SEL_H & 0x80)/ 0x80))
        #define TH_CH_COU0   (TH_CH_COU6+ (OPTION_CHANNEL_SEL_H & 0x01)       +((OPTION_CHANNEL_SEL_H & 0x02)/ 0x02))
        #define TH_CH_COU1   (TH_CH_COU0+((OPTION_CHANNEL_SEL_H & 0x04)/ 0x04)+((OPTION_CHANNEL_SEL_H & 0x08)/ 0x08))
        #define TH_CH_COU2   (TH_CH_COU1+ (OPTION_CHANNEL_SEL_L & 0x01)       +((OPTION_CHANNEL_SEL_L & 0x02)/ 0x02))
        #define TH_CH_COU3   (TH_CH_COU2+((OPTION_CHANNEL_SEL_L & 0x04)/ 0x04)+((OPTION_CHANNEL_SEL_L & 0x08)/ 0x08))
        #define TH_CH_COU4   (TH_CH_COU3+((OPTION_CHANNEL_SEL_L & 0x10)/ 0x10)+((OPTION_CHANNEL_SEL_L & 0x20)/ 0x20))
        #define TH_CH_COU    (TH_CH_COU4+((OPTION_CHANNEL_SEL_L & 0x40)/ 0x40)+((OPTION_CHANNEL_SEL_L & 0x80)/ 0x80))
    #endif
    #define TH_COU_DEC   (TH_CH_COU-1)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #ifdef OPT_PANEL_COVER_PWRON
        #define OPT_PANEL_COVER_CH    (TH_CH_COU - 1)
        #if (TH_CH_COU < 3)
            #undefine OPT_PANEL_COVER_PWRON
        #endif
        #if (OPTION_TH_WHEEL_NUM)
            #undefine OPT_PANEL_COVER_CH
            #if (OPTION_TH_WHEEL_NUM == 2)
                #define OPT_PANEL_COVER_CH    (3)
            #else
                #define OPT_PANEL_COVER_CH    (OPTION_TH_WHEEL_NUM)
            #endif
        #endif
    #endif
    ;===========================================================================================================
    #ifdef AUTO_THRESHOLD
        #if (OPTION_TOUCH_REF_GRADE == 5)
            #define OPTION_TOUCH_REF_THRESHOLD   0x20
            #define OPTION_TOUCH_REF_SHIFT       5
        #endif
        #if (OPTION_TOUCH_REF_GRADE == 6)
            #define OPTION_TOUCH_REF_THRESHOLD   0x40
            #define OPTION_TOUCH_REF_SHIFT       6
        #endif
        #if (OPTION_TOUCH_REF_GRADE == 7)
            #define OPTION_TOUCH_REF_THRESHOLD   0x80
            #define OPTION_TOUCH_REF_SHIFT       7
        #endif
        #ifndef OPTION_TOUCH_REF_THRESHOLD
            #define OPTION_TOUCH_REF_THRESHOLD   0x40
            #define OPTION_TOUCH_REF_SHIFT       6
        #endif
        #define OPTION_TOUCH_REF_NOISE       OPTION_TOUCH_REF_THRESHOLD / 5
        #define OPTION_TOUCH_REF_SLP_SHIFT   OPTION_TOUCH_REF_SHIFT-1
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;Get Reference Channels
    #ifdef AUTO_THRESHOLD
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x01)
            #define  REF_CH_SEL_L  0x01
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x02)
            #define  REF_CH_SEL_L  0x03
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x04)
            #define  REF_CH_SEL_L  0x07
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x08)
            #define  REF_CH_SEL_L  0x0F
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x10)
            #define  REF_CH_SEL_L  0x1F
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x20)
            #define  REF_CH_SEL_L  0x3F
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x40)
            #define  REF_CH_SEL_L  0x7F
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x80)
            #define  REF_CH_SEL_L  0xFF
            #define  REF_CH_SEL_H  0x00
        #endif
        #if (OPTION_TOUCH_REF_CH_SEL_L == 0x00)
            #if (OPTION_TOUCH_REF_CH_SEL_H == 0x01)
                #define  REF_CH_SEL_L  0xFF
                #define  REF_CH_SEL_H  0x01
            #endif
            #if (OPTION_TOUCH_REF_CH_SEL_H == 0x02)
                #define  REF_CH_SEL_L  0xFF
                #define  REF_CH_SEL_H  0x03
            #endif
            #if (OPTION_TOUCH_REF_CH_SEL_H == 0x04)
                #define  REF_CH_SEL_L  0xFF
                #define  REF_CH_SEL_H  0x07
            #endif
            #if (OPTION_TOUCH_REF_CH_SEL_H == 0x08)
                #define  REF_CH_SEL_L  0xFF
                #define  REF_CH_SEL_H  0x0F
            #endif
            #ifndef P101C
                #if (OPTION_TOUCH_REF_CH_SEL_H == 0x10)
                    #define  REF_CH_SEL_L  0xFF
                    #define  REF_CH_SEL_H  0x1F
                #endif

                #if (OPTION_TOUCH_REF_CH_SEL_H == 0x20)
                    #define  REF_CH_SEL_L  0xFF
                    #define  REF_CH_SEL_H  0x3F
                #endif

                #if (OPTION_TOUCH_REF_CH_SEL_H == 0x40)
                    #define  REF_CH_SEL_L  0xFF
                    #define  REF_CH_SEL_H  0x7F
                #endif

                #if (OPTION_TOUCH_REF_CH_SEL_H == 0x80)
                    #define  REF_CH_SEL_L  0xFF
                    #define  REF_CH_SEL_H  0xFF
                #endif
            #endif
        #endif
        #ifndef REF_CH_SEL_L
            #define  REF_CH_SEL_L  0x00
            #define  REF_CH_SEL_H  0x00
        #endif
        #ifdef P101C
            #define TH_REF_COU0                ((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x01)       +((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x02)/ 0x02))
            #define TH_REF_COU1   (TH_REF_COU0+((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x04)/ 0x04)+((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x08)/ 0x08))
            #define TH_REF_COU2   (TH_REF_COU1+ (REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x01)       +((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x02)/ 0x02))
            #define TH_REF_COU3   (TH_REF_COU2+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x04)/ 0x04)+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x08)/ 0x08))
            #define TH_REF_COU4   (TH_REF_COU3+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x10)/ 0x10)+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x20)/ 0x20))
            #define TH_REF_COU    (TH_REF_COU4+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x40)/ 0x40)+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x80)/ 0x80))
        #else
            #define TH_REF_COU5               (((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x10)/ 0x10)+((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x20)/ 0x20))
            #define TH_REF_COU6   (TH_REF_COU5+((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x40)/ 0x40)+((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x80)/ 0x80))
            #define TH_REF_COU0   (TH_REF_COU6+ (REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x01)       +((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x02)/ 0x02))
            #define TH_REF_COU1   (TH_REF_COU0+((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x04)/ 0x04)+((REF_CH_SEL_H & OPTION_CHANNEL_SEL_H & 0x08)/ 0x08))
            #define TH_REF_COU2   (TH_REF_COU1+ (REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x01)       +((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x02)/ 0x02))
            #define TH_REF_COU3   (TH_REF_COU2+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x04)/ 0x04)+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x08)/ 0x08))
            #define TH_REF_COU4   (TH_REF_COU3+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x10)/ 0x10)+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x20)/ 0x20))
            #define TH_REF_COU    (TH_REF_COU4+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x40)/ 0x40)+((REF_CH_SEL_L & OPTION_CHANNEL_SEL_L & 0x80)/ 0x80))
        #endif
        #if (TH_REF_COU == 00)
            #undefine TH_REF_COU
            #define   TH_REF_COU   1
        #endif
        #define TH_REF_COU_DEC TH_REF_COU-1
    #endif
    ;***************************************************************************************************
    ;wheel 0
    ;***************************************************************************************************
    ;滑条设置
    ;Get first memroy address which is define to store Wheel STATE, data..
    #define OPTION_STATE_0_LINE_WHEEL    (STATE_0_LINE + (OPTION_WHEEL_START_POSITION * 4))   ;飞凌按键起始位置86
    #define OPTION_DIFF_0_LINE_WHEEL     (OPTION_STATE_0_LINE_WHEEL + 3)
    #if ((OPTION_TH_WHEEL_NUM==0)|(OPTION_TH_WHEEL_NUM==1))
        #define OPTION_WHEEL_NUM         0x00     ;
    #endif
    #ifndef OPTION_WHEEL_NUM
        #if ((OPTION_WHEEL_START_POSITION + OPTION_TH_WHEEL_NUM + 1) > TH_CH_COU)
            #define OPTION_WHEEL_NUM     (TH_CH_COU - OPTION_WHEEL_START_POSITION - 1)
        #else
            #define OPTION_WHEEL_NUM     OPTION_TH_WHEEL_NUM ;
        #endif
    #endif
    ;#define OPTION_WHEEL_END_POSITION    (OPTION_WHEEL_NUM+OPTION_WHEEL_START_POSITION)
    #define OPTION_WHEEL_END_POSITION    (OPTION_WHEEL_NUM+OPTION_WHEEL_START_POSITION+1)

    #define OPTION_WHEEL_SWITCH_REG      (OPTION_WHEEL_RESOLUTION+1) / (OPTION_WHEEL_NUM + 1)
    #define OPTION_WHEEL_REG             (OPTION_WHEEL_RESOLUTION+1) / OPTION_WHEEL_NUM

    #ifdef DEBUG_WHEEL_DELTA_OUT
        #ifdef DEBUG_WHEEL_DIFF_OUT
            #define OPT_DBG_WHEEL_DELTA_CH (OPTION_WHEEL_NUM + 1)
        #else
            #define OPT_DBG_WHEEL_DELTA_CH (0x00)
        #endif
    #endif
    #ifdef DEBUG_WHEEL_LOCATION_OUT
        #ifdef DEBUG_WHEEL_DELTA_OUT
            #define OPT_DBG_WHEEL_LOCATION_CH (OPT_DBG_WHEEL_DELTA_CH + 1)
        #else
            #ifdef DEBUG_WHEEL_DIFF_OUT
                #define OPT_DBG_WHEEL_LOCATION_CH (OPTION_WHEEL_NUM + 1)
            #else
                #define OPT_DBG_WHEEL_LOCATION_CH (0x00)
            #endif
        #endif
    #endif
    ;; for wheel delta out, wheel diff out must set first. the output data is, wheel_ch0_diff~wheel_chx_diff~wheel_delta
    ;#ifdef DEBUG_WHEEL_DELTA_OUT
    ;    #ifndef DEBUG_WHEEL_DIFF_OUT
    ;        #define  DEBUG_WHEEL_DIFF_OUT
    ;    #endif
    ;#endif

    ;***************************************************************************************************
    ;wheel 1
    ;***************************************************************************************************
    ;滑条设置
    ;Get first memroy address which is define to store Wheel STATE, data..
    ;#define OPTION_STATE_0_LINE_WHEEL1    (STATE_0_LINE + (OPTION_WHEEL_START_POSITION1 * 4))   ;飞凌按键起始位置86
    ;#define OPTION_DIFF_0_LINE_WHEEL1     (OPTION_STATE_0_LINE_WHEEL1 + 3)
    #define OPTION_DIFF_W2_W1_SPACE       (W2_W1_START_SPACE*4)
    #if ((OPTION_TH_WHEEL_NUM1==0)|(OPTION_TH_WHEEL_NUM1==1))
        #define OPTION_WHEEL_NUM1         0x00     ;
    #endif
    #ifndef OPTION_WHEEL_NUM1
        #if ((OPTION_WHEEL_START_POSITION1 + OPTION_TH_WHEEL_NUM1 + 1) > TH_CH_COU)
            #define OPTION_WHEEL_NUM1     (TH_CH_COU - OPTION_WHEEL_START_POSITION1 - 1)
        #else
            #define OPTION_WHEEL_NUM1     OPTION_TH_WHEEL_NUM1 ;
        #endif
    #endif
    ;#define OPTION_WHEEL_END_POSITION1    (OPTION_WHEEL_NUM1+OPTION_WHEEL_START_POSITION1)
    #define OPTION_WHEEL_END_POSITION1    (OPTION_WHEEL_NUM1+OPTION_WHEEL_START_POSITION1+1)

    #define OPTION_WHEEL_SWITCH_REG1      (OPTION_WHEEL_RESOLUTION1+1) / (OPTION_WHEEL_NUM1 + 1)
    #define OPTION_WHEEL_REG1             (OPTION_WHEEL_RESOLUTION1+1) / OPTION_WHEEL_NUM1

    ;;;;#ifdef DEBUG_WHEEL_DELTA_OUT
    ;;;;    #ifdef DEBUG_WHEEL_DIFF_OUT
    ;;;;        #define OPT_DBG_WHEEL_DELTA_CH (OPTION_WHEEL_NUM + 1)
    ;;;;    #else
    ;;;;        #define OPT_DBG_WHEEL_DELTA_CH (0x00)
    ;;;;    #endif
    ;;;;#endif
    ;;;;#ifdef DEBUG_WHEEL_LOCATION_OUT
    ;;;;    #ifdef DEBUG_WHEEL_DELTA_OUT
    ;;;;        #define OPT_DBG_WHEEL_LOCATION_CH (OPT_DBG_WHEEL_DELTA_CH + 1)
    ;;;;    #else
    ;;;;        #ifdef DEBUG_WHEEL_DIFF_OUT
    ;;;;            #define OPT_DBG_WHEEL_LOCATION_CH (OPTION_WHEEL_NUM + 1)
    ;;;;        #else
    ;;;;            #define OPT_DBG_WHEEL_LOCATION_CH (0x00)
    ;;;;        #endif
    ;;;;    #endif
    ;;;;#endif
    ;; for wheel delta out, wheel diff out must set first. the output data is, wheel_ch0_diff~wheel_chx_diff~wheel_delta
    ;#ifdef DEBUG_WHEEL_DELTA_OUT
    ;    #ifndef DEBUG_WHEEL_DIFF_OUT
    ;        #define  DEBUG_WHEEL_DIFF_OUT
    ;    #endif
    ;#endif

    ;***************************************************************************************************
    ;水位检测功能
    ;***************************************************************************************************
    ;===================================================================================================
    ;OPTION_WATER_M100_DREF = 1, Water * 100 / ref
    ;OPTION_WATER_M100_DREF = 0, ref * 100 / water
    #define OPTION_WATER_MUTIL_REF          0
    #define OPTION_WATER_MREF_L             00110001B
    #define OPTION_WATER_MREF_H             00000000B
    #define OPTION_WATER_M100_DREF          0
    #ifdef DEBUG_WATER_DATA_OUT
        ;#define DEBUG_WATER_TOUCH_DATA_OUT
    #endif

    #ifndef  OPTION_TH_WATER_NUM
        #define  OPTION_TH_WATER_NUM        0
    #endif
    #ifndef OPTION_WATER_START_POSITION
    #define OPTION_WATER_START_POSITION     0   ;水位通道逻辑起始位置
                                                ;例-1:
                                                ;#define OPTION_WATER_START_POSITION  0x00
                                                ;OPTION_TOUCH_CHANNEL_SEL_L   00111111B    即TOUCH0(P1.0)为水位起点
                                                ;例-2:
                                                ;#define OPTION_WATER_START_POSITION  0x01
                                                ;OPTION_TOUCH_CHANNEL_SEL_L   00111110B    即TOUCH2(P1.2)为水位起点
    #endif
    #if ((OPTION_WATER_START_POSITION + OPTION_TH_WATER_NUM ) > TH_CH_COU)
        #define OPTION_WATER_NUM            (TH_CH_COU - OPTION_WATER_START_POSITION )
    #else
        #define OPTION_WATER_NUM            OPTION_TH_WATER_NUM
    #endif

    #define  OPTION_WATER_CH_0              (OPTION_WATER_CH0  )
    #define  OPTION_WATER_CH_1              (OPTION_WATER_CH1  )
    #define  OPTION_WATER_CH_2              (OPTION_WATER_CH2  )
    #define  OPTION_WATER_CH_3              (OPTION_WATER_CH3  )
    #define  OPTION_WATER_CH_4              (OPTION_WATER_CH4  )
    #define  OPTION_WATER_CH_5              (OPTION_WATER_CH5  )
    #define  OPTION_WATER_CH_6              (OPTION_WATER_CH6  )
    #define  OPTION_WATER_CH_7              (OPTION_WATER_CH7  )
    #define  OPTION_WATER_CH_8              (OPTION_WATER_CH8  )
    #define  OPTION_WATER_CH_9              (OPTION_WATER_CH9  )
    #define  OPTION_WATER_CH_10             (OPTION_WATER_CH10 )
    #define  OPTION_WATER_CH_11             (OPTION_WATER_CH11 )

    #define  OPTION_NO_WATER_CH_0           (OPTION_NOWATER_CH0  )
    #define  OPTION_NO_WATER_CH_1           (OPTION_NOWATER_CH1  )
    #define  OPTION_NO_WATER_CH_2           (OPTION_NOWATER_CH2  )
    #define  OPTION_NO_WATER_CH_3           (OPTION_NOWATER_CH3  )
    #define  OPTION_NO_WATER_CH_4           (OPTION_NOWATER_CH4  )
    #define  OPTION_NO_WATER_CH_5           (OPTION_NOWATER_CH5  )
    #define  OPTION_NO_WATER_CH_6           (OPTION_NOWATER_CH6  )
    #define  OPTION_NO_WATER_CH_7           (OPTION_NOWATER_CH7  )
    #define  OPTION_NO_WATER_CH_8           (OPTION_NOWATER_CH8  )
    #define  OPTION_NO_WATER_CH_9           (OPTION_NOWATER_CH9  )
    #define  OPTION_NO_WATER_CH_10          (OPTION_NOWATER_CH10 )
    #define  OPTION_NO_WATER_CH_11          (OPTION_NOWATER_CH11 )

    #define  OPTION_WATER_REF               ( TH_COU_DEC ) ;0x00
    #define  OPTION_WATER_END_POSITION      ( OPTION_WATER_START_POSITION + OPTION_WATER_NUM -1)
    #define  OPTION_WATER_START_MEM         ( BASE_0_LINE )
    ;#define  OPTION_WATER_START_MEM         ( BASE_0_LINE + (OPTION_WATER_START_POSITION * 2))
    #define  OPTION_WATER_REF_MEM           ( BASE_0_LINE + (OPTION_WATER_REF * 2))
    #if (OPTION_TH_WATER_NUM == 0)
        #undefine  OPTION_WATER_MUTIL_REF
        #define OPTION_WATER_MUTIL_REF      0
    #endif

    #if (OPTION_TH_WATER_NUM > 0)
        #define  OPTION_WATER_DEBOUNCE_EN
        #ifndef  OPTION_WATER_DEBOUNCE_NU
            #define  OPTION_WATER_DEBOUNCE_NU       0x05
        #endif
    #endif
    ;***************************************************************************************************
    ;Memory for Touch function
    ;***************************************************************************************************
    ;#define  OPT_MASK_DPAGE_CHANGE
    ;Dpage0 memory used
    #define       TH_MEM_END             (0x80)
    ;#if (OPT_DBG_UART_CODE_IN_LIB)
    ;#if (OPTION_WHEEL_NUM!=0)
    ;    #define       TH_MEM_START       (0x003C)
    ;#else
    ;    #define       TH_MEM_START       (0x003F)
    ;#endif
    ;#if (OPTION_WHEEL_NUM1!=0)
    ;    #undefine     TH_MEM_START
    ;    #define       TH_MEM_START       (0x0038)
    ;#endif
    ;#else
    ;#if (OPTION_WHEEL_NUM!=0)
    ;    #define       TH_MEM_START       (0x0040)
    ;#else
    ;    #define       TH_MEM_START       (0x0043)
    ;#endif
    ;#if (OPTION_WHEEL_NUM1!=0)
    ;    #undefine     TH_MEM_START
    ;    #define       TH_MEM_START       (0x003C)
    ;#endif
    ;#endif
    ;#if (OPT_DBG_UART_CODE_IN_LIB)
    ;UART_SEND_DATA          EQU         (TH_MEM_END - 12)
    ;CHECK_SUM               EQU         (TH_MEM_END - 11)
    ;UART_SEND_BIT_CNT       EQU         (TH_MEM_END - 10)
    ;UART_DELAY_T1           EQU         (TH_MEM_END - 9)
    ;#endif
    ;#if (OPTION_WHEEL_NUM1!=0)
    ;    WHEEL_RESERVER01     EQU         (TH_MEM_END-8)
    ;    WHEEL_DEBOUNCE1      EQU         (TH_MEM_END-7)
    ;    WHEEL_PRE_LOCATION1  EQU         (TH_MEM_END-6)
    ;    WHEEL_POSITION1      EQU         (TH_MEM_END-5)
    ;#endif
    ;#ifdef DEBUG_WHEEL_TEST_FUNCTION
    ;    RTH_CH_COU              EQU      (TH_MEM_START-4)
    ;    OPTION_RWHEEL_NUM       EQU      (TH_MEM_START-3)
    ;    OPTION_RCHANNEL_SEL_L   EQU      (TH_MEM_START-2)
    ;    OPTION_RCHANNEL_SEL_H   EQU      (TH_MEM_START-1)
    ;#endif
    ;#if (OPTION_WHEEL_NUM!=0)
    ;    WHEEL_RESERVER0     EQU          (TH_MEM_END-4)
    ;    WHEEL_DEBOUNCE      EQU          (TH_MEM_END-3)
    ;    WHEEL_PRE_LOCATION  EQU          (TH_MEM_END-2)
    ;    WHEEL_POSITION      EQU          (TH_MEM_END-1)
    ;#endif
    #define       TH_MEM_START           (0x0043)
    #if (OPT_SIX_THRESHOLD_FOR_ONE_CHANNEL)
    #if (OPT_DBG_UART_CODE_IN_LIB)
        #define       RAM_TH_SIX_THRESHOLD_SEL  (TH_MEM_START - 5)
    #else
        #define       RAM_TH_SIX_THRESHOLD_SEL  (TH_MEM_START - 1)
    #endif
    #endif
    #if (OPT_DBG_UART_CODE_IN_LIB)
        #if (OPTION_WHEEL_NUM!=0)
        UART_SEND_DATA          EQU         (TH_MEM_START - 8)
        CHECK_SUM               EQU         (TH_MEM_START - 7)
        UART_SEND_BIT_CNT       EQU         (TH_MEM_START - 6)
        UART_DELAY_T1           EQU         (TH_MEM_START - 5)
        #else
        UART_SEND_DATA          EQU         (TH_MEM_START - 4)
        CHECK_SUM               EQU         (TH_MEM_START - 3)
        UART_SEND_BIT_CNT       EQU         (TH_MEM_START - 2)
        UART_DELAY_T1           EQU         (TH_MEM_START - 1)
        #endif
    #endif
    #if (OPTION_WHEEL_NUM1!=0)
        WHEEL_RESERVER01     EQU         (TH_MEM_START-8)
        WHEEL_DEBOUNCE1      EQU         (TH_MEM_START-7)
        WHEEL_PRE_LOCATION1  EQU         (TH_MEM_START-6)
        WHEEL_POSITION1      EQU         (TH_MEM_START-5)
    #endif
    #ifdef DEBUG_WHEEL_TEST_FUNCTION
        RTH_CH_COU              EQU      (TH_MEM_START-8)
        OPTION_RWHEEL_NUM       EQU      (TH_MEM_START-7)
        OPTION_RCHANNEL_SEL_L   EQU      (TH_MEM_START-6)
        OPTION_RCHANNEL_SEL_H   EQU      (TH_MEM_START-5)
    #endif
    #if (OPTION_WHEEL_NUM!=0)
        WHEEL_RESERVER0     EQU          (TH_MEM_START-4)
        WHEEL_DEBOUNCE      EQU          (TH_MEM_START-3)
        WHEEL_PRE_LOCATION  EQU          (TH_MEM_START-2)
        WHEEL_POSITION      EQU          (TH_MEM_START-1)
    #endif

    TH_KEY_EXPIRE_H         EQU          (TH_MEM_START + 0)  ;
    #define  TH_GIE_FLAG    TH_KEY_EXPIRE_H , 7
    KEY_STATE_H             EQU          (TH_MEM_START + 1)  ;
        #DEFINE  KEY_15                  KEY_STATE_H, 7      ;
        #DEFINE  KEY_14                  KEY_STATE_H, 6      ;
        #DEFINE  KEY_13                  KEY_STATE_H, 5      ;
        #DEFINE  KEY_12                  KEY_STATE_H, 4      ;
        #DEFINE  KEY_11                  KEY_STATE_H, 3      ;
        #DEFINE  KEY_10                  KEY_STATE_H, 2      ;
        #DEFINE  KEY_9                   KEY_STATE_H, 1      ;
        #DEFINE  KEY_8                   KEY_STATE_H, 0      ;
    TH_KEY_EXPIRE_L         EQU          (TH_MEM_START + 2)  ;
    KEY_STATE_L             EQU          (TH_MEM_START + 3)  ;
        #DEFINE  KEY_7                   KEY_STATE_L, 7      ;
        #DEFINE  KEY_6                   KEY_STATE_L, 6      ;
        #DEFINE  KEY_5                   KEY_STATE_L, 5      ;
        #DEFINE  KEY_4                   KEY_STATE_L, 4      ;
        #DEFINE  KEY_3                   KEY_STATE_L, 3      ;
        #DEFINE  KEY_2                   KEY_STATE_L, 2      ;
        #DEFINE  KEY_1                   KEY_STATE_L, 1      ;
        #DEFINE  KEY_0                   KEY_STATE_L, 0      ;

    LOW_POWER               EQU          (TH_MEM_START + 4)  ;
        #define   LP_EN                  LOW_POWER,0
        #define   LP_AL                  LOW_POWER,1
        #define   FIRST                  LOW_POWER,2
        #define   DIFF_P_N               LOW_POWER,3
        #define   MIN_BS_SCAN            LOW_POWER,4
        #define   BIT_TH_GIE_FLAG        LOW_POWER,4
        #define   PWR_ON_SPEED_UP        LOW_POWER,5         ;V1.4
        #define   WATER_CHANNEL_TRUE     LOW_POWER,6
        #define   AUTO_SCAN_TIME_CHECK   LOW_POWER,7
        #define   WHEEL_CH1_GEN          LOW_POWER,7
        #define   TH_THRESHOLD_TOW_SEL   LOW_POWER,7
    FLAGE                   EQU          (TH_MEM_START+ 5)  ;
        #define   TH_SCAN_DATA_GEN       FLAGE,0
        #define   WHEEL_CHANNEL_TRUE     FLAGE,1
        #define   WHEEL_CONTINUE         FLAGE,2
        #define   WHEEL_CORRECT_PN       FLAGE,3
        #define   WHEEL_GUESS_INC_DEC    FLAGE,4
        #define   WHEEL_CONTINUE1        FLAGE,5
        #define   WHEEL_CORRECT_PN1      FLAGE,6
        #define   WHEEL_GUESS_INC_DEC1   FLAGE,7

    BUF0                    EQU          (TH_MEM_START+ 6) ;
    BUF1                    EQU          (TH_MEM_START+ 7) ;
    BUF2                    EQU          (TH_MEM_START+ 8) ;
    BUF3                    EQU          (TH_MEM_START+ 9) ;
    BUF4                    EQU          (TH_MEM_START+10) ;
    R0                      EQU          (TH_MEM_START+11) ;
    R1                      EQU          (TH_MEM_START+12) ;
    R2                      EQU          (TH_MEM_START+13) ;
    R3                      EQU          (TH_MEM_START+14) ;
    R4                      EQU          (TH_MEM_START+15) ;
    TH_COU_ACC_AVG_H        EQU          (TH_MEM_START+16) ;Touch count or ACC or Average value low byte
    TH_COU_ACC_AVG_L        EQU          (TH_MEM_START+17) ;Touch count or ACC or Average value high byte
    CURRENT_TH_NU           EQU          (TH_MEM_START+18) ;Channel Map number in function
    CURRENT_TH_CH_H         EQU          (TH_MEM_START+19) ;current selected touch channel
    CURRENT_TH_CH_L         EQU          (TH_MEM_START+20) ;current selected touch channel
    BASE_VALUE_H            EQU          (TH_MEM_START+21) ;current BASE value high bit
    BASE_VALUE_L            EQU          (TH_MEM_START+22) ;current BASE value low bit
    TH_ACTIVE_DATA          EQU          (TH_MEM_START+23) ;Current acitve data count
    TH_BUCKET_DATA          EQU          (TH_MEM_START+24) ;Current Touch Channel Bucket Data
    SCAN_CYC_CNT            EQU          (TH_MEM_START+25) ;Current Total Scan cycles for Touch
    SCAN_TIME               EQU          (TH_MEM_START+26) ;低功耗模式扫描次数
    BUCKET_THRESHOLD        EQU          (TH_MEM_START+27) ;水桶累积至N0~N7值后基值加1或减1
    SLP_WKUP                EQU          (TH_MEM_START+27) ;
    KEYFINGER_THRESHOLD     EQU          (TH_MEM_START+28) ;触摸阈值
    RELEASE_THRESHOLD       EQU          (TH_MEM_START+29) ;释放阈值
    NOISE_THRESHOLD         EQU          (TH_MEM_START+30) ;噪声阈值(一般设置为小于触摸阈值的1/3)
    TH_STATE_DATA           EQU          (TH_MEM_START+31) ;Current Touch Channel State
        #DEFINE  TH_CURRENT_STATE_E      TH_STATE_DATA, 5  ;
        #DEFINE  TH_CURRENT_STATE_D      TH_STATE_DATA, 4  ;
        #DEFINE  TH_CURRENT_STATE_4      TH_STATE_DATA, 3  ;
        #DEFINE  TH_CURRENT_STATE_3      TH_STATE_DATA, 2  ;
        #DEFINE  TH_CURRENT_STATE_2      TH_STATE_DATA, 1  ;
        #DEFINE  TH_CURRENT_STATE_1      TH_STATE_DATA, 0  ;
    DIFF_CASE               EQU          (TH_MEM_START+32) ;Difference value states
        #DEFINE  DIFF_CASE_5             DIFF_CASE, 4      ;
        #DEFINE  DIFF_CASE_4             DIFF_CASE, 3      ;
        #DEFINE  DIFF_CASE_3             DIFF_CASE, 2      ;
        #DEFINE  DIFF_CASE_2             DIFF_CASE, 1      ;
        #DEFINE  DIFF_CASE_1             DIFF_CASE, 0      ;
    DIFF_VALUE              EQU          (TH_MEM_START+33) ;BASE - Average
    ;Touch count ACC  计数累加值 平均值
    CHANNEL_0_ACCTO         EQU          (TH_MEM_START+34) ;
    MEM_ACCTO_END           EQU          (TH_MEM_START+34+26);
    #ifdef P101C
        #DEFINE  B_MAX_THCH_LOCATION     R1    , 4
    #else
        #DEFINE  B_MAX_THCH_LOCATION     R1    , 5
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; complex function for memory
    #if (AUTO_TH_EN == 0x01)
        SQUARE_INL          EQU          CHANNEL_0_ACCTO+ 0  ;
        SQUARE_INH          EQU          CHANNEL_0_ACCTO+ 1  ;
        RR_TEMP0            EQU          CHANNEL_0_ACCTO+ 2  ;
        RR_TEMP1            EQU          CHANNEL_0_ACCTO+ 3  ;
        RL_TEMP0            EQU          CHANNEL_0_ACCTO+ 4  ;
        RL_TEMP1            EQU          CHANNEL_0_ACCTO+ 5  ;
        RL_TEMP2            EQU          CHANNEL_0_ACCTO+ 6  ;
        RL_TEMP3            EQU          CHANNEL_0_ACCTO+ 7  ;
        SQUARE_OUTH0        EQU          CHANNEL_0_ACCTO+ 8  ;
        SQUARE_OUTH1        EQU          CHANNEL_0_ACCTO+ 9  ;
        SQUARE_OUTH2        EQU          CHANNEL_0_ACCTO+10  ;
        SQUARE_OUTH3        EQU          CHANNEL_0_ACCTO+11  ;
        CH0_SQUARE0         EQU          CHANNEL_0_ACCTO+12  ;
        CH0_SQUARE1         EQU          CHANNEL_0_ACCTO+13  ;
        CH0_SQUARE2         EQU          CHANNEL_0_ACCTO+14  ;
        CH0_SQUARE3         EQU          CHANNEL_0_ACCTO+15  ;
        REF_CH_NU           EQU          CHANNEL_0_ACCTO+16  ;
        REF_CH_TEMP         EQU          CHANNEL_0_ACCTO+17  ;
        SLP_WKUP0           EQU          KEYFINGER_THRESHOLD
        SLP_WKUP1           EQU          RELEASE_THRESHOLD
        SLP_WKUP2           EQU          NOISE_THRESHOLD
    #endif
    LP_TH0_CUT              EQU          CHANNEL_0_ACCTO+12  ;
    LP_TH0_STATUS           EQU          CHANNEL_0_ACCTO+13  ;
    LP_TH1_CUT              EQU          CHANNEL_0_ACCTO+14  ;
    LP_TH1_STATUS           EQU          CHANNEL_0_ACCTO+15  ;
    LP_TH2_CUT              EQU          CHANNEL_0_ACCTO+16  ;
    LP_TH2_STATUS           EQU          CHANNEL_0_ACCTO+17  ;
    LP_TH0_BASE_L           EQU          CHANNEL_0_ACCTO+18  ;
    LP_TH0_BASE_H           EQU          CHANNEL_0_ACCTO+19  ;
    LP_TH1_BASE_L           EQU          CHANNEL_0_ACCTO+20  ;
    LP_TH1_BASE_H           EQU          CHANNEL_0_ACCTO+21  ;
    LP_TH2_BASE_L           EQU          CHANNEL_0_ACCTO+22  ;
    LP_TH2_BASE_H           EQU          CHANNEL_0_ACCTO+23  ;
    LP_SCAN_COU             EQU          DIFF_CASE
    #if ((OPTION_WHEEL_NUM!=0) | (OPTION_WATER_NUM!=0))
        W_CH0_DIFF_H4BITS   EQU          (CHANNEL_0_ACCTO+ 0)
        W_DIFF_H4BITS_START EQU          (CHANNEL_0_ACCTO + OPTION_WHEEL_START_POSITION)
        ;W_DIFF_H4BITS_START1 EQU         (CHANNEL_0_ACCTO + OPTION_WHEEL_START_POSITION1)
        W2_W1_START_SPACE   EQU          (OPTION_WHEEL_START_POSITION1 - OPTION_WHEEL_START_POSITION)
        W_CH0_PN            EQU          CHANNEL_0_ACCTO+14
        W_DELTA_CH          EQU          CHANNEL_0_ACCTO+15
        W_SUM_DIFF_L        EQU          CHANNEL_0_ACCTO+16
        W_SUM_DIFF_H        EQU          CHANNEL_0_ACCTO+17
        W_DELTA_DIFF_L      EQU          CHANNEL_0_ACCTO+18
        W_DELTA_DIFF_H      EQU          CHANNEL_0_ACCTO+19
        W_DELTA_N1_DIFF_L   EQU          CHANNEL_0_ACCTO+20
        W_DELTA_N1_DIFF_H   EQU          CHANNEL_0_ACCTO+21
        W_DELTA_P1_DIFF_L   EQU          CHANNEL_0_ACCTO+22
        W_DELTA_P1_DIFF_H   EQU          CHANNEL_0_ACCTO+23
        WATER_DETECTED_L    EQU          CHANNEL_0_ACCTO+20
        WATER_DETECTED_H    EQU          CHANNEL_0_ACCTO+21
        NOWATER_DETECTED_L  EQU          CHANNEL_0_ACCTO+22
        NOWATER_DETECTED_H  EQU          CHANNEL_0_ACCTO+23
    #endif
    ;-------------------------------------------------------------------------------
    ;dpage1 memory used
    #define        D1_THLIB_MEM_START    (0x80)
    ; BASE value 基线值
    BASE_0_LINE             EQU          (D1_THLIB_MEM_START);
    ;Touch State, Active, Bucket value 状态值、有效数据数、水桶 差值
    STATE_0_LINE            EQU          (BASE_0_LINE  + (TH_CH_COU*2)) ;
    ;Set OPTION_WIND_ALG Memory
    #if (AUTO_TH_EN == 0x01)
        TH0_TH_MEM          EQU          (STATE_0_LINE + (TH_CH_COU*4))
        #ifdef OPTION_WIND_ALG
            M_WIND_BASE_0_LINE  EQU      (TH0_TH_MEM   + (TH_CH_COU*2))
            ;EBASEL, EBASEH, RDEBOUNCE, UDEBOUNCE
            #define END_TH0_TH_MEM       (TH0_TH_MEM   + (TH_CH_COU*6))
        #else
            #define END_TH0_TH_MEM       (TH0_TH_MEM   + (TH_CH_COU*2))
        #endif
    #else
        #ifdef OPTION_WIND_ALG
            M_WIND_BASE_0_LINE  EQU      (STATE_0_LINE + (TH_CH_COU*4))
            #define END_TH0_TH_MEM       (STATE_0_LINE + (TH_CH_COU*8))
        #else
            #define END_TH0_TH_MEM       (STATE_0_LINE + (TH_CH_COU*4))
        #endif
    #endif
    #ifdef OPT_TH_SCAN_MAX_MIN_CHECK
        MAX_MIN_DATA_0_LINE     EQU      (END_TH0_TH_MEM)
        #undefine  END_TH0_TH_MEM
        #define   END_TH0_TH_MEM         (MAX_MIN_DATA_0_LINE + (TH_CH_COU*4))
    #endif
    #ifdef OPT_PANEL_COVER_PWRON
        M_PLAN_DEBOUNCE     EQU          (END_TH0_TH_MEM + 1)
    #endif
    M_PRE_WHEEL_DELTA_L     EQU          (END_TH0_TH_MEM + 5)
    M_PRE_WHEEL_DELTA_H     EQU          (END_TH0_TH_MEM + 6)
    #ifdef TH_EMC_SCAN_EN
        EMC_DELAY1          EQU          (END_TH0_TH_MEM + 0)
        EMC_DELAY2          EQU          (END_TH0_TH_MEM + 1)
    #endif
    WATER_LP_BASE           EQU          (END_TH0_TH_MEM + 2)   ;Memory mutil functions
    #if (OPTION_WHEEL_NUM!=0)
    #ifdef OPTION_DIRECTION_DEBOUNCE_EN
        WHEEL_DIR_DEBOUNCE  EQU          (END_TH0_TH_MEM + 0)
    #endif
    #endif
    #if (OPTION_WHEEL_NUM1!=0)
    #ifdef OPTION_DIRECTION_DEBOUNCE_EN
        WHEEL_DIR_DEBOUNCE1  EQU          (END_TH0_TH_MEM + 1)
    #endif
    #endif
    AUTO_CH_SCAN_TIME       EQU          (END_TH0_TH_MEM + 3)
    #ifdef  BASE_GET_WAIT
        MIRROR_BASE_WAIT_CON_L   EQU     (BASE_0_LINE + 0)
        MIRROR_BASE_WAIT_CON_H   EQU     (BASE_0_LINE + 1)
        ;BASE_WAIT_STATE_END can not be clear for TOUCH reset
        BASE_WAIT_STATE          EQU     (END_TH0_TH_MEM + 4)
        #DEFINE  BASE_WAIT_STATE_END     BASE_WAIT_STATE, 0  ;
    #endif
    #if (STD_GND_EN == 0x01)
        TH_CHL_EN           EQU          (END_TH0_TH_MEM + 5)
        TH_CHH_EN           EQU          (END_TH0_TH_MEM + 6)
    #endif
    #ifdef MIRROR_ENABLE
        MIRROR_E_TOUCH_L    EQU          (END_TH0_TH_MEM + 5)
        MIRROR_E_TOUCH_H    EQU          (END_TH0_TH_MEM + 6)
    #endif
    TH_PWRON_WAIT_CNT       EQU          (END_TH0_TH_MEM + 7)
    #define        D1_THLIB_MEM_END      (END_TH0_TH_MEM + 4)
    #if (END_TH0_TH_MEM > (0xF0 - 6))
        #error "memory not enough!! reduce touch or disable some functions"
    #endif
    ;***************************************************************************************************
    ;扫描时间自动调整功能
    #ifdef AUTO_SCAN_TIME
        ;Memory define for AUTO Scan Time Adjust   begin
        ;临时CDC转换时间累加变量
        CDC_CHARGE_TIME_ACCH     EQU     CHANNEL_0_ACCTO+ 22
        CDC_CHARGE_TIME_ACCL     EQU     CHANNEL_0_ACCTO+ 23
        ;Memory define for AUTO Scan Time Adjust   end
        ;每轮扫描的扫描时间单位us
        #define OPTION_ONE_TIME_SCAN_GAP    20000   ;us
        ;CDC status check time is 300us for one channel
        #define OPTION_CDC_ACC_TIME        ((OPTION_ONE_TIME_SCAN_GAP) - 300 * (TH_CH_COU))
        ;Charge time is OPTION_CMOD_CHARGE_CNT *1.5us @8M 2分频
        #define TEMP_OPTION_CMOD_TIME      (OPTION_CMOD_CHARGE_CNT)*3/2
        #define OPTION_CMOD_CHARGE         (TEMP_OPTION_CMOD_TIME)*(TH_CH_COU)
        #define OPTION_AUTO_DEBOUNCE_OUT   (OPTION_KEY_RESPONSE_TIME) / (OPTION_ONE_TIME_SCAN_GAP) / 2
        #define OPTION_AUTO_DEBOUNCE_IN    (OPTION_KEY_RESPONSE_TIME) / (OPTION_ONE_TIME_SCAN_GAP) - (OPTION_AUTO_DEBOUNCE_OUT)
        #undefine OPTION_KEY_IN_DEBONCE
        #if(OPTION_AUTO_DEBOUNCE_IN!=0)
            #define OPTION_KEY_IN_DEBONCE  (OPTION_AUTO_DEBOUNCE_IN)-1
        #else
            #define OPTION_KEY_IN_DEBONCE  0
        #endif
        #undefine OPTION_KEY_OUT_DEBONCE
        #if(OPTION_AUTO_DEBOUNCE_OUT!=0)
            #define OPTION_KEY_OUT_DEBONCE (OPTION_AUTO_DEBOUNCE_OUT)-1
        #else
            #define OPTION_KEY_OUT_DEBONCE 0
        #endif
    #endif
    ;**************************************************************************
    ;低功耗设置
    ;***************************************************************************************************
    #if (((OPTION_LP_CHANNEL_SEL_L & OPTION_CHANNEL_SEL_L)||(OPTION_LP_CHANNEL_SEL_H & OPTION_CHANNEL_SEL_H))==0)
        #undefine OPTION_LP_CHANNEL_SEL_L
        #undefine OPTION_LP_CHANNEL_SEL_H
        #define  OPTION_LP_CHANNEL_SEL_L   OPTION_CHANNEL_SEL_L
        #define  OPTION_LP_CHANNEL_SEL_H   (OPTION_CHANNEL_SEL_H & 0x0F)
    #endif
    #define TEMP_OPTION_LP_CHANNEL_SEL_L (OPTION_LP_CHANNEL_SEL_L & OPTION_CHANNEL_SEL_L)
    #define TEMP_OPTION_LP_CHANNEL_SEL_H (OPTION_LP_CHANNEL_SEL_H & OPTION_CHANNEL_SEL_H & 0x0F)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #define LP_CH0_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x01) / 0x01)
    #define LP_CH1_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x02) / 0x02)
    #define LP_CH2_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x04) / 0x04)
    #define LP_CH3_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x08) / 0x08)
    #define LP_CH4_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x10) / 0x10)
    #define LP_CH5_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x20) / 0x20)
    #define LP_CH6_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x40) / 0x40)
    #define LP_CH7_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_L & 0x80) / 0x80)
    #define LP_CH8_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_H & 0x01) / 0x01)
    #define LP_CH9_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_H & 0x02) / 0x02)
    #define LP_CHA_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_H & 0x04) / 0x04)
    #define LP_CHB_STATE               ((TEMP_OPTION_LP_CHANNEL_SEL_H & 0x08) / 0x08)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #define LP_CH0TO5                  LP_CH0_STATE+LP_CH1_STATE+LP_CH2_STATE+LP_CH3_STATE+LP_CH4_STATE+LP_CH5_STATE
    #define LP_GP0_CH_L    0
    #define LP_GP0_CH_H    0
    #define LP_GP1_CH_L    0
    #define LP_GP1_CH_H    0
    #define LP_GP2_CH_L    0
    #define LP_GP2_CH_H    0
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #define LP_GP0_CH0     0
    #define LP_GP0_CH1     0
    #define LP_GP0_CH2     0
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #define LP_TOTAL_CH LP_CH0_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x01
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x01
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x01
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x01
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0_STATE+LP_CH1_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x03
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_TEMP_OPTION_LP_CHANNEL_SEL_L&0x03
        #define LP_GP0_C2_TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x03
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x03
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0_STATE+LP_CH1_STATE+LP_CH2_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x07
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x07
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x07
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x07
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0_STATE+LP_CH1_STATE+LP_CH2_STATE+LP_CH3_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x0F
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x0F
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x0F
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x0F
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0_STATE+LP_CH1_STATE+LP_CH2_STATE+LP_CH3_STATE+LP_CH4_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x1F
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x1F
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x1F
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x1F
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  (TEMP_OPTION_LP_CHANNEL_SEL_L&0x1F - (LP_GP0_CH_L))
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0_STATE+LP_CH1_STATE+LP_CH2_STATE+LP_CH3_STATE+LP_CH4_STATE+LP_CH5_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x3F
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x3F
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x3F
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x3F
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x3F - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0TO5+LP_CH6_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x7F
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x7F
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x7F
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0x7F
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0x7F - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0TO5+LP_CH6_STATE+LP_CH7_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x00
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0TO5+LP_CH6_STATE+LP_CH7_STATE+LP_CH8_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x01
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x01
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x01
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x01
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x01 - (LP_GP0_CH_H)
    #endif
    #if (LP_TOTAL_CH>8)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x01 - (LP_GP0_CH_H) - (LP_GP1_CH_H)
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0TO5+LP_CH6_STATE+LP_CH7_STATE+LP_CH8_STATE+LP_CH9_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x03
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x03
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x03
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x03
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x03 - (LP_GP0_CH_H)
    #endif
    #if (LP_TOTAL_CH>8)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x03 - (LP_GP0_CH_H) - (LP_GP1_CH_H)
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0TO5+LP_CH6_STATE+LP_CH7_STATE+LP_CH8_STATE+LP_CH9_STATE+LP_CHA_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x07
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x07
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x07
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x07
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x07 - (LP_GP0_CH_H)
    #endif
    #if (LP_TOTAL_CH>8)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x07 - (LP_GP0_CH_H) - (LP_GP1_CH_H)
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #undefine LP_TOTAL_CH
    #define LP_TOTAL_CH LP_CH0TO5+LP_CH6_STATE+LP_CH7_STATE+LP_CH8_STATE+LP_CH9_STATE+LP_CHA_STATE+LP_CHB_STATE
    #if ((LP_TOTAL_CH!=0)&(LP_TOTAL_CH<=4))
    #undefine LP_GP0_CH_L
    #define LP_GP0_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
    #undefine LP_GP0_CH_H
    #define LP_GP0_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F
    #if((LP_GP0_CH1==1) &&(LP_GP0_CH0==1)&&(LP_GP0_CH2==0))
        #define LP_GP0_C2_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C2_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F
        #undefine LP_GP0_CH2
        #define LP_GP0_CH2 1
    #endif
    #if((LP_GP0_CH1==0) &&(LP_GP0_CH0==1))
        #define LP_GP0_C1_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C1_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F
        #undefine LP_GP0_CH1
        #define LP_GP0_CH1 1
    #endif
    #if(LP_GP0_CH0==0)
        #define LP_GP0_C0_L TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF
        #define LP_GP0_C0_H TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F
        #undefine LP_GP0_CH0
        #define LP_GP0_CH0 1
    #endif
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H)
    #endif
    #if (LP_TOTAL_CH>8)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) - (LP_GP1_CH_H)
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #ifndef LP_GP0_C1_L
        #define LP_GP0_C1_L    0
        #define LP_GP0_C1_H    0
    #endif
    #ifndef LP_GP0_C2_L
        #define LP_GP0_C2_L    0
        #define LP_GP0_C2_H    0
    #endif
    #if (LP_TOTAL_CH==5)
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) + (LP_GP0_C2_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) + (LP_GP0_C2_H)
    #endif
    #if (LP_TOTAL_CH==6)
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) + (LP_GP0_C1_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) + (LP_GP0_C1_H)
    #endif
    #if (LP_TOTAL_CH==7)
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) + (LP_GP0_C0_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) + (LP_GP0_C0_H)
    #endif
    #if (LP_TOTAL_CH==8)
    #undefine LP_GP1_CH_L
    #define LP_GP1_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L)
    #undefine LP_GP1_CH_H
    #define LP_GP1_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H)
    #endif
    #if (LP_TOTAL_CH==9)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L) + (LP_GP0_C2_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) - (LP_GP1_CH_H) + (LP_GP0_C2_H)
    #endif
    #if (LP_TOTAL_CH==10)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L) + (LP_GP0_C1_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) - (LP_GP1_CH_H) + (LP_GP0_C1_H)
    #endif
    #if (LP_TOTAL_CH==11)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L) + (LP_GP0_C0_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) - (LP_GP1_CH_H) + (LP_GP0_C0_H)
    #endif
    #if (LP_TOTAL_CH==12)
    #undefine LP_GP2_CH_L
    #define LP_GP2_CH_L  TEMP_OPTION_LP_CHANNEL_SEL_L&0xFF - (LP_GP0_CH_L) - (LP_GP1_CH_L)
    #undefine LP_GP2_CH_H
    #define LP_GP2_CH_H  TEMP_OPTION_LP_CHANNEL_SEL_H&0x0F - (LP_GP0_CH_H) - (LP_GP1_CH_H)
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #if (LP_TOTAL_CH>8 )
        #define LP_GPS 3
    #endif
    #if ((LP_TOTAL_CH>4) && (LP_TOTAL_CH<=8))
        #define LP_GPS 2
    #endif
    #if (LP_TOTAL_CH<=4 )
        #define LP_GPS 1
    #endif
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #define   LP_BASE_DEBENCE       0x04  ;debounce for LP base update for V3.5
    #define   LP_BASE_UP_VALUE      0x00  ;LP base +base_up_value or -base_up_value. LP_BASE_UP_NEW_VALUE will mask this function

#endif

;***************************************************************************************************
