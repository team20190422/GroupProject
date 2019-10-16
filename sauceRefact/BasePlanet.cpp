#include <DxLib.h>
#include <math.h>
#include "GameTask.h"
#include "BasePlanet.h"

constexpr int PLAYER_SIZE_X = 32;
constexpr int PLAYER_SIZE_Y = 32;

std::vector<float> BasePlanet::univG;

BasePlanet::BasePlanet():Obj(j,j)
{
	Init();
}

BasePlanet::~BasePlanet()
{
}

void BasePlanet::Init()
{
	width = 0;
	hight = 0;
	playerPos = { 0,0 };
	playerPosC = { 0,0 };
	playerAngle = 0.0f;

	orbitPosC = { 0,0 };

	planetPosC = { 0,0 };
	distance = 0.0f;
	gravity = 0.0f;
	orbitDistance = 0.0f;

	g = { 0.0f };
	r = { 0.0f };
	PtoP = { 0.0f,0.0f };	// PlayerToPlanet
	dist = 0.0f;			// PlayerToPlanet‚Ì‘å‚«‚³
}

void BasePlanet::Update()
{
}

int BasePlanet::GetRadius(int image)
{
	GetGraphSize(image, &width, &hight);
	return width / 2;
}

void BasePlanet::Draw()
{
	
}

const float & BasePlanet::GetDistance()
{
	return this->distance;
}

const float & BasePlanet::GetGravity()
{
	return this->gravity;
}

const float & BasePlanet::GetOrbitDistance()
{
	return this->orbitDistance;
}

const VECTOR3 & BasePlanet::GetVec()
{
	auto planetAngle = atan2(planetPosC.y - playerPosC.y, planetPosC.x - playerPosC.x) + 1.5f;
	VECTOR3 planetVec = { 0,0 };

	planetVec.x = sin(planetAngle);
	planetVec.y = -cos(planetAngle);
	
	GameTask::GetInstance().SetPlanetPos(planetPosC);
	return planetVec;
}

const VECTOR3 & BasePlanet::GetPos()
{
	return this->pos;
}


