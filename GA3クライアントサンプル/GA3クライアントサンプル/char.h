#pragma once
#include "main.h"
#include"Hit.h"

//プレイヤークラス(クライアント）
class Player :public Base {
private:
	//座標と二転換距離の情報
	struct PosAndDistance
	{
		float distance;
		Point pos;
	};
public:
	//コンストラクタ
	Player(int S_ID);


	Point GetPoint() { return pos; };
	Vector GetVector() { return vec; };
	float Distance2Pos(Point myPos, Point yourPos);
	Vector VecNormalize(Vector vec);

	//ボタン情報
	int Button[8]{ 0, 0, 0, 0, 0, 0, 0, 0 };

	//位置
	Point pos{ 0,0 };
	//移動ベクトル
	Vector vec{ 0,0 };
	//弾のベクトル
	Vector BulletVec{ 0,0 };
	//敵の位置と二転換距離
	PosAndDistance EnemyPosInfo{ 0,{0,0} };

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
	int in{ 0 };//データの読み取り、書き込み位置調整用

	int ActionID{ 0 };//アクションID

	//位置
	Point pos{ 0,0 };
	//移動ベクトル
	Vector vec{ 0,0 };


	Bullet(float _x, float _y,float x,float y);

	int Action(list<unique_ptr<Base>>& base,int NetHandle);

	void Draw();
};