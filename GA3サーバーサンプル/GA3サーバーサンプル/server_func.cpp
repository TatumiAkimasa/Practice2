#pragma once
#include "main.h"
#include "net.h"
#include "server.h"

char str[512]{ "null" };
int in{ 0 };//データの読み取り、書き込み位置調整用
int ActionID{ 0 };//アクションID

//初回接続処理関数
//(リスト, 管理データ, プレイヤーID)
//登録完了の場合「1」を返す
int Initial_Connection_Process(list<unique_ptr<Base>>& base, Player_Data* p, int ID)
{
	//接続したネットワークハンドルを取得
	int GetHandle = GetNewAcceptNetWork();

	//接続があった場合の処理
	if (GetHandle != -1)
	{
		//リスト更新
		//ネットワークハンドルの登録
		(*p).NetHandle[ID] = GetHandle;//ネットワークハンドルを登録

		//IDの送信
		//接続のあったネットワークにサーバーの登録IDを送信
		char setID[4];
		sprintf_s(setID, "%d", ID);//IDを文字に変換
		NetWorkSend((*p).NetHandle[ID], &setID, sizeof(ID));//IDを送信

		//リストの存在フラグをONにする
		(*p).FLG[ID] = 1;

		//初期位置設定
		(*p).data[ID].pos.x = 0.0f;
		(*p).data[ID].pos.y = 0.0f;

		//他のプレイヤーに接続を知らせる
		for (int i = 0; i < MAX_CONNECTION; i++) {
			if (i != ID && (*p).NetHandle[i] != -1) {
				in = 0;
				//送信データの作成
				//(ID,srver_ID)
				ActionID = PLAYER_LOGIN;
				memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
				memcpy_s(str + in, sizeof(int), &ID, sizeof(int));
				//データ送信
				NetWorkSend((*p).NetHandle[i], str, sizeof(str));			
			}
		}

		//他のプレイヤーの情報を送信
		for (int i = 0; i < MAX_CONNECTION; i++) {
			if (i != ID && (*p).NetHandle[i] != -1) {
				//送信データの作成
				//(ID,server_ID,位置情報)
				ActionID = MAKE_PLAYER;
				in = 0;
				memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
				memcpy_s(str + in, sizeof(int), &i, sizeof(int)); in += sizeof(int);
				memcpy_s(str + in, sizeof(Point), &(*p).data[i].pos, sizeof(Point)); 
				
				//データ送信
				NetWorkSend(GetHandle, str, sizeof(str));
			}
		}

		//手続き完了を送信
		ActionID = CONNECTION_SEND_COMPLETION;
		in = 0;
		memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int));
		NetWorkSend(GetHandle, str, sizeof(str));//データ送信

		return 1;
	}

	return 0;
}


//接続中の処理関数
//(リスト, プレイヤーNo, 管理データ, 受信データ)
int Connection_Process(list<unique_ptr<Base>>& base, int ID, Player_Data* p, int DataLength)
{
	in = 0;
	ActionID = 0;

	if (DataLength != 0) {
		//受信データをstrにコピー
		NetWorkRecv((*p).NetHandle[ID], str, sizeof(str));

		//アクションID取得
		memcpy_s(&ActionID, sizeof(int), str + in, sizeof(int));in += sizeof(int);

		//受信データがある場合
		switch (ActionID) {
		case PLAYER_UPDATE:
			//サーバー情報を更新
			memcpy_s(&(*p).data[ID].pos, sizeof(Point), str + in, sizeof(Point)); in += sizeof(Point);
			memcpy_s(&(*p).data[ID].HP, sizeof(int), str + in, sizeof(int)); in += sizeof(int);

			//サーバー側で弾の情報を更新(trueなら取得)
			if (&(*p).data[ID].isShot)
			{
				//弾生成
				memcpy_s(&(*p).data[ID].Bulletvec, sizeof(Vector), str + in, sizeof(Vector)); in += sizeof(Vector);
				memcpy_s(&(*p).data[ID].isShot, sizeof(bool), str + in, sizeof(bool));
				//ID識別なし
			}

			//自分以外のプレイヤーに情報を送信
			for (int i = 0; i < MAX_CONNECTION; i++) {
				if (i != ID && (*p).NetHandle[i] != -1) {
					//送信データの作成
					//(ID,server_ID,位置情報)
					in = 0;
					memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
					memcpy_s(str + in, sizeof(int), &ID, sizeof(int)); in += sizeof(int);
					memcpy_s(str + in, sizeof(Point), &(*p).data[ID].pos, sizeof(Point)); in += sizeof(Point);
					memcpy_s(str + in, sizeof(int), &(*p).data[ID].HP, sizeof(int)); in += sizeof(int);
					if (&(*p).data[ID].isShot)
					{
						//弾のVec情報、フラグ状況を送信。
						memcpy_s(str + in, sizeof(Vector), &(*p).data[ID].Bulletvec, sizeof(Vector)); in += sizeof(Vector);
						memcpy_s(str + in, sizeof(bool), &(*p).data[ID].isShot, sizeof(bool)); in += sizeof(bool);
					}

					//データ送信
					NetWorkSend((*p).NetHandle[i], str, sizeof(str));
				}
			}
		}
	}

	return 0;
}