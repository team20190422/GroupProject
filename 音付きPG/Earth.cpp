#include <DxLib.h>
#include "Earth.h"
#include "GameTask.h"

Earth::Earth()
{
	Init();
}


Earth::~Earth()
{
}

void Earth::Init()
{
	image = LoadGraph("image/EarthTest.png");
	r = (float)BasePlanet::GetRadius(image);
	pos = { 220, 650 };
}

void Earth::Update()
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

void Earth::Draw()
{
	DrawRotaGraphF(pos.x, pos.y, 1.0, 0, image, true);
}
