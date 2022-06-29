#pragma once
#include "char.h"
#include "net.h"

int AnyPlayer::Action(list<unique_ptr<Base>>& base, int NetHandle)
{
	if (isShot)
	{
		if (!AnyisShot)
		{
			base.emplace_back((unique_ptr<Base>)new Bullet(vec.x, vec.y, pos.x, pos.y));
			AnyisShot = true;
		}
	}
	else
		AnyisShot = false;

	return 0;
}

void AnyPlayer::Draw()
{
	DrawGraphF(pos.x, pos.y, img, TRUE);
	DrawFormatStringF(pos.x, pos.y+64, GetColor(255, 255, 255), "ID=%d", server_ID);
}