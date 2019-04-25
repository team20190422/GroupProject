#pragma once
#include "Obj.h"

class BasePlanet 
	:public Obj{
public:
	BasePlanet();
	~BasePlanet();
	void Draw();
	int HitCheck(VECTOR3,VECTOR3, VECTOR3, VECTOR3, float);
private:

	struct Vec2 {
		float x,y;
	};

	int width, hight;
	const int(&j)[6] = { 0 };
	VECTOR3 playerPos = { 0,0 };
	VECTOR3 playerPosC = { 0,0 };		// playerPosの中心座標
	float playerAngle = 0.0f;
	Vec2 hit = {0,0};

	VECTOR3 planetPosC = { 0,0 };		// planetPosの中心座標
	VECTOR3 nearPos = { 0,0 };

protected:
	float g,r;
	int image;
	int PlanetFactry(float, float, VECTOR3);
	int GetRadius(int);

};

