#pragma once
#include "char.h"
#include "net.h"

//�v���C���[�̈ړ����x
constexpr auto PlayerSpeedX = 5.0f;
constexpr auto PlayerSpeedY = 5.0f;

char str[512]{ "null" };
int in{ 0 };//�f�[�^�̓ǂݎ��A�������݈ʒu�����p
int ActionID{ 0 };//�A�N�V����ID

Player::Player(int S_ID) {
	img = LoadGraph("image\\player.png");

	server_ID = S_ID;//�T�[�o�[ID

	objID = PLAYER;
	
}

int Player::Action(list<unique_ptr<Base>>& base,int NetHandle)
{
	vec.x = 0.0f; vec.y = 0.0f;

	if (CheckHitKey(KEY_INPUT_LEFT)) vec.x = -PlayerSpeedX;
	if (CheckHitKey(KEY_INPUT_RIGHT)) vec.x = PlayerSpeedX;
	if (CheckHitKey(KEY_INPUT_DOWN)) vec.y = PlayerSpeedY;
	if (CheckHitKey(KEY_INPUT_UP)) vec.y = -PlayerSpeedY;
	if (CheckHitKey(KEY_INPUT_Z) == true)
	{
		base.emplace_back((unique_ptr<Base>)new Bulett(3.0f, 3.0f, pos.x, pos.y));
		isShot = true;
	}
	else
		isShot = false;
	


	//Z�Œe�Ăяo��
	//if (CheckHitKey(KEY_INPUT_Z))base.emplace_back((unique_ptr<Base>)new BULETT(pos, BULETT);

	pos.x += vec.x;
	pos.y += vec.y;

	//�ړ������ꍇ�A�ʒu�̍X�V���𑗐M
	if (vec.x != 0 || vec.y != 0||isShot==true) {
		in = 0;//�ǂݎ��ʒu������
		ActionID = PLAYER_UPDATE;

		//���M�f�[�^�̍쐬
		//�s��ID
		memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
		//�ʒu
		memcpy_s(str + in, sizeof(Point), &pos, sizeof(Point)); in += sizeof(Point);

		Vector a = { 3.0f,3.0f };

		//�ʒu
		memcpy_s(str + in, sizeof(Vector), &a, sizeof(Vector)); in += sizeof(Vector);

		memcpy_s(str + in, sizeof(bool), &isShot, sizeof(bool));

		//�T�[�o�[�ɑ��M
		NetWorkSend(NetHandle, str, sizeof(str));
	}

	return 0;
}

void Player::Draw()
{
	DrawGraphF(pos.x, pos.y, img, TRUE);
	DrawFormatStringF(pos.x, pos.y+64, GetColor(255, 255, 255), "ID=%d", server_ID);
}

// �x�N�g���̐��K��
Vector VecNormalize(Vector vec)
{
	vec.x = vec.x / (vec.x * vec.x + vec.y * vec.y);
	vec.y = vec.y / (vec.x * vec.x + vec.y * vec.y);

	return vec;
}