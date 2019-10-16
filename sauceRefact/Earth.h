#pragma once
#include "BasePlanet.h"

class UnivGravityCalc;

constexpr unsigned int EarthMax = 20;
class Earth :
	public BasePlanet
{
public:
	Earth(VECTOR3 pos,UnivGravityCalc& u);
	~Earth();

	const VECTOR3 & GetPos(void);
	bool SetPos(VECTOR3 pos);


private:
	VECTOR3 mPos = { 0,0 };				// �n���̍��W
	double earthSize = 3.0;				// �n���̃T�C�Y
	//float Size = 0;						
	int EarthImage[EarthMax] = { 0 };	// �n���̃A�j���[�V�����摜�i�[�p
	int planetImage = 0;				// �n���̑傫���擾�p
	int animCnt = 0;					// �n���̃A�j���[�V�����J�E���g
	float gravity = 2.0f;				// �n���̏d��
	float mass = 7000.0f;				// �n���̎���

	UnivGravityCalc& univ;

protected:
	void Init(void);
	void Update(void);
	void Draw(void);
};

