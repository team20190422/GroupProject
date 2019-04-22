#pragma once
#include<vector>
#include<list>
#include<map>

//class Player;
//class Stage;
//class Enemy;


// ��ʑJ�ڗp
enum GAME_MODE {
	GAME_INIT,
	GAME_TITLE,
	GAME_MAIN,
	GAME_RESULT
};
class GameTask
{
private:
	GameTask();
	GameTask(const GameTask&) {}		//�R�s�[�R���X�g���N�^��private��
	GameTask operator=(const GameTask&) {}	//�����private��
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
	int GameUpdate(void);	//�Q�[�����[�v���C��


	//char KeyData[256], KeyDataOld[256]; 


	//int animCnt;
	//bool runFlag, lrFlag, jumpFlag, hitFlag;
	//int TitleX, TitleY;
	

private:

	int GameInit(void);
	int GameTitle(void);
	int GameMain(void);
	int GameResult(void);

	int (GameTask::*GtskPtr)(void);

	// ���֌W
	int newKey, oldKey , trgKey;

	
};