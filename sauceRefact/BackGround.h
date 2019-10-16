#pragma once
#include "Obj.h"

//class GameTask;

class BackGround :public Obj
{
public:
	BackGround();
	~BackGround();

	void Init();
	void Update();
	void Draw();	

	bool removeFlag;	// 星の画面外時削除用
private:
	float vyS = 0;		// 星(小サイズ)のY座標移動用
	float vyM = 0;		// 星(中サイズ)のY座標移動用
	int randomX;		// ランダムX座標格納用
	int randomY;		// ランダムY座標格納用
	int count;			// 星の生成上限値設定用
	const int(&j)[KEY_MAX] = { 0 };
};