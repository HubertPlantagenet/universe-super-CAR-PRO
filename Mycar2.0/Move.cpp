#include"Move.h"
#include<Arduino.h>

void Car::ChangeMode(Mode state)
{
	mode = state;
	Serial1.print("Mode = ");
	Serial1.println(mode);
}
Mode Car::GetMode()
{
	return mode;
}
void Car::SetSpeed(u8 speed_m)
{
	SpeedL = speed_m;
	SpeedR = speed_m;
}
void Car::GetSpeed()
{
	Serial1.print(SpeedR);
	Serial1.print("_");
	Serial1.println(SpeedL);
}
void Car::LED_on_off(bool OF)
{
	analogWrite(LED, OF);
}
void Car::AddSpeedR(u8 speed_m)
{
	SpeedR += speed_m;
	if (SpeedR >= 255)
		SpeedR = 255;
}
void Car::AddSpeedL(u8 speed_m)
{
	SpeedL += speed_m;
	if (SpeedL >= 255)
		SpeedL = 255;
}
void Car::ReduceSpeedR(u8 speed_m)
{
	SpeedR -= speed_m;
	if (SpeedR <= 50)
		SpeedR = 50;
}
void Car::ReduceSpeedL(u8 speed_m)
{
	SpeedL -= speed_m;
	if (SpeedL <= 50)
		SpeedL = 50;
}


void Car::Stop()
{
	analogWrite(ENA, 0);
	analogWrite(ENB, 0);
}
void Car::straight()
{
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, HIGH);
	digitalWrite(IN3, HIGH);
	digitalWrite(IN4, LOW);
}
void Car::buck()
{
	digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);
}
void Car::GO(u8 direction)  //1 直走  2 后退   speed 控制速度
{
	if (direction == 1)
		straight();
	else if (direction == 2)
		buck();
	analogWrite(ENA, SpeedL);
	analogWrite(ENB, SpeedR);
}
void Car::Turn_in_situ(u8 direction)   //1左 2右  转向
{
	switch (direction)
	{
	case 1://左转
	{
		digitalWrite(IN1, LOW);
		digitalWrite(IN2, HIGH);
		digitalWrite(IN3, LOW);
		digitalWrite(IN4, HIGH);
	} break;
	case 2://右转
	{
		digitalWrite(IN1, HIGH);
		digitalWrite(IN2, LOW);
		digitalWrite(IN3, HIGH);
		digitalWrite(IN4, LOW);
	} break;
	case 3:
	{
		straight();
	}break;
	}     //switch结束
	analogWrite(ENA, SpeedL);
	analogWrite(ENB, SpeedR);
}