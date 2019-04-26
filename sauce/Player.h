#pragma once
#include "Obj.h"
#include "KeyMng.h"
#include <array>
#include <list>

typedef std::shared_ptr<Obj> particle_ptr;
typedef std::list<particle_ptr> particle_List;

typedef std::list<std::shared_ptr<Obj>> sideParticleList;

// ΩÀﬂ∞ƒﬁÇÃç≈ëÂíl
constexpr double speedMax = 5.0f;

//  ﬂ∞√®∏ŸÇÃç≈ëÂíl
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

	VECTOR3 AddVec();

	RECT  &GetRect();

	RECT p;

private:
	std::list<particle_ptr>::iterator AddObjlist(particle_ptr && objPtr);

	particle_List particleList;
	std::list<particle_ptr>::iterator particle;
	sideParticleList sideParticleList;
	std::list<std::shared_ptr<Obj>>::iterator sideParticle;

	void SetMove(void);

	VECTOR3 pos = { 0,0 };
	VECTOR3 size = { 64 / 2, 32 / 1 };

	VECTOR3 radianPos = { 0,0 };
	VECTOR3 turnPos = { 0,0 };
	VECTOR3 vec = { 0,-1 };
	MATRIX master = { 0 };
	//int particleTime = 0;
	std::array<int, particleMax> particleTime = { 0 };
	float Angle = 0;
	float speed = 0.5f;
	float count = -3.0f;
	int sideCheck = 0;
	float distance;
	float EofG;		// èdóÕÇÃâeãø
	VECTOR3 gVec = { 0,0 };
	float vx;
	float vy;
};

