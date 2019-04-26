#include <Dxlib.h>
#include "GameTask.h"
#include "BackGround.h"
#include "Player.h"

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
	udFlag = false;	
	randomX = GetRand(SCREEN_SIZE_X);
	if(count <= 300)
	{
		randomY = GetRand(SCREEN_SIZE_Y);
		randomY_2 = GetRand(SCREEN_SIZE_Y);
	}
	else
	{
		randomY = GetRand(SCREEN_SIZE_Y) - 800;
		randomY_2 = GetRand(SCREEN_SIZE_Y) + 800;
	}


}

void BackGround::Update()
{
	if (udFlag == false) {
		vy += 0.2;
		if (randomY + vy > SCREEN_SIZE_Y)
		{
			removeFlag = true;
		}
	}
	if (udFlag == true) {
		vy2 -= 0.2;
		if (randomY + vy2 > SCREEN_SIZE_Y)
		{
			removeFlag = true;
		}
	}
}

void BackGround::Draw()
{
	if (udFlag == false) {
		if (randomX % 2 == 0)
		{
			DrawCircle(randomX, randomY + vy, 1, 0xffffff, true);
		}
		else if (randomX % 3 == 0)
		{
			DrawCircle(randomX, randomY + vy, 2, 0xffffff, true);
		}
	}
	if (udFlag == true) {
		if (randomX % 2 == 0)
		{
			DrawCircle(randomX, randomY_2 + vy2, 1, 0xffffff, true);
		}
		else if (randomX % 3 == 0)
		{
			DrawCircle(randomX, randomY_2 + vy2, 2, 0xffffff, true);
		}
	}
}

bool BackGround::SetFlag(bool flag)
{
	this->udFlag = flag;
	return true;
}
