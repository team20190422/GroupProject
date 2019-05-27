#pragma once
#include "BasePlanet.h"

constexpr int ImageMax = 3;
class Asteroid :
	public BasePlanet
{
public:
	Asteroid(VECTOR3 pos, int AstCnt);
	~Asteroid();

private:
	VECTOR3 mPos = { 0,0 };
	double asteroidSize = 3.0;
	int imageSize = 0;
	float Size = 0;
	float gravity = 1.1f;
	int AsteroidImage[ImageMax] = { 0 };
	int planetImage[ImageMax] = { 0 };

	int animNum = 0;

protected:
	void Init(void);
	void Update(void);
	void Draw(void);

};

