// FindWay.cpp
// δ��  2018.12.5  2:00 
#include"FindWay.h"
//#include"Arduino.h"

State Find::GetState() //��⵽Ϊ 0 û��⵽Ϊ1
{
	if (FindLEFT2 == 1 && FindLEFT1 == 1 && FindMID == 0 && FindRIGHT1 == 1 && FindLEFT2 == 1)
	{
		return Straight;		//ֱ��
	}
	//if (FindLEFT2 == && FindLEFT1 == && FindMID == && FindRIGHT1 == && FindLEFT2 == )
	//{
	//	return turn_round;		//ԭ�ص�ͷ
	//}
	if (FindLEFT2 == 0 && FindLEFT1 == 0 && FindMID == 0 && FindRIGHT1 == 0 && FindLEFT2 == 0)
	{
		//���ú���t �ɺ���t���� ԭ����ת ԭ����ת�� (tֻ�Ǵ��� ����δȡ)
		//���庯��ʵ���� Դ�ļ����߳���д ����ʹ�� PT_WAIT_UNITL


		return 0;
	}
	if (FindLEFT2 == 1 && FindLEFT2 == 1)  // ִ��΢��
	{
		if (FindLEFT1 == 0 && FindMID == 0 && FindRIGHT1 == 1)	//1 0 0 1 1
		{
			return LittleLEFT;		//����΢��
		}
		if(FindLEFT1 == 0 && FindMID == 1 && FindRIGHT1 == 1)	//1 0 1 1 1
		{
			return LittleLEFT;		//����΢��
		}
		if (FindLEFT1 == 1 && FindMID == 0 && FindRIGHT1 == 0)  //1 1 0 0 1 
		{
			return LittleRIGHT;		//����΢��
		}
		if (FindLEFT1 == 1 && FindMID == 1 && FindRIGHT1 == 0)  //1 1 1 0 1
		{
			return LittleRIGHT;		//����΢��
		}
	}
}
