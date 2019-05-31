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
	//�L�[���X�V
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

const float & GameTask::GetRocketSize(void)
{
	return rocketSize;
}

const int & GameTask::GetLandingCnt(int i)
{
	return landingCnt[i];
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
	SetWindowText("�X�C���O�o�C");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	for (int j = 0; j < 11; j++)
	{
		DieAnim[j] = LoadDivGraph("image/Explosion/����_��.png", 11, 11, 1, 115, 100, DieAnim, true);
		OutScrAnim[0][j] = LoadDivGraph("image/Number/count_sushiki.png", 10, 10, 1, 50, 50, OutScrAnim[0], true);
		if (j <= StageMax)
		{
			OutScrAnim[1][j] = LoadDivGraph("image/Number/StageCnt_sushiki.png", 3, 3, 1, 100, 100, OutScrAnim[1], true);
		}
		//DieAnim[j] = LoadGraph("image/����_��.png");
	}
	for (int i = 0; i < EarthMax; i++)
	{
		EarthImage[i] = LoadDivGraph("image/earthAnimNC.png", 20, 20, 1, 100, 50, EarthImage, true);
	}

	//���y�t�@�C���ǂݍ���
	OP = LoadBGM("sound/���̉F���̂ǂ�����.mp3");
	Main = LoadBGM("sound/�������~���.mp3");
	ED1 = LoadBGM("sound/�V��.ogg");
	ED2 = LoadBGM("sound/farewell.ogg");
	LED = LoadBGM("sound/���E���l�B�ɗh���܂�.ogg");
	Over = LoadBGM("sound/�F�����.ogg");
	Result_rank = LoadBGM("sound/bomb.mp3");
	Result_rankAll = LoadBGM("sound/destruction1.mp3");
	Cheers = LoadBGM("sound/people_people-stadium-cheer1.mp3");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// ���k���ꂽ�S�f�[�^�̓V�X�e���������Ɋi�[����A�Đ����镔�����������𓀂��Ȃ���T�E���h�������Ɋi�[����(�炵�I���Ɖ𓀂����f�[�^�͔j�������̂ŉ��x���𓀏������s����)
	Decision = LoadSoundMem("sound/�I����.ogg");
	Rocket = LoadSoundMem("sound/���P�b�g����.mp3");
	EngineM = LoadSoundMem("sound/��s�@�E���^�W�F�b�g�@mid.mp3");
  	EngineLand = LoadSoundMem("sound/atmosphere4.mp3");
	Boost = LoadSoundMem("sound/�K�X�o�[�i�[.mp3");
	fire = LoadSoundMem("sound/�K�X�o�[�i�[.mp3");
	Emergency = LoadSoundMem("sound/�x��.ogg");
	Emergency2 = LoadSoundMem("sound/�x��03.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	UFO = LoadSoundMem("sound/UFO01.ogg");
	wind = LoadSoundMem("sound/�V��E�r��̕�.mp3");
	noise = LoadSoundMem("sound/�����̉��E�e���r�̃z���C�g�m�C�Y��.mp3");
	koukaon = LoadSoundMem("sound/small_explosion1.mp3");
	Gas = LoadSoundMem("sound/�K�X���R��鉹loop.mp3");
	ClearBGM = LoadSoundMem("sound/uchuu-hachimoku.mp3");

	GtskPtr = &GameTask::GameTitle;
	return 0;
}


int GameTask::GameInit(void)
{
	//
	auto reset = [&] {
		time = 0;
		AnimCnt = 0;
		clearCnt = 0;
		limitAnimSize = 2.0f;
		limitTime = 6;
		subTitleCnt = 0;
		subTitleAnim = 0;
		outScreenTime = 0;
		EtoP = 0.0f;
		EtoPtrans = ((-533 / 5) + 700);
		disTrans = 50.0f;
		shake = 0.0f;
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
	};
	//

	objList.clear();
	bpList.clear();

	//
	reset();
	//

	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	obstracle = AddObjlist(std::make_shared<Obstracle>());

	earth = AddBplist(std::make_shared<Earth>(VECTOR3(225, SCREEN_SIZE_Y * 1.5f)));

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

	(*player)->init("image/Player2.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);

	//ImageMng::GetInstance().SetID("TITLE", "image/�^�C�g��.png");
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

	//�T�E���h�֌W
	ChangeVolumeSoundMem(255 * 70 / 100, OP);//OP�̉��̃{�����[����70%�ɐݒ�
	if (CheckSoundMem(OP) == 0)PlaySoundMem(OP, DX_PLAYTYPE_LOOP);//OP���Đ����łȂ���Ή���炷

																  //�B���R�}���h
	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}

	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/landBG.png"), true);
	//if ((lgtsCnt++ / 30) % 2 == 0)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 1, angle += 0.005f, ImageMng::GetInstance().SetID("image/LGTS.png"), true);
	}
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - 100, earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	// ���ى��
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, (SCREEN_SIZE_Y - 100) + shakeEarth, earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		int ufo_x = 25, ufo_y = 200;
		DrawGraph(ufo_x, ufo_y, IMAGE_ID("image/UFO����.png"), true);
	}
	//�Q�[�����[�h�ڍs
	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		/*if (CheckSoundMem(OP) == 0)*/PlaySoundMem(Rocket, DX_PLAYTYPE_BACK);
		titleShake = 5;
		//pushSpace = true;
		launchFlag = true;
	}

	// ̪���
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

	// �U��
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
		if (!UFOFlag)
		{
			// �߰è�ٍ쐬
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

			// �߰è�ق̍폜
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
			// ۹�ĕ`��
			DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/rocket.png"), true);
		}
		else
		{
			UFOpos.x += 5;
			if (!ufoYflag)
			{
				UFOpos.y--;
			}
			else
			{
				UFOpos.y++;
			}
			if (UFOpos.y <= 440 && !ufoYflag)
			{
				ufoYflag = true;
			}
			else if (UFOpos.y >= 450 && ufoYflag)
			{
				ufoYflag = false;
			}
			// ufo�`��
			DrawRotaGraph(UFOpos.x, UFOpos.y, 0.3, 0, ImageMng::GetInstance().SetID("image/ufo(side).png"), true);
		}

		timeCnt++;
		// ��ݽ����
		if (timeCnt > 1)
		{
			if (KeyMng::GetInstance().trgKey[P1_SPACE])
			{
				skipFlag = true;
			}
		}
		DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/rocket.png"), true);
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
				if (CheckSoundMem(OP) == 1) StopSoundMem(OP);//Title���Đ����Ȃ�Title���~�߂�

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

// �F���V�j
int GameTask::GameMain(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ClsDrawScreen();

	// �߰�ޗp
	if (KeyMng::GetInstance().trgKey[P1_PAUSE] && !GetHitCheck())
	{
		if (pauseFlag)
		{
			pauseFlag = false;
		}
		else
		{
			pauseFlag = true;
			pauseBrightTime = 0;
		}
	}

	//DrawFormatString(10, 600, 0xffffff, "flag %d", pauseFlag);

	if (!pauseFlag)
	{
		// ���ިݸގ��̕���p����ьv��
		MainTimer++;
	}
	else
	{
		if (255 - pauseBrightTime > 100)
		{
			pauseBrightTime += 5;
		}
		SetDrawBright(255 - pauseBrightTime, 255 - pauseBrightTime, 255 - pauseBrightTime);
	}

	//DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0xffffff, "%d", lpGameTask.clearCheck);
	//DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0xffffff, "%d", lpGameTask.StageCnt);

	ChangeVolumeSoundMem(255 * 50 / 100, Main);//OP�̉��̃{�����[����70%�ɐݒ�
	if (CheckSoundMem(Main) == 0)PlaySoundMem(Main, DX_PLAYTYPE_LOOP);//Main���Đ����łȂ���Ή���炷

																	  //�T�E���h�֌W
	if (KeyMng::GetInstance().newKey[P1_UP]) {//���L�[�������ꂽ�Ƃ�
		if (UFOFlag == true) 
		{
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFO���Đ����łȂ���Ή���炷
		}
		else
		{
			eSoundFlag = 1;
			//���P�b�g���˂̉����Đ����łȂ���΃��P�b�g���˂̉����Đ�����
			ChangeVolumeSoundMem(255 * 60 / 100, EngineM);
			if (CheckSoundMem(EngineM) == 0)PlaySoundMem(EngineM, DX_PLAYTYPE_LOOP);//UFO���Đ����łȂ���Ή���炷
		}
	}
	else
	{	//�����łȂ���Ή����~�߂�
		StopSoundMem(UFO);//UFO�����~�߂�
		StopSoundMem(EngineM);//Rocket�����~�߂�
		StopSoundMem(Rocket);//Rocket�����~�߂�
		if (soundVol <= 100)
		{
			soundVol++;
		}
		//ChangeVolumeSoundMem(255 * soundV.Engine - soundVol / 100, EngineF);
	}
	if (KeyMng::GetInstance().newKey[P1_RIGHT] || KeyMng::GetInstance().newKey[P1_LEFT])
	{
		if (UFOFlag == true)
		{
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFO���Đ����łȂ���Ή���炷
		}
		else
		{
			eSoundFlag = 1;
			//���P�b�g���˂̉����Đ����łȂ���΃��P�b�g���˂̉����Đ�����
			ChangeVolumeSoundMem(255 * 30 / 100, Gas);
			if (CheckSoundMem(Gas) == 0)PlaySoundMem(Gas, DX_PLAYTYPE_LOOP);//UFO���Đ����łȂ���Ή���炷
		}
	}
	else 
	{	//�����łȂ���Ή����~�߂�
		StopSoundMem(UFO);//UFO�����~�߂�
		StopSoundMem(Rocket);//Rocket�����~�߂�
		StopSoundMem(Gas);//Rocket�����~�߂�
		if (soundVol <= 100)
		{
			soundVol++;
		}
		//ChangeVolumeSoundMem(255 * soundV.Engine - soundVol / 100, EngineF);
	}

	if (KeyMng::GetInstance().oldKey[P1_UP])
	{
		soundV.Engine--;
	}
	else
	{
		soundV.Engine = 100;
	}

	SetCurrentPositionSoundMem(44100,Boost);
	if (KeyMng::GetInstance().trgKey[P1_SPACE]) {
	//	if (CheckSoundMem(Boost) == 0)PlaySoundMem(Boost, DX_PLAYTYPE_BACK);//Boost���Đ����łȂ���Ή���炷
	//	psFlag = true;
	//}
	//else {
	//	if (sBoostCnt >= 50)
	//	{
	//		sBoostCnt = 0;
	//		StopSoundMem(Boost);//Boost�����~�߂�
	//	}
	//}

	//if (psFlag)
	//{
	//	sBoostCnt++;
	//	if (sBoostCnt > 50)
	//	{
	//		psFlag = false;
	//		sBoostCnt = 50;
	//	}
	}

	// ��������
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

			//DrawFormatString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_CENTER_Y, GetColor(subTitleCnt, subTitleCnt, subTitleCnt), "STAGE");
			SetDrawBright(subTitleCnt, subTitleCnt, subTitleCnt);
			DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y + 25, 1.3, 0, IMAGE_ID("image/stage_kana.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X + SCREEN_SIZE_X / 4, SCREEN_CENTER_Y + 25, 0.7, 0, OutScrAnim[1][StageCnt], true);
			SetDrawBright(255, 255, 255);
		}
		else
		{
			if (subTitleCnt > 0)
			{
				subTitleCnt -= 5;
				//DrawFormatString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_CENTER_Y, GetColor(subTitleCnt, subTitleCnt, subTitleCnt), "STAGE");
				SetDrawBright(subTitleCnt, subTitleCnt, subTitleCnt);
				DrawRotaGraph(SCREEN_CENTER_X, SCREEN_CENTER_Y + 25, 1.3, 0, IMAGE_ID("image/stage_kana.png"), true);
				DrawRotaGraph(SCREEN_CENTER_X + SCREEN_SIZE_X / 4, SCREEN_CENTER_Y + 25, 0.7, 0, OutScrAnim[1][StageCnt], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{

			}
		}
		ChangeFont("MS�S�V�b�N");

		SetFontSize(20);		// ̫�Ă̻���

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
	// �����܂�

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(Main) == 1) {	//Main���Đ����Ȃ�
			StopSoundMem(Main);	////�������ɓǂݍ���Main�̉��f�[�^���폜
			StopSoundMem(Rocket);// Rocket���Đ����Ȃ�Rocket�̉����~�߂�
			StopSoundMem(Boost);// Boost���Đ����Ȃ�Boost�̉����~�߂�
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

		// ���ׂĂ̘f����Update
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
		//(*player)->GetPos();
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
				DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
				StopSoundMem(UFO);		//UFO�����~�߂�
				StopSoundMem(Rocket);	//Rocket�����~�߂�
				StopSoundMem(Boost);	//Boost�����~�߂�
				if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//�����������Ă��邩���ׂĂȂ��Ă��Ȃ�������炷
																				// ������if��
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
	// �w�i�̍폜
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

	//��`�̓����蔻��
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) {
		hitCheck = true;
		if (GetLandCheck()) {
			hitCheck = false;
		}
	}

	if (hitCheck == true) {	//�v���C���[�����񂾂Ƃ�
		StopSoundMem(UFO);		//UFO�����~�߂�
		StopSoundMem(Rocket);	//Rocket�����~�߂�
		StopSoundMem(Boost);	//Boost�����~�߂�
								//���������Đ����łȂ���Δ��������Đ�����
		if (AnimTime++ % 10 == 0)
		{
			AnimCnt++;
		}
		DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
		if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//Bom���Đ����łȂ���Ή���炷
		if (AnimCnt >= 11)
		{
			GameOver();
		}
	}
	else {
		StopSoundMem(Bom);	//Bom�����~�߂�
	}

	// �����܂�
	Transition();


	// ����������
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
				// �����Ɉڍs
				GtskPtr = &GameTask::GameLandInit;
			}

		}

		if (landingCnt[0] <= 100)
		{
			// Я��ݸر
			if (returnFlag && clearCheck && landingCheck && landingFlag)
			{
				auto SaveGameMain = SaveDrawScreenToPNG(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, "image/Screen/screen.png", 0);
				resultAnim = LoadGraph("image/Screen/screen.png");

				// Я��ݸر
				GtskPtr = &GameTask::GameResult;
			}
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	else
	{
		// ����
		if (landingCnt[0] < 255 && !GetHitCheck())
		{
			landingCnt[0] += 20;
		}

		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0.9, 0, ImageMng::GetInstance().SetID("image/����.png"), true);
	DrawRotaGraph(SCREEN_SIZE_X / 2, 0, 0.9, 0, ImageMng::GetInstance().SetID("image/����.png"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ��������
	// ���@�̉�ʊO��
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
			landingCnt[1] -= 10;
			limitTime--;
			if (limitTime <= 0)
			{
				limitTime = 0;
			}
		/*	if (CheckSoundMem(Emergency2) == 0)PlaySoundMem(Emergency2, DX_PLAYTYPE_BACK);*/
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
		/*	if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);*/
			if (CheckSoundMem(noise) == 1)StopSoundMem(noise);
			soundV.noise = 50;
		}
	}

	// �R�����ʎ�
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
				landingCnt[1] -= 5;
			}
			else if (landingCnt[1] <= 5)
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
	// �����܂�


	if (clearCheck)
	{
		clearCnt++;
	}
	if (AnimCnt >= 10)
	{
		AnimCnt = 10;
	}

	// �����������̑����̖��G����
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

	// ��������
	if (OutOfScreen && !pauseFlag)
	{
		//SetFontSize(limitAnimSize--);
		limitAnimSize -= 0.033f;
		if (limitTime <= 0)
			SetDrawBright(255, 255, 255);
		//DrawFormatString(SCREEN_CENTER_X, SCREEN_CENTER_Y, GetColor(255, 255, 255), "%d", limitTime);
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, limitAnimSize, 0, OutScrAnim[0][limitTime], true);
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		SetFontSize(20);		// ̫�Ă̻���
		if(cdCount++ % 4 == 0)
		landingCnt[1]--;
		if (landingCnt[1] < 65 && limitTime == 0)
		{
			ClsDrawScreen();
			StopSoundMem(noise);
			GtskPtr = &GameTask::GameOver;
			GameOverTime = 0;
		}
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
	}

	if (limitAnimSize <= 0)
	{
		limitAnimSize = 2.0f;
	}



	// �ð�޶���
	if (!getSample && !pauseFlag)
	{
		StageDraw();

	}
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawString(100, 200, "PAUSE", 0xffffff, true);
	}


	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "playerPosX %f playerPosY %f", playerPos.x, playerPos.y);
	DrawFormatStringF(10, 550, GetColor(255, 255, 255), "targetVecX %f targetVecY %f", targetVec.x, targetVec.y);
	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "time %d", MainTimer);


	if (clearCheck)
	{
		StopSoundMem(wind);
	}

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
	StopSoundMem(Emergency);//Emergency�����~�߂�

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
	//if(GetScene() == 2 && )
	
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

	if (GetSpr())
	{
		if (KeyMng::GetInstance().newKey[P1_UP])
		{
			ChangeVolumeSoundMem(255 * 100 / 100, EngineLand);
			if (CheckSoundMem(EngineLand) == 0)
				PlaySoundMem(EngineLand, DX_PLAYTYPE_LOOP);//Engine���Đ����łȂ���Ή���炷
		}
		else
		{
			StopSoundMem(EngineLand);
		}
		if (KeyMng::GetInstance().newKey[P1_RIGHT] || KeyMng::GetInstance().newKey[P1_LEFT])
		{
			if (CheckSoundMem(Gas) == 0)
				PlaySoundMem(Gas, DX_PLAYTYPE_LOOP);//Engine���Đ����łȂ���Ή���炷
		}
		else
		{
			StopSoundMem(Gas);
		}
	}

	// �����B��������F���֖߂�
	if (landAnimFlag)
	{
		pltrgPos = VECTOR3(playerPos.x + targetVec.x * 2, playerPos.y);
		(*player)->SetPos(pltrgPos);
		SetScrollPos(targetVec);
		setCount = true;
		landingCheck = false;
		landAnimFlag = false;
		landingFlag = true;
		clearCheck = true;						// �ر�\��Ԃɂ���
		darkFlag = false;
		darkFlag2 = false;
		pushSpace = false;
		lightFlag = false;
		cupLandingCheck = false;			// ��߾ق�size��0�ɂȂ������׸�
		checkCnt = 0;
		pltrgPos = { 0,0 };
		if (objList.size() > 0)
		{
			objList.pop_back();
		}
		GtskPtr = &GameTask::GameMain;
	}

	Transition();
	DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 0xffffff, "%f", GetCupSize());
	ScreenFlip();
	return 0;
}

int GameTask::GameResult(void)
{
	auto Evaluation = [&] {

		// ��ѕ]��
		if (MainTimer <= 200)
		{
			timeEval = 3;
		}
		else if(MainTimer <= 400)
		{
			timeEval = 2;
		}
		else
		{
			timeEval = 1;
		}

		// �R���c�]��
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

		// �c�@�]��

		// ����
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

	ClsDrawScreen();
	int imageX = 0, imageY = 0;

	// �摜�̻��ގ擾
	GetGraphSize(ImageMng::GetInstance().SetID("image/Result/�Î�2.png"), &imageX, &imageY);
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
	SetDrawBright(110,110,110);
	DrawGraph(0, 0, resultAnim, true);
	SetDrawBright(255, 255, 255);


	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);

	//////////////////////////////////////////////
	if (!getSample)
	{
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/�Î�2.png"), true);
	}
	else
	{
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/�g2.png"), true);
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/����2.png"), true);
	}
	DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y - imageY / 2 + 50, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/�g.png"), true);
	/////////////////////////////////////////////////

	// �]��
	Evaluation();

	//�T�E���h
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// Rocket���Đ����Ȃ�Rocket�̉����~�߂�
	if (CheckSoundMem(Boost) == 1)StopSoundMem(Boost);// Boost���Đ����Ȃ�Boost�̉����~�߂�
	StopSoundMem(Bom);	// Bom���Đ����Ȃ�Bom�̉����~�߂�
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// Main���Đ����Ȃ�Main�̉����~�߂�
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//Emergency�����Đ����Ȃ�Emergency�����~�߂�

	SetFontSize(50);		// ̫�Ă̻���
	SetFontThickness(8);	// ̫�Ă̑���
	ChangeFont("Ailerons");
	//DrawString(SCREEN_SIZE_X / 2 - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "RESULT", 0xffffff);
	//DrawFormatStringF(10, 450, GetColor(255, 255, 255), "time   %d %c", MainTimer, timeEval);
	//DrawFormatStringF(10, 500, GetColor(255, 255, 255), "sample %d %c", getSample, sampleEval);//Evaluation
	//DrawFormatStringF(10, 600, GetColor(255, 255, 255), "Evaluation %d", getSample);
	//SetFontSize(20);		// ̫�Ă̻���
	//SetFontThickness(8);	// ̫�Ă̑���
	//ChangeFont("MS�S�V�b�N");

	// ��ver
	DrawRotaGraph(SCREEN_SIZE_X / 2, 50, 1.5, 0, ImageMng::GetInstance().SetID("image/result_kana.png"), true);
	DrawRotaGraph(100, 125, 1, 0, ImageMng::GetInstance().SetID("image/time_kana.png"), true);
	DrawRotaGraph(150, 200, 1, 0, ImageMng::GetInstance().SetID("image/nenryo_kana.png"), true);
	DrawRotaGraph(100, 275, 1, 0, ImageMng::GetInstance().SetID("image/life_kana.png"), true);
	DrawRotaGraph(100, SCREEN_SIZE_Y / 2, 1, 0, ImageMng::GetInstance().SetID("image/rank_kana.png"), true);


	// ��̧�ޯ�ver
	//DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.5, 0, ImageMng::GetInstance().SetID("image/result_eng.png"), true);
	//DrawRotaGraph(100, 500, 1, 0, ImageMng::GetInstance().SetID("image/time_eng.png"), true);
	//DrawRotaGraph(100, 600, 1, 0, ImageMng::GetInstance().SetID("image/sample_eng.png"), true);

	// �]��
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
				rankSize.incEnd = false;
			}
		}
	}
	if (timeEval == 3)
	{
		DrawRotaGraph(400, 125, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if(timeEval == 2)
	{
		DrawRotaGraph(400, 125, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400, 125, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (fuelEval == 3)
	{
		DrawRotaGraph(400, 200, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if(fuelEval == 2)
	{
		DrawRotaGraph(400, 200, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400, 200, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (lifeEval == 3)
	{
		DrawRotaGraph(400, 275, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if (lifeEval == 2)
	{
		DrawRotaGraph(400, 275, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400, 275, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (all == 9 || all == 8)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
		if (all == 9)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50, SCREEN_SIZE_Y / 2, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else if (all == 7 || all == 6)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
		if (all == 7)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50, SCREEN_SIZE_Y / 2, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else if (all == 5 || all == 4)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
		if (all == 5)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50, SCREEN_SIZE_Y / 2, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_D.png"), true);
	}
	

	static int count = 0;
	int Clear_X = 0, Clear_Y = 680;

	if (StageCnt == 0) {
		if (CheckSoundMem(ED1) == 0)PlaySoundMem(ED1, DX_PLAYTYPE_LOOP);//Result���Đ����łȂ���Ή���炷
		count = (count + 1) % 100;
		if (count < 50) {
			//DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage1Clear.png"), true);
		}
	}
	else if (StageCnt == 1) {
		if (CheckSoundMem(ED2) == 0)PlaySoundMem(ED2, DX_PLAYTYPE_LOOP);//Result���Đ����łȂ���Ή���炷
		count = (count + 1) % 100;
		if (count < 50) {
			//DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage2Clear.png"), true);
		}
	}
	else if (StageCnt == 2) {
		ChangeVolumeSoundMem(255 * 70 / 100, LED);//LED�̉��̃{�����[����70%�ɐݒ�
		if (CheckSoundMem(LED) == 0)PlaySoundMem(LED, DX_PLAYTYPE_LOOP);//Result���Đ����łȂ���Ή���炷
		count = (count + 1) % 100;
		if (count < 50) {
			//DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage3Clear.png"), true);
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

		if (CheckSoundMem(ED1) == 1)StopSoundMem(ED1);	// ED1���Đ����Ȃ�Ed1�̉����~�߂�
		if (CheckSoundMem(ED2) == 1)StopSoundMem(ED2);	// ED1���Đ����Ȃ�Ed1�̉����~�߂�

		if (CheckSoundMem(LED) == 1)StopSoundMem(LED);	// LED���Đ����Ȃ�LED�̉����~�߂�

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
		//DrawFormatStringF(10, 500, GetColor(255, 255, 255), "���� %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);
		//DrawFormatStringF(10, 550, GetColor(255, 255, 255), "time %d", MainTimer);
		//DrawFormatStringF(10, 600, GetColor(255, 255, 255), "MaxTime %d", MaxTime);
	}
	ScreenFlip();

	return 0;

}

int GameTask::GameOver(void)
{
	//�T�E���h
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// Rocket���Đ����Ȃ�Rocket�̉����~�߂�
	if (CheckSoundMem(Bom) == 1)StopSoundMem(Bom);// Bom���Đ����Ȃ�Bom�̉����~�߂�
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// Main���Đ����Ȃ�Main�̉����~�߂�
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//Emergency�����Đ����Ȃ�Emergency�����~�߂�
	if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);
	if (CheckSoundMem(Over) == 0)PlaySoundMem(Over, DX_PLAYTYPE_LOOP);//Over���Đ����łȂ���Ή���炷

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
		if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// Over���Đ����Ȃ�Over�̉����~�߂�
														// �w�i�̍폜
		std::vector<BackGround*>::iterator itrBG = backVec.begin();
		while (itrBG != backVec.end())
		{
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
		if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// Over���Đ����Ȃ�Over�̉����~�߂�

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


	SetFontSize(50);		// ̫�Ă̻���
	SetFontThickness(8);	// ̫�Ă̑���
	ChangeFont("Ailerons");
	DrawString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "GAME OVER", 0xffffff);
	SetFontSize(20);		// ̫�Ă̻���
	SetFontThickness(8);	// ̫�Ă̑���
	ChangeFont("MS�S�V�b�N");

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "���� %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);
	
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
		DrawGraph(-250 + shake, -100 + shake, ImageMng::GetInstance().SetID("image/shuchusen2.png"), true);
		alphaJ += 1.3f;
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake, 265 / 2 + shake, koukaSize, 0, ImageMng::GetInstance().SetID("image/koukaon.png"), true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaJ);
		DrawGraph(0 + shake / 2, 0 + shake / 2, ImageMng::GetInstance().SetID("image/jiki_end.png"), true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaM);
		DrawGraph(70 + shake / 2, (SCREEN_SIZE_Y - 75 * 3.0f) + shake / 2, ImageMng::GetInstance().SetID("image/ka-zuEnd_moji.png"), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alphaM);
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
		DrawRotaGraph(SCREEN_SIZE_X / 2 - 50, SCREEN_SIZE_Y / 2, 1, 0, IMAGE_ID("image/�����]��.png"), true);
	}

	// �����]��
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

	DrawString(0, 0, "GameClear", 0xffffff);
	

	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "MaxTime %d", MaxTime);

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
	// ��Ԃ̑J��
	for (int i = 0; i < 3; i++)
	{
		if (GtskPtr == &GameTask::GameMain)
		{
			DrawLine(399 + i, 50, 399 + i, 750, GetColor(128,128,128), true);
			// ���n
			DrawLine(399 + i, 400, 399 + i, 750, GetColor(128,128,128), true);
			// ��h��
			DrawLine(399 + i, EtoPtrans, 399 + i, 750, GetColor(255,255,255), true);
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
				disTrans = -GetLdistance() / 2 + 700 * 0.55;

			DrawLine(399 + i, 50, 399 + i, 750, GetColor(128,128,128), true);
			DrawLine(399 + i, 50, 399 + i, disTrans, GetColor(255, 255, 255), true);
			DrawLine(399 + i, 400, 399 + i, 750, GetColor(128,128,128), true);
			DrawCircle(400, 50, 5, GetColor(255, 255, 255), true);
			if (disTrans >= 160)
			{
				colBright++;
				if (colBright > 255)
				{
					colBright = 255;
				}
			}
			DrawCircle(400, 160, 5, GetColor(colBright,colBright,colBright), true);
			DrawStringToHandle(406, 150, "parachute", GetColor(colBright, colBright, colBright), font);
			DrawStringToHandle(406, 160, "separate", GetColor(colBright, colBright, colBright), font);
			DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/mars_trans.png"), true);
			DrawRotaGraph(400, disTrans, 1, 0, ImageMng::GetInstance().SetID("image/spCraft.png"), true);
			SetDrawBright(128, 128, 128);
			DrawRotaGraph(400, 750, 2, 0, ImageMng::GetInstance().SetID("image/chikyu_trans.png"), true);
			DrawRotaGraph(400, EtoPtrans, 1.5, 0, ImageMng::GetInstance().SetID("image/player4.png"), true);
			SetDrawBright(255, 255, 255);
		}
	}
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


