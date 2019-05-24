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

	bool removeFlag;


private:
	float vyS = 0;
	float vyM = 0;
	int randomX;
	int randomY;
	int count;
	const int(&j)[7] = { 0 };
};