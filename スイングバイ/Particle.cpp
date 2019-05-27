#include "Particle.h"
#include "ImageMng.h"


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

	auto Color = GetColor((!sideFlag ? 100 : 255), (time * time >= 255 ? 0 : 255 - (time * time)), (time * time >= 255 ? 0 : 255 - (time * time)));
	//if (sideFlag == 5)
	//{

		/*if (time % 2 == 0)
		{*/
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (sideFlag == 5 ? 10 : 20)-time);
			DrawRotaGraph((int)pos.x, (int)pos.y, 0.1, 0, ImageMng::GetInstance().SetID("image/‰Œ.png"), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			//DrawCircle((int)pos.x, (int)pos.y, 4 + lpGameTask.GetRocketSize(), GetColor(50, 50, 50), true);
		//}
	//}
	//DrawCircle((int)pos.x, (int)pos.y, (sideFlag != 5 ? 1 : (2 - ((time / 7) % 3)) + lpGameTask.GetRocketSize()), Color/*GetColor(150, 40, 40)*/, true);

	//DrawPixel((int)pos.x, (int)pos.y, GetColor(255, 255, 255));
}

void Particle::Update(void)
{
	SetMove();
	//if(sideFlag)
	//DrawFormatStringF(10, 400, GetColor(255, 255, 255), "vecX@%f  vecY %f", vec.x, vec.y);
}

void Particle::SetMove(void)
{
	/*vec.x = cos(60) * vec.x + -sin(60) * vec.y;
	vec.y = sin(60) * vec.x + cos(60) * vec.y;*/
	pos += -vec;
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
