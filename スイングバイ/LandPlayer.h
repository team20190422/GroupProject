#pragma once
#include "Obj.h"
#include "GameTask.h"

class LandPlayer :
	public Obj
{
public:
	LandPlayer(const int(&trgKey)[6], const int(&oldKey)[6]);
	~LandPlayer();

	void Draw(void);
	void Update(void);
	void SetMove(void);

private:
	bool sinFlag = false;
	bool injectionFlag = false;
	bool shieldFlag = true;
	bool separateFlag = false;

	int count = 0;
	int colCnt = 1;
	int colTmp = 200;
	int colTmp2 = 200;
	int cupsule = 0;
	int planet = 0;
	int capsuleShield = 0;
	int spCraft = 0;
	int landMap = 0;
	int capsulePara[10] = { 0 };
	int capsuleParaL = 0;
	int color = 0;
	int colorPos = 0;
	int animCnt = 0;
	int anim = 0;
	int tmp;
	int RGB[3] = {154,96,61 + 30};
	int lrFlag = 0;										// -1:����] 0:�����l 1:�E��]			
	
	float countF = 0.0f;
	float size = 4.0f;
	float vx = 0.0f;
	float vy = 0.0f;
	float angle = 0.0f;
	float shieldAngle = 0.0f;
	float paraAngle = 0.0f;
	float spCAngle = 0.0f;
	float spCAngleF = 0.0f;								// spaceCraft�̍ŏI�p�x
	float rolInc = 0.0f;
	float speed = 0.0f;

	VECTOR3 motherPos = { 0,0 };
	VECTOR3 cupPos = {0,0};
	VECTOR3 shieldPos = { 0,0 };
	VECTOR3 paraPos = {SCREEN_SIZE_X/ 2, -100 };
};

