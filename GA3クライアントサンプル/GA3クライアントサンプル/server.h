#pragma once
#include "net.h"
#include "char.h"
#include <sstream>

//�ڑ��v���C���[ID
enum {
	Player1,
	Player2,
};

//�v���C���[�f�[�^�Ǘ��p
typedef struct Player_Data {
	//�v���C���[�f�[�^
	Player data[MAX_CONNECTION];

	//�l�b�g���[�N�n���h��
	int NetHandle[MAX_CONNECTION]{ -1,-1,-1,-1 };

	//���ݗp�t���O
	int FLG[MAX_CONNECTION]{ -1,-1,-1,-1 };

}Player_Data;


//����ڑ������֐�(�T�[�o�[�p�j
int Initial_Connection_Process();

//�ڑ����̏����֐�(�T�[�o�[�p)
int Connection_Process();