#pragma once
#include "VECTOR3.h"
#include "Obj.h"
class Obstracle :
	public Obj
{
public:
	Obstracle();
	~Obstracle();
	void Update();
	void Draw();
	void SetMove();
	RECT &GetRect();
	RECT o;
private:
	VECTOR3 pos = { 0.0f,0.0f };
	VECTOR3 size = { 64 / 2 , 32 / 1 };
	float speed;
};

