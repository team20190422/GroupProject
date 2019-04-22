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
int GameTask::GameUpDate(void)
{
	//キー情報更新
	KeyMng::GetInstance().Update();

	switch (gameMode) {
	case GAME_INIT:
		GameInit();
		break;
	case GAME_TITLE:
		GameTitle();
		break;
	case GAME_MAIN:
		GameMain();
		break;
	case GAME_RESULT:
		GameResult();
		break;
		return 0;
	}
}

GameTask::GameTask()
{
	SystemInit();

	gameMode = GAME_INIT;
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
	return 0;
}

int GameTask::GameInit(void)
{
	DrawString(0, 0, "INIT", 0xffff00);
	if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_TITLE;
	ImageMng::GetInstance().SetID("TITLE", "image/タイトル.png");
	return 0;
}

int GameTask::GameTitle(void)
{
	//ゲームモード移行
	if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_MAIN;
	DrawString(0, 0, "GAME_TITLE", 0xffffff);
	return 0;
}

int GameTask::GameMain(void)
{
	if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_RESULT;
	DrawString(0, 0, "GAME_MAIN", 0xffffff);
	return 0;
}

int GameTask::GameResult(void)
{
	if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_INIT;
	DrawString(0, 0, "GameResult", 0xffffff);
	return 0;
}






