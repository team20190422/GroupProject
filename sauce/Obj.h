#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "VECTOR2.h"
#include "KeyMng.h"
#include "VECTOR3.h"

class Obj
{
public:
	//Obj();
	Obj(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Obj();
	
	void init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, float speed);
	virtual void Update(void);			//	�X�V����
	virtual void Draw(void);			//	�`��p

	const VECTOR2& GetSize(void);
	void SetSize(const VECTOR2& divSize);

	virtual bool SetPos(VECTOR3 pos);
	virtual const VECTOR3& GetPos(void);

	virtual bool SetAngle(float Angle);
	virtual const float& GetAngle(void);

private:

	VECTOR2 divSize = { 0,0 };			//	�`�����߂̻���
	VECTOR2 divCnt = { 0,0 };			//	�`�����߂̐�
	VECTOR2 chipOffset = { 0,0 };			//	�`�����߂̲Ұ��ID�̊J�n�ʒu

protected:
	virtual void SetMove(void);
	std::string imageName;

	VECTOR3 pos = { 0,0 };			//	�`��ʒu
	VECTOR2 drawOffset;
	float speed;						//	��߰��
	float Angle;
};

