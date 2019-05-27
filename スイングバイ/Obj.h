#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "VECTOR2.h"
#include "KeyMng.h"
#include "VECTOR3.h"

constexpr unsigned int PLAYER_SIZE = 32;

class Obj
{
public:
	Obj();
	Obj(const int (&trgKey)[KEY_MAX], const int (&oldKey)[KEY_MAX]);
	~Obj();
	
	void init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, float speed);
	virtual void Update(void);			//	�X�V����
	virtual void Draw(void);			//	�`��p

	virtual RECT &GetRect();			//�����蔻��̋�`�p

	virtual const int& GetTimer(void);

	const VECTOR2& GetSize(void);
	void SetSize(const VECTOR2& divSize);

	virtual bool SetPos(VECTOR3 pos);
	virtual const VECTOR3& GetPos(void);

	virtual bool SetAngle(float Angle);
	virtual const float& GetAngle(void);

	virtual bool SetDistance(float distance);
	virtual const float& GetDistance();

	virtual const VECTOR3 & GetVec();
	virtual bool SetVec(VECTOR3 vec);

	const VECTOR3 & Normalize(VECTOR3,float);


private:

	VECTOR2 divSize = { 0,0 };			//	�`�����߂̻���
	VECTOR2 divCnt = { 0,0 };			//	�`�����߂̐�
	VECTOR2 chipOffset = { 0,0 };			//	�`�����߂̲Ұ��ID�̊J�n�ʒu
	RECT rect;								//�����蔻��̋�`�̑傫��

protected:
	virtual void SetMove(void);
	std::string imageName;

	VECTOR3 pos = { 0,0 };			//	�`��ʒu
	VECTOR2 drawOffset;
	float speed;						//	��߰��
	float Angle;
	float distance;
	VECTOR3 Vec;
};

