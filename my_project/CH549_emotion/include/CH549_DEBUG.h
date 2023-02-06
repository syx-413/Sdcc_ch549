/* 调试 */
/* 提供printf子程序和延时函数 */

#ifndef	__DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <string.h>

//定义函数返回值
#ifndef  SUCCESS
#define  SUCCESS  1
#endif
#ifndef  FAIL
#define  FAIL    0
#endif

//定义定时器起始
#ifndef  START
#define  START  1
#endif
#ifndef  STOP
#define  STOP    0
#endif

#ifndef  DE_PRINTF                       //调试开关
#define  DE_PRINTF     1
#endif

#define	 FREQ_SYS	  48000000	         //系统主频48MHz
#define  OSC_EN_XT     1                 //外部晶振使能，默认开启内部晶振

#ifndef  UART0BUAD
#define  UART0BUAD     115200
#endif


extern void	CfgFsys( );                        // CH549时钟选择和配置
extern void	mDelayuS( UINT16 n );              // 以uS为单位延时
extern void	mDelaymS( UINT16 n );              // 以mS为单位延时
extern void  CH559UART0Alter();                 // CH549串口0引脚映射到P0.2/P0.3
extern void	mInitSTDIO( );                     // T1作为波特率发生器
extern void  CH549SoftReset( );                 // CH549软复位
extern void  CH549WDTModeSelect(UINT8 mode);	   // 看门狗模式选择
extern void  CH549WDTFeed(UINT8 tim);           // 喂狗
	
#endif

