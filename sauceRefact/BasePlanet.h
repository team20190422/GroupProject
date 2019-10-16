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
	const float& GetDistance();				// 惑星とプレイヤー間の距離を得る
	const float& GetGravity();				// 目標惑星の重力を得る
	const float& GetOrbitDistance();		// プレイヤーの予想軌道の点1つ1つの距離を得る
	const VECTOR3& GetVec();				// 目標惑星のベクトルを得る
	const VECTOR3& GetPos();				// 目標惑星の座標を得る

	static std::vector<float>univG;			// univGravity格納用

private:

	struct Vec2 {
		float x,y;
	};

	int width, hight;					// 画像サイズ取得用
	const int(&j)[KEY_MAX] = { 0 };
	VECTOR3 playerPos = { 0,0 };
	VECTOR3 playerPosC = { 0,0 };		// playerPosの中心座標
	float playerAngle = 0.0f;			// プレイヤーの回転角		

	VECTOR3 orbitPosC = { 0,0 };		// orbitの中心座標

	VECTOR3 planetPosC = { 0,0 };		// planetPosの中心座標
	float distance = 0.0f;				// 惑星とプレイヤー間の距離格納用
	float gravity = 0.0f;				// 惑星の重力格納用
	float orbitDistance = 0.0f;			// プレイヤーの予想軌道の点1つ1つの距離格納用

protected:
	float g, r = { 0.0f };				// 惑星の重力、惑星の半径
	int image;							// 画像サイズを得る際に使用
	int GetRadius(int);					// 画像の半分のサイズ(惑星の半径)を得る

	VECTOR3 PtoP = { 0.0f,0.0f };	// PlayerToPlanet
	float dist = 0.0f;				// PlayerToPlanetの大きさ
	static std::vector<VECTOR3>PtoPVector;		// PtoP(PlayerToPlanet)格納用
};
