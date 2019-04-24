#pragma once
#include "Obj.h"

//class GameTask;

class BackGround :public Obj
{
public:
	BackGround();
	~BackGround();

	void Init();
	void Update();
	void Draw();	

	int removeFlag;
private:
	float vy = 0;
	int randomX;
	int randomY;
	int count;
	const int(&j)[6] = { 0 };
};