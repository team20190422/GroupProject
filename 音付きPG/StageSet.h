#pragma once
#include "VECTOR3.h"
#include <vector>
#include <array>

constexpr unsigned int stageMax = 2;

// ˆê–Ê
std::vector<VECTOR3> planetSet = {
	VECTOR3(150, 200) ,
	VECTOR3(250, 100) ,
	VECTOR3(200, 0),
	VECTOR3(150,-200),
	VECTOR3(150,-500),
	VECTOR3(300,-600),
};

// “ñ–Ê
std::vector<VECTOR3> planetSet2 = { 
	VECTOR3(200, 200) ,
	VECTOR3(300, 0) ,
	VECTOR3(50,-100),
	VECTOR3(150,-300),
	VECTOR3(150,-500),
	VECTOR3(300,-900),
	VECTOR3(200,-1200)
};

// ŽO–Ê
std::vector<VECTOR3> planetSet3 = {
	VECTOR3(210, 300) ,
	VECTOR3(50, 200) ,
	VECTOR3(300, 90) ,
	VECTOR3(150, 0) ,
	VECTOR3(300,-100),
	VECTOR3(200,-300),
	VECTOR3(50,-500),
	VECTOR3(300,-700),
	VECTOR3(190,-900),
	VECTOR3(40,-1200),
	VECTOR3(300,-1400),
	VECTOR3(100,-1800),
	VECTOR3(230,-2000)
};

std::vector<VECTOR3> stageSet[] = { planetSet,planetSet2,planetSet3 };
std::vector<VECTOR3> targetSet = { VECTOR3(50, -320),VECTOR3(50, -750), VECTOR3(150,-1500) };
