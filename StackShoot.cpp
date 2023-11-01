#pragma once

#include "stackshoot.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1){		// �c�w���C�u��������������
	
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�f�o�b�O�o�͗p������//
	//char p[300];

	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1920, 1080, 16);

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//�ړ��p�^�[���𐶐�
	//OutputDebugString("Make Movements\n\n");
	std::vector<EnemyMoveInterface*> movements;
	movements.push_back(new EnemyMove());
	movements.push_back(new EnemyMoveRoundTrip());

	//�ˌ��p�^�[���𐶐�
	std::vector<EnemyShootInterface*> shoots;
	shoots.push_back(new EnemyShoot());

	int stageNum = 1;	//�X�e�[�W�ԍ�
	int result;	//�N���Aor���s

	char enemyImageFile[256];	//�G�̉摜�t�@�C����
	int movement;	//�G�̍s���p�^�[���ԍ�
	int shoot;		//�G�̎ˌ��p�^�[���ԍ�
	std::vector <char*> bulletNums;

	int FileHandle;	//�ǂݍ��ރt�@�C���ԍ�
	char file[256];	//�e�X�e�[�W�̏�񂪏�����Ă���t�@�C����
	char str[256];	//�ǂݍ��񂾍s

	// �X�e�[�W�ԍ������ƂɊO���t�@�C������ �G�̉摜�t�@�C���C�s���p�^�[��vector�̃C���f�b�N�X��ǂݍ���
	sprintf_s(file, "./%s", FILE);	//�t�@�C���w��
	
	//�f�o�b�O�o��//
	//OutputDebugString("Open File\n\n");

	FileHandle = FileRead_open(file);	//�t�@�C�����J��
	
	//�f�o�b�O�o��//
	//sprintf_s(p, "Opened %s\n\n", file);
	//OutputDebugString(p);

	for (int i = 0; i < stageNum; i++) {	//���̃X�e�[�W�ԍ��̏�񂪏�����Ă���s�܂�

		FileRead_gets(str, 256, FileHandle);	// ��s�ǂ�

		//�f�o�b�O�o��//
		//OutputDebugString(str);
		//OutputDebugString("\n");
	}
	char* ntok;
	char* tok = strtok_s(str, ",", &ntok);	//�G�̉摜�t�@�C�������擾
	
	sprintf_s(enemyImageFile, "./images/%s.png", tok);

	//�f�o�b�O�o��
	//OutputDebugString(enemyImageFile);

	tok = strtok_s(NULL, ",", &ntok);	//�s���p�^�[���ԍ����擾
	movement = atoi(tok);

	//�ˌ��p�^�[���ԍ����擾
	tok = strtok_s(NULL, ",", &ntok);	//�ˌ��p�^�[���ԍ����擾
	shoot = atoi(tok);

	//�e�̔ԍ��������擾
	tok = strtok_s(NULL, ",", &ntok);	//�e�̉摜�t�@�C���ԍ����擾
	while (tok != NULL) {

		bulletNums.push_back(tok);
		tok = strtok_s(NULL, ",", &ntok);	//�e�̉摜�t�@�C���ԍ����擾

		//�f�o�b�O�o��//
		//OutputDebugString("Add Info to buletNums\n");
	}

	//�f�o�b�O�o��//
	//sprintf_s(p, "read %s\n\n", file);
	//OutputDebugString(p);

	//�Q�[���J�n
	Stage stage = Stage(100, 5, 1, enemyImageFile, movements[movement], shoots[shoot], bulletNums);	//������fallSpeed��50�̖� ������makeFrame��50/fallSpeed < makeFrame ��O�����X�e�[�W�ԍ�

	result = stage.loop();	//�X�e�[�W�̃��[�v����

	if (result == 0) {

		OutputDebugString("\n\nClear!!\n\n");	//�N���A
	}
	else if (result == -1) {

		OutputDebugString("\n\nDefeated :(\n\n");	//�s�k
	}
	else if (result == -2) {

		OutputDebugString("\n\nStack Over Flow :(\n\n");	//�u���b�N���ς݂����肫����
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}


