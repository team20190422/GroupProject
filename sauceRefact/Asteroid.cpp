#include "Asteroid.h"
#include "Obstracle.h"
#include "PlayerOrbit.h"
#include "UnivGravityCalc.h"
#include "GameTask.h"


constexpr int OBST_SIZE = 25;

std::vector<VECTOR3> Asteroid::PtoPVector;
std::vector<float> Asteroid::distance;

Asteroid::Asteroid(VECTOR3 pos, int AstCnt, UnivGravityCalc& u) : univ(u)
{
	mPos = pos;
	Init();
	animNum = (AstCnt % 3);
	astCount = AstCnt;
}

Asteroid::~Asteroid()
{
}

const VECTOR3 & Asteroid::GetPos(void)
{
	return pos;
}

bool Asteroid::SetPos(VECTOR3 pos)
{
	this->pos = pos;
	return false;
}

void Asteroid::Init(void)
{
	AsteroidImage[0] = LoadGraph("image/asteroid01.png");
	AsteroidImage[1] = LoadGraph("image/asteroid02.png");
	AsteroidImage[2] = LoadGraph("image/asteroid03.png");

	planetImage[0] = LoadSoftImage("image/asteroid01.png");
	planetImage[1] = LoadSoftImage("image/asteroid02.png");
	planetImage[2] = LoadSoftImage("image/asteroid03.png");

	for (int i = 0; i < 3; i++)
	{
		lpGameTask.SetSoftImg(i, planetImage[i]);
	}
	pos = mPos;

	univ.AddAstPos(pos);
	univ.AddAstMass(mass);

	asteroidSize = 1.8f;
	gravity = 1.3f;
	mass = 3000.0f;
	animNum = 0;
	astCount = 0;
}

void Asteroid::Update(void)
{
	unsigned int rSize = (PLAYER_SIZE / 2);
	VECTOR3 playerPosR(lpGameTask.playerPos.x + rSize, lpGameTask.playerPos.y + rSize);
	VECTOR3 playerPosL(lpGameTask.playerPos.x - rSize, lpGameTask.playerPos.y - rSize);
	VECTOR3 radianPos(pos.x + (r * cos(1 / 2)), pos.y + (r * sin(1 / 2)));

	unsigned int meteoHarf = (OBST_SIZE / 2);
	VECTOR3 obstPosR(lpGameTask.GetObstPos().x + meteoHarf, lpGameTask.GetObstPos().y + meteoHarf);
	VECTOR3 obstPosL(lpGameTask.GetObstPos().x - meteoHarf, lpGameTask.GetObstPos().y - meteoHarf);

	lpGameTask.targetSize = r;
	lpGameTask.targetVec = (radianPos - pos);
	if (!lpGameTask.GetHitCheck() && !lpGameTask.GetLandCheck())
	{
		if (!lpGameTask.plPosMaxFlag)
		{
			pos = pos + lpGameTask.GetScrollPos();
		}
	}

	int r = 0, g = 0, b = 0, a = 0;
	if (!lpGameTask.GetDB())
	{
		for (int x = 0; x < IMG_SIZE; x++)
		{
			for (int y = 0; y < IMG_SIZE; y++)
			{
				GetPixelSoftImage(planetImage[animNum], x, y, &r, &g, &b, &a);

				if (a > 0)
				{
					auto addPos = VECTOR3(x + 2, y + 2);
					VECTOR3 asteroidPosL((pos.x - IMG_SIZE) + (x * asteroidSize), (pos.y - IMG_SIZE) + (y * asteroidSize));
					VECTOR3 asteroidPosR((pos.x - IMG_SIZE) + addPos.x * asteroidSize, (pos.y - IMG_SIZE) + addPos.y * asteroidSize);

					if (asteroidPosR.x > playerPosL.x + 3 && asteroidPosL.x < playerPosR.x - 3)
					{
						if (asteroidPosR.y > playerPosL.y + 3 && asteroidPosL.y < playerPosR.y - 3)
						{
							lpGameTask.SetHitCheck(true);
						}
					}

					if (asteroidPosR.x > obstPosL.x && asteroidPosL.x < obstPosR.x)
					{
						if (asteroidPosR.y > obstPosL.y && asteroidPosL.y < obstPosR.y)
						{
							lpGameTask.SetHitObstAst(true);
						}
					}
				}
			}
		}
	}

	lpGameTask.SetAnimNum(animNum);
	lpGameTask.SetAstPos(astCount - 1, pos);

	univ.SetAstPos(astCount - 1, pos);
}

void Asteroid::Draw(void)
{
	DrawRotaGraphF(pos.x, pos.y, asteroidSize, 0, AsteroidImage[animNum], true);
}

