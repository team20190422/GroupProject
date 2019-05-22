#pragma once
#include "Obj.h"
#include "GameTask.h"

class LandPlayer :
	public Obj
{
public:
	LandPlayer(const int(&trgKey)[7], const int(&oldKey)[7]);
	~LandPlayer();

	void Draw(void);
	void Update(void);

};

