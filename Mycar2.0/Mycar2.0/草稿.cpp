#define PT_USE_TIMER
#include <FlexiTimer2.h> //定时器库
#include<pt.h>
#include"Move.h"
/*
#define ENA 5   //使能控制  紫
#define ENB 6   //控速      红
#define IN1 46  //控方向    灰  白  黑 棕
#define IN2 48  //          白
#define IN3 50  //          黑
#define IN4 52  //          棕
#define LED 3


RGB_LED ---------- 接线  11 12 13  GND
*/
/*
/////////////////////////////命令//////////////////////////////
W/w  前进 （按下W前进 然后等待w命令停止  WASD L 下同）
S/s  后退  A/a  D/d  左右    （可能存在接线误差 具体可在上位机调试）
L/l  打开关闭指示灯
i    打开关闭 AI状态
q    打开关闭 set状体  set状态用以设定速度（目前）
P M    右轮加速减速
O K    左轮加速减速
+ -    整体加速减速
#      获得当前速度
*/
#define u8 unsigned char
#define ON   HIGH
#define OFF  LOW
#define Left_turn 1
#define Right_turn 2
#define FindLEFT3   31
#define FindLEFT2  33
#define FindLEFT1  35
#define FindRIGHT1  37
#define FindRIGHT2  39
#define FindRIGHT3  41
#define time1 1
#define time2 5

static Car Mycar;              //只在源文件
static struct pt pt1, pt2;
pt_timer servotimer1;
pt_timer servotimer2;

static int mission1(struct pt *pt)
{
	PT_BEGIN(pt);  //线程开始
	while (1)
	{
		//线程循环开始
		Mycar.ch = ' ';  //每次循环初始化 ch 
		if (Serial1.available())
			Mycar.ch = Serial1.read();
		if (Mycar.ch == 'i')  // 字符i 用来切换至控制寻迹模式
		{
			Mycar.ChangeMode(FIND);
			return;
		}
		if (Mycar.ch == 'm')  //字符'm'用来切换到遥控模式
		{
			Mycar.ChangeMode(MOVE);
			return;
		}
		if (Mycar.ch == 'q')  //字符 q 用来切换至Set模式
		{
			Mycar.ChangeMode(SET);
			return;
		}
		PT_YIELD(pt);
		if (Mycar.GetMode() == SET)   //若当前处于 Set模式
		{
			ChoiceByset();
			return;
		}
		if (Mycar.GetMode() == MOVE)  //若当前不处于 AI模式
		{
			//////////////////////////////
			{
				switch (Mycar.ch)
				{
				case 'L':
				{
					Mycar.LED_on_off(ON);
					/*while (Mycar.ch != 'l')
					{
					if (Serial1.available())
					Mycar.ch = Serial1.read();
					}
					Mycar.LED_on_off(OFF);*/
				} break;
				case 'l':
				{
					Mycar.LED_on_off(OFF);
				}break;
				case 'W':
				{
					Mycar.GO(1);
					/*while (Mycar.ch != 'w')
					{
					Mycar.GO(1);
					if (Serial1.available())
					Mycar.ch = Serial1.read();
					}
					Mycar.Stop();*/
				} break;
				case 'w':
				{
					Mycar.Stop();
				}break;
				case 'S':
				{
					while (Mycar.ch != 's')
					{
						Mycar.GO(2);
						if (Serial1.available())
							Mycar.ch = Serial1.read();
					}
					Mycar.Stop();
				} break;
				case 'A':
				{
					while (Mycar.ch != 'a')
					{
						Mycar.Turn_in_situ(Left_turn);
						if (Serial1.available())
							Mycar.ch = Serial1.read();
					}
					Mycar.Stop();
				} break;
				case 'D':
				{
					while (Mycar.ch != 'd')
					{
						Mycar.Turn_in_situ(Right_turn);
						if (Serial1.available())
							Mycar.ch = Serial1.read();
					}
					Mycar.Stop();
				} break;
				// 控速部分
				case 'P':  //右轮速度  加
				{
					Mycar.AddSpeedR();
				} break;
				case 'M':  //右轮速度  减
				{
					Mycar.ReduceSpeedR();
				} break;
				case 'O':  //左轮速度  加
				{
					Mycar.AddSpeedL();
				} break;
				case 'K':  //左轮速度  减
				{
					Mycar.ReduceSpeedL();
				} break;
				case '+':  //整体速度  加
				{
					Mycar.AddSpeedL();
					Mycar.AddSpeedR();
				} break;
				case '-':  //整体速度  减
				{
					Mycar.ReduceSpeedL();
					Mycar.ReduceSpeedR();
				} break;
				case '#':
				{
					Mycar.GetSpeed();
				} break;
				default:
					break;
				}
			}
			//////////////////////////////
			//  delay(300);
			//	Mycar.Stop();
			return;
		}
		if (Mycar.GetMode() == FIND)
		{
			//绘蓝杯寻迹部分

		}
	}//线程循环结束
	PT_END(pt);    //线程结束
}
static int mission2(struct pt *pt)
{
	PT_BEGIN(pt);  //线程开始
	static byte i;
	while (1)
	{
		for (i = 0; i < 255; i++)
		{
			analogWrite(13, i);
			PT_TIMER_DELAY(pt, time2);
		}
		PT_TIMER_DELAY(pt, time1);
		for (i = 0; i < 255; i++)
		{
			analogWrite(13, 255 - i);
			analogWrite(12, i);
			PT_TIMER_DELAY(pt, time2);
		}
		PT_TIMER_DELAY(pt, time1);
		for (i = 0; i < 255; i++)
		{
			analogWrite(12, 255 - i);
			analogWrite(11, i);
			PT_TIMER_DELAY(pt, time2);
		}
		PT_TIMER_DELAY(pt, time1);
		for (i = 0; i < 255; i++)
		{
			analogWrite(12, i);
			analogWrite(13, i);
			PT_TIMER_DELAY(pt, time2);
		}
		PT_TIMER_DELAY(pt, time1);
		for (i = 0; i < 255; i++)
		{
			analogWrite(12, 255 - i);
			analogWrite(13, 255 - i);
			analogWrite(11, 255 - i);
			PT_TIMER_DELAY(pt, time2);
		}
	}
	PT_END(pt);    //线程结束
}


void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial1.begin(9600);   //设置蓝牙通讯波特率
	FlexiTimer2::set(750, 1.0 / 1000, Return_ch); //0.75秒 打印一次当前的Mycar.ch
	FlexiTimer2::start();
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	digitalWrite(13, LOW); digitalWrite(12, LOW); digitalWrite(11, LOW);
	PT_INIT(&pt1);
	PT_INIT(&pt2);  //两个线程初始化
}
void Return_ch()    //返回并打印 Mycar.ch
{
	Serial1.print("ch = ");
	Serial1.println(Mycar.ch);
}
void ChoiceByset()
{
	if (Serial1.available())
	{
		Mycar.ch = Serial1.read();
		Mycar.SetSpeed(Mycar.ch);
		Mycar.ChangeMode(MOVE);
	}
}

void loop() { //主函数主循环
			  // put your main code here, to run repeatedly:
	mission1(&pt1);
	mission2(&pt2);
}