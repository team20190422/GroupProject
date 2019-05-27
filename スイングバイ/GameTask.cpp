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
	SetWindowText("ÉXÉCÉìÉOÉoÉC");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	for (int j = 0; j < 11; j++)
	{
		DieAnim[j] = LoadDivGraph("image/Explosion/îöî≠_ëÂ.png", 11, 11, 1, 115, 100, DieAnim,true);
		OutScrAnim[j] = LoadDivGraph("image/Number/countdown.png", 11, 11, 1, 100, 100, OutScrAnim, true);

		//DieAnim[j] = LoadGraph("image/îöî≠_ëÂ.png");
	}
	for (int i = 0; i < EarthMax; i++)
	{
		EarthImage[i] = LoadDivGraph("image/earthAnimNC.png", 20, 20, 1, 100, 50, EarthImage, true);
	}

	//âπäyÉtÉ@ÉCÉãì«Ç›çûÇ›
	OP = LoadBGM("sound/ãÛÇÃãLâØ.ogg");
	Main = LoadBGM("sound/âFíàÇÃò»Ç›.ogg");
	ED1 = LoadBGM("sound/óVêØ.ogg");
	ED2 = LoadBGM("sound/farewell.ogg");
	LED = LoadBGM("sound/ê¢äEÇ™ñlíBÇ…óhÇÍÇÈÇ‹Ç≈.ogg");
	Over = LoadBGM("sound/âFíàãÛä‘.ogg");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);	// à≥èkÇ≥ÇÍÇΩëSÉfÅ[É^ÇÕÉVÉXÉeÉÄÉÅÉÇÉäÇ…äiî[Ç≥ÇÍÅAçƒê∂Ç∑ÇÈïîï™ÇæÇØíÄéüâìÄÇµÇ»Ç™ÇÁÉTÉEÉìÉhÉÅÉÇÉäÇ…äiî[Ç∑ÇÈ(ñ¬ÇÁÇµèIÇÌÇÈÇ∆âìÄÇµÇΩÉfÅ[É^ÇÕîjä¸Ç≥ÇÍÇÈÇÃÇ≈âΩìxÇ‡âìÄèàóùÇ™çsÇÌÇÍÇÈ)
	Decision = LoadSoundMem("sound/ëIëâπ.ogg");
	Rocket = LoadSoundMem("sound/ÉçÉPÉbÉgï¨éÀ.ogg");
	Boost = LoadSoundMem("sound/ÉKÉXÉoÅ[ÉiÅ[.ogg");
	Emergency = LoadSoundMem("sound/åxïÒ.ogg");
	Emergency2 = LoadSoundMem("sound/åxïÒ03.ogg");
	Bom = LoadSoundMem("sound/explosion3.ogg");
	UFO = LoadSoundMem("sound/UFO01.ogg");

	GtskPtr = &GameTask::GameTitle;
	return 0;
}


int GameTask::GameInit(void)
{
	//
	auto riset = [&] {
		time = 0;
		MainTimer = 0;
		AnimCnt = 0;
		clearCnt = 0;
		limitAnimSize = 2.0f;
		limitTime = 4;
		subTitleCnt = 0;
		subTitleAnim = 0;
		outScreenTime = 0;
		resultAnimCnt = 200;
		resultTime = 0;

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

	for (auto i : targetSet)
	{
		i += VECTOR3(1, 0);

	}
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
			MarsCnt++;
			mars = AddBplist(std::make_shared<Mars>(targetPlanet, MarsCnt));
		}
	}

	if (UFOFlag == true) {
		(*player)->init("image/UFO.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}
	else {
		(*player)->init("image/Player.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 1.0f);
	}
	(*obstracle)->init("image/meteo.png", VECTOR2(64 / 2, 32 / 1), VECTOR2(2, 1), VECTOR2(1, 0), 0.5f);

	//ImageMng::GetInstance().SetID("TITLE", "image/É^ÉCÉgÉã.png");
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

	//ÉTÉEÉìÉhä÷åW
	ChangeVolumeSoundMem(255 * 70 / 100, OP);//OPÇÃâπÇÃÉ{ÉäÉÖÅ[ÉÄÇ70%Ç…ê›íË
	if (CheckSoundMem(OP) == 0)PlaySoundMem(OP, DX_PLAYTYPE_LOOP);//OPÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑

																  //âBÇµÉRÉ}ÉìÉh
	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}

	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/landBG.png"), true);
	//if ((lgtsCnt++ / 30) % 2 == 0)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 1, angle+=0.005f, ImageMng::GetInstance().SetID("image/LGTS.png"), true);
	}
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - 100, earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	// ¿≤ƒŸâÊñ 
	DrawGraph(0, 0, ImageMng::GetInstance().SetID("image/title.png"), true);
	DrawRotaGraphF(SCREEN_SIZE_X / 2, (SCREEN_SIZE_Y - 100) + shakeEarth, earthSize, 0, EarthImage[(earthAnimCnt++ / 15) % 19], true);

	if (KeyMng::GetInstance().newKey[P1_LCtrl]) {
		UFOFlag = true;
	}
	if (UFOFlag == true) {
		int ufo_x = 25, ufo_y = 200;
		DrawGraph(ufo_x, ufo_y, IMAGE_ID("image/UFOå∞åª.png"), true);
	}
	//ÉQÅ[ÉÄÉÇÅ[Éhà⁄çs
	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);

		titleShake = 5;
		//pushSpace = true;
	}

	// êUìÆ
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
		if (UFOFlag == true) {
			DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/uf0(side).png"), true);
		}
		else {
			DrawRotaGraph(rocketPos.x, rocketPos.y, rocketSize, 0, ImageMng::GetInstance().SetID("image/rocket.png"), true);
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

		if (rocketPos.y < 0)
		{
			if (landingCnt[0] > 0 && !lightFlag)
			{
				landingCnt[0] -= 5;
			}
			else
			{
				lightFlag = true;
				/*DeleteGraph(ImageMng::GetInstance().SetID("image/rocket.png"));
				DeleteGraph(ImageMng::GetInstance().SetID("image/landBG.png"));
				DeleteGraph(ImageMng::GetInstance().SetID("image/title.png"));
				for (int i = 0; i < 20; i++)
				{
					DeleteGraph(EarthImage[i]);
				}*/
				if (CheckSoundMem(OP) == 1) StopSoundMem(OP);//TitleÇ™çƒê∂íÜÇ»ÇÁTitleÇé~ÇﬂÇÈ
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

// âFíàóVâj
int GameTask::GameMain(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ClsDrawScreen();

	// ¥›√ﬁ®›∏ﬁéûÇÃï™äÚópÇÃ¿≤—åvë™
	MainTimer++;

	if (CheckSoundMem(Main) == 0)PlaySoundMem(Main, DX_PLAYTYPE_LOOP);//MainÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑

																	  //ÉTÉEÉìÉhä÷åW
	if (KeyMng::GetInstance().newKey[P1_UP]) {//Å™ÉLÅ[Ç™âüÇ≥ÇÍÇΩÇ∆Ç´
		if (UFOFlag == true) {
			if (CheckSoundMem(UFO) == 0)PlaySoundMem(UFO, DX_PLAYTYPE_LOOP);//UFOÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
		else {
			//ÉçÉPÉbÉgï¨éÀÇÃâπÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒÉçÉPÉbÉgï¨éÀÇÃâπÇçƒê∂Ç∑ÇÈ
			if (CheckSoundMem(Rocket) == 0)PlaySoundMem(Rocket, DX_PLAYTYPE_LOOP);//RocketÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		}
	}
	else {	//ÇªÇ§Ç≈Ç»ÇØÇÍÇŒâπÇé~ÇﬂÇÈ
		StopSoundMem(UFO);//UFOâπÇé~ÇﬂÇÈ
		StopSoundMem(Rocket);//RocketâπÇé~ÇﬂÇÈ
	}

	if (KeyMng::GetInstance().newKey[P1_SPACE]) {
		if (CheckSoundMem(Boost) == 0)PlaySoundMem(Boost, DX_PLAYTYPE_BACK);//BoostÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
	}
	else {
		StopSoundMem(Boost);//BoostâπÇé~ÇﬂÇÈ
	}


	// Ç±Ç±Ç©ÇÁ
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
		ChangeFont("MSÉSÉVÉbÉN");

		SetFontSize(20);		// Ã´›ƒÇÃª≤Ωﬁ

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
	// Ç±Ç±Ç‹Ç≈

	if (KeyMng::GetInstance().trgKey[P1_ENTER])
	{
		PlaySoundMem(Decision, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(Main) == 1) {	//MainÇ™çƒê∂íÜÇ»ÇÁ
			StopSoundMem(Main);	////ÉÅÉÇÉäÇ…ì«Ç›çûÇÒÇæMainÇÃâπÉfÅ[É^ÇçÌèú
			StopSoundMem(Rocket);// RocketÇ™çƒê∂íÜÇ»ÇÁRocketÇÃâπÇé~ÇﬂÇÈ
			StopSoundMem(Boost);// BoostÇ™çƒê∂íÜÇ»ÇÁBoostÇÃâπÇé~ÇﬂÇÈ
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
		itrBG->Update();
		itrBG->Draw();
	}

	distance = { DISTANCE_MAX };
	time++;

	for (auto itr : bpList)
	{

		// Ç∑Ç◊ÇƒÇÃòfêØÇÃUpdate
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
			//DrawString((int)playerPos.x, (int)playerPos.y, "Ç‚ÇÁÇÍÇΩ", 0xffffff);
			StopSoundMem(UFO);		//UFOâπÇé~ÇﬂÇÈ
			StopSoundMem(Rocket);	//RocketâπÇé~ÇﬂÇÈ
			StopSoundMem(Boost);	//BoostâπÇé~ÇﬂÇÈ
			if (CheckSoundMem(Bom) == 0)PlaySoundMem(Bom, DX_PLAYTYPE_BACK);//îöî≠âπÇ™ñ¬Ç¡ÇƒÇ¢ÇÈÇ©í≤Ç◊ÇƒÇ»Ç¡ÇƒÇ¢Ç»Ç©Ç¡ÇΩÇÁñ¬ÇÁÇ∑
																			// Ç±Ç±ÇÃifï™
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

	//ãÈå`ÇÃìñÇΩÇËîªíË
	if (HitCheck((*player)->GetRect(), (*obstracle)->GetRect()) == true) {
		hitCheck = true;
		if (GetLandCheck()) {
			hitCheck = false;
		}
	}

	if (hitCheck == true) {	//ÉvÉåÉCÉÑÅ[Ç™éÄÇÒÇæÇ∆Ç´
		StopSoundMem(UFO);		//UFOâπÇé~ÇﬂÇÈ
		StopSoundMem(Rocket);	//RocketâπÇé~ÇﬂÇÈ
		StopSoundMem(Boost);	//BoostâπÇé~ÇﬂÇÈ
								//îöî≠âπÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒîöî≠âπÇçƒê∂Ç∑ÇÈ
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
	else {
		StopSoundMem(Bom);	//BomâπÇé~ÇﬂÇÈ
	}

	// íÖó§ê¨å˜éû
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
				// íÖó§Ç…à⁄çs
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
		// Ç±Ç±
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
				if (CheckSoundMem(Emergency2) == 0)PlaySoundMem(Emergency2, DX_PLAYTYPE_BACK);

			}
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
	}
	else
	{
		limitTime = 4;
		limitAnimSize = 2.0f;
		outScreenTime = 0;
		if (Energy >= 20 && landingCnt[1] < 255 && landingCnt[0] >= 255)
		{
			landingCnt[1] += 10;
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
			if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);

		}
	}

	// îRóøè≠ó éû
	if (Energy > 0 && Energy < 20 && !(landingCheck && landingFlag))
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

	if (Energy <= 0 && !(landingCheck && landingFlag))
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
				StopSoundMem(Emergency);
				GtskPtr = &GameTask::GameOver;
				GameOverTime = 0;
			}
			SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);


		}
	}
	// Ç±Ç±Ç‹Ç≈
	

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
		else
		{
			//clearCnt = 0;
		}
	}

	// Ç±Ç±Ç©ÇÁ
	if (OutOfScreen)
	{

		//SetFontSize(limitAnimSize--);
		limitAnimSize -= 0.033f;
		if(limitTime > 10)
		SetDrawBright(255, 255, 255);
		//DrawFormatString(SCREEN_CENTER_X, SCREEN_CENTER_Y, GetColor(255, 255, 255), "%d", limitTime);
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, limitAnimSize, 0, OutScrAnim[limitTime], true);
		SetDrawBright(landingCnt[1], landingCnt[1], landingCnt[1]);
		SetFontSize(20);		// Ã´›ƒÇÃª≤Ωﬁ

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
	}

	if (limitAnimSize <= 0)
	{
		limitAnimSize = 2.0f;
	}

	

	// Ω√∞ºﬁ∂≥›ƒ
	StageDraw();

	// Ç±Ç±Ç‹Ç≈

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "playerPosX %f playerPosY %f", playerPos.x,playerPos.y);
	DrawFormatStringF(10, 550, GetColor(255, 255, 255), "targetVecX %f targetVecY %f", targetVec.x, targetVec.y);
	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "time %d", MainTimer);

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
	StopSoundMem(Emergency);//EmergencyâπÇé~ÇﬂÇÈ

	ClsDrawScreen();
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

	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		landAnimFlag = true;
	}

	// èåèíBê¨ÇµÇΩÇÁâFíàÇ÷ñﬂÇÈ
	if (landAnimFlag)
	{
		pltrgPos = VECTOR3(playerPos.x + targetVec.x, playerPos.y);
		(*player)->SetPos(pltrgPos);
		SetScrollPos(-targetVec);
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
	auto Evaluation = [&] {

		// ¿≤—ï]âø
		if (MainTimer <= 200)
		{
			timeEval = 'A';
		}
		else
		{
			timeEval = 'B';
		}

		// çÃéÊï]âø
		if (getSample)
		{
			sampleEval = 'A';
		}
		else
		{
			sampleEval = 'B';
		}

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
	DrawGraph(0, 0, resultAnim, true);


	SetDrawBright(landingCnt[0], landingCnt[0], landingCnt[0]);


	DrawString(0, 0, "GameResult", 0xffffff);

	if (!getSample)
	{
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/ê√é‚2.png"), true);
	}
	else
	{
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/òg2.png"), true);
		DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)) + resultAnimCnt, SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/äΩäÏ2.png"), true);
	}
	DrawRotaGraph((SCREEN_SIZE_X - (imageX / 2)), SCREEN_SIZE_Y / 4, 1.0, 0, ImageMng::GetInstance().SetID("image/Result/òg.png"), true);

	// ï]âø
	Evaluation();

	//ÉTÉEÉìÉh
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// RocketÇ™çƒê∂íÜÇ»ÇÁRocketÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Boost) == 1)StopSoundMem(Boost);// BoostÇ™çƒê∂íÜÇ»ÇÁBoostÇÃâπÇé~ÇﬂÇÈ
	StopSoundMem(Bom);	// BomÇ™çƒê∂íÜÇ»ÇÁBomÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// MainÇ™çƒê∂íÜÇ»ÇÁMainÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//EmergencyâπÇ™çƒê∂íÜÇ»ÇÁEmergencyâπÇé~ÇﬂÇÈ

	SetFontSize(50);		// Ã´›ƒÇÃª≤Ωﬁ
	SetFontThickness(8);	// Ã´›ƒÇÃëæÇ≥
	ChangeFont("Ailerons");
	DrawString(SCREEN_SIZE_X / 2 - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "RESULT", 0xffffff);
	DrawFormatStringF(10, 450, GetColor(255, 255, 255), "time   %d %c", MainTimer, timeEval);
	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "sample %d %c", getSample, sampleEval);//Evaluation
	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "Evaluation %d", getSample);
	SetFontSize(20);		// Ã´›ƒÇÃª≤Ωﬁ
	SetFontThickness(8);	// Ã´›ƒÇÃëæÇ≥
	ChangeFont("MSÉSÉVÉbÉN");

	static int count = 0;
	int Clear_X = 0, Clear_Y = 680;

	if (StageCnt == 0) {
		if (CheckSoundMem(ED1) == 0)PlaySoundMem(ED1, DX_PLAYTYPE_LOOP);//ResultÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		count = (count + 1) % 100;
		if (count < 50) {
			DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage1Clear.png"), true);
		}
	}
	else if (StageCnt == 1) {
		if (CheckSoundMem(ED2) == 0)PlaySoundMem(ED2, DX_PLAYTYPE_LOOP);//ResultÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		count = (count + 1) % 100;
		if (count < 50) {
			DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage2Clear.png"), true);
		}
	}
	else if (StageCnt == 2) {
		ChangeVolumeSoundMem(255 * 70 / 100, LED);//LEDÇÃâπÇÃÉ{ÉäÉÖÅ[ÉÄÇ70%Ç…ê›íË
		if (CheckSoundMem(LED) == 0)PlaySoundMem(LED, DX_PLAYTYPE_LOOP);//ResultÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑
		count = (count + 1) % 100;
		if (count < 50) {
			DrawGraph(Clear_X, Clear_Y, IMAGE_ID("image/Result/Stage3Clear.png"), true);
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

		if (CheckSoundMem(ED1) == 1)StopSoundMem(ED1);	// ED1Ç™çƒê∂íÜÇ»ÇÁEd1ÇÃâπÇé~ÇﬂÇÈ
		if (CheckSoundMem(ED2) == 1)StopSoundMem(ED2);	// ED1Ç™çƒê∂íÜÇ»ÇÁEd1ÇÃâπÇé~ÇﬂÇÈ

		if (CheckSoundMem(LED) == 1)StopSoundMem(LED);	// LEDÇ™çƒê∂íÜÇ»ÇÁLEDÇÃâπÇé~ÇﬂÇÈ

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
	}
	//DrawFormatStringF(10, 500, GetColor(255, 255, 255), "íÖó§ %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);
	//DrawFormatStringF(10, 550, GetColor(255, 255, 255), "time %d", MainTimer);
	//DrawFormatStringF(10, 600, GetColor(255, 255, 255), "MaxTime %d", MaxTime);
	ScreenFlip();

	return 0;
}

int GameTask::GameOver(void)
{
	//ÉTÉEÉìÉh
	if (CheckSoundMem(Rocket) == 1)StopSoundMem(Rocket);// RocketÇ™çƒê∂íÜÇ»ÇÁRocketÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Bom) == 1)StopSoundMem(Bom);// BomÇ™çƒê∂íÜÇ»ÇÁBomÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Main) == 1)StopSoundMem(Main);// MainÇ™çƒê∂íÜÇ»ÇÁMainÇÃâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Emergency) == 1)StopSoundMem(Emergency);//EmergencyâπÇ™çƒê∂íÜÇ»ÇÁEmergencyâπÇé~ÇﬂÇÈ
	if (CheckSoundMem(Emergency2) == 1)StopSoundMem(Emergency2);
	if (CheckSoundMem(Over) == 0)PlaySoundMem(Over, DX_PLAYTYPE_LOOP);//OverÇ™çƒê∂íÜÇ≈Ç»ÇØÇÍÇŒâπÇñ¬ÇÁÇ∑

	//âÊëú
	if (AnimTime++ % 10 == 0)
	{
		AnimCnt++;
	}
	DrawGraph((int)playerPos.x, (int)playerPos.y - 300, DieAnim[AnimCnt], true);

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
		if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// OverÇ™çƒê∂íÜÇ»ÇÁOverÇÃâπÇé~ÇﬂÇÈ
		// îwåiÇÃçÌèú
		std::vector<BackGround*>::iterator itrBG = backVec.begin();
		while (itrBG != backVec.end())
		{
			count--;
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
		if (CheckSoundMem(Over) == 1)StopSoundMem(Over);// OverÇ™çƒê∂íÜÇ»ÇÁOverÇÃâπÇé~ÇﬂÇÈ

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


	SetFontSize(50);		// Ã´›ƒÇÃª≤Ωﬁ
	SetFontThickness(8);	// Ã´›ƒÇÃëæÇ≥
	ChangeFont("Ailerons");
	DrawString(SCREEN_CENTER_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 2, "GAME OVER", 0xffffff);
	SetFontSize(20);		// Ã´›ƒÇÃª≤Ωﬁ
	SetFontThickness(8);	// Ã´›ƒÇÃëæÇ≥
	ChangeFont("MSÉSÉVÉbÉN");

	DrawFormatStringF(10, 500, GetColor(255, 255, 255), "íÖó§ %d flag %d return %d clear %d sample %d", landingCheck, landingFlag, returnFlag, clearCheck, getSample);

	ScreenFlip();

	return 0;
}

int GameTask::GameClear(void)
{
	ClsDrawScreen();

	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		GtskPtr = &GameTask::GameTitle;
	}

	if (MaxTime >= 2000)
	{
		DrawGraph(0, 0, IMAGE_ID("image/Result/result.png"), true);
		DrawGraph(0, 400, IMAGE_ID("image/Result/Stage2Clear.png"), true);
	}
	else
	{
		DrawGraph(0, 0, IMAGE_ID("image/Result/result2.png"), true);
		DrawGraph(0, 400, IMAGE_ID("image/Result/Stage3Clear.png"), true);
	}

	DrawString(0, 0, "GameClear", 0xffffff);

	DrawFormatStringF(10, 600, GetColor(255, 255, 255), "MaxTime %d", MaxTime);

	ScreenFlip();

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


