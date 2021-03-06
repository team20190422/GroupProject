#pragma once
#include "Obj.h"

class BasePlanet 
	:public Obj{
public:
	BasePlanet();
	~BasePlanet();
	void Draw();
	int HitCheck(VECTOR3,VECTOR3, VECTOR3, VECTOR3, float);
	const float& GetDistance();
	const float& GetGravity();
	const VECTOR3& GetVec();
private:

	struct Vec2 {
		float x,y;
	};

	int width, hight;
	const int(&j)[7] = { 0 };
	VECTOR3 playerPos = { 0,0 };
	VECTOR3 playerPosC = { 0,0 };		// playerPosの中心座標
	float playerAngle = 0.0f;
	Vec2 hit = {0,0};

	VECTOR3 planetPosC = { 0,0 };		// planetPosの中心座標
	VECTOR3 nearPos = { 0,0 };
	float distance = 0.0f;
	float gravity = 0.0f;


protected:
	float g, r = { 0.0f };
	int image;
	bool PlanetFactry(float, float, VECTOR3);
	int GetRadius(int);

};

