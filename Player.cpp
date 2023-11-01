#pragma once

#include "player.h"

class Player {

private:

	int imageHandle;	//���@�̉摜�ԍ�

	int pos[2];	//���@�̍��W
	int width;	//���@�̕��i���̑傫���j
	int height;	//���@�̍����i�c�̑傫���j

	int bulletImageHandle;	//�e�̉摜�ԍ�

	std::vector<Bullet*> bullets;		//�������e����

	int hp;		//�̗�
	int bombNum;	//�������Ă��锚�e�̐�
	int speed;	//�ړ����x
	double speedCoeff;	//�ړ����x�W��
	double powerCoeff;	//�e�̈З͌W��
	int speedTime;	//�X�s�[�h�A�b�v��Ԃ̎c�莞��
	int powerTime;	//�p���[�A�b�v��Ԃ̎c�莞��
	int bubbleTime;	//�o�u����Ԃ̎c�莞��
	int doubleTime;	//�_�u����Ԃ̎c�莞��

	int frame;		//�o�߃t���[��
	int shootFrame;	//�ˌ��Ԋu

	int invincibleTime;	//��e��̎c�薳�G����

public:

	//�R���X�g���N�^
	Player() {

		imageHandle = LoadGraph("./images/player.png");
		bulletImageHandle = LoadGraph("./images/bullet.png");

		width = 20;
		height = 20;
		pos[0] = (WIDTH / 2 - width / 2) + x0;
		pos[1] = HEIGHT - height;


		hp = 60;
		bombNum = 0;
		speed = 7;
		speedCoeff = 1;
		powerCoeff = 1;
		speedTime = 0;
		powerTime = 0;
		bubbleTime = 0;

		frame = 0;
		shootFrame = 4;

		invincibleTime = 0;

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "player:%d,%d\n\n", pos[0], pos[1]);
		//OutputDebugString(p);
	}

	//���@�ƒe�̕`��
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);	//���@�̕`��

		for (int i = 0; i < bullets.size(); i++) {

			bullets[i]->Draw();	//�e�̕`��
		}
	};

	//�e����̕\��
	void WriteStats() {

		unsigned int color = GetColor(255, 255, 255);	//���������g��

		DrawFormatString(1200, 50, color, "HP:%d", hp);
		//DrawFormatString(1200, 50, color, "HP:%d invincibleTime:%d", hp, invincibleTime);
		//DrawFormatString(1200, 100, color, "powerCoeff:%f powerTime:%d", powerCoeff, powerTime);
		//DrawFormatString(1200, 150, color, "speedCoeff:%f speedTime:%d", speedCoeff, speedTime);
		//DrawFormatString(1200, 200, color, "bubbleTime:%d", bubbleTime);
		//DrawFormatString(1200, 250, color, "doubleTime:%d", doubleTime);
		DrawFormatString(1200, 100, color, "bombNum:%d", bombNum);
		//DrawFormatString(1200, 350, color, "InvincibleTime:%d", invincibleTime);
		//DrawFormatString(1200, 400, color, "bulletNum:%d", bullets.size());
	};

	//���@�̈ړ�
	void Move(int x, int y) {

		//�ړ���̌v�Z
		pos[0] += speedCoeff * speed * x;
		pos[1] += speedCoeff * speed * y;

		//�ړ��͈͊O�ɍs���Ȃ��悤�ɂ���
		if (pos[0] < x0) {

			pos[0] = x0;
		}
		if (pos[0] > x0 + WIDTH - width) {

			pos[0] = x0 + WIDTH - width;
		}
		if (pos[1] < 0) {

			pos[1] = 0;
		}
		if (pos[1] > HEIGHT - height) {

			pos[1] = HEIGHT - height;
		}
	};

	//�e���ړ�
	void MoveBullets() {

		//��ʊO�ɏo���e���폜
		EraseBullets();

		//�e�e�̍��W���X�V
		for (int i = 0; i < bullets.size(); i++) {

			bullets[i]->Move();
		}
	};

	//��ʊO�ɏo���e���폜
	void EraseBullets() {

		auto itr = bullets.begin();

		while (itr != bullets.end()) {

			if ((*itr)->GetPosY() < - (*itr)->GetHeight()) {	//��ʊO�Ȃ�

				delete* itr;				//�e���폜
				itr = bullets.erase(itr);
			}
			else {	//��ʓ��Ȃ�

				itr++;	//�����������̒e��
			}
		}
	};

	//�e������
	void Shoot() {		

		if (frame < shootFrame) {	//�ˌ��\�ȃt���[���łȂ����

			frame++;	//frame�X�V
		}
		else {	//�ˌ��\�ȃt���[���Ȃ�

			if (CheckHitKey(KEY_INPUT_RSHIFT) == 1) {	//�L�[���͂��󂯕t����

				bullets.push_back(new Bullet(pos[0] + width / 2, pos[1], 0, -30, 50, bulletImageHandle));	//�e�𐶐�
			}

			frame = 0;
		}

		//�f�o�b�O�o��//
		//char p[300];
		//sprintf_s(p, "%d ", bullets.size());
		//OutputDebugString(p);
	};

	//���e���g��
	bool UseBomb() {

		if (CheckHitKey(KEY_INPUT_S) == 1) {	//S�L�[���͂���������

			if (bombNum > 0) {	//���e�������Ă�����

				bombNum--;	//���e������

				return TRUE;
			}
			else {

				return FALSE;
			}
		}
		else {

			return FALSE;
		}
	};

	//�ΏۂɃ_���[�W��^����
	int DealDamage(int targetX, int targetY, int targetWidth, int targetHeight) {

		int damage = 0;	//�e�e���^����_���[�W
		int damageSum = 0;	//�^���鑍�_���[�W

		auto itr = bullets.begin();

		while (itr != bullets.end()) {

			damage = (*itr)->CalcDamage(targetX, targetY, targetWidth, targetHeight, powerCoeff);	//�e�e���^����_���[�W���v�Z

			if (damage > 0) {	//�_���[�W��0���傫���i�Ώۂɒe���������Ă���j�Ȃ�

				damageSum += damage;	//�^����_���[�W�����Z
				delete* itr;			//���������e���폜
				itr = bullets.erase(itr);
			}
			else {	//�_���[�W��0�ȉ��i�Ώۂɒe���������Ă��Ȃ��j�Ȃ�

				itr++;	//�����������̒e��
			}
		}

		return damageSum;	//�_���[�W��^����
	};

	//���@���Ώۂ���_���[�W���󂯂�
	void RecieveDamage(int targetX, int targetY, int targetWidth, int targetHeight, int power) {


		//�ΏۂƂ̏Փ˔���
		if (pos[0] <= targetX + targetWidth && pos[0] + width >= targetX) {

			if (pos[1] <= targetY + targetHeight && pos[1] + height >= targetY) {

				if (bubbleTime > 0) {	//�o�u����Ԃ�������

					bubbleTime--;	//�o�u���̎c�莞�Ԃ�����ɂ���i�o�u����Ԃ̎c�莞�Ԃ�������������j
				}
				else {	//�o�u����Ԃ���Ȃ�������

					hp -= power;	//�_���[�W���󂯂�
					invincibleTime = 1000;	//���G���Ԃɓ���
				}
			}
		}
	};

	//�u���b�N�����̌��ʂ𓾂�
	void GetEffect(int blockType, int chainNum, int combos) {

		if (blockType == 1) {	//���e�u���b�N���������Ȃ�

			GetBombEffect(chainNum);
		}
		else if (blockType == 2) {	//�n�[�g�u���b�N���������Ȃ�

			GetHeartEffect(chainNum, combos);
		}
		else if (blockType == 3) {	//�p���[�u���b�N���������Ȃ�

			GetPowerEffect(chainNum, combos);
		}
		else if (blockType == 4) {	//�X�s�[�h�u���b�N���������Ȃ�

			GetSpeedEffect(chainNum, combos);
		}
		else if (blockType == 5) {	//�o�u���u���b�N���������Ȃ�

			GetBubbleEffect(chainNum, combos);
		}
		else if (blockType == 6) {	//�_�u���u���b�N���������Ȃ�

			GetDoubleEffect(chainNum, combos);
		}
	};

	//���e�u���b�N�����̌��ʂ𓾂�
	void GetBombEffect(int chainNum) {

		bombNum = bombNum + (chainNum / 4);	//�������ɉ����Ĕ��e�����

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "add %d bombs\n", chainNum % 4);
		//OutputDebugString(p);
	};

	//�n�[�g�u���b�N�����̌��ʂ𓾂�
	void GetHeartEffect(int chainNum, int combos) {
	
		int cure;	//�񕜗�

		cure = 5 * combos * chainNum;	//�񕜗ʂ̌v�Z

		hp = hp + cure;	//HP����

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "cure:%d, new hp:%d\n", cure, hp);
		//OutputDebugString(p);
	};

	//�p���[�u���b�N�����̌��ʂ𓾂�
	void GetPowerEffect(int chainNum, int combos) {

		powerCoeff = 0.5 * (double)combos + 1;	//�R���{���ɉ����ČW�����X�V
		powerTime = powerTime + (1000 + 50 * (chainNum - 4));	//�������ɉ����ăp���[�A�b�v���Ԃ��X�V

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "power up  coeff:%f, powerTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};

	//�X�s�[�h�u���b�N�����̌��ʂ𓾂�
	void GetSpeedEffect(int chainNum, int combos) {

		speedCoeff = 0.5 * (double)combos + 1;	//�R���{���ɉ����ČW�����X�V
		speedTime = speedTime + (1000 + 50 * (chainNum - 4));	//�������ɉ����ăX�s�[�h�A�b�v���Ԃ��X�V

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "speed up  coeff:%f, speedTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};

	//�o�u���u���b�N�����̌��ʂ𓾂�
	void GetBubbleEffect(int chainNum, int combos) {

		bubbleTime = bubbleTime + (800 + 50 * (chainNum - 4));	//�������ɉ����ăo�u����Ԃ̎��Ԃ��X�V
		invincibleTime = 0;	//���G���Ԃ�0�ɂ���

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "bubbleTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};

	//�_�u���u���b�N�����̌��ʂ𓾂�
	void GetDoubleEffect(int chainNum, int combos) {

		doubleTime = doubleTime + (900 + 50 * (chainNum - 4));	//�������ɉ����ă_�u����Ԃ̎��Ԃ��X�V
		shootFrame = 2;	//�ˌ��Ԋu�������ɂȂ�

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "doubleTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};
	
	//�e��ϐ��̍X�V
	void Update() {

		if (powerTime > 0) {	//�p���[�A�b�v���Ԃ�0���傫��������

			powerTime--;	//�p���[�A�b�v���Ԍ���
		}
		else {	//�p���[�A�b�v���Ԃ�0�ȉ���������

			powerCoeff = 1;	//�W����1�ɖ߂�
		}

		if (speedTime > 0) {	//�X�s�[�h�A�b�v���Ԃ�0���傫��������

			speedTime--;	//�X�s�[�h�A�b�v���Ԍ���
		}
		else {	//�X�s�[�h�A�b�v���Ԃ�0�ȉ���������

			speedCoeff = 1;	//�W����1�ɖ߂�
		}

		if (bubbleTime > 0) {	//�o�u����Ԃ̎c�莞�Ԃ�0���傫��������

			bubbleTime--;	//�c�莞�Ԍ���
		}

		if (doubleTime > 0) {	//�_�u����Ԃ̎c�莞�Ԃ�0���傫��������

			doubleTime--;	//�c�莞�Ԍ���
		}
		else {	//�_�u����Ԃ̎c�莞�Ԃ�0�ȉ���������

			shootFrame = 4;	//�ˌ��Ԋu��߂�
		}

		if (invincibleTime > 0) {	//���G���Ԃ�0���傫��������

			invincibleTime--;	//���G���Ԍ���
		}
	};

	//bullets�̐擪�C�e���[�^�擾
	auto GetBulletsBegin() {

		return bullets.begin();
	};

	//bullets�̖����C�e���[�^�擾
	auto GetBulletsEnd() {

		return bullets.end();
	};

	//HP���擾
	int GetHp() {

		return hp;
	};

	//���G���Ԃ��擾
	int GetInvincibleTime() {

		return invincibleTime;
	};
};