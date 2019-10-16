#pragma once
#include<vector>
#include<array>
#include<list>
#include<map>
#include "Obj.h"
#include "BasePlanet.h"
#include "Tutorial.h"

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
class UnivGravityCalc;

class GameTask : public Obj
{
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
	bool HitCheck(RECT rect1, RECT rect2);		// ��`�Ƌ�`�̏Փ˔���
	int count = 0;

	// ��������
	const bool& GetHitCheck(void);
	void SetHitCheck(bool hitCheck);

	// ��������
	const bool& GetLandCheck(void);				
	void SetLandCheck(bool landing);

	// ���[�r�[�V�[�����J�v�Z���T�C�Y��0�ȉ��ɂȂ���������
	const bool & GetCupLandCheck(void);
	void SetCupLandCheck(bool cupLanding);

	// �t�F�[�h�A�E�g����
	const bool & GetDarkFlag2(void);
	void SetDarkFlag2(bool dark);

	// �v���C���[�R���c��
	const int& GetEnergy(void);
	void SetEnergy(int energy);

	// �X�N���[�����W
	const VECTOR3& GetScrollPos(void);
	void SetScrollPos(VECTOR3 addPos);

	// �v���C���[���W
	const float& GetPlPosY(void);
	void SetPlPosY(float plPos);

	// �n�����W
	const float& GetErPosY(void);
	void SetErPosY(float ErPos);

	// �X�N���[�����W(Y�̂�)
	const float& GetSclPosY(void);
	void SetSclPosY(float sclPos);

	// ���[�r�[���̃V�[��
	const float& GetScene(void);
	void SetScene(float scene);

	// �������[�h���̃v���C���[�ƒn�ʂ̋���
	const float& GetLdistance(void);
	void SetLdistance(float distance);

	// ���[�r�[�V�[�����̃J�v�Z���̃T�C�Y
	const float& GetCupSize(void);
	void SetCupSize(float capSize);

	// ���[�r�[�V�[�����̋@�̃Z�p���[�g���
	const bool& GetSpr(void);
	void SetSpr(bool separate);

	// �f�o�b�O���[�h
	const bool& GetDB(void);
	void SetDB(bool debug);

	// ��ʂ̃��l
	const float& GetAlpha(void);
	void SetAlpha(float alpha);

	// �ڕW�f���̍��W
	const VECTOR3& GetPlanetPos(void);
	void SetPlanetPos(VECTOR3 plVec);

	// ��Q��(覐�)�̍��W
	const VECTOR3& GetObstPos();
	void SetObstPos(VECTOR3);

	// UI�̃��l
	const float& GetUIAlpha();
	void SetUIAlpha(float);

	// ���f���Ə�Q���̏Փ˔���
	const bool& GetHitObstAst();
	void SetHitObstAst(bool);

	// ���f���ƃv���C���[�O���̏Փ˔���
	const bool& GetHitOrbAst();
	void SetHitOrbAst(bool);

	// �v���C���[���W
	const VECTOR3& GetPlayerPos();
	void SetPlayerPos(VECTOR3);

	// ���f�����W
	const VECTOR3& GetAstPos(int);
	void SetAstPos(int ,VECTOR3);

	// ��ʗh�炵
	const int& GetShake(void);

	// �^�C�g����ʂ̃��P�b�g�T�C�Y
	const float& GetRocketSize(void);

	// �t�F�[�h�A�E�g�p(���l)
	const int& GetLandingCnt(int i);

	// �ڕW�f�����W
	const VECTOR3& GetPlanetPosition(int i);

	// �ڕW�f���̍��W
	const float& GetPlanetGravity(int i);
	void SetPlanetGravity(int,float);

	// �����p�x
	const int& GetLandAngle();
	void SetLandAngle(int);

	// �摜���
	const int& GetSoftImg(int);
	void SetSoftImg(int, int);

	// ���݂̃X�e�[�W��
	const int& GetStageCnt();
	void SetStageCnt(int);

	// �摜�̃A�j���[�V�����ԍ�
	const int& GetAnimNum();
	void SetAnimNum(int);

	// Planet��Player�̃x�N�g���v�Z
	const VECTOR3& GetPlanetToPlayerVectorCalc(VECTOR3,VECTOR3);

	// Planet��Player�̃x�N�g��
	const VECTOR3& GetPlanetToPlayerVector(int);
	void SetPlanetToPlayerVector(int, VECTOR3);

	// Planet��Player�̋���
	const float& GetPlanetToPlayerDistance(int);
	void SetPlanetToPlayerDistance(int, float);

	// ���L���͌v�Z
	const VECTOR3& GetPlayerUniversalGravirty();
	void SetPlayerUniversalGravirty(VECTOR3);

	// �n����艺�ŉ�ʊO�ɍs�����ۂ̃t���O
	const bool& GetOutOfScreenUnderEarth();
	void SetOutOfScreenUnderEarth(bool);

	// ���G���ԃt���O
	const bool& GetMutekiFlag();

	VECTOR3 playerPos;
	float playerAngle;

	// �Ď��p��Angle
	bool setCount = false;

	float distance = 0.0f;
	float gravity = 0.0f;

	//���ޯ�
	VECTOR3 targetPos = { 0,0 };
	VECTOR3 targetVec = { 0,0 };
	float targetDistance = 0.0f;
	float targetSize = 0;

	// ��ڲ԰
	VECTOR3 playerVec = { 0,0 };
	VECTOR3 planetPos = { 0,0 };
	VECTOR3 PandPvec = { 0,0 };				// playerPosC��planetPosC���޸��
	VECTOR3 ScrollPos = { 0,0 };			// ��׽�۰�
	VECTOR3 pltrgPos = { 0,0 };
	VECTOR3 pltrgVec = { 0,0 };
	VECTOR3 pltrgScr = { 0,0 };
	VECTOR3 setplPos = { 0,0 };
	bool OutOfScreen = false;				// ��ڲ԰����ʒ[���痣�ꂽ�ꍇ���׸�
	bool landingFlag = false;				// ��ڲ԰����������������
	bool returnFlag = false;				// ��ڲ԰���n���ɋA�Ґ������������׸�
	bool getSample = false;					// ��ڲ԰�A�Ҏ��ɖڕW�̘f���ɓ��B���������׸�
	bool plPosMaxFlag = false;				// ��ڲ԰��Y���W�������̌��E�ɒB������
	bool clearCheck = false;				// �f���̒����ɐ��������׸�

	bool darkFlag = false;					// �Ó]�׸�
	bool landGameCheck = false;				// �������������߲��
	bool landAnimFlag = false;				// ������������
	bool setScrPos = false;

	bool tipsFlag = false;

	int StageCnt = 0;
	int planetMax = 0;

private:

	GameTask();
	GameTask(const GameTask&) {}		//�R�s�[�R���X�g���N�^��private��
	GameTask operator=(const GameTask&) {}	//�����private��
	~GameTask();
	void Die(void);
	static GameTask *s_Instance;
	std::vector<BackGround*>backVec;

	std::list<obj_ptr>::iterator AddObjlist(obj_ptr && objPtr);
	std::list<bp_ptr>::iterator AddBplist(bp_ptr && bpPtr);

	int GameInit(void);
	int GameCreator(void);
	int GameTitle(void);
	int GameTutorial(void);
	int GameMain(void);				// �F���V�j
	int GameLandInit(void);
	int GameLanding(void);			//����
	int GameResult(void);
	int GameOver(void);
	int GameClear(void);

	void Transition();				// ��ԑJ�ڕ\����
	int Shake();					// ��ʗh�炵����


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

	// ����رِ���
	std::unique_ptr <Tutorial> tuPtr;

	// ���L���͌v�Z
	std::shared_ptr<UnivGravityCalc> univGc;

	std::vector <VECTOR3> planetPosAry;
	std::vector <float> planetGravityAry;
	std::vector <VECTOR3> PtoPVecAry;
	std::vector <float> PtoPDistAry;

	// ���֌W
	int newKey, oldKey , trgKey;
	int Energy = { 0 };
	int time = 0;

	int DieAnim[12] = { 0 };		// ���S�A�j���[�V�����i�[�p
	int OutScrAnim[2][11] = { 0 };	// ��ʊO���J�E���g�_�E�������摜�i�[�p
	int AnimCnt = 0;				
	int AnimTime = 0;
	int clearCnt = 0;				// �����������̖��G����
	int MarsCnt = 0;				// �ڕW�f���̃X�e�[�W���̉摜�ύX�p
	int earthAnimCnt = 0;			// �n���A�j���[�V�����J�E���^
	int EarthImage[20] = { 0 };		// �n���摜�i�[
	int bEarthImage[20] = { 0 };	// �o�b�h�G���h�n���摜�i�[
	int timeCnt = 0;				// �V�[���X�L�b�v���g�p
	int retryCnt = 10;				// �c�@�p�̶��� �ްѵ��ް���ɉ��Z
	int shakeWidth = 5;				// ��ʗh�ꕝ
	int planetPosCnt = 0;
	int stageCnt = 0;				// �X�e�[�W���i�[
	int initMainLandCnt = 0;		// �����l:0 Init:1 Main:2 Land:3

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
	bool darkFlag2 = false;					// �t�F�[�h�A�E�g�t���O
	bool pushSpace = false;					// �^�C�g���ŃX�y�[�X�������ꂽ���t���O
	bool lightFlag = false;					// �t�F�[�h�C���t���O
	bool skipFlag = false;	
	bool launchFlag = false;				// ���˃t���O
	bool psFlag = false;
	bool fireFlag = false;					// ��C���˓��t���O
	bool hundredFlag = false;				// ��C���˓��T�E���h�̃t�F�[�h�A�E�g�t���O
	bool OutScr = false;					// ��ʊO�t���O
	bool Spr = false;						// ���[�r�[���@�̃Z�p���[�g�t���O
	bool GameOverFlag = false;	
	bool DrawGameOver = false;
	bool debug = false;
	bool shakeFlag = false;
	bool playResultFlag = false;
	bool changeMain = false;
	bool creatorSpaceFlag = false;			// �`�[�����S�\���t���O
	bool resultSkip = false;

	// ���y�֌W
	// BGM
	int OP, Main, ED1, ED2, LED, Over;	
	// ���ʉ�
	int Start,Decision,Choose,Pause,PauseBack,Cancel, Rocket, Bom, Boost, Emergency, Emergency2, 
		EngineM, EngineLand, Result_rank, Result_rankAll, Cheers, wind, 
		noise, fire, koukaon, Gas, ClearBGM,Clap,Booing;
	// �B���R�}���h�֌W
	int UFO;
	bool UFOFlag = false;
	bool ufoYflag = false;
	VECTOR3 UFOpos = { 0,450 };
	int ufoTime = 0;

	int GameOverCnt = 0;
	int limitTime = 6;		// ��ʊO���̃J�E���^	
	int cdCount = 0;
	int soundVol = 0;

	int softImg[3] = { 0 };
	int animNum = 0;

	int creatorCount = 0;	// �`�[�����S�\������

	float limitAnimSize = 2.0f;				// ��ʊO���̐����̑傫������
	float earthSize = 5.0f;
	float rocketSize = 0.0f;
	float angle = 0.0f;
	float EarthPos = 0.0f;
	float plPos = 0.0f;
	float EtoP = 0.0f;
	float EtoPtrans = ((-533 / 5) + 700);	// Earth to Planet �̃~�j�}�b�v
	float SclPos = 0.0f;
	float landDistance = 0.0f;
	float disTrans = 50.0f;
	float cupSize = 2.0f;
	float alphaJ = 0.0f;
	float alphaM = 0.0f;
	float koukaSize = 0.3f;
	float koukaSave;
	float slideE = 0.0f;
	float slideP = 0.0;
	float alpha = 0.0f;
	float uiAlpha = 255.0f;
	float transAlpha = 255.0f;

	// �T�E���h����
	struct sound{
		float OP = 70;
		float Rocket = 70;
		float Engine = 100;
		float noise = 50;
		float fire = 0;
	};

	// ���U���g�����N����
	struct rankSi{
		float time = 0.0f;
		float sample = 0.0f;
		float life = 0.0f;
		float all = 0.0f;
		float bigSize = 1.5f;
		bool incEnd = false;
		int count = 0;
		int countSave = 0;
	};

	// �R���������̏㉺�{�b�N�X
	struct lin{
		int count1 = 0;
		int count2 = 0;
		int count3 = 0;
		float L = 20.0f;
		float R1 = 20.0f;
		float R2 = 20.0f;
		float R3 = 20.0f;
		bool end = false;
	};

	rankSi rankSize;
	sound soundV;
	lin line;

	int GameOverTime = 0;
	int outScreenTime = 0;

	// �����܂�
	VECTOR3 rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };


	//�Q�[���I�[�o�[���Ɏg���ϐ�
	float overBright;				//�I�[�o�[��ʎ��̉�ʂ̖��邳
	int paint_x = 0, paint_y = 0;	//�`�悷��Ƃ��̂��炸�l
	int Ppos_x = 210, Ppos_y = 220;	//���@�̍��W
	int Bpos_x = 150, Bpos_y = 170;	//�����\���̍��W

	int MainTimer = 0;
	int MaxTime = 0;

	int titleBright = 0;
	int titleTime = 0;
	int shake = 0;
	int kouka_shake = 5;

	int resultAnim = 0;
	int resultTime = 0;
	int resultAnimCnt = 200;

	bool pauseFlag = false;					// �߰�ޗp�׸�
	int pauseBrightTime = 0;
	bool pauseCheck = false;				// �߰�ގ��̏���
	bool retryCheck = false;				// �߰�ގ�����ײ�������ꂽ���̔���

	bool modeFlag = true;

	bool hitObstAst = false;
	bool hitOrbAst = false;

	bool uteFlag = false;		// Under The Earth Flag

	int Scene = 0;
	int transBright = 128;
	int colBright = 128;
	int font = 0;
	int font1 = 0;

	int soundCnt = 0;
	int sBoostCnt = 0;

	int eSoundFlag = 0;
	int fCnt = 0;

	int land = false;

	bool mutekiFlag = false;
	int muteki = 0;

	int blinkCnt = 0;
	int spCnt = 0;
	int titleTransitionCnt = 0;

	// �S�̓I�ȕ]��
	int all = 0;	// 0:�����l 9:A+ 8:A 7:B+ 6:B 5:C+ 4:C 
	int stageRank1 = 0, stageRank2 = 0, stageRank3 = 0, stageRank4 = 0;
	int sogo = 0;
	int timeEval = 0, sampleEval = 0, CompEval = 0, fuelEval = 0,lifeEval = 0;		 // 0:�����l 3:A 2:B 1:C life�̂� 0:�����l 6,5:A 4,3:B 2,1:C
	int BackGraundCnt = 0;
	int rankFlag = 0;	// A�ȏ�:3 B�ȏ�:2 C�ȏ�:1 �����l:0
	int score = 0;

	VECTOR3 dirOfTrav = { 0.0f,0.0f };
	VECTOR3 obstPos = { 0.0f,0.0f };
	VECTOR3 playerPosition = { 0.0f,0.0f };
	VECTOR3 universalGravity = { 0.0f,0.0f };

	std::vector<VECTOR3>astPos;
};