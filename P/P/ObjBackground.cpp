//�g�p����w�b�_�[�t�@�C��
#include "ObjBackground.h"
#include "GameHead.h"
#include "GameL\DrawTexture.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjBackground::Init()
{
	m_y1 = 0.0f;
}

//�A�N�V����
void CObjBackground::Action()
{
	//�w�i�@�̓���
	//m_y1 -= 10.0f;
	if (m_y1 < -800.0f)
		m_y1 = 800;

}

//�h���[
void CObjBackground::Draw()
{
	//�`�ʃJ���[���@R=RED G=Green B=Blue A=Alpha(���ߏ��j
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;  //�`�挳�؂���ʒu
	RECT_F dst;  //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//�w�i�@�̈ʒu�ݒ肵�`��
	dst.m_top = 0.0f;
	dst.m_left = 0.0f ;
	dst.m_right = 32.0f ;
	dst.m_bottom = 32.0f;

	//1�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�̏������Ƃɕ`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

	

}
