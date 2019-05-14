#include <Dxlib.h>
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
	if (lpGameTask.playerVec.y < 0)
	{
		if (count <= 300)
		{
			randomY = GetRand(SCREEN_SIZE_Y);
		}
		else
		{
			randomY = GetRand(SCREEN_SIZE_Y) - 800;
		}
	}
	else if(lpGameTask.playerVec.y > 0)
	{
		if (count <= 300)
		{
			randomY = GetRand(SCREEN_SIZE_Y);
		}
		else
		{
			randomY = GetRand(SCREEN_SIZE_Y) + 800;
		}
	}
	
}

void BackGround::Update()
{
	if (lpGameTask.playerVec.y < 0)
	{
		vy += 0.2f;
		if (randomY + vy > SCREEN_SIZE_Y)
		{
			removeFlag = true;
		}
	}
	else if (lpGameTask.playerVec.y > 0)
	{
		vy -= 0.2f;
		if (randomY + vy < 0)
		{
			removeFlag = true;
		}
	}
}

void BackGround::Draw()
{
	//int col = GetRand(255);
	if (randomX % 2 == 0)
	{
		DrawCircle(randomX, randomY + vy, 1, GetColor(255,255,255), true);
	}
	else if(randomX % 3 == 0)
	{
		DrawCircle(randomX, randomY + vy, 2, GetColor(255,255,255), true);
	}	
}
