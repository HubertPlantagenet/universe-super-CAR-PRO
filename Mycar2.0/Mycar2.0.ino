#define PT_USE_TIMER
#include <FlexiTimer2.h> //定时器库
#include<pt.h>
#include"Move.h"
/*

Github 版本


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
#define time1 1
#define time2 5
unsigned Turn_time_A = 800;
unsigned Turn_time_D = 700;

Car Mycar;              //只在源文件
static struct pt pt1, pt2;
pt_timer servotimer1;
pt_timer servotimer2;

class Turn  // 转向相关
{
public:
	Turn();
	~Turn();
	byte direction;  //转向方向
	unsigned int time;
private:

};

Turn::Turn()
{
	direction = 0;
	time = 1000;
}

Turn::~Turn()
{
}
Turn turn;

//绘蓝杯寻迹转向函数
	 /*void ninty_turn(u8 direction, u8 time)
{

}*/
//直角转向函数  direction方向 time 转的时间

static int mission1(struct pt *pt)
{
	PT_BEGIN(pt);  //线程开始
	while (1)
	{
		//线程循环开始
		Mycar.ch = ' ';  //每次循环初始化 ch 
		Mycar.ch2 = ' ';  //每次循环初始化 ch2 
//		Serial1.println("MOVE");
		if (Serial1.available())
			Mycar.ch = Serial1.read();
		if (Serial2.available())
		{
	//		Serial1.println("Receive from Serial2");
			// test 部分  Mycar.ch2 用来接收无线通信的指令
			Mycar.ch2 = Serial2.read();
			Serial1.print("ch2 = ");
			Serial1.println(Mycar.ch2);
		}
		PT_YIELD(pt);
		if (Mycar.ch == ' ')
			continue;
		//if (Mycar.ch2 != ' ')
		//{

		//}
		if (Mycar.ch == '!')
		{
			Mycar.Stop();
		}
		if (Mycar.ch == 'i')  // 字符i 用来切换至控制寻迹模式
		{
			Mycar.ChangeMode(FIND);
			continue;
		}
		if (Mycar.ch == 'm')  //字符'm'用来切换到遥控模式
		{
			Mycar.ChangeMode(MOVE);
			continue;
		}
		if (Mycar.ch == 'q')  //字符 q 用来切换至Set模式
		{
			Mycar.ChangeMode(SET);
			continue;
		}
		PT_YIELD(pt);
		if (Mycar.mode == SET)   //若当前处于 Set模式
		{
			ChoiceByset();
			continue;
		}
		if (Mycar.mode == MOVE)  //若当前不处于 AI模式
		{
			if (Mycar.ch != ' ')
				Serial1.println(Mycar.ch);
			//////////////////////////////
			{
				switch (Mycar.ch)
				{
				case 'L':	//亮灯 
				{
					if (Mycar.RGB_LED == true)
					{
						Mycar.LED_on_off(OFF);
						Mycar.RGB_LED = false;
					}
					else
					{
						Mycar.LED_on_off(ON);
						Mycar.RGB_LED = true;
					}
				} break;
				case 'W':	//前进
				{
					Mycar.GO(1);
					Serial1.println("GO1");
				} break;
				case 'w':	//停
				{
					Mycar.Stop();
				}break;
				case 'S':	//后退
				{
					Mycar.GO(2);
				} break;
				case 's':	//停
				{
					Mycar.Stop();
				}break;
				case 'A':	//左转
				{
					Mycar.Turn_in_situ(Left_turn);
				} break;
				case 'a':	//调回左右轮正转
				{
					Mycar.Turn_in_situ(3);
				}break;
				case 'D':	//右转
				{
					Mycar.Turn_in_situ(Right_turn);
				} break;
				case 'd':	//调回左右轮正转
				{
					Mycar.Turn_in_situ(3);
				}break;
				// 控速部分
				case 'P':  //右轮速度  加
				{
					Mycar.AddSpeedR();
					Mycar.GetSpeed();
				} break;
				case 'M':  //右轮速度  减
				{
					Mycar.ReduceSpeedR();
					Mycar.GetSpeed();
				} break;
				case 'O':  //左轮速度  加
				{
					Mycar.AddSpeedL();
					Mycar.GetSpeed();
				} break;
				case 'K':  //左轮速度  减
				{
					Mycar.ReduceSpeedL();
					Mycar.GetSpeed();
				} break;
				case '+':  //整体速度  加
				{
					Mycar.AddSpeedL();
					Mycar.AddSpeedR();
					Mycar.GetSpeed();
				} break;
				case '-':  //整体速度  减
				{
					Mycar.ReduceSpeedL();
					Mycar.ReduceSpeedR();
					Mycar.GetSpeed();
				} break;
				case '#':	//获取当前速度
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
			continue;
		}
		if (Mycar.GetMode() == FIND)
		{
			//绘蓝杯寻迹部分
			//test 部分
			/*if (Mycar.ch == 'A')
			{
				Mycar.Turn_in_situ(Left_turn);
				Serial1.println("Left Turn_time _ begin");
				PT_TIMER_DELAY(pt, Turn_time_A);
				Mycar.Stop();
				Serial1.println("Turn_time Time out");
				continue;
			}
			if (Mycar.ch == 'D')
			{
				Mycar.Turn_in_situ(Right_turn);
				Serial1.println("Right Turn_time _ begin");
				PT_TIMER_DELAY(pt, Turn_time_D);
				Mycar.Stop();
				Serial1.println("Turn_time Time out");
				continue;
			}
			if (Mycar.ch == '+')
			{
				Turn_time_A += 100;
				Turn_time_D += 100;
				Serial1.print("Turn_time = ");
				Serial1.print(Turn_time_A);
				Serial1.println(Turn_time_D);
				continue;
			}
			if (Mycar.ch == '-')
			{
				Turn_time_A -= 100;
				Turn_time_D -= 100;
				Serial1.print("Turn_time = ");
				Serial1.print(Turn_time_A);
				Serial1.println(Turn_time_D);
				continue;
			}*/ 


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
		if (Mycar.RGB_LED == true)
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
		else
		{
			analogWrite(13, 0);
			analogWrite(12, 0);
			analogWrite(11, 0);
			PT_YIELD(pt);
		}
	}
	PT_END(pt);    //线程结束
}


void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial1.begin(9600);   //设置蓝牙通讯波特率
	Serial2.begin(9600);   //设置无线通讯的波特率
	FlexiTimer2::set(750, 1.0 / 1000, Return_ch); //0.75秒 打印一次当前的Mycar.ch
//	FlexiTimer2::start();
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
	Serial1.print("mode = ");
	if (Mycar.mode == 3)
	{
		Serial1.println("MOVE");
		return;
	}
	if (Mycar.mode == 4)
	{
		Serial1.println("FIND");
		return;
	}
	if (Mycar.mode == 5)
	{
		Serial1.println("SET");
		return;
	}
	//	byte j = Mycar.GetMode;
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