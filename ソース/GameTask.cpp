#include "DxLib.h"
#include "GameTask.h"
#include "Player.h"
#include "BackGround.h"
#include "Obstracle.h"
#include "BasePlanet.h"
#include "Mars.h"
#include "Earth.h"
//#include"Enemy.h"
//#include "Stage.h"
#include"KeyMng.h"
#include"ImageMng.h"


GameTask *GameTask::s_Instance = nullptr;
int GameTask::GameUpdate(void)
{
	int rtn_id;
	//キー情報更新
	KeyMng::GetInstance().Update();

	rtn_id = (this->*GtskPtr)();

	return rtn_id;
}


int GameTask::SetCount()
{
	return count;
}

bool GameTask::HitCheck(RECT rect1, RECT rect2)
{
	if (rect1.left <= rect2.right &&rect1.top <= rect2.bottom
		&&rect1.right >= rect2.left &&rect1.bottom >= rect2.top) {
		return true;
	}
	else {
		return false;
	}
}

const bool & GameTask::GetHitCheck(void)
{
	return this->hitCheck;
}

void GameTask::SetHitCheck(bool hitCheck)
{
	this->hitCheck = hitCheck;
}

const bool & GameTask::GetLandCheck(void)
{
	return landingCheck;
}

void GameTask::SetLandCheck(bool landing)
{
	landingCheck = landing;
}

const int & GameTask::GetEnergy(void)
{
	return Energy;
}

void GameTask::SetEnergy(int energy)
{
	Energy = energy;
}

const VECTOR3 & GameTask::GetScrollPos(void)
{
	return ScrollPos;
}

void GameTask::SetScrollPos(VECTOR3 addPos)
{
	ScrollPos.y = addPos.y;
}

GameTask::GameTask()
{
	//GtskPtr = &GameTask::SystemInit;
	oldKey = 0;
}

GameTask::~GameTask()
{

}

void GameTask::Die(void)
{

}

void GameTask::Create(void)
{
	if (!s_Instance) {
		s_Instance = new GameTask();
	}
}


int GameTask::SystemInit(void)
{
	SetWindowText("スイングバイ");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	for (int j = 0; j < 11; j++)
	{
		DieAnim[j] = LoadDivGraph("image/爆発_大.png", 11, 11, 1, 115, 100, DieAnim,true);
		//DieAnim[j] = LoadGraph("image/爆発_大.png");
	}

	GtskPtr = &GameTask::GameTitle;
	return 0;
}


int GameTask::GameInit(void)
{
	objList.clear();
	bpList.clear();

	DrawString(0, 0, "INIT", 0xffff00);
	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	obstracle = AddObjlist(std::make_shared<Obstracle>());

	earth = AddBplist(std::make_shared<Earth>(VECTOR3(225, SCREEN_SIZE_Y * 2)));

	mars = AddBplist(std::make_shared<Mars>(VECTOR3(200,200)));

	//mars = AddBplist(std::make_shared<Mars>(VECTOR3(225, 900)));

	(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);

	//ImageMng::GetInstance().SetID("TITLE", "image/タイトル.png");
	back = new BackGround();

	GtskPtr = &GameTask::GameMain;

	return 0;
}

int GameTask::GameTitle(void)
{
	ClsDrawScreen();

	//ゲームモード移行
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		GtskPtr = &GameTask::GameInit;
	}
	DrawString(0, 0, "GAME_TITLE", 0xffffff);
	ScreenFlip();
	return 0;
}

int GameTask::GameMain(void)
{
	ClsDrawScreen();


	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		landingCheck = false;
		GtskPtr = &GameTask::GameResult;
	}

	std::vector<BackGround*>::iterator itrBG = backVec.begin();

	if (count <= 300)
	{
		count++;
		back = new BackGround();
		backVec.push_back(back);
	}
	else if (count > 300 && count <= 600)
	{
		count++;
		back = new BackGround();
		backVec.push_back(back);
	}

	for (auto itrBG : backVec)
	{
		itrBG->Update();
		itrBG->Draw();
	}

	distance = { DISTANCE_MAX };
	time++;

	for (auto itr : bpList)
	{

		// すべての惑星のUpdate
		if (!GetHitCheck() || time < 10)
		{
			itr->Update();
		}

		itr->Draw();
		if (itr->GetDistance() < distance)
		{

			PandPvec = itr->GetVec();
			if(itr->GetDistance() > 0)
				distance = itr->GetDistance();

		}

	}

	for (auto itr : objList)
	{
		//(*player)->GetPos();
		playerPos = (*player)->GetPos();
		playerAngle = (*player)->GetAngle();
		playerVec = (*player)->GetVec();

		if (!GetHitCheck())
		{
			itr->Update();
			itr->Draw();

		}
		else
		{
			//itr->SetVec(VECTOR3(0, 0));
			if (AnimTime++ % 10 == 0)
			{
				AnimCnt++;
			}
			//DrawBox(playerPos.x, playerPos.y, playerPos.x + 200, playerPos.y + 200, 0xffffff, true);
			DrawRotaGraph(playerPos.x, playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
			DrawString(playerPos.x, playerPos.y, "やられた", 0xffffff);
		}
		
		if (landingCheck && landingFlag)
		{
			SetHitCheck(false);

			if (checkCnt++ > 120 && !returnFlag)
			{
				pltrgPos = VECTOR3(playerPos.x + targetVec.x * 2, playerPos.y);
				(*player)->SetPos(pltrgPos);
				SetScrollPos(targetVec);
				setCount = true;
				landingCheck = false;
				checkCnt = 0;
				pltrgPos = { 0,0 };
			}
		}
	}
	// 背景の削除
	itrBG = backVec.begin();
	while (itrBG != backVec.end())
	{
		if ((*itrBG)->removeFlag == true)
		{
			count--;
			delete(*itrBG);
			itrBG = backVec.erase(itrBG);
			break;
		}
		else
		{
			itrBG++;
		}
	}

	//矩形の当たり判定
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) {
		DrawBox(100, 100, 200, 200, GetColor(255, 255, 255), true);
	}

	// 着陸成功時
	if (landingCheck && landingFlag)
	{
		if (landingCnt[0] > 0)
		{
			landingCnt[0] -= 20;
		}
		else
		{
			// ﾐｯｼｮﾝｸﾘｱ
			if (returnFlag && clearCheck && landingCheck && landingFlag)
			{

				// ﾐｯｼｮﾝｸﾘｱ
				GtskPtr = &GameTask::GameResult;
			}
			// ｸﾘｱ可能状態にする
			clearCheck = true;
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	else
	{
		if (landingCnt[0] < 255)
		{
			landingCnt[0] += 20;
		}

		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}

	// 燃料少量時
	if (Energy < 200)
	{
		if (landingCnt[1] > 0 && !energyAnim)
		{
			landingCnt[1] -= 10;
		}
		else
		{
			energyAnim = true;
		}

		if (landingCnt[1] < 255 && energyAnim)
		{
			landingCnt[1] += 10;
		}
		else
		{
			energyAnim = false;
		}
		SetDrawBright(255, landingCnt[1], landingCnt[1]);
	}

	if (clearCheck)
	{
		clearCnt++;
	}

	// 着陸成功時の多少の無敵時間
	if (clearCheck && (landingCheck || landingFlag))
	{
		if (clearCnt < 60)
		{
			SetHitCheck(false);
		}
		else
		{
			clearCnt = 0;
		}
	}

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "着陸 %d flag %d hit %d clear %d", landingCheck, landingFlag, hitCheck, clearCheck);
	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "posX %f posY %f", playerPos.x, playerPos.y);

	DrawFormatStringF(10, 550, GetColor(255, 255, 255), "targetX %f targetY %f", targetVec.x, targetVec.y);
	DrawFormatStringF(10, 650, GetColor(255, 255, 255), "setPosX %f setPosX %f", pltrgPos.x, pltrgPos.y);


	ScreenFlip();

	return 0;
}

int GameTask::GameResult(void)
{

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		time = 0;
		AnimCnt = 0;
		clearCheck = false;
		landingCheck = false;
		landingFlag = false;
		returnFlag = false;
		getSample = false;
		GtskPtr = &GameTask::GameInit;
	}
	if (landingCnt[0] < 255)
	{
		landingCnt[0] += 20;
	}

	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);


	DrawString(0, 0, "GameResult", 0xffffff);


	SetFontSize(50);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("Ailerons");
	DrawString(SCREEN_SIZE_X / 2 - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "GAME CLEAR", 0xffffff);
	SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("MSゴシック");

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "着陸 %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);

	ScreenFlip();

	return 0;
}

std::list<obj_ptr>::iterator GameTask::AddObjlist(obj_ptr && objPtr)
{
	objList.push_back(objPtr);
	auto itr = objList.end();
	itr--;
	return itr;
}

std::list<bp_ptr>::iterator GameTask::AddBplist(bp_ptr && bpPtr)
{
	bpList.push_back(bpPtr);
	auto itr = bpList.end();
	itr--;
	return itr;
}


