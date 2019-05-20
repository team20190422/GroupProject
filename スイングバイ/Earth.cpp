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
	Size = (float)BasePlanet::GetRadius(EarthImage[0]) * ((float)earthSize/ 2);
}

void Earth::Update(void)
{

	unsigned int rSize = (PLAYER_SIZE / 2);
	VECTOR3 playerPosR(lpGameTask.playerPos.x + rSize, lpGameTask.playerPos.y + rSize);

	if (!lpGameTask.plPosMaxFlag)
	{
		pos = pos + lpGameTask.GetScrollPos();
	}

	for (float i = 0.0f; i < 16 ; i+= 0.1f)
	{
		VECTOR3 radianPos(pos.x + (Size * cos(i / 2)), pos.y + (Size * sin(i / 2)));

		DrawBox(radianPos.x - rSize, radianPos.y - rSize, radianPos.x + rSize, radianPos.y + rSize, GetColor(255, 0, 0), true);
		if (playerPosR.x > radianPos.x - rSize && lpGameTask.playerPos.x < radianPos.x + rSize)
		{

			if (playerPosR.y > radianPos.y - rSize && lpGameTask.playerPos.y < radianPos.y + rSize)
			{
				DrawString(lpGameTask.playerPos.x, lpGameTask.playerPos.y + rSize, "Get", 0xffffff, true);
				lpGameTask.SetLandCheck(true);
				lpGameTask.returnFlag = true;
			}
		}
	}




}

void Earth::Draw(void)
{

	DrawRotaGraphF(pos.x, pos.y, earthSize, 0, EarthImage[(animCnt++ / 15) % 19], true);

}
