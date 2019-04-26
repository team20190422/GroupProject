#pragma once
#include "Obj.h"
#include "KeyMng.h"
#include <array>

// ΩÀﬂ∞ƒﬁÇÃç≈ëÂíl

constexpr double speedMax = 5.0f;
class Player :
	public Obj
{
public:
	Player(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Player();

	void Draw(void);
	void Update(void);
	RECT  &GetRect();
	double Abstract(double i);
	RECT p;	
	float &GetSpeed();
private:
	void SetMove(void);
	VECTOR3 pos = { 0,0 };
	VECTOR3 size = { 64 / 2, 32 / 1 };
	VECTOR3 radianPos = { 0,0 };
	VECTOR3 vec = { 0,-1 };
	MATRIX master = { 0 };
	double Angle = 0;
	float speed = 1.0f;
	double count = -3.0f;
};

