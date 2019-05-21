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
	image = LoadGraph("image/Mars.png");
	planetImage = LoadSoftImage("image/Mars.png");
	nextPlanet = LoadGraph("image/nextPlanet.png");
	r = (float)BasePlanet::GetRadius(image);
	pos = mPos;
}

void Mars::Update()
{
	auto HitCheck = [&] {
		int r = 0, g = 0, b = 0, a = 0;
		unsigned int rSize = (PLAYER_SIZE / 4);

		VECTOR3 playerPosR(lpGameTask.playerPos.x + rSize, lpGameTask.playerPos.y + rSize);
		VECTOR3 playerPosL(lpGameTask.playerPos.x - rSize, lpGameTask.playerPos.y - rSize);

		for (int x = 0; x < 128; x++)
		{
			for (int y = 0; y < 128; y++)
			{
				GetPixelSoftImage(planetImage, x, y, &r, &g, &b, &a);

				if (a > 60)
				{
					VECTOR3 marsPos(pos.x - 64 + x, pos.y - 64 + y);
					DrawPixel((int)marsPos.x, (int)marsPos.y, GetColor(255, 0, 0));
					if ((marsPos.x > playerPosL.x && marsPos.x < playerPosR.x))
					{
						if ((marsPos.y > playerPosL.y && marsPos.y < playerPosR.y))
						{
							return true;
						}
					}
				}
			}
		}

		return false;
	};
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
			DrawString((int)lpGameTask.playerPos.x, (int)lpGameTask.playerPos.y + rSize, "Get", 0xffffff, true);
			lpGameTask.SetLandCheck(true);
			lpGameTask.getSample = true;
		}
		else if (HitCheck() && !lpGameTask.GetLandCheck())
		{
			lpGameTask.SetHitCheck(true);
		}
		else
		{
			lpGameTask.SetHitCheck(false);
		}
	}
	else if (HitCheck() && !lpGameTask.GetLandCheck())
	{
		
		lpGameTask.SetHitCheck(true);
	}
	else
	{
		lpGameTask.SetHitCheck(false);
	}

	if (BasePlanet::PlanetFactry(gravity, r, pos) && !lpGameTask.GetLandCheck())
	{
	}

	if (!lpGameTask.landingFlag)
	{
		DrawBox((int)radianPos.x - rSize, (int)radianPos.y - rSize, (int)radianPos.x + rSize, (int)radianPos.y + rSize, GetColor(255, 0, 0), true);
	}
	//DrawFormatString(10, 100, GetColor(255, 255, 255), "hitFlag %d", lpGameTask.GetHitCheck());
}

void Mars::Draw()
{
	
	// nextPlanet
	DrawRotaGraph(SCREEN_SIZE_X - 50, 100, 1.0, 0, nextPlanet, true);
	DrawRotaGraph(SCREEN_SIZE_X - 50, 100, 0.5, 0, image, true);
	DrawRotaGraphF(pos.x, pos.y,1.0,0,image, true);


	//DrawGraph(pos.x, pos.y, image, true);
}
