#pragma once
#include<vector>
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


constexpr int SCREEN_SIZE_X(450);
constexpr int SCREEN_SIZE_Y(800);

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

	const VECTOR3& GetScrollPos(void);
	void SetScrollPos(VECTOR3 addPos);


	VECTOR3 playerPos;
	float playerAngle;

	float distance = 0;

	VECTOR3 playerVec = { 0,0 };

	VECTOR3 PandPvec = { 0,0 };			// playerPosC��planetPosC���޸��
	VECTOR3 ScrollPos = { 0,0 };		// ��׽�۰�

	//char KeyData[256], KeyDataOld[256]; 


	//int animCnt;
	//bool runFlag, lrFlag, jumpFlag, hitFlag;
	//int TitleX, TitleY;
	

private:

	std::list<obj_ptr>::iterator AddObjlist(obj_ptr && objPtr);
	std::list<bp_ptr>::iterator AddBplist(bp_ptr && bpPtr);

	int GameInit(void);
	int GameTitle(void);
	int GameMain(void);
	int GameResult(void);

	int (GameTask::*GtskPtr)(void);

	obj_List objList;
	std::list<obj_ptr>::iterator player;
	BackGround* back;
	std::list<obj_ptr>::iterator obstracle;

	// bpList�Ɋi�[
	bp_List bpList;
	std::list<bp_ptr>::iterator mars;
	std::list<bp_ptr>::iterator jupiter;
	std::list<bp_ptr>::iterator earth;

	// ���֌W
	int newKey, oldKey , trgKey;

	//���y�֌W
	int OP, Main, End;	//BGM
	int Decision, Cancel, Rocket,Bom,Boost,UFO,UFOBoost;
	bool UFOFlag,BomFlag;
	//�t�H���g�֌W
	int Font;//�t�H���g�n���h��
	//��ڲ԰�̓����蔻��̊Ǘ�
	bool hitCheck = false;
	
};