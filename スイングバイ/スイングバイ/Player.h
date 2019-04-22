#pragma once
#include "Obj.h"
#include "KeyMng.h"
class Player :
	public Obj
{
public:
	Player(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Player();
};

