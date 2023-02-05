# SDCC EIDE base on vscode

## sdcc 与 keil 语法差异 
```
{
sbit pin=P1^0;//KEIL 中定义 pin 为 P1.1

#define pin P1_0//SDCC 中定义 pin 为 P1.1
__sbit __at 0x90 pin//SDCC 
SBIT(pin,0x90,0);//SDCC 

void Timer0() interrupt 1//KEIL 中定义 Timer0()为中断1的中断服务函数
void Timer0() __interrupt 1//SDCC 中定义 Timer0()为中断1的中断服务函数
//declare nvic function before use 在使用中断函数之前要声明

//keil
int data number;

//sdcc
int __data sdcc;
//在keil关键字data、bdata、idata、xdata、code等前面加上两个_就是sdcc关键字,如__code
}
```
