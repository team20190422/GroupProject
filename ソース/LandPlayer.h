#pragma once
#include "Obj.h"
#include "GameTask.h"

class LandPlayer :
	public Obj
{
public:
	LandPlayer(const int(&trgKey)[6], const int(&oldKey)[6]);
	~LandPlayer();

	void Draw(void);
	void Update(void);

};

