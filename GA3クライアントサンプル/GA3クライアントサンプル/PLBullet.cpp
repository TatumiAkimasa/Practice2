#pragma once
#include"char.h"
#include"net.h"
#include<math.h>

//弾の移動速度
constexpr auto BulettSpeedX = 6.0f;
constexpr auto BulettSpeedY = 6.0f;

//char str[512]{ "null" };


PLBullet::PLBullet(float _x, float _y, float x, float y) {
	img = LoadGraph("image\\Bulett.png");

	server_ID = BULETT;

	vec.x = _x;
	vec.y = _y;

	pos.x = x;
	pos.y = y;

	objID = BULETT;
}

int PLBullet::Action(list<unique_ptr<Base>>& base, int a)
{
	pos.x += vec.x;
	pos.y += vec.y;

	ActionID = PLAYER_UPDATE;



	//オブジェクトの処理
	for (auto i = base.begin(); i != base.end(); i++) {

		if ((*i)->objID == ANYPLAYER)
		{
			Point anypst = ((AnyPlayer*)(*i).get())->pos;

			if (DistanceS(pos.x, pos.y, pos.x + 64.0f, pos.y + 64.0f, anypst.x, anypst.y, anypst.x + 64.0f, anypst.y + 64.0f))
			{
				FLAG = false;
			}
		}

	}


	//領域外に行ったら消す
	if (WINDOW_WIDTH < pos.x + 10.0f)
	{
		FLAG = false;
	}
	else if (-20.0f > pos.x - 10.0f)
	{
		FLAG = false;
	}
	else if (WINDOW_HEIGHT < pos.y + 10.0f)
	{
		FLAG = false;
	}
	else if (-20.0f > pos.y - 10.0f)
	{
		FLAG = false;
	}

	return 0;
}

void Bullet::Draw()
{
	DrawGraphF(pos.x, pos.y, img, TRUE);

}