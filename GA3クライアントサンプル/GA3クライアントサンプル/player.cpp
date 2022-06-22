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
	if (CheckHitKey(KEY_INPUT_Z) == true)		//�����Œe�𔭎�
	{
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->objID == ANYPLAYER)
			{
				PosAndDistance info=
				{
					Distance2Pos(pos, ((AnyPlayer*)(*i).get())->GetPoint()),
					((AnyPlayer*)(*i).get())->GetPoint()
				};
				
				if (info.distance < EnemyPosInfo.distance)
				{
					EnemyPosInfo = info;
				}
			}
		}

		Vector v{ 0,0 };
		float l = sqrtf((EnemyPosInfo.pos.x - pos.x) * (EnemyPosInfo.pos.x - pos.x) + (EnemyPosInfo.pos.y - pos.y));
		v.x = (EnemyPosInfo.pos.x - pos.x) / l * 3.0f;
		v.y = (EnemyPosInfo.pos.y - pos.y) / l * 3.0f;


		if (!isShot)
		{
			base.emplace_back((unique_ptr<Base>)new Bullet(v.x, v.y, pos.x, pos.y));
			isShot = true;
		}
	}
	else
	{
		isShot = false;
	}

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
	DrawFormatStringF(pos.x, pos.y , GetColor(255, 255, 255), "HP=%d", HP);
}

// �x�N�g���̐��K��
Vector VecNormalize(Vector vec)
{
	vec.x = vec.x / (vec.x * vec.x + vec.y * vec.y);
	vec.y = vec.y / (vec.x * vec.x + vec.y * vec.y);

	return vec;
}


//float BHnear�֐�
//����1  -> myPos�i���g�̃|�W�V�����j
//����2  -> yourPos�i����Ƃ��A��r�������I�u�W�F�N�g�̃|�W�V�����j
//���e   -> ��l���ƒe�̓�_�ԋ������v�Z���A���̒l��Ԃ�
float Distance2Pos(Point myPos, Point yourPos)
{
	float m_d;
	//�O�����̒藝�Ŏ�l���Ƃ̓�_�ԋ������v�Z
	m_d = (yourPos.x - myPos.x) * (yourPos.x - myPos.x) + (yourPos.y - myPos.y) * (yourPos.y - myPos.y);
	m_d = sqrt(m_d);

	return m_d;
}
