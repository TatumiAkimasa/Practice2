#pragma once
#include "DxLib.h"
#include <list>
#include <memory>

using namespace std;

//window�T�C�Y
constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;

//�ʒu
typedef struct  Point {
	float x, y;
}Point;

//�ړ��x�N�g��
typedef struct Vector {
	float x, y;
}Vector;

//�x�[�X�N���X
class Base {
private:
public:
	int img{ -1 };//�摜
	int ID{ -1 };//�I�u�W�F�N�gID

	int server_ID{ -1 };//�T�[�o�[ID

	bool FLAG{ true };//���݃t���O

	//����
	virtual int Action(list<unique_ptr<Base>>& base) = 0;
	//�`��
	virtual void Draw() = 0;
};
