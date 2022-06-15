//�N���C�A���g���v���O����
#pragma once
#include "main.h"
#include "net.h"
#include "client.h"
#include "char.h"
#include <thread>
#include <mutex>

//�~���[�e�B�N�X
mutex m;

//�I�u�W�F�N�g�̃��X�g
list<unique_ptr<Base>> base;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdline, _In_ int nShowCmd)
{
	//window���[�h�ؑ�
	ChangeWindowMode(TRUE);
	//window�T�C�Y
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	//�o�b�N�O���E���h�����̋���
	SetAlwaysRunFlag(TRUE);
	//���d�N���̋���
	SetDoubleStartValidFlag(TRUE);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	//window�̖��O
	SetWindowText("�ڑ���");

	//�o�b�N�o�b�t�@���g�p
	SetDrawScreen(DX_SCREEN_BACK);

	//IP�A�h���X�Z�b�g
	IP = IP_set();

	char str[512]{ "null" };
	int in{ 0 };//�f�[�^�̓ǂݎ��A�������݈ʒu�����p
	int ActionID{ 0 };//�A�N�V����ID
	int player_server_ID{ 0 };//�v���C���[�̃T�[�o�[ID
					  
	//�ڑ��t���O
	bool LoginFlg{ false };

	//����ڑ�����-------------------------------------------------------------------------------
	//�w�肵��IP�A�h���X�ɐڑ�
	NetHandle = ConnectNetWork(IP, port);

	if (NetHandle == -1) {
		//�ڑ����m�����Ȃ��ꍇ�A�v���O�����I��
		while (true) {
			DrawFormatString(0, 0, GetColor(255, 255, 255),
				"�ڑ����s�E�E�E\n�L�[���͂Ńv���O�����I��"
			);
			ScreenFlip();
			//�L�[�̓��͑҂�
			WaitKey();

			//�v���O�����I��
			DxLib_End();
			return 0;
		}
	}
	//�T�[�o�[����̍ŏ��̒ʐM�ҋ@
	//�o�^����ID�����M����Ă���
	while (true)
	{
		ClearDrawScreen();//��ʃN���A
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"IP:%d.%d.%d%d�ɐڑ����E�E�E",
			IP.d1, IP.d2, IP.d3, IP.d4);
		//�f�[�^�����Ă����ꍇ�̏���
		if (GetNetWorkDataLength(NetHandle) != 0) {
			char str[4]{ "" };
			//��M�����[�f�[�^�̏���
			if (NetWorkRecv(NetHandle, str, sizeof(str)) != -1) {
				//�o�^����serverID�̎擾
				player_server_ID = atoi(str);
				//�I�u�W�F�N�g�̐���
				base.emplace_back((unique_ptr<Base>)new Player(player_server_ID));
				//���O�C���t���O��true�ɂ���
				//LoginFlg = true;
				break;
			}
		}
		ScreenFlip();
		if ((ProcessMessage() == -1)) break;
	}
	//���v���C���[�ǂݍ���
	while (!LoginFlg) {
		ClearDrawScreen();//��ʃN���A
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"���v���C���[�f�[�^�̓ǂݍ��ݒ�...");

		//�f�[�^�����Ă����ꍇ�̏���
		if (GetNetWorkDataLength(NetHandle) != 0) {
			//��M�f�[�^��str�ɃR�s�[
			NetWorkRecv(NetHandle, str, sizeof(str));

			in = 0;//�f�[�^�̓ǂݎ��ʒu������
			//�A�N�V����ID�擾
			memcpy_s(&ActionID, sizeof(int), str + in, sizeof(int));in += sizeof(int);

			switch (ActionID) {
			case CONNECTION_SEND_COMPLETION:
				//�f�[�^���M����
				LoginFlg = true;
				break;
			case MAKE_PLAYER:
				//���̃v���C���[����
				Point p{ 0,0 };
				memcpy_s(&player_server_ID, sizeof(int), str + in, sizeof(int)); in += sizeof(int);
				memcpy_s(&p, sizeof(Point), str + in, sizeof(Point));
				base.emplace_back((unique_ptr<Base>)new AnyPlayer(player_server_ID, p.x, p.y));
				break;
			}
		}

		ScreenFlip();
		if ((ProcessMessage() == -1)) break;
	}
	//-----------------------------------------------------------------------------------------------
 	
	//�f�[�^��M�p�X���b�h
	//��M�����f�[�^����������
	thread* t1 = new thread([&]()
		{
			while (true) {
				if (LoginFlg) {
					//��M�����f�[�^�̑傫�����擾
					int DataLength = GetNetWorkDataLength(NetHandle);

					//��M�f�[�^������ꍇ
					if (DataLength != 0) {
						ActionID = 0;
						in = 0;//�ǂݎ��ʒu������

						//�f�[�^��M
						NetWorkRecv(NetHandle, str, sizeof(str));

						//ID�̓ǂݎ��
						memcpy_s(&ActionID, sizeof(int), str, sizeof(int)); in += sizeof(int);

						switch (ActionID) {
							//���̃v���C���[���O�C�����������ꍇ
						case PLAYER_LOGIN:
							memcpy_s(&player_server_ID, sizeof(int), str + in, sizeof(int));
							base.emplace_back((unique_ptr<Base>)new AnyPlayer(player_server_ID));
							break;
							//���̃v���C���[�̏�񂪃A�b�v�f�[�g���ꂽ�ꍇ
						case PLAYER_UPDATE:
							Point pos{ 0,0 };
							//�Y������ID�����X�V
							memcpy_s(&player_server_ID, sizeof(int), str + in, sizeof(int)); in += sizeof(int);
							memcpy_s(&pos, sizeof(Point), str + in, sizeof(Point));
							//���X�g��ID�������f�[�^���X�V
							for (auto i = base.begin(); i != base.end(); i++) {
								if ((*i)->server_ID == player_server_ID) {
									((AnyPlayer*)(*i).get())->pos = pos;
								}
							}
							break;
						}
					}
				}
				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	//FPS
	//���ݎ��Ԃ̎擾
	double nextTime = GetNowCount();

	//���C�����[�v
	while (true)
	{
		if(CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//��ʂ̃N���A
		ClearDrawScreen();

		//�I�u�W�F�N�g�̏���
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Action(base,NetHandle);

		//�`�揈��
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Draw();

		//FPS����
		nextTime += 1000 / FPS;//1�t���[���ɂ����鎞��
		if (nextTime > GetNowCount()) {
			//���Ԃ��o�߂��Ă��Ȃ���΁A���̎��ԑ҂�
			WaitTimer((int)nextTime - GetNowCount());
		}

		//list����̍폜����
		for (auto i = base.begin(); i != base.end(); i++) {
			if (!((*i)->FLAG)) {
				i = base.erase(i);
				break;
			}
		}

		//�l�b�g���[�N�n���h���̕`��
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"NetHandle=%d",
			NetHandle
		);

		ScreenFlip();
		if ((ProcessMessage() == -1)) break;
	}

	//�ڑ����I������
	CloseNetWork(NetHandle);

	//�v���O�����I��
	DxLib_End();

	return 0;
}