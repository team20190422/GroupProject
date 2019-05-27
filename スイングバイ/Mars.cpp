#include <DxLib.h>
#include "Mars.h"
#include "GameTask.h"

Mars::Mars(VECTOR3 pos, int marsCnt)
{
	mPos = pos;
	imageCnt = marsCnt;
	Init();
}

Mars::~Mars()
{
}

void Mars::Init()
{
	image = (imageCnt == 1 ? LoadGraph("image/Mars.png") : LoadGraph("image/JupiterTest.png"));
	planetImage = (imageCnt == 1 ? LoadSoftImage("image/Mars.png") : LoadSoftImage("image/JupiterTest.png"));
	nextPlanet = LoadGraph("image/nextPlanet.png");
	mokutekichi = LoadGraph("image/mokutekichi.png");
	r = (float)BasePlanet::GetRadius(image);
	GetGraphSize(image, &imageSize.x, &imageSize.y);
	pos = mPos;
}

void Mars::Update()
{
	auto HitCheck = [&] {
		int r = 0, g = 0, b = 0, a = 0;
		unsigned int rSize = (PLAYER_SIZE / 4);

		VECTOR3 playerPosR(lpGameTask.playerPos.x + rSize, lpGameTask.playerPos.y + rSize);
		VECTOR3 playerPosL(lpGameTask.playerPos.x - rSize, lpGameTask.playerPos.y - rSize);

		for (int x = 0; x < imageSize.x; x++)
		{
			for (int y = 0; y < imageSize.y; y++)
			{
				GetPixelSoftImage(planetImage, x, y, &r, &g, &b, &a);

				if (a > 60)
				{
					VECTOR3 marsPos(pos.x - (imageSize.x / 2) + x, pos.y - imageSize.y / 2 + y);
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
	VECTOR3 radianPos(pos.x + (r * cos(-imageCnt / 2)), pos.y + (r * sin(-imageCnt / 2)));


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
			//DrawString((int)lpGameTask.playerPos.x, (int)lpGameTask.playerPos.y + rSize, "Get", 0xffffff, true);
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
	DrawRotaGraphF(pos.x, pos.y,1.0,0,image, true);
	DrawRotaGraph(55, 110, (imageCnt == 1 ? 0.5 : 0.3), 0, image, true);
	DrawRotaGraph(80, 55, 1, 0, mokutekichi, true);
	DrawRotaGraph(55, 110, 1.0, 0, nextPlanet, true);

	//DrawGraph(pos.x, pos.y, image, true);
}
