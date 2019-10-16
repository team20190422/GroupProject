#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
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
#include"KeyMng.h"
#include"ImageMng.h"
#include"UnivGravityCalc.h"

constexpr unsigned int SCREEN_CENTER_X = 200;
constexpr unsigned int SCREEN_CENTER_Y = 300;
constexpr unsigned int StageMax = 3;

GameTask *GameTask::s_Instance = nullptr;
int GameTask::GameUpdate(void)
{
	int rtn_id;
	//ÉLÅ[èÓïÒçXêV
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

const VECTOR3 & GameTask::GetPlanetPosition(int i)
{
	return this->planetPosAry[i];
}

const float & GameTask::GetPlanetGravity(int i)
{
	return this->planetGravityAry[i];
}

void GameTask::SetPlanetGravity(int i,float g)
{
	planetGravityAry[i] = g;
}

const int & GameTask::GetLandAngle()
{
	return land;
}

void GameTask::SetLandAngle(int landAngle)
{
	land = landAngle;
}

const int & GameTask::GetSoftImg(int i)
{
	return softImg[i];
}

void GameTask::SetSoftImg(int i, int sImg)
{
	softImg[i] = sImg;
}

const int & GameTask::GetStageCnt()
{
	return stageCnt;
}

void GameTask::SetStageCnt(int sCnt)
{
	stageCnt = sCnt;
}

const int & GameTask::GetAnimNum()
{
	return animNum;
}

void GameTask::SetAnimNum(int anim)
{
	animNum = anim;
}

const VECTOR3& GameTask::GetPlanetToPlayerVectorCalc(VECTOR3 planet, VECTOR3 player)
{
	auto v = planet - player;
	return v;
}

const VECTOR3& GameTask::GetPlanetToPlayerVector(int i)
{
	return PtoPVecAry[i];
}

void GameTask::SetPlanetToPlayerVector(int i, VECTOR3 vec)
{
	PtoPVecAry[i] = vec;
}

const float & GameTask::GetPlanetToPlayerDistance(int i)
{
	return PtoPDistAry[i];
}

void GameTask::SetPlanetToPlayerDistance(int i, float dist)
{
	PtoPDistAry[i] = dist;
}

const VECTOR3 & GameTask::GetPlayerUniversalGravirty()
{
	return universalGravity;
}

void GameTask::SetPlayerUniversalGravirty(VECTOR3 g)
{
	universalGravity = g;
}

const bool & GameTask::GetOutOfScreenUnderEarth()
{
	return uteFlag;
}

void GameTask::SetOutOfScreenUnderEarth(bool i)
{
	uteFlag = i;
}

const bool & GameTask::GetMutekiFlag()
{
	return mutekiFlag;
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

const bool & GameTask::GetDB(void)
{
	return debug;
}

void GameTask::SetDB(bool debug)
{
	this->debug = debug;
}

const float & GameTask::GetAlpha(void)
{
	return alpha;
}

void GameTask::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

const VECTOR3 & GameTask::GetPlanetPos(void)
{
	return planetPos;
}

void GameTask::SetPlanetPos(VECTOR3 plPos)
{
	planetPos = plPos;
}

const VECTOR3 & GameTask::GetObstPos()
{
	return obstPos;
}

void GameTask::SetObstPos(VECTOR3 obstaclePos)
{
	obstPos = obstaclePos;
}

const float& GameTask::GetUIAlpha()
{
	return uiAlpha;
}

void GameTask::SetUIAlpha(float alpha)
{
	uiAlpha = alpha;
}

const bool & GameTask::GetHitObstAst()
{
	return hitObstAst;
}

void GameTask::SetHitObstAst(bool hit)
{
	hitObstAst = hit;
}

const bool & GameTask::GetHitOrbAst()
{
	return hitOrbAst;
}

void GameTask::SetHitOrbAst(bool hit)
{
	hitOrbAst = hit;
}

const VECTOR3 & GameTask::GetPlayerPos()
{
	return playerPosition;
}

void GameTask::SetPlayerPos(VECTOR3 pos)
{
	playerPosition = pos;
}

const VECTOR3 & GameTask::GetAstPos(int i)
{
	return astPos[i];
}

void GameTask::SetAstPos(int i,VECTOR3 ast)
{
	astPos[i] = ast;
}

const int & GameTask::GetShake(void)
{
	return Shake();
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
	if (!s_Instance) 
	{
		s_Instance = new GameTask();
	}
}


int GameTask::SystemInit(void)
{
	SetWindowText("ÉXÉCÉìÉO");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	for (int j = 0; j < 11; j++)
	{
		DieAnim[j] = LoadDivGraph("image/Explosion/îöî≠_ëÂ.png", 11, 11, 1, 115, 100, DieAnim,true);
		OutScrAnim[0][j] = LoadDivGraph("image/Number/count_sushiki.png", 10, 10, 1, 50, 50, OutScrAnim[0], true);
		if (j <= StageMax)
		{
			OutScrAnim[1][j] = LoadDivGraph("image/Number/stageCnt_sushiki.png", 3, 3, 1, 100, 100, OutScrAnim[1], true);
		}
	}
	for (int i = 0; i < EarthMax; i++)
	{
		EarthImage[i] = LoadDivGraph("image/earthAnimNC.png", 20, 20, 1, 100, 50, EarthImage, true);
		bEarthImage[i] = LoadDivGraph("image/earthBEanim.png", 20, 20, 1, 100, 50, bEarthImage, true);
	}

	//âπäyÉtÉ@ÉCÉãì«Ç›çûÇ›
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// à≥èkÇ≥ÇÍÇΩëSÉfÅ[É^ÇÕÉVÉXÉeÉÄÉÅÉÇÉäÇ…äiî[Ç≥ÇÍÅAçƒê∂Ç∑ÇÈïîï™ÇæÇØíÄéüâìÄÇµÇ»Ç™ÇÁÉTÉEÉìÉhÉÅÉÇÉäÇ…äiî[Ç∑ÇÈ(ñ¬ÇÁÇµèIÇÌÇÈÇ∆âìÄÇµÇΩÉfÅ[É^ÇÕîjä¸Ç≥ÇÍÇÈÇÃÇ≈âΩìxÇ‡âìÄèàóùÇ™çsÇÌÇÍÇÈ)

	
	OP = LoadSoundMem("sound/Ç±ÇÃâFíàÇÃÇ«Ç±Ç©Ç≈.ogg");
	Main = LoadSoundMem("sound/êØó±Ç™ç~ÇÈñÈ.mp3");
	ED1 = LoadSoundMem("sound/óVêØ.ogg");
	ED2 = LoadSoundMem("sound/farewell.ogg");
	LED = LoadSoundMem("sound/ê¢äEÇ™ñlíBÇ…óhÇÍÇÈÇ‹Ç≈.ogg");
	Over = LoadSoundMem("sound/âFíàãÛä‘.ogg");
	Result_rank = LoadSoundMem("sound/bomb.mp3");
	Result_rankAll = LoadSoundMem("sound/destruction1.mp3");
	Cheers = LoadSoundMem("sound/people_people-stadium-cheer1.mp3");
	Clap = LoadSoundMem("sound/people_people-stadium-applause1.mp3");
	Booing = LoadSoundMem("sound/booing.wav");
	Start = LoadSoundMem("sound/button81.mp3");
	Decision= LoadSoundMem("sound/button83.mp3");
	Choose = LoadSoundMem("sound/pon.mp3");
	Pause = LoadSoundMem("sound/enter16.mp3");
	PauseBack = LoadSoundMem("sound/cancel7.mp3");
	Rocket = LoadSoundMem("sound/ÉçÉPÉbÉgï¨éÀ.mp3");
	EngineM = LoadSoundMem("sound/îÚçsã@ÅEè¨å^ÉWÉFÉbÉgã@mid.mp3");
	EngineLand = LoadSoundMem("sound/atmosphere4.mp3");
	Boost = LoadSoundMem("sound/ÉoÉbÉNÉuÅ[ÉXÉ^Å[.ogg");
	fire = LoadSoundMem("sound/ÉKÉXÉoÅ[ÉiÅ[.mp3");
	Emergency = LoadSoundMem("sound/åxïÒ.ogg");
	Emergency2 = LoadSoundMem("sound/åxïÒ03.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	UFO = LoadSoundMem("sound/UFO01.ogg");
	wind = LoadSoundMem("sound/ìVåÛÅEçrñÏÇÃïó.mp3");
	noise = LoadSoundMem("sound/çªóíÇÃâπÅEÉeÉåÉrÇÃÉzÉèÉCÉgÉmÉCÉYâπ.mp3");
	koukaon = LoadSoundMem("sound/small_explosion1.mp3");
	Gas = LoadSoundMem("sound/ÉKÉXÇ™òRÇÍÇÈâπloop.mp3");
	ClearBGM = LoadSoundMem("sound/uchuu-hachimoku.mp3");

	GtskPtr = &GameTask::GameCreator;
	return 0;
}


int GameTask::GameInit(void)
{
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
		koukaSave = 0;
		koukaSize = 0.3f;
		alphaJ = 0.0f;
		alphaM = 0.0f;
		titleTime = 0;

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
		launchFlag = false;
		shakeFlag = false;
		pushSpace = false;
		resultSkip = false;

		targetPos = { 0,0 };
		targetVec = { 0,0 };
		targetDistance = 0.0f;
		targetSize = 0;

		playerVec = { 0,0 };
		planetPos = { 0,0 };
		PandPvec = { 0,0 };			// playerPosCÇ∆planetPosCÇÃÕﬁ∏ƒŸ
		ScrollPos = { 0,0 };		// ∂“◊Ω∏€∞Ÿ
		pltrgPos = { 0,0 };
		pltrgVec = { 0,0 };
		pltrgScr = { 0,0 };
		setplPos = { 0,0 };
		OutOfScreen = false;				// Ãﬂ⁄≤‘∞Ç™âÊñ í[Ç©ÇÁó£ÇÍÇΩèÍçáÇÃÃ◊∏ﬁ
		plPosMaxFlag = false;				// Ãﬂ⁄≤‘∞ÇÃYç¿ïWÇ™â∫ë§ÇÃå¿äEÇ…íBÇµÇΩÇÁ

		darkFlag = false;					// à√ì]Ã◊∏ﬁ
		landGameCheck = false;				// íÖó§éûÇÃ¡™Ø∏Œﬂ≤›ƒ
		landAnimFlag = false;				// íÖó§ê¨å˜îªíË
		setScrPos = false;
		planetMax = 0;

		Energy = { 0 };
		AnimTime = 0;
		earthAnimCnt = 0;
		timeCnt = 0;
		planetPosCnt = 0;
		initMainLandCnt = 0;

		hitCheck = false;					// òfêØÇ…íÖó§ÇπÇ∏Ç…è’ìÀÇµÇΩÃ◊∏ﬁ
		cupLandingCheck = false;			// ∂ÃﬂæŸÇÃsizeÇ™0Ç…Ç»Ç¡ÇΩÇ©Ã◊∏ﬁ

		energyAnim = false;
		darkFlag2 = false;
		lightFlag = false;
		skipFlag = false;
		Spr = false;
		GameOverFlag = false;
		DrawGameOver = false;
		debug = false;
		playResultFlag = false;
		changeMain = false;
		creatorSpaceFlag = false;

		UFOpos = { 0,450 };
		ufoTime = 0;
		GameOverCnt = 0;
		cdCount = 0;
		soundVol = 0;
		animNum = 0;
		creatorCount = 0;

		earthSize = 5.0f;
		rocketSize = 0.0f;
		angle = 0.0f;
		EarthPos = 0.0f;
		SclPos = 0.0f;
		landDistance = 0.0f;
		cupSize = 2.0f;
		slideE = 0.0f;
		slideP = 0.0;
		alpha = 0.0f;
		uiAlpha = 255.0f;
		transAlpha = 255.0f;

		soundV.OP = 70;
		soundV.Rocket = 70;
		soundV.Engine = 100;
		soundV.noise = 50;
		soundV.fire = 0;

		rankSize.time = 0.0f;
		rankSize.sample = 0.0f;
		rankSize.life = 0.0f;
		rankSize.all = 0.0f;
		rankSize.bigSize = 1.5f;
		rankSize.incEnd = false;
		rankSize.count = 0;
		rankSize.countSave = 0;

		line.count1 = 0;
		line.count2 = 0;
		line.count3 = 0;
		line.L = 20.0f;
		line.R1 = 20.0f;
		line.R2 = 20.0f;
		line.R3 = 20.0f;
		line.end = false;

		paint_x = 0, paint_y = 0;
		Ppos_x = 210, Ppos_y = 220;
		Bpos_x = 150, Bpos_y = 170;

		MainTimer = 0;
		MaxTime = 0;

		titleBright = 0;
		kouka_shake = 5;

		resultAnim = 0;

		pauseFlag = false;
		pauseBrightTime = 0;
		pauseCheck = false;
		retryCheck = false;

		hitObstAst = false;
		hitOrbAst = false;

		uteFlag = false;

		Scene = 0;
		transBright = 128;
		colBright = 128;

		soundCnt = 0;
		sBoostCnt = 0;

		eSoundFlag = 0;
		fCnt = 0;

		land = false;

		mutekiFlag = false;
		muteki = 0;

		blinkCnt = 0;

		all = 0;
		stageRank1 = 0, stageRank2 = 0, stageRank3 = 0, stageRank4 = 0;
		sogo = 0;
		timeEval = 0, sampleEval = 0, CompEval = 0, fuelEval = 0, lifeEval = 0;
		BackGraundCnt = 0;
		rankFlag = 0;
		score = 0;

		dirOfTrav = { 0.0f,0.0f };
		obstPos = { 0.0f,0.0f };
		playerPosition = { 0.0f,0.0f };
		universalGravity = { 0.0f,0.0f };

		SetAlpha(0.0f);

		tuPtr.reset();
	};

	objList.clear();
	bpList.clear();
	tSetPos.clear();

	reset();

	univGc = std::make_shared<UnivGravityCalc>();

	for (auto i : targetSet)
	{ 
		i += VECTOR3(1, 0);
	}
	DrawString(0, 0, "INIT", 0xffff00);

	player = AddObjlist(std::make_shared<Player>(lpKeyMng.trgKey,lpKeyMng.oldKey,*univGc));
	obstracle = AddObjlist(std::make_shared<Obstracle>());
		
	int AsteroidCnt = 0;
	for (auto planet : stageSet[StageCnt])
	{
		AsteroidCnt++;
		asteroid = AddBplist(std::make_shared<Asteroid>(planet, AsteroidCnt, *univGc));
	}

	earth = AddBplist(std::make_shared<Earth>(VECTOR3(225, SCREEN_SIZE_Y * 1.5f), *univGc));

	for (auto targetPlanet : targetSet)
	{
		if (targetPlanet == targetSet[StageCnt])
		{
			MarsCnt++;
			mars = AddBplist(std::make_shared<Mars>(targetPlanet, MarsCnt, *univGc));
		}
	}
	MarsCnt++;
	astPos.resize(AsteroidCnt + MarsCnt);
	MarsCnt--;
	

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

	if (modeFlag)
	{
		GtskPtr = &GameTask::GameTutorial;
	}
	else
	{
		GtskPtr = &GameTask::GameMain;
	}
	planetGravityAry.resize(bpList.size());
	return 0;
}

int GameTask::GameCreator(void)
{
	creatorCount++;
	if (creatorCount > 150)
	{
		creatorSpaceFlag = true;
	}

	if (creatorSpaceFlag)
	{
		if (titleBright > 0)
		{
			titleBright -= 3;
			SetDrawBright(titleBright, titleBright, titleBright);
		}
		else
		{
			GtskPtr = &GameTask::GameTitle;
		}
	}
	else
	{
		if (titleBright < 255)
		{
			titleBright += 3;
			SetDrawBright(titleBright, titleBright, titleBright);
		}
	}

	//SetDrawBright(255, 255, 255);
	//DrawString(SCREEN_SIZE_Y / 2 - 225, SCREEN_SIZE_Y / 2 - 120, "Created by", 0xffffff);
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.0, 0, IMAGE_ID("image/createdbyNasu.png"), true);
	ScreenFlip();
	return 0;
}

int GameTask::GameTitle(void)
{
	modeFlag = true;
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

	retryCnt = 10;
	SetStageCnt(0);
	StageCnt = 0;
	MarsCnt = 0;
	pauseFlag = false;
	pauseCheck = false;

	if(KeyMng::GetInstance().trgKey[P1_LCtrl] && KeyMng::GetInstance().trgKey[P1_PAUSE])

	//ÉTÉEÉìÉhä÷åW
	ChangeVolumeSoundMem(255 * 70 / 100, OP);//OPÇÃâπÇÃÉ{ÉäÉÖÅ[ÉÄÇ70%Ç…ê›íË
	if (!CheckSoundMem(OP))
	{
		PlaySoundMem(OP, DX_PLAYTYPE_LOOP);
	}

																  //âBÇµÉRÉ}ÉìÉh
	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}

	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/landBG.png"), true);

	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 1, angle+=0.005f, ImageMng::GetInstance().SetID("image/LGTS.png"), true);

	// ¿≤ƒŸâÊñ 
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - 100, earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		int ufo_x = 25, ufo_y = 200;
		DrawGraph(ufo_x, ufo_y, IMAGE_ID("image/UFOèoåª.png"), true);
	}

	//ÉQÅ[ÉÄÉÇÅ[Éhà⁄çs
	if (!launchFlag && !shakeFlag)
	{
		if (KeyMng::GetInstance().trgKey[P1_SPACE])
		{
			PlaySoundMem(Start, DX_PLAYTYPE_BACK);
			PlaySoundMem(Rocket, DX_PLAYTYPE_BACK);
			launchFlag = true;
			shakeFlag = true;
		}
	}

	if (shakeFlag)
	{
		DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
		DrawRotaGraphF(SCREEN_SIZE_X / 2, (SCREEN_SIZE_Y - 100) + Shake(), earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);
	}

	// Ã™∞ƒﬁ
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

	// êUìÆ
	if (shakeFlag)
	{
		titleTime++;
		if (titleTime % 100 == 0)
		{
			pushSpace = true;
		}

		timeCnt++;
		// º∞›Ω∑ØÃﬂ
		if (timeCnt > 1)
		{
			if (KeyMng::GetInstance().trgKey[P1_SPACE])
			{
				skipFlag = true;
			}
		}
		
		blinkCnt++;
		if (blinkCnt / 60 % 2 == 0)
		{
			DrawRotaGraph(SCREEN_SIZE_X - 100, SCREEN_SIZE_Y - 15,1.0,0, IMAGE_ID("image/spaceSkip.png"),true);
		}
	}

	if (pushSpace)
	{
		shakeWidth = 5;

		if (!UFOFlag)
		{
			//  ﬂ∞√®∏ŸçÏê¨
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

			//  ﬂ∞√®∏ŸÇÃçÌèú
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
			// €πØƒï`âÊ
			DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/rocket.png"), true);
		}
		else
		{
			ufoTime++;
			UFOpos.x += 2;

			// ufoï`âÊ
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

				skipFlag = false;
				timeCnt = 0;
				GtskPtr = &GameTask::GameInit;
			}

			if (landingCnt[0] <= 0)
			{
				StopSoundMem(Start);
				StopSoundMem(Rocket);
			}
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	ScreenFlip();
	return 0;
}

int GameTask::GameTutorial(void)
{
	ClsDrawScreen();
	if (!tuPtr)
	{
		tuPtr = std::make_unique<Tutorial>();
	}
	tuPtr->Update();
	tuPtr->Draw();

	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		if (tipsFlag)
		{
			changeMain = true;
		}
		if (CheckSoundMem(OP) == 1) StopSoundMem(OP);//TitleÇ™çƒê∂íÜÇ»ÇÁTitleÇé~ÇﬂÇÈ
		tipsFlag = true;
	}
	
	if(!changeMain)
	{
		if (landingCnt[0] > 255)
		{
			landingCnt[0] = 255;
		}
		else
		{
			landingCnt[0] += 5;
		}
	}
	else
	{
		landingCnt[0] -= 5;
		if (landingCnt[0] < 0)
		{
			landingCnt[0] = 0;
			changeMain = false;
			tipsFlag = false;
			GtskPtr = &GameTask::GameMain;
		}
	}

	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	ScreenFlip();
	return 0;
}

// âFíàóVâj
int GameTask::GameMain(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ClsDrawScreen();

	// Œﬂ∞Ωﬁóp
	if (CheckSoundMem(OP)) {
		StopSoundMem(OP);
	}
	if (KeyMng::GetInstance().trgKey[P1_PAUSE] && !GetHitCheck())
	{
		if (pauseFlag)
		{
			ChangeVolumeSoundMem(255 * 80 / 100, PauseBack);
			PlaySoundMem(PauseBack, DX_PLAYTYPE_BACK);
			pauseFlag = false;
			pauseCheck = false;
		}
		else
		{
			ChangeVolumeSoundMem(255 * 80 / 100, Pause);
			PlaySoundMem(Pause, DX_PLAYTYPE_BACK);
			pauseFlag = true;
			pauseBrightTime = 0;
		}
	}

	if (mutekiFlag)
	{
		muteki++;
		if (muteki < 60)
		{
			mutekiFlag == false;
		}
	}

	if (!pauseFlag)
	{
		// ¥›√ﬁ®›∏ﬁéûÇÃï™äÚópÇÃ¿≤—åvë™
		MainTimer++;
	}
	else
	{
		// Œﬂ∞ΩﬁéûÇÃèàóù
		if (retryCnt > 0)
		{
			if (KeyMng::GetInstance().trgKey[P1_UP] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0)
			{
				if (pauseCheck)
				{
					pauseCheck = false;
				}
				PlaySoundMem(Choose, DX_PLAYTYPE_BACK);
			}
			else if (KeyMng::GetInstance().trgKey[P1_DOWN])
			{
				if (!pauseCheck)
				{
					pauseCheck = true;
				}
				PlaySoundMem(Choose, DX_PLAYTYPE_BACK);
			}
		}
		else
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

		// ÿƒ◊≤or¿≤ƒŸ
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
			if (CheckSoundMem(Main))
			{
				StopSoundMem(Main);// MainÇ™çƒê∂íÜÇ»ÇÁMainÇÃâπÇé~ÇﬂÇÈ
			}
															// îwåiÇÃçÌèú
 			std::vector<BackGround*>::iterator itrBG = backVec.begin();

			titleBright = 0;
			rocketSize = 0.0f;
			rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };
			lightFlag = false;
			pushSpace = false;
			UFOFlag = false;
			GameOverFlag = false;
			DrawGameOver = false;
			OutScr = false;
			launchFlag = false;
			shakeFlag = false;
			pushSpace = false;
			shake = 0.0f;
			shakeWidth = 5;
			overBright = 255;
			titleTime = 0;
			retryCnt = 10;

			modeFlag = true;
			PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
			if (!CheckSoundMem(OP))
			{
				GtskPtr = &GameTask::GameTitle;
			}
		}
		if (KeyMng::GetInstance().trgKey[P1_SPACE] && !pauseCheck)
		{
			PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
			if (!CheckSoundMem(OP))
			{
				AnimCnt = 0;
				AnimTime = 0;
				retryCnt--;
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

				modeFlag = false;
				if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// OverÇ™çƒê∂íÜÇ»ÇÁOverÇÃâπÇé~ÇﬂÇÈ
			}
		}
	}

	if (GtskPtr == &GameTask::GameMain)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, Main);//OPÇÃâπÇÃÉ{ÉäÉÖÅ[ÉÄÇ70%Ç…ê›íË
		if (CheckSoundMem(Main) == 0)PlaySoundMem(Main, DX_PLAYTYPE_LOOP);//MainÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
	}
																	  //ÉTÉEÉìÉhä÷åW
	if (KeyMng::GetInstance().newKey[P1_UP] && !pauseFlag) //Å™ÉLÅ[Ç™âüÇ≥ÇÍÇΩÇ∆Ç´
	{
		if (UFOFlag == true)
		{
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFOÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
		else
		{
			eSoundFlag = 1;
			//ÉçÉPÉbÉgï¨éÀÇÃâπÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒÉçÉPÉbÉgï¨éÀÇÃâπÇçƒê∂Ç∑ÇÈ
			ChangeVolumeSoundMem(255 * 60 / 100, EngineM);
			if (CheckSoundMem(EngineM) == 0)PlaySoundMem(EngineM, DX_PLAYTYPE_LOOP);//UFOÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
	}
	else
	{	//ÇªÇ§Ç≈Ç»ÇØÇÍÇŒâπÇé~ÇﬂÇÈ
		StopSoundMem(UFO);//UFOâπÇé~ÇﬂÇÈ
		StopSoundMem(EngineM);//RocketâπÇé~ÇﬂÇÈ
		StopSoundMem(Rocket);//RocketâπÇé~ÇﬂÇÈ
		if (soundVol <= 100)
		{
			soundVol++;
		}
	}
	if (KeyMng::GetInstance().newKey[P1_RIGHT] || KeyMng::GetInstance().newKey[P1_LEFT])
	{
		if (UFOFlag == true)
		{
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFOÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
		else
		{
			eSoundFlag = 1;
			//ÉçÉPÉbÉgï¨éÀÇÃâπÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒÉçÉPÉbÉgï¨éÀÇÃâπÇçƒê∂Ç∑ÇÈ
			ChangeVolumeSoundMem(255 * 30 / 100, Gas);
			if (CheckSoundMem(Gas) == 0)PlaySoundMem(Gas, DX_PLAYTYPE_LOOP);//UFOÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
	}
	else
	{	//ÇªÇ§Ç≈Ç»ÇØÇÍÇŒâπÇé~ÇﬂÇÈ
		StopSoundMem(UFO);//UFOâπÇé~ÇﬂÇÈ
		StopSoundMem(Rocket);//RocketâπÇé~ÇﬂÇÈ
		StopSoundMem(Gas);//RocketâπÇé~ÇﬂÇÈ
		if (soundVol <= 100)
		{
			soundVol++;
		}
	}

	if (KeyMng::GetInstance().oldKey[P1_UP] && !pauseFlag)
	{
		soundV.Engine--;
	}
	else
	{
		soundV.Engine = 100;
	}

	if (KeyMng::GetInstance().trgKey[P1_SPACE]) 
	{
		if (!pauseFlag)
		{
			ChangeVolumeSoundMem(255 * 60 / 100, Boost);
			PlaySoundMem(Boost, DX_PLAYTYPE_BACK);//BoostÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
	}


	// Ç±Ç±Ç©ÇÁ
	auto StageDraw = [&] 
	{
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
	};

	auto GameOver = [&] 
	{
		if (GetHitCheck())
		{
			if (landingCnt[0] > 0)
			{
				landingCnt[0] -= 15;
				return true;
			}
			else
			{
				if (GetOutOfScreenUnderEarth())
				{
					SetHitCheck(false);
				}
				GtskPtr = &GameTask::GameOver;
				return true;
			}
		}
		
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);

		return false;
	};

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

	planetPosCnt = 0;

	planetMax = bpList.size();

	planetPosAry.resize(bpList.size());

	PtoPVecAry.resize(planetMax);
	PtoPDistAry.resize(planetMax);

	for (auto itr : bpList)
	{
		// Ç∑Ç◊ÇƒÇÃòfêØÇÃUpdate
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
		if (planetPosCnt < bpList.size())
		{
			planetPosAry[planetPosCnt] = itr->GetPos();
			planetPosCnt++;
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
				DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
				StopSoundMem(UFO);		//UFOâπÇé~ÇﬂÇÈ
				StopSoundMem(Rocket);	//RocketâπÇé~ÇﬂÇÈ
				StopSoundMem(Boost);	//BoostâπÇé~ÇﬂÇÈ
				if (CheckSoundMem(Bom) == 0)
				{
					ChangeVolumeSoundMem(255 * 70 / 100, Bom);
					PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//îöî≠âπÇ™ñ¬Ç¡ÇƒÇ¢ÇÈÇ©í≤Ç◊ÇƒÇ»Ç¡ÇƒÇ¢Ç»Ç©Ç¡ÇΩÇÁñ¬ÇÁÇ∑
				}
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
	// îwåiÇÃçÌèú
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


	// –∆œØÃﬂÇÃï`âÊ
	Transition();

	//ãÈå`ÇÃìñÇΩÇËîªíË
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) 
	{
		hitCheck = true;
		if (GetLandCheck()) 
		{
			hitCheck = false;
		}
	}

	if (hitCheck == true) //ÉvÉåÉCÉÑÅ[Ç™éÄÇÒÇæÇ∆Ç´
	{	
		StopSoundMem(UFO);		//UFOâπÇé~ÇﬂÇÈ
		StopSoundMem(Rocket);	//RocketâπÇé~ÇﬂÇÈ
		StopSoundMem(Boost);	//BoostâπÇé~ÇﬂÇÈ
								//âπÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒîöî≠âπÇçƒê∂Ç∑ÇÈ
		if (AnimTime++ % 10 == 0)
		{
			AnimCnt++;
		}
		DrawRotaGraph((int)playerPos.x, (int)playerPos.y, 1.0, 0, DieAnim[AnimCnt], true);
		if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//BomÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		if (AnimCnt >= 11)
		{
			GameOver();
		}
	}
	else 
	{
		StopSoundMem(Bom);	//BomâπÇé~ÇﬂÇÈ
	}


	// íÖó§ê¨å˜éû
	if (landingCheck && landingFlag)
	{
		(*player)->SetVec(VECTOR3(0, 0));
		(*player)->SetAccel(VECTOR3(0, 0));

		if (landingCnt[0] > 0)
		{
			landingCnt[0] -= 25;
		}
		else
		{
			setScrPos = false;
			if (landingCheck && landingFlag && !clearCheck)
			{
				// íÖó§Ç…à⁄çs
				setScrPos = true;
				setplPos = (*player)->GetplPos();
				
				GtskPtr = &GameTask::GameLandInit;
			}
		}

		if (landingCnt[0] <= 100)
		{
			// –ØºÆ›∏ÿ±
			if (returnFlag && clearCheck && landingCheck && landingFlag)
			{
				auto SaveGameMain = SaveDrawScreenToPNG(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, "image/Screen/screen.png", 0);
				resultAnim = LoadGraph("image/Screen/screen.png");

				// –ØºÆ›∏ÿ±
				GtskPtr = &GameTask::GameResult;
			}
		}
		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	else
	{
		if (landingCnt[0] < 255 && !GetHitCheck())
		{
			landingCnt[0] += 20;
		}

		SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0.9, 0, ImageMng::GetInstance().SetID("image/éüÇ÷.png"), true);
	DrawRotaGraph(SCREEN_SIZE_X / 2, 0, 0.9, 0, ImageMng::GetInstance().SetID("image/éüÇ÷.png"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// Ç±Ç±Ç©ÇÁ
	// é©ã@ÇÃâÊñ äOéû
	if (OutOfScreen && !pauseFlag)
	{
		SetDrawBright(landingCnt[1] + 50, landingCnt[1] + 50, landingCnt[1] + 50);
		soundV.noise -= 0.02f;
		if (soundV.noise < 0)
		{
			soundV.noise = 0;
		}
		ChangeVolumeSoundMem(255 * soundV.noise / 100, noise);
		if (CheckSoundMem(noise) == 0)
		{
			PlaySoundMem(noise, DX_PLAYTYPE_LOOP);
		}
		StopSoundMem(noise);

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

	// îRóøè≠ó éû
	if (Energy > 0 && Energy < 20 && !(landingCheck && landingFlag) && !pauseFlag)
	{
		if (landingCnt[1] > 0 && !energyAnim)
		{
			PlaySoundMem(Emergency, DX_PLAYTYPE_BACK);
		}
		else
		{
			energyAnim = true;
		}

		if (landingCnt[1] < 200 && energyAnim)
		{
			
		}
		else
		{
			energyAnim = false;
		}
		SetDrawBright(250, landingCnt[1], landingCnt[1]);
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

	if (clearCheck)
	{
		clearCnt++;
	}
	if (AnimCnt >= 10)
	{
		AnimCnt = 10;
	}

	// íÖó§ê¨å˜éûÇÃëΩè≠ÇÃñ≥ìGéûä‘
	if (clearCheck && (landingCheck || landingFlag))
	{
		if (clearCnt < 60)
		{
			SetHitCheck(false);
		}
		
	}

	if (OutOfScreen && !pauseFlag)
	{
		limitAnimSize -= 0.033f;
		if(limitTime <= 0)
		SetDrawBright(255, 255, 255);
		if (limitTime >= 1)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, limitAnimSize, 0, OutScrAnim[0][limitTime], true);
		}
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		if (limitTime <= 0)
		{
			if (landingCnt[1] > 0)
			{
				landingCnt[1] -= 10;
			}
			else
			{
				ClsDrawScreen();
				StopSoundMem(noise);
				GtskPtr = &GameTask::GameOver;
				GameOverTime = 0;
			}
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		}
	}

	if (limitAnimSize <= 0)
	{
		limitAnimSize = 2.0f;
	}

	

	// Ω√∞ºﬁ∂≥›ƒ
	if (!getSample && !pauseFlag)
	{
		StageDraw();
	}

	// Œﬂ∞ΩﬁéûÇÃï`âÊ
	if (pauseFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, pauseBrightTime * 2);

		SetDrawBright(100 + pauseBrightTime, 100 + pauseBrightTime,100 + pauseBrightTime);
		DrawRotaGraph(SCREEN_CENTER_X + 25, 50, 1.5, 0, IMAGE_ID("image/pause/pause.png"), true);

		if (pauseCheck)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2, 570, 1, 0, IMAGE_ID("image/pause/XboxPause.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 275, 1.1, 0, IMAGE_ID("image/pause/titleback.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 275, 0.8, 0, IMAGE_ID("image/pause/ëIë.png"), true);
			SetDrawBright(255 - pauseBrightTime, 255 - pauseBrightTime, 255 - pauseBrightTime);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 175, 1.0, 0, IMAGE_ID("image/pause/retry.png"), true);
			for (int i = 0; i < retryCnt; i++)
			{
				if (i >= 5)
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + (i - 5) * 40, 175 + 40, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
				else
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + i * 40, 175 - 20, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
			}
		}
		else
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2, 570, 1, 0, IMAGE_ID("image/pause/XboxPause.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 175, 1.1, 0, IMAGE_ID("image/pause/retry.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 175, 0.8, 0, IMAGE_ID("image/pause/ëIë.png"), true);
			for (int i = 0; i < retryCnt; i++)
			{
				if (i >= 5)
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + (i - 5) * 40, 175 + 40, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
				else
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + i * 40, 175 - 20, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
			}
			SetDrawBright(255 - pauseBrightTime, 255 - pauseBrightTime, 255 - pauseBrightTime);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 275, 1.0, 0, IMAGE_ID("image/pause/titleback.png"), true);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
 	StopSoundMem(Emergency);//EmergencyâπÇé~ÇﬂÇÈ

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


	// –∆œØÃﬂÇÃï`âÊ
	Transition();

	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);

	int a = GetLandCheck();
	int b = GetCupLandCheck();
	int c = darkFlag;

	if (GetSpr())
	{
		if (KeyMng::GetInstance().newKey[P1_UP])
		{
			ChangeVolumeSoundMem(255 * 100 / 100, EngineLand);
			if (CheckSoundMem(EngineLand) == 0)
				PlaySoundMem(EngineLand, DX_PLAYTYPE_LOOP);//EngineÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
		else
		{
			StopSoundMem(EngineLand);
		}

		if (KeyMng::GetInstance().newKey[P1_RIGHT] || KeyMng::GetInstance().newKey[P1_LEFT])
		{
			if (CheckSoundMem(Gas) == 0)
				PlaySoundMem(Gas, DX_PLAYTYPE_LOOP);//EngineÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
		else
		{
			StopSoundMem(Gas);
		}
	}

	// èåèíBê¨ÇµÇΩÇÁâFíàÇ÷ñﬂÇÈ
	if (landAnimFlag)
	{
		auto tVec = Obj::Normalized(targetVec);
		pltrgPos = VECTOR3(playerPos.x + targetVec.x*2, playerPos.y);
		(*player)->SetPos(VECTOR3(pltrgPos.x,333));
		(*player)->SetVec(tVec);
		targetVec.y = 0.0f;
		SetScrollPos(-targetVec);
		pltrgVec = targetVec;
		getSample = true;
		setCount = true;
		landingCheck = false;
		landAnimFlag = false;
		landingFlag = true;
		clearCheck = true;						// ∏ÿ±â¬î\èÛë‘Ç…Ç∑ÇÈ
		darkFlag = false;
		darkFlag2 = false;
		pushSpace = false;
		lightFlag = false;
		cupLandingCheck = false;			// ∂ÃﬂæŸÇÃsizeÇ™0Ç…Ç»Ç¡ÇΩÇ©Ã◊∏ﬁ
		mutekiFlag = true;
		landingCnt[1] = 0;
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		if (objList.size() > 0)
		{
			objList.pop_back();
		}
		GtskPtr = &GameTask::GameMain;
	}

	// îöî≠ÇµÇΩÇÁπﬁ∞—µ∞ ﬁ∞
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

		if (getSample)
		{
			// ¿≤—ï]âø
			if (MainTimer <= 4000)
			{
				timeEval = 3;
			}
			else if (MainTimer <= 2000)
			{
				timeEval = 2;
			}
			else
			{
				timeEval = 1;
			}

			// îRóøécï]âø
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

			// écã@ï]âø
			lifeEval = ((retryCnt >= 8 || retryCnt <= 10) ? 3 : (retryCnt >= 4 || retryCnt <= 7) ? 2 : (retryCnt >= 1 || retryCnt <= 3) ? 1 : 0);
		}
		else
		{
			timeEval = 0;
			fuelEval = 0;
			lifeEval = 0;
		}

		// ëççá
		all = timeEval + fuelEval + lifeEval;

		if (StageCnt == 0)
		{
			stageRank1 = all;
		}
		else if (StageCnt == 1)
		{
			stageRank2 = all;
		}
		else if (StageCnt == 2)
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
	// âÊëúÇÃª≤ΩﬁéÊìæ
	GetGraphSize(ImageMng::GetInstance().SetID("image/Result/ê√é‚2.png"), &imageX, &imageY);
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



	if(all >= 8)
	{
		rankFlag = 3;
		if (rankSize.all >= 1.5)
		{
			if (rankSize.bigSize > 0)
			{
				rankSize.bigSize -= 0.1f;
			}
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/òg2.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/äΩäÏ2.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/òg.png"), true);

		}
		else
		{
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/ê√é‚2.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/òg.png"), true);

		}

	}
	else if (all >= 6 && all < 8)
	{
		rankFlag = 2;
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/ê√é‚2.png"), true);
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/òg.png"), true);
	}
	else
	{
		if (rankSize.all >= 1.5)
		{
			if (rankSize.bigSize > 0)
			{
				rankSize.bigSize -= 0.1f;
			}
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/ÉKÅ[Éì.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0 + rankSize.bigSize, 0, ImageMng::GetInstance().SetID("image/Result/òg.png"), true);

		}
		else
		{
			rankFlag = 1;
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/ê√é‚2.png"), true);
			DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + shake, SCREEN_SIZE_Y - imageY / 2 + 50 + shake, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/òg.png"), true);
		}
	}

	// ï]âø
	Evaluation();

	//ÉTÉEÉìÉh
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// RocketÇ™çƒê∂íÜÇ»ÇÁRocketÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Boost) == 1)StopSoundMem(Boost);// BoostÇ™çƒê∂íÜÇ»ÇÁBoostÇÃâπÇé~ÇﬂÇÈ
	StopSoundMem(Bom);	// BomÇ™çƒê∂íÜÇ»ÇÁBomÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// MainÇ™çƒê∂íÜÇ»ÇÁMainÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//EmergencyâπÇ™çƒê∂íÜÇ»ÇÁEmergencyâπÇé~ÇﬂÇÈ

	// ∂≈ver
	DrawRotaGraph(SCREEN_SIZE_X / 2 + shake * 1.5, 50, 1.5, 0, ImageMng::GetInstance().SetID("image/result_kana.png"), true);
	DrawRotaGraph(100 + shake * 1.5, 125, 1, 0, ImageMng::GetInstance().SetID("image/time_kana.png"), true);
	DrawRotaGraph(150 + shake * 1.5, 200, 1, 0, ImageMng::GetInstance().SetID("image/nenryo_kana.png"), true);
	DrawRotaGraph(100 + shake * 1.5, 275, 1, 0, ImageMng::GetInstance().SetID("image/life_kana.png"), true);
	DrawRotaGraph(100 + shake * 1.5, SCREEN_SIZE_Y / 2 - 25 + shake, 1, 0, ImageMng::GetInstance().SetID("image/rank_kana.png"), true);

	// ±ŸÃßÕﬁØƒver
	//DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.5, 0, ImageMng::GetInstance().SetID("image/result_eng.png"), true);
	//DrawRotaGraph(100, 500, 1, 0, ImageMng::GetInstance().SetID("image/time_eng.png"), true);
	//DrawRotaGraph(100, 600, 1, 0, ImageMng::GetInstance().SetID("image/sample_eng.png"), true);

	// ï]âø
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
		DrawBox(line.L + shake, 155 + shake, line.R1 + shake, 158 + shake, 0xffffff, true);
		DrawBox(line.L - shake, 230 - shake, line.R2 - shake, 233 - shake, 0xffffff, true);
		DrawBox(line.L + shake, 305 + shake, line.R3 + shake, 308 + shake, 0xffffff, true);
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
				resultSkip = true;
				ChangeVolumeSoundMem(255 * 80 / 100, Result_rankAll);
				PlaySoundMem(Result_rankAll, DX_PLAYTYPE_BACK);
				if (rankFlag == 3) {
					PlaySoundMem(Cheers, DX_PLAYTYPE_BACK);
				}
				else if (rankFlag == 2) {
					PlaySoundMem(Clap, DX_PLAYTYPE_BACK);
				}
				else
				{
					PlaySoundMem(Booing, DX_PLAYTYPE_BACK);
				}
				playResultFlag = true;
				rankSize.incEnd = false;
			}
		}

		if (CheckSoundMem(Result_rankAll) == 0)
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
		DrawRotaGraph(400 + shake, 125 - shake, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if (timeEval == 2)
	{
		DrawRotaGraph(400 + shake, 125 - shake, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400 + shake, 125 - shake, rankSize.time, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (fuelEval == 3)
	{
		DrawRotaGraph(400 + shake, 200 - shake, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if (fuelEval == 2)
	{
		DrawRotaGraph(400 + shake, 200 - shake, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400 + shake, 200 - shake, rankSize.sample, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (lifeEval == 3)
	{
		DrawRotaGraph(400 + shake, 275, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
	}
	else if (lifeEval == 2)
	{
		DrawRotaGraph(400 + shake, 275, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
	}
	else
	{
		DrawRotaGraph(400 + shake, 275, rankSize.life, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
	}

	if (all == 9 || all == 8)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake * 1.5, SCREEN_SIZE_Y / 2 - 30 + shake * 1.5, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_A.png"), true);
		if (all == 9)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50 + shake * 1.5, SCREEN_SIZE_Y / 2 - 30 + shake * 1.5, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else if (all == 7 || all == 6)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake * 1.5, SCREEN_SIZE_Y / 2 - 30 + shake * 1.5, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_B.png"), true);
		if (all == 7)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50 + shake * 1.5, SCREEN_SIZE_Y / 2 - 30 + shake * 1.5, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else if (all == 5 || all == 4)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake * 1.5, SCREEN_SIZE_Y / 2 - 30 + shake * 1.5, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_C.png"), true);
		if (all == 5)
		{
			DrawRotaGraph(SCREEN_SIZE_X / 2 + 50 + shake * 1.5, SCREEN_SIZE_Y / 2 - 30 + shake * 1.5, rankSize.all, 0, ImageMng::GetInstance().SetID("image/+.png"), true);
		}
	}
	else
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2 + shake * 1.5, SCREEN_SIZE_Y / 2 - 30 + shake * 1.5, rankSize.all, 0, ImageMng::GetInstance().SetID("image/rank_D.png"), true);
	}

	static int count = 0;
	int Clear_X = 0, Clear_Y = 680;
	if (StageCnt == 0) {
		if (CheckSoundMem(ED1) == 0)PlaySoundMem(ED1, DX_PLAYTYPE_LOOP);//ResultÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		count = (count + 1) % 100;
	}
	else if (StageCnt == 1) {
		if (CheckSoundMem(ED2) == 0)PlaySoundMem(ED2, DX_PLAYTYPE_LOOP);//ResultÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		count = (count + 1) % 100;
	}
	else if (StageCnt == 2) {
		ChangeVolumeSoundMem(255 * 70 / 100, LED);//LEDÇÃâπÇÃÉ{ÉäÉÖÅ[ÉÄÇ70%Ç…ê›íË
		if (CheckSoundMem(LED) == 0)PlaySoundMem(LED, DX_PLAYTYPE_LOOP);//ResultÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		count = (count + 1) % 100;
	}

	if (resultSkip)
	{
		spCnt++;
		if ((spCnt / 30) % 2 == 0)
		{
			DrawString(SCREEN_SIZE_X / 2 - 120, SCREEN_SIZE_Y / 2 + 40, "Press the 'Space Button'", 0xffffff);
		}
		if (KeyMng::GetInstance().trgKey[P1_SPACE])
		{
			StageCnt++;
			lpGameTask.SetStageCnt(StageCnt);
			ResultReset();
			PlaySoundMem(Start, DX_PLAYTYPE_BACK);

			if (CheckSoundMem(ED1) == 1)StopSoundMem(ED1);	// ED1Ç™çƒê∂íÜÇ»ÇÁEd1ÇÃâπÇé~ÇﬂÇÈ
			if (CheckSoundMem(ED2) == 1)StopSoundMem(ED2);	// ED1Ç™çƒê∂íÜÇ»ÇÁEd1ÇÃâπÇé~ÇﬂÇÈ

			if (CheckSoundMem(LED) == 1)StopSoundMem(LED);	// LEDÇ™çƒê∂íÜÇ»ÇÁLEDÇÃâπÇé~ÇﬂÇÈ

			MaxTime = MaxTime + MainTimer;
			modeFlag = false;
			resultSkip = false;
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
	}
	
	ScreenFlip();

	return 0;
}

int GameTask::GameOver(void)
{
 	ClsDrawScreen();
	//ÉTÉEÉìÉh
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// RocketÇ™çƒê∂íÜÇ»ÇÁRocketÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Bom) == 1)StopSoundMem(Bom);// BomÇ™çƒê∂íÜÇ»ÇÁBomÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// MainÇ™çƒê∂íÜÇ»ÇÁMainÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//EmergencyâπÇ™çƒê∂íÜÇ»ÇÁEmergencyâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);
	if (CheckSoundMem(Over) == 0)PlaySoundMem(Over, DX_PLAYTYPE_LOOP);//OverÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑

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
	//âÊñ äOÇ…èoÇƒÉQÅ[ÉÄÉIÅ[ÉoÅ[Ç…Ç»Ç¡ÇΩéû
	if (OutOfScreen) {
		DrawGameOver = true;
		//ÉmÉCÉYÇÃï`âÊ
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
			paint_y++;//ï`âÊÇ∑ÇÈÇ∆Ç´ÇÃÇ∏ÇÁÇ∑íl
		}
		else if (playerVec.y > 0) {
			paint_y--;//ï`âÊÇ∑ÇÈÇ∆Ç´ÇÃÇ∏ÇÁÇ∑íl
		}
		if (playerVec.x > 0) {
			paint_x++;//ï`âÊÇ∑ÇÈÇ∆Ç´ÇÃÇ∏ÇÁÇ∑íl
		}
		else if (playerVec.x < 0) {
			paint_x--;//ï`âÊÇ∑ÇÈÇ∆Ç´ÇÃÇ∏ÇÁÇ∑íl
		}
	}
	else
	{	//ÇªÇÍà»äOÇÃéû(îRóøêÿÇÍ)
		if (GameOverFlag)
		{
			paint_x = 0;//ï`âÊÇ∑ÇÈÇ∆Ç´ÇÃÇ∏ÇÁÇ∑íl
			paint_y--;	//ï`âÊÇ∑ÇÈÇ∆Ç´ÇÃÇ∏ÇÁÇ∑íl
		}
	}
	//é©ã@ÇÃï`âÊ

	if (UFOFlag == true) //é©ã@Ç™ufoÇÃéû
	{	
		DrawRotaGraph(Ppos_x + paint_x, Ppos_y - paint_y, 1.0, playerAngle, ImageMng::GetInstance().SetID("image/ufo.png"), true);
	}
	else 
	{
		//é©ã@í èÌéû(ÉçÉPÉbÉg)
		DrawRotaGraph(Ppos_x + paint_x, Ppos_y - paint_y, 1.0, playerAngle, ImageMng::GetInstance().SetID("image/player.png"), true);
	}

	// ÿƒ◊≤or¿≤ƒŸÇëIë
	if (DrawGameOver)
	{
		GameOverCnt = false;
		if (retryCnt > 0)
		{
			if (KeyMng::GetInstance().trgKey[P1_UP] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0)
			{
				PlaySoundMem(Choose, DX_PLAYTYPE_BACK);
				if (pauseCheck)
				{
					pauseCheck = false;
				}
			}
			else if (KeyMng::GetInstance().trgKey[P1_DOWN])
			{
				PlaySoundMem(Choose, DX_PLAYTYPE_BACK);
				if (!pauseCheck)
				{
					pauseCheck = true;
				}
			}
		}
		else
		{
			if (!pauseCheck)
			{
				pauseCheck = true;
			}
		}

		// ÿƒ◊≤or¿≤ƒŸ
		if (KeyMng::GetInstance().trgKey[P1_SPACE] && pauseCheck)
		{
			PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
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
			if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// OverÇ™çƒê∂íÜÇ»ÇÁOverÇÃâπÇé~ÇﬂÇÈ
															// îwåiÇÃçÌèú
			std::vector<BackGround*>::iterator itrBG = backVec.begin();

			titleBright = 0;
			rocketSize = 0.0f;
			rocketPos = { SCREEN_SIZE_X / 2,SCREEN_SIZE_Y - 150 };
			lightFlag = false;
			pushSpace = false;
			UFOFlag = false;
			GameOverFlag = false;
			DrawGameOver = false;
			OutScr = false;
			launchFlag = false;
			shakeFlag = false;
			pushSpace = false;
			shake = 0.0f;
			shakeWidth = 5;
			overBright = 255;
			titleTime = 0;
			retryCnt = 10;

			modeFlag = true;
			GtskPtr = &GameTask::GameTitle;
		}
		if (initMainLandCnt == 0)
		{
			if (KeyMng::GetInstance().trgKey[P1_SPACE] && !landGameCheck && !pauseCheck)
			{
				if (!getSample)
				{
					if (initMainLandCnt == 0)
					{
						retryCnt--;

						initMainLandCnt = 1;
					}
				}
				else
				{
					if (initMainLandCnt == 0)
					{
						retryCnt--;

						initMainLandCnt = 2;
					}
				}
				if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// OverÇ™çƒê∂íÜÇ»ÇÁOverÇÃâπÇé~ÇﬂÇÈ
			}

			// ¡™Ø∏Œﬂ≤›ƒìûíBéû
			if (KeyMng::GetInstance().trgKey[P1_SPACE] && landGameCheck && !pauseCheck)
			{
				if (initMainLandCnt == 0)
				{
					retryCnt--;

					initMainLandCnt = 3;
				}
			}
		}

		if (initMainLandCnt == 1)
		{
			PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
			AnimCnt = 0;
			AnimTime = 0;
			paint_y = 0;
			(*obstracle)->SetPos(VECTOR3((float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y));
			GameOverFlag = false;
			DrawGameOver = false;
			OutScr = false;
			overBright = 255;
			modeFlag = false;

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
			initMainLandCnt = 0;
		}
		else if (initMainLandCnt == 2)
		{
			PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
			AnimCnt = 0;
			AnimTime = 0;
			paint_y = 0;
			(*obstracle)->SetPos(VECTOR3((float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y));
			GameOverFlag = false;
			DrawGameOver = false;
			OutScr = false;
			overBright = 255;
			modeFlag = false;

			auto setCnt = 0;
			auto itrPos = VECTOR3(0, 0);
			for (auto itr : bpList)
			{
				itrPos = itr->GetPos();
				itr->SetPos(VECTOR3(tSetPos[setCnt].x, tSetPos[setCnt].y + (pltrgPos.y - targetSet[StageCnt].y + 105)));
				setCnt++;
			}
			(*player)->SetPos(VECTOR3(pltrgScr.x*1.2f, 333));
			(*player)->SetVec(VECTOR3(0, 0.1f));
			(*player)->SetEnergy(100.0f);
			(*player)->SetplPos(VECTOR3(setplPos.x, setplPos.y));
			SetScrollPos(-targetVec);


			setCount = true;
			landingCheck = false;
			landAnimFlag = false;
			landingFlag = true;
			clearCheck = true;						// ∏ÿ±â¬î\èÛë‘Ç…Ç∑ÇÈ
			hitCheck = false;
			clearCnt = 0;

			GtskPtr = &GameTask::GameMain;
			initMainLandCnt = 0;
		}
		else if (initMainLandCnt == 3)
		{
			landGameCheck = false;
			OutScr = false;

			if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// OverÇ™çƒê∂íÜÇ»ÇÁOverÇÃâπÇé~ÇﬂÇÈ

			GtskPtr = &GameTask::GameLanding;
			initMainLandCnt = 0;
		}
	}


	//è¨òfêØorË¶êŒÇ…ìñÇΩÇ¡ÇƒÉQÅ[ÉÄÉIÅ[ÉoÅ[ÇÃéû
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

		DrawGraph(Bpos_x, Bpos_y - paint_y, DieAnim[AnimCnt], true);	//îöî≠ÉGÉtÉFÉNÉgï`âÊ
	}

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

	if (DrawGameOver)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 - 50, 1.0, 0, IMAGE_ID("image/pause/gameover.png"), true);
		if (pauseCheck)
		{
			DrawRotaGraph(SCREEN_CENTER_X - 75, 625, 1.0, 0, IMAGE_ID("image/pause/titleback.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 625, 0.8, 0, IMAGE_ID("image/pause/ëIë.png"), true);
			SetDrawBright(100, 100, 100);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 525, 1.0, 0, IMAGE_ID("image/pause/retry.png"), true);
			for (int i = 0; i < retryCnt; i++)
			{
				if (i >= 5)
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + (i - 5) * 40, 525 + 40, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
				else
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + i * 40, 525 - 20, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
			}
		}
		else
		{
			DrawRotaGraph(SCREEN_CENTER_X - 75, 525, 1.0, 0, IMAGE_ID("image/pause/retry.png"), true);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 525, 0.8, 0, IMAGE_ID("image/pause/ëIë.png"), true);
			for (int i = 0; i < retryCnt; i++)
			{
				if (i >= 5)
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + (i - 5) * 40, 525 + 40, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
				else
				{
					DrawRotaGraph(SCREEN_CENTER_X + 55 + i * 40, 525 - 20, 0.8, 340 * 3.14 / 180, IMAGE_ID("image/Player.png"), true);
				}
			}
			SetDrawBright(100, 100, 100);
			DrawRotaGraph(SCREEN_CENTER_X - 75, 625, 1.0, 0, IMAGE_ID("image/pause/titleback.png"), true);
		}
	}

	ScreenFlip();

	return 0;
}

int GameTask::GameClear(void)
{
	ClsDrawScreen();
	score = sogo * 4 - 8;

	titleTransitionCnt++;
	if (KeyMng::GetInstance().trgKey[P1_SPACE] || titleTransitionCnt == 4000)
	{
		StopSoundMem(ClearBGM);
		modeFlag = true;
		titleTransitionCnt = 0;
		GtskPtr = &GameTask::GameTitle;
	}
	else
	{
		if (CheckSoundMem(ClearBGM) == 0)
			PlaySoundMem(ClearBGM, DX_PLAYTYPE_LOOP);
	}

	if (MaxTime >= 2000)
	{
		if (slideE < 150)
		{
			slideE++;
		}
		if (slideP < 120)
		{
			slideP += 0.8f;
		}
		DrawGraph(0, 0, IMAGE_ID("image/landBG.png"), true);
		DrawRotaGraph(SCREEN_SIZE_X / 2, slideE, -earthSize - 1, 0, bEarthImage[(earthAnimCnt++ / 15) % 19], true);
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - slideP, 3, 0, IMAGE_ID("image/BEnd.png"), true);
		DrawRotaGraph(SCREEN_SIZE_X / 2 - 50, SCREEN_SIZE_Y / 2, 1, 0, IMAGE_ID("image/ëççáï]âø.png"), true);
	}
	else
	{
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
		DrawRotaGraph(SCREEN_SIZE_X / 2 - 50, SCREEN_SIZE_Y / 2, 1, 0, IMAGE_ID("image/ëççáï]âø.png"), true);
	}

	// ëççáï]âø
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

	if ((titleTransitionCnt / 30) % 2 == 0)
	{
		DrawString(SCREEN_SIZE_X / 2 - 120, SCREEN_SIZE_Y - 50, "Press the 'Space Button'", 0xffffff);
	}

	ScreenFlip();

	return 0;
}

void GameTask::Transition()
{
	EtoP = (GetErPosY() - GetPlPosY()) / 300;
	EtoPtrans = ((-GetSclPosY() / EtoP) + 700);

	if (!pauseFlag)
	{
		if (GetPlayerPos().x > 350 && GetPlayerPos().y > 0 && GetPlayerPos().y < 800)
		{
			if (transAlpha > 50)
			{
				transAlpha -= 15.0f;
			}
		}
		else
		{
			if (transAlpha < 255)
			{
				transAlpha += 15.0f;
			}
		}
	}
	else
	{
		if (transAlpha > 80)
		{
			transAlpha -= 5.0f;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (GtskPtr == &GameTask::GameMain)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, transAlpha);
			DrawLine(399 + i, 50, 399 + i, 730, GetColor(128, 128, 128), true);
			DrawLine(399 + i, 400, 399 + i, 730, GetColor(128, 128, 128), true);
			DrawLine(399 + i, EtoPtrans, 399 + i, 730, GetColor(255, 255, 255), true);
			DrawCircle(400, 50, 5, GetColor(128, 128, 128), true);
			DrawCircle(400, 160, 5, GetColor(128, 128, 128), true);
			DrawRotaGraph(400, 725, 2, 0, ImageMng::GetInstance().SetID("image/chikyu_trans.png"), true);
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
			if (lpGameTask.GetStageCnt() == 0)
			{
				DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/mars_trans.png"), true);
			}
			else if (lpGameTask.GetStageCnt() == 1)
			{
				DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/jupit_trans.png"), true);
			}
			else
			{
				DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/nept_trans.png"), true);
			}
			SetDrawBright(255, 255, 255);
			DrawRotaGraph(400, EtoPtrans, 1.5, 0, ImageMng::GetInstance().SetID("image/player4.png"), true);
			SetDrawBright(128, 128, 128);
			DrawRotaGraph(400, disTrans, 1, 0, ImageMng::GetInstance().SetID("image/spCraft.png"), true);
			SetDrawBright(255, 255, 255);
			SetAlpha(0.0f);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, transAlpha);
		}
		else if (GtskPtr == &GameTask::GameLanding && GetScene() == 2)
		{
			if (-GetLdistance() / 2 + 700 * 0.55 > 50)
				disTrans = -GetLdistance() / 2 + 700 * 0.55;

			if (GetAlpha() >= 255)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, transAlpha);
			}
			else
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, GetAlpha());
			}
			DrawLine(399 + i, 50, 399 + i, 730, GetColor(128, 128, 128), true);
			DrawLine(399 + i, 50, 399 + i, disTrans, GetColor(255, 255, 255), true);
			DrawLine(399 + i, 400, 399 + i, 730, GetColor(128, 128, 128), true);
			DrawCircle(400, 50, 5, GetColor(255, 255, 255), true);

			if (GetLandAngle() == -1)
			{
				colBright = 128;
				disTrans = 50.0f;
				SetLandAngle(0);
				SetAlpha(0.0f);
				SetLdistance(800);
			}
			else
			{
				if (disTrans >= 160)
				{
					colBright++;
					if (colBright > 255)
					{
						colBright = 255;
					}
				}
			}

			DrawCircle(400, 160, 5, GetColor(colBright, colBright, colBright), true);

			if (lpGameTask.GetStageCnt() == 0)
			{
				DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/mars_trans.png"), true);
			}
			else if (lpGameTask.GetStageCnt() == 1)
			{
				DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/jupit_trans.png"), true);
			}
			else
			{
				DrawRotaGraph(400, 400, 2, 0, ImageMng::GetInstance().SetID("image/nept_trans.png"), true);
			}
			DrawRotaGraph(400, disTrans, 1, 0, ImageMng::GetInstance().SetID("image/spCraft.png"), true);
			SetDrawBright(128, 128, 128);
			DrawRotaGraph(400, 725, 2, 0, ImageMng::GetInstance().SetID("image/chikyu_trans.png"), true);
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

std::list<bp_ptr>::iterator GameTask::AddBplist(bp_ptr && bpPtr)
{
	bpList.push_back(bpPtr);
	auto itr = bpList.end();
	itr--;
	return itr;
}


