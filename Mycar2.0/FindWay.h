#pragma once
#ifndef  __FindWay
#define  __FindWay

#include<Arduino.h>

//  ����̽ͷ���ݽ��ܿ�
//  �ӿڿ��Ը���
#define FindLEFT1   31
#define FindLEFT2   33
#define FindMID     35
#define FindRIGHT1  37
#define FindRIGHT2  39
typedef byte State;
#define Straight     1		//ֱ��
#define LittleLEFT   2		//��΢��
#define LittleRIGHT  3		//��΢��
#define LEFT         4		//ԭ����ת
#define RIGHT        5		//ԭ����ת
#define turn_round   6		//ԭ�ػ�ͷ



class Find
{
private:


public:
	State GetState();		//ͨ�����⴫����ȷ��Ӧ��ִ�е�״̬

	Find();
	~Find();
};

Find::Find()
{
	//�򿪴��� ��Ϊ����ģʽ
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
