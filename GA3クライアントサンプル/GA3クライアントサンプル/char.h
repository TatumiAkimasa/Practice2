#pragma once
#include "main.h"
#include"Hit.h"

//�v���C���[�N���X(�N���C�A���g�j
class Player :public Base {
private:
	//���W�Ɠ�]�������̏��
	struct PosAndDistance
	{
		float distance;
		Point pos;
	};
public:
	//�R���X�g���N�^
	Player(int S_ID);


	Point GetPoint() { return pos; };
	Vector GetVector() { return vec; };
	float Distance2Pos(Point myPos, Point yourPos);
	Vector VecNormalize(Vector vec);

	//�{�^�����
	int Button[8]{ 0, 0, 0, 0, 0, 0, 0, 0 };

	//�ʒu
	Point pos{ 0,0 };
	//�ړ��x�N�g��
	Vector vec{ 0,0 };
	//�e�̃x�N�g��
	Vector BulletVec{ 0,0 };
	//�G�̈ʒu�Ɠ�]������
	PosAndDistance EnemyPosInfo{ 0,{0,0} };

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
	bool AnyisShot = false;
public:

	Point GetPoint() { return pos; };
	Vector GetVector() { return vec; };


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

	void AnyShot(bool a)
	{
		isShot = a;
	}
};

class Bullet :public Base
{
private:
public:
	int in{ 0 };//�f�[�^�̓ǂݎ��A�������݈ʒu�����p

	int ActionID{ 0 };//�A�N�V����ID

	//�ʒu
	Point pos{ 0,0 };
	//�ړ��x�N�g��
	Vector vec{ 0,0 };


	Bullet(float _x, float _y,float x,float y);

	int Action(list<unique_ptr<Base>>& base,int NetHandle);

	void Draw();
};