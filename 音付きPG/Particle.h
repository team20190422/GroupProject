#pragma once
#include "Player.h"

class Particle :
	public Player
{
public:
	Particle(const VECTOR3& targetPos, const VECTOR3& targetVec, const int& sideFlag);
	~Particle();

	void Draw(void);
	void Update(void);

	void SetMove(void);

	const int& GetTimer(void);

	bool SetPos(VECTOR3 pos);
	const VECTOR3& GetPos(void);

	int time = 0;

private:
	const int(&trgKey)[6] = { 0 };
	const int(&oldKey)[6] = { 0 };
	std::weak_ptr<Player> target;

	VECTOR3 pos = { 0,0 };
	VECTOR3 vec = { 0,0 };

	// âEÇÕ1 ç∂ÇÕ2
	int sideFlag = 0;

	int fire;
};

