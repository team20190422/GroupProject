#pragma once
#include "BasePlanet.h"

class Mars :
	public BasePlanet
{
public:
	Mars(VECTOR3 pos, int marsCnt);
	~Mars();	

private:
	VECTOR3 mPos = { 0,0 };
	double time = 0;
	int imageCnt = 0;
	int nextPlanet = 0;
	int planetImage = 0;
	int mokutekichi = 0;
	float gravity = 1.5f;
	VECTOR2 imageSize = { 0,0 };

protected:
	void Init();
	void Update();
	void Draw();

};

