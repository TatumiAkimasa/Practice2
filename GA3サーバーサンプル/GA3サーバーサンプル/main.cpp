//�T�[�o�[���v���O����
#pragma once
#include "main.h"
#include "net.h"
#include "server.h"
#include "char.h"
#include <thread>
#include <mutex>

//�~���[�e�B�N�X
mutex m;

//�I�u�W�F�N�g�̃��X�g
list<unique_ptr<Base>> base;

int DataLength{ -1 };//�f�[�^��M�p

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {

	//window���[�h�ؑ�
	ChangeWindowMode(TRUE);
	//window�T�C�Y
	SetGraphMode(800, 600, 32);
	//�o�b�N�O���E���h�����̋���
	SetAlwaysRunFlag(TRUE);
	//���d�N���̋���
	SetDoubleStartValidFlag(TRUE);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	//�o�b�N�o�b�t�@�ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//window�̖��O
	SetWindowText("�T�[�o�[");

	//�|�[�g
	int port{ 26 };

	//�v���C���[�f�[�^(�l�b�g���ID���ʐM��Ԃ����܂Ƃ߂�)
	Player_Data p;
	
	//�ڑ��ҋ@��ԂɈڍs
	PreparationListenNetWork(port);

	//����M�p�f�[�^
	int DataLength{ -1 };

	//	Player1�X���b�h(�Đ����s��)
	thread* t1 = new thread([&]() 
		{
			while (true) {
				//�ڑ��ҋ@
				while (true) {
					if (Initial_Connection_Process(base, &p, Player1)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage()==-1) break;
				}

				//���C�����[�v
				while (true) {
					//�ڑ����̏���
					//�f�[�^�̎�M�`�F�b�N
					DataLength = GetNetWorkDataLength(p.NetHandle[Player1]);

					m.lock();
					//���X�g�̏���
					Connection_Process(base, Player1, &p, DataLength);
					m.unlock();

					//�l�b�g���[�N�n���h�����Ȃ��Ȃ����ꍇ�A�ڑ��ҋ@�Ɉڍs
					if (p.NetHandle[Player1] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	//	Player2�X���b�h
	thread* t2 = new thread([&]()
		{
			while (true) {
				//�ڑ��ҋ@
				while (true) {
					if (Initial_Connection_Process(base, &p, Player2)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				//���C�����[�v
				while (true) {
					//�ڑ����̏���
					//�f�[�^�̎�M�`�F�b�N
					DataLength = GetNetWorkDataLength(p.NetHandle[Player2]);

					m.lock();
					//���X�g�̏���
					Connection_Process(base, Player2, &p, DataLength);
					m.unlock();

					//�l�b�g���[�N�n���h�����Ȃ��Ȃ����ꍇ�A�ڑ��ҋ@�Ɉڍs
					if (p.NetHandle[Player2] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	thread* t3 = new thread([&]()
		{
			while (true) {
				//�ڑ��ҋ@
				while (true) {
					if (Initial_Connection_Process(base, &p, Player3)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				//���C�����[�v
				while (true) {
					//�ڑ����̏���
					//�f�[�^�̎�M�`�F�b�N
					DataLength = GetNetWorkDataLength(p.NetHandle[Player3]);

					m.lock();
					//���X�g�̏���
					Connection_Process(base, Player3, &p, DataLength);
					m.unlock();

					//�l�b�g���[�N�n���h�����Ȃ��Ȃ����ꍇ�A�ڑ��ҋ@�Ɉڍs
					if (p.NetHandle[Player3] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);

	thread* t4 = new thread([&]()
		{
			while (true) {
				//�ڑ��ҋ@
				while (true) {
					if (Initial_Connection_Process(base, &p, Player4)) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				//���C�����[�v
				while (true) {
					//�ڑ����̏���
					//�f�[�^�̎�M�`�F�b�N
					DataLength = GetNetWorkDataLength(p.NetHandle[Player4]);

					m.lock();
					//���X�g�̏���
					Connection_Process(base, Player4, &p, DataLength);
					m.unlock();

					//�l�b�g���[�N�n���h�����Ȃ��Ȃ����ꍇ�A�ڑ��ҋ@�Ɉڍs
					if (p.NetHandle[Player4] == -1) break;

					if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
				}

				if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
			}
		}
	);
	//�T�[�o�[���C�����[�v
	while (true) {
		//��ʃN���A
		ClearDrawScreen();
		
		//�N���[����IP�A�h���X
		IPDATA IP;
		GetMyIPAddress(&IP, 1, NULL);
		DrawFormatString(0,0,GetColor(255,255,255),
			"PC��IP�A�h���X %d:%d:%d:%d �ڑ��|�[�g:%d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			port
		);

		//�ڑ���Ԃ̕`��
		for (int i = 0; i < MAX_CONNECTION; i++) {
//			if (p.FLG[i] != -1) {
				DrawFormatString(0, 32 + (i * 36), GetColor(255, 255, 255),
					"ID=%d:�ʒu(%.0lf,%.0lf)�t���O��:%d�e��Vec(%.0lf,%.0lf)",
					i,
					p.data[i].pos.x,
					p.data[i].pos.y,
					p.data[i].isShot,
					p.data[i].Bulletvec.x,
					p.data[i].Bulletvec.y
				);
//			}
		}

		//�ؒf�����ꍇ�̏���
		int Losthandle = GetLostNetWork();
		for (int i = 0; i < MAX_CONNECTION; i++) {
			if (Losthandle == p.NetHandle[i]) {
				p.NetHandle[i] = -1;
				p.data[i].pos.x = 0.0f;
				p.data[i].pos.y = 0.0f;
				p.FLG[i] = -1;
			}
		}

		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE) || ProcessMessage() == -1) break;
	}

	//�X���b�h�𓯊����ďI��
	t1->join();
	delete t1;
	//�X���b�h�𓯊����ďI��
	t2->join();
	delete t2;

	//�X���b�h�𓯊����ďI��
	t3->join();
	delete t3;
	//�X���b�h�𓯊����ďI��
	t4->join();
	delete t4;

	StopListenNetWork();//�l�b�g���[�N�̑ҋ@���~

	DxLib_End();

	return 0;
}