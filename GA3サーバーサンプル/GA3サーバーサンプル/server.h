#pragma once
#include "char.h"

//接続プレイヤーID
enum {
	Player1,
	Player2,
	Player3,
	Player4,
};

//プレイヤー管理データ
typedef struct Player_Data {
	//プレイヤーデータ
	Player data[MAX_CONNECTION];

	//ネットワークハンドル
	int NetHandle[MAX_CONNECTION]{ -1,-1,-1,-1 };

	//存在用フラグ
	int FLG[MAX_CONNECTION]{ -1,-1,-1,-1 };

}Player_Data;


//初回接続処理関数
//(リスト, 管理データ, プレイヤーID)
int Initial_Connection_Process(list<unique_ptr<Base>>& base, Player_Data* p, int ID);

//接続中の処理関数
//(リスト, プレイヤーID, 管理データ, 受信データ)
int Connection_Process(list<unique_ptr<Base>>& base, int ID, Player_Data* p, int DataLength);