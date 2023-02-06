/**
  ******************************************************************
  * @file    CH549_LCD.c
  * @author  Daniel Wu, Yujun Wu,Benue
  * @version 0.1.1
  * @date    2022-03-16
  * @brief
  * @note 	 Thanks for LCDWIKI@github 
  ******************************************************************
**/

#include <CH549_LCDFONT.h>
#include <CH549_LCD.h>
#include <CH549_SPI.h>
#include <CH549_DEBUG.h>
#include <CH549_sdcc.h>	

#define TFTLCD_DELAY16  0xFFFF

#define SWAP_HW(a, b) do{ int t = (a); (a) = (b); (b) = t; }while(0)

struct LCD_parameter_struct LCD_parameter ={LCD_W,LCD_H,WHITE,BLACK,8,0};




#if LCD_MODEL == LCD_ST7789
/******************************************************************************
      函数说明：设置读写起始和结束地址
      入口数据：x1,x1 设置列的起始和结束地址
                y0,y1 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_setAddrWindow(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1)
{
		LCD_writeCmd(0x2a);//列地址设置
		LCD_writeHalfword(x0);
		LCD_writeHalfword(x1);
		LCD_writeCmd(0x2b);//行地址设置
		LCD_writeHalfword(y0);
		LCD_writeHalfword(y1);
		LCD_writeCmd(0x2c);//储存器写
}

/******************************************************************************
      函数说明：LCD初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_init(void)
{

	LCD_RES_Clr();
	mDelaymS(20);
	LCD_RES_Set();
	mDelaymS(20);
	LCD_BLK_Set();
	mDelaymS(20);
	//************* Start Initial Sequence **********//
	LCD_writeCmd(0x11); //Sleep out 
	mDelaymS(20);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	LCD_writeCmd(0x36);
	LCD_writeByte(0x00);

	LCD_writeCmd(0x3A); 
	LCD_writeByte(0x05);

	LCD_writeCmd(0xB2);
	LCD_writeByte(0x0C);
	LCD_writeByte(0x0C);
	LCD_writeByte(0x00);
	LCD_writeByte(0x33);
	LCD_writeByte(0x33); 

	LCD_writeCmd(0xB7); 
	LCD_writeByte(0x35);  

	LCD_writeCmd(0xBB);
	LCD_writeByte(0x19);

	LCD_writeCmd(0xC0);
	LCD_writeByte(0x2C);

	LCD_writeCmd(0xC2);
	LCD_writeByte(0x01);

	LCD_writeCmd(0xC3);
	LCD_writeByte(0x12);   

	LCD_writeCmd(0xC4);
	LCD_writeByte(0x20);  

	LCD_writeCmd(0xC6); 
	LCD_writeByte(0x0F);    

	LCD_writeCmd(0xD0); 
	LCD_writeByte(0xA4);
	LCD_writeByte(0xA1);

	LCD_writeCmd(0xE0);
	LCD_writeByte(0xD0);
	LCD_writeByte(0x04);
	LCD_writeByte(0x0D);
	LCD_writeByte(0x11);
	LCD_writeByte(0x13);
	LCD_writeByte(0x2B);
	LCD_writeByte(0x3F);
	LCD_writeByte(0x54);
	LCD_writeByte(0x4C);
	LCD_writeByte(0x18);
	LCD_writeByte(0x0D);
	LCD_writeByte(0x0B);
	LCD_writeByte(0x1F);
	LCD_writeByte(0x23);

	LCD_writeCmd(0xE1);
	LCD_writeByte(0xD0);
	LCD_writeByte(0x04);
	LCD_writeByte(0x0C);
	LCD_writeByte(0x11);
	LCD_writeByte(0x13);
	LCD_writeByte(0x2C);
	LCD_writeByte(0x3F);
	LCD_writeByte(0x44);
	LCD_writeByte(0x51);
	LCD_writeByte(0x2F);
	LCD_writeByte(0x1F);
	LCD_writeByte(0x1F);
	LCD_writeByte(0x20);
	LCD_writeByte(0x23);
	LCD_writeCmd(0x21); 

	LCD_writeCmd(0x29); 
} 
#endif
#if LCD_MODEL == LCD_ILI9225

const UINT16 ILI9225_regValues[] = 
{
	0x01, 0x011C,
	0x02, 0x0100,	
	0x03, 0x1030,
	0x08, 0x0808, // set BP and FP
	0x0B, 0x1100, // frame cycle
	0x0C, 0x0000, // RGB interface setting R0Ch=0x0110 for RGB 18Bit and R0Ch=0111for RGB16Bit
	0x0F, 0x1401, // Set frame rate----0801
	0x15, 0x0000, // set system interface
	0x20, 0x0000, // Set GRAM Address
	0x21, 0x0000, // Set GRAM Address
	//*************Power On sequence ****************//
	TFTLCD_DELAY16, 50, // delay 50ms
	0x10, 0x0800, // Set SAP,DSTB,STB----0A00
	0x11, 0x1F3F, // Set APON,PON,AON,VCI1EN,VC----1038
	TFTLCD_DELAY16, 50, // delay 50ms
	0x12, 0x0121, // Internal reference voltage= Vci;----1121
	0x13, 0x006F, // Set GVDD----0066
	0x14, 0x4349, // Set VCOMH/VCOML voltage----5F60
	//-------------- Set GRAM area -----------------//
	0x30, 0x0000,
	0x31, 0x00DB,
	0x32, 0x0000,
	0x33, 0x0000,
	0x34, 0x00DB,
	0x35, 0x0000,
	0x36, 0x00AF,
	0x37, 0x0000,
	0x38, 0x00DB,
	0x39, 0x0000,
	// ----------- Adjust the Gamma Curve ----------//
	0x50, 0x0001, // 0x0400
	0x51, 0x200B, // 0x060B
	0x52, 0x0000, // 0x0C0A
	0x53, 0x0404, // 0x0105
	0x54, 0x0C0C, // 0x0A0C
	0x55, 0x000C, // 0x0B06
	0x56, 0x0101, // 0x0004
	0x57, 0x0400, // 0x0501
	0x58, 0x1108, // 0x0E00
	0x59, 0x050C, // 0x000E
	TFTLCD_DELAY16, 50, // delay 50ms
	0x07, 0x1017,
	0x22, 0x0000,
};

void LCD_WriteReg(UINT8 cmd, UINT16 d)
{
	LCD_writeCmd(cmd);
	LCD_writeHalfword(d);
}

void LCD_init()
{
	int size = sizeof(ILI9225_regValues);

	LCD_RES_Clr();
	mDelaymS(20);
	LCD_RES_Set();
	mDelaymS(20);
	LCD_BLK_Set();
	mDelaymS(20);

    UINT16 *p = (UINT16 *) ILI9225_regValues;
    while (size > 0) 
	{
        UINT16 cmd = *p++;
        UINT16 d = *p++;
        if (cmd == TFTLCD_DELAY16)
        {
            mDelaymS(d);
        }
        else 
		{
			LCD_writeCmd(cmd);
			LCD_writeHalfword(d);
		}
        size -= 2 * sizeof(int);
    }
}

/******************************************************************************
      函数说明：设置读写起始和结束地址
      入口数据：x1,x1 设置列的起始和结束地址
                y0,y1 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_setAddrWindow(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1)
{
	int x, y, t;
	switch(LCD_parameter.dir) 
	{
		default:
			x  = x0;
			y  = y0;
			break;
		case 1:
			t  = y0;
			y0 = x0;
			x0 = LCD_W  - 1 - y1;
			y1 = x1;
			x1 = LCD_W  - 1 - t;
			x  = x1;
			y  = y0;
			break;
		case 2:
			t  = x0;
			x0 = LCD_W  - 1 - x1;
			x1 = LCD_W  - 1 - t;
			t  = y0;
			y0 = LCD_H - 1 - y1;
			y1 = LCD_H - 1 - t;
			x  = x1;
			y  = y1;
			break;
		case 3:
			t  = x0;
			x0 = y0;
			y0 = LCD_H - 1 - x1;
			x1 = y1;
			y1 = LCD_H - 1 - t;
			x  = x0;
			y  = y1;
			break;
	}
	LCD_writeCmd(0x36);//列地址设置
	LCD_writeHalfword(x1);
	LCD_writeCmd(0x37);//列地址设置
	LCD_writeHalfword(x0);
	LCD_writeCmd(0x38);//行地址设置
	LCD_writeHalfword(y1);
	LCD_writeCmd(0x39);//行地址设置
	LCD_writeHalfword(y0);
	LCD_writeCmd(0x20);
	LCD_writeHalfword(x);
	LCD_writeCmd(0x21);
	LCD_writeHalfword(y);
	LCD_writeCmd(0x22);//储存器写
}

void LCD_setDir(UINT8 dir)
{
    LCD_parameter.dir = dir & 3;           // just perform the operation ourselves on the protected variables
    LCD_parameter.width = (LCD_parameter.dir & 1) ? LCD_H : LCD_W;
    LCD_parameter.height = (LCD_parameter.dir & 1) ? LCD_W : LCD_H;
	UINT16 val;
	switch(LCD_parameter.dir) 
	{
		case 0: 
			val = 0x1030; //0 degree 
			break;
		case 1: 
			val = 0x1028; //90 degree 
			break;
		case 2: 
			val = 0x1000; //180 degree 
			break;
		case 3: 
			val = 0x1018; //270 degree 
			break;
	}
	
	LCD_writeCmd(0x03);
	LCD_writeHalfword(val);
	//Vert_Scroll(0, HEIGHT, 0);
}
#endif
/* ------------------------------------------- LCD相关函数 -------------------------------------------*/



void LCD_setColor(UINT16 color){
	LCD_parameter.color = color;
}
void LCD_setBackground(UINT16 color){
	LCD_parameter.Background = color;
}

void LCD_setColorRGB(UINT8 r,UINT8 g,UINT8 b){
	LCD_parameter.color = RGB888_565(r,g,b); 
}
void LCD_setBackgroundRGB(UINT8 r,UINT8 g,UINT8 b){
	LCD_parameter.Background = RGB888_565(r,g,b);
}
void LCD_setFont(UINT8 font){
	LCD_parameter.font = font;
}
/******************************************************************************
      函数说明：在指定区域填充背景颜色
      入口数据：x0,y0   起始坐标
                x1,y1   终止坐标
      返回值：  无
******************************************************************************/
void LCD_clear(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1)
{          
	UINT32 cnt;
	if (x0 > x1)SWAP_HW(x0,x1);
	if (y0 > y1)SWAP_HW(y0,y1);

	LCD_setAddrWindow(x0,y0,x1,y1);
	cnt = (x1-x0+1)*(y1-y0+1);								   	 	
	for(;cnt != 0;cnt--)
	{
		LCD_writeHalfword(LCD_parameter.Background);
	} 					  	    
}

//fill a circle,thx for LCDWIKI
void LCD_fillCircle(int x, int y, int radius)
{
	LCD_fill(x, y-radius,x, y+radius+1);
	LCD_fillSemiCircle(x, y, radius, 3, 0);
}

//fill a semi-circle,thx for LCDWIKI
void LCD_fillSemiCircle(int x0, int y0, int r, UINT8 cornername,int delta)
{
	int f     = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x     = 0;
	int y     = r;

	while (x<y) 
	{
    	if (f >= 0) 
		{
      		y--;
      		ddF_y += 2;
      		f += ddF_y;
    	}
    	x++;
    	ddF_x += 2;
    	f += ddF_x;

    	if (cornername & 0x1) 
		{
      		LCD_fill(x0+x, y0-y,x0+x, y0+y+1+delta);
      		LCD_fill(x0+y, y0-x,x0+y, y0+x+1+delta);
    	}
    	if (cornername & 0x2) 
		{
      		LCD_fill(x0-x, y0-y, x0-x, y0+y+1+delta);
      		LCD_fill(x0-y, y0-x, x0-y, y0+x+1+delta);
    	}
  	}
}


/******************************************************************************
      函数说明：LCD 写入1字节
      入口数据：data 写入的数据
      返回值：  无
******************************************************************************/
void LCD_writeByte(UINT8 data)
{
	LCD_CS_SEL();
	CH549SPIMasterWrite(data);       //使用CH549的SPI写入1字节数据
	LCD_CS_DSEL();
}

/******************************************************************************
      函数说明：LCD 写入半字
      入口数据：data 写入的数据
      返回值：  无
******************************************************************************/
void LCD_writeHalfword(UINT16 data)
{
	LCD_writeByte(data>>8);
	LCD_writeByte(data);
}

/******************************************************************************
      函数说明：LCD写入命令
      入口数据：cmd 写入的命令
      返回值：  无
******************************************************************************/
void LCD_writeCmd(UINT8 cmd)
{
	LCD_DC_CMD();//写命令
	LCD_writeByte(cmd);
	LCD_DC_DATA();//写数据
}

/******************************************************************************
      函数说明：在指定区域填充前景颜色
      入口数据：x0,y0   起始坐标
                x1,y1   终止坐标
      返回值：  无
******************************************************************************/
void LCD_fill(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1)
{   
	UINT32 cnt;
	if (x0 > x1)SWAP_HW(x0,x1);
	if (y0 > y1)SWAP_HW(y0,y1);

	LCD_setAddrWindow(x0,y0,x1,y1);
	cnt = (x1-x0+1)*(y1-y0+1);								   	 	
		for(;cnt != 0;cnt--)
		{
			LCD_writeHalfword(LCD_parameter.color);
		} 
}


/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
      返回值：  无
******************************************************************************/
void LCD_drawPixel(UINT16 x,UINT16 y)
{
	LCD_setAddrWindow(x,y,x,y);//设置光标位置 
	LCD_writeHalfword(LCD_parameter.color);
} 

/******************************************************************************
      函数说明：画线
      入口数据：x0,y0   起始坐标
                x1,y1   终止坐标
      返回值：  无
******************************************************************************/
void LCD_drawLine(UINT16 x0,UINT16 y0,UINT16 x1,UINT16 y1)
{
	UINT16 t; 
	int xErr=0,yErr=0,dx,dy,dist;
	int incX,incY,x,y;
	dx=x1-x0; //计算坐标增量 
	dy=y1-y0;
	x=x0;//画线起点坐标
	y=y0;
	if(dx>0)incX=1; //设置单步方向 
	else if (dx==0)incX=0;//垂直线 
	else {incX=-1;dx=-dx;}
	if(dy>0)incY=1;
	else if (dy==0)incY=0;//水平线 
	else {incY=-1;dy=-dy;}
	if(dx>dy)dist=dx; //选取基本增量坐标轴 
	else dist=dy;
	for(t=0;t<dist+1;t++)
	{
		LCD_drawPixel(x,y);//画点
		xErr+=dx;
		yErr+=dy;
		if(xErr>dist)
		{
			xErr-=dist;
			x+=incX;
		}
		if(yErr>dist)
		{
			yErr-=dist;
			y+=incY;
		}
	}
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y0   起始坐标
                x1,y1   终止坐标
      返回值：  无
******************************************************************************/
void LCD_drawRectangle(UINT16 x0, UINT16 y0, UINT16 x1, UINT16 y1)
{
	LCD_drawLine(x0,y0,x1,y0);
	LCD_drawLine(x0,y0,x0,y1);
	LCD_drawLine(x0,y1,x1,y1);
	LCD_drawLine(x1,y0,x1,y1);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
      返回值：  无
******************************************************************************/
void LCD_drawCircle(UINT16 x0,UINT16 y0,UINT8 r)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_drawPixel(x0-b,y0-a);             //3           
		LCD_drawPixel(x0+b,y0-a);             //0           
		LCD_drawPixel(x0-a,y0+b);             //1                
		LCD_drawPixel(x0-a,y0-b);             //2             
		LCD_drawPixel(x0+b,y0+a);             //4               
		LCD_drawPixel(x0+a,y0-b);             //5
		LCD_drawPixel(x0+a,y0+b);             //6 
		LCD_drawPixel(x0-b,y0+a);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}


//////////////////////////////////////////////////////////



/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                overlay:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_showChar(UINT16 x,UINT16 y,UINT8 num,UINT8 overlay)
{
	UINT8 temp,fontWidth,t,m=0;
	UINT16 i,TypefaceNum;//一个字符所占字节大小
	UINT16 x0=x;
	fontWidth=LCD_parameter.font/2;
	TypefaceNum=(fontWidth/8+((fontWidth%8)?1:0))*LCD_parameter.font;
	num=num-' ';    //得到偏移后的值
	LCD_setAddrWindow(x,y,x+fontWidth-1,y+LCD_parameter.font-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		switch (LCD_parameter.font)
		{
		case 12:temp=ascii_1206[num][i];break;
		case 16:temp=ascii_1608[num][i];break;
		case 24:temp=ascii_2412[num][i];break;
		case 32:temp=ascii_3216[num][i];break;
		default:return;
		}
		for(t=0;t<8;t++)
		{
			if(!overlay)//非叠加模式
			{
				if(temp&(0x01<<t))LCD_writeHalfword(LCD_parameter.color);
				else LCD_writeHalfword(LCD_parameter.Background);
				m++;
				if(m%fontWidth==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))LCD_drawPixel(x,y);//画一个点
				x++;
				if((x-x0)==fontWidth)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                overlay:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_showString(UINT16 x,UINT16 y,char *p,UINT8 overlay)
{         
	while(*p!='\0')
	{       
		LCD_showChar(x,y,*p,overlay);
		x+=LCD_parameter.font/2;
		p++;
	}  
}

/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组    
      返回值：  无
******************************************************************************/
void LCD_showPicture(UINT16 x,UINT16 y,UINT16 length,UINT16 width,UINT8 pic[])
{
	UINT16 i,j;
	UINT32 k=0;
	LCD_setAddrWindow(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_writeByte(pic[k*2]);
			LCD_writeByte(pic[k*2+1]);
			k++;
		}
	}
}
