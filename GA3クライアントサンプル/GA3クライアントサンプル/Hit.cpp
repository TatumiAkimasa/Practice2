#include"Hit.h"

//playerに当たったら消す
//二点間距離計算（四角同士）
//S1x,S1y　→自身のポジション情報の引数
//S2x,S2y　→相手のポジション情報の引数
//S1mx,S1my→自身のポジション情報の引数。xの場合は+していって、yの場合は-していっく。
//S2mx,S2my→相手のポジション情報の引数。xの場合は+していって、yの場合は-していっく。
bool DistanceS(float S1x, float S1y, float S1mx, float S1my, float S2x, float S2y, float S2mx, float S2my)
{
	//縦横一括判定
	if (S1x <= S2mx && S2x <= S1mx && S1y <= S2my && S2y <= S1my)
	{
		return true;
	}
	else
	{
		return false;
	}
}