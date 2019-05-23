#include "KeyMng.h"


void KeyMng::Init()
{
	//フラグ全クリア
	for(int i=0;i<KEY_MAX;i++){
		newKey[i]=0;
		trgKey[i]=0;
		oldKey[i] = 0;
		upKey[i]=0;
	}
}

bool KeyMng::Update()
{
	//キー情報更新
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;	// 全部押していない事にする
		trgKey[i] = false;	// 全部押していない事にする
		upKey[i] = false;	// 全部押していない事にする
	}

	if (CheckHitKey(KEY_INPUT_UP)) newKey[P1_UP] = true;
	if (CheckHitKey(KEY_INPUT_DOWN)) newKey[P1_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_RIGHT)) newKey[P1_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_LEFT)) newKey[P1_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_SPACE)) newKey[P1_SPACE] = true;
	if (CheckHitKey(KEY_INPUT_RETURN)) newKey[P1_ENTER] = true;
	if (CheckHitKey(KEY_INPUT_LCONTROL))newKey[P1_LCtrl] = true;

	//p2
	//省略

	//トリガand アップ
	for (int i = 0; i < KEY_MAX; i++) {
		trgKey[i] = newKey[i] & ~oldKey[i];//トリガ
		upKey[i] = ~newKey[i] & oldKey[i];//アップ

		//次ループの準備
		oldKey[i] = newKey[i];
	}
	return true;
}
