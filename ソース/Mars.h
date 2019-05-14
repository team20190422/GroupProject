#pragma once
#include "BasePlanet.h"

class Mars :
	public BasePlanet
{
public:
	Mars(VECTOR3 pos);
	~Mars();	

private:
	VECTOR3 mPos = { 0,0 };
	double time = 0;
protected:
	void Init();
	void Update();
	void Draw();
};

