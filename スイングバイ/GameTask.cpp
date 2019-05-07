#include "DxLib.h"
#include "GameTask.h"
#include "Player.h"
#include "BackGround.h"
#include "Obstracle.h"
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

	DrawString(0, 0, "INIT", 0xffff00);
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		GtskPtr = &GameTask::GameTitle;
	}
	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	//back = AddObjlist(std::make_shared<BackGround>());
	obstracle = AddObjlist(std::make_shared<Obstracle>());

	(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 1, 32 / 1),VECTOR2(2,1), VECTOR2(1, 0), 1.0f);
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
	else if (count > 300 && count <= 600)
	{
		count++;
		back = new BackGround();
		backVec.push_back(back);
	}

	for (auto itrBG : backVec)
	{
		/*プレイヤーのスピードが0より小さいか又プレイヤーの角度が2.0より大きければ
		　バック画面のスクロールを逆（下から上）にする*/
		if (((*player)->GetSpeed() < (float)0.0)||((*player)->GetAngle() > (double)2.0)) {
			itrBG->SetFlag(true);//下から上にスクロール
			//プレイヤーの速度を表示
			DrawFormatString(10, 220, 0xffffff, "GetSpeed % 2f", (*player)->GetSpeed());
		}
		/*プレイヤーのスピードが1より大きいか又はプレイヤーの角度が4.5より小さいなら
			バック画面のスクロールを元（上から下）にする*/
		else if (((*player)->GetSpeed() > (float)1.0)||((*player)->GetAngle() < (double)4.5)) {
			itrBG->SetFlag(false);//上から下にスクロール
			//プレイヤーの速度を表示
			DrawFormatString(10, 220, 0xffffff, "GetSpeed % 2f", (*player)->GetSpeed());
		}	
		itrBG->Update();
		itrBG->Draw();
	}

	for (auto itr : objList)
	{
		itr->Update();
		itr->Draw();
	}
	
	//矩形の当たり判定(プレイヤーとオブストラクル(障害物))
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) {
		DrawBox(100, 100, 200, 200, GetColor(255, 255, 255), true);
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

	DrawFormatString(10, 190, GetColor(255, 255, 255), "X　%d",count);

	//DrawString(0, 0, "GAME_MAIN", 0xffffff);
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