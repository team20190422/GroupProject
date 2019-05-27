#include "Obj.h"
#include "Dxlib.h"
#include "ImageMng.h"


Obj::Obj()
{
}

Obj::Obj(const int(&trgKey)[KEY_MAX], const int(&oldKey)[KEY_MAX])
{
}


Obj::~Obj()
{
	//delete imageID;
}

void Obj::init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, float speed)
{
	imageName = filname;
	ImageMng::GetInstance().SetID(filname);
	this->divSize = divSize;
	this->divCnt = divCnt;
	this->chipOffset = chipOffset;
	this->speed = speed;
}

void Obj::Update(void)
{
}

void Obj::Draw(void)
{
}

RECT &Obj::GetRect()
{
	return this->rect;
}

const int & Obj::GetTimer(void)
{
	return 0;
}

const VECTOR2 & Obj::GetSize(void)
{
	return this->divSize;
}

void Obj::SetSize(const VECTOR2 & divSize)
{
	this->divSize = divSize;
}

bool Obj::SetPos(VECTOR3 pos)
{
	this->pos = pos;
	return true;
}

const VECTOR3 & Obj::GetPos(void)
{
	return this->pos;
}

bool Obj::SetAngle(float Angle)
{
	this->Angle = Angle;
	return true;
}

const float & Obj::GetAngle(void)
{
	return this->Angle;
}

bool Obj::SetDistance(float distance)
{
	this->distance = distance;
	return true;
}

const float & Obj::GetDistance()
{
	return this->distance;
}

const VECTOR3 & Obj::GetVec()
{
	return this->Vec;
}

bool Obj::SetVec(VECTOR3 vec)
{
	this->Vec = vec;
	return false;
}

const VECTOR3 & Obj::Normalize(VECTOR3 i,float mgn)
{
	i.x /= mgn;
	i.y /= mgn;
	return i;
}

void Obj::SetMove(void)
{

}


