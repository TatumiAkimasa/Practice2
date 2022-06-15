#pragma once
#include "net.h"
#include "main.h"

//IPアドレス
IPDATA IP;

//ネットワークハンドル
int NetHandle{ -1 };

//ポート
int port{ 26 };

//IPアドレスセット
IPDATA IP_set();