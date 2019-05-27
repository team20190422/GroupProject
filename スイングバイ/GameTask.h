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
	bool OutOfScreen = false;				// ﾌﾟﾚｲﾔｰが画面端から離れた場合のﾌﾗｸﾞ
	bool landingFlag = false;				// ﾌﾟﾚｲﾔｰが着陸成功したら
	bool returnFlag = false;				// ﾌﾟﾚｲﾔｰが地球に帰還成功した時のﾌﾗｸﾞ
	bool getSample = false;					// ﾌﾟﾚｲﾔｰ帰還時に目標の惑星に到達したかのﾌﾗｸﾞ
	bool plPosMaxFlag = false;				// ﾌﾟﾚｲﾔｰのY座標が下側の限界に達したら
	bool clearCheck = false;				// 惑星の着陸に成功したﾌﾗｸﾞ

	bool darkFlag = false;					// 暗転ﾌﾗｸﾞ

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
	int OutScrAnim[11] = { 0 };
	int AnimCnt = 0;
	int AnimTime = 0;
	int checkCnt = 0;
	int clearCnt = 0;				// 着陸成功時の無敵時間
	int MarsCnt = 0;
	int earthAnimCnt = 0;
	int EarthImage[20] = { 0 };
	int lgtsCnt = 0;
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
	bool landAnimFlag = false;
	bool darkFlag2 = false;
	bool pushSpace = false;
	bool lightFlag = false;

	//音楽関係
	int OP, Main, ED1, ED2, LED, Over;	//BGM
	int Decision, Cancel, Rocket, Bom, Boost, Emergency, Emergency2;
	//隠しコマンド関係
	int UFO;
	bool UFOFlag = false;


	// ここから
	int limitTime = 4;
	float limitAnimSize = 2.0f;
	float earthSize = 5.0f;
	float rocketSize = 0.0f;
	float angle = 0.0f;

	int GameOverTime = 0;
	int outScreenTime = 0;

	int StageCnt = 0;
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

	// 全体的な評価
	char timeEval = 0, sampleEval = 0, CompEval = 0;
	int BackGraundCnt = 0;

};