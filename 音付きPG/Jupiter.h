#pragma once
#include "BasePlanet.h"
class Jupiter :
	public BasePlanet
{
public:
	Jupiter(VECTOR3 pos);
	~Jupiter();

private:
	VECTOR3 mPos = { 0,0 };
	double time = 0;
	int nextPlanet = 0;
	int planetImage = 0;
	float gravity = 1.5f;

protected:
	void Init();
	void Update();
	void Draw();

};

