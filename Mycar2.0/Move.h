
#pragma once
//Move.h
#ifndef __Move
#define __Move

#include<Arduino.h>
#define u8 unsigned char
#define ON   HIGH
#define OFF  LOW
#define Mode byte
#define MOVE 3
#define FIND 4
#define SET 5

class Car
{
private:
	//ENA  使能控制  紫
	//ENB  控速      红
	//IN1  控方向    灰  白  黑 棕
	//IN2            白
	//IN3            黑
	//IN4            棕
	//LED  灯
	byte SpeedR;    //左轮速度
	byte SpeedL;    //右轮速度
	byte ENA;       // 使能 左or右 轮  （存储引脚号）
	byte ENB;       // 使能 左or右 轮  （存储引脚号）
	byte IN1;       // 信号输出控制方向  （存储引脚号）
	byte IN2;       // 信号输出控制方向  （存储引脚号）
	byte IN3;       // 信号输出控制方向  （存储引脚号）
	byte IN4;       // 信号输出控制方向  （存储引脚号）
	byte LED;       // 控制led灯
	void buck();            //后退函数  通过GO函数调用
	void straight();        //直走函数  通过GO函数调用
public:
	Mode Face;		//小车面朝的方向
	Mode mode;      //小车当前模式
	char ch;                             //用于接受命令字符
	void GO(u8 direction);               //1 直走  2 后退   speed 控制速度
	void Turn_in_situ(u8 direction);	 // 1 左 2 右  转向
	void Stop();						 //停止
	void AddSpeedR(u8 speed_m = 10);     //加速右轮
	void AddSpeedL(u8 speed_m = 10);	 //加速左轮
	void ReduceSpeedR(u8 speed_m = 10);  //减速右轮
	void ReduceSpeedL(u8 speed_m = 10);  //减速左轮
	void SetSpeed(u8 speed_m);		     //直接设定速度
	Mode GetMode();                      //获取当前的Mode 模式
	void ChangeMode(Mode state);		 //改变Mode 模式
	void LED_on_off(bool OF);            //控制led灯亮与不亮
	void GetSpeed();                     //获取两边速度并返回到上位机
	bool RGB_LED;
	Car()
	{
		RGB_LED = true;
		SpeedR = 100;
		SpeedL = 100;
		mode = FIND;
		ENA = 5;
		ENB = 6;
		IN1 = 46;
		IN2 = 48;
		IN3 = 50;
		IN4 = 52;
		LED = 3;
		ch = ' ';
		LED_on_off(ON);
		pinMode(ENA, OUTPUT);
		pinMode(ENB, OUTPUT);
		pinMode(IN1, OUTPUT);
		pinMode(IN2, OUTPUT);
		pinMode(IN3, OUTPUT);
		pinMode(IN4, OUTPUT);
		pinMode(LED, OUTPUT);
	}
};


#endif // !__Move