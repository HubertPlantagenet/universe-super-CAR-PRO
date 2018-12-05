#pragma once
#ifndef  __keyboard
#define  __keyboard

#include<Keypad.h>
#include<Arduino.h>

//#define C4  48
//#define C3  46
//#define C2  44
//#define C1  42
//#define R1  40
//#define R2  38
//#define R3  36
//#define R4  34

#define numRows 4  //定义4行
#define numCols 4  //定义4列

//行高列低

char keymap[numRows][numCols] = {
  { '1','2','3',',' }, //第一行
{ '4','5','6','A' }, //第二行
{ '7','8','9','B' },
{ '*','0','#','C' }
};

class Keyboard
{
public:
  //  char GetKeyDown();  //获取按键按下信息
  byte Cols[4] = { 42,44,46,48 };
  byte Rows[4] = { 40,38,36,34 };
  Keypad keypad = Keypad(makeKeymap(keymap), Rows, Cols, numRows, numCols);

private:

};





#endif // ! __keyboard
