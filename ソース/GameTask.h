#pragma once
#include<vector>
#include<list>
#include<map>
#include "Obj.h"

//class Player;
//class Stage;
//class Enemy;


// 画面遷移用
enum GAME_MODE {
	GAME_INIT,
	GAME_TITLE,
	GAME_MAIN,
	GAME_RESULT
};

typedef std::shared_ptr<Obj> obj_ptr;
typedef std::list<obj_ptr> obj_List;


class GameTask
{
private:
	GameTask();
	GameTask(const GameTask&) {}		//コピーコンストラクタのprivate化
	GameTask operator=(const GameTask&) {}	//代入をprivate化
	~GameTask();
	static GameTask *s_Instance;
public:
	static void Create(void);
	static GameTask &GetInstance(void)
	{
		Create();
		return *s_Instance;
	}

	int SystemInit(void);
	int GameUpdate(void);	//ゲームループメイン


	//char KeyData[256], KeyDataOld[256]; 


	//int animCnt;
	//bool runFlag, lrFlag, jumpFlag, hitFlag;
	//int TitleX, TitleY;
	

private:

	std::list<obj_ptr>::iterator AddObjlist(obj_ptr && objPtr);

	int GameInit(void);
	int GameTitle(void);
	int GameMain(void);
	int GameResult(void);

	int (GameTask::*GtskPtr)(void);

	obj_List objList;
	std::list<obj_ptr>::iterator player;


	// ｷｰ関係
	int newKey, oldKey , trgKey;

	
};