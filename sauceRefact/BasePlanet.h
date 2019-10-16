#pragma once
#include "Obj.h"

constexpr float PLAYER_MASS = 0.01f;

class BasePlanet 
	:public Obj{
public:
	BasePlanet();
	~BasePlanet();
	void Init();
	void Update();
	void Draw();
	const float& GetDistance();				// �f���ƃv���C���[�Ԃ̋����𓾂�
	const float& GetGravity();				// �ڕW�f���̏d�͂𓾂�
	const float& GetOrbitDistance();		// �v���C���[�̗\�z�O���̓_1��1�̋����𓾂�
	const VECTOR3& GetVec();				// �ڕW�f���̃x�N�g���𓾂�
	const VECTOR3& GetPos();				// �ڕW�f���̍��W�𓾂�

	static std::vector<float>univG;			// univGravity�i�[�p

private:

	struct Vec2 {
		float x,y;
	};

	int width, hight;					// �摜�T�C�Y�擾�p
	const int(&j)[KEY_MAX] = { 0 };
	VECTOR3 playerPos = { 0,0 };
	VECTOR3 playerPosC = { 0,0 };		// playerPos�̒��S���W
	float playerAngle = 0.0f;			// �v���C���[�̉�]�p		

	VECTOR3 orbitPosC = { 0,0 };		// orbit�̒��S���W

	VECTOR3 planetPosC = { 0,0 };		// planetPos�̒��S���W
	float distance = 0.0f;				// �f���ƃv���C���[�Ԃ̋����i�[�p
	float gravity = 0.0f;				// �f���̏d�͊i�[�p
	float orbitDistance = 0.0f;			// �v���C���[�̗\�z�O���̓_1��1�̋����i�[�p

protected:
	float g, r = { 0.0f };				// �f���̏d�́A�f���̔��a
	int image;							// �摜�T�C�Y�𓾂�ۂɎg�p
	int GetRadius(int);					// �摜�̔����̃T�C�Y(�f���̔��a)�𓾂�

	VECTOR3 PtoP = { 0.0f,0.0f };	// PlayerToPlanet
	float dist = 0.0f;				// PlayerToPlanet�̑傫��
	static std::vector<VECTOR3>PtoPVector;		// PtoP(PlayerToPlanet)�i�[�p
};
