#pragma once
#ifndef  __FindWay
#define  __FindWay

//  红外探头数据接受口
#define  LEFT1
#define  LEFT2
#define  MID
#define  RIGHT1
#define  RIGHT2


class Find
{
private:


public:
	Find();
	~Find();
};

Find::Find()
{
	pinMode();
}

Find::~Find()
{
}




#endif // ! __FindWay
