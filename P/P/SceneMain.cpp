//STLデバック機能をOffにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GmameLで使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\Audio.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"


//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録（386*564ピクセル）
	Draw::LoadImageW(L"メイン背景_512.png", 0, TEX_SIZE_512);

	//外部グラフィックファイルを読み込み0番に登録（386*564ピクセル）
	Draw::LoadImageW(L"image.png", 1, TEX_SIZE_512);

	//背景オブジェクト作成
	CObjBackground* back = new CObjBackground();
	Objs::InsertObj(back, OBJ_BACK_GROUND, 5);
}

//ゲーム実行中メソッド
void CSceneMain::Scene()
{

}