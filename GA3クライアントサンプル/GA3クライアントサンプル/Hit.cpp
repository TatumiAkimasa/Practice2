#include"Hit.h"

//player�ɓ������������
//��_�ԋ����v�Z�i�l�p���m�j
//S1x,S1y�@�����g�̃|�W�V�������̈���
//S2x,S2y�@������̃|�W�V�������̈���
//S1mx,S1my�����g�̃|�W�V�������̈����Bx�̏ꍇ��+���Ă����āAy�̏ꍇ��-���Ă������B
//S2mx,S2my������̃|�W�V�������̈����Bx�̏ꍇ��+���Ă����āAy�̏ꍇ��-���Ă������B
bool DistanceS(float S1x, float S1y, float S1mx, float S1my, float S2x, float S2y, float S2mx, float S2my)
{
	//�c���ꊇ����
	if (S1x <= S2mx && S2x <= S1mx && S1y <= S2my && S2y <= S1my)
	{
		return true;
	}
	else
	{
		return false;
	}
}