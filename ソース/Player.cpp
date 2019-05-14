#include "Player.h"
#include "ImageMng.h"
#include "Particle.h"

Player::Player(const int(&trgKey)[6], const int(&oldKey)[6]) :Obj(trgKey, oldKey)
{
	particleList.clear();
	MaxFlag = false;
	pos = { (float)SCREEN_SIZE_X / 2, (float)SCREEN_SIZE_Y - (float)SCREEN_SIZE_Y / 3 };
	radianPos = { pos.x,pos.y };
	plPos = pos;
}


Player::~Player()
{
}

void Player::Draw(void)
{

	Angle = atan2(radianPos.y - pos.y, radianPos.x - pos.x) + 1.5f;
	if (lpGameTask.setCount)
	{
		count -= 6.0f;
		vec = -vec;
		lpGameTask.setCount = false;
	}

	turnPos.x = pos.x + (13 * cos(count / 2));
	turnPos.y = pos.y + (13 * sin(count / 2));

	if (sideCheck)
	{
		sidePos.x = turnPos.x + ((13 * sin(-count / 2)) * (sideCheck == 2 ? 1 : -1));
		sidePos.y = turnPos.y + ((13 * cos(count / 2)) * (sideCheck == 2 ? 1 : -1));

	}
	else
	{
		sidePos.x = pos.x + (13 * cos(count / 2));
		sidePos.y = pos.y + (13 * sin(count / 2));
	}

	//DrawFormatString(10, 160, GetColor(255, 255, 255), "sideCheck　%d", sideCheck);


	//DrawFormatString(10, 650, GetColor(255, 255, 255), "count　%f", count);

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

	DrawRotaGraph(pos.x, pos.y, Size, Angle, IMAGE_ID(imageName), true);

	if (pos.x < -32)
	{
		lpGameTask.OutOfScreen = true;
		DrawTriangle(0, pos.y, 20, pos.y + 10, 20, pos.y - 10, 0xffffff, true);
		DrawCircle(40, pos.y, 32, GetColor(255, 255, 255), true);
		DrawRotaGraph(40, pos.y, 1.0, Angle, IMAGE_ID(imageName), true);
	}
	else if(pos.x > SCREEN_SIZE_X + PLAYER_SIZE)
	{
		lpGameTask.OutOfScreen = true;
		DrawTriangle(SCREEN_SIZE_X, pos.y, SCREEN_SIZE_X - 20, pos.y + 10, SCREEN_SIZE_X - 20, pos.y - 10, 0xffffff, true);
		DrawCircle(SCREEN_SIZE_X - 40, pos.y, 32, GetColor(255, 255, 255), true);
		DrawRotaGraph(SCREEN_SIZE_X - 40, pos.y, 1.0, Angle, IMAGE_ID(imageName), true);
	}
	else
	{
		lpGameTask.OutOfScreen = false;
	}

	DrawLine(pos.x-16, pos.y, pos.x + 16, pos.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y -16, pos.x, pos.y + 16, GetColor(0, 255, 255), true);

	DrawLine(pos.x, pos.y, newPrePos.x + pos.x,newPrePos.y + pos.y, GetColor(0, 255, 255), true);
	DrawLine(pos.x, pos.y, newPos.x, newPos.y, GetColor(0, 255, 0), true);


	/*DrawCircle(turnPos.x, turnPos.y,2, GetColor(255, 255, 255),true);
	DrawCircle(radianPos.x, radianPos.y, 2, GetColor(255, 255, 255), true);
	DrawCircle(newPos.x, newPos.y, 2, GetColor(255, 255, 255), true);
	DrawCircle(newPrePos.x + pos.x, newPrePos.y + pos.y, 2, GetColor(255, 255, 255), true);

	DrawCircle(sidePos.x, sidePos.y, 2, GetColor(255, 255, 0), true);*/

	SetFontSize(25);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(5);	// ﾌｫﾝﾄの太さ
	ChangeFont("Ailerons");

	// システムUI
	DrawGraph(10, 40, IMAGE_ID("image/speedUI_Left.png"), true);
	DrawGraph(10, 70, IMAGE_ID("image/speedUI_Left.png"), true);
	DrawBox(15, 120, 15 + (energy / 7), 130, GetColor(255, 55 + (energy / 5), 55 + (energy / 5)), true);
	DrawGraph(10, 100, IMAGE_ID("image/engine.png"), true);

	DrawExtendGraph(5, 35, 145, 65, IMAGE_ID("image/speed.png"), true);
	DrawExtendGraph(-50, 70, 90, 110, IMAGE_ID("image/distance.png"), true);
	DrawExtendGraph(5, 100, 145, 150, IMAGE_ID("image/fuel.png"), true);

	DrawFormatString(90, 30, GetColor(255, 255, 255), ":%.2f", speed);
	DrawFormatString(70, 60, GetColor(255, 255, 255), ":%d", (int)distance);
	DrawFormatString(60, 95, GetColor(255, 255, 255), ":%d", energy);


	SetFontSize(20);		// ﾌｫﾝﾄのｻｲｽﾞ
	SetFontThickness(8);	// ﾌｫﾝﾄの太さ
	ChangeFont("MSゴシック");
	
	if (energy < 0)
	{
		energy = 0;
	}
}

void Player::Update(void)
{
	radianPos.x = pos.x + (100 * cos(count / 2));
	radianPos.y = pos.y + (100 * sin(count / 2));


	float PreAngle = atan2(radianPos.y - pos.y, radianPos.x - pos.x) + 1.5f;
	float PreAngle2 = atan2(newPrePos.y, newPrePos.x) + 1.5f;

	
	newPos.x = (pos.x) + (50 * cos(newcount / 2));
	newPos.y = (pos.y) + (50 * sin(newcount / 2));

	DrawFormatString(10, 700, 0xffffff, "Angle1:%f Angle2:%f", PreAngle, PreAngle2);
	DrawFormatString(10, 750, 0xffffff, "newcount:%f", newcount);

	p.left = (long)(pos.x - size.x / 2);
	p.right = (long)(pos.x + size.x / 2);
	p.top = (long)(pos.y - size.y / 2);
	p.bottom = (long)(pos.y + size.y / 2);

	if (sideParticleList.size() > 0)
	{
		//(*sideParticle)->SetPos(turnPos + VECTOR3((sideCheck == 0 ? 0 : (sideCheck == 1 ? -10 : 10)), 0));
	}
	if (!lpGameTask.GetHitCheck())
	{
		if (lpGameTask.GetLandCheck())
		{
			speed = 0.13f;
			if (landingTime++ % 3 == 0)
			{
				Size -= 0.015f;
			}
			if (Size <= 0)
			{
				lpGameTask.landingFlag = true;
			}
		}
		else
		{
			if (Size != 1.0f)
			{
				Size = 1.0f;
			}
		}

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
		speed = 0;
		distance = 1000;
		gVec = VECTOR3(0,0);

	}
	lpGameTask.SetEnergy(energy);
	distance = GameTask::GetInstance().distance;
	gVec = GameTask::GetInstance().PandPvec;
	//DrawFormatString(10, 400, GetColor(255, 255, 255), "Angle:%ff", Angle);
	/*DrawFormatString(10, 350, GetColor(255, 255, 255), "EofG:%f", EofG);
	DrawFormatString(10, 380, GetColor(255, 255, 255), "gvecX:%f gvecY:%f", gVec.x, gVec.y);*/
}

RECT  &Player::GetRect()
{
	return this->p;
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
	plPos += lpGameTask.GetScrollPos();


	//DrawFormatString(10, 350, GetColor(255, 255, 255), "addVecX:%f addVecY:%f", addVec.x,addVec.y);
	if (MaxFlag && !lpGameTask.landingFlag && !lpGameTask.GetHitCheck())
	{
		if (plPos.y > playerPosMaxY)
		{
			lpGameTask.plPosMaxFlag = false;
			lpGameTask.SetScrollPos(-(addVec * speed));
		}
		else
		{
			lpGameTask.plPosMaxFlag = true;
			pos.y += (addVec.y * speed);
		}
		MaxFlag = false;
	}

	if (pos.y >= posMax.y - addVec.y)
	{
		MaxFlag = true;
		pos.x += addVec.x * speed;
	}
	else
	{
		pos.x += addVec.x *speed;
		MaxFlag = true;

	}
	SetPos(pos);

	DrawLine(radianPos.x, radianPos.y, pos.x, pos.y, 0x0000ff, true);

	for (int i = 0; i < particleMax; i++)
	{
		if (particleList.size() > 0)
			particleTime[0][i]++;

		/*if (sideParticleList.size() > 0)
			particleTime[sideCheck][playerTime]++;*/

	}

	if (KeyMng::GetInstance().trgKey[P1_SPACE] && energy > 0)
	{
		//particleTime++;
		
		if (speed < speedMax)
		{
			speed += 3.0f;
		}
		energy -= 100;

		particleFlag = true;
		particleCheck = 5.0f;
		vec.x = sin(Angle);
		vec.y = -(cos(Angle));

	}
	else if (KeyMng::GetInstance().newKey[P1_SPACE] && energy > 0)
	{
		particleFlag = true;
		particleCheck = 5.0f;
		newPrePos = (radianPos - pos);
		newPrecount = count;
		newcount = count;
	}

	else if (KeyMng::GetInstance().newKey[P1_UP] && energy > 0)
	{
		if (speed < speedMax)
		{
			speed += 0.01f;
		}
		particleFlag = true;
		vec.x = sin(Angle);
		vec.y = -(cos(Angle));
		newPrePos = (radianPos - pos);
		newPrecount = count;
		energy -= 1;
		//newcount = count;
		if (count != newcount)
		{
			if (count > newcount)
			{
				newcount += 0.01f;
			}
			else if (count < newcount)
			{
				newcount -= 0.01f;
			}
			else
			{

			}
		}

	}
	if (KeyMng::GetInstance().newKey[P1_DOWN] && energy > 0)
	{
		if (speed >= 0.05f)
		{
			speed -= 0.03f;
		}
	}
	

	VECTOR3 sideVec(radianPos - pos);

	// 角度変更
	if (!lpGameTask.GetLandCheck())
	{
		if (KeyMng::GetInstance().newKey[P1_RIGHT])
		{
			count += 0.05f;
			sideFlag = true;
			sideCheck = 1;
			newcount = newPrecount;
		}
		else if (KeyMng::GetInstance().newKey[P1_LEFT])
		{
			count -= 0.05f;
			sideFlag = true;
			sideCheck = 2;
			newcount = newPrecount;
		}
		else
		{
			//sideFlag = false;
			sideCheck = 0;
			if (sideParticleList.size() > 0)
			{
				if (!(sideParticleList.empty()))
				{
					sideParticleList.pop_front();

				}
			}
		}
	}
	else
	{

	}

	if (speed > speedMax)
	{
		speed -= 0.1f;
	}

	if (particleFlag && !lpGameTask.GetLandCheck())
	{
		float parMax = (KeyMng::GetInstance().newKey[P1_SPACE] ? 2.0f : 2.9f);
		for (float f = 0.0; f <parMax; f += 0.1)
		{
			particle = AddObjlist(std::make_shared<Particle>(VECTOR3(pos.x, pos.y - (10 * vec.y)), (vec*f)*particleCheck, 0));
		}
	}
	if (sideFlag && !lpGameTask.GetLandCheck())
	{
		for (float f = 0.0; f < 1.0; f += 0.1)
		{
			if (sidePos != turnPos)
			{
				sideParticleList.push_back(std::make_shared<Particle>(turnPos, OneVec(turnPos - sidePos), sideCheck));
				sideParticle = sideParticleList.end();
				sideParticle--;
			}
		}
	}

	//　ｴﾝｼﾞﾝﾊﾟｰﾃｨｸﾙの消去
	for (int i = 0; i < particleMax; i++)
	{
		if (particleList.size() > 0)
		{

			if (particleList.front()->GetTimer() > 12 || particleTime[0][0] > 12)
			{

 				if (!(particleList.empty()))
				{
					particleList.pop_front();

				}
			}
		}
		else
		{
			particleTime[0][i] = 0;
		}

		if (sideParticleList.size() > 0)
		{
			if (sideParticleList.front()->GetTimer() > 12)
			{
				if (!(sideParticleList.empty()))
				{
					sideParticleList.pop_front();
				}
			}
		}
		

	}
	if (sideParticleList.size() > 0)
	{
		//DrawFormatString(10, 600, 0xffffff, "%d", sideParticleList.front()->GetTimer());
	}
}

std::list<particle_ptr>::iterator Player::AddObjlist(particle_ptr && objPtr)
{
	particleList.push_back(objPtr);
	auto itr = particleList.end();
	itr--;
	return itr;
}

