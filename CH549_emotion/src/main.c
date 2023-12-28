/********************************************************************
    @file    main.c
    @author  Maggie <maggie_mayu@verimake.com>,Benue <benuelin@verimake.com>
    @version 1.0.0
    @date    2022-03-18
    @brief See https://verimake.com/d/167-51adc-ch549
  ******************************************************************
**/

#include <CH549_sdcc.h>   //ch549的头文件，其中定义了单片机的一些特殊功能寄存器
#include <CH549_LCD.h>
#include <math.h>
#include <CH549_SPI.h>
#include <CH549_ADC.h>
#include <CH549_DEBUG.h>

/*****************************************************
 * 使用 ILI9225 176*220 LCD,
 * LCD 引脚等配置见 CH549_LCD.h
 * 也可以更改配置，使用 ST7789 LCD
 * 教程见 https://verimake.com/d/167-51adc-ch549
*/
#define ADC_CH 1				//ADC 通道,通道 1 为 P1_1
#define ADCMAX 4096				//ADC 最大采样值
#define ADC2MOOD (72.0/ADCMAX)	//ADC 到心情值的转换系数，
#define MOUTHARC 0.0004			//嘴巴弧度
#define MOUTH_AMPLITUDE 0.002	//嘴巴上下摆动幅度
#define MOUTH_Y 0.35			//嘴巴中心高
#define MOUTH_X (LCD_parameter.width/2)	//嘴巴中心横坐标

// 脸，眼，嘴的颜色，括号内顺序为 R,G,B
#define FACE_COLOR (RGB888_565(252, 194, 27))
#define EYE_COLOR (RGB888_565(47, 47, 47))
#define MOUTH_COLOR (RGB888_565(47, 47, 47))

//求绝对值
#define ABS(x) ((x)>0?(x):-(x))

/*画脸函数*/
void showFace(void)
{
	UINT16 rFace =LCD_parameter.height *2 / 5;      //脸对应的圆的半径
	UINT16 xFace = (LCD_parameter.width) / 2;       //脸对应圆的圆心x轴坐标
	UINT16 yFace = (LCD_parameter.height) / 2;      //y轴坐标
	LCD_setColor(FACE_COLOR);                		//设置脸RGB颜色设定
	LCD_fillCircle(xFace, yFace, rFace);       		//画脸(x坐标,y坐标,半径)

	UINT16 rEye = rFace / 7 ;   					//眼睛对应圆的半径
	UINT16 xEyeOffset = rFace/3;    				//眼睛x轴偏移
	UINT16 yEye = yFace + rFace/4;     				//眼睛y轴坐标
	LCD_setColor(EYE_COLOR);                   		//眼睛RGB颜色
	LCD_fillCircle(xFace+xEyeOffset, yEye, rEye);	//画右眼
	LCD_fillCircle(xFace-xEyeOffset, yEye, rEye);	//画左眼
}

int mouthCurve(int x,int mood) {
	float a = MOUTHARC*mood;								//嘴巴弧度
	int h = LCD_parameter.height*(MOUTH_Y-MOUTH_AMPLITUDE*mood);	//嘴巴顶点y
  	x -= MOUTH_X ;					//嘴巴顶点x
  	return  (a * x * x + h);
}

int getADC(UINT8 ch){
  	ADC_ChSelect(ch);
	ADC_StartSample();                 //启动采样
	while((ADC_CTRL&bADC_IF) == 0);    //查询等待标志置位
	ADC_CTRL = bADC_IF;                //清标志
	return ADC_DAT;                    //输出ADC采样值
}

//主函数
void main()
{
	CfgFsys();        		//单片机主频配置

	SPIMasterModeSet(3);    //SPI 主机模式设置
	SPI_CK_SET(2);         	//设置 SPI 分频
	LCD_init();            	//初始化LCD
	LCD_setDir(3);			//屏幕显示方向 目前(库版本0.1.1)仅对 ILI9225 有效

	ADC_ExInit( 3 ); 		//初始化 ADC
	
	LCD_setColor(WHITE);
	LCD_fill(0, 0, LCD_parameter.width-1, LCD_parameter.height-1); //屏幕填充白色
	showFace();				//画出脸和眼睛

	int lastMood= 0;
	while (1) {
		int mood;

		mood=(getADC(ADC_CH)-ADCMAX/2) * ADC2MOOD;
		// 画嘴巴
		if(ABS(mood - lastMood)>1){	// 心情波动超过 1 时才刷新
			int x;
			// 擦除以前的嘴
			LCD_setColor(FACE_COLOR);
			for (x = MOUTH_X - ABS(lastMood); x <= MOUTH_X + ABS(lastMood); x++)
			{
					int y =mouthCurve(x,lastMood);
					LCD_fill(x,y,x,y+3);
			}

			lastMood = mood;
			// 根据心情画现在的嘴
			LCD_setColor(MOUTH_COLOR);
			for (x = MOUTH_X - ABS(mood); x <= MOUTH_X + ABS(mood); x++)
			{
					int y =mouthCurve(x,mood);
					LCD_fill(x,y,x,y+3);
			}
			mDelaymS(50);	
		}
	}
}






