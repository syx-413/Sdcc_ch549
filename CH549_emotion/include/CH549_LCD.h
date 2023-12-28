/**
  ******************************************************************
  * @file    CH549_LCD.h
  * @author  Daniel Wu, Yujun Wu,Benue
  * @version 0.1.1
  * @date    2022-03-16
  * @brief
  ******************************************************************
**/

#include <CH549_sdcc.h>	  	//ch549的头文件，其中定义了单片机的一些特殊功能寄存器

#ifndef _CH549_LCD_H_
#define _CH549_LCD_H_

//支持的 LCD 型号
#define LCD_ST7789 0
#define LCD_ILI9225 1

//实际使用的 LCD 型号与分辨率
#define LCD_MODEL (LCD_ILI9225) 
#define LCD_W 176
#define LCD_H 220

//LCD 的 SPI 接口定义
#define LCD_BLK     (P3_2)                 //Backlight 背光控制
#define LCD_RES     (P3_0)                 //Reset     复位 
#define LCD_DC      (P3_1)                 //Data/Command 数据/命令选择
#define LCD_CS      (P3_3) 

// SPI 引脚
// CH549 硬件 SPI 的引脚不可改动
// #define LCD_SCK     (P1_7)              //SCLK/SCL  SPI 时钟线
// #define LCD_MOSI     (P1_5)             //MOSI/SDA  SPI 数据线

//-----------------LCD端口定义----------------
#define LCD_CMD  0	//写命令
#define LCD_DATA 1	//写数据

#define LCD_CS_POL 0 //CS 极性

//RGB565颜色
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define RED              0xF800
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define ORANGE           0xFD20
#define PURPLE           0x8010
#define BROWN            0XBC40
#define GOLD             0xFEA0
#define SILVER           0xC618
#define GRAY             0X8430
#define GRAY175          0XAD75
#define GRAY151          0X94B2
#define GRAY187          0XBDD7
#define GRAY240          0XF79E
#define MAGENTA          0xF81F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define BRRED            0XFC07
#define LGRAY            0XC618
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAYBLUE        0XA651 //浅灰蓝色
#define LBBLUE           0X2B12 //浅棕蓝色

#define RGB888_565(r,g,b) ((UINT16)((((UINT16)(r)<<8)&0xF800)|(((UINT16)(g)<<3)&0x7E0)|(((UINT16)(b) >> 3))))



// #define LCD_SCK_Clr() (LCD_SCK=0)
// #define LCD_SCK_Set() (LCD_SCK=1)

// #define LCD_MOSI_Clr() (LCD_MOSI=0)
// #define LCD_MOSI_Set() (LCD_MOSI=1)

#define LCD_RES_Clr()  (LCD_RES=0)
#define LCD_RES_Set()  (LCD_RES=1)

#define LCD_DC_CMD()   (LCD_DC=LCD_CMD)
#define LCD_DC_DATA()   (LCD_DC=LCD_DATA)

#define LCD_BLK_Clr()  (LCD_BLK=0)
#define LCD_BLK_Set()  (LCD_BLK=1)

#define LCD_CS_SEL()  (LCD_CS=LCD_CS_POL)
#define LCD_CS_DSEL()  (LCD_CS=(!LCD_CS_POL))

struct LCD_parameter_struct{
	int width;
	int height;
	UINT16 color;
	UINT16 Background;
	UINT8 font;
	UINT8 dir;
};
extern struct LCD_parameter_struct LCD_parameter;

//LCD函数定义
void LCD_init(void);        //LCD初始化
void LCD_writeByte(UINT8 data);  //写入一个字节
void LCD_writeHalfword(UINT16 data);  //写入两个字节
void LCD_writeCmd(UINT8 cmd);    //写入一个指令
void LCD_setAddrWindow(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1);  //设置坐标函数
void LCD_setDir(UINT8 dir);

void LCD_setColor(UINT16 color);			//设置前景颜色
void LCD_setBackground(UINT16 color);		//设置背景颜色
void LCD_setColorRGB(UINT8 r,UINT8 g,UINT8 b);
void LCD_setBackgroundRGB(UINT8 r,UINT8 g,UINT8 b);
void LCD_setFont(UINT8 font);				//设置字体
void LCD_fill(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1);  //指定区域填充前景颜色
void LCD_clear(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1);	 //指定区域填充背景颜色
void LCD_drawPixel(UINT16 x,UINT16 y);                        //在指定位置画一个点
void LCD_drawLine(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1);         //在指定位置画一条线
void LCD_drawRectangle(UINT16 x0, UINT16 y0, UINT16 x1, UINT16 y1); //在指定位置画一个矩形
void LCD_drawCircle(UINT16 x0,UINT16 y0,UINT8 r);                   //在指定位置画一个圆
void LCD_fillCircle(int x, int y, int radius);				//在指定位置画一个实心圆
void LCD_fillSemiCircle(int x0, int y0, int r, UINT8 cornername,int delta);
void LCD_showChar(UINT16 x,UINT16 y,UINT8 num,UINT8 overlay);//显示一个字符
void LCD_showString(UINT16 x,UINT16 y,const UINT8 *p,UINT8 overlay);//显示字符串

#endif