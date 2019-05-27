#include "Earth.h"
#include "GameTask.h"


Earth::Earth(VECTOR3 pos)
{
	mPos = pos;
	Init();
}


Earth::~Earth()
{
}

void Earth::Init(void)
{
	earthSize = 5.0;
	pos = mPos;
	for (int i = 0; i < EarthMax; i++)
	{

		EarthImage[i] = LoadDivGraph("image/earthAnimNC.png", 20, 20, 1, 100, 50, EarthImage, true);
			//LoadGraph("image/earthAnimNC.png");

	}
	planetImage = LoadSoftImage("image/earthCp.png");
	Size = (float)BasePlanet::GetRadius(EarthImage[0]) * ((float)earthSize/ 2);
}

void Earth::Update(void)
{
	auto HitCheck = [&] {
		int r = 0, g = 0, b = 0, a = 0;
		unsigned int rSize = (PLAYER_SIZE / 4);

		VECTOR3 playerPosR(lpGameTask.playerPos.x + rSize, lpGameTask.playerPos.y + rSize);
		VECTOR3 playerPosL(lpGameTask.playerPos.x - rSize, lpGameTask.playerPos.y - rSize);

		for (int x = 0; x < 100; x++)
		{
			for (int y = 0; y < 50; y++)
			{
				GetPixelSoftImage(planetImage, x, y, &r, &g, &b, &a);

				if (a > 60)
				{
					//VECTOR3 marsPos(pos.x - 64 + x, pos.y - 64 + y);
					VECTOR3 earthPosL((pos.x - 230) + (x * earthSize), (pos.y - 50) + (y * earthSize));
					VECTOR3 earthPosR((pos.x - 230) + (x + 2) * earthSize, (pos.y - 50) + (y + 2) * earthSize);

					//DrawBox(earthPosL.x, earthPosL.y, earthPosR.x, earthPosR.y, GetColor(255, 0, 0), true);
					//DrawPixel((int)marsPos.x, (int)marsPos.y, GetColor(255, 0, 0));
					if ((earthPosR.x > playerPosL.x && earthPosL.x < playerPosR.x))
					{
						if ((earthPosR.y > playerPosL.y && earthPosL.y < playerPosR.y))
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

	if (!lpGameTask.plPosMaxFlag)
	{
		pos = pos + lpGameTask.GetScrollPos();
	}

	/*for (float i = 0.0f; i < 16 ; i+= 0.1f)
	{
		VECTOR3 radianPos(pos.x + (Size * cos(i / 2)), pos.y + (Size * sin(i / 2)));

		DrawBox(radianPos.x - rSize, radianPos.y - rSize, radianPos.x + rSize, radianPos.y + rSize, GetColor(255, 0, 0), true);
		if (playerPosR.x > radianPos.x - rSize && lpGameTask.playerPos.x < radianPos.x + rSize)
		{

			if (playerPosR.y > radianPos.y - rSize && lpGameTask.playerPos.y < radianPos.y + rSize)
			{
				lpGameTask.SetLandCheck(true);
				lpGameTask.returnFlag = true;
			}
		}
	}*/

	if (HitCheck())
	{
		lpGameTask.SetLandCheck(true);
		lpGameTask.clearCheck = true;
		lpGameTask.returnFlag = true;
	}

	if (BasePlanet::PlanetFactry(gravity, r, pos) && !lpGameTask.GetLandCheck())
	{
	}


}

void Earth::Draw(void)
{

	DrawRotaGraphF(pos.x, pos.y, earthSize, 0, EarthImage[(animCnt++ / 15) % 19], true);

}
