//使用するヘッダーファイル
#include "ObjBackground.h"
#include "GameHead.h"
#include "GameL\DrawTexture.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjBackground::Init()
{
	m_y1 = 0.0f;
}

//アクション
void CObjBackground::Action()
{
	//背景①の動作
	//m_y1 -= 10.0f;
	if (m_y1 < -800.0f)
		m_y1 = 800;

}

//ドロー
void CObjBackground::Draw()
{
	//描写カラー情報　R=RED G=Green B=Blue A=Alpha(透過情報）
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;  //描画元切り取り位置
	RECT_F dst;  //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//背景①の位置設定し描画
	dst.m_top = 0.0f;
	dst.m_left = 0.0f ;
	dst.m_right = 32.0f ;
	dst.m_bottom = 32.0f;

	//1番目に登録したグラフィックをsrc・dst・cの情報をもとに描画
	Draw::Draw(1, &src, &dst, c, 0.0f);

	

}
