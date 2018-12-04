#pragma once
#ifndef  __FindWay
#define  __FindWay

#include<Arduino.h>

//  红外探头数据接受口
//  接口可以更改
#define FindLEFT1   31
#define FindLEFT2   33
#define FindMID     35
#define FindRIGHT1  37
#define FindRIGHT2  39
typedef byte State;
#define Straight     1		//直行
#define LittleLEFT   2		//左微调
#define LittleRIGHT  3		//右微调
#define LEFT         4		//原地左转
#define RIGHT        5		//原地右转
#define turn_round   6		//原地回头



class Find
{
private:


public:
	State GetState();		//通过红外传感器确定应该执行的状态

	Find();
	~Find();
};

Find::Find()
{
	//打开串口 设为输入模式
	pinMode(FindLEFT2, INPUT);
	pinMode(FindLEFT1, INPUT);
	pinMode(FindMID, INPUT);
	pinMode(FindRIGHT1, INPUT);
	pinMode(FindRIGHT2, INPUT);

}

Find::~Find()
{
}




#endif // ! __FindWay
