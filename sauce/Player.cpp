#include "Player.h"
#include "ImageMng.h"
#include "GameTask.h"


Player::Player(const int(&trgKey)[6], const int(&oldKey)[6]) :Obj(trgKey, oldKey)
{
	pos = { (float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y };
	radianPos = { pos.x,pos.y };
}


Player::~Player()
{
}

void Player::Draw(void)
{
	int mouseX, mouseY;

	GetMousePoint(&mouseX, &mouseY);

	Angle = (float)atan2(radianPos.y - pos.y, radianPos.x - pos.x) + 1.5f;

	radianPos.x = pos.x + (20 * cos(count / 2));
	radianPos.y = pos.y + (20 * sin(count / 2));

	/*DrawFormatStringF(10, 10, GetColor(255, 255, 255), "角度　%f", Angle);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "posX　%f  posY %f", pos.x , pos.y);
	DrawFormatString(10, 70, GetColor(255, 255, 255), "vecX　%f  vecY %f", vec.x, vec.y);
	DrawFormatString(10, 100, GetColor(255, 255, 255), "MposX　%f  MposY %f", mouseX,mouseY);
	DrawFormatString(10, 130, GetColor(255, 255, 255), "RdX　%f  RdY %f", radianPos.x, radianPos.y);
	DrawFormatString(10, 160, GetColor(255, 255, 255), "speed　%f", speed);*/

	DrawRotaGraph(pos.x, pos.y, 1.0, Angle, IMAGE_ID(imageName), true);
	//DrawGraph(pos.x, pos.y, IMAGE_ID(imageName), true);
	DrawLine(pos.x-16, pos.y, pos.x + 16, pos.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y -16, pos.x, pos.y + 16, GetColor(0, 255, 255), true);
	//DrawCircle(radianPos.x, radianPos.y,10, GetColor(255, 255, 255),true);

}

void Player::Update(void)
{
	SetMove();
}

float Player::Abstract(float i)
{

	return (i < 0 ? -i : i);
}

// 外側からplayerPosの情報更新があったときに使う
bool Player::SetPos(VECTOR3 pos)
{
	this->pos = pos;
	return true;
}

// Objで仮想関数になっているのでplayerのGetPosが呼ばれる。
const VECTOR3 & Player::GetPos(void)
{
	return this->pos;
}

bool Player::SetAngle(float Angle)
{
	this->Angle = Angle;
	return true;
}

const float & Player::GetAngle(void)
{
	return this->Angle;
}

void Player::SetMove(void)
{
	/*vec.x = cos(Angle) * vec.x + -sin(Angle) * vec.y;
	vec.y = sin(Angle) * vec.x + cos(Angle) * vec.y;*/

	//VECTOR front = VTransform(VGet(pos.x, pos.y, 1.0f),master);

	if (KeyMng::GetInstance().newKey[P1_SPACE])
	{
		if(speed < speedMax)
		speed += 0.1f;
	}

	if (KeyMng::GetInstance().newKey[P1_UP])
	{
		if(speed < speedMax)
		speed += 0.02f;
	}
	if (KeyMng::GetInstance().newKey[P1_DOWN])
	{
		if(speed > 0)
		speed -= 0.02f;
	}

	vec.x = (sin(Angle) * speed);
	vec.y = -(cos(Angle) * speed);

	pos += vec;

	if (KeyMng::GetInstance().newKey[P1_RIGHT])
	{
		count += 0.12f;
	}
	else if (KeyMng::GetInstance().newKey[P1_LEFT])
	{
		count -= 0.12f;
	}
	//SetPos(pos);
}

