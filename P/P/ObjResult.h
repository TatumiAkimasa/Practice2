#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：敵機
class CObjResult :public CObj
{
public:
	CObjResult();
	~CObjResult() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
private:
	bool m_key_flag;
};