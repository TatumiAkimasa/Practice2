#pragma once
#include "net.h"
#include "char.h"
#include <sstream>

//接続プレイヤーID
enum {
	Player1,
	Player2,
};

//プレイヤーデータ管理用
typedef struct Player_Data {
	//プレイヤーデータ
	Player data[MAX_CONNECTION];

	//ネットワークハンドル
	int NetHandle[MAX_CONNECTION]{ -1,-1,-1,-1 };

	//存在用フラグ
	int FLG[MAX_CONNECTION]{ -1,-1,-1,-1 };

}Player_Data;


//初回接続処理関数(サーバー用）
int Initial_Connection_Process();

//接続中の処理関数(サーバー用)
int Connection_Process();