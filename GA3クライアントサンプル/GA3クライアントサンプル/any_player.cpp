#pragma once
#include "char.h"
#include "net.h"

int AnyPlayer::Action(list<unique_ptr<Base>>& base, int NetHandle)
{
	if (HPany <= 0)
	{
		FLAG = false;
	}

	return 0;
}

void AnyPlayer::Draw()
{
	DrawGraphF(pos.x, pos.y, img, TRUE);
	DrawFormatStringF(pos.x, pos.y+64, GetColor(255, 255, 255), "ID=%d", server_ID);
	DrawFormatStringF(pos.x, pos.y, GetColor(255, 255, 255), "HP=%d", HPany);
}