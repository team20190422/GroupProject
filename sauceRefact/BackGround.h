#pragma once
#include "Obj.h"

//class GameTask;

class BackGround :public Obj
{
public:
	BackGround();
	~BackGround();

	void Init();
	void Update();
	void Draw();	

	bool removeFlag;	// ���̉�ʊO���폜�p
private:
	float vyS = 0;		// ��(���T�C�Y)��Y���W�ړ��p
	float vyM = 0;		// ��(���T�C�Y)��Y���W�ړ��p
	int randomX;		// �����_��X���W�i�[�p
	int randomY;		// �����_��Y���W�i�[�p
	int count;			// ���̐�������l�ݒ�p
	const int(&j)[KEY_MAX] = { 0 };
};