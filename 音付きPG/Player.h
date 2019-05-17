#pragma once
#include "Obj.h"
#include "KeyMng.h"
#include "GameTask.h"
#include <array>
#include <list>

typedef std::shared_ptr<Obj> particle_ptr;
typedef std::list<particle_ptr> particle_List;

typedef std::list<std::shared_ptr<Obj>> sideParticleList;

// ��߰�ނ̍ő�l
constexpr float speedMax = 3.0f;

// �߰è�ق̍ő�l
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


	std::array<int, particleMax> particleTime = { 0 };	// �߰è�ق̕\������

	VECTOR3 posMax = { 0,600 };							// �[
	VECTOR3 pos = { 0,0 };
	VECTOR3 size = { 64 / 2, 32 / 1 };
	VECTOR3 radianPos = { 0,0 };						// ��ڲ԰�̑O���̍��W
	VECTOR3 turnPos = { 0,0 };							// ��ڲ԰�̍��E�̍��W
	VECTOR3 vec = { 0,-1 };								// ��ڲ԰���޸��
	VECTOR3 gVec = { 0,0 };								// �d��
	int animCnt = 0;									//�A�j���[�V�����J�E���g
	float count = -3.0f;								//�@�O�����W�̵̾��
	float Angle = 0;									// ��]�p�x
	float speed = 0.5f;									// ��߰��
	float distance;										// ��ڲ԰����f���܂ł̋����̑傫��
	float EofG = 1.5f;									// �d�͂̉e��
	int sideCheck = 0;									// ���E���߰è�ق�����
	bool MaxFlag = false;
	bool DeathFlag;
};

