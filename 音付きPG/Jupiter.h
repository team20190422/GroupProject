#pragma once
#include "BasePlanet.h"
class Jupiter :
	public BasePlanet
{
public:
	Jupiter();
	~Jupiter();

private:

protected:
	void Init();
	void Update();
	void Draw();
};

