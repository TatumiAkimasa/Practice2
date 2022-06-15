#pragma once
#include "main.h"
#include"Hit.h"

//プレイヤークラス(クライアント）
class Player :public Base {
private:
public:
	//コンストラクタ
	Player(int S_ID);

	//ボタン情報
	int Button[8]{ 0, 0, 0, 0, 0, 0, 0, 0 };

	//位置
	Point pos{ 0,0 };
	//移動ベクトル
	Vector vec{ 0,0 };

	//ヒットポイント
	int HP{ 5 };

	bool isShot = false;

	//処理
	int Action(list<unique_ptr<Base>>& base,int NetHandle);
	//描画
	void Draw();

	//デストラクタ
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

	//位置
	Point pos{ 0,0 };
	//移動ベクトル
	Vector vec{ 0,0 };
	Bulett(float _x, float _y,float x,float y);

	int Action(list<unique_ptr<Base>>& base,int NetHandle);

	void Draw();
};