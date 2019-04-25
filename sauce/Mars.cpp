#include <DxLib.h>
#include "Mars.h"

Mars::Mars()
{
	Init();
}

Mars::~Mars()
{
}

void Mars::Init()
{
	image = LoadGraph("image/MarsTest.png");
	r = BasePlanet::GetRadius(image);
	pos = { 200,400 };
}

void Mars::Update()
{
	BasePlanet::PlanetFactry(g, r, pos);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "posXÅ@%f  posY %f", pos.x, pos.y);
}

void Mars::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1.0,0,image, true);
	//DrawGraph(pos.x, pos.y, image, true);
}
