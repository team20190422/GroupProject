#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include "DxLib.h"
#include "GameTask.h"
#include "Player.h"
#include "LandPlayer.h"
#include "BackGround.h"
#include "Obstracle.h"
#include "BasePlanet.h"
#include "Mars.h"
#include "Earth.h"
#include "Asteroid.h"
#include "Particle.h"
#include "StageSet.h"
//#include"Enemy.h"
//#include "Stage.h"
#include"KeyMng.h"
#include"ImageMng.h"

//
constexpr unsigned int SCREEN_CENTER_X = 200;
constexpr unsigned int SCREEN_CENTER_Y = 300;
constexpr unsigned int StageMax = 3;

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

const bool & GameTask::GetCupLandCheck(void)
{
	return cupLandingCheck;
}

void GameTask::SetCupLandCheck(bool cupLanding)
{
	cupLandingCheck = cupLanding;
}

const bool & GameTask::GetDarkFlag2(void)
{
	return darkFlag2;
}

void GameTask::SetDarkFlag2(bool dark)
{
	darkFlag2 = dark;
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

const float & GameTask::GetRocketSize(void)
{
	return rocketSize;
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
		DieAnim[j] = LoadDivGraph("image/Explosion/爆発_大.png", 11, 11, 1, 115, 100, DieAnim,true);
		OutScrAnim[j] = LoadDivGraph("image/Number/countdown.png", 11, 11, 1, 100, 100, OutScrAnim, true);

		//DieAnim[j] = LoadGraph("image/爆発_大.png");
	}
	for (int i = 0; i < EarthMax; i++)
	{
		EarthImage[i] = LoadDivGraph("image/earthAnimNC.png", 20, 20, 1, 100, 50, EarthImage, true);
	}

	//音楽ファイル読み込み
	OP = LoadBGM("sound/空の記憶.ogg");
	Main = LoadBGM("sound/宇宙の佇み.ogg");
	ED1 = LoadBGM("sound/遊星.ogg");
	ED2 = LoadBGM("sound/farewell.ogg");
	LED = LoadBGM("sound/世界が僕達に揺れるまで.ogg");
	Over = LoadBGM("sound/宇宙空間.ogg");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// 圧縮された全データはシステムメモリに格納され、再生する部分だけ逐次解凍しながらサウンドメモリに格納する(鳴らし終わると解凍したデータは破棄されるので何度も解凍処理が行われる)
	Decision = LoadSoundMem("sound/選択音.ogg");
	Rocket = LoadSoundMem("sound/ロケット噴射.ogg");
	Boost = LoadSoundMem("sound/ガスバーナー.ogg");
	Emergency = LoadSoundMem("sound/警報.ogg");
	Emergency2 = LoadSoundMem("sound/警報03.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	UFO = LoadSoundMem("sound/UFO01.ogg");

	GtskPtr = &GameTask::GameTitle;
	return 0;
}


int GameTask::GameInit(void)
{
	//
	auto riset = [&] {
		time = 0;
		MainTimer = 0;
		AnimCnt = 0;
		clearCnt = 0;
		limitAnimSize = 2.0f;
		limitTime = 4;
		subTitleCnt = 0;
		subTitleAnim = 0;
		outScreenTime = 0;
		resultAnimCnt = 200;
		resultTime = 0;

		clearCheck = false;
		landingCheck = false;
		landingFlag = false;
		returnFlag = false;
		getSample = false;
		subTitleFlag = false;
	};
	//

	objList.clear();
	bpList.clear();

	//
	riset();
	//

	for (auto i : targetSet)
	{
		i += VECTOR3(1, 0);

	}
	DrawString(0, 0, "INIT", 0xffff00);

	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	obstracle = AddObjlist(std::make_shared<Obstracle>());

	earth = AddBplist(std::make_shared<Earth>(VECTOR3(225, SCREEN_SIZE_Y * 2)));

	int AsteroidCnt = 0;
	for (auto planet : stageSet[StageCnt])
	{
		AsteroidCnt++;
		asteroid = AddBplist(std::make_shared<Asteroid>(planet, AsteroidCnt));
	}

	for (auto targetPlanet : targetSet)
	{
		if (targetPlanet == targetSet[StageCnt])
		{
			MarsCnt++;
			mars = AddBplist(std::make_shared<Mars>(targetPlanet, MarsCnt));
		}
	}

	if (UFOFlag == true) {
		(*player)->init("image/UFO.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}
	else {
		(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);

	//ImageMng::GetInstance().SetID("TITLE", "image/タイトル.png");
	back = new BackGround();

	GtskPtr = &GameTask::GameMain;

	return 0;
}

int GameTask::GameTitle(void)
{
	auto AddPtclist = [&](particle_ptr && objPtr)
	{
		particleList.push_back(objPtr);
		auto itr = particleList.end();
		itr--;
		return itr;
	};


	ClsDrawScreen();

	titleTime++;
	int shakeEarth = GetRand(titleShake);

	if (titleBright < 255)
	{
		titleBright += 2;
		SetDrawBright(titleBright, titleBright, titleBright);
	}


	StageCnt = 0;
	MarsCnt = 0;

	//サウンド関係
	ChangeVolumeSoundMem(255 * 70 / 100, OP);//OPの音のボリュームを70%に設定
	if (CheckSoundMem(OP) == 0)PlaySoundMem(OP, DX_PLAYTYPE_LOOP);//OPが再生中でなければ音を鳴らす

																  //隠しコマンド
	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}

	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/landBG.png"), true);
	//if ((lgtsCnt++ / 30) % 2 == 0)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 1, angle+=0.005f, ImageMng::GetInstance().SetID("image/LGTS.png"), true);
	}
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - 100, earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	// ﾀｲﾄﾙ画面
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, (SCREEN_SIZE_Y - 100) + shakeEarth, earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		int ufo_x = 25, ufo_y = 200;
		DrawGraph(ufo_x, ufo_y, IMAGE_ID("image/UFO顕現.png"), true);
	}
	//ゲームモード移行
	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);

		titleShake = 5;
		//pushSpace = true;
	}

	// 振動
	if (titleShake > 0)
	{
		if (titleTime % 30 == 0)
		{
			titleShake--;
		}
	}

	if (titleShake == 1)
	{
		titleShake = 0;
		pushSpace = true;
	}

	if (pushSpace)
	{
		// ﾊﾟｰﾃｨｸﾙ作成
		float parMax = 2.0f;
		for (float f = 0.0; f < parMax; f += 0.1)
		{
			particle = AddPtclist(std::make_shared<Particle>(rocketPos, VECTOR3(0, 0), 5));
		}
		for (auto title : particleList)
		{
			title->Draw();
			title->Update();
		}

		// ﾊﾟｰﾃｨｸﾙの削除
		for (int i = 0; i < particleList.size(); i++)
		{
			if (particleList.size() > 0)
			{

				if (particleList.front()->GetTimer() > 7)
				{

					if (!(particleList.empty()))
					{
						particleList.pop_front();

					}
				}
			}
		}
		// ﾛｹｯﾄ描画
		if (UFOFlag == true) {
			DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/uf0(side).png"), true);
		}
		else {
			DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/rocket.png"), true);
		}
		rocketPos.y -= 3.0f;
		if (rocketSize >= 2.0f)
		{
			rocketSize = 2.0f;
		}
		else
		{
			rocketSize += 0.01f;
		}

		if (rocketPos.y < 0)
		{
			if (landingCnt[0] > 0 && !lightFlag)
			{
				landingCnt[0] -= 5;
			}
			else
			{
				lightFlag = true;
				/*DeleteGraph(ImageMng::GetInstance().SetID("image/rocket.png"));
				DeleteGraph(ImageMng::GetInstance().SetID("image/landBG.png"));
				DeleteGraph(ImageMng::GetInstance().SetID("image/title.png"));
				for (int i = 0; i < 20; i++)
				{
					DeleteGraph(EarthImage[i]);
				}*/
				if (CheckSoundMem(OP) == 1) StopSoundMem(OP);//Titleが再生中ならTitleを止める
				GtskPtr = &GameTask::GameInit;
			}
			/*if (lightFlag)
			{
			if (landingCnt[0] < 255)
			{
			landingCnt[0] += 5;
			}
			else
			{
			GtskPtr = &GameTask::GameInit;
			}
			}*/
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	//DrawString(0, 0, "GAME_TITLE", 0xffffff);
	ScreenFlip();
	return 0;
}

// 宇宙遊泳
int GameTask::GameMain(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ClsDrawScreen();

	// ｴﾝﾃﾞｨﾝｸﾞ時の分岐用のﾀｲﾑ計測
	MainTimer++;

	if (CheckSoundMem(Main) == 0)PlaySoundMem(Main, DX_PLAYTYPE_LOOP);//Mainが再生中でなければ音を鳴らす

																	  //サウンド関係
	if (KeyMng::GetInstance().newKey[P1_UP]) {//↑キーが押されたとき
		if (UFOFlag == true) {
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFOが再生中でなければ音を鳴らす
		}
		else {
			//ロケット噴射の音が再生中でなければロケット噴射の音を再生する
			if (CheckSoundMem(Rocket) == 0)PlaySoundMem(Rocket, DX_PLAYTYPE_LOOP);//Rocketが再生中でなければ音を鳴らす
		}
	}
	else {	//そうでなければ音を止める
		StopSoundMem(UFO);//UFO音を止める
		StopSoundMem(Rocket);//Rocket音を止める
	}

	if (KeyMng::GetInstance().newKey[P1_SPACE]) {
		if (CheckSoundMem(Boost) == 0)PlaySoundMem(Boost, DX_PLAYTYPE_BACK);//Boostが再生中でなければ音を鳴らす
	}
	else {
		StopSoundMem(Boost);//Boost音を止める
	}


	// ここから
	auto StageDraw = [&] {
		SetFontSize(60);
		ChangeFont("Ailerons");

		if (!subTitleFlag)
		{
			if (subTitleCnt < 255)
			{
				subTitleCnt += 5;
			}
			else
			{
				subTitleAnim++;
				if (subTitleAnim > 60)
				{
					subTitleFlag = true;
				}
			}

			DrawFormatString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_CENTER_Y, GetColor(subTitleCnt, subTitleCnt, subTitleCnt), "STAGE %d", StageCnt + 1);
		}
		else
		{
			if (subTitleCnt > 0)
			{
				subTitleCnt -= 5;
				DrawFormatString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_CENTER_Y, GetColor(subTitleCnt, subTitleCnt, subTitleCnt), "STAGE %d", StageCnt + 1);

			}
			else
			{

			}
		}
		ChangeFont("MSゴシック");

		SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ

	};

	auto GameOver = [&] {

		if (GetHitCheck())
		{
			if (landingCnt[0] > 0)
			{
				landingCnt[0] -= 15;
				return true;
			}
			else
			{
				GtskPtr = &GameTask::GameOver;
				return true;
			}
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);

		return false;
	};
	// ここまで

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(Main) == 1) {	//Mainが再生中なら
			StopSoundMem(Main);	////メモリに読み込んだMainの音データを削除
			StopSoundMem(Rocket);// Rocketが再生中ならRocketの音を止める
			StopSoundMem(Boost);// Boostが再生中ならBoostの音を止める
			StopSoundMem(Emergency2);
		}

		landingCheck = false;
		GtskPtr = &GameTask::GameResult;
	}

	std::vector<BackGround*>::iterator itrBG = backVec.begin();


	if (count <= 300)
	{
		count++;
		back = new BackGround();
		backVec.push_back(back);
		BackGraundCnt++;

	}
	else if (count > 300 && count <= 600)
	{
		count++;
		back = new BackGround();
		backVec.push_back(back);
		BackGraundCnt++;

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

		if (!clearCheck)
		{
			targetDistance = (*mars)->GetDistance();
		}
		else
		{
			targetDistance = (*earth)->GetDistance();
		}
		if (itr->GetDistance() < distance)
		{

			PandPvec = itr->GetVec();
			if (itr->GetDistance() > 0)
			{
				distance = itr->GetDistance();
				gravity = itr->GetGravity();

			}
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
			DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
			//DrawString((int)playerPos.x, (int)playerPos.y, "やられた", 0xffffff);
			StopSoundMem(UFO);		//UFO音を止める
			StopSoundMem(Rocket);	//Rocket音を止める
			StopSoundMem(Boost);	//Boost音を止める
			if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//爆発音が鳴っているか調べてなっていなかったら鳴らす
																			// ここのif分
			if (AnimCnt >= 11)
			{
				GameOver();
			}
		}
		
		if (landingCheck && landingFlag)
		{
			SetHitCheck(false);

			
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
			BackGraundCnt--;

			break;
		}
		else
		{
			itrBG++;
		}
	}

	//矩形の当たり判定
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) {
		hitCheck = true;
		if (GetLandCheck()) {
			hitCheck = false;
		}
	}

	if (hitCheck == true) {	//プレイヤーが死んだとき
		StopSoundMem(UFO);		//UFO音を止める
		StopSoundMem(Rocket);	//Rocket音を止める
		StopSoundMem(Boost);	//Boost音を止める
								//爆発音が再生中でなければ爆発音を再生する
		if (AnimTime++ % 10 == 0)
		{
			AnimCnt++;
		}
		DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
		if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//Bomが再生中でなければ音を鳴らす
		if (AnimCnt >= 11)
		{
			GameOver();
		}
	}
	else {
		StopSoundMem(Bom);	//Bom音を止める
	}

	// 着陸成功時
	if (landingCheck && landingFlag)
	{
		if (landingCnt[0] > 0)
		{
			landingCnt[0] -= 25;
		}
		else
		{
			
			if (landingCheck && landingFlag && !clearCheck)
			{
				// 着陸に移行
				GtskPtr = &GameTask::GameLandInit;
			}
			
		}

		if (landingCnt[0] <= 100)
		{
			// ﾐｯｼｮﾝｸﾘｱ
			if (returnFlag && clearCheck && landingCheck && landingFlag)
			{
				auto SaveGameMain = SaveDrawScreenToPNG(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, "image/Screen/screen.png", 0);
				resultAnim = LoadGraph("image/Screen/screen.png");

				// ﾐｯｼｮﾝｸﾘｱ
				GtskPtr = &GameTask::GameResult;
			}
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	else
	{
		// ここ
		if (landingCnt[0] < 255 && !GetHitCheck())
		{
			landingCnt[0] += 20;
		}

		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0.9, 0, ImageMng::GetInstance().SetID("image/次へ.png"), true);
	DrawRotaGraph(SCREEN_SIZE_X / 2, 0, 0.9, 0, ImageMng::GetInstance().SetID("image/次へ.png"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ここから
	// 自機の画面外時
	if (OutOfScreen)
	{
		SetDrawBright(landingCnt[1] + 50, landingCnt[1] + 50, landingCnt[1] + 50);

		for (int x = 0; x < SCREEN_SIZE_X; x++)
		{
			for (int y = 0; y < SCREEN_SIZE_Y; y++)
			{
				auto randomY = GetRand(10000);

				DrawPixel(x, y + randomY, GetColor(255, 255, 255));
			}
		}

		
			if (landingCnt[1] > 0 && (outScreenTime++ % 60) == 0)
			{
				landingCnt[1] -= 20;
				limitTime++;
				if (CheckSoundMem(Emergency2) == 0)PlaySoundMem(Emergency2, DX_PLAYTYPE_BACK);

			}
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
	}
	else
	{
		limitTime = 4;
		limitAnimSize = 2.0f;
		outScreenTime = 0;
		if (Energy >= 20 && landingCnt[1] < 255 && landingCnt[0] >= 255)
		{
			landingCnt[1] += 10;
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
			if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);

		}
	}

	// 燃料少量時
	if (Energy > 0 && Energy < 20 && !(landingCheck && landingFlag))
	{
		if (landingCnt[1] > 0 && !energyAnim)
		{
			landingCnt[1] -= 10;
			PlaySoundMem(Emergency, DX_PLAYTYPE_BACK);

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

	if (Energy <= 0 && !(landingCheck && landingFlag))
	{
		if (GameOverTime++ > 60)
		{
			if (landingCnt[1] > 0)
			{
				landingCnt[1] -= 10;
			}
			else if(landingCnt[1] <= 5)
			{
				ClsDrawScreen();
				StopSoundMem(Emergency);
				GtskPtr = &GameTask::GameOver;
				GameOverTime = 0;
			}
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);


		}
	}
	// ここまで
	

	if (clearCheck)
	{
		clearCnt++;
	}
	if (AnimCnt >= 10)
	{
		AnimCnt = 10;
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
			//clearCnt = 0;
		}
	}

	// ここから
	if (OutOfScreen)
	{

		//SetFontSize(limitAnimSize--);
		limitAnimSize -= 0.033f;
		if(limitTime > 10)
		SetDrawBright(255, 255, 255);
		//DrawFormatString(SCREEN_CENTER_X, SCREEN_CENTER_Y, GetColor(255, 255, 255), "%d", limitTime);
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, limitAnimSize, 0, OutScrAnim[limitTime], true);
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ

		if (limitTime >= 10)
		{
			if (landingCnt[1] > 0)
			{
				landingCnt[1] -= 10;
			}
			else
			{

				if (GameOverTime++ > 60)
				{
					ClsDrawScreen();
					GtskPtr = &GameTask::GameOver;
					GameOverTime = 0;
				}
			}

			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		}
	}

	if (limitAnimSize <= 0)
	{
		limitAnimSize = 2.0f;
	}

	

	// ｽﾃｰｼﾞｶｳﾝﾄ
	StageDraw();

	// ここまで

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "playerPosX %f playerPosY %f", playerPos.x,playerPos.y);
	DrawFormatStringF(10, 550, GetColor(255, 255, 255), "targetVecX %f targetVecY %f", targetVec.x, targetVec.y);
	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "time %d", MainTimer);

	ScreenFlip();

	return 0;
}

int GameTask::GameLandInit(void)
{
	landPlayer = AddObjlist(std::make_shared<LandPlayer>(lpKeyMng.trgKey, lpKeyMng.oldKey));

	(*landPlayer)->init("image/playerBeforeLanding.png", VECTOR2(44 / 1, 22 / 1), VECTOR2(1, 1), VECTOR2(0, 0), 1.0f);


	GtskPtr = &GameTask::GameLanding;

	return 0;
}

int GameTask::GameLanding(void)
{
	StopSoundMem(Emergency);//Emergency音を止める

	ClsDrawScreen();
	if (GetLandCheck())
	{
		if (landingCnt[0] < 255)
		{
			landingCnt[0] += 20;
		}
		else
		{
			SetLandCheck(false);
		}
	}

	if (GetCupLandCheck() && darkFlag == false)
	{
		if (landingCnt[0] > 0)
		{
			landingCnt[0] -= 20;
		}
		else
		{
			darkFlag = true;
		}
	}

	if (darkFlag == true && !GetDarkFlag2())
	{
		if (landingCnt[0] < 255)
		{
			landingCnt[0] += 20;
		}
	}

	if (GetDarkFlag2())
	{
		if (landingCnt[0] > 0)
		{
			landingCnt[0] -= 20;
		}
		else
		{
			SetDarkFlag2(false);
		}
	}

	for (auto itr : objList)
	{
		(*landPlayer)->Draw();
		(*landPlayer)->Update();
	}

	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);

	int a = GetLandCheck();
	int b = GetCupLandCheck();
	int c = darkFlag;
	//DrawString(0, 0, "GameLanding", 0xffffff);
	DrawFormatString(0, 80, 0xffffff, "%d", a);
	DrawFormatString(0, 95, 0xffffff, "%d", b);
	DrawFormatString(0, 110, 0xffffff, "%d", c);

	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		landAnimFlag = true;
	}

	// 条件達成したら宇宙へ戻る
	if (landAnimFlag)
	{
		pltrgPos = VECTOR3(playerPos.x + targetVec.x, playerPos.y);
		(*player)->SetPos(pltrgPos);
		SetScrollPos(-targetVec);
		setCount = true;
		landingCheck = false;
		landAnimFlag = false;
		landingFlag = true;
		clearCheck = true;						// ｸﾘｱ可能状態にする
		darkFlag = false;
		darkFlag2 = false;
		pushSpace = false;
		lightFlag = false;
		cupLandingCheck = false;			// ｶﾌﾟｾﾙのsizeが0になったかﾌﾗｸﾞ
		checkCnt = 0;
		pltrgPos = { 0,0 };
		if (objList.size() > 0)
		{
			objList.pop_back();
		}
		GtskPtr = &GameTask::GameMain;
	}

	ScreenFlip();
	return 0;
}

int GameTask::GameResult(void)
{
	auto Evaluation = [&] {

		// ﾀｲﾑ評価
		if (MainTimer <= 200)
		{
			timeEval = 'A';
		}
		else
		{
			timeEval = 'B';
		}

		// 採取評価
		if (getSample)
		{
			sampleEval = 'A';
		}
		else
		{
			sampleEval = 'B';
		}

	};

	ClsDrawScreen();
	int imageX = 0, imageY = 0;
	// 画像のｻｲｽﾞ取得
	GetGraphSize(ImageMng::GetInstance().SetID("image/Result/静寂2.png"), &imageX, &imageY);
	if (resultAnimCnt > 0)
	{
		if (resultTime++ % 200 <= 8)
		{
			resultAnimCnt -= 20;
		}
		else
		{
			resultAnimCnt--;
		}
	}

	if (landingCnt[0] < 255)
	{
		landingCnt[0] += 20;
	}
	DrawGraph(0, 0, resultAnim, true);


	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);


	DrawString(0, 0, "GameResult", 0xffffff);

	if (!getSample)
	{
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/静寂2.png"), true);
	}
	else
	{
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/枠2.png"), true);
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/歓喜2.png"), true);
	}
	DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/枠.png"), true);

	// 評価
	Evaluation();

	//サウンド
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// Rocketが再生中ならRocketの音を止める
	if (CheckSoundMem(Boost) == 1)StopSoundMem(Boost);// Boostが再生中ならBoostの音を止める
	StopSoundMem(Bom);	// Bomが再生中ならBomの音を止める
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// Mainが再生中ならMainの音を止める
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//Emergency音が再生中ならEmergency音を止める

	SetFontSize(50);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("Ailerons");
	DrawString(SCREEN_SIZE_X / 2 - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "RESULT", 0xffffff);
	DrawFormatStringF(10, 450, GetColor(255, 255, 255), "time   %d %c", MainTimer, timeEval);
	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "sample %d %c", getSample, sampleEval);//Evaluation
	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "Evaluation %d", getSample);
	SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("MSゴシック");

	static int count = 0;
	int Clear_X = 0, Clear_Y = 680;

	if (StageCnt == 0) {
		if (CheckSoundMem(ED1) == 0)PlaySoundMem(ED1, DX_PLAYTYPE_LOOP);//Resultが再生中でなければ音を鳴らす
		count = (count + 1) % 100;
		if (count < 50) {
			DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage1Clear.png"), true);
		}
	}
	else if (StageCnt == 1) {
		if (CheckSoundMem(ED2) == 0)PlaySoundMem(ED2, DX_PLAYTYPE_LOOP);//Resultが再生中でなければ音を鳴らす
		count = (count + 1) % 100;
		if (count < 50) {
			DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage2Clear.png"), true);
		}
	}
	else if (StageCnt == 2) {
		ChangeVolumeSoundMem(255 * 70 / 100, LED);//LEDの音のボリュームを70%に設定
		if (CheckSoundMem(LED) == 0)PlaySoundMem(LED, DX_PLAYTYPE_LOOP);//Resultが再生中でなければ音を鳴らす
		count = (count + 1) % 100;
		if (count < 50) {
			DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage3Clear.png"), true);
		}
	}


	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		/*time = 0;
		AnimCnt = 0;
		clearCnt = 0;
		clearCheck = false;
		landingCheck = false;
		landingFlag = false;
		returnFlag = false;
		getSample = false;*/
		StageCnt++;
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);

		if (CheckSoundMem(ED1) == 1)StopSoundMem(ED1);	// ED1が再生中ならEd1の音を止める
		if (CheckSoundMem(ED2) == 1)StopSoundMem(ED2);	// ED1が再生中ならEd1の音を止める

		if (CheckSoundMem(LED) == 1)StopSoundMem(LED);	// LEDが再生中ならLEDの音を止める

		MaxTime = MaxTime + MainTimer;
		GtskPtr = &GameTask::GameInit;
		if (StageCnt == StageMax)
		{
			titleBright = 0;
			rocketSize = 0.0f;
			rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };
			lightFlag = false;
			pushSpace = false;
			UFOFlag = false;

			GtskPtr = &GameTask::GameClear;
		}
	}
	//DrawFormatStringF(10, 500, GetColor(255, 255, 255), "着陸 %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);
	//DrawFormatStringF(10, 550, GetColor(255, 255, 255), "time %d", MainTimer);
	//DrawFormatStringF(10, 600, GetColor(255, 255, 255), "MaxTime %d", MaxTime);
	ScreenFlip();

	return 0;
}

int GameTask::GameOver(void)
{
	//サウンド
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// Rocketが再生中ならRocketの音を止める
	if (CheckSoundMem(Bom) == 1)StopSoundMem(Bom);// Bomが再生中ならBomの音を止める
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// Mainが再生中ならMainの音を止める
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//Emergency音が再生中ならEmergency音を止める
	if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);
	if (CheckSoundMem(Over) == 0)PlaySoundMem(Over, DX_PLAYTYPE_LOOP);//Overが再生中でなければ音を鳴らす

	//画像
	if (AnimTime++ % 10 == 0)
	{
		AnimCnt++;
	}
	DrawGraph((int)playerPos.x, (int)playerPos.y - 300, DieAnim[AnimCnt], true);

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		time = 0;
		AnimCnt = 0;
		clearCnt = 0;
		clearCheck = false;
		landingCheck = false;
		landingFlag = false;
		returnFlag = false;
		getSample = false;
		UFOFlag = false;
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// Overが再生中ならOverの音を止める
		// 背景の削除
		std::vector<BackGround*>::iterator itrBG = backVec.begin();
		while (itrBG != backVec.end())
		{
			count--;
			delete(*itrBG);
			itrBG = backVec.erase(itrBG);
			BackGraundCnt--;
		}


		GtskPtr = &GameTask::GameTitle;
	}
	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		MarsCnt--;
		time = 0;
		AnimCnt = 0;
		clearCnt = 0;
		clearCheck = false;
		landingCheck = false;
		landingFlag = false;
		returnFlag = false;
		getSample = false;
		if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// Overが再生中ならOverの音を止める

		GtskPtr = &GameTask::GameInit;
	}

	if (landingCnt[0] < 255)
	{
		landingCnt[0] += 5;
	}
	if (landingCnt[1] < 255)
	{
		landingCnt[1] += 5;
	}

	if (landingCnt[0] < landingCnt[1])
	{
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	else
	{
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
	}


	DrawString(0, 0, "GameResult", 0xffffff);


	SetFontSize(50);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("Ailerons");
	DrawString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "GAME OVER", 0xffffff);
	SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("MSゴシック");

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "着陸 %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);

	ScreenFlip();

	return 0;
}

int GameTask::GameClear(void)
{
	ClsDrawScreen();

	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		GtskPtr = &GameTask::GameTitle;
	}

	if (MaxTime >= 2000)
	{
		DrawGraph(0, 0, IMAGE_ID("image/Result/result.png"), true);
		DrawGraph(0, 400, IMAGE_ID("image/Result/Stage2Clear.png"), true);
	}
	else
	{
		DrawGraph(0, 0, IMAGE_ID("image/Result/result2.png"), true);
		DrawGraph(0, 400, IMAGE_ID("image/Result/Stage3Clear.png"), true);
	}

	DrawString(0, 0, "GameClear", 0xffffff);

	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "MaxTime %d", MaxTime);

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


