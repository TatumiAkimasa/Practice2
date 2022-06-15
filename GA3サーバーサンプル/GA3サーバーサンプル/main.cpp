//サーバー側プログラム
#pragma once
#include "main.h"
#include "net.h"
#include "server.h"
#include "char.h"
#include <thread>
#include <mutex>

//ミューティクス
mutex m;

//オブジェクトのリスト
list<unique_ptr<Base>> base;

int DataLength{ -1 };//データ受信用

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {

	//windowモード切替
	ChangeWindowMode(TRUE);
	//windowサイズ
	SetGraphMode(800, 600, 32);
	//バックグラウンド処理の許可
	SetAlwaysRunFlag(TRUE);
	//多重起動の許可
	SetDoubleStartValidFlag(TRUE);

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	//バックバッファ設定
	SetDrawScreen(DX_SCREEN_BACK);

	//windowの名前
	SetWindowText("サーバー");

	//ポート
	int port{ 26 };

	//プレイヤーデータ(ネット上でIDやら通信状態やらをまとめる)
	Player_Data p;
	
	//接続待機状態に移行
	PreparationListenNetWork(port);

	//送受信用データ
	int DataLength{ -1 };

	//	Player1スレッド(再潜入不可)
	thread* t1 = new thread([&]() 
		{
			while (true) {
				//接続待機
				while (true) {
					if (Initial_Connection_Process(base, &p, Player1)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage()==-1) break;
				}

				//メインループ
				while (true) {
					//接続中の処理
					//データの受信チェック
					DataLength = GetNetWorkDataLength(p.NetHandle[Player1]);

					m.lock();
					//リストの処理
					Connection_Process(base, Player1, &p, DataLength);
					m.unlock();

					//ネットワークハンドルがなくなった場合、接続待機に移行
					if (p.NetHandle[Player1] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	//	Player2スレッド
	thread* t2 = new thread([&]()
		{
			while (true) {
				//接続待機
				while (true) {
					if (Initial_Connection_Process(base, &p, Player2)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				//メインループ
				while (true) {
					//接続中の処理
					//データの受信チェック
					DataLength = GetNetWorkDataLength(p.NetHandle[Player2]);

					m.lock();
					//リストの処理
					Connection_Process(base, Player2, &p, DataLength);
					m.unlock();

					//ネットワークハンドルがなくなった場合、接続待機に移行
					if (p.NetHandle[Player2] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	thread* t3 = new thread([&]()
		{
			while (true) {
				//接続待機
				while (true) {
					if (Initial_Connection_Process(base, &p, Player3)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				//メインループ
				while (true) {
					//接続中の処理
					//データの受信チェック
					DataLength = GetNetWorkDataLength(p.NetHandle[Player3]);

					m.lock();
					//リストの処理
					Connection_Process(base, Player3, &p, DataLength);
					m.unlock();

					//ネットワークハンドルがなくなった場合、接続待機に移行
					if (p.NetHandle[Player3] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	thread* t4 = new thread([&]()
		{
			while (true) {
				//接続待機
				while (true) {
					if (Initial_Connection_Process(base, &p, Player4)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				//メインループ
				while (true) {
					//接続中の処理
					//データの受信チェック
					DataLength = GetNetWorkDataLength(p.NetHandle[Player4]);

					m.lock();
					//リストの処理
					Connection_Process(base, Player4, &p, DataLength);
					m.unlock();

					//ネットワークハンドルがなくなった場合、接続待機に移行
					if (p.NetHandle[Player4] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);
	//サーバーメインループ
	while (true) {
		//画面クリア
		ClearDrawScreen();
		
		//起動端末のIPアドレス
		IPDATA IP;
		GetMyIPAddress(&IP, 1, NULL);
		DrawFormatString(0,0,GetColor(255,255,255),
			"PCのIPアドレス %d:%d:%d:%d 接続ポート:%d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			port
		);

		//接続状態の描画
		for (int i = 0; i < MAX_CONNECTION; i++) {
//			if (p.FLG[i] != -1) {
				DrawFormatString(0, 32 + (i * 36), GetColor(255, 255, 255),
					"ID=%d:位置(%.0lf,%.0lf)フラグ状況:%d弾のVec(%.0lf,%.0lf)",
					i,
					p.data[i].pos.x,
					p.data[i].pos.y,
					p.data[i].isShot,
					p.data[i].Bulletvec.x,
					p.data[i].Bulletvec.y
				);
//			}
		}

		//切断した場合の処理
		int Losthandle = GetLostNetWork();
		for (int i = 0; i < MAX_CONNECTION; i++) {
			if (Losthandle == p.NetHandle[i]) {
				p.NetHandle[i] = -1;
				p.data[i].pos.x = 0.0f;
				p.data[i].pos.y = 0.0f;
				p.FLG[i] = -1;
			}
		}

		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
	}

	//スレッドを同期して終了
	t1->join();
	delete t1;
	//スレッドを同期して終了
	t2->join();
	delete t2;

	//スレッドを同期して終了
	t3->join();
	delete t3;
	//スレッドを同期して終了
	t4->join();
	delete t4;

	StopListenNetWork();//ネットワークの待機を停止

	DxLib_End();

	return 0;
}