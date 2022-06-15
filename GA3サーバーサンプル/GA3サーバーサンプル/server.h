#pragma once
#include "char.h"

//�ڑ��v���C���[ID
enum {
	Player1,
	Player2,
	Player3,
	Player4,
};

//�v���C���[�Ǘ��f�[�^
typedef struct Player_Data {
	//�v���C���[�f�[�^
	Player data[MAX_CONNECTION];

	//�l�b�g���[�N�n���h��
	int NetHandle[MAX_CONNECTION]{ -1,-1,-1,-1 };

	//���ݗp�t���O
	int FLG[MAX_CONNECTION]{ -1,-1,-1,-1 };

}Player_Data;


//����ڑ������֐�
//(���X�g, �Ǘ��f�[�^, �v���C���[ID)
int Initial_Connection_Process(list<unique_ptr<Base>>& base, Player_Data* p, int ID);

//�ڑ����̏����֐�
//(���X�g, �v���C���[ID, �Ǘ��f�[�^, ��M�f�[�^)
int Connection_Process(list<unique_ptr<Base>>& base, int ID, Player_Data* p, int DataLength);