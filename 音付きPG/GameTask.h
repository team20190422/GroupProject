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

	const int& GetEnergy(void);
	void SetEnergy(int energy);

	const VECTOR3& GetScrollPos(void);
	void SetScrollPos(VECTOR3 addPos);

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

	// ｻﾌﾞﾀｲﾄﾙ
	int subTitleCnt = 0;
	int subTitleAnim = 0;
	bool subTitleFlag = false;
	std::array<int, 3> landingCnt = { 255, 255,255 };


	//ﾌﾟﾚｲﾔｰの当たり判定の管理
	bool hitCheck = false;					// 惑星に着陸せずに衝突したﾌﾗｸﾞ
	bool landingCheck = false;				// 目標の惑星に到達したﾌﾗｸﾞ
	bool clearCheck = false;				// 惑星の着陸に成功したﾌﾗｸﾞ

	bool energyAnim = false;
	bool landAnimFlag = false;

	//音楽関係
	int OP, Main,ED1,ED2,LED,Over;	//BGM
	int Decision, Cancel, Rocket, Bom, Boost,Emergency;
	//隠しコマンド関係
	int UFO,UFOBoost;
	bool UFOFlag = false;
	// ここから
	int limitTime = 4;
	float limitAnimSize = 2.0f;
	int GameOverTime = 0;
	int outScreenTime = 0;
	int StageCnt = 0;
	// ここまで

};