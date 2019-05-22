#include "LandPlayer.h"
#include "ImageMng.h"


LandPlayer::LandPlayer(const int(&trgKey)[7], const int(&oldKey)[7]) :Obj(trgKey, oldKey)
{
	pos = { (float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y / 4 };
}


LandPlayer::~LandPlayer()
{
}

void LandPlayer::Draw(void)
{
	// ’n–Ê
	for (int x = 0; x < SCREEN_SIZE_X; x++)
	{
		for (int y = 0; y < SCREEN_SIZE_Y; y++)
		{
			auto randomY = GetRand(1000);

			
			if (y > SCREEN_SIZE_Y / 2 && y < SCREEN_SIZE_Y - SCREEN_SIZE_Y / 4)
			{
				SetDrawBright(100, 100, 100);
				DrawPixel(x, y + randomY, GetColor(255, 255, 255));
			}
			else if (y >= SCREEN_SIZE_Y - SCREEN_SIZE_Y / 4)
			{
				SetDrawBright(255, 255, 255);
				DrawPixel(x, y, GetColor(255, 255, 255));
			}
		}
	}
	SetDrawBright(255, 255, 255);
	DrawRotaGraph(pos.x, pos.y, 1, 0, IMAGE_ID(imageName), true);

}

void LandPlayer::Update(void)
{
}
