#pragma once
#include"char.h"
#include"net.h"
#include<math.h>

//�e�̈ړ����x
constexpr auto BulettSpeedX = 6.0f;
constexpr auto BulettSpeedY = 6.0f;

char str[512]{ "null" };
int in{ 0 };//�f�[�^�̓ǂݎ��A�������݈ʒu�����p
int ActionID{ 0 };//�A�N�V����ID

Bulett::Bulett(int B_ID, float _x, float _y,float x,float y){
	img = LoadGraph("image\\Bulett.png");

	server_ID = B_ID;//�T�[�o�[ID
	vec.x = _x;
	vec.y = _y;

	pos.x = x;
	pos.y = y;

	objID = BULETT;
}

int Bulett::Action(list<unique_ptr<Base>>& base)
{
	pos.x += vec.x;
	pos.y += vec.y;

	ActionID = PLAYER_UPDATE;
	
	bool hitANYPL = false;

	//�I�u�W�F�N�g�̏���
	for (auto i = base.begin(); i != base.end(); i++) {
		
		if ((*i)->objID == ANYPLAYER)
		{
			Point anypst = ((AnyPlayer*)(*i).get())->pos;

			if (DistanceS(pos.x, pos.y, pos.x + 10.0f, pos.y - 10.0f, anypst.x, anypst.y, anypst.x + 10.0f, anypst.y - 10.0f))
			{
				hitANYPL = true;
			}
		}

	}
	for (auto i = base.begin(); i != base.end(); i++) {

		if ((*i)->objID == PLAYER)
		{
			((AnyPlayer*)(*i).get())->HP--;
		}

	}

	//�̈�O�ɍs���������
	if (WINDOW_WIDTH < pos.x + 10.0f)
	{
		FLAG = false;
	}
	else if (0.0f > pos.x - 10.0f)
	{
		FLAG = false;
	}
	else if (WINDOW_HEIGHT > pos.y + 10.0f)
	{
		FLAG = false;
	}
	else if (0.0f > pos.y - 10.0f)
	{
		FLAG = false;
	}

	return 0;
}

void Bulett::Draw()
{
	DrawGraphF(pos.x, pos.y, img, TRUE);
	
}