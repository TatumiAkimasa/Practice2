#pragma once
#include "main.h"
#include "net.h"
#include "server.h"

char str[512]{ "null" };
int in{ 0 };//�f�[�^�̓ǂݎ��A�������݈ʒu�����p
int ActionID{ 0 };//�A�N�V����ID

//����ڑ������֐�
//(���X�g, �Ǘ��f�[�^, �v���C���[ID)
//�o�^�����̏ꍇ�u1�v��Ԃ�
int Initial_Connection_Process(list<unique_ptr<Base>>& base, Player_Data* p, int ID)
{
	//�ڑ������l�b�g���[�N�n���h�����擾
	int GetHandle = GetNewAcceptNetWork();

	//�ڑ����������ꍇ�̏���
	if (GetHandle != -1)
	{
		//���X�g�X�V
		//�l�b�g���[�N�n���h���̓o�^
		(*p).NetHandle[ID] = GetHandle;//�l�b�g���[�N�n���h����o�^

		//ID�̑��M
		//�ڑ��̂������l�b�g���[�N�ɃT�[�o�[�̓o�^ID�𑗐M
		char setID[4];
		sprintf_s(setID, "%d", ID);//ID�𕶎��ɕϊ�
		NetWorkSend((*p).NetHandle[ID], &setID, sizeof(ID));//ID�𑗐M

		//���X�g�̑��݃t���O��ON�ɂ���
		(*p).FLG[ID] = 1;

		//�����ʒu�ݒ�
		(*p).data[ID].pos.x = 0.0f;
		(*p).data[ID].pos.y = 0.0f;

		//���̃v���C���[�ɐڑ���m�点��
		for (int i = 0; i < MAX_CONNECTION; i++) {
			if (i != ID && (*p).NetHandle[i] != -1) {
				in = 0;
				//���M�f�[�^�̍쐬
				//(ID,srver_ID)
				ActionID = PLAYER_LOGIN;
				memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
				memcpy_s(str + in, sizeof(int), &ID, sizeof(int));
				//�f�[�^���M
				NetWorkSend((*p).NetHandle[i], str, sizeof(str));			
			}
		}

		//���̃v���C���[�̏��𑗐M
		for (int i = 0; i < MAX_CONNECTION; i++) {
			if (i != ID && (*p).NetHandle[i] != -1) {
				//���M�f�[�^�̍쐬
				//(ID,server_ID,�ʒu���)
				ActionID = MAKE_PLAYER;
				in = 0;
				memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
				memcpy_s(str + in, sizeof(int), &i, sizeof(int)); in += sizeof(int);
				memcpy_s(str + in, sizeof(Point), &(*p).data[i].pos, sizeof(Point)); 
				
				//�f�[�^���M
				NetWorkSend(GetHandle, str, sizeof(str));
			}
		}

		//�葱�������𑗐M
		ActionID = CONNECTION_SEND_COMPLETION;
		in = 0;
		memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int));
		NetWorkSend(GetHandle, str, sizeof(str));//�f�[�^���M

		return 1;
	}

	return 0;
}


//�ڑ����̏����֐�
//(���X�g, �v���C���[No, �Ǘ��f�[�^, ��M�f�[�^)
int Connection_Process(list<unique_ptr<Base>>& base, int ID, Player_Data* p, int DataLength)
{
	in = 0;
	ActionID = 0;

	if (DataLength != 0) {
		//��M�f�[�^��str�ɃR�s�[
		NetWorkRecv((*p).NetHandle[ID], str, sizeof(str));

		//�A�N�V����ID�擾
		memcpy_s(&ActionID, sizeof(int), str + in, sizeof(int));in += sizeof(int);

		//��M�f�[�^������ꍇ
		switch (ActionID) {
		case PLAYER_UPDATE:
			//�T�[�o�[�����X�V
			memcpy_s(&(*p).data[ID].pos, sizeof(Point), str + in, sizeof(Point)); in += sizeof(Point);
			memcpy_s(&(*p).data[ID].HP, sizeof(int), str + in, sizeof(int)); in += sizeof(int);

			//�T�[�o�[���Œe�̏����X�V(true�Ȃ�擾)
			if (&(*p).data[ID].isShot)
			{
				//�e����
				memcpy_s(&(*p).data[ID].Bulletvec, sizeof(Vector), str + in, sizeof(Vector)); in += sizeof(Vector);
				memcpy_s(&(*p).data[ID].isShot, sizeof(bool), str + in, sizeof(bool));
				//ID���ʂȂ�
			}

			//�����ȊO�̃v���C���[�ɏ��𑗐M
			for (int i = 0; i < MAX_CONNECTION; i++) {
				if (i != ID && (*p).NetHandle[i] != -1) {
					//���M�f�[�^�̍쐬
					//(ID,server_ID,�ʒu���)
					in = 0;
					memcpy_s(str + in, sizeof(int), &ActionID, sizeof(int)); in += sizeof(int);
					memcpy_s(str + in, sizeof(int), &ID, sizeof(int)); in += sizeof(int);
					memcpy_s(str + in, sizeof(Point), &(*p).data[ID].pos, sizeof(Point)); in += sizeof(Point);
					memcpy_s(str + in, sizeof(int), &(*p).data[ID].HP, sizeof(int)); in += sizeof(int);
					if (&(*p).data[ID].isShot)
					{
						//�e��Vec���A�t���O�󋵂𑗐M�B
						memcpy_s(str + in, sizeof(Vector), &(*p).data[ID].Bulletvec, sizeof(Vector)); in += sizeof(Vector);
						memcpy_s(str + in, sizeof(bool), &(*p).data[ID].isShot, sizeof(bool)); in += sizeof(bool);
					}

					//�f�[�^���M
					NetWorkSend((*p).NetHandle[i], str, sizeof(str));
				}
			}
		}
	}

	return 0;
}