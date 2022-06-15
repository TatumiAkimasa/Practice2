//スレッドクラス
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
	
	//デストラクタ
	~Thread() { t->join(); };
};