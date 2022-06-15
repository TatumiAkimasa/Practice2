//クライアント側プログラム
#pragma once
#include "main.h"
#include "net.h"
#include "client.h"
#include "char.h"
#include <thread>
#include <mutex>

//ミューティクス
mutex m;

//オブジェクトのリスト
list<unique_ptr<Base>> base;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdline, _In_ int nShowCmd)
{
	//windowモード切替
	ChangeWindowMode(TRUE);
	//windowサイズ
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	//バックグラウンド処理の許可
	SetAlwaysRunFlag(TRUE);
	//多重起動の許可
	SetDoubleStartValidFlag(TRUE);

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	//windowの名前
	SetWindowText("接続側");

	//バックバッファを使用
	SetDrawScreen(DX_SCREEN_BACK);

	//IPアドレスセット
	IP = IP_set();

	char str[512]{ "null" };
	int in{ 0 };//データの読み取り、書き込み位置調整用
	int ActionID{ 0 };//アクションID
	int player_server_ID{ 0 };//プレイヤーのサーバーID
					  
	//接続フラグ
	bool LoginFlg{ false };

	//初回接続処理-------------------------------------------------------------------------------
	//指定したIPアドレスに接続
	NetHandle = ConnectNetWork(IP, port);

	if (NetHandle == -1) {
		//接続が確立しない場合、プログラム終了
		while (true) {
			DrawFormatString(0, 0, GetColor(255, 255, 255),
				"接続失敗・・・\nキー入力でプログラム終了"
			);
			ScreenFlip();
			//キーの入力待ち
			WaitKey();

			//プログラム終了
			DxLib_End();
			return 0;
		}
	}
	//サーバーからの最初の通信待機
	//登録したIDが送信されてくる
	while (true)
	{
		ClearDrawScreen();//画面クリア
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"IP:%d.%d.%d%dに接続中・・・",
			IP.d1, IP.d2, IP.d3, IP.d4);
		//データ送られてきた場合の処理
		if (GetNetWorkDataLength(NetHandle) != 0) {
			char str[4]{ "" };
			//受信したーデータの処理
			if (NetWorkRecv(NetHandle, str, sizeof(str)) != -1) {
				//登録したserverIDの取得
				player_server_ID = atoi(str);
				//オブジェクトの生成
				base.emplace_back((unique_ptr<Base>)new Player(player_server_ID));
				//ログインフラグをtrueにする
				//LoginFlg = true;
				break;
			}
		}
		ScreenFlip();
		if ((ProcessMessage() == -1)) break;
	}
	//他プレイヤー読み込み
	while (!LoginFlg) {
		ClearDrawScreen();//画面クリア
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"他プレイヤーデータの読み込み中...");

		//データ送られてきた場合の処理
		if (GetNetWorkDataLength(NetHandle) != 0) {
			//受信データをstrにコピー
			NetWorkRecv(NetHandle, str, sizeof(str));

			in = 0;//データの読み取り位置初期化
			//アクションID取得
			memcpy_s(&ActionID, sizeof(int), str + in, sizeof(int));in += sizeof(int);

			switch (ActionID) {
			case CONNECTION_SEND_COMPLETION:
				//データ送信完了
				LoginFlg = true;
				break;
			case MAKE_PLAYER:
				//他のプレイヤー生成
				Point p{ 0,0 };
				memcpy_s(&player_server_ID, sizeof(int), str + in, sizeof(int)); in += sizeof(int);
				memcpy_s(&p, sizeof(Point), str + in, sizeof(Point));
				base.emplace_back((unique_ptr<Base>)new AnyPlayer(player_server_ID, p.x, p.y));
				break;
			}
		}

		ScreenFlip();
		if ((ProcessMessage() == -1)) break;
	}
	//-----------------------------------------------------------------------------------------------
 	
	//データ受信用スレッド
	//受信したデータを処理する
	thread* t1 = new thread([&]()
		{
			while (true) {
				if (LoginFlg) {
					//受信したデータの大きさを取得
					int DataLength = GetNetWorkDataLength(NetHandle);

					//受信データがある場合
					if (DataLength != 0) {
						ActionID = 0;
						in = 0;//読み取り位置初期化

						//データ受信
						NetWorkRecv(NetHandle, str, sizeof(str));

						//IDの読み取り
						memcpy_s(&ActionID, sizeof(int), str, sizeof(int)); in += sizeof(int);

						switch (ActionID) {
							//他のプレイヤーログインがあった場合
						case PLAYER_LOGIN:
							memcpy_s(&player_server_ID, sizeof(int), str + in, sizeof(int));
							base.emplace_back((unique_ptr<Base>)new AnyPlayer(player_server_ID));
							break;
							//他のプレイヤーの情報がアップデートされた場合
						case PLAYER_UPDATE:
							Point pos{ 0,0 };
							//該当するID情報を更新
							memcpy_s(&player_server_ID, sizeof(int), str + in, sizeof(int)); in += sizeof(int);
							memcpy_s(&pos, sizeof(Point), str + in, sizeof(Point));
							//リストのIDが同じデータを更新
							for (auto i = base.begin(); i != base.end(); i++) {
								if ((*i)->server_ID == player_server_ID) {
									((AnyPlayer*)(*i).get())->pos = pos;
								}
							}
							break;
						}
					}
				}
				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	//FPS
	//現在時間の取得
	double nextTime = GetNowCount();

	//メインループ
	while (true)
	{
		if(CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//画面のクリア
		ClearDrawScreen();

		//オブジェクトの処理
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Action(base,NetHandle);

		//描画処理
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Draw();

		//FPS処理
		nextTime += 1000 / FPS;//1フレームにかける時間
		if (nextTime > GetNowCount()) {
			//時間が経過していなければ、その時間待つ
			WaitTimer((int)nextTime - GetNowCount());
		}

		//listからの削除処理
		for (auto i = base.begin(); i != base.end(); i++) {
			if (!((*i)->FLAG)) {
				i = base.erase(i);
				break;
			}
		}

		//ネットワークハンドルの描画
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"NetHandle=%d",
			NetHandle
		);

		ScreenFlip();
		if ((ProcessMessage() == -1)) break;
	}

	//接続を終了する
	CloseNetWork(NetHandle);

	//プログラム終了
	DxLib_End();

	return 0;
}