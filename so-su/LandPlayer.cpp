#include "LandPlayer.h"
#include "ImageMng.h"

constexpr float PI = 3.1415;
constexpr int SPC_SIZE_X = 40;
constexpr int SPC_SIZE_Y = 28;

LandPlayer::LandPlayer(const int(&trgKey)[6], const int(&oldKey)[6]) :Obj(trgKey, oldKey)
{
	motherPos = { (float)SCREEN_SIZE_X / 2,  -20 };
	LoadDivGraph("image/capsuleParaAnim.png", 10, 10, 1, 15, 30, capsulePara, true);
	BG = LoadGraph("image/landBG.png");
	mapSoft = LoadSoftImage("image/landMap01.png");
	pos = { 50,-500 };
}


LandPlayer::~LandPlayer()
{
}

void LandPlayer::Draw(void)
{
	DrawGraph(0, 0, BG, true);
	if (lpGameTask.darkFlag == false)
	{
		color = GetColor(114, 56, 36);
		DrawCircle(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 500, color, true);
		if (injectionFlag == true)
		{
			DrawRotaGraph(cupPos.x, cupPos.y, size, 0, ImageMng::GetInstance().SetID("image/capsule.png"), true);
		}
		else
		{
		}
		DrawRotaGraph(motherPos.x, motherPos.y, 2, 0, IMAGE_ID(imageName), true);
		//DrawFormatString(SCREEN_SIZE_X - 100, SCREEN_SIZE_Y / 2, 0xffffff, "%d", GetFontSize());
		SetFontSize(15);
		DrawFormatString(SCREEN_SIZE_X - 150, SCREEN_SIZE_Y - 15,0xffffff ,"SPACEでスキップ");
		SetFontSize(20);
	}
	else
	{
		if (!shieldFlag && lpGameTask.darkFlag == true && !lpGameTask.GetDarkFlag2())
		{
			for (int i = 1; i < SCREEN_SIZE_Y; i++)
			{
				if (i % colTmp == 0)
				{
					RGB[0];
					RGB[1];
					RGB[2] -= 30;
					if (RGB[0] >= 255)
						RGB[0] = 255;
					else if (RGB[0] <= 0)
						RGB[0] = 0;

					if (RGB[1] >= 255)
						RGB[1] = 255;
					else if (RGB[1] <= 0)
						RGB[1] = 0;

					if (RGB[2] >= 255)
						RGB[2] = 255;
					else if (RGB[2] <= 0)
						RGB[2] = 0;

					colTmp2 /= 2;
					colTmp += colTmp2;
				}
				else
				{
				}
				// ｸﾞﾗﾃﾞｰｼｮﾝさせる
				DrawLine(0, i, SCREEN_SIZE_X, i, GetColor(RGB[0], RGB[1], RGB[2]), true);
			}
			DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 3, 0, ImageMng::GetInstance().SetID("image/landMap01.png"), true);
			DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 3, 0, ImageMng::GetInstance().SetID("image/landMap02.png"), true);
			DrawGraph(105, 44, ImageMng::GetInstance().SetID("image/sokudoUI.png"), true);
			DrawGraph(95, 56, ImageMng::GetInstance().SetID("image/speedUI_under.png"), true);
			DrawGraph(100, 77, ImageMng::GetInstance().SetID("image/kyoriUI.png"), true);
			DrawGraph(65, 89, ImageMng::GetInstance().SetID("image/speedUI_under.png"), true);
			DrawRotaGraph(60, 60, 2, spCAngleF, ImageMng::GetInstance().SetID("image/suihei01.png"), true);
			DrawRotaGraph(60, 60, 2, 0, ImageMng::GetInstance().SetID("image/suihei02.png"), true);
			DrawRotaGraph(60, 60, spCSize, spCAngleF, ImageMng::GetInstance().SetID("image/spCraft.png"), true);
			DrawRotaGraph(pos.x, pos.y + 45, 1.5, spCAngleF, ImageMng::GetInstance().SetID("image/spCraft.png"), true);
			DrawRotaGraph(paraPos.x, paraPos.y, 1.5, paraAngle, ImageMng::GetInstance().SetID("image/capsuleParaL02.png"), true);
		}
		else if (pos.y > 0)
		{
			if (anim >= 8)
			{
				anim = 8;
			}
			else
			{
				anim = (animCnt++ / 125) % 10;
			}
		}
		else
		{
			anim = 0;
		}
		if (shieldFlag)
		{
			DrawRotaGraph(pos.x, pos.y, 2.5, angle, capsulePara[anim], true);
			DrawRotaGraph(shieldPos.x, shieldPos.y, 2.5, shieldAngle, ImageMng::GetInstance().SetID("image/shield.png"), true);
			SetFontSize(15);
			DrawFormatString(SCREEN_SIZE_X - 150, SCREEN_SIZE_Y - 15, 0xffffff, "SPACEでスキップ");
			SetFontSize(20);
		}
	}
	//DrawFormatString(SCREEN_SIZE_X /2, SCREEN_SIZE_Y/2, 0xffffff, "scene:%d",scene);
	//DrawFormatString(0, 15, 0xffffff, "motherPos.x:%f,motherPos.y:%f", motherPos.x, motherPos.y);
	//DrawFormatString(0, 30, 0xffffff, "cupPos.x:%f,cupPos.y:%f", cupPos.x, cupPos.y);
	//DrawFormatString(0, 45, 0xffffff, "speed:%f", speed);
}

void LandPlayer::Update(void)
{
	// ｼｰﾝｽｷｯﾌﾟ
	if (KeyMng::GetInstance().trgKey[P1_SPACE] && skipCnt == 0)
	{
		shieldFlag = false;
		lpGameTask.SetCupLandCheck(true);
		lpGameTask.SetDarkFlag2(true);
		skipFlag = true;
		skipCnt++;
	}

	count++;
	if (motherPos.y < SCREEN_SIZE_Y / 2)
	{
		countF += 0.001f;
	}
	else
	{
		countF -= 0.001f;
		if (sinFlag == true)
		{
			countF = 0.0f;
		}
	}
	if (motherPos.y < SCREEN_SIZE_Y / 4)
	{
		motherPos.y += 0.03f + countF;
	}
	else
	{
		if (cupPos.y == 0)
		{
			cupPos = motherPos;
			motherPos.y += 20;
		}
		sinFlag = true;
	}

	if (sinFlag == true)
	{
		motherPos.y = -sin(PI * 2 / 600 * count) * 5;
		motherPos.y += SCREEN_SIZE_Y / 4;

		colorPos = GetPixel(cupPos.x, cupPos.y + 10);
		if (colorPos == color);
		{
			if (size >= 0)
			{
				size -= 0.005f;
			}
			else
			{
				scene = 1;
				lpGameTask.SetCupLandCheck(true);
			}
		}
	}
	if (count > 1000)
	{
		injectionFlag = true;
	}
	if (injectionFlag == true)
	{
		cupPos.y += 1.0f;
	}

	if (shieldFlag)
	{
		if (anim < 5 && lpGameTask.darkFlag == true && !lpGameTask.GetDarkFlag2())
		{
			angle = -0.3f;
			shieldAngle = angle;
			shieldPos.x = pos.x + 8;
			shieldPos.y = pos.y + 31;
			pos.x += 0.3f;
			pos.y += 0.6f;
		}
		else
		{
			if (angle < 0.0f)
			{
				angle += 0.001f;
			}
			else
			{
				angle = 0.0f;
			}
			shieldPos.x -= 0.2f;
			shieldPos.y += 0.8f;
			shieldAngle += 0.01f;
			pos.y += 0.40f;
		}
	}
	else

	{
		scene = 2;
		if (SCREEN_SIZE_Y / 4 < pos.y && scene == 2)
		{
			separateFlag = true;
		}

		if (skipFlag == true && skipCnt == 1)
		{
			pos.x = SCREEN_SIZE_X / 2;
			pos.y = -100;
			skipCnt++;
		}

		if (separateFlag)
		{
			pos.y += 0.5f;
			paraPos.x -= 0.20f;
			paraPos.y += 0.30f;
			paraAngle -= 0.0003f;
			SetMove();
		}
		else
		{
			pos.y += 0.40f;
			paraPos = pos;
		}
	}

	if (pos.y - 100 > SCREEN_SIZE_Y)
	{
		lpGameTask.SetDarkFlag2(true);
		pos.x = SCREEN_SIZE_X / 2;
		pos.y = -100;
		anim = 0;
		animCnt = 0;						// DrawRotaGraph(pos.x, pos.y, 2, 0, capsuleParaLAnim[anim], true);のanimが1から始まってしまうため
		shieldFlag = false;
	}

	int spCHarf = spCSize / 2;
	VECTOR3 spCraftPosR((SPC_SIZE_X * spCSize) + spCHarf, (SPC_SIZE_Y * spCSize) + spCHarf);
	VECTOR3 spCraftPosL((SPC_SIZE_X * spCSize) - spCHarf, (SPC_SIZE_Y * spCSize) - spCHarf);

	int r = 0, g = 0, b = 0, a = 0;
	int x = 0, y = 0;
	int t = 0, u = 0, o = 0;

	for (int i = 0; i < mapImageSize.x; i++)
	{
		for (int j = SCREEN_SIZE_Y / 2; j < mapImageSize.y; j++)
		{
			GetPixelSoftImage(mapSoft, i, j, &r, &g, &b, &a);

			if (a > 0)
			{
				VECTOR3 mapPosL(mapImageSize.x + i, mapImageSize.y + j);
				VECTOR3 mapPosR(mapImageSize.x + (i- 2), mapImageSize.y + (j - 2));
				DrawBox(mapPosL.x, mapPosL.y, mapPosR.x, mapPosR.y, 0xff0000,true);
				t = r;
				u = g;
				o = b;
			}
			//x = i;
			//y = j;
		}
	}
	//GetPixelSoftImage(mapSoft, 449, 799, &r, &g, &b, &a);
	DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0xffffff, "R:%d G:%d B:%d", t, u, o);

}

void LandPlayer::SetMove(void)
{
	pos.x += vx;
	pos.y += vy * speed;
	spCAngleF += spCAngle + rolInc;
	if (KeyMng::GetInstance().newKey[P1_UP])
	{
		if (speed < 1.0f)
		{
			speed += 0.003f;
		}
		vx = sin(spCAngleF) * speed;
		vy = -cos(spCAngleF) * speed;
	}
	else
	{
		if (speed > -1.0f)
		{
			speed -= 0.003f;
		}
	}
	if (KeyMng::GetInstance().newKey[P1_RIGHT])
	{
		spCAngle += 0.0001f;
		lrFlag = 1;
	}
	else if (KeyMng::GetInstance().newKey[P1_LEFT])
	{
		spCAngle -= 0.0001f;
		lrFlag = -1;
	}

	if (lrFlag == 1)
	{
		rolInc += 0.000005f;
	}
	else if (lrFlag == -1)
	{
		rolInc -= 0.000005f;
	}
}
