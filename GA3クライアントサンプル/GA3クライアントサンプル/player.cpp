#pragma once
#include "char.h"
#include "net.h"

//プレイヤーの移動速度
constexpr auto PlayerSpeedX = 5.0f;
constexpr auto PlayerSpeedY = 5.0f;

char str[512]{ "null" };
int in{ 0 };//データの読み取り、書き込み位置調整用
int ActionID{ 0 };//アクションID

Player::Player(int S_ID) {
	img = LoadGraph("image\\player.png");

	server_ID = S_ID;//サーバーID

	objID = PLAYER;
	
}

int Player::Action(list<unique_ptr<Base>>& base,int NetHandle)
{
	vec.x = 0.0f; vec.y = 0.0f;

	if (CheckHitKey(KEY_INPUT_LEFT)) vec.x = -PlayerSpeedX;
	if (CheckHitKey(KEY_INPUT_RIGHT)) vec.x = PlayerSpeedX;
	if (CheckHitKey(KEY_INPUT_DOWN)) vec.y = PlayerSpeedY;
	if (CheckHitKey(KEY_INPUT_UP)) vec.y = -PlayerSpeedY;
	if (CheckHitKey(KEY_INPUT_Z) == true)		//ここで弾を発射
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

	//移動した場合、位置の更新情報を送信
	if (vec.x != 0 || vec.y != 0||isShot==true) {
		in = 0;//読み取り位置初期化
		ActionID = PLAYER_UPDATE;

		//送信データの作成
		//行動ID
		memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
		//位置
		memcpy_s(str + in, sizeof(Point), &pos, sizeof(Point)); in += sizeof(Point);

		Vector a = { 3.0f,3.0f };

		//位置
		memcpy_s(str + in, sizeof(Vector), &a, sizeof(Vector)); in += sizeof(Vector);

		memcpy_s(str + in, sizeof(bool), &isShot, sizeof(bool));

		//サーバーに送信
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

// ベクトルの正規化
Vector VecNormalize(Vector vec)
{
	vec.x = vec.x / (vec.x * vec.x + vec.y * vec.y);
	vec.y = vec.y / (vec.x * vec.x + vec.y * vec.y);

	return vec;
}


//float BHnear関数
//引数1  -> myPos（自身のポジション）
//引数2  -> yourPos（相手とか、比較したいオブジェクトのポジション）
//内容   -> 主人公と弾の二点間距離を計算し、その値を返す
float Distance2Pos(Point myPos, Point yourPos)
{
	float m_d;
	//三平方の定理で主人公との二点間距離を計算
	m_d = (yourPos.x - myPos.x) * (yourPos.x - myPos.x) + (yourPos.y - myPos.y) * (yourPos.y - myPos.y);
	m_d = sqrt(m_d);

	return m_d;
}
