#pragma once
#include "VECTOR2.h"//int�^
#include"VECTOR3.h"//float�^

typedef struct
{
	VECTOR3 pos, mov, tmp;
	VECTOR2 size, bsize, jsize,dsize;
	bool walkFlag;
	bool lrFlag;
	bool jumpFlag;
	bool brakeFlag;
	bool damageFlag;
	bool hitTFlag;
	bool hitBFlag;
}PLAYER;

class Player 
{
private:
	int animCnt;
	float jumppow, pow, G;
public:
	Player();
	~Player();
	void SystemInit();		//�摜�ǂݍ���
	void Init();			//�p�����[�^������
	void Update();			//�ړ�����
	void Draw();			//�`�揈��
	void Damage();			//���C�t�����������̏���
	void HitMapTop();		//�}�b�v�Ɠ����������̔���(���)
	void HitMapBottom();	//�}�b�v�Ɠ����������̔���(����)
	PLAYER player;
	RECT p;

	//����t���O��Ԃ�(�E�H�[�N)
	bool GetWalkFlag() {
		return player.walkFlag;
	}
	//�W�����v�t���O��Ԃ�
	bool GetJumpFlag() {
		return player.jumpFlag;
	}
	//�W�����v�t���O���Z�b�g����
	void SetJumpFlag(bool flag) {
		if (flag == true) {
			player.jumpFlag = true;//�W�����v��
		}
		else {
			player.jumpFlag = false;//�W�����v������Ȃ�
		}
	}
	//�u���[�L��ԃt���O��Ԃ�
	bool GetBrakeFlag() {
		return player.brakeFlag;
	}

	//���W��Ԃ�
	VECTOR3&GetPos() {
		return player.pos;
	}
	//pos���Z�b�g����
	VECTOR3& SetPos(VECTOR3 pos) {
		this->player.pos = pos;
		return pos;
	}

	//�ړ��l��Ԃ�
	VECTOR3&GetMov() {
		return player.mov;
	}
	//mov���Z�b�g����
	VECTOR3& SetMov(VECTOR3 mov) {
		this->player.mov = mov;
		return mov;
	}

	//tmp��Ԃ�
	VECTOR3&GetTmp() {
		return player.tmp;
	}

	//�Î~���ƈړ����̃T�C�Y��Ԃ�
	VECTOR2&GetSize() {
		return player.size;

	}

	//�u���[�L���[�V�����̊G�̃T�C�Y��Ԃ�
	VECTOR2&GetBSize() {
		return player.bsize;
	}

	//�W�����v���[�V�����̃T�C�Y��Ԃ�
	VECTOR2&GetJSize() {
		return player.jsize;
	}
	
	//�_���[�W�t���O��Ԃ�
	bool&GetDamageFlag() {
		return player.damageFlag;
	}

	//�_���[�W�t���O���Z�b�g����
	void SetDamageFlag(bool flag) {
		if (flag == true) {
			player.damageFlag = true;//�_���[�W��H�����
		}
		else {
			player.damageFlag = false;//�_���[�W��H����Ă��Ȃ�
		}
	}

	//�q�b�g�t���O��Ԃ�
	bool&GetHitBFlag() {
		return player.hitBFlag;
	}

	//�q�b�g�t���O���Z�b�g����
	void SetHitBFlag(bool flag) {
		if (flag == true) {
			player.hitBFlag = true;//�������Ă���
		}
		else {
			player.hitBFlag = false;//�������Ă��Ȃ�
		}
	}

	//�q�b�g�t���O��Ԃ�
	bool&GetHitTFlag() {
		return player.hitTFlag;
	}

	//�q�b�g�t���O���Z�b�g����
	void SetHitTFlag(bool flag) {
		if (flag == true) {
			player.hitTFlag = true;//�������Ă���
		}
		else {
			player.hitTFlag = false;//�������Ă��Ȃ�
		}
	}

	bool&GetLRFlag() {
		return player.lrFlag;
	}
};