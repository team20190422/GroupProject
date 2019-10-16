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
	const float& GetDistance();				// f―ΖvC[ΤΜ£πΎι
	const float& GetGravity();				// ΪWf―ΜdΝπΎι
	const float& GetOrbitDistance();		// vC[Μ\zOΉΜ_1Β1ΒΜ£πΎι
	const VECTOR3& GetVec();				// ΪWf―ΜxNgπΎι
	const VECTOR3& GetPos();				// ΪWf―ΜΐWπΎι

	static std::vector<float>univG;			// univGravityi[p

private:

	struct Vec2 {
		float x,y;
	};

	int width, hight;					// ζTCYζΎp
	const int(&j)[KEY_MAX] = { 0 };
	VECTOR3 playerPos = { 0,0 };
	VECTOR3 playerPosC = { 0,0 };		// playerPosΜSΐW
	float playerAngle = 0.0f;			// vC[Μρ]p		

	VECTOR3 orbitPosC = { 0,0 };		// orbitΜSΐW

	VECTOR3 planetPosC = { 0,0 };		// planetPosΜSΐW
	float distance = 0.0f;				// f―ΖvC[ΤΜ£i[p
	float gravity = 0.0f;				// f―ΜdΝi[p
	float orbitDistance = 0.0f;			// vC[Μ\zOΉΜ_1Β1ΒΜ£i[p

protected:
	float g, r = { 0.0f };				// f―ΜdΝAf―ΜΌa
	int image;							// ζTCYπΎιΫΙgp
	int GetRadius(int);					// ζΜΌͺΜTCY(f―ΜΌa)πΎι

	VECTOR3 PtoP = { 0.0f,0.0f };	// PlayerToPlanet
	float dist = 0.0f;				// PlayerToPlanetΜε«³
	static std::vector<VECTOR3>PtoPVector;		// PtoP(PlayerToPlanet)i[p
};
