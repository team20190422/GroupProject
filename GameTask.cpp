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

	int rtn_id;
	rtn_id = (this->*GtskPtr)();
	memcpy(KeyDataOld, KeyData, sizeof(KeyData));
	GetHitKeyStateAll(KeyData);
	//if (KeyData[KEY_INPUT_RETURN] && KeyDataOld[KEY_INPUT_RETURN]);
	
	return rtn_id;
}

GameTask::GameTask()
{
	SystemInit();
	GtskPtr = &GameTask::GameInit;
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
		return false;
	}
	GtskPtr = &GameTask::GameInit;
	SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

int GameTask::GameInit(void)
{
	DrawString(0, 0, "INIT", 0xffff00); 
	GtskPtr = &GameTask::GameTitle;
	ImageMng::GetInstance().SetID("TITLE", "image/タイトル.png");
	return 0;
}

int GameTask::GameTitle(void)
{
	//ゲームモード移行
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
		GtskPtr = &GameTask::GameMain;
	DrawString(0, 0, "GAME_TITLE", 0xffffff);
	return 0;
}

int GameTask::GameMain(void)
{
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
		GtskPtr = &GameTask::GameResult;
	DrawString(0, 0, "GAME_MAIN", 0xffffff);
	return 0;
}

int GameTask::GameResult(void)
{
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
		GtskPtr = &GameTask::GameInit;
	DrawString(0, 0, "GameResult", 0xffffff);
	return 0;
}
