#ifndef __UART_H__
#define __UART_H__
#include <CH549_sdcc.h>	 //ch549的头文件，其中定义了单片机的一些特殊功能寄存器
#include <CH549_DEBUG.h>   //CH549官方提供库的头文件，定义了一些关于时钟设置等函数
/* UART1相关 */
#define   UART1_INTERRUPT                           //定义是否开启串口1中断
#define   UART1_BUAD           115200               //串口1波特率配置
/* UART2相关 */
#define   UART2_INTERRUPT                           //定义是否开启串口2中断
#define   UART2_BUAD           115200               //串口2波特率配置
/* UART3相关 */
#define   UART3_INTERRUPT                           //定义是否开启串口3中断
#define   UART3_BUAD           115200               //串口2波特率配置
/* 外部调用子函数 */
extern void  CH549UART1Init();                      //UART1初始化函数
extern void  CH549UART1Alter();                     //串口1引脚映射
extern UINT8 CH549UART1RcvByte( );                  //UART1接收一个字节
extern void  CH549UART1SendByte(UINT8 SendDat);     //UART1发送一个字节
extern void  CH549UART2Init();                      //UART2初始化函数
extern UINT8 CH549UART2RcvByte( );                  //UART2接收一个字节
extern void  CH549UART2SendByte(UINT8 SendDat);     //UART2发送一个字节
extern void  CH549UART3Init();                      //UART3初始化函数
extern UINT8 CH549UART3RcvByte( );                  //UART3接收一个字节
extern void  CH549UART3SendByte(UINT8 SendDat);     //UART3发送一个字节
extern void UART1Interrupt(void) __interrupt INT_NO_UART1 __using 1 ;         //串口1中断服务程序,使用寄存器组1
extern void UART2Interrupt(void) __interrupt INT_NO_UART2 __using 1 ;         //串口2中断服务程序,使用寄存器组1
extern void UART3Interrupt(void) __interrupt INT_NO_UART3 __using 1 ;         //串口3中断服务程序,使用寄存器组1
#endif
