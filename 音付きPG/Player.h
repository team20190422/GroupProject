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

//下方向の移動の最大値
constexpr int playerPosMaxY = -330;

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
	RECT p;

private:
	void SetMove(void);

	std::list<particle_ptr>::iterator AddObjlist(particle_ptr && objPtr);
	std::list<particle_ptr>::iterator particle;
	std::list<std::shared_ptr<Obj>>::iterator sideParticle;

	particle_List particleList;
	sideParticleList sideParticleList;

	std::vector<int> particleSizeMax = { 1,1,1 };

	std::array<std::array<int, particleMax>, 3> particleTime = { 0 };	// ﾊﾟｰﾃｨｸﾙの表示時間

	VECTOR3 posMax = { 0,600 };							// 端
	VECTOR3 pos = { (float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y - (float)SCREEN_SIZE_Y / 3 };
	VECTOR3 size = { 64 / 2, 32 / 1 };
	VECTOR3 radianPos = { 0,0 };						// ﾌﾟﾚｲﾔｰの前方の座標
	VECTOR3 turnPos = { 0,0 };							// ﾌﾟﾚｲﾔｰの左右の座標
	VECTOR3 sidePos = { 0,0 };
	VECTOR3 vec = { 0,-1 };								// ﾌﾟﾚｲﾔｰのﾍﾞｸﾄﾙ
	VECTOR3 gVec = { 0,0 };								// 重力
	VECTOR3 PreVec = { 0,0 };
	VECTOR3 plPos = { 0,0 };
	float count = -3.0f;								//　前方座標のｵﾌｾｯﾄ
	float rolInc = 0.0f;
	float Size = 1.0f;										// ｻｲｽﾞ
	float Angle = 0;									// 回転角度
	float speed = 0.5f;									// ｽﾋﾟｰﾄﾞ
	float distance;										// ﾌﾟﾚｲﾔｰから惑星までの距離の大きさ
	float EofG = 1.5f;									// 重力の影響
	int sideCheck = 0;									// 左右のﾊﾟｰﾃｨｸﾙのﾁｪｯｸ
	bool MaxFlag = false;
	int lrFlag = 0;
	VECTOR3 newPos = { 0,0 };
	VECTOR3 newPrePos = { 0,0 };
	float newPrecount = -3.0f;
	float newcount = -3.0f;

	float PreAngle;
	float PreAngle2;

	int energy = 1000;
	int landingTime = 0;
};

