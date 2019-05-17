#include "Player.h"
#include "ImageMng.h"
#include "Particle.h"

VECTOR2 dsize = { 80,65 };
VECTOR2 dnum = { 9,1 };

Player::Player(const int(&trgKey)[6], const int(&oldKey)[6]) :Obj(trgKey, oldKey)
{
	particleList.clear();
	MaxFlag = false;
	DeathFlag = false;
	pos = { (float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y - (float)SCREEN_SIZE_Y / 3 };
	radianPos = { pos.x,pos.y };
	animCnt = 0;
	ImageMng::GetInstance().SetID("bom", "image/爆発.png", dsize,dnum);
}


Player::~Player()
{
}

void Player::Draw(void)
{

	Angle = atan2(radianPos.y - pos.y, radianPos.x - pos.x) + 1.5f;

	turnPos.x = pos.x + (13 * cos(count / 2));
	turnPos.y = pos.y + (13 * sin(count / 2));

	//DrawFormatString(10, 160, GetColor(255, 255, 255), "speed　%f", speed);

	for (auto itr : particleList)
	{
		itr->Draw();
		itr->Update();

	}
	for (auto itr : sideParticleList)
	{
		itr->Draw();
		itr->Update();
	}
	if (DeathFlag == false) {
		DrawRotaGraph(pos.x, pos.y, 1.0, Angle, IMAGE_ID(imageName), true);
	}
	DrawLine(pos.x-16, pos.y, pos.x + 16, pos.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y -16, pos.x, pos.y + 16, GetColor(0, 255, 255), true);
	DrawCircle(turnPos.x, turnPos.y,2, GetColor(255, 255, 255),true);

	SetFontSize(25);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(5);	// ﾌｫﾝﾄの太さ
	ChangeFont("Ailerons");
	animCnt++;
	if (DeathFlag == true) {
		ImageMng::GetInstance().DrawImage("bom", pos.x - size.x, pos.y - size.y / 2, animCnt / 10 % 10, true);
	}

	// UI
	DrawGraph(10, 10, IMAGE_ID("image/speedUI_Left.png"), true);
	DrawGraph(SCREEN_SIZE_X - 160, 10, IMAGE_ID("image/speedUI_Right.png"), true);
	DrawExtendGraph(5, 15, 145, 45, IMAGE_ID("image/speed.png"), true);
	DrawExtendGraph(240, 10, 380, 50, IMAGE_ID("image/distance.png"), true);
	DrawFormatString(90, 10, GetColor(255, 255, 255), ":%.2f", speed);
	DrawFormatString(SCREEN_SIZE_X - SCREEN_SIZE_X / 6 - 5, 10, GetColor(255, 255, 255), ":%d", (int)distance);
	SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("MSゴシック");
}

void Player::Update(void)
{
	radianPos.x = pos.x + (100 * cos(count / 2));
	radianPos.y = pos.y + (100 * sin(count / 2));

	p.left = (long)(pos.x - size.x / 2);
	p.right = (long)(pos.x + size.x / 2);
	p.top = (long)(pos.y - size.y / 2);
	p.bottom = (long)(pos.y + size.y / 2);

	if (sideParticleList.size() > 0)
	{
		(*sideParticle)->SetPos(turnPos + VECTOR3((sideCheck == 0 ? 0 : (sideCheck == 1 ? -10 : 10)), 0));
	}
	if (!lpGameTask.GetHitCheck())
	{
		SetMove();
	}
	else 
	{
		for (int i = 0; i < particleMax; i++)
		{
			if (particleList.size() > 0)
			{
				if (!(particleList.empty()))
				{
					particleList.pop_front();
				}
			}
		}
	}
	distance = GameTask::GetInstance().distance;
	gVec = GameTask::GetInstance().PandPvec;
	/*DrawFormatString(10, 350, GetColor(255, 255, 255), "EofG:%f", EofG);
	DrawFormatString(10, 380, GetColor(255, 255, 255), "gvecX:%f gvecY:%f", gVec.x, gVec.y);*/
}

RECT  &Player::GetRect()
{
	return this->p;
}

bool & Player::GetDeathFlag()
{
	return this->DeathFlag;
}

void Player::SetDeathFlag(bool flag)
{
	if (flag == true) {
		DeathFlag = true;
	}
	else {
		DeathFlag = false;
	}
}

VECTOR3 Player::Abstract(VECTOR3 i)
{
	return VECTOR3((i.x < 0 ? -0.5 : i.x == 0 ? 0 : 0.5),(i.y < 0 ? -0.5 : i.y == 0 ? 0 : 0.5));
}

VECTOR3 Player::OneVec(VECTOR3 vec)
{
	return VECTOR3(vec.x == 0 ? 0 : (vec.x < 0 ? -1 : 1), vec.y == 0 ? 0 : (vec.y < 0 ? -1 : 1));
}

bool Player::SetPos(VECTOR3 pos)
{
	this->pos = pos;
	return true;
}

const VECTOR3 & Player::GetPos(void)
{
	return this->pos;
}

VECTOR3 Player::AddVec(VECTOR3 pTop,VECTOR3 fTop)
{
	return this->vec = pTop + fTop;
}

void Player::SetMove(void)
{
	bool particleFlag = false;
	bool sideFlag = false;
	float particleCheck = 1.0f;
	// 単位ベクトル1
	//Obj::Normalize(gVec, distance);
	// 単位ベクトル2
	float a = abs(radianPos.x - pos.x);
	float b = abs(radianPos.y - pos.y);
	float vecMgn = sqrt((a * a) + (b * b));
	/////////////
	auto addVec = AddVec((Obj::Normalize((gVec), distance) * EofG), vec);// Obj::Normalize(vec, vecMgn));
	SetVec(addVec);

	//DrawFormatString(10, 350, GetColor(255, 255, 255), "addVecX:%f addVecY:%f", addVec.x,addVec.y);
	if (MaxFlag)
	{
		lpGameTask.SetScrollPos(-(addVec * speed));
		MaxFlag = false;
	}

	if (pos.y >= posMax.y - addVec.y)
	{
		MaxFlag = true;
		pos.x += addVec.x * speed;
	}
	else
	{
		pos.x += addVec.x * speed;
		MaxFlag = true;
	}
	SetPos(pos);

	DrawLine(radianPos.x, radianPos.y, pos.x, pos.y, 0x0000ff, true);
	DrawCircle(pos.x, pos.y, 10, 0x0000ff);

	for (int i = 0; i < particleMax; i++)
	{
		particleTime[i]++;
	}

	if (KeyMng::GetInstance().trgKey[P1_SPACE])
	{
		//particleTime++;
		
		if (speed < speedMax)
		{
			speed += 3.0f;
		}

		particleFlag = true;
		particleCheck = 5.0f;
		vec.x = sin(Angle);
		vec.y = -(cos(Angle));

	}
	else if (KeyMng::GetInstance().newKey[P1_SPACE])
	{
		particleFlag = true;
		particleCheck = 5.0f;

	}
	else if (KeyMng::GetInstance().newKey[P1_UP])
	{
		if (speed < speedMax)
		{
			speed += 0.01f;
		}
		particleFlag = true;
		vec.x = sin(Angle);
		vec.y = -(cos(Angle));

	}
	if (KeyMng::GetInstance().newKey[P1_DOWN])
	{
		if (speed >= 0.05f)
		{
			speed -= 0.03f;
		}
	}
	if (particleFlag)
	{
		float parMax = (KeyMng::GetInstance().newKey[P1_SPACE] ? 2.0f : 2.9f);
		for (float f = 0.0; f <parMax; f += 0.1)
		{
			particle = AddObjlist(std::make_shared<Particle>(pos, (vec*f)*particleCheck,0));
		}
	}

	VECTOR3 sideVec(radianPos - pos);

	// 角度変更
	if (KeyMng::GetInstance().newKey[P1_RIGHT])
	{
		count += 0.05f;
		sideFlag = true;
		sideCheck = 1;
		if (sideParticleList.size() <=0)
		{
			sideParticleList.push_back(std::make_shared<Particle>(turnPos, VECTOR3(0, 0), 1));
			sideParticle = sideParticleList.end();
			sideParticle--;
		}
	}
	else if (KeyMng::GetInstance().newKey[P1_LEFT])
	{
		count -= 0.05f;
		sideFlag = true;
		sideCheck = 2;
		if (sideParticleList.size() <= 0)
		{
			sideParticleList.push_back(std::make_shared<Particle>(turnPos, VECTOR3(0, 0), 2));
			sideParticle = sideParticleList.end();
			sideParticle--;
		}

	}
	else
	{
		sideFlag = false;
		sideCheck = 0;
		if (sideParticleList.size() > 0)
		{
			if (!(sideParticleList.empty()))
			{
				sideParticleList.pop_front();

			}
		}
	}

	if (speed > speedMax)
	{
		speed -= 0.1f;
	}

	//　ｴﾝｼﾞﾝﾊﾟｰﾃｨｸﾙの消去
	for (int i = 0; i < particleMax; i++)
	{
		if (particleList.size() > 0)
		{

			if ((*particle)->GetTimer() > 0 || particleTime[0] > 12)
			{

 				if (!(particleList.empty()))
				{
					particleList.pop_front();

				}
			}
		}
		else
		{
			particleTime[i] = 0;
		}
	}
	if (DeathFlag == true) {
		speed = 0.0f;
	}
}

std::list<particle_ptr>::iterator Player::AddObjlist(particle_ptr && objPtr)
{
	particleList.push_back(objPtr);
	auto itr = particleList.end();
	itr--;
	return itr;
}

