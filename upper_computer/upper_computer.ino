/*
Name:    upper_computer.ino
Created: 2018/12/5 13:17:41
Author:  JingYu
*/
#define PT_USE_TIMER
#include"keyboard.h"
#include<pt.h>

static struct pt pt1, pt2;
pt_timer servotimer1;
pt_timer servotimer2;

// the setup function runs once when you press reset or power the board

Keyboard keyboard;
char key1; //接收按键信息
char ch;   //接受来自小车的信息
// 接受到小车的消息：
/*
   'B' :  绿灯闪烁
          begin  输入起点 格式  xx  比如 12  即代表（1，2），再按#表示确认；
          然后输入终点坐标 格式  xx  比如 43  即代表（4，3），再按#表示确认；
  ‘E’： 到达终点  蓝灯闪烁 1.5秒  然后绿灯闪烁 再次进入B模式
   

          

*/

static int mission1(struct pt *pt)  //线程1  做主线程
{
  PT_BEGIN(pt);
  while (1)
  {
    ch = NO_KEY;
    key1 = keyboard.keypad.getKey();
    if (Serial1.available())
    {
      ch = Serial1.read();
    }
    if (ch == NO_KEY)
    {
      //continue;
    }
    // test部分
    {
      if (key1 != NO_KEY)
      {
        Serial.print(key1);
        Serial1.print(key1);
      }
    }
    PT_YIELD(pt);
    if (ch == 'P')
    {

    }
  }
  PT_END(pt);
}
static int mission2(struct pt *pt)
{
  PT_BEGIN(pt);
  while (1)
  {
    PT_YIELD(pt);
  }
  PT_END(pt);
}


void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  PT_INIT(&pt1);
  PT_INIT(&pt2);  //两个线程初始化
}

// the loop function runs over and over again until power down or reset
void loop() {
//   key1 = keyboard.keypad.getKey();


  /*if (key1 != NO_KEY)
  {
    Serial.print(key1);
  }*/
  mission1(&pt1);
  mission2(&pt2);
}
