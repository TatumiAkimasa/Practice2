//�X���b�h�N���X
#pragma once
#include "main.h"
#include <thread>

using namespace std;

class Thread {
private:
public:
	thread* t = new thread([&]() 
		{

		}
	);
	
	//�f�X�g���N�^
	~Thread() { t->join(); };
};