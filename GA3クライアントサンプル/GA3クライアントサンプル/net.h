//通信用
#pragma once

//接続数
constexpr auto MAX_CONNECTION = 4;

//アクションID
enum {
	CONNECTION_SEND_COMPLETION,//初回接続完了
	MAKE_PLAYER,//プレイヤー生成
	PLAYER_LOGIN,//プレイヤーログイン
	PLAYER_LOGOUT,//プレイヤーログアウト
	PLAYER_UPDATE,//プレイヤーデータ更新
};
