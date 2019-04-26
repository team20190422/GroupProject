#include "Player.h"
#include "ImageMng.h"
#include "GameTask.h"
#include "Particle.h"

Player::Player(const int(&trgKey)[6], const int(&oldKey)[6]) :Obj(trgKey, oldKey)
{
	particleList.clear();

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

	Angle = atan2(radianPos.y - pos.y, radianPos.x - pos.x) + 1.5f;

	radianPos.x = pos.x + (20 * cos(count / 2));
	radianPos.y = pos.y + (20 * sin(count / 2));

	turnPos.x = pos.x + (13 * cos(count / 2));
	turnPos.y = pos.y + (13 * sin(count / 2));

	/*VECTOR radian = VTransform(VGet(1, 0, 0), master);
	MATRIX tmp = MGetRotAxis(radian, Angle);
	master = MMult(master, tmp);*/
	/*DrawFormatStringF(10, 10, GetColor(255, 255, 255), "角度　%f", Angle);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "posX　%f  posY %f", pos.x , pos.y);
	DrawFormatString(10, 70, GetColor(255, 255, 255), "vecX　%f  vecY %f", vec.x, vec.y);
	DrawFormatString(10, 100, GetColor(255, 255, 255), "MposX　%f  MposY %f", mouseX,mouseY);
	DrawFormatString(10, 130, GetColor(255, 255, 255), "RdX　%f  RdY %f", radianPos.x, radianPos.y);
	DrawFormatString(10, 160, GetColor(255, 255, 255), "speed　%f", speed);
*/
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

	DrawRotaGraph(pos.x, pos.y, 1.0, Angle, IMAGE_ID(imageName), true);
	DrawLine(pos.x-16, pos.y, pos.x + 16, pos.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y -16, pos.x, pos.y + 16, GetColor(0, 255, 255), true);
	DrawCircle(turnPos.x, turnPos.y,2, GetColor(255, 255, 255),true);

}

void Player::Update(void)
{
	p.left = (long)(pos.x - size.x / 2);
	p.right = (long)(pos.x + size.x / 2);
	p.top = (long)(pos.y - size.y / 2);
	p.bottom = (long)(pos.y + size.y / 2);

	if (sideParticleList.size() > 0)
	{
		(*sideParticle)->SetPos(turnPos + VECTOR3((sideCheck == 0 ? 0 : (sideCheck == 1 ? -10 : 10)), 0));
	}
	//DrawBox(p.left, p.top, p.right, p.bottom, GetColor(255, 255, 255), true);
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
	// 比例:y=ax
	EofG = 0.5 * distance;
	vx = cos(EofG);
	vy = sin(EofG);
	gVec = GameTask::GetInstance().PandPvec;
	DrawFormatString(10, 350, GetColor(255, 255, 255), "EofG:%f", EofG);
	DrawFormatString(10, 380, GetColor(255, 255, 255), "gvecX:%f gvecY:%f", gVec.x, gVec.y);
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

VECTOR3 Player::AddVec()
{
	return this->vec = gVec + vec;
}

void Player::SetMove(void)
{
	bool particleFlag = false;
	bool sideFlag = false;
	float particleCheck = 1.0f;
	/*vec.x = cos(Angle) * vec.x + -sin(Angle) * vec.y;
	vec.y = sin(Angle) * vec.x + cos(Angle) * vec.y;*/

	//VECTOR front = VTransform(VGet(pos.x, pos.y, 1.0f),master);

	vec.x = sin(Angle);
	vec.y = -(cos(Angle));
	VECTOR3 i = Obj::Normalize(gVec, distance);
	AddVec();
	pos += (vec * speed);
	SetPos(pos);

	DrawFormatString(10, 190, GetColor(255, 255, 255), "Normal.x　%f,Normal.y　%f", i.x,i.y);

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

		//particle = AddObjlist(std::make_shared<Particle>(pos, vec));

		/*particle = AddObjlist(std::make_shared<Particle>(pos, VECTOR3(vec.x + 1.5f,vec.y)));
		particle = AddObjlist(std::make_shared<Particle>(pos, VECTOR3(vec.x - 1.5f, vec.y)));*/
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
			speed += 0.02f;
		}
		particleFlag = true;
		/*particle = AddObjlist(std::make_shared<Particle>(pos, VECTOR3(vec.x + 1.5f, vec.y)));
		particle = AddObjlist(std::make_shared<Particle>(pos, VECTOR3(vec.x - 1.5f, vec.y)));*/
	}
	if (KeyMng::GetInstance().newKey[P1_DOWN])
	{
		if (speed >= 0.05f)
		{
			speed -= 0.02f;
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
		count += 0.1f;
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
		count -= 0.1f;
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

	//DrawFormatString(10, 190, GetColor(255, 255, 255), "flag　%d", sideFlag);

}

std::list<particle_ptr>::iterator Player::AddObjlist(particle_ptr && objPtr)
{
	particleList.push_back(objPtr);
	auto itr = particleList.end();
	itr--;
	return itr;
}

