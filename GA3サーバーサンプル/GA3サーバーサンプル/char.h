#pragma once
#include "main.h"

//プレイヤークラス
class Player :public Base {
private:
public:
	//コンストラクタ
	//Player();

	int Button[8]{ 0, 0, 0, 0, 0, 0, 0, 0 };

	Point pos{ 0,0 };
	Vector vec{ 0,0 };

	int HP{ 5 };

	bool barst=false;

	int Action(list<unique_ptr<Base>>& base) { return 0; };
	void Draw() {};

	~Player() { DeleteGraph(img); };
};

//ふｃきょう

class Bullet :public Base {
private:
public:
	//コンストラクタ
	//Player();

	
	Vector vec{ 0,0 };


	int Action(list<unique_ptr<Base>>& base) { return 0; };
	void Draw() {};

	~Bullet() { DeleteGraph(img); };
};