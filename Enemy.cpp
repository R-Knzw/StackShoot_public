#pragma once

#include "enemy.h"

class Enemy {

private:

	int imageHandle;	//�G�̉摜�ԍ�
	std::vector<char*> bulletImageIndex;	//�e�̉摜�t�@�C���̃C���f�b�N�X
	std::vector<int> bulletImageHandle;	//�e�̉摜�ԍ�

	int pos[2];	//�G�̍��W
	int width;	//�G�̕��i���̑傫���j
	int height;	//�G�̍����i�c�̑傫���j
	
	std::vector<Bullet*> bullets;		//�������e����

	int hp;		//�̗�
	int power;	//�G�ɐG�ꂽ���̃_���[�W

	int frame;	//�o�߃t���[��

	EnemyMoveInterface* move;	//�s���p�^�[��
	EnemyShootInterface* shoot;	//�ˌ��p�^�[��

public:

	//�R���X�g���N�^
	Enemy(int imageHandle, EnemyMoveInterface* move, EnemyShootInterface* shoot, std::vector<char*> bulletNums) {

		this->imageHandle = imageHandle;

		GetGraphSize(imageHandle, &width, &height);
		pos[0] = (WIDTH / 2 - width / 2) + x0;
		pos[1] = 0;

		//�f�o�b�O�o��
		//char p[300];
		//sprintf_s(p, "enemy pos:%d,%d\n\n", pos[0], pos[1]);
		//OutputDebugString(p);

		hp = 20000;
		power = 40;

		bulletImageIndex = bulletNums;

		for (int i = 0; i < bulletImageIndex.size(); i++) {

			char f[256];
			sprintf_s(f, "./images/bullet%s.png", bulletImageIndex[i]);
			bulletImageHandle.push_back(LoadGraph(f));
		}
		this->move = move;
		this->shoot = shoot;
	}

	//�`��
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);	//�G�̕`��

		for (int i = 0; i < bullets.size(); i++) {

			bullets[i]->Draw();	//�e�̕`��
		}
	};

	//�e����̕\��
	void WriteStats() {

		unsigned int color = GetColor(255, 255, 255);	//���������g��

		DrawFormatString(600, 50, color, "HP:%d", hp);
	};

	void Move() {

		move->Move(1, 0, width, height, pos);
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

			if ((*itr)->GetPosX() < x0 -(*itr)->GetWidth() || (*itr)->GetPosX() > x0 + WIDTH || (*itr)->GetPosY() < - (*itr)->GetSpeedY() || (*itr)->GetPosY() > HEIGHT + (*itr)->GetHeight()) {	//��ʊO�Ȃ�

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

		shoot->Shoot(pos[0] + width / 2, pos[1] + height / 2, 0, 5, 20, &bulletImageHandle, &bullets);

		//�f�o�b�O�o��
		//char p[256];
		//sprintf_s(p, "enemy bullets[] size:%d\n\n", bullets.size());
		//OutputDebugString(p);
	};

	//�_���[�W���󂯂�
	void RecieveDamage(int damage) {

		hp = hp - damage;
	};

	//x���W���擾
	int GetPosX() {

		return pos[0];
	};

	//y���W���擾
	int GetPosY() {

		return pos[1];
	};

	//�傫�����擾
	int GetWidth() {

		return width;
	};

	//HP�擾
	int GetHp() {

		return hp;
	};

	//�����擾
	int GetHeight() {

		return height;
	};

	//�������擾
	int GetPower() {

		return power;
	};

	//bullets�̐擪�C�e���[�^�擾
	auto GetBulletsBegin() {

		return bullets.begin();
	};

	//bullets�̖����C�e���[�^�擾
	auto GetBulletsEnd() {

		return bullets.end();
	};
};

