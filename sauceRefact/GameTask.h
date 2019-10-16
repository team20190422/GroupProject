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
	int GameUpdate(void);	//ゲームループメイン

	int SetCount();
	bool HitCheck(RECT rect1, RECT rect2);		// 矩形と矩形の衝突判定
	int count = 0;

	// 着陸判定
	const bool& GetHitCheck(void);
	void SetHitCheck(bool hitCheck);

	// 着陸判定
	const bool& GetLandCheck(void);				
	void SetLandCheck(bool landing);

	// ムービーシーン中カプセルサイズが0以下になったか判定
	const bool & GetCupLandCheck(void);
	void SetCupLandCheck(bool cupLanding);

	// フェードアウト判定
	const bool & GetDarkFlag2(void);
	void SetDarkFlag2(bool dark);

	// プレイヤー燃料残量
	const int& GetEnergy(void);
	void SetEnergy(int energy);

	// スクロール座標
	const VECTOR3& GetScrollPos(void);
	void SetScrollPos(VECTOR3 addPos);

	// プレイヤー座標
	const float& GetPlPosY(void);
	void SetPlPosY(float plPos);

	// 地球座標
	const float& GetErPosY(void);
	void SetErPosY(float ErPos);

	// スクロール座標(Yのみ)
	const float& GetSclPosY(void);
	void SetSclPosY(float sclPos);

	// ムービー中のシーン
	const float& GetScene(void);
	void SetScene(float scene);

	// 着陸モード時のプレイヤーと地面の距離
	const float& GetLdistance(void);
	void SetLdistance(float distance);

	// ムービーシーン中のカプセルのサイズ
	const float& GetCupSize(void);
	void SetCupSize(float capSize);

	// ムービーシーン中の機体セパレート情報
	const bool& GetSpr(void);
	void SetSpr(bool separate);

	// デバッグモード
	const bool& GetDB(void);
	void SetDB(bool debug);

	// 画面のα値
	const float& GetAlpha(void);
	void SetAlpha(float alpha);

	// 目標惑星の座標
	const VECTOR3& GetPlanetPos(void);
	void SetPlanetPos(VECTOR3 plVec);

	// 障害物(隕石)の座標
	const VECTOR3& GetObstPos();
	void SetObstPos(VECTOR3);

	// UIのα値
	const float& GetUIAlpha();
	void SetUIAlpha(float);

	// 小惑星と障害物の衝突判定
	const bool& GetHitObstAst();
	void SetHitObstAst(bool);

	// 小惑星とプレイヤー軌道の衝突判定
	const bool& GetHitOrbAst();
	void SetHitOrbAst(bool);

	// プレイヤー座標
	const VECTOR3& GetPlayerPos();
	void SetPlayerPos(VECTOR3);

	// 小惑星座標
	const VECTOR3& GetAstPos(int);
	void SetAstPos(int ,VECTOR3);

	// 画面揺らし
	const int& GetShake(void);

	// タイトル画面のロケットサイズ
	const float& GetRocketSize(void);

	// フェードアウト用(α値)
	const int& GetLandingCnt(int i);

	// 目標惑星座標
	const VECTOR3& GetPlanetPosition(int i);

	// 目標惑星の座標
	const float& GetPlanetGravity(int i);
	void SetPlanetGravity(int,float);

	// 着陸角度
	const int& GetLandAngle();
	void SetLandAngle(int);

	// 画像情報
	const int& GetSoftImg(int);
	void SetSoftImg(int, int);

	// 現在のステージ数
	const int& GetStageCnt();
	void SetStageCnt(int);

	// 画像のアニメーション番号
	const int& GetAnimNum();
	void SetAnimNum(int);

	// PlanetとPlayerのベクトル計算
	const VECTOR3& GetPlanetToPlayerVectorCalc(VECTOR3,VECTOR3);

	// PlanetとPlayerのベクトル
	const VECTOR3& GetPlanetToPlayerVector(int);
	void SetPlanetToPlayerVector(int, VECTOR3);

	// PlanetとPlayerの距離
	const float& GetPlanetToPlayerDistance(int);
	void SetPlanetToPlayerDistance(int, float);

	// 万有引力計算
	const VECTOR3& GetPlayerUniversalGravirty();
	void SetPlayerUniversalGravirty(VECTOR3);

	// 地球より下で画面外に行った際のフラグ
	const bool& GetOutOfScreenUnderEarth();
	void SetOutOfScreenUnderEarth(bool);

	// 無敵時間フラグ
	const bool& GetMutekiFlag();

	VECTOR3 playerPos;
	float playerAngle;

	// 監視用のAngle
	bool setCount = false;

	float distance = 0.0f;
	float gravity = 0.0f;

	//ﾀｰｹﾞｯﾄ
	VECTOR3 targetPos = { 0,0 };
	VECTOR3 targetVec = { 0,0 };
	float targetDistance = 0.0f;
	float targetSize = 0;

	// ﾌﾟﾚｲﾔｰ
	VECTOR3 playerVec = { 0,0 };
	VECTOR3 planetPos = { 0,0 };
	VECTOR3 PandPvec = { 0,0 };				// playerPosCとplanetPosCのﾍﾞｸﾄﾙ
	VECTOR3 ScrollPos = { 0,0 };			// ｶﾒﾗｽｸﾛｰﾙ
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
	bool landGameCheck = false;				// 着陸時のﾁｪｯｸﾎﾟｲﾝﾄ
	bool landAnimFlag = false;				// 着陸成功判定
	bool setScrPos = false;

	bool tipsFlag = false;

	int StageCnt = 0;
	int planetMax = 0;

private:

	GameTask();
	GameTask(const GameTask&) {}		//コピーコンストラクタのprivate化
	GameTask operator=(const GameTask&) {}	//代入をprivate化
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
	int GameMain(void);				// 宇宙遊泳
	int GameLandInit(void);
	int GameLanding(void);			//着陸
	int GameResult(void);
	int GameOver(void);
	int GameClear(void);

	void Transition();				// 状態遷移表制御
	int Shake();					// 画面揺らし制御


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

	// ﾁｭｰﾄﾘｱﾙ制御
	std::unique_ptr <Tutorial> tuPtr;

	// 万有引力計算
	std::shared_ptr<UnivGravityCalc> univGc;

	std::vector <VECTOR3> planetPosAry;
	std::vector <float> planetGravityAry;
	std::vector <VECTOR3> PtoPVecAry;
	std::vector <float> PtoPDistAry;

	// ｷｰ関係
	int newKey, oldKey , trgKey;
	int Energy = { 0 };
	int time = 0;

	int DieAnim[12] = { 0 };		// 死亡アニメーション格納用
	int OutScrAnim[2][11] = { 0 };	// 画面外時カウントダウン数字画像格納用
	int AnimCnt = 0;				
	int AnimTime = 0;
	int clearCnt = 0;				// 着陸成功時の無敵時間
	int MarsCnt = 0;				// 目標惑星のステージ毎の画像変更用
	int earthAnimCnt = 0;			// 地球アニメーションカウンタ
	int EarthImage[20] = { 0 };		// 地球画像格納
	int bEarthImage[20] = { 0 };	// バッドエンド地球画像格納
	int timeCnt = 0;				// シーンスキップ時使用
	int retryCnt = 10;				// 残機用のｶｳﾝﾄ ｹﾞｰﾑｵｰﾊﾞｰ時に加算
	int shakeWidth = 5;				// 画面揺れ幅
	int planetPosCnt = 0;
	int stageCnt = 0;				// ステージ数格納
	int initMainLandCnt = 0;		// 初期値:0 Init:1 Main:2 Land:3

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
	bool darkFlag2 = false;					// フェードアウトフラグ
	bool pushSpace = false;					// タイトルでスペースが押されたかフラグ
	bool lightFlag = false;					// フェードインフラグ
	bool skipFlag = false;	
	bool launchFlag = false;				// 発射フラグ
	bool psFlag = false;
	bool fireFlag = false;					// 大気圏突入フラグ
	bool hundredFlag = false;				// 大気圏突入サウンドのフェードアウトフラグ
	bool OutScr = false;					// 画面外フラグ
	bool Spr = false;						// ムービー時機体セパレートフラグ
	bool GameOverFlag = false;	
	bool DrawGameOver = false;
	bool debug = false;
	bool shakeFlag = false;
	bool playResultFlag = false;
	bool changeMain = false;
	bool creatorSpaceFlag = false;			// チームロゴ表示フラグ
	bool resultSkip = false;

	// 音楽関係
	// BGM
	int OP, Main, ED1, ED2, LED, Over;	
	// 効果音
	int Start,Decision,Choose,Pause,PauseBack,Cancel, Rocket, Bom, Boost, Emergency, Emergency2, 
		EngineM, EngineLand, Result_rank, Result_rankAll, Cheers, wind, 
		noise, fire, koukaon, Gas, ClearBGM,Clap,Booing;
	// 隠しコマンド関係
	int UFO;
	bool UFOFlag = false;
	bool ufoYflag = false;
	VECTOR3 UFOpos = { 0,450 };
	int ufoTime = 0;

	int GameOverCnt = 0;
	int limitTime = 6;		// 画面外時のカウンタ	
	int cdCount = 0;
	int soundVol = 0;

	int softImg[3] = { 0 };
	int animNum = 0;

	int creatorCount = 0;	// チームロゴ表示時間

	float limitAnimSize = 2.0f;				// 画面外時の数字の大きさ制御
	float earthSize = 5.0f;
	float rocketSize = 0.0f;
	float angle = 0.0f;
	float EarthPos = 0.0f;
	float plPos = 0.0f;
	float EtoP = 0.0f;
	float EtoPtrans = ((-533 / 5) + 700);	// Earth to Planet のミニマップ
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

	// サウンド制御
	struct sound{
		float OP = 70;
		float Rocket = 70;
		float Engine = 100;
		float noise = 50;
		float fire = 0;
	};

	// リザルトランク制御
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

	// 燃料減少時の上下ボックス
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

	// ここまで
	VECTOR3 rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };


	//ゲームオーバー時に使う変数
	float overBright;				//オーバー画面時の画面の明るさ
	int paint_x = 0, paint_y = 0;	//描画するときのずらず値
	int Ppos_x = 210, Ppos_y = 220;	//自機の座標
	int Bpos_x = 150, Bpos_y = 170;	//爆発表示の座標

	int MainTimer = 0;
	int MaxTime = 0;

	int titleBright = 0;
	int titleTime = 0;
	int shake = 0;
	int kouka_shake = 5;

	int resultAnim = 0;
	int resultTime = 0;
	int resultAnimCnt = 200;

	bool pauseFlag = false;					// ﾎﾟｰｽﾞ用ﾌﾗｸﾞ
	int pauseBrightTime = 0;
	bool pauseCheck = false;				// ﾎﾟｰｽﾞ時の処理
	bool retryCheck = false;				// ﾎﾟｰｽﾞ時にﾘﾄﾗｲが押された時の判定

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

	// 全体的な評価
	int all = 0;	// 0:初期値 9:A+ 8:A 7:B+ 6:B 5:C+ 4:C 
	int stageRank1 = 0, stageRank2 = 0, stageRank3 = 0, stageRank4 = 0;
	int sogo = 0;
	int timeEval = 0, sampleEval = 0, CompEval = 0, fuelEval = 0,lifeEval = 0;		 // 0:初期値 3:A 2:B 1:C lifeのみ 0:初期値 6,5:A 4,3:B 2,1:C
	int BackGraundCnt = 0;
	int rankFlag = 0;	// A以上:3 B以上:2 C以上:1 初期値:0
	int score = 0;

	VECTOR3 dirOfTrav = { 0.0f,0.0f };
	VECTOR3 obstPos = { 0.0f,0.0f };
	VECTOR3 playerPosition = { 0.0f,0.0f };
	VECTOR3 universalGravity = { 0.0f,0.0f };

	std::vector<VECTOR3>astPos;
};