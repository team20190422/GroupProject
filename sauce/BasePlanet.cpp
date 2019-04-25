#include <DxLib.h>
#include <math.h>
#include "GameTask.h"
#include "BasePlanet.h"

constexpr int PLAYER_SIZE_X = 32;
constexpr int PLAYER_SIZE_Y = 32;

BasePlanet::BasePlanet():Obj(j,j)
{
}

BasePlanet::~BasePlanet()
{
}

// 重力作成
//BasePlanet::PlanetFactry(惑星の重力, 惑星の半径, 惑星のpos)
int BasePlanet::PlanetFactry(float g, float r, VECTOR3 planetPos)
{
	// playerPosCをﾌﾟﾚｲﾔｰの中心座標に設定
	playerPosC = GameTask::GetInstance().playerPos;
	// playerPosをﾌﾟﾚｲﾔｰの左上座標に設定
	playerPos.x = playerPosC.x - (PLAYER_SIZE_X / 2);
	playerPos.y = playerPosC.y - (PLAYER_SIZE_Y / 2);
	// planetPosCを惑星の中心座標に設定
	planetPosC.x = planetPos.x;
	planetPosC.y = planetPos.y;

	planetPos.x = planetPosC.x - r;
	planetPos.y = planetPosC.y - r;
	// playerPosとplanetPosを結ぶ

	DrawCircle(planetPos.x, planetPos.y, 2, 0x0000ff, true);
	//DrawCircle(planetPosC.x, planetPosC.y, 100, 0xff0000, true);
	DrawCircle(playerPos.x, playerPos.y, 2, 0x0000ff, true);
	//DrawCircle(playerPosC.x, playerPosC.y, 20, 0xff0000, true);

	DrawBox(playerPos.x, playerPos.y, playerPos.x + 32, playerPos.y + 32, GetColor(255, 255, 255), true);
	DrawFormatString(10, 70, GetColor(255, 255, 255), "PposX　%f  PposY %f", playerPos.x, playerPos.y);
	DrawFormatString(10, 130, GetColor(255, 255, 255), "PLposX　%f  PLposY %f", planetPos.x, planetPos.y);

	if (HitCheck(playerPos, planetPos, playerPosC, planetPosC, r))
	{
		DrawString(playerPos.x, playerPos.y - 15, "hit!", 0xffffff, 0xffffff0);
	}
	return 0;
}

int BasePlanet::GetRadius(int image)
{
	GetGraphSize(image, &width, &hight);
	return width / 2;
}

void BasePlanet::Draw()
{
	
}

int BasePlanet::HitCheck(VECTOR3 playerPos,VECTOR3 planetPos, VECTOR3 playerPosC, VECTOR3 planetPosC, float r)
{
	// playerの回転角を取得
	playerAngle = GameTask::GetInstance().playerAngle;

	// 矩形の中心点を軸に円を回転させ、矩形0度の時の円の座標を求める。
	hit.x = cos(playerAngle) * (planetPos.x - playerPosC.x) - sin(playerAngle) * (planetPos.y - playerPosC.y) + playerPosC.x;
	hit.y = sin(playerAngle) * (planetPos.x - playerPosC.x) - cos(playerAngle) * (planetPos.y - playerPosC.y) + playerPosC.y;

	// 角度を戻した円の中心点から矩形へ一番近い点を求める。
	// X座標
	if (hit.x < playerPos.x)
	{
		nearPos.x = playerPos.x;
	}
	else if(hit.x > playerPos.x + PLAYER_SIZE_X)
	{
		nearPos.x = playerPos.x + PLAYER_SIZE_X;
	}
	else
	{
		nearPos.x = hit.x;
	}
	// Y座標
	if (hit.y < playerPos.y)
	{
		nearPos.y = playerPos.y;
	}
	else if(hit.y > playerPos.y + PLAYER_SIZE_Y)
	{
		nearPos.y = playerPos.y + PLAYER_SIZE_Y;
	}
	else
	{
		nearPos.y = hit.y;
	}

	//ﾋﾟﾀｺﾞﾗｽの定理
	float a = abs(hit.x - nearPos.x);
	float b = abs(hit.y - nearPos.y);

	float distance = sqrt((a * a) + (b * b));

	DrawFormatString(0, 300, 0xffffff, "%f", distance);

	if (distance < r)
	{
		return true;
	}
	else
	{
		return false;
	}
}
