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

	Angle = (double)atan2(radianPos.y - pos.y, radianPos.x - pos.x) + 1.5f;

	radianPos.x = pos.x + (20 * cos(count / 2));
	radianPos.y = pos.y + (20 * sin(count / 2));

	/*VECTOR radian = VTransform(VGet(1, 0, 0), master);
	MATRIX tmp = MGetRotAxis(radian, Angle);
	master = MMult(master, tmp);*/
	DrawFormatStringF(10, 10, GetColor(255, 255, 255), "角度　%f", Angle);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "posX　%f  posY %f", pos.x , pos.y);
	DrawFormatString(10, 70, GetColor(255, 255, 255), "vecX　%f  vecY %f", vec.x, vec.y);
	DrawFormatString(10, 100, GetColor(255, 255, 255), "MposX　%f  MposY %f", mouseX,mouseY);
	DrawFormatString(10, 130, GetColor(255, 255, 255), "RdX　%f  RdY %f", radianPos.x, radianPos.y);
	DrawFormatString(10, 160, GetColor(255, 255, 255), "speed　%f", speed);

	DrawRotaGraph(pos.x, pos.y, 1.0, Angle, IMAGE_ID(imageName), true);
	DrawLine(pos.x-16, pos.y, pos.x + 16, pos.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y -16, pos.x, pos.y + 16, GetColor(0, 255, 255), true);
	//DrawCircle(radianPos.x, radianPos.y,10, GetColor(255, 255, 255),true);

}

void Player::Update(void)
{
	//プレイヤーRECTの初期値を設定
	p.left = pos.x - size.x / 2;
	p.right = pos.x + size.x / 2;
	p.top = pos.y - size.y / 2;
	p.bottom = pos.y + size.y / 2;
	SetMove();
	//矩形のサイズを再設定(プレイヤー)
	int p_width = p.right - p.left;
	int p_height = p.bottom - p.top;
	SetRect(&p, pos.x - size.x / 2, pos.y - size.y / 2,
		        pos.x + p_width / 2,pos.y + p_height / 2);
	//矩形のサイズを描画(デバッグ用)
	DrawBox(p.left,p.top,p.right,p.bottom, GetColor(255,0,0), false);

}

//RECTの値を取得
RECT  &Player::GetRect()
{
	return this->p;
}

double Player::Abstract(double i)
{

	return (i < 0 ? -i : i);
}
//速度の値を取得
float & Player::GetSpeed()
{
	return this->speed;
}
//角度の値を取得
double & Player::GetAngle()
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
}

