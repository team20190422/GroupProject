#pragma once
#include "BasePlanet.h"
class Earth :
	public BasePlanet
{
public:
	Earth();
	~Earth();

private:

protected:
	void Init();
	void Update();
	void Draw();
};

