#pragma once
#include "main.h"

//�v���C���[�N���X
class Player :public Base {
private:
public:
	//�R���X�g���N�^
	//Player();

	int Button[8]{ 0, 0, 0, 0, 0, 0, 0, 0 };

	Point pos{ 0,0 };
	Vector vec{ 0,0 };

	int HP{ 5 };

	int Action(list<unique_ptr<Base>>& base) { return 0; };
	void Draw() {};

	~Player() { DeleteGraph(img); };
};