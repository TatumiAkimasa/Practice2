#pragma once
#include "DxLib.h"
#include <list>
#include <memory>

using namespace std;

//FPS
constexpr auto FPS = 30;

//windowサイズ
constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;

//位置
typedef struct  Point {
	float x, y;
}Point;

//移動ベクトル
typedef struct Vector {
	float x, y;
}Vector;

//オブジェクトID
enum {
	PLAYER,
	ANYPLAYER,
	BULETT,
};

//ベースクラス
class Base {
private:
public:
	int img{ -1 };//画像
	int objID{ -1 };//オブジェクトID

	int server_ID{ -1 };//サーバーID

	bool FLAG{ true };//存在フラグ

	//処理
	virtual int Action(list<unique_ptr<Base>>& base,int NetHandle) = 0;
	
	//描画
	virtual void Draw() = 0;
};