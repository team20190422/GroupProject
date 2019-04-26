#include"DxLib.h"
#include "Chara_Base.h"
#include"ImageMng.h"
#include "KeyMng.h"
#include "Player.h"
#include "Field.h"

constexpr float speed = 1.5f;				//�E�H�[�N���[�V�������X�s�[�h
constexpr float runspeed = 4.5f;			//�_�b�V�����[�V�������X�s�[�h
constexpr float RSPEED_MAX = 1.5;			//�E�H�[�N�X�s�[�h�ő�l
constexpr float LSPEED_MAX = -1.5f;			//�E�H�[�N�X�s�[�h�ő�l
constexpr float RUN_RSPEED_MAX = 4.5f;		//�_�b�V���X�s�[�h�ő�l
constexpr float RUN_LSPEED_MAX = -4.5f;		//�_�b�V���X�s�[�h�ő�l

Player::Player()
{
	SystemInit();
	Init();
}

Player::~Player()
{

}

void Player::SystemInit()
{
	//�摜�o�^
	//�Î~�摜
	ImageMng::GetInstance().SetID("stop2", "image/stop.png");
	//�����i����&����)�摜
	VECTOR2 divSize = { 32,45 };
	VECTOR2 divNum = { 2,1 };
	ImageMng::GetInstance().SetID("move", "image/move.png", divSize, divNum);
	//�W�����v�摜
	VECTOR2 jdivSize = { 32,45 };
	VECTOR2 jdivNum = { 2,1 };
	ImageMng::GetInstance().SetID("jump", "image/jump.png", jdivSize, jdivNum);
	//�u���[�L�摜
	VECTOR2 bdivSize = {32,45 };
	VECTOR2 bdivNum = { 2,1 };
	ImageMng::GetInstance().SetID("brake", "image/brake.png", bdivSize, bdivNum);
	//�_���[�W�摜
	VECTOR2 ddivSize = { 32,45 };
	VECTOR2 ddivNum = { 3,1 };
	ImageMng::GetInstance().SetID("damage","image/damage.png",ddivSize,ddivNum);

}

void Player::Init()
{
	//�p�����[�^������
	animCnt = 0;						//�A�j���[�V�����p�J�E���g
	player.pos = { 250.0f,449.0f };		//�v���C���[�̍��W
	player.mov = { 0.0f,0.0f };			//�v���C���[�̈ړ��l
	player.tmp = { 0.0f,0.0f };			//�v���C���[�̒l���ꎞ�I�Ɏ��ϐ�
	jumppow = 0.0f;						//�W�����v�p���[
	pow = 15.0f;						//�W�����v�p���[
	G = 0.98f;							//�������̏d��
	player.size = { 32,45 };			//�v���C���[�̉摜�T�C�Y(�����G�Ɠ������[�V����)
	player.bsize = { 32,45 };			//�v���C���[�̉摜�T�C�Y(�u���[�L���[�V����)
	player.jsize = { 32,45 };			//�v���C���[�̉摜�T�C�Y(�W�����v���[�V����)
	player.dsize = { 32,45 };			//�v���C���[�̉摜�T�C�Y(�_���[�W���[�V����)

	//�t���O������
	player.walkFlag = false;			//false:�E�H�[�N���Ă��Ȃ�,ture;�E�H�[�N��
	player.lrFlag = false;				//false�E����,ture;������
	player.jumpFlag = false;			//false:�W�����v���Ă��Ȃ�,ture;�W�����v��
	player.brakeFlag = false;			//false:��u���[�L���,ture;�u���[�L���
	player.damageFlag = false;			//false:�_���[�W��H����Ă��Ȃ�,true:�_���[�W��H�����
	player.hitTFlag = false;			//false:�������Ă���,true:�������Ă��Ȃ�
	player.hitBFlag = false;			//false:�������Ă���,true:�������Ă��Ȃ�

	//RECT
	p.left = player.pos.x - player.size.x / 2;
	p.right = player.pos.x + player.size.x / 2;
	p.top = player.pos.y - player.size.y / 2;
	p.bottom = player.pos.y + player.size.y / 2;
}

void Player::Update()
{
	player.walkFlag = false;
	player.brakeFlag = false;

	//�E�H�[�N����
	if (KeyMng::GetInstance().newKey[P1_RIGHT]) {
		if (player.mov.x < RSPEED_MAX) {
			player.mov.x += speed;
		}
		player.walkFlag = true;
		player.lrFlag = false;
		player.brakeFlag = false;
		player.damageFlag = false;
		if (player.pos.x - player.size.x / 2 >= EndPos) {
			player.pos.x = StartPos;
		}
	}
	if (KeyMng::GetInstance().newKey[P1_LEFT]) {
		if (player.mov.x > LSPEED_MAX) {
			player.mov.x -= speed;
		}
		player.walkFlag=true;
		player.lrFlag = true;
		player.brakeFlag = false;
		player.damageFlag = false;
		if (player.pos.x + player.size.x / 2 <= StartPos) {
			player.pos.x = EndPos;
		}
	}
	//�_�b�V������
	if ((KeyMng::GetInstance().newKey[P1_RIGHT]) && (KeyMng::GetInstance().newKey[P1_LSHIFT])) {
		if (player.mov.x < RUN_RSPEED_MAX) {
			player.mov.x += speed;
		}
		player.lrFlag = false;
		player.brakeFlag = false;
		player.damageFlag = false;
	}
	if ((KeyMng::GetInstance().newKey[P1_LEFT]) && (KeyMng::GetInstance().newKey[P1_LSHIFT])) {
		if (player.mov.x > RUN_LSPEED_MAX) {
			player.mov.x -= speed;
		}     
		player.lrFlag = true;
		player.brakeFlag = false;
		player.damageFlag = false;
	}
	//�W�����v����
	if ((KeyMng::GetInstance().newKey[P1_SPACE]) && player.jumpFlag == false) {
		player.jumpFlag = true;
		player.damageFlag = false;
		player.hitBFlag = false;
		jumppow += pow;
	}
	if ((player.jumpFlag == true)||(player.hitBFlag == false)) {
		// ���������x��������
		jumppow -= G;
		// ��������
		player.pos.y -= jumppow;
	}

	// �����n�ʂɂ��Ă�����~�܂�
	if (player.hitBFlag == true) {
		player.jumpFlag = false;
		HitMapBottom();
		jumppow = 0.0f;
	}

	//��������
	if ((player.walkFlag == false)&&(player.mov.x < -0.01f)) {
		DrawBox(180, 10, 200, 10, GetColor(0, 0, 255), false);
		player.mov.x += 0.1f;
		player.brakeFlag = true;
	}
	if ((player.walkFlag == false)&&(player.mov.x > 0.01f)) {
		DrawBox(180, 10, 200, 10, GetColor(255, 0, 0), false);
		player.mov.x -= 0.1f;
		player.brakeFlag = true;
	}

	//�l���ꎞ�I�ɑ��
	player.tmp.x = player.pos.x + player.mov.x;
	player.tmp.y = player.pos.y + player.mov.y;
		
	//�ŏI�I�ȍ��W
	player.pos.x = player.tmp.x;
	player.pos.y = player.tmp.y;
}

void Player::Draw()
{
	//�Î~���[�V����
	if((player.walkFlag == false)&&(player.jumpFlag == false)&&(player.brakeFlag == false))
		ImageMng::GetInstance().DrawImage("stop2", player.pos.x - player.size.x / 2,
		    player.pos.y - player.size.y / 2, true, player.lrFlag);
	
	//�E�H�[�N���[�V����
	if ((player.walkFlag == true)&&(player.jumpFlag == false)&&(player.brakeFlag == false))
		ImageMng::GetInstance().DrawImage("move", player.pos.x - player.size.x / 2,
		    player.pos.y - player.size.y / 2, animCnt / 7 % 4, true, player.lrFlag);

	//�W�����v���[�V����
	if (player.jumpFlag == true) {
		ImageMng::GetInstance().DrawImage("jump", player.pos.x - player.jsize.x / 2,
			player.pos.y - player.jsize.y / 2, animCnt / 7 % 14, true, player.lrFlag);
	}

	////�u���[�L���[�V����
	if (player.brakeFlag == true){
		ImageMng::GetInstance().DrawImage("brake", player.pos.x - player.bsize.x / 2,
			player.pos.y - player.bsize.y / 2, animCnt / 7 % 2, true, player.lrFlag);
	}

	//�_���[�W���[�V����
	if (player.damageFlag == true) {
		ImageMng::GetInstance().DrawImage("damage", player.pos.x - player.dsize.x / 2,
			player.pos.y - player.dsize.y / 2, animCnt / 7  7, true, player.lrFlag);
	}
}

void Player::Damage()
{
	/*const float respawn = 250.0f;
	if (player.damageFlag == true) {
		player.pos.y =  respawn;
	}*/
}


void Player::HitMapTop()
{
	if (player.hitTFlag == true) {
		player.tmp.y = player.pos.y + MAP_CHIP_SIZE/2 ;
	}
}

void Player::HitMapBottom()
{
	if (player.hitBFlag == true) {
		player.tmp.y = player.pos.y - MAP_CHIP_SIZE/2;
	}
}



