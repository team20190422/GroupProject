#pragma once
#include "BasePlanet.h"

constexpr int ImageMax = 3;		// ¬˜f¯‰æ‘œ(3í—Ş)

class UnivGravityCalc;
class Asteroid :
	public BasePlanet
{
public:
	Asteroid(VECTOR3 pos, int AstCnt,UnivGravityCalc& u);
	~Asteroid();

	const VECTOR3 & GetPos(void);	// ¬˜f¯‚ÌÀ•Wæ“¾—p
	bool SetPos(VECTOR3 pos);		// ¬˜f¯‚ÌÀ•WŠi”[—p

private:
	VECTOR3 mPos = { 0,0 };		// –Ú•W˜f¯‚ÌÀ•W
	double asteroidSize = 3.0;	// ¬˜f¯‚ÌƒTƒCƒY
	float gravity = 1.3f;		// ¬˜f¯‚Ìˆø—Í‚Ì‹­‚³
	float mass = 3000.0f;		// ¬˜f¯‚Ì¿—Ê
	int AsteroidImage[ImageMax] = { 0 };	// ¬˜f¯‰æ‘œŠi”[—p
	int planetImage[ImageMax] = { 0 };		// –Ú•W˜f¯‰æ‘œŠi”[—p
	int animNum = 0;						// ‰æ‘œ‘I‘ğ—p
	int astCount = 0;						// ¬˜f¯‚ÌŒÂ”Ši”[—p
	static std::vector<float>distance;		// PtoP(Player to Planet)Ši”[—p

	UnivGravityCalc& univ;

protected:
	void Init(void);
	void Update(void);
	void Draw(void);
};

