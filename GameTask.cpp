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

const int & GameTask::GetLandingCnt(int i)
{
	return landingCnt[i];
}


const float & GameTask::GetErPosY(void)
{
	return EarthPos;
}

void GameTask::SetErPosY(float ErPos)
{
	EarthPos = ErPos;
}

const float & GameTask::GetSclPosY(void)
{
	return SclPos;
}

void GameTask::SetSclPosY(float sclPos)
{
	SclPos = sclPos;
}

const float & GameTask::GetScene(void)
{
	return Scene;
}

void GameTask::SetScene(float scene)
{
	Scene = scene;
}

const float & GameTask::GetLdistance(void)
{
	return landDistance;
}

void GameTask::SetLdistance(float distance)
{
	landDistance = distance;
}


const float & GameTask::GetCupSize(void)
{
	return cupSize;
}

void GameTask::SetCupSize(float capSize)
{
	this->cupSize = capSize;
}

const bool & GameTask::GetSpr(void)
{
	return Spr;
}

void GameTask::SetSpr(bool separate)
{
	Spr = separate;
}

const float & GameTask::GetAlpha(void)
{
	return alpha;
}

void GameTask::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

const float & GameTask::GetPlPosY(void)
{
	return plPos;
}

void GameTask::SetPlPosY(float plPos)
{
	this->plPos = plPos;
}

GameTask::GameTask()
{
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

	DieAnim = ImageMng::GetInstance().SetID("image/Explosion/Explosion.png", VECTOR2(115, 100), VECTOR2(11, 1));

	OutScrAnim[0] = ImageMng::GetInstance().SetID("image/Number/count_sushiki.png", VECTOR2(50, 50), VECTOR2(10, 1));

	for (int j = 0; j < 11; j++)
	{
		if (j <= StageMax)
		{
			OutScrAnim[1] = ImageMng::GetInstance().SetID("image/Number/stageCnt_sushiki.png", VECTOR2(100, 100), VECTOR2(3, 1));
			//OutScrAnim[1][j] = LoadDivGraph("image/Number/stageCnt_sushiki.png", 3, 3, 1, 100, 100, OutScrAnim[1], true);
		}
	}

	EarthImage = ImageMng::GetInstance().SetID("image/earthAnimNC.png", VECTOR2(100, 50), VECTOR2(20, 1));



	//音楽ファイル読み込み
	OP = LoadBGM("sound/この宇宙のどこかで.mp3");
	Main = LoadBGM("sound/星粒が降る夜.mp3");
	ED1 = LoadBGM("sound/遊星.ogg");
	ED2 = LoadBGM("sound/farewell.ogg");
	LED = LoadBGM("sound/世界が僕達に揺れるまで.ogg");
	Over = LoadBGM("sound/宇宙空間.ogg");
	Result_rank = LoadBGM("sound/bomb.mp3");
	Result_rankAll = LoadBGM("sound/destruction1.mp3");
	Cheers = LoadBGM("sound/people_people-stadium-cheer1.mp3");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// 圧縮された全データはシステムメモリに格納され、再生する部分だけ逐次解凍しながらサウンドメモリに格納する(鳴らし終わると解凍したデータは破棄されるので何度も解凍処理が行われる)
	Decision = LoadSoundMem("sound/選択音.ogg");
	Rocket = LoadSoundMem("sound/ロケット噴射.mp3");
	EngineM = LoadSoundMem("sound/飛行機・小型ジェット機mid.mp3");
	EngineLand = LoadSoundMem("sound/atmosphere4.mp3");
	Boost = LoadSoundMem("sound/ガスバーナー.mp3");
	fire = LoadSoundMem("sound/ガスバーナー.mp3");
	Emergency = LoadSoundMem("sound/警報.ogg");
	Emergency2 = LoadSoundMem("sound/警報03.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	UFO = LoadSoundMem("sound/UFO01.ogg");
	wind = LoadSoundMem("sound/天候・荒野の風.mp3");
	noise = LoadSoundMem("sound/砂嵐の音・テレビのホワイトノイズ音.mp3");
	koukaon = LoadSoundMem("sound/small_explosion1.mp3");
	Gas = LoadSoundMem("sound/ガスが漏れる音loop.mp3");
	ClearBGM = LoadSoundMem("sound/uchuu-hachimoku.mp3");

	GtskPtr = &GameTask::GameTitle;
	return 0;
}


int GameTask::GameInit(void)
{
	//
	auto reset = [&] {
		time = 0;
		MainTimer = 0;
		AnimCnt = 0;
		clearCnt = 0;
		limitAnimSize = 2.0f;
		limitTime = 6;
		subTitleCnt = 0;
		subTitleAnim = 0;
		outScreenTime = 0;
		resultAnimCnt = 200;
		resultTime = 0;
		overBright = 255.0f;
		EtoP = 0.0f;
		EtoPtrans = ((-533 / 5) + 700);
		disTrans = 50.0f;
		shake = 0.0f;
		shakeWidth = 5;
		kouka_shake = 5;
		koukaSave = 0;
		koukaSize = 0.3f;
		alphaJ = 0.0f;
		alphaM = 0.0f;
		font = CreateFontToHandle(NULL, 10, 1);

		clearCheck = false;
		landingCheck = false;
		landingFlag = false;
		returnFlag = false;
		getSample = false;
		subTitleFlag = false;
		psFlag = false;
		fireFlag = false;
		hundredFlag = false;
		OutScr = false;
		SetAlpha(0.0f);
	};
	//

	objList.clear();
	bpList.clear();
	bpList.reserve(stageSet[StageCnt].size() * 2);

	tSetPos.clear();

	//
	reset();
	//


	/*for (auto i : targetSet)
	{
		i += VECTOR3(1, 0);

	}*/
	DrawString(0, 0, "INIT", 0xffff00);

	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	obstracle = AddObjlist(std::make_shared<Obstracle>());

	earth = AddBplist(std::make_shared<Earth>(VECTOR3(225, SCREEN_SIZE_Y * 1.5f)));

	int AsteroidCnt = 0;
	for (auto planet : stageSet[StageCnt])
	{
		auto max = stageSet[StageCnt].size();
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

	for (auto itr : bpList)
	{
		tSetPos.push_back(itr->GetPos());
	}

	if (UFOFlag == true) {
		(*player)->init("image/UFO.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}
	else {
		(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);

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


	if (titleBright < 255)
	{
		titleBright += 2;
		SetDrawBright(titleBright, titleBright, titleBright);
	}


	StageCnt = 0;
	MarsCnt = 0;
	pauseFlag = false;
	pauseCheck = false;

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

	// ﾀｲﾄﾙ画面
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, (SCREEN_SIZE_Y - 100), earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		int ufo_x = 25, ufo_y = 200;
		DrawGraph(ufo_x, ufo_y, IMAGE_ID("image/UFO出現.png"), true);
	}
	//ゲームモード移行
	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		PlaySoundMem(Rocket, DX_PLAYTYPE_BACK);
		shakeFlag = true;
		launchFlag = true;

	}
	if (shakeFlag)
	{
		DrawRotaGraphF(SCREEN_SIZE_X / 2, (SCREEN_SIZE_Y - 100) + Shake(), earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);
	}
	// ﾌｪｰﾄﾞ
	if (launchFlag)
	{
		soundV.Rocket -= 0.08f;
		ChangeVolumeSoundMem(255 * soundV.Rocket / 100, Rocket);
		if (rocketPos.y < SCREEN_SIZE_Y / 4)
		{
			soundV.OP -= 0.5f;
			ChangeVolumeSoundMem(255 * soundV.OP / 100, OP);
		}
	}

	// 振動
	if (shakeFlag)
	{
		titleTime++;
		if (titleTime % 100 == 0)
		{
			pushSpace = true;
		}
	}

	if (pushSpace)
	{
		DrawFormatString(SCREEN_SIZE_X - 150, SCREEN_SIZE_Y - 15, 0xffffff, "SPACEでスキップ");

		shakeWidth = 5;

		timeCnt++;
		// ｼｰﾝｽｷｯﾌﾟ
		if (timeCnt > 1)
		{
			if (KeyMng::GetInstance().trgKey[P1_SPACE])
			{
				skipFlag = true;
			}
		}
		if (!UFOFlag)
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
			DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/rocket.png"), true);
		}
		else
		{
			ufoTime++;
			UFOpos.x += 2;

			// ufo描画
			DrawRotaGraph(UFOpos.x, UFOpos.y - sin(3.1415 * 2 / 100 * ufoTime) * 30, 0.3, 0, ImageMng::GetInstance().SetID("image/ufo(side).png"), true);
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

		if (rocketPos.y < 0 || skipFlag)
		{
			if (landingCnt[0] > 0 && !lightFlag)
			{
				landingCnt[0] -= 5;
			}
			else
			{
				lightFlag = true;

				if (CheckSoundMem(OP) == 1) StopSoundMem(OP);//Titleが再生中ならTitleを止める

				skipFlag = false;
				timeCnt = 0;
				GtskPtr = &GameTask::GameInit;
			}
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	ScreenFlip();
	return 0;
}

// 宇宙遊泳
int GameTask::GameMain(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ClsDrawScreen();

	///////////////////////////////////////////////////////////////////////////////////
	// ﾎﾟｰｽﾞ用
	if (KeyMng::GetInstance().trgKey[P1_PAUSE] && !GetHitCheck())
	{
		if (pauseFlag)
		{
			pauseFlag = false;
			pauseCheck = false;
		}
		else
		{
			pauseFlag = true;
			pauseBrightTime = 0;
		}
	}

	//DrawFormatString(10, 600, 0xffffff, "time %d", MainTimer);

	if (!pauseFlag)
	{
		// ｴﾝﾃﾞｨﾝｸﾞ時の分岐用のﾀｲﾑ計測
		MainTimer++;
	}
	else
	{
		// ﾎﾟｰｽﾞ時の処理
		if (KeyMng::GetInstance().trgKey[P1_UP])
		{
			if (pauseCheck)
			{
				pauseCheck = false;
			}
		}
		else if (KeyMng::GetInstance().trgKey[P1_DOWN])
		{
			if (!pauseCheck)
			{
				pauseCheck = true;
			}
		}
		if (255 - pauseBrightTime > 100)
		{
			pauseBrightTime += 5;
		}
		SetDrawBright(255 - pauseBrightTime, 255 - pauseBrightTime, 255 - pauseBrightTime);

		// ﾘﾄﾗｲorﾀｲﾄﾙ
		if (KeyMng::GetInstance().trgKey[P1_SPACE] && pauseCheck)
		{
			time = 0;
			AnimCnt = 0;
			AnimTime = 0;
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

			titleBright = 0;
			if (shakeWidth > 0)
				shakeWidth = 0;
			rocketSize = 0.0f;
			rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };
			lightFlag = false;
			pushSpace = false;
			UFOFlag = false;

			GtskPtr = &GameTask::GameTitle;
		}
		if (KeyMng::GetInstance().trgKey[P1_SPACE] && !pauseCheck)
		{
			AnimCnt = 0;
			AnimTime = 0;
			retryCnt++;
			MarsCnt--;
			time = 0;
			AnimCnt = 0;
			clearCnt = 0;
			clearCheck = false;
			landingCheck = false;
			landingFlag = false;
			returnFlag = false;
			getSample = false;
			retryCheck = true;
			if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// Overが再生中ならOverの音を止める
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////

	ChangeVolumeSoundMem(255 * 50 / 100, Main);//OPの音のボリュームを70%に設定
	if (CheckSoundMem(Main) == 0)PlaySoundMem(Main, DX_PLAYTYPE_LOOP);//Mainが再生中でなければ音を鳴らす

																	  //サウンド関係
	if (KeyMng::GetInstance().newKey[P1_UP] && !pauseFlag) {//↑キーが押されたとき
		if (UFOFlag == true)
		{
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFOが再生中でなければ音を鳴らす
		}
		else
		{
			eSoundFlag = 1;
			//ロケット噴射の音が再生中でなければロケット噴射の音を再生する
			ChangeVolumeSoundMem(255 * 60 / 100, EngineM);
			if (CheckSoundMem(EngineM) == 0)PlaySoundMem(EngineM, DX_PLAYTYPE_LOOP);//UFOが再生中でなければ音を鳴らす
		}
	}
	else
	{	//そうでなければ音を止める
		StopSoundMem(UFO);//UFO音を止める
		StopSoundMem(EngineM);//Rocket音を止める
		StopSoundMem(Rocket);//Rocket音を止める
		if (soundVol <= 100)
		{
			soundVol++;
		}
		//ChangeVolumeSoundMem(255 * soundV.Engine - soundVol / 100, Engine);
	}
	if (KeyMng::GetInstance().newKey[P1_RIGHT] || KeyMng::GetInstance().newKey[P1_LEFT])
	{
		if (UFOFlag == true)
		{
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFOが再生中でなければ音を鳴らす
		}
		else
		{
			eSoundFlag = 1;
			//ロケット噴射の音が再生中でなければロケット噴射の音を再生する
			ChangeVolumeSoundMem(255 * 30 / 100, Gas);
			if (CheckSoundMem(Gas) == 0)PlaySoundMem(Gas, DX_PLAYTYPE_LOOP);//UFOが再生中でなければ音を鳴らす
		}
	}
	else
	{	//そうでなければ音を止める
		StopSoundMem(UFO);//UFO音を止める
		StopSoundMem(Rocket);//Rocket音を止める
		StopSoundMem(Gas);//Rocket音を止める
		if (soundVol <= 100)
		{
			soundVol++;
		}
		//ChangeVolumeSoundMem(255 * soundV.Engine - soundVol / 100, EngineF);
	}

	if (KeyMng::GetInstance().oldKey[P1_UP] && !pauseFlag)
	{
		soundV.Engine--;
	}
	else
	{
		soundV.Engine = 100;
	}
	SetCurrentPositionSoundMem(44100, Boost);

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
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, subTitleCnt);

			DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y + 25, 1.3, 0, IMAGE_ID("image/Number/stage_kana.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X + SCREEN_SIZE_X / 4, SCREEN_CENTER_Y + 25, 0.7, 0, OutScrAnim[1][StageCnt], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
		else
		{
			if (subTitleCnt > 0)
			{
				subTitleCnt -= 5;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, subTitleCnt);
				DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y + 25, 1.3, 0, IMAGE_ID("image/Number/stage_kana.png"), true);
				DrawRotaGraph(SCREEN_CENTER_X + SCREEN_SIZE_X / 4, SCREEN_CENTER_Y + 25, 0.7, 0, OutScrAnim[1][StageCnt], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
		if (!pauseFlag)
		{
			itrBG->Update();
		}
		itrBG->Draw();
	}

	distance = { DISTANCE_MAX };
	
	if (!pauseFlag)
	{
		time++;
	}
	for (auto itr : bpList)
	{

		// すべての惑星のUpdate
		if (!GetHitCheck() || time < 10)
		{
			if (!pauseFlag)
			{
				itr->Update();
			}
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
		playerPos = (*player)->GetPos();
		playerAngle = (*player)->GetAngle();
		playerVec = (*player)->GetVec();

		itr->Draw();

		if (!GetHitCheck() && !pauseFlag)
		{
			itr->Update();

		}
		else
		{
			if (!pauseFlag)
			{
				if (AnimTime++ % 10 == 0)
				{
					AnimCnt++;
				}
				if (AnimCnt <= 10)
				{
					DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
				}
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
		if (AnimCnt <= 10)
		{
			DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
		}
		if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//Bomが再生中でなければ音を鳴らす
		if (AnimCnt >= 11)
		{
			GameOver();
		}
	}
	else {
		StopSoundMem(Bom);	//Bom音を止める
	}

	// ﾐﾆﾏｯﾌﾟの描画
	Transition();


	// 着陸成功時
	if (landingCheck && landingFlag)
	{
		if (landingCnt[0] > 0)
		{
			landingCnt[0] -= 25;
		}
		else
		{
			setScrPos = false;
			if (landingCheck && landingFlag && !clearCheck)
			{
				// 着陸に移行
				setScrPos = true;
				setplPos = (*player)->GetplPos();
				
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
	if (OutOfScreen && !pauseFlag)
	{
		SetDrawBright(landingCnt[1] + 50, landingCnt[1] + 50, landingCnt[1] + 50);
		soundV.noise -= 0.02f;
		if (soundV.noise < 0)
		{
			soundV.noise = 0;
		}
		ChangeVolumeSoundMem(255 * soundV.noise / 100, noise);
		if (CheckSoundMem(noise) == 0)PlaySoundMem(noise, DX_PLAYTYPE_LOOP);
		//if (limitAnimSize < 0)
		{
			StopSoundMem(noise);
		}

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
			limitTime--;
			if (limitTime <= 0)
			{
				limitTime = 0;
			}
			//if (CheckSoundMem(Emergency2) == 0)PlaySoundMem(Emergency2, DX_PLAYTYPE_BACK);

		}
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
	}
	else
	{
		if (!pauseFlag)
		{
			limitTime = 6;
			limitAnimSize = 2.0f;
			outScreenTime = 0;
		}
		if (Energy >= 20 && landingCnt[1] < 255 && landingCnt[0] >= 255)
		{
			landingCnt[1] += 10;
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
			if (CheckSoundMem(noise) == 1)StopSoundMem(noise);
			soundV.noise = 50;
		}
	}

	// 燃料少量時
	if (Energy > 0 && Energy < 20 && !(landingCheck && landingFlag) && !pauseFlag)
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

	if (Energy <= 0 && !(landingCheck && landingFlag) && !pauseFlag)
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
				OutScr = true;
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
		
	}

	// ここから
	if (OutOfScreen && !pauseFlag)
	{

		limitAnimSize -= 0.033f;
		if (limitTime <= 0)
			SetDrawBright(255, 255, 255);
		if (limitTime >= 1)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, limitAnimSize, 0, OutScrAnim[0][limitTime], true);
		}
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ
		if (limitTime <= 0)
		{
			if (landingCnt[1] > 0)
			{
				landingCnt[1] -= 10;
			}
			else
			{

				//if (GameOverTime++ > 60)
				{
					ClsDrawScreen();
					StopSoundMem(noise);
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
	if (!getSample && !pauseFlag)
	{
		StageDraw();

	}

	/////////////////////////////////////////////////////////////////////////
	// ﾎﾟｰｽﾞ時の描画
	if (pauseFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, pauseBrightTime * 2);

		SetDrawBright(100 + pauseBrightTime, 100 + pauseBrightTime,100 + pauseBrightTime);
		DrawRotaGraph(SCREEN_CENTER_X + 25, 200, 1.5, 0, IMAGE_ID("image/pause/pause.png"), true);

		if (pauseCheck)
		{
			DrawRotaGraph(SCREEN_CENTER_X - 75, 425, 1.0, 0, IMAGE_ID("image/pause/titleback.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 425, 0.8, 0, IMAGE_ID("image/pause/選択.png"), true);
			SetDrawBright(255 - pauseBrightTime, 255 - pauseBrightTime, 255 - pauseBrightTime);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 325, 1.0, 0, IMAGE_ID("image/pause/retry.png"), true);
		}
		else
		{
			DrawRotaGraph(SCREEN_CENTER_X - 75, 325, 1.0, 0, IMAGE_ID("image/pause/retry.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 325, 0.8, 0, IMAGE_ID("image/pause/選択.png"), true);
			SetDrawBright(255 - pauseBrightTime, 255 - pauseBrightTime, 255 - pauseBrightTime);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 425, 1.0, 0, IMAGE_ID("image/pause/titleback.png"), true);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//DrawString(100, 200, "PAUSE", 0xffffff, true);
	}

	if (retryCheck)
	{
		retryCheck = false;
		pauseFlag = false;
		GtskPtr = &GameTask::GameInit;
	}

	if (clearCheck)
	{
		StopSoundMem(wind);
	}
	//////////////////////////////////////////////////////////////////////////////////////////

	//DrawFormatString(10, 650, 0xffffff, "retryCnt %d", retryCnt);
	// ここまで
	ScreenFlip();

	return 0;
}

int GameTask::GameLandInit(void)
{
	landPlayer = AddObjlist(std::make_shared<LandPlayer>(lpKeyMng.trgKey, lpKeyMng.oldKey, StageCnt));

	(*landPlayer)->init("image/playerBeforeLanding.png", VECTOR2(44 / 1, 22 / 1), VECTOR2(1, 1), VECTOR2(0, 0), 1.0f);


	GtskPtr = &GameTask::GameLanding;

	return 0;
}

int GameTask::GameLanding(void)
{
 	StopSoundMem(Emergency);//Emergency音を止める

	ClsDrawScreen();
	if (GetScene() == 0 && GetCupSize() < 1.9f)
	{
		ChangeVolumeSoundMem(255 * soundV.fire / 100, fire);
		if (CheckSoundMem(fire) == 0)PlaySoundMem(fire, DX_PLAYTYPE_BACK);
		fireFlag = true;
	}
	if (GetCupLandCheck())
	{
		StopSoundMem(fire);
	}
	if (fireFlag == true)
	{
		if (soundV.fire < 100 && hundredFlag == false)
		{
			soundV.fire++;
		}
		else
		{
			hundredFlag = true;
		}
		if (hundredFlag == true)
		{
			if (soundV.fire > 0)
			{
				soundV.fire -= 2.0f;
			}
			else
			{
				soundV.fire = 0;
			}
		}
	}

	if (GetScene() == 2 && soundCnt == 0)
	{
		ChangeVolumeSoundMem(255 * 70 / 100, wind);
		PlaySoundMem(wind, DX_PLAYTYPE_LOOP);
		soundCnt++;
	}

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
	Transition();


	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);

	int a = GetLandCheck();
	int b = GetCupLandCheck();
	int c = darkFlag;
	/*DrawFormatString(0, 80, 0xffffff, "%d", a);
	DrawFormatString(0, 95, 0xffffff, "%d", b);
	DrawFormatString(0, 110, 0xffffff, "%d", c);*/

	if (GetSpr())
	{
		if (KeyMng::GetInstance().newKey[P1_UP])
		{
			ChangeVolumeSoundMem(255 * 100 / 100, EngineLand);
			if (CheckSoundMem(EngineLand) == 0)
				PlaySoundMem(EngineLand, DX_PLAYTYPE_LOOP);//Engineが再生中でなければ音を鳴らす
		}
		else
		{
			StopSoundMem(EngineLand);
		}
		if (KeyMng::GetInstance().newKey[P1_RIGHT] || KeyMng::GetInstance().newKey[P1_LEFT])
		{
			if (CheckSoundMem(Gas) == 0)
				PlaySoundMem(Gas, DX_PLAYTYPE_LOOP);//Engineが再生中でなければ音を鳴らす
		}
		else
		{
			StopSoundMem(Gas);
		}
	}

	// 条件達成したら宇宙へ戻る
	if (landAnimFlag)
	{
		pltrgPos = VECTOR3(playerPos.x + targetVec.x, playerPos.y);
		(*player)->SetPos(pltrgPos);
		SetScrollPos(-targetVec);
		pltrgVec = targetVec;
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
		//pltrgPos = { 0,0 };
		//landingCnt[0] = 0;
		landingCnt[1] = 0;
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		if (objList.size() > 0)
		{
			objList.pop_back();
		}
		GtskPtr = &GameTask::GameMain;
	}

	// 爆発したらｹﾞｰﾑｵｰﾊﾞｰ
	if (landGameCheck)
	{
		ClsDrawScreen();
		landingCnt[0] = 0;
		GtskPtr = &GameTask::GameOver;
	}

	ScreenFlip();
	return 0;
}

int GameTask::GameResult(void)
{
	auto Evaluation = [&] {

		// ﾀｲﾑ評価
		if (MainTimer <= 1200)
		{
			timeEval = 3;
		}
		else if (MainTimer <= 1800)
		{
			timeEval = 2;
		}
		else
		{
			timeEval = 1;
		}

		// 燃料残評価
		if (GetEnergy() >= 30)
		{
			fuelEval = 3;
		}
		else if (GetEnergy() >= 20)
		{
			fuelEval = 2;
		}
		else
		{
			fuelEval = 1;
		}

		
		// 残機評価
		lifeEval = ((retryCnt == 0) ? 3 : (retryCnt == 1) ? 2 : (retryCnt == 2) ? 1 : 0);


		// 総合
		all = timeEval + fuelEval + lifeEval;
		if (StageCnt == 0)
		{
			stageRank1 = all;
		}
		else if (StageCnt == 1)
		{
			stageRank2 = all;
		}
		else
		{
			stageRank3 = all;
			sogo = stageRank1 + stageRank2 + stageRank3;
		}
	};

	auto ResultReset = [&] {
		//Line
		line.count1 = 0;
		line.count2 = 0;
		line.count3 = 0;
		line.L = 20.0f;
		line.R1 = 20.0f;
		line.R2 = 20.0f;
		line.R3 = 20.0f;
		line.end = false;

		// rankSize
		rankSize.time = 0.0f;
		rankSize.sample = 0.0f;
		rankSize.life = 0.0f;
		rankSize.all = 0.0f;
		rankSize.incEnd = false;
		rankSize.count = 0;
		rankSize.countSave = 0;
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
	SetDrawBright(50, 50, 50);
	DrawGraph(0, 0, resultAnim, true);


	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);



	if (!getSample)
	{
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/静寂2.png"), true);
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/枠.png"), true);
	}
	else
	{
		if (rankSize.all >= 1.5)
		{
			if (rankSize.bigSize > 0)
			{
				rankSize.bigSize -= 0.1f;
			}
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y - imageY / 2 + 50, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/枠2.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y - imageY / 2 + 50, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/歓喜2.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y - imageY / 2 + 50, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/枠.png"), true);

		}
		else
		{
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/静寂2.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/枠.png"), true);

		}
	}



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

	// ｶﾅver
	DrawRotaGraph(SCREEN_SIZE_X / 2, 50, 1.5, 0, ImageMng::GetInstance().SetID("image/result_kana.png"), true);
	DrawRotaGraph(100, 125, 1, 0, ImageMng::GetInstance().SetID("image/time_kana.png"), true);
	DrawRotaGraph(150, 200, 1, 0, ImageMng::GetInstance().SetID("image/nenryo_kana.png"), true);
	DrawRotaGraph(100, 275, 1, 0, ImageMng::GetInstance().SetID("image/life_kana.png"), true);
	DrawRotaGraph(100, SCREEN_SIZE_Y / 2, 1, 0, ImageMng::GetInstance().SetID("image/rank_kana.png"), true);



	// 評価
	rankSize.count++;
	if (rankSize.count > 20)
	{
		line.count1++;
		if (rankSize.time < 1.1f)
		{
			rankSize.time += 0.035f;
		}
		else
		{
			if (rankSize.countSave == 0)
			{
				playResultFlag = true;
				rankSize.countSave = rankSize.count;
				PlaySoundMem(Result_rank, DX_PLAYTYPE_BACK);
			}
		}

		if (line.R1 < 430)
		{
			line.R1 = line.count1 * 15;
		}
		else
		{
			if (line.R2 < 430)
			{
				line.R2 = line.count2 * 15;
			}
		}
		if (line.R2 > 430)
		{
			if (line.R3 < 430)
			{
				line.R3 = line.count3 * 15;
			}
		}
		DrawBox(line.L, 155, line.R1, 158, 0xffffff, true);
		DrawBox(line.L, 230, line.R2, 233, 0xffffff, true);
		DrawBox(line.L, 305, line.R3, 308, 0xffffff, true);
		if (rankSize.count + 20 < rankSize.countSave * 2)
		{
			line.count2++;
			if (rankSize.sample < 1.1f)
			{
				rankSize.sample += 0.035f;
			}
			else
			{
				playResultFlag = true;
				PlaySoundMem(Result_rank, DX_PLAYTYPE_BACK);
			}
		}
		else if (rankSize.count + 40 < rankSize.countSave * 3)
		{
			line.count3++;
			if (rankSize.life < 1.1f)
			{
				rankSize.life += 0.035f;
			}
			else
			{
				playResultFlag = true;
				rankSize.incEnd = true;
				PlaySoundMem(Result_rank, DX_PLAYTYPE_BACK);
			}
		}
		if (rankSize.incEnd)
		{
			if (rankSize.all < 1.5f)
			{
				rankSize.all += 0.03f;
			}
			else
			{
				ChangeVolumeSoundMem(255 * 80 / 100, Result_rankAll);
				PlaySoundMem(Result_rankAll, DX_PLAYTYPE_BACK);
				PlaySoundMem(Cheers, DX_PLAYTYPE_BACK);
				playResultFlag = true;
				rankSize.incEnd = false;
			}
		}

		if (CheckSoundMem(Result_rank) == 0)
		{
			playResultFlag = false;
		}

		if (playResultFlag)
		{
			shake = Shake();
		}
		else
		{
			shake = 0;
		}
	}

	if (timeEval == 3)
	{
		DrawRotaGraph(400 + shake, 125 + shake, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if (timeEval == 2)
	{
		DrawRotaGraph(400 + shake, 125 + shake, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400 + shake, 125 + shake, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (fuelEval == 3)
	{
		DrawRotaGraph(400 + shake, 200 + shake, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if (fuelEval == 2)
	{
		DrawRotaGraph(400 + shake, 200 + shake, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400 + shake, 200 + shake, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (lifeEval == 3)
	{
		DrawRotaGraph(400 + shake, 275 + shake, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if (lifeEval == 2)
	{
		DrawRotaGraph(400 + shake, 275 + shake, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400 + shake, 275 + shake, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (all == 9 || all == 8)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake, SCREEN_SIZE_Y / 2 + shake, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
		if (all == 9)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50 + shake, SCREEN_SIZE_Y / 2 + shake, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else if (all == 7 || all == 6)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake, SCREEN_SIZE_Y / 2 + shake, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
		if (all == 7)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50 + shake, SCREEN_SIZE_Y / 2 + shake, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else if (all == 5 || all == 4)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake, SCREEN_SIZE_Y / 2 + shake, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
		if (all == 5)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50 + shake, SCREEN_SIZE_Y / 2 + shake, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake, SCREEN_SIZE_Y / 2 + shake, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_D.png"), true);
	}

	static int count = 0;
	int Clear_X = 0, Clear_Y = 680;
	if (StageCnt == 0) {
		if (CheckSoundMem(ED1) == 0)PlaySoundMem(ED1, DX_PLAYTYPE_LOOP);//Resultが再生中でなければ音を鳴らす
		count = (count + 1) % 100;
		
	}
	else if (StageCnt == 1) {
		if (CheckSoundMem(ED2) == 0)PlaySoundMem(ED2, DX_PLAYTYPE_LOOP);//Resultが再生中でなければ音を鳴らす
		count = (count + 1) % 100;
		
	}
	else if (StageCnt == 2) {
		ChangeVolumeSoundMem(255 * 70 / 100, LED);//LEDの音のボリュームを70%に設定
		if (CheckSoundMem(LED) == 0)PlaySoundMem(LED, DX_PLAYTYPE_LOOP);//Resultが再生中でなければ音を鳴らす
		count = (count + 1) % 100;
		
	}

	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		
		StageCnt++;
		ResultReset();
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
	
	ScreenFlip();

	return 0;
}

int GameTask::GameOver(void)
{
	ClsDrawScreen();
	//サウンド
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// Rocketが再生中ならRocketの音を止める
	if (CheckSoundMem(Bom) == 1)StopSoundMem(Bom);// Bomが再生中ならBomの音を止める
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// Mainが再生中ならMainの音を止める
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//Emergency音が再生中ならEmergency音を止める
	if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);
	if (CheckSoundMem(Over) == 0)PlaySoundMem(Over, DX_PLAYTYPE_LOOP);//Overが再生中でなければ音を鳴らす


	//フェードアウト	
	if (GameOverFlag)
	{
		if (landingCnt[0] >= 255 && landingCnt[1] >= 255)
		{
			if (overBright >= 70) {
				overBright -= 0.35f;
			}
			else
			{
				DrawGameOver = true;
			}
			SetDrawBright(overBright, overBright, overBright);
		}
		DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/landBG.png"), true);
	}
	//画面外に出てゲームオーバーになった時
	if (OutOfScreen) {
		DrawGameOver = true;
		//ノイズの描画
		for (int x = 0; x < SCREEN_SIZE_X; x++)
		{
			for (int y = 0; y < SCREEN_SIZE_Y; y++)
			{
				auto randomY = GetRand(10000);

				DrawPixel(x, y + randomY, GetColor(255, 255, 255));
			}
		}
		if (playerVec.y < 0)
		{
			paint_y++;//描画するときのずらす値
		}
		else if (playerVec.y > 0) {
			paint_y--;//描画するときのずらす値
		}
		if (playerVec.x > 0) {
			paint_x++;//描画するときのずらす値
		}
		else if (playerVec.x < 0) {
			paint_x--;//描画するときのずらす値
		}
	}
	else 
	{	//それ以外の時(燃料切れ)
		if (GameOverFlag)
		{
			paint_x = 0;//描画するときのずらす値
			paint_y--;	//描画するときのずらす値
		}
	}
	//自機の描画


	if (UFOFlag == true) {	//自機がufoの時
		DrawRotaGraph(Ppos_x + paint_x, Ppos_y - paint_y, 1.0, playerAngle, ImageMng::GetInstance().SetID("image/ufo.png"), true);
	}
	else {
		//自機通常時(ロケット)
		DrawRotaGraph(Ppos_x + paint_x, Ppos_y - paint_y, 1.0, playerAngle, ImageMng::GetInstance().SetID("image/player.png"), true);
	}

	// ﾘﾄﾗｲorﾀｲﾄﾙを選択
	if (DrawGameOver)
	{
		GameOverCnt = false;
		if (KeyMng::GetInstance().trgKey[P1_UP])
		{
			if (pauseCheck)
			{
				pauseCheck = false;
			}
		}
		else if (KeyMng::GetInstance().trgKey[P1_DOWN])
		{
			if (!pauseCheck)
			{
				pauseCheck = true;
			}
		}

		// ﾘﾄﾗｲorﾀｲﾄﾙ
		if (KeyMng::GetInstance().trgKey[P1_SPACE] && pauseCheck)
		{
			time = 0;
			AnimCnt = 0;
			AnimTime = 0;
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

			titleBright = 0;
			if (shakeWidth > 0)
				shakeWidth = 0;
			rocketSize = 0.0f;
			rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };
			lightFlag = false;
			pushSpace = false;
			UFOFlag = false;
			GameOverFlag = false;
			DrawGameOver = false;
			OutScr = false;
			overBright = 255;

			GtskPtr = &GameTask::GameTitle;
		}
		if (KeyMng::GetInstance().trgKey[P1_SPACE] && !landGameCheck && !pauseCheck)
		{
			AnimCnt = 0;
			AnimTime = 0;
			paint_y = 0;
			retryCnt++;
			(*obstracle)->SetPos(VECTOR3((float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y));
			GameOverFlag = false;
			DrawGameOver = false;
			OutScr = false;
			overBright = 255;
			if (!getSample)
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
				GtskPtr = &GameTask::GameInit;
			}
			else
			{
				auto setCnt = 0;
				auto itrPos = VECTOR3(0, 0);
				for (auto itr : bpList)
				{
					itrPos = itr->GetPos();
					itr->SetPos(VECTOR3(tSetPos[setCnt].x, tSetPos[setCnt].y + (pltrgPos.y - targetSet[StageCnt].y)));
					setCnt++;
				}
				(*player)->SetPos(VECTOR3(pltrgScr.x*1.2f, playerPos.y));
				(*player)->SetVec(VECTOR3(0, 0.1f));
				(*player)->SetEnergy(100.0f);
				(*player)->SetplPos(VECTOR3(setplPos.x, setplPos.y));
				SetScrollPos(-targetVec);


				setCount = true;
				landingCheck = false;
				landAnimFlag = false;
				landingFlag = true;
				clearCheck = true;						// ｸﾘｱ可能状態にする
				hitCheck = false;
				clearCnt = 0;
				GtskPtr = &GameTask::GameMain;
			}
			if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// Overが再生中ならOverの音を止める


		}

		// ﾁｪｯｸﾎﾟｲﾝﾄ到達時
		if (KeyMng::GetInstance().trgKey[P1_SPACE] && landGameCheck && !pauseCheck)
		{
			landGameCheck = false;
			OutScr = false;
			retryCnt++;

			if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// Overが再生中ならOverの音を止める

			GtskPtr = &GameTask::GameLanding;
		}
	}


	//小惑星or隕石に当たってゲームオーバーの時
	//if (bomFlag == true) {
	if (hitCheck == true && !OutScr) {
		GameOverFlag = true;
		DrawGameOver = true;
		if (AnimCnt >= 11) {
			AnimCnt = 0;
		}
		if (AnimTime++ % 10 == 0)
		{
			AnimCnt++;
		}
		if (AnimCnt <= 10)
		{
			DrawGraph(Bpos_x, Bpos_y - paint_y, DieAnim[AnimCnt], true);	//爆発エフェクト描画
		}
	}
	//}
	if (OutScr)
	{
		if (alphaJ > 128)
		{
			alphaM += 2.5f;
		}
		if (koukaSize < 1 && koukaSize > 0)
		{
			koukaSize += 0.025f;
			koukaSave = koukaSize;
		}
		else if (koukaSave > 1)
		{
			PlaySoundMem(koukaon, DX_PLAYTYPE_BACK);
			koukaSave = -1;
		}
		if (koukaSave == -1)
		{
			shake = GetRand(kouka_shake);
		}
		if (!CheckSoundMem(koukaon))
		{
			shake = 0;
		}
		if (shake == 0)
		{
			GameOverCnt++;
		}
		if (GameOverCnt > 60)
		{
			GameOverFlag = true;
		}
		if (!DrawGameOver && KeyMng::GetInstance().trgKey[P1_SPACE] && GtskPtr != &GameTask::GameInit && GtskPtr != &GameTask::GameMain && GtskPtr != &GameTask::GameTitle && GtskPtr != &GameTask::GameLanding)
		{
			shake = 0;
			GameOverFlag = true;
			StopSoundMem(koukaon);
			overBright = 70;
			DrawGameOver = true;
		}
		DrawGraph(-250 + shake, -100 + shake, ImageMng::GetInstance().SetID("image/shuchusen2.png"), true);
		alphaJ += 1.3f;
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake, 265 / 2 + shake, koukaSize, 0, ImageMng::GetInstance().SetID("image/koukaon.png"), true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaJ);
		DrawGraph(0 + shake / 2, 0 + shake / 2, ImageMng::GetInstance().SetID("image/jiki_end.png"), true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaM);
		DrawGraph(70 + shake / 2, (SCREEN_SIZE_Y - 75 * 3.0f) + shake / 2, ImageMng::GetInstance().SetID("image/ka-zuEnd_moji.png"), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alphaM);
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


	//DrawString(0, 0, "GameResult", 0xffffff);

	if (DrawGameOver)
	{
		SetFontSize(50);		// ﾌｫﾝﾄのｻｲｽﾞ
		SetFontThickness(8);	// ﾌｫﾝﾄの太さ
		ChangeFont("Ailerons");
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 - 50, 1.0, 0, IMAGE_ID("image/pause/gameover.png"), true);
		if (pauseCheck)
		{
			DrawRotaGraph(SCREEN_CENTER_X - 75, 625, 1.0, 0, IMAGE_ID("image/pause/titleback.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 625, 0.8, 0, IMAGE_ID("image/pause/選択.png"), true);
			SetDrawBright(100, 100, 100);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 525, 1.0, 0, IMAGE_ID("image/pause/retry.png"), true);
		}
		else
		{
			DrawRotaGraph(SCREEN_CENTER_X - 75, 525, 1.0, 0, IMAGE_ID("image/pause/retry.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 525, 0.8, 0, IMAGE_ID("image/pause/選択.png"), true);
			SetDrawBright(100, 100, 100);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 625, 1.0, 0, IMAGE_ID("image/pause/titleback.png"), true);
		}
		//DrawString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "GAME OVER", 0xffffff);
		SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ
		SetFontThickness(8);	// ﾌｫﾝﾄの太さ
		ChangeFont("MSゴシック");
	}
	
	ScreenFlip();

	return 0;
}

int GameTask::GameClear(void)
{
	ClsDrawScreen();


	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		StopSoundMem(ClearBGM);
		GtskPtr = &GameTask::GameTitle;
	}

	if (MaxTime >= 2000)
	{
	}
	else
	{
		if (CheckSoundMem(ClearBGM) == 0)
			PlaySoundMem(ClearBGM, DX_PLAYTYPE_LOOP);
		if (slideE > -130)
		{
			slideE--;
		}
		if (slideP < 50)
		{
			slideP += 0.5;
		}
		DrawGraph(0, 0, IMAGE_ID("image/landBG.png"), true);
		DrawRotaGraph(SCREEN_SIZE_X + 130 + slideE, 150, -earthSize - 1, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);
		DrawRotaGraph(0 + slideP, SCREEN_SIZE_Y - 150, 3, 0, IMAGE_ID("image/End.png"), true);
		DrawRotaGraph(SCREEN_SIZE_X / 2 - 50, SCREEN_SIZE_Y / 2, 1, 0, IMAGE_ID("image/総合評価.png"), true);
	}

	// 総合評価
	if (StageCnt == 3)
	{
		if (sogo <= 27 && sogo >= 18)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 70, SCREEN_SIZE_Y / 2, 2, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
			if (sogo >= 23)
			{
				DrawRotaGraph(SCREEN_SIZE_X / 2 + 120, SCREEN_SIZE_Y / 2, 2, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
			}
		}
		else if (sogo >= 17 && sogo <= 8)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 70, SCREEN_SIZE_Y / 2, 2, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
			if (sogo >= 11)
			{
				DrawRotaGraph(SCREEN_SIZE_X / 2 + 120, SCREEN_SIZE_Y / 2, 2, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
			}
		}
		else if (sogo >= 7 && sogo <= 0)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 70, SCREEN_SIZE_Y / 2, 2, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
			if (sogo > 3)
			{
				DrawRotaGraph(SCREEN_SIZE_X / 2 + 120, SCREEN_SIZE_Y / 2, 2, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
			}
		}
		else
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 70, SCREEN_SIZE_Y / 2, 2, 0, ImageMng::GetInstance().SetID("image/rank_D.png"), true);
		}
	}

	//DrawString(0, 0, "GameClear", 0xffffff);


	//DrawFormatStringF(10, 600, GetColor(255, 255, 255), "MaxTime %d", MaxTime);

	ScreenFlip();

	return 0;
}

void GameTask::Transition()
{
	EtoP = (GetErPosY() - GetPlPosY()) / 300;
	//if(((-GetSclPosY() / EtoP) + 700) > 350)
	EtoPtrans = ((-GetSclPosY() / EtoP) + 700);

	//DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0xffffff, "%f", EtoP);
	//DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 + 20, 0xffffff, "%f", EtoPtrans);
	//DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 + 20, 0xffffff, "%f", disTrans);
	for (int i = 0; i < 3; i++)
	{
		if (GtskPtr == &GameTask::GameMain)
		{
			DrawLine(399 + i, 50, 399 + i, 750, GetColor(128, 128, 128), true);
			DrawLine(399 + i, 400, 399 + i, 750, GetColor(128, 128, 128), true);
			DrawLine(399 + i, EtoPtrans, 399 + i, 750, GetColor(255, 255, 255), true);
			DrawCircle(400, 50, 5, GetColor(128, 128, 128), true);
			DrawCircle(400, 160, 5, GetColor(128, 128, 128), true);
			DrawRotaGraph(400, 750, 2, 0, ImageMng::GetInstance().SetID("image/chikyu_trans.png"), true);
			if (GetLandCheck())
			{
				transBright++;
			}
			if (clearCheck)
			{
				transBright--;
				if (transBright < 128)
				{
					transBright = 128;
				}
			}
			SetDrawBright(transBright, transBright, transBright);
			DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/mars_trans.png"), true);
			SetDrawBright(255, 255, 255);
			DrawRotaGraph(400, EtoPtrans, 1.5, 0, ImageMng::GetInstance().SetID("image/player4.png"), true);
			SetDrawBright(128, 128, 128);
			DrawRotaGraph(400, disTrans, 1, 0, ImageMng::GetInstance().SetID("image/spCraft.png"), true);
			//DrawString(400, 160, "parachute\nseparate", 0xffffff, true);
			DrawStringToHandle(406, 150, "parachute", GetColor(255, 255, 255), font);
			DrawStringToHandle(406, 160, "separate", GetColor(255, 255, 255), font);
			SetDrawBright(255, 255, 255);
		}
		else if (GtskPtr == &GameTask::GameLanding && GetScene() == 2)
		{
			if (-GetLdistance() / 2 + 700 * 0.55 > 50)
			{
				disTrans = -GetLdistance() / 2 + 700 * 0.55;
			}

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, GetAlpha());
			DrawLine(399 + i, 50, 399 + i, 750, GetColor(128, 128, 128), true);
			DrawLine(399 + i, 50, 399 + i, disTrans, GetColor(255, 255, 255), true);
			DrawLine(399 + i, 400, 399 + i, 750, GetColor(128, 128, 128), true);
			DrawCircle(400, 50, 5, GetColor(255, 255, 255), true);
			if (disTrans >= 160)
			{
				colBright++;
				if (colBright > 255)
				{
					colBright = 255;
				}
			}
			DrawCircle(400, 160, 5, GetColor(colBright, colBright, colBright), true);
			DrawStringToHandle(406, 150, "parachute", GetColor(colBright, colBright, colBright), font);
			DrawStringToHandle(406, 160, "separate", GetColor(colBright, colBright, colBright), font);
			DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/mars_trans.png"), true);
			DrawRotaGraph(400, disTrans, 1, 0, ImageMng::GetInstance().SetID("image/spCraft.png"), true);
			SetDrawBright(128, 128, 128);
			DrawRotaGraph(400, 750, 2, 0, ImageMng::GetInstance().SetID("image/chikyu_trans.png"), true);
			DrawRotaGraph(400, EtoPtrans, 1.5, 0, ImageMng::GetInstance().SetID("image/player4.png"), true);
			SetDrawBright(255, 255, 255);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, GetAlpha());
		}
	}
}

int GameTask::Shake()
{
	shake = GetRand(shakeWidth);
	if (pushSpace && GtskPtr == &GameTask::GameTitle)
	{
		return 0;
	}
	else
	{
		return shake;
	}
}

std::list<obj_ptr>::iterator GameTask::AddObjlist(obj_ptr && objPtr)
{
	objList.push_back(objPtr);
	auto itr = objList.end();
	itr--;
	return itr;
}

std::vector<bp_ptr>::iterator GameTask::AddBplist(bp_ptr && bpPtr)
{
	bpList.push_back(bpPtr);
	auto itr = bpList.end();
	itr--;
	return itr;
}


