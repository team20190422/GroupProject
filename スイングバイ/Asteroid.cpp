#include "Asteroid.h"
#include "GameTask.h"


Asteroid::Asteroid(VECTOR3 pos, int AstCnt)
{
	mPos = pos;
	animNum = (AstCnt % 2);
	Init();
}


Asteroid::~Asteroid()
{
}

void Asteroid::Init(void)
{
	asteroidSize = 2.0;
	pos = mPos;

	AsteroidImage[0] = LoadGraph("image/asteroid01.png");
	AsteroidImage[1] = LoadGraph("image/asteroid02.png");
	AsteroidImage[2] = LoadGraph("image/asteroid03.png");
	/*for (int j = 0; j < ImageMax; j++)
	{
		AsteroidImage[j] = LoadDivGraph("image/Asteroid.png", 3, 3, 1, 40, 40, AsteroidImage, true);
	}*/
	planetImage[0] = LoadSoftImage("image/asteroid01.png");
	planetImage[1] = LoadSoftImage("image/asteroid02.png");
	planetImage[2] = LoadSoftImage("image/asteroid03.png");

	imageSize = 40;
	Size = (float)BasePlanet::GetRadius(AsteroidImage[animNum])* ((float)asteroidSize / 2);

}

void Asteroid::Update(void)
{
	unsigned int rSize = (PLAYER_SIZE / 2);
	VECTOR3 playerPosR(lpGameTask.playerPos.x + rSize, lpGameTask.playerPos.y + rSize);
	VECTOR3 playerPosL(lpGameTask.playerPos.x - rSize, lpGameTask.playerPos.y - rSize);
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

	int r = 0,g = 0,b = 0,a = 0;

	for (int x = 0; x < imageSize; x++)
	{
		for (int y = 0; y < imageSize; y++)
		{
			GetPixelSoftImage(planetImage[animNum], x, y, &r, &g, &b, &a);

			if (a > 0)
			{
				VECTOR3 asteroidPosL((pos.x - imageSize) + (x * asteroidSize), (pos.y - imageSize) + (y * asteroidSize));
				VECTOR3 asteroidPosR((pos.x - imageSize) + (x + 2) * asteroidSize, (pos.y - imageSize) + (y + 2) * asteroidSize);


				DrawBox(asteroidPosL.x, asteroidPosL.y, asteroidPosR.x, asteroidPosR.y, GetColor(255, 0, 0), true);
				if ((asteroidPosR.x > playerPosL.x && asteroidPosL.x < playerPosR.x))
				{
					if ((asteroidPosR.y > playerPosL.y && asteroidPosL.y < playerPosR.y))
					{
						lpGameTask.SetHitCheck(true);
					}
				}
			}
		}
	}

	if (BasePlanet::PlanetFactry(gravity, Size, pos))
	{

		//lpGameTask.SetHitCheck(true);
	}
	

}

void Asteroid::Draw(void)
{
	DrawRotaGraphF(pos.x, pos.y, asteroidSize, 0, AsteroidImage[animNum], true);
}

