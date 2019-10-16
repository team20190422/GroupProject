#include "Earth.h"
#include "GameTask.h"
#include "UnivGravityCalc.h"

Earth::Earth(VECTOR3 pos, UnivGravityCalc& u):univ(u)
{
	mPos = pos;
	Init();
}


Earth::~Earth()
{
}

const VECTOR3 & Earth::GetPos(void)
{
	return pos;
}

bool Earth::SetPos(VECTOR3 pos)
{
	this->pos = pos;
	return false;
}

void Earth::Init(void)
{
	earthSize = 5.0;
	pos = mPos;
	for (int i = 0; i < EarthMax; i++)
	{
		EarthImage[i] = LoadDivGraph("image/earthAnimNC.png", 20, 20, 1, 100, 50, EarthImage, true);
	}
	planetImage = LoadSoftImage("image/earthCp.png");
//	Size = (float)BasePlanet::GetRadius(EarthImage[0]) * ((float)earthSize/ 2);

	animCnt = 0;
	gravity = 2.0f;
	mass = 7000.0f;

	univ.AddAstMass(mass);
	univ.AddAstPos(pos);
}

void Earth::Update(void)
{
	lpGameTask.SetErPosY(pos.y);

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
					VECTOR3 earthPosL((pos.x - 230) + (x * earthSize), (pos.y - 50) + (y * earthSize));
					VECTOR3 earthPosR((pos.x - 230) + (x + 2) * earthSize, (pos.y - 50) + (y + 2) * earthSize);

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

	univ.SetAstPos(lpGameTask.planetMax - 2, pos);

	if (HitCheck())
	{
		lpGameTask.SetLandCheck(true);
		lpGameTask.clearCheck = true;
		lpGameTask.returnFlag = true;
	}
}

void Earth::Draw(void)
{
	DrawRotaGraphF(pos.x, pos.y, earthSize, 0, EarthImage[(animCnt++ / 15) % 19], true);
}
