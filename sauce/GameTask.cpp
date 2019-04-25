#include "DxLib.h"
#include "GameTask.h"
#include "Player.h"
#include "BackGround.h"
#include "BasePlanet.h"
#include "Mars.h"
//#include"Enemy.h"
//#include "Stage.h"
#include"KeyMng.h"
#include"ImageMng.h"

#define  lpGameTask GameTask::GetInstance();

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

GameTask::GameTask()
{
	//GtskPtr = &GameTask::SystemInit;
	oldKey = 0;
}

GameTask::~GameTask()
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
	GtskPtr = &GameTask::GameInit;
	return 0;
}


int GameTask::GameInit(void)
{
	objList.clear();
	bpList.clear();

	DrawString(0, 0, "INIT", 0xffff00);
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		GtskPtr = &GameTask::GameTitle;
	}

	// newみたいなもの
	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	mars = AddBplist(std::make_shared<Mars>());

	(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	

	back = new BackGround();
	return 0;
}

int GameTask::GameTitle(void)
{
	//ゲームモード移行
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		GtskPtr = &GameTask::GameMain;
	}
	DrawString(0, 0, "GAME_TITLE", 0xffffff);
	return 0;
}

int GameTask::GameMain(void)
{
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		GtskPtr = &GameTask::GameResult;
	}

	std::vector<BackGround*>::iterator itrBG = backVec.begin();

	if (count <= 300)
	{
		count++;
		back = new BackGround();
		backVec.push_back(back);
	}
	else if ( count > 300 && count <= 600)
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
	for (auto itr : bpList)
	{
		// すべての惑星のUpdate
		itr->Update();
		itr->Draw();
	}
	for (auto itr : objList)
	{
		playerPos = (*player)->GetPos();
		playerAngle = (*player)->GetAngle();
		itr->Update();
		itr->Draw();
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
	DrawFormatString(10, 100, GetColor(255, 255, 255), "X　%d",count);

	DrawString(0, 0, "GAME_MAIN", 0xffffff);
	return 0;
}

int GameTask::GameResult(void)
{
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		GtskPtr = &GameTask::GameInit;
	}
	DrawString(0, 0, "GameResult", 0xffffff);
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




