#include "DxLib.h"
#include "GameTask.h"
#include "Player.h"
#include "BackGround.h"
#include "Obstracle.h"
#include "BasePlanet.h"
#include "Earth.h"
#include "Mars.h"
#include "Jupiter.h"
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
	InitSoundMem();		//メモリに読み込んだ音データをすべて削除する

	DrawString(0, 0, "INIT", 0xffff00);
	GtskPtr = &GameTask::GameTitle;
	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	obstracle = AddObjlist(std::make_shared<Obstracle>());
	mars = AddBplist(std::make_shared<Mars>());
	jupiter = AddBplist(std::make_shared<Jupiter>());
	earth = AddBplist(std::make_shared<Earth>());
	(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);
	//画像読み込み
	ImageMng::GetInstance().SetID2("Title", "image/title.png");//タイトル
	ImageMng::GetInstance().SetID2("Result", "image/result.png");//リザルト
	//音楽ファイル読み込み
	OP = LoadBGM("sound/uchuu-tanken .ogg");
	Main = LoadBGM("sound/宇宙の佇み.ogg");
	End = LoadBGM("sound/遊星.ogg");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// 圧縮された全データはシステムメモリに格納され、再生する部分だけ逐次解凍しながらサウンドメモリに格納する(鳴らし終わると解凍したデータは破棄されるので何度も解凍処理が行われる)
	Decision = LoadSoundMem("sound/選択音.ogg");
	Rocket = LoadSoundMem("sound/ロケット噴射.ogg");
	Boost = LoadSoundMem("sound/ガスバーナー.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	//隠しコマンド
	UFO = LoadSoundMem("sound/UFO01.ogg");
	UFOBoost = LoadSoundMem("sound/sf_energy2 .ogg");
	UFOFlag = false;//隠しコマンド関係フラグ
	BomFlag = false;//爆発フラグ

	//フォント
	InitFontToHandle();	//フォントデータをすべて削除する
	Font = CreateFontToHandle("Segoe Print", 40, 3, DX_FONTTYPE_NORMAL);
	back = new BackGround();
	return 0;
}

int GameTask::GameTitle(void)
{
	int Title_X = -500;
	int Title_Y = 0;
	//画像描画
	ImageMng::GetInstance().DrawImage("Title", Title_X, Title_Y, true);
	//タイトル文字描画
	int title_x = 100;
	int title_y = 100;
	DrawStringToHandle(title_x, title_y, "Swing Bye", 0xFFFFFF, Font);
	//サウンド関係
	if(CheckSoundMem(OP)== 0)PlaySoundMem(OP, DX_PLAYTYPE_LOOP);
	//隠しコマンド
	if (KeyMng::GetInstance().newKey[P1_SPACE]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		(*player)->init("image/Player2.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
		DrawString(170, 300, "UFO出現", GetColor(255, 255, 255));
	}

	//ゲームモード移行
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(OP) == 1) {	//Titleが再生中なら
			DeleteSoundMem(OP);	//メモリに読み込んだTitleの音データを削除
		}
		GtskPtr = &GameTask::GameMain;
	}
	DrawString(0, 0, "GAME_TITLE", 0xffffff);
	return 0;
}

int GameTask::GameMain(void)
{
	if (CheckSoundMem(Main) == 0)PlaySoundMem(Main, DX_PLAYTYPE_LOOP);

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(Main) == 1) {	//Mainが再生中なら
			DeleteSoundMem(Main);	////メモリに読み込んだMainの音データを削除
			DeleteSoundMem(Rocket);
			DeleteSoundMem(Boost);
			DeleteSoundMem(UFO);
			DeleteSoundMem(UFOBoost);
			DeleteSoundMem(Bom);
		}
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

	for (auto itr : bpList)
	{
		// すべての惑星のUpdate
		itr->Update();
		itr->Draw();
		if (itr->GetDistance() < distance)
		{
			PandPvec = itr->GetVec();

		}
		distance = itr->GetDistance();
	}

	for (auto itr : objList)
	{
		//(*player)->GetPos();
		playerPos = (*player)->GetPos();
		playerAngle = (*player)->GetAngle();
		playerVec = (*player)->GetVec();
		
		if (KeyMng::GetInstance().newKey[P1_UP]) {//↑キーが押されたとき
			 
			if (UFOFlag == true) {//UFOFlagがtrueの時
				//UFOの音が再生中でなければUFOの音を再生する
				if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);
			}
			else {
				//ロケット噴射の音が再生中でなければロケット噴射の音を再生する
				if (CheckSoundMem(Rocket) == 0)PlaySoundMem(Rocket, DX_PLAYTYPE_LOOP);
			}
		}
		else {	//そうでなければ音を止める
			StopSoundMem(UFO);
			StopSoundMem(Rocket);
		}
		
		if (KeyMng::GetInstance().newKey[P1_SPACE]) {
			if (UFOFlag == true) {//UFOFlagがtrueの時
								  //UFOの音が再生中でなければUFOの音を再生する
				if (CheckSoundMem(UFOBoost) == 0)PlaySoundMem(UFOBoost, DX_PLAYTYPE_BACK);
			}
			else {
				if (CheckSoundMem(Boost) == 0)PlaySoundMem(Boost, DX_PLAYTYPE_BACK);
			}
		}
		else {
			StopSoundMem(UFOBoost);
			StopSoundMem(Boost);
		}

		if ((*player)->GetDeathFlag() == true) {	//プレイヤーが死んだとき
			BomFlag = true;
			DeleteSoundMem(Rocket);	//メモリに読み込んだロケット噴射音の音データを削除
			DeleteSoundMem(UFO);
			DeleteSoundMem(Boost);
			//爆発音が再生中でなければ爆発音を再生する
			if (BomFlag == true) {
				if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);
			}
		}
		else {
			BomFlag = false;
		}

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

	//矩形の当たり判定
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) {
		(*player)->SetDeathFlag(true);
		BomFlag = true;
	}

	//DrawFormatStringF(10, 400, GetColor(255, 255, 255), "hit %d", GetHitCheck());
	/*DrawFormatStringF(10, 500, GetColor(255, 255, 255), "dis %f", distance);
	DrawFormatStringF(10, 530, GetColor(255, 255, 255), "vec.x %f,Vec.y %f", PandPvec.x,PandPvec.y);*/
	//DrawString(0, 0, "GAME_MAIN", 0xffffff);
	return 0;
}

int GameTask::GameResult(void)
{
	//画像描画
	int Result_X = -100;
	int Result_Y = 0;
	ImageMng::GetInstance().DrawImage("Result", Result_X, Result_Y, true);
	//タイトル文字描画
	int result_x = 150;
	int result_y = 100;
	DrawStringToHandle(result_x, result_y, "Result", 0xFFFFFF, Font);
	//サウンド
	if (CheckSoundMem(Rocket) == 1)DeleteSoundMem(Rocket);
	if (CheckSoundMem(Bom) == 1)DeleteSoundMem(Bom);
	if (CheckSoundMem(End) == 0)PlaySoundMem(End, DX_PLAYTYPE_LOOP);

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(End) == 1) {	//Resultが再生中なら
			DeleteSoundMem(End);	//メモリに読み込んだResultの音データを削除
		}
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


