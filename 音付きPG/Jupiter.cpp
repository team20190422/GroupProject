#include <DxLib.h>
#include "Jupiter.h"
#include "GameTask.h"


Jupiter::Jupiter()
{
	Init();
}


Jupiter::~Jupiter()
{
}

void Jupiter::Init()
{
	image = LoadGraph("image/JupiterTest.png");
	r = (float)BasePlanet::GetRadius(image);
	pos = { 250,-3000 };
}

void Jupiter::Update()
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
}

void Jupiter::Draw()
{
	DrawRotaGraphF(pos.x, pos.y, 1.0, 0, image, true);
}
