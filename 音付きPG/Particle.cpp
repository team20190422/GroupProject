#include "Particle.h"



Particle::Particle(const VECTOR3& targetPos, const VECTOR3& targetVec, const int& sideFlag):Player(trgKey, oldKey)
{
	pos = targetPos;
	vec = targetVec;
	this->sideFlag = sideFlag;
}

Particle::~Particle()
{
}

void Particle::Draw(void)
{
    time++;

	auto Color = GetColor(255, (time * time >= 255 ? 0 : 255 - (time * time)), (time * time >= 255 ? 0 : 255 - (time * time)));
	DrawCircle((int)pos.x, (int)pos.y, (!sideFlag ? 1 : 3), Color/*GetColor(150, 40, 40)*/, true);
	
	//DrawPixel((int)pos.x, (int)pos.y, GetColor(255, 255, 255));
}

void Particle::Update(void)
{
	SetMove();

}

void Particle::SetMove(void)
{
	/*vec.x = cos(60) * vec.x + -sin(60) * vec.y;
	vec.y = sin(60) * vec.x + cos(60) * vec.y;*/
	if (!sideFlag)
	{
		pos += -vec;
	}
	else
	{
		
		//DrawFormatStringF(150, 10, GetColor(255, 255, 255), "posX@%f  posY %f", pos.x, pos.y);
	}
}

const int & Particle::GetTimer(void)
{
    return time;
}

bool Particle::SetPos(VECTOR3 pos)
{
	this->pos = pos;
	return true;
}

const VECTOR3 & Particle::GetPos(void)
{
	return pos;
}
