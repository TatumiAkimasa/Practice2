//STL�f�o�b�O�@�\���I�t�ɂ���
#define _SECURESCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//�g�p����Q�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneResult.h"
#include "GameHead.h"


//�R���X�g���N�^
CSceneResult::CSceneResult()
{

}

//�Q�[�����C�����������\�b�h
void CSceneResult::InitScene()
{
	////���y���ǂݍ���
	//Audio::LoadAudio(0, L"duck.wav", SOUND_TYPE::BACK_MUSIC);

	////�o�b�N�~���[�W�b�N�X�^�[�g
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster((1.0 - v));
	//Audio::Start(0);//bgm�X�^�[�g
	//����XBGM����Ǝv�����̂œK���ɏ����Ƃ��܂����B
	//�K�v�Ȃ���Ώ����Ă�������

	//�o�͂����镶���̃O���t�B�b�N���쐬
	Font::SetStrTex(L"�I���I");

	//�^�C�g���I�u�W�F�N�g�쐬
	//��l���I�u�W�F�N�g�쐬
	CObjResult* obj = new CObjResult();//���U���g�쐬
	Objs::InsertObj(obj, OBJ_RESULT, 10);//��������U���g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneResult::Scene()
{



}