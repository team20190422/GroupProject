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
	vyS = 0;
	vyM = 0;
}

void BackGround::Update()
{
	if (lpGameTask.playerVec.y < 0)
	{
		vyS += 0.1f;
		vyM += 0.2f;
		if (randomY + vyS > SCREEN_SIZE_Y || randomY + (vyM / 2) > SCREEN_SIZE_Y)
		{
			removeFlag = true;
		}
	}
	else if (lpGameTask.playerVec.y > 0)
	{
		vyS -= 0.1f;
		vyM -= 0.2f;
		if (randomY + vyS < 0 || randomY + (vyM / 2) < 0)
		{
			removeFlag = true;
		}
	}
}

void BackGround::Draw()
{
	if (randomX % 2 == 0)
	{
		DrawCircle(randomX, randomY + vyS, 1, GetColor(255,255,255), true);
	}
	else if(randomX % 3 == 0)
	{
		DrawCircle(randomX, randomY + vyM, 2, GetColor(255,255,255), true);
	}	
}
