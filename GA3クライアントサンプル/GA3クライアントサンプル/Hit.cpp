#include"Hit.h"

//player‚É“–‚½‚Á‚½‚çÁ‚·
	//“ñ“_ŠÔ‹——£ŒvZilŠp“¯mj
bool DistanceS(float S1x, float S1y, float S1mx, float S1my, float S2x, float S2y, float S2mx, float S2my)
{
	//c‰¡ˆêŠ‡”»’è
	if (S1x <= S2mx && S2x <= S1mx && S1y <= S2my && S2y <= S1my)
	{
		return true;
	}
	else
	{
		return false;
	}
}