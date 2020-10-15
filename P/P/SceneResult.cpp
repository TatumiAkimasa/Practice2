//STLデバッグ機能をオフにする
#define _SECURESCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//使用するゲームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneResult.h"
#include "GameHead.h"


//コンストラクタ
CSceneResult::CSceneResult()
{

}

//ゲームメイン初期化メソッド
void CSceneResult::InitScene()
{
	////音楽情報読み込み
	//Audio::LoadAudio(0, L"duck.wav", SOUND_TYPE::BACK_MUSIC);

	////バックミュージックスタート
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((1.0 - v));
	//Audio::Start(0);//bgmスタート
	//↑後々BGM入ると思ったので適当に書いときました。
	//必要なければ消してください

	//出力させる文字のグラフィックを作成
	Font::SetStrTex(L"終了！");

	//タイトルオブジェクト作成
	//主人公オブジェクト作成
	CObjResult* obj = new CObjResult();//リザルト作成
	Objs::InsertObj(obj, OBJ_RESULT, 10);//作ったリザルトをオブジェクトマネージャーに登録
}

//ゲームメイン実行中メソッド
void CSceneResult::Scene()
{



}