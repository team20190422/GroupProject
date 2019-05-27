#pragma once
#include<vector>
#include<array>
#include<list>
#include<map>
#include "Obj.h"
#include "BasePlanet.h"

//class Player;
//class Stage;
//class Enemy;

#define  lpGameTask GameTask::GetInstance()

// ��ʑJ�ڗp
enum GAME_MODE {
	GAME_INIT,
	GAME_TITLE,
	GAME_MAIN,
	GAME_RESULT
};

typedef std::shared_ptr<Obj> obj_ptr;
typedef std::list<obj_ptr> obj_List;

typedef std::shared_ptr<BasePlanet> bp_ptr;
typedef std::list<bp_ptr> bp_List;

typedef std::shared_ptr<Obj> title_ptr;
typedef std::list<title_ptr> title_List;


constexpr int SCREEN_SIZE_X(450);
constexpr int SCREEN_SIZE_Y(800);
constexpr int DISTANCE_MAX(10000);

class BackGround;
class Player;
class Obstracle;

class GameTask
{
private:
	GameTask();
	GameTask(const GameTask&) {}		//�R�s�[�R���X�g���N�^��private��
	GameTask operator=(const GameTask&) {}	//�����private��
	~GameTask();
	void Die(void);
	static GameTask *s_Instance;
	std::vector<BackGround*>backVec;

public:
	static void Create(void);
	static GameTask &GetInstance(void)
	{
		Create();
		return *s_Instance;
	}

	int SystemInit(void);
	int GameUpdate(void);	//�Q�[�����[�v���C��

	int SetCount();
	bool HitCheck(RECT rect1, RECT rect2);
	int count = 0;

	const bool& GetHitCheck(void);
	void SetHitCheck(bool hitCheck);

	const bool& GetLandCheck(void);
	void SetLandCheck(bool landing);

	const bool & GetCupLandCheck(void);
	void SetCupLandCheck(bool cupLanding);

	const bool & GetDarkFlag2(void);
	void SetDarkFlag2(bool dark);

	const int& GetEnergy(void);
	void SetEnergy(int energy);

	const VECTOR3& GetScrollPos(void);
	void SetScrollPos(VECTOR3 addPos);

	const float& GetRocketSize(void);


	VECTOR3 playerPos;
	float playerAngle;

	// �Ď��p��Angle
	bool setCount = false;

	float distance = 0;
	float gravity = 0.0f;

	//���ޯ�
	VECTOR3 targetPos = { 0,0 };
	VECTOR3 targetVec = { 0,0 };
	float targetDistance = 0.0f;
	float targetSize = 0;

	// ��ڲ԰
	VECTOR3 playerVec = { 0,0 };

	VECTOR3 PandPvec = { 0,0 };			// playerPosC��planetPosC���޸��
	VECTOR3 ScrollPos = { 0,0 };		// ��׽�۰�
	VECTOR3 pltrgPos = { 0,0 };
	bool OutOfScreen = false;				// ��ڲ԰����ʒ[���痣�ꂽ�ꍇ���׸�
	bool landingFlag = false;				// ��ڲ԰����������������
	bool returnFlag = false;				// ��ڲ԰���n���ɋA�Ґ������������׸�
	bool getSample = false;					// ��ڲ԰�A�Ҏ��ɖڕW�̘f���ɓ��B���������׸�
	bool plPosMaxFlag = false;				// ��ڲ԰��Y���W�������̌��E�ɒB������
	bool clearCheck = false;				// �f���̒����ɐ��������׸�

	bool darkFlag = false;					// �Ó]�׸�

private:

	std::list<obj_ptr>::iterator AddObjlist(obj_ptr && objPtr);
	std::list<bp_ptr>::iterator AddBplist(bp_ptr && bpPtr);

	int GameInit(void);
	int GameTitle(void);
	int GameMain(void);				// �F���V�j
	int GameLandInit(void);
	int GameLanding(void);			//����
	int GameResult(void);
	int GameOver(void);
	int GameClear(void);

	int (GameTask::*GtskPtr)(void);

	obj_List objList;
	std::list<obj_ptr>::iterator player;
	std::list<obj_ptr>::iterator landPlayer;
	BackGround* back;
	std::list<obj_ptr>::iterator obstracle;

	// bpList�Ɋi�[
	bp_List bpList;
	std::list<bp_ptr>::iterator earth;
	std::list<bp_ptr>::iterator mars;
	std::list<bp_ptr>::iterator asteroid;

	title_List particleList;
	std::list<title_ptr>::iterator particle;

	// int
	// ���֌W
	int newKey, oldKey , trgKey;
	int Energy = { 0 };
	int time = 0;

	int DieAnim[12] = { 0 };
	int OutScrAnim[11] = { 0 };
	int AnimCnt = 0;
	int AnimTime = 0;
	int checkCnt = 0;
	int clearCnt = 0;				// �����������̖��G����
	int MarsCnt = 0;
	int earthAnimCnt = 0;
	int EarthImage[20] = { 0 };
	int lgtsCnt = 0;
	VECTOR3 pos = { 0,0 };

	// �������
	int subTitleCnt = 0;
	int subTitleAnim = 0;
	bool subTitleFlag = false;
	std::array<int, 3> landingCnt = { 255, 255,255 };


	//��ڲ԰�̓����蔻��̊Ǘ�
	bool hitCheck = false;					// �f���ɒ��������ɏՓ˂����׸�
	bool landingCheck = false;				// �ڕW�̘f���ɓ��B�����׸�
	bool cupLandingCheck = false;			// ��߾ق�size��0�ɂȂ������׸�

	bool energyAnim = false;
	bool landAnimFlag = false;
	bool darkFlag2 = false;
	bool pushSpace = false;
	bool lightFlag = false;

	//���y�֌W
	int OP, Main, ED1, ED2, LED, Over;	//BGM
	int Decision, Cancel, Rocket, Bom, Boost, Emergency, Emergency2;
	//�B���R�}���h�֌W
	int UFO;
	bool UFOFlag = false;


	// ��������
	int limitTime = 4;
	float limitAnimSize = 2.0f;
	float earthSize = 5.0f;
	float rocketSize = 0.0f;
	float angle = 0.0f;

	int GameOverTime = 0;
	int outScreenTime = 0;

	int StageCnt = 0;
	// �����܂�
	VECTOR3 rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };

	int titleBright = 0;
	int titleTime = 0;
	int titleShake = 0;

	int MainTimer = 0;
	int MaxTime = 0;

	int resultAnim = 0;
	int resultTime = 0;
	int resultAnimCnt = 200;

	// �S�̓I�ȕ]��
	char timeEval = 0, sampleEval = 0, CompEval = 0;
	int BackGraundCnt = 0;

};