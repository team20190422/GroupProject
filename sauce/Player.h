#pragma once
#include "Obj.h"
#include "KeyMng.h"
#include <array>

// ΩÀﬂ∞ƒﬁÇÃç≈ëÂíl

constexpr float speedMax = 5.0f;
class Player :
	public Obj
{
public:
	Player(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Player();

	void Draw(void);
	void Update(void);

	float Abstract(float i);

	bool SetPos(VECTOR3 pos);
	const VECTOR3& GetPos(void);


	bool SetAngle(float Angle);
	const float& GetAngle(void);

private:
	void SetMove(void);

	VECTOR3 pos = { 0,0 };
	VECTOR3 radianPos = { 0,0 };
	VECTOR3 vec = { 0,-1 };
	MATRIX master = { 0 };
	float Angle = 0;
	float speed = 1.0f;
	float count = -3.0f;

};

