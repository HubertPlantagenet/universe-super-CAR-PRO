
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
	//ENA  ʹ�ܿ���  ��
	//ENB  ����      ��
	//IN1  �ط���    ��  ��  �� ��
	//IN2            ��
	//IN3            ��
	//IN4            ��
	//LED  ��
	byte SpeedR;    //�����ٶ�
	byte SpeedL;    //�����ٶ�
	byte ENA;       // ʹ�� ��or�� ��  ���洢���źţ�
	byte ENB;       // ʹ�� ��or�� ��  ���洢���źţ�
	byte IN1;       // �ź�������Ʒ���  ���洢���źţ�
	byte IN2;       // �ź�������Ʒ���  ���洢���źţ�
	byte IN3;       // �ź�������Ʒ���  ���洢���źţ�
	byte IN4;       // �ź�������Ʒ���  ���洢���źţ�
	byte LED;       // ����led��
	void buck();            //���˺���  ͨ��GO��������
	void straight();        //ֱ�ߺ���  ͨ��GO��������
public:
	Mode Face;		//С���泯�ķ���
	Mode mode;      //С����ǰģʽ
	char ch;                             //���ڽ��������ַ�
	void GO(u8 direction);               //1 ֱ��  2 ����   speed �����ٶ�
	void Turn_in_situ(u8 direction);	 // 1 �� 2 ��  ת��
	void Stop();						 //ֹͣ
	void AddSpeedR(u8 speed_m = 10);     //��������
	void AddSpeedL(u8 speed_m = 10);	 //��������
	void ReduceSpeedR(u8 speed_m = 10);  //��������
	void ReduceSpeedL(u8 speed_m = 10);  //��������
	void SetSpeed(u8 speed_m);		     //ֱ���趨�ٶ�
	Mode GetMode();                      //��ȡ��ǰ��Mode ģʽ
	void ChangeMode(Mode state);		 //�ı�Mode ģʽ
	void LED_on_off(bool OF);            //����led�����벻��
	void GetSpeed();                     //��ȡ�����ٶȲ����ص���λ��
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