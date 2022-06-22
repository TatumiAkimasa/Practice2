#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ObjBackground
class CObjBackground : public CObj
{
public:
	CObjBackground() {};
	~CObjBackground() {};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー
private:

	float m_y1; //背景①の描画情報
};
