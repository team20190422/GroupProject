#pragma once
#include "VECTOR3.h"
#include <vector>
#include <array>

constexpr unsigned int stageMax = 2;

// ˆê–Ê
std::vector<VECTOR3> non = {
	VECTOR3(150, 200) ,
	VECTOR3(250, 100) ,
	VECTOR3(200, 0),
	VECTOR3(150,-200),
	VECTOR3(150,-500),
	VECTOR3(300,-600),
};

// “ñ–Ê
std::vector<VECTOR3> planetSet = { 
	VECTOR3(200, 200) ,
	VECTOR3(300, 0) ,
	VECTOR3(50,-100),
	VECTOR3(150,-300),
	VECTOR3(150,-500),
	VECTOR3(300,-900),
	VECTOR3(200,-1200)
};

std::vector<VECTOR3> stageSet[] = { non,planetSet };
std::vector<VECTOR3> targetSet = { VECTOR3(50, -320),VECTOR3(50, -750) };
