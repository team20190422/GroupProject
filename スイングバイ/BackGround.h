#pragma once
#include "Obj.h"

class BackGround :public Obj
{
public:
	BackGround();
	~BackGround();

	void Init();
	void Update();
	void Draw();	
	bool SetFlag(bool flag);

	int removeFlag;
private:
	float vy = 0;
	float vy2 = 0;
	int randomX;
	int randomY_2;
	int randomY;
	int count;
	int udFlag;	//��ʃX�N���[���̏㉺����t���O
	const int(&j)[6] = { 0 };
};