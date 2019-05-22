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
	SetWindowText("�X�C���O�o�C");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	for (int j = 0; j < 11; j++)
	{
		DieAnim[j] = LoadDivGraph("image/����_��.png", 11, 11, 1, 115, 100, DieAnim,true);
		OutScrAnim[j] = LoadDivGraph("image/countdown.png", 11, 11, 1, 100, 100, OutScrAnim, true);

		//DieAnim[j] = LoadGraph("image/����_��.png");
	}
	//���y�t�@�C���ǂݍ���
	OP = LoadBGM("sound/uchuu-tanken .ogg");
	Main = LoadBGM("sound/�F���̘Ȃ�.ogg");
	Result = LoadBGM("sound/�V��.ogg");
	Over = LoadBGM("sound/�F�����.ogg");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// ���k���ꂽ�S�f�[�^�̓V�X�e���������Ɋi�[����A�Đ����镔�����������𓀂��Ȃ���T�E���h�������Ɋi�[����(�炵�I���Ɖ𓀂����f�[�^�͔j�������̂ŉ��x���𓀏������s����)
	Decision = LoadSoundMem("sound/�I����.ogg");
	Rocket = LoadSoundMem("sound/���P�b�g����.ogg");
	Boost = LoadSoundMem("sound/�K�X�o�[�i�[.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	UFO = LoadSoundMem("sound/UFO01.ogg");
	GtskPtr = &GameTask::GameTitle;
	return 0;
}


int GameTask::GameInit(void)
{

	auto riset = [&] {
		time = 0;
		AnimCnt = 0;
		clearCnt = 0;
		limitAnimSize = 2.0f;
		limitTime = 4;
		subTitleCnt = 0;
		subTitleAnim = 0;
		outScreenTime = 0;
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
			mars = AddBplist(std::make_shared<Mars>(targetPlanet));
		}
	}

	if (UFOFlag == true) {
		(*player)->init("image/Player2.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}else{
		(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);

	back = new BackGround();

	GtskPtr = &GameTask::GameMain;

	return 0;
}

int GameTask::GameTitle(void)
{
	ClsDrawScreen();
	StageCnt = 0;

	int Title_X = -500, Title_Y = 0;
	//�摜�`��
	DrawGraph(Title_X, Title_Y, IMAGE_ID("image/title.png"), true);
	//�^�C�g�����S�`��
	int title_x = 50, title_y = 50;
	DrawGraph(title_x, title_y, IMAGE_ID("image/titleRogo.png"), true);
	//�T�E���h�֌W
	if (CheckSoundMem(OP) == 0)PlaySoundMem(OP, DX_PLAYTYPE_LOOP);//OP���Đ����łȂ���Ή���炷
	
	//�B���R�}���h
	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		int ufo_x = 25, ufo_y = 150;
		DrawGraph(ufo_x, ufo_y,IMAGE_ID("image/UFO����.png"), true);
	}
	//�Q�[�����[�h�ڍs
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(OP) == 1) StopSoundMem(OP);//Title���Đ����Ȃ�Title���~�߂�
		GtskPtr = &GameTask::GameInit;
	}
	DrawString(0, 0, "GAME_TITLE", 0xffffff);
	ScreenFlip();
	return 0;
}

// �F���V�j
int GameTask::GameMain(void)
{
	ClsDrawScreen();
	if (CheckSoundMem(Main) == 0)PlaySoundMem(Main, DX_PLAYTYPE_LOOP);//Main���Đ����łȂ���Ή���炷
	
	//�T�E���h�֌W
	if (KeyMng::GetInstance().newKey[P1_UP]) {//���L�[�������ꂽ�Ƃ�
		if (UFOFlag == true) {
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFO���Đ����łȂ���Ή���炷
		}
		else {
			//���P�b�g���˂̉����Đ����łȂ���΃��P�b�g���˂̉����Đ�����
			if (CheckSoundMem(Rocket) == 0)PlaySoundMem(Rocket, DX_PLAYTYPE_LOOP);//Rocket���Đ����łȂ���Ή���炷
		}
	}
	else {	//�����łȂ���Ή����~�߂�
		StopSoundMem(UFO);//UFO�����~�߂�
		StopSoundMem(Rocket);//Rocket�����~�߂�
	}

	if (KeyMng::GetInstance().newKey[P1_SPACE]) {
		if (CheckSoundMem(Boost) == 0)PlaySoundMem(Boost, DX_PLAYTYPE_BACK);//Boost���Đ����łȂ���Ή���炷
	}
	else {
		StopSoundMem(Boost);//Boost�����~�߂�
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
		ChangeFont("MS�S�V�b�N");

		SetFontSize(20);		// ̫�Ă̻���

	};

	auto GameOver = [&] {

		if (GetHitCheck())
		{
			if (landingCnt[0] > 0)
			{
				landingCnt[0] -= 10;
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
		landingCheck = false;
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(Main) == 1) {	//Main���Đ����Ȃ�
			StopSoundMem(Main);	////�������ɓǂݍ���Main�̉��f�[�^���폜
			StopSoundMem(Rocket);// Rocket���Đ����Ȃ�Rocket�̉����~�߂�
			StopSoundMem(Boost);// Boost���Đ����Ȃ�Boost�̉����~�߂�
			StopSoundMem(Bom);	// Bom���Đ����Ȃ�Bom�̉����~�߂�
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

	distance = { DISTANCE_MAX };
	time++;

	for (auto itr : bpList)
	{

		// ���ׂĂ̘f����Update
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
			DrawString((int)playerPos.x, (int)playerPos.y, "���ꂽ", 0xffffff);
			StopSoundMem(UFO);		//UFO�����~�߂�
			StopSoundMem(Rocket);	//Rocket�����~�߂�
			StopSoundMem(Boost);	//Boost�����~�߂�
			if(CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//�����������Ă��邩���ׂĂȂ��Ă��Ȃ�������炷
			// ������if��
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
	// �w�i�̍폜
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

	//��`�̓����蔻��
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) {
		hitCheck = true;
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


	// ����������
	if (landingCheck && landingFlag)
	{
		if (landingCnt[0] > 0)
		{
			landingCnt[0] -= 20;
		}
		else
		{
			// Я��ݸر
			if (returnFlag && clearCheck && landingCheck && landingFlag)
			{
				// Я��ݸر
				GtskPtr = &GameTask::GameResult;
			}
			if (landingCheck && landingFlag && !clearCheck)
			{
				// �����Ɉڍs
				GtskPtr = &GameTask::GameLandInit;
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

	// ��������
	// ���@�̉�ʊO��
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
			}
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
	}
	else
	{
		limitTime = 4;
		limitAnimSize = 2.0f;
		outScreenTime = 0;
		if (Energy >= 200 && landingCnt[1] < 255 && landingCnt[0] >= 255)
		{
			landingCnt[1] += 10;
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);

		}
	}

	// �R�����ʎ�
	if (Energy < 200 && !GetHitCheck())
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

	if (Energy <= 0 && !GetHitCheck())
	{
		if (GameOverTime++ > 60)
		{
			if (landingCnt[1] > 0)
			{
				landingCnt[1] -= 15;
			}
			else if(landingCnt[1] <= 5)
			{
				ClsDrawScreen();
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
	if (OutOfScreen)
	{

		//SetFontSize(limitAnimSize--);
		limitAnimSize -= 0.033f;
		if(limitTime > 10)
		SetDrawBright(255, 255, 255);
		//DrawFormatString(SCREEN_CENTER_X, SCREEN_CENTER_Y, GetColor(255, 255, 255), "%d", limitTime);
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, limitAnimSize, 0, OutScrAnim[limitTime], true);
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		SetFontSize(20);		// ̫�Ă̻���

	}

	if (limitAnimSize <= 0)
	{
		limitAnimSize = 2.0f;
	}

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

	// �ð�޶���
	StageDraw();

	// �����܂�

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "���� %d flag %d hit %d clear %d", landingCheck, landingFlag, hitCheck, clearCheck);
	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "GameOverTime %d", GameOverTime);
	DrawFormatStringF(10, 650, GetColor(255, 255, 255), "landingCnt1 %d", landingCnt[1]);
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

	ClsDrawScreen();


	if (landingCnt[0] < 255 && !landAnimFlag)
	{
		landingCnt[0] += 20;
	}
	if (landingCnt[0] > 0 && landAnimFlag)
	{
		landingCnt[0] -= 20;
	}

	for (auto itr : objList)
	{
		(*landPlayer)->Draw();
		(*landPlayer)->Update();
	}

	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);

	DrawString(0, 0, "GameLanding", 0xffffff);

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		landAnimFlag = true;
	}

	// �����B��������F���֖߂�
	if (landAnimFlag && landingCnt[0] <= 0)
	{
		pltrgPos = VECTOR3(playerPos.x + targetVec.x * 2, playerPos.y);
		(*player)->SetPos(pltrgPos);
		SetScrollPos(targetVec);
		setCount = true;
		landingCheck = false;
		landAnimFlag = false;
		clearCheck = true;						// �ر�\��Ԃɂ���
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
	//�摜�`��
	int Result_X = -100, Result_Y = 0;
	DrawGraph(Result_X, Result_Y, IMAGE_ID("image/result.png"), true);
	//�^�C�g�������`��
	int result_x = 50;
	int result_y = 50;
	//DrawStringToHandle(result_x, result_y, "Result", 0xFFFFFF, Font);
	DrawGraph(result_x, result_y, IMAGE_ID("image/ResultRogo.png"), true);
	//�T�E���h
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// Rocket���Đ����Ȃ�Rocket�̉����~�߂�
	if (CheckSoundMem(Bom) == 1)StopSoundMem(Bom);// Bom���Đ����Ȃ�Bom�̉����~�߂�
	if (CheckSoundMem(Result) == 0)PlaySoundMem(Result, DX_PLAYTYPE_LOOP);//Result���Đ����łȂ���Ή���炷

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
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
		if (CheckSoundMem(Result) == 1)StopSoundMem(Result);	// Result���Đ����Ȃ�Result�̉����~�߂�
		GtskPtr = &GameTask::GameInit;
		if (StageCnt == StageMax)
		{
			UFOFlag = false;
			GtskPtr = &GameTask::GameTitle;
		}
	}
	if (landingCnt[0] < 255)
	{
		landingCnt[0] += 20;
	}

	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);


	DrawString(0, 0, "GameResult", 0xffffff);


	SetFontSize(50);		// ̫�Ă̻���
	SetFontThickness(8);	// ̫�Ă̑���
	ChangeFont("Ailerons");
	DrawString(SCREEN_SIZE_X / 2 - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "GAME CLEAR", 0xffffff);
	SetFontSize(20);		// ̫�Ă̻���
	SetFontThickness(8);	// ̫�Ă̑���
	ChangeFont("MS�S�V�b�N");

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "���� %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);

	ScreenFlip();

	return 0;
}

int GameTask::GameOver(void)
{

	//�T�E���h
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// Rocket���Đ����Ȃ�Rocket�̉����~�߂�
	if (CheckSoundMem(Bom) == 1)StopSoundMem(Bom);// Bom���Đ����Ȃ�Bom�̉����~�߂�
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// Main���Đ����Ȃ�Main�̉����~�߂�
	if (CheckSoundMem(Over) == 0)PlaySoundMem(Over,DX_PLAYTYPE_LOOP);//Over���Đ����łȂ���Ή���炷
	
	
	//PlaySoundMem(Over, DX_PLAYTYPE_LOOP);
	
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
		GtskPtr = &GameTask::GameTitle;
	}
	if (KeyMng::GetInstance().trgKey[P1_SPACE])
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


	DrawString(0, 0, "GameResult", 0xffffff);


	SetFontSize(50);		// ̫�Ă̻���
	SetFontThickness(8);	// ̫�Ă̑���
	ChangeFont("Ailerons");
	DrawString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "GAME OVER", 0xffffff);
	SetFontSize(20);		// ̫�Ă̻���
	SetFontThickness(8);	// ̫�Ă̑���
	ChangeFont("MS�S�V�b�N");

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "���� %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);

	ScreenFlip();

	return 0;
}

int GameTask::GameClear(void)
{
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


