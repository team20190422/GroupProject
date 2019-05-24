#include "KeyMng.h"


void KeyMng::Init()
{
	//�t���O�S�N���A
	for(int i=0;i<KEY_MAX;i++){
		newKey[i]=0;
		trgKey[i]=0;
		oldKey[i] = 0;
		upKey[i]=0;
	}
}

bool KeyMng::Update()
{
	//�L�[���X�V
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;	// �S�������Ă��Ȃ����ɂ���
		trgKey[i] = false;	// �S�������Ă��Ȃ����ɂ���
		upKey[i] = false;	// �S�������Ă��Ȃ����ɂ���
	}

	if (CheckHitKey(KEY_INPUT_UP)) newKey[P1_UP] = true;
	if (CheckHitKey(KEY_INPUT_DOWN)) newKey[P1_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_RIGHT)) newKey[P1_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_LEFT)) newKey[P1_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_SPACE)) newKey[P1_SPACE] = true;
	if (CheckHitKey(KEY_INPUT_RETURN)) newKey[P1_ENTER] = true;
	if (CheckHitKey(KEY_INPUT_LCONTROL))newKey[P1_LCtrl] = true;

	//p2
	//�ȗ�

	//�g���Kand �A�b�v
	for (int i = 0; i < KEY_MAX; i++) {
		trgKey[i] = newKey[i] & ~oldKey[i];//�g���K
		upKey[i] = ~newKey[i] & oldKey[i];//�A�b�v

		//�����[�v�̏���
		oldKey[i] = newKey[i];
	}
	return true;
}
