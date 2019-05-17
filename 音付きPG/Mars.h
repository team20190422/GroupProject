#pragma once
#include "BasePlanet.h"

class Mars :
	public BasePlanet
{
public:
	Mars();
	~Mars();	
private:

protected:
	void Init();
	void Update();
	void Draw();
};

