#include "DxLib.h"
#include "GameTask.h"
//#include "Player.h"
//#include"Enemy.h"
//#include "Stage.h"
#include"KeyMng.h"
#include"ImageMng.h"

constexpr int SCREEN_SIZE_X(450);
constexpr int SCREEN_SIZE_Y(800);

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
	DrawString(0, 0, "INIT", 0xffff00);
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		GtskPtr = &GameTask::GameTitle;
	}
	ImageMng::GetInstance().SetID("TITLE", "image/タイトル.png");
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






