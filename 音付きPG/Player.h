#pragma once
#include "Obj.h"
#include "KeyMng.h"
#include "GameTask.h"
#include <array>
#include <list>

typedef std::shared_ptr<Obj> particle_ptr;
typedef std::list<particle_ptr> particle_List;

typedef std::list<std::shared_ptr<Obj>> sideParticleList;

// ｽﾋﾟｰﾄﾞの最大値
constexpr float speedMax = 3.0f;

// ﾊﾟｰﾃｨｸﾙの最大値
constexpr unsigned int particleMax = 30;

class Player :
	public Obj
{
public:
	Player(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Player();

	void Draw(void);
	void Update(void);

	VECTOR3 Abstract(VECTOR3 i);
	VECTOR3 OneVec(VECTOR3 vec);

	bool SetPos(VECTOR3 pos);
	const VECTOR3& GetPos(void);

	VECTOR3 AddVec(VECTOR3,VECTOR3);

	RECT  &GetRect();
	bool& GetDeathFlag();
	void SetDeathFlag(bool flag);

	RECT p;

private:
	void SetMove(void);


	std::list<particle_ptr>::iterator AddObjlist(particle_ptr && objPtr);
	std::list<particle_ptr>::iterator particle;
	std::list<std::shared_ptr<Obj>>::iterator sideParticle;

	particle_List particleList;
	sideParticleList sideParticleList;


	std::array<int, particleMax> particleTime = { 0 };	// ﾊﾟｰﾃｨｸﾙの表示時間

	VECTOR3 posMax = { 0,600 };							// 端
	VECTOR3 pos = { 0,0 };
	VECTOR3 size = { 64 / 2, 32 / 1 };
	VECTOR3 radianPos = { 0,0 };						// ﾌﾟﾚｲﾔｰの前方の座標
	VECTOR3 turnPos = { 0,0 };							// ﾌﾟﾚｲﾔｰの左右の座標
	VECTOR3 vec = { 0,-1 };								// ﾌﾟﾚｲﾔｰのﾍﾞｸﾄﾙ
	VECTOR3 gVec = { 0,0 };								// 重力
	int animCnt = 0;									//アニメーションカウント
	float count = -3.0f;								//　前方座標のｵﾌｾｯﾄ
	float Angle = 0;									// 回転角度
	float speed = 0.5f;									// ｽﾋﾟｰﾄﾞ
	float distance;										// ﾌﾟﾚｲﾔｰから惑星までの距離の大きさ
	float EofG = 1.5f;									// 重力の影響
	int sideCheck = 0;									// 左右のﾊﾟｰﾃｨｸﾙのﾁｪｯｸ
	bool MaxFlag = false;
	bool DeathFlag;
};

