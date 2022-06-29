#pragma once
#include "DxLib.h"

// char->int �ɕϊ�(���l�j
int ctoi(char c);

//IP�ݒ�
IPDATA IP_set() {
	IPDATA ip{ 0,0,0,0 };

	int numImg = LoadGraph("image\\number.png");
	int buttonImg = LoadGraph("image\\button.png");

	//IP���l�̏������Ɛ錾
	//�Œ肷��ꍇ�́A������IP�A�h���X�������l�����ē���
	char str[12]{
		'1','9','2',//p1
		'1','6','8',//p2
		'0','0','1',//p3
		'1','8','7',//p4
	};

	//�}�E�X�J�[�\���ʒu
	int MouseX{ 0 }, MouseY{ 0 };
	int button{ 0 };//�}�E�X�̍��{�^���L���p

	//�}�E�X�J�[�\���\���̗L��
	//SetMouseDispFlag(TRUE);

	while (TRUE) {
		//esc�ŏI��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ClearDrawScreen();

		//���N���b�N
		if (GetMouseInput() == MOUSE_INPUT_LEFT && !button) {
			//�}�E�X�̈ʒu���擾
			GetMousePoint(&MouseX, &MouseY);

			int k = 0;
			for (int j = 0; j < 512; j += 128) {
				for (int i = 0; i < 93; i += 32) {
					//�N���b�N�����ʒu�̃{�^������
					//��{�^��
					if (MouseX > i + j && MouseX < i + j + 32 && MouseY > 16 && MouseY < 48) {
						str[k]++;
						if (str[k] >= '9' + 1)str[k] = '0';
					}
					//���{�^��
					if (MouseX > i + j && MouseX < i + j + 32 && MouseY > 80 && MouseY < 96) {
						str[k]--;
						if (str[k] <= '0' - 1)str[k] = '9';
					}
					k++;
				}
			}

			//OK�{�^��
			if (MouseX > 4 && MouseX < 53 && MouseY>128 && MouseY < 158) {
				int ipNo[4]{ 0,0,0,0 };
				char link[3]{ '0','0','0' };

				link[0] = str[0];
				link[1] = str[1];
				link[2] = str[2];
				ip.d1 = atoi(link);

				link[0] = str[3];
				link[1] = str[4];
				link[2] = str[5];
				ip.d2 = atoi(link);

				link[0] = str[6];
				link[1] = str[7];
				link[2] = str[8];
				ip.d3 = atoi(link);

				link[0] = str[9];
				link[1] = str[10];
				link[2] = str[11];
				ip.d4 = atoi(link);

				break;
			}
		}

		//�`��
		DrawString(0, 0, "�ڑ����IP����", GetColor(255, 255, 255));
		for (int i = 0, j = 0; i < 15; i++) {
			if ((i + 1) % 4 != 0) {
				DrawRectGraph(i * 32, 16, 0, 0, 32, 32, buttonImg, TRUE, 0, 0);//�㑤�{�^��
				DrawRectGraph(i * 32, 80, 0, 0, 32, 32, buttonImg, TRUE, 0, 1);//�����{�^��
				DrawRectGraph(i * 32, 48, ctoi(str[j]) * 32, 0, 32, 32, numImg, TRUE, 0, 0);//����
				j++;
			}
			else {
				//�J���}
				DrawRectGraph(i * 32 + 16, 80, 81, 0, 4, 4, buttonImg, TRUE, 0, 0);
			}
		}
		//OK�{�^��
		DrawRectGraph(4, 128, 32, 0, 49, 30, buttonImg, TRUE, 0, 0);

		//�{�^���̏���ۑ�
		button = GetMouseInput();

		ScreenFlip();
		if ((ProcessMessage() == -1)) break;
	}

	return ip;
}

// char -> int
// ���l�ȊO��'-1'��Ԃ�
int ctoi(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	return -1;
}