#pragma once
#include "main.h"
#include"Hit.h"

//�v���C���[�N���X(�N���C�A���g�j
class Player :public Base {
private:
public:
	//�R���X�g���N�^
	Player(int S_ID);

	//�{�^�����
	int Button[8]{ 0, 0, 0, 0, 0, 0, 0, 0 };

	//�ʒu
	Point pos{ 0,0 };
	//�ړ��x�N�g��
	Vector vec{ 0,0 };

	//�q�b�g�|�C���g
	int HP{ 5 };

	bool isShot = false;

	//����
	int Action(list<unique_ptr<Base>>& base,int NetHandle);
	//�`��
	void Draw();

	//�f�X�g���N�^
	~Player() { DeleteGraph(img); };
};

class AnyPlayer :public Player {
private:
public:
	AnyPlayer(int S_ID) : Player(S_ID) 
	{
		img = LoadGraph("image\\any_player.png");

		server_ID = S_ID;
		
		objID = ANYPLAYER;
	};

	AnyPlayer(int S_ID, float _x, float _y) :Player(S_ID) 
	{
		img = LoadGraph("image\\any_player.png");

		server_ID = S_ID;

		pos.x = _x;
		pos.y = _y;

		objID = ANYPLAYER;
	}

	int Action(list<unique_ptr<Base>>& base, int NetHandle);
	void Draw();

	~AnyPlayer() { DeleteGraph(img); };
};

class Bulett :public Base
{
private:
public:

	//�ʒu
	Point pos{ 0,0 };
	//�ړ��x�N�g��
	Vector vec{ 0,0 };
	Bulett(float _x, float _y,float x,float y);

	int Action(list<unique_ptr<Base>>& base,int NetHandle);

	void Draw();
};