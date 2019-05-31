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

// 画面遷移用
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
	GameTask(const GameTask&) {}		//コピーコンストラクタのprivate化
	GameTask operator=(const GameTask&) {}	//代入をprivate化
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
	int GameUpdate(void);	//ゲームループメイン

	int SetCount();
	bool HitCheck(RECT rect1, RECT rect2);
	int count = 0;

	int StageCnt = 0;

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

	const float& GetPlPosY(void);
	void SetPlPosY(float plPos);

	const float& GetErPosY(void);
	void SetErPosY(float ErPos);

	const float& GetSclPosY(void);
	void SetSclPosY(float sclPos);

	const float& GetScene(void);
	void SetScene(float scene);

	const float& GetLdistance(void);
	void SetLdistance(float distance);

	const float& GetCupSize(void);
	void SetCupSize(float capSize);

	const bool& GetSpr(void);
	void SetSpr(bool separate);

	const float& GetRocketSize(void);

	const int& GetLandingCnt(int i);

	VECTOR3 playerPos;
	float playerAngle;

	// 監視用のAngle
	bool setCount = false;

	float distance = 0;
	float gravity = 0.0f;

	//ﾀｰｹﾞｯﾄ
	VECTOR3 targetPos = { 0,0 };
	VECTOR3 targetVec = { 0,0 };
	float targetDistance = 0.0f;
	float targetSize = 0;

	// ﾌﾟﾚｲﾔｰ
	VECTOR3 playerVec = { 0,0 };

	VECTOR3 PandPvec = { 0,0 };			// playerPosCとplanetPosCのﾍﾞｸﾄﾙ
	VECTOR3 ScrollPos = { 0,0 };		// ｶﾒﾗｽｸﾛｰﾙ
	VECTOR3 pltrgPos = { 0,0 };
	VECTOR3 pltrgVec = { 0,0 };
	VECTOR3 pltrgScr = { 0,0 };
	VECTOR3 setplPos = { 0,0 };
	bool OutOfScreen = false;				// ﾌﾟﾚｲﾔｰが画面端から離れた場合のﾌﾗｸﾞ
	bool landingFlag = false;				// ﾌﾟﾚｲﾔｰが着陸成功したら
	bool returnFlag = false;				// ﾌﾟﾚｲﾔｰが地球に帰還成功した時のﾌﾗｸﾞ
	bool getSample = false;					// ﾌﾟﾚｲﾔｰ帰還時に目標の惑星に到達したかのﾌﾗｸﾞ
	bool plPosMaxFlag = false;				// ﾌﾟﾚｲﾔｰのY座標が下側の限界に達したら
	bool clearCheck = false;				// 惑星の着陸に成功したﾌﾗｸﾞ

	bool darkFlag = false;					// 暗転ﾌﾗｸﾞ

	bool landGameCheck = false;
	bool landAnimFlag = false;
	bool setScrPos = false;
private:

	std::list<obj_ptr>::iterator AddObjlist(obj_ptr && objPtr);
	std::list<bp_ptr>::iterator AddBplist(bp_ptr && bpPtr);

	int GameInit(void);
	int GameTitle(void);
	int GameMain(void);				// 宇宙遊泳
	int GameLandInit(void);
	int GameLanding(void);			//着陸
	int GameResult(void);
	int GameOver(void);
	int GameClear(void);

	void Transition();

	int (GameTask::*GtskPtr)(void);

	obj_List objList;
	std::list<obj_ptr>::iterator player;
	std::list<obj_ptr>::iterator landPlayer;
	BackGround* back;
	std::list<obj_ptr>::iterator obstracle;

	// bpListに格納
	bp_List bpList;
	std::list<bp_ptr>::iterator earth;
	std::list<bp_ptr>::iterator mars;
	std::list<bp_ptr>::iterator asteroid;

	title_List particleList;
	std::list<title_ptr>::iterator particle;

	// int
	// ｷｰ関係
	int newKey, oldKey , trgKey;
	int Energy = { 0 };
	int time = 0;

	int DieAnim[12] = { 0 };
	int OutScrAnim[2][11] = { 0 };
	int AnimCnt = 0;
	int AnimTime = 0;
	int checkCnt = 0;
	int clearCnt = 0;				// 着陸成功時の無敵時間
	int MarsCnt = 0;
	int earthAnimCnt = 0;
	int EarthImage[20] = { 0 };
	int lgtsCnt = 0;
	int timeCnt = 0;
	VECTOR3 pos = { 0,0 };

	// ｻﾌﾞﾀｲﾄﾙ
	int subTitleCnt = 0;
	int subTitleAnim = 0;
	bool subTitleFlag = false;
	std::array<int, 3> landingCnt = { 255, 255,255 };


	//ﾌﾟﾚｲﾔｰの当たり判定の管理
	bool hitCheck = false;					// 惑星に着陸せずに衝突したﾌﾗｸﾞ
	bool landingCheck = false;				// 目標の惑星に到達したﾌﾗｸﾞ
	bool cupLandingCheck = false;			// ｶﾌﾟｾﾙのsizeが0になったかﾌﾗｸﾞ

	bool energyAnim = false;
	bool darkFlag2 = false;
	bool pushSpace = false;
	bool lightFlag = false;
	bool skipFlag = false;
	bool launchFlag = false;
	bool psFlag = false;
	bool fireFlag = false;
	bool hundredFlag = false;
	bool OutScr = false;
	bool Spr = false;

	//音楽関係
	int OP, Main, ED1, ED2, LED, Over;	//BGM
	int Decision, Cancel, Rocket, Bom, Boost, Emergency, Emergency2, EngineM, EngineLand,Result_rank, Result_rankAll,Cheers,wind,noise,fire,koukaon,Gas,ClearBGM;
	//隠しコマンド関係
	int UFO;
	bool UFOFlag = false;
	bool ufoYflag = false;
	VECTOR3 UFOpos = { 0,450 };

	// ここから
	int limitTime = 4;
	int cdCount = 0;
	int soundVol = 0;
	float limitAnimSize = 2.0f;
	float earthSize = 5.0f;
	float rocketSize = 0.0f;
	float angle = 0.0f;
	float EarthPos = 0.0f;
	float plPos = 0.0f;
	float EtoP = 0.0f;
	float EtoPtrans = ((-533 / 5) + 700);
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

	struct {
		float OP = 70;
		float Rocket = 70;
		float Engine = 100;
		float noise = 50;
		float fire = 0;
	}soundV;

	struct {
		float time = 0.0f;
		float sample = 0.0f;
		float life = 0.0f;
		float all = 0.0f;
		bool incEnd = false;
		int count = 0;
		int countSave = 0;
	}rankSize;

	struct {
		int count1 = 0;
		int count2 = 0;
		int count3 = 0;
		float L = 20.0f;
		float R1 = 20.0f;
		float R2 = 20.0f;
		float R3 = 20.0f;
		bool end = false;
	}line;

	int GameOverTime = 0;
	int outScreenTime = 0;

	// ここまで
	VECTOR3 rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };


	int titleBright = 0;
	int titleTime = 0;
	int titleShake = 0;

	int MainTimer = 0;
	int MaxTime = 0;

	int resultAnim = 0;
	int resultTime = 0;
	int resultAnimCnt = 200;

	bool pauseFlag = false;					// ﾎﾟｰｽﾞ用ﾌﾗｸﾞ
	int pauseBrightTime = 0;

	int Scene = 0;
	int transBright = 128;
	int colBright = 128;

	int font = 0;

	int soundCnt = 0;
	int sBoostCnt = 0;

	int eSoundFlag = 0;
	int fCnt = 0;
	int kouka_shake = 5;
	int shake = 0;


	// 全体的な評価
	int all = 0;	// 0:初期値 9:A+ 8:A 7:B+ 6:B 5:C+ 4:C 
	int stageRank1 = 0, stageRank2 = 0, stageRank3 = 0;
	int sogo = 0;
	int timeEval = 0, sampleEval = 0, CompEval = 0, fuelEval = 0, lifeEval = 0;		// 0:初期値 3:A 2:B 1:C
	int BackGraundCnt = 0;
};