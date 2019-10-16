#pragma once
#include "BasePlanet.h"

constexpr int ImageMax = 3;		// ���f���摜(3���)

class UnivGravityCalc;
class Asteroid :
	public BasePlanet
{
public:
	Asteroid(VECTOR3 pos, int AstCnt,UnivGravityCalc& u);
	~Asteroid();

	const VECTOR3 & GetPos(void);	// ���f���̍��W�擾�p
	bool SetPos(VECTOR3 pos);		// ���f���̍��W�i�[�p

private:
	VECTOR3 mPos = { 0,0 };		// �ڕW�f���̍��W
	double asteroidSize = 3.0;	// ���f���̃T�C�Y
	float gravity = 1.3f;		// ���f���̈��͂̋���
	float mass = 3000.0f;		// ���f���̎���
	int AsteroidImage[ImageMax] = { 0 };	// ���f���摜�i�[�p
	int planetImage[ImageMax] = { 0 };		// �ڕW�f���摜�i�[�p
	int animNum = 0;						// �摜�I��p
	int astCount = 0;						// ���f���̌��i�[�p
	static std::vector<float>distance;		// PtoP(Player to Planet)�i�[�p

	UnivGravityCalc& univ;

protected:
	void Init(void);
	void Update(void);
	void Draw(void);
};

