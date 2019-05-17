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
	Obj();
	Obj(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Obj();
	
	void init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, float speed);
	virtual void Update(void);			//	�X�V����
	virtual void Draw(void);			//	�`��p

	virtual RECT &GetRect();			//�����蔻��̋�`�p

	virtual const int& GetTimer(void);	//���Ԏ擾�p

	const VECTOR2& GetSize(void);		//�T�C�Y��Ԃ�
	void SetSize(const VECTOR2& divSize);	//�T�C�Y���Z�b�g����

	virtual bool SetPos(VECTOR3 pos);		//���W���Z�b�g����
	virtual const VECTOR3& GetPos(void);	//���W���擾����

	virtual bool SetAngle(float Angle);		//�p�x���Z�b�g����
	virtual const float& GetAngle(void);	//�p�x���擾����

	virtual bool SetDistance(float distance);	//�������Z�b�g����
	virtual const float& GetDistance();			//�������擾����

	virtual const VECTOR3 & GetVec();			//Vec���擾����
	virtual bool SetVec(VECTOR3 vec);			//Vec���Z�b�g����

	virtual bool& GetDeathFlag();
	virtual void SetDeathFlag(bool flag);

	const VECTOR3 & Normalize(VECTOR3,float);	//���K��

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
	float Angle;					//�p�x
	float distance;					//����
	VECTOR3 Vec;
	bool DeathFlag;
};

