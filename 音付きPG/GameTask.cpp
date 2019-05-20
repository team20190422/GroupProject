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
	SetWindowText("�X�C���O�o�C");
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
	InitSoundMem();		//�������ɓǂݍ��񂾉��f�[�^�����ׂč폜����

	DrawString(0, 0, "INIT", 0xffff00);
	GtskPtr = &GameTask::GameTitle;
	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey));
	obstracle = AddObjlist(std::make_shared<Obstracle>());
	mars = AddBplist(std::make_shared<Mars>());
	jupiter = AddBplist(std::make_shared<Jupiter>());
	earth = AddBplist(std::make_shared<Earth>());
	(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);
	//�摜�ǂݍ���
	ImageMng::GetInstance().SetID2("Title", "image/title.png");//�^�C�g��
	ImageMng::GetInstance().SetID2("Result", "image/result.png");//���U���g
	//���y�t�@�C���ǂݍ���
	OP = LoadBGM("sound/uchuu-tanken .ogg");
	Main = LoadBGM("sound/�F���̘Ȃ�.ogg");
	End = LoadBGM("sound/�V��.ogg");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// ���k���ꂽ�S�f�[�^�̓V�X�e���������Ɋi�[����A�Đ����镔�����������𓀂��Ȃ���T�E���h�������Ɋi�[����(�炵�I���Ɖ𓀂����f�[�^�͔j�������̂ŉ��x���𓀏������s����)
	Decision = LoadSoundMem("sound/�I����.ogg");
	Rocket = LoadSoundMem("sound/���P�b�g����.ogg");
	Boost = LoadSoundMem("sound/�K�X�o�[�i�[.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	//�B���R�}���h
	UFO = LoadSoundMem("sound/UFO01.ogg");
	UFOBoost = LoadSoundMem("sound/sf_energy2 .ogg");
	UFOFlag = false;//�B���R�}���h�֌W�t���O
	BomFlag = false;//�����t���O

	//�t�H���g
	InitFontToHandle();	//�t�H���g�f�[�^�����ׂč폜����
	Font = CreateFontToHandle("Segoe Print", 40, 3, DX_FONTTYPE_NORMAL);
	back = new BackGround();
	return 0;
}

int GameTask::GameTitle(void)
{
	int Title_X = -500;
	int Title_Y = 0;
	//�摜�`��
	ImageMng::GetInstance().DrawImage("Title", Title_X, Title_Y, true);
	//�^�C�g�������`��
	int title_x = 100;
	int title_y = 100;
	DrawStringToHandle(title_x, title_y, "Swing Bye", 0xFFFFFF, Font);
	//�T�E���h�֌W
	if(CheckSoundMem(OP)== 0)PlaySoundMem(OP, DX_PLAYTYPE_LOOP);
	//�B���R�}���h
	if (KeyMng::GetInstance().newKey[P1_SPACE]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		(*player)->init("image/Player2.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
		DrawString(170, 300, "UFO�o��", GetColor(255, 255, 255));
	}

	//�Q�[�����[�h�ڍs
	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(OP) == 1) {	//Title���Đ����Ȃ�
			DeleteSoundMem(OP);	//�������ɓǂݍ���Title�̉��f�[�^���폜
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
		if (CheckSoundMem(Main) == 1) {	//Main���Đ����Ȃ�
			DeleteSoundMem(Main);	////�������ɓǂݍ���Main�̉��f�[�^���폜
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
		// ���ׂĂ̘f����Update
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
		
		if (KeyMng::GetInstance().newKey[P1_UP]) {//���L�[�������ꂽ�Ƃ�
			 
			if (UFOFlag == true) {//UFOFlag��true�̎�
				//UFO�̉����Đ����łȂ����UFO�̉����Đ�����
				if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);
			}
			else {
				//���P�b�g���˂̉����Đ����łȂ���΃��P�b�g���˂̉����Đ�����
				if (CheckSoundMem(Rocket) == 0)PlaySoundMem(Rocket, DX_PLAYTYPE_LOOP);
			}
		}
		else {	//�����łȂ���Ή����~�߂�
			StopSoundMem(UFO);
			StopSoundMem(Rocket);
		}
		
		if (KeyMng::GetInstance().newKey[P1_SPACE]) {
			if (UFOFlag == true) {//UFOFlag��true�̎�
								  //UFO�̉����Đ����łȂ����UFO�̉����Đ�����
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

		if ((*player)->GetDeathFlag() == true) {	//�v���C���[�����񂾂Ƃ�
			BomFlag = true;
			DeleteSoundMem(Rocket);	//�������ɓǂݍ��񂾃��P�b�g���ˉ��̉��f�[�^���폜
			DeleteSoundMem(UFO);
			DeleteSoundMem(Boost);
			//���������Đ����łȂ���Δ��������Đ�����
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
	//�摜�`��
	int Result_X = -100;
	int Result_Y = 0;
	ImageMng::GetInstance().DrawImage("Result", Result_X, Result_Y, true);
	//�^�C�g�������`��
	int result_x = 150;
	int result_y = 100;
	DrawStringToHandle(result_x, result_y, "Result", 0xFFFFFF, Font);
	//�T�E���h
	if (CheckSoundMem(Rocket) == 1)DeleteSoundMem(Rocket);
	if (CheckSoundMem(Bom) == 1)DeleteSoundMem(Bom);
	if (CheckSoundMem(End) == 0)PlaySoundMem(End, DX_PLAYTYPE_LOOP);

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(End) == 1) {	//Result���Đ����Ȃ�
			DeleteSoundMem(End);	//�������ɓǂݍ���Result�̉��f�[�^���폜
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


