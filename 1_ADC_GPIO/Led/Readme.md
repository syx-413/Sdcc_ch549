## Eide 属性
### 包含目录
包含目录（IncludePath）是指 c 头文件（.h）的搜索路径

这个配置包含了项目的全局的包含目录

如果编译器在构建时抛出一个错误，并告诉您没有找到 xx.h 文件，您可能需要检查此配置
### 库目录
当你使用 -l 命令行选项（比如：-lxxx, -lmy_lib）添加了一些库时（.lib, .a），该配置将告诉链接器这些库文件的搜索路径

注意
这个配置仅适用于 GCC 系列编译器，对于其他类型编译器， 你可以使用 添加源文件 功能直接添加 .lib, .obj 文件到项目，这将获得同样的效果






## Sdcc 语法差距
包含自定义的头文件时必须使用双引号。例如，我的某个项目中有个名为tm1638.h 的文件，那么在Keil中我可以写
`#include <tm1638.h> `，
但在SDCC中必须写成 `#include "tm1638.h"`。

Keil中的特殊类型 `sbit `和 `sfr `在SDCC中为 `__sbit和 __sfr` 。例如，

Keil中的代码    `sfr P0 = 0x80;`         `sbit P0_1 = P0 ^ 1`
在SDCC中就要写成：`__sfr __at (0x80) P0`; `__sbit __at (0x81) P0_1`; 。


不过好在8052.h 中已经为我们定义好了常用的端口，需要使用哪个端口时，直接使用P0、P1、P2_1之类的宏即可。

Keil中的`code`关键字（用于将数据放入代码段）在SDCC中应该写成`__code`。例如，

在Keil中的代码 `unsigned char code sevenseg_hex[] = { ... };` 
在SDCC中应该这样写：`"__code unsigned char sevenseg_hex[] = { ... };"`

Keil中的 interrupt 关键字在SDCC中应该写成 `__interrupt`。所以定义中断处理函数的代码在SDCC中应该写成：
`void timer0() __interrupt 1 { ... }`
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



### CH549
CH549 芯片是一款兼容 MCS51 指令集的增强型 E8051 内核单片机，其 79%的指令是单字节单周期
指令，平均指令速度比标准 MCS51 快 8～15 倍。
CH549 支持最高 48MHz 系统主频，内置 64K 程序存储器 Flash-ROM 和 256 字节内部 iRAM 以及 2K
字节片内 xRAM，xRAM 支持 DMA 直接内存存取。


CH549 内置了 12 位 ADC 模数转换、电容式触摸按键检测模块、TS 温度传感器、内置时钟、3 组
定时器和 3 路信号捕捉、8 路 PWM、4 组异步串口、SPI 等功能模块，支持全速和低速 USB-Host 主机
模式和 USB-Device 设备模式以及 USB type-C，如需完整 PD 功能建议用 CH543。