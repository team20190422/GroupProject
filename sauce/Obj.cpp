#include "Obj.h"
#include "Dxlib.h"
#include "ImageMng.h"


/*Obj::Obj()
{
}*/

Obj::Obj(const int(&trgKey)[6], const int(&oldKey)[6])
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

void Obj::SetMove(void)
{

}


