#include "Obstracle.h"
#include "GameTask.h"
#include "ImageMng.h"

Obstracle::Obstracle()
{
	pos = { (float)SCREEN_SIZE_X / 2,(float)SCREEN_SIZE_Y};
	speed = 5.0f;
}

Obstracle::~Obstracle()
{
}

void Obstracle::Update()
{
	//オブストラクルRECTの初期値を設定
	o.left = pos.x - size.x / 2;
	o.right = pos.x + size.x / 2;
	o.top = pos.y - size.y / 2;
	o.bottom = pos.y + size.y / 2;
	SetMove();
	//矩形のサイズを再設定
	int o_width = o.right - o.left;
	int o_height = o.bottom - o.top;
	SetRect(&o,pos.x - size.x / 2, pos.y - size.y / 2,
			   pos.x + o_width / 2, pos.y + o_height / 2);
	//矩形のサイズを描画(デバッグ用)
	DrawBox(o.left,o.top, o.right, o.bottom, GetColor(255, 0, 0), false);
}

void Obstracle::Draw()
{
	DrawGraph(pos.x - size.x/2, pos.y - size.y/2, IMAGE_ID(imageName),true);
	DrawLine(pos.x, pos.y - SCREEN_SIZE_Y, pos.x, pos.y+ SCREEN_SIZE_Y, GetColor(255, 255, 255), true);
}

void Obstracle::SetMove()
{
	pos.y += speed;
	if (pos.y > SCREEN_SIZE_Y) {	//画面外（下）に行ったら座標を画面の上に変更
		pos.y = SCREEN_SIZE_Y - SCREEN_SIZE_Y;
		pos.x = GetRand(SCREEN_SIZE_X);
	}
}

RECT  &Obstracle::GetRect()
{
	return this->o;
}
