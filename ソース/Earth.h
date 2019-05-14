#pragma once
#include "BasePlanet.h"

constexpr unsigned int EarthMax = 20;
class Earth :
	public BasePlanet
{
public:
	Earth(VECTOR3 pos);
	~Earth();

private:
	VECTOR3 mPos = { 0,0 };
	double earthSize = 3.0;
	float Size = 0;
	int EarthImage[EarthMax] = { 0 };
	int earthCnt = 0;
	int animCnt = 0;

protected:
	void Init(void);
	void Update(void);
	void Draw(void);
};

