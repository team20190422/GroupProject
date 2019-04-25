#include <Dxlib.h>
#include <list>
#include "GameTask.h"
#include "BackGround.h"

BackGround::BackGround():Obj(j, j)
{
	Init();
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	count = GameTask::GetInstance().SetCount();
	removeFlag = false;
	randomX = GetRand(SCREEN_SIZE_X);
	if(count <= 300)
	{
		randomY = GetRand(SCREEN_SIZE_Y);
	}
	else
	{
		randomY = GetRand(SCREEN_SIZE_Y) - 800;
	}
	
}

void BackGround::Update()
{
	vy += 0.2;
	if (randomY + vy > SCREEN_SIZE_Y)
	{
		removeFlag = true;
	}
}

void BackGround::Draw()
{
	if (randomX % 2 == 0)
	{
		DrawCircle(randomX, randomY + vy, 1, 0xffffff, true);
	}
	else if(randomX % 3 == 0)
	{
		DrawCircle(randomX, randomY + vy, 2, 0xffffff, true);
	}	
}
