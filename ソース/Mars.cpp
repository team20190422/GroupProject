#include <DxLib.h>
#include "Mars.h"
#include "GameTask.h"

Mars::Mars(VECTOR3 pos)
{
	mPos = pos;
	Init();
}

Mars::~Mars()
{
}

void Mars::Init()
{
	image = LoadGraph("image/MarsTest.png");
	r = (float)BasePlanet::GetRadius(image);
	pos = mPos;
}

void Mars::Update()
{

	unsigned int rSize = (PLAYER_SIZE / 2);
	VECTOR3 playerPosR(lpGameTask.playerPos.x + rSize, lpGameTask.playerPos.y + rSize);
	time += 0.01f;
	VECTOR3 radianPos(pos.x + (r * cos(1 / 2)), pos.y + (r * sin(1 / 2)));


	lpGameTask.targetSize = r;
	lpGameTask.targetPos = radianPos;
	lpGameTask.targetVec = (radianPos - pos);

	if (!lpGameTask.GetHitCheck() && !lpGameTask.GetLandCheck())
	{
		if (!lpGameTask.plPosMaxFlag)
		{
			pos = pos + lpGameTask.GetScrollPos();
		}
	}

	if (!lpGameTask.landingFlag && (playerPosR.x > radianPos.x - rSize && lpGameTask.playerPos.x < radianPos.x + rSize))
	{

		if (!lpGameTask.landingFlag && (playerPosR.y > radianPos.y - rSize && lpGameTask.playerPos.y < radianPos.y + rSize))
		{
			DrawString(lpGameTask.playerPos.x, lpGameTask.playerPos.y + rSize, "Get", 0xffffff, true);
			lpGameTask.SetLandCheck(true);
			lpGameTask.getSample = true;
		}
		else if (BasePlanet::PlanetFactry(g, r, pos) && !lpGameTask.GetLandCheck())
		{
			lpGameTask.SetHitCheck(true);
		}
		else
		{
			lpGameTask.SetHitCheck(false);
		}
	}
	else if (BasePlanet::PlanetFactry(g, r, pos) && !lpGameTask.GetLandCheck())
	{
		
		lpGameTask.SetHitCheck(true);
	}
	else
	{
		lpGameTask.SetHitCheck(false);
	}

	if (!lpGameTask.landingFlag)
	{
		DrawBox(radianPos.x - rSize, radianPos.y - rSize, radianPos.x + rSize, radianPos.y + rSize, GetColor(255, 0, 0), true);
	}
	//DrawFormatString(10, 100, GetColor(255, 255, 255), "hitFlag %d", lpGameTask.GetHitCheck());
}

void Mars::Draw()
{
	DrawRotaGraphF(pos.x, pos.y,1.0,0,image, true);
	//DrawGraph(pos.x, pos.y, image, true);
}
