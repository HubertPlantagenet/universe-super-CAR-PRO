#define PT_USE_TIMER
#include <FlexiTimer2.h> //��ʱ����
#include<pt.h>
#include"Move.h"
/*
#define ENA 5   //ʹ�ܿ���  ��
#define ENB 6   //����      ��
#define IN1 46  //�ط���    ��  ��  �� ��
#define IN2 48  //          ��
#define IN3 50  //          ��
#define IN4 52  //          ��
#define LED 3


RGB_LED ---------- ����  11 12 13  GND
*/
/*
/////////////////////////////����//////////////////////////////
W/w  ǰ�� ������Wǰ�� Ȼ��ȴ�w����ֹͣ  WASD L ��ͬ��
S/s  ����  A/a  D/d  ����    �����ܴ��ڽ������ ���������λ�����ԣ�
L/l  �򿪹ر�ָʾ��
i    �򿪹ر� AI״̬
q    �򿪹ر� set״��  set״̬�����趨�ٶȣ�Ŀǰ��
P M    ���ּ��ټ���
O K    ���ּ��ټ���
+ -    ������ټ���
#      ��õ�ǰ�ٶ�
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

static Car Mycar;              //ֻ��Դ�ļ�
static struct pt pt1, pt2;
pt_timer servotimer1;
pt_timer servotimer2;

static int mission1(struct pt *pt)
{
	PT_BEGIN(pt);  //�߳̿�ʼ
	while (1)
	{
		//�߳�ѭ����ʼ
		Mycar.ch = ' ';  //ÿ��ѭ����ʼ�� ch 
		if (Serial1.available())
			Mycar.ch = Serial1.read();
		if (Mycar.ch == 'i')  // �ַ�i �����л�������Ѱ��ģʽ
		{
			Mycar.ChangeMode(FIND);
			return;
		}
		if (Mycar.ch == 'm')  //�ַ�'m'�����л���ң��ģʽ
		{
			Mycar.ChangeMode(MOVE);
			return;
		}
		if (Mycar.ch == 'q')  //�ַ� q �����л���Setģʽ
		{
			Mycar.ChangeMode(SET);
			return;
		}
		PT_YIELD(pt);
		if (Mycar.GetMode() == SET)   //����ǰ���� Setģʽ
		{
			ChoiceByset();
			return;
		}
		if (Mycar.GetMode() == MOVE)  //����ǰ������ AIģʽ
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
				// ���ٲ���
				case 'P':  //�����ٶ�  ��
				{
					Mycar.AddSpeedR();
				} break;
				case 'M':  //�����ٶ�  ��
				{
					Mycar.ReduceSpeedR();
				} break;
				case 'O':  //�����ٶ�  ��
				{
					Mycar.AddSpeedL();
				} break;
				case 'K':  //�����ٶ�  ��
				{
					Mycar.ReduceSpeedL();
				} break;
				case '+':  //�����ٶ�  ��
				{
					Mycar.AddSpeedL();
					Mycar.AddSpeedR();
				} break;
				case '-':  //�����ٶ�  ��
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
			//������Ѱ������

		}
	}//�߳�ѭ������
	PT_END(pt);    //�߳̽���
}
static int mission2(struct pt *pt)
{
	PT_BEGIN(pt);  //�߳̿�ʼ
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
	PT_END(pt);    //�߳̽���
}


void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial1.begin(9600);   //��������ͨѶ������
	FlexiTimer2::set(750, 1.0 / 1000, Return_ch); //0.75�� ��ӡһ�ε�ǰ��Mycar.ch
	FlexiTimer2::start();
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	digitalWrite(13, LOW); digitalWrite(12, LOW); digitalWrite(11, LOW);
	PT_INIT(&pt1);
	PT_INIT(&pt2);  //�����̳߳�ʼ��
}
void Return_ch()    //���ز���ӡ Mycar.ch
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

void loop() { //��������ѭ��
			  // put your main code here, to run repeatedly:
	mission1(&pt1);
	mission2(&pt2);
}