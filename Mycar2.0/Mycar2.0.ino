#define PT_USE_TIMER
#include <FlexiTimer2.h> //��ʱ����
#include<pt.h>
#include"Move.h"
/*

Github �汾


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
#define time1 1
#define time2 5
unsigned Turn_time_A = 800;
unsigned Turn_time_D = 700;

Car Mycar;              //ֻ��Դ�ļ�
static struct pt pt1, pt2;
pt_timer servotimer1;
pt_timer servotimer2;

class Turn  // ת�����
{
public:
	Turn();
	~Turn();
	byte direction;  //ת����
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

//������Ѱ��ת����
	 /*void ninty_turn(u8 direction, u8 time)
{

}*/
//ֱ��ת����  direction���� time ת��ʱ��

static int mission1(struct pt *pt)
{
	PT_BEGIN(pt);  //�߳̿�ʼ
	while (1)
	{
		//�߳�ѭ����ʼ
		Mycar.ch = ' ';  //ÿ��ѭ����ʼ�� ch 
		Mycar.ch2 = ' ';  //ÿ��ѭ����ʼ�� ch2 
//		Serial1.println("MOVE");
		if (Serial1.available())
			Mycar.ch = Serial1.read();
		if (Serial2.available())
		{
	//		Serial1.println("Receive from Serial2");
			// test ����  Mycar.ch2 ������������ͨ�ŵ�ָ��
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
		if (Mycar.ch == 'i')  // �ַ�i �����л�������Ѱ��ģʽ
		{
			Mycar.ChangeMode(FIND);
			continue;
		}
		if (Mycar.ch == 'm')  //�ַ�'m'�����л���ң��ģʽ
		{
			Mycar.ChangeMode(MOVE);
			continue;
		}
		if (Mycar.ch == 'q')  //�ַ� q �����л���Setģʽ
		{
			Mycar.ChangeMode(SET);
			continue;
		}
		PT_YIELD(pt);
		if (Mycar.mode == SET)   //����ǰ���� Setģʽ
		{
			ChoiceByset();
			continue;
		}
		if (Mycar.mode == MOVE)  //����ǰ������ AIģʽ
		{
			if (Mycar.ch != ' ')
				Serial1.println(Mycar.ch);
			//////////////////////////////
			{
				switch (Mycar.ch)
				{
				case 'L':	//���� 
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
				case 'W':	//ǰ��
				{
					Mycar.GO(1);
					Serial1.println("GO1");
				} break;
				case 'w':	//ͣ
				{
					Mycar.Stop();
				}break;
				case 'S':	//����
				{
					Mycar.GO(2);
				} break;
				case 's':	//ͣ
				{
					Mycar.Stop();
				}break;
				case 'A':	//��ת
				{
					Mycar.Turn_in_situ(Left_turn);
				} break;
				case 'a':	//������������ת
				{
					Mycar.Turn_in_situ(3);
				}break;
				case 'D':	//��ת
				{
					Mycar.Turn_in_situ(Right_turn);
				} break;
				case 'd':	//������������ת
				{
					Mycar.Turn_in_situ(3);
				}break;
				// ���ٲ���
				case 'P':  //�����ٶ�  ��
				{
					Mycar.AddSpeedR();
					Mycar.GetSpeed();
				} break;
				case 'M':  //�����ٶ�  ��
				{
					Mycar.ReduceSpeedR();
					Mycar.GetSpeed();
				} break;
				case 'O':  //�����ٶ�  ��
				{
					Mycar.AddSpeedL();
					Mycar.GetSpeed();
				} break;
				case 'K':  //�����ٶ�  ��
				{
					Mycar.ReduceSpeedL();
					Mycar.GetSpeed();
				} break;
				case '+':  //�����ٶ�  ��
				{
					Mycar.AddSpeedL();
					Mycar.AddSpeedR();
					Mycar.GetSpeed();
				} break;
				case '-':  //�����ٶ�  ��
				{
					Mycar.ReduceSpeedL();
					Mycar.ReduceSpeedR();
					Mycar.GetSpeed();
				} break;
				case '#':	//��ȡ��ǰ�ٶ�
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
			//������Ѱ������
			//test ����
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
	}//�߳�ѭ������
	PT_END(pt);    //�߳̽���
}
static int mission2(struct pt *pt)
{
	PT_BEGIN(pt);  //�߳̿�ʼ
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
	PT_END(pt);    //�߳̽���
}


void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial1.begin(9600);   //��������ͨѶ������
	Serial2.begin(9600);   //��������ͨѶ�Ĳ�����
	FlexiTimer2::set(750, 1.0 / 1000, Return_ch); //0.75�� ��ӡһ�ε�ǰ��Mycar.ch
//	FlexiTimer2::start();
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

void loop() { //��������ѭ��
			  // put your main code here, to run repeatedly:
	mission1(&pt1);
	mission2(&pt2);
}