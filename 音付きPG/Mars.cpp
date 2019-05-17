#include <DxLib.h>
#include "Mars.h"
#include "GameTask.h"

Mars::Mars()
{
	Init();
}

Mars::~Mars()
{
}

void Mars::Init()
{
	image = LoadGraph("image/Mars2.png");
	r = (float)BasePlanet::GetRadius(image);
	pos = { 200,-500 };
}

void Mars::Update()
{
	pos = pos + lpGameTask.GetScrollPos();
	if (BasePlanet::PlanetFactry(g, r, pos))
	{
		lpGameTask.SetHitCheck(true);
	}
	else
	{
		lpGameTask.SetHitCheck(false);
	}

	//DrawFormatString(10, 40, GetColor(255, 255, 255), "posXÅ@%f  posY %f", pos.x, pos.y);
}

void Mars::Draw()
{
	DrawRotaGraphF(pos.x, pos.y, 1.0,0,image, true);
	//DrawGraph(pos.x, pos.y, image, true);
}
