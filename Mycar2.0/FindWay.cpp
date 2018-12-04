// FindWay.cpp
// 未完  2018.12.5  2:00 
#include"FindWay.h"
//#include"Arduino.h"

State Find::GetState() //检测到为 0 没检测到为1
{
	if (FindLEFT2 == 1 && FindLEFT1 == 1 && FindMID == 0 && FindRIGHT1 == 1 && FindLEFT2 == 1)
	{
		return Straight;		//直行
	}
	//if (FindLEFT2 == && FindLEFT1 == && FindMID == && FindRIGHT1 == && FindLEFT2 == )
	//{
	//	return turn_round;		//原地调头
	//}
	if (FindLEFT2 == 0 && FindLEFT1 == 0 && FindMID == 0 && FindRIGHT1 == 0 && FindLEFT2 == 0)
	{
		//调用函数t 由函数t决定 原地左转 原地右转： (t只是代号 名仍未取)
		//具体函数实现在 源文件主线程中写 可以使用 PT_WAIT_UNITL


		return 0;
	}
	if (FindLEFT2 == 1 && FindLEFT2 == 1)  // 执行微调
	{
		if (FindLEFT1 == 0 && FindMID == 0 && FindRIGHT1 == 1)	//1 0 0 1 1
		{
			return LittleLEFT;		//向左微调
		}
		if(FindLEFT1 == 0 && FindMID == 1 && FindRIGHT1 == 1)	//1 0 1 1 1
		{
			return LittleLEFT;		//向左微调
		}
		if (FindLEFT1 == 1 && FindMID == 0 && FindRIGHT1 == 0)  //1 1 0 0 1 
		{
			return LittleRIGHT;		//向右微调
		}
		if (FindLEFT1 == 1 && FindMID == 1 && FindRIGHT1 == 0)  //1 1 1 0 1
		{
			return LittleRIGHT;		//向右微调
		}
	}
}
