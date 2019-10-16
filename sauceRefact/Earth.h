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
	VECTOR3 mPos = { 0,0 };				// 地球の座標
	double earthSize = 3.0;				// 地球のサイズ
	//float Size = 0;						
	int EarthImage[EarthMax] = { 0 };	// 地球のアニメーション画像格納用
	int planetImage = 0;				// 地球の大きさ取得用
	int animCnt = 0;					// 地球のアニメーションカウント
	float gravity = 2.0f;				// 地球の重力
	float mass = 7000.0f;				// 地球の質量

	UnivGravityCalc& univ;

protected:
	void Init(void);
	void Update(void);
	void Draw(void);
};

