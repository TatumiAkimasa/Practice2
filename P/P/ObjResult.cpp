#include "GameHead.h"
#include "ObjResult.h"
#include "GameL\DrawFont.h"
#include "GameL\SceneManager.h"
#include "GameL\WinInputs.h"

//�g�p����Q�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjResult::CObjResult()
{

}

//�C�j�V�����C�Y
void CObjResult::Init()
{
	m_key_flag = false;
}

//�A�N�V����
void CObjResult::Action()
{
	//�G���^�[�L�[�������ăV�[���F�Q�[���^�C�g���Ɉڍs����
	/*if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneTitle());
			m_key_flag == false;
		}
	}
	else
	{
		m_key_flag = true;
	}*/
	//���^�C�g����ʂ��Ȃ��̂ŃR�����g�A�E�g�������Ă����܂���
}

//�h���[
void CObjResult::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"�I���I", 320, 250, 32, c);
}