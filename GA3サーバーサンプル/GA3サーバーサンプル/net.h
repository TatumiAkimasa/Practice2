//�ʐM�p
#pragma once

//�ڑ���
constexpr auto MAX_CONNECTION = 4;

//�A�N�V����ID
enum {
	CONNECTION_SEND_COMPLETION,//����ڑ�����
	MAKE_PLAYER,//�v���C���[����
	PLAYER_LOGIN,//�v���C���[���O�C��
	PLAYER_LOGOUT,//�v���C���[���O�A�E�g
	PLAYER_UPDATE,//�v���C���[�f�[�^�X�V
};
