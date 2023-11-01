#pragma once

#include "bullet.h"

//�e�N���X
class Bullet {

private:

	int imageHandle;	//�摜�ԍ�

	int pos[2];	//�e�̍��W(x,y)
	int width;	//�e�̕��i���̑傫���j
	int height;	//�e�̍����i�c�̑傫���j

	int speedX;	//�������̒e��
	int speedY;	//�c�����̒e��

	int power;	//�e�̃_���[�W

public:
	
	//�R���X�g���N�^
	Bullet(int x, int y, int speedX, int speedY, int power, int imageHandle) {

		this->imageHandle = imageHandle;

		GetGraphSize(imageHandle, &width, &height);
		pos[0] = x - width / 2;
		pos[1] = y;
		
		this->speedX = speedX;
		this->speedY = speedY;
		this->power = power;
	}

	//�e�̕`��
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);
	};

	//�e�̈ړ�
	void Move() {

		pos[0] += speedX;
		pos[1] += speedY;
	};

	//�ΏۂƂ̏Փ˔���
	bool CheckHit(int targetX, int targetY, int targetWidth, int targetHeight) {

		if (pos[0] <= targetX + targetWidth && pos[0] + width >= targetX) {

			if (pos[1] <= targetY + targetHeight && pos[1] + height >= targetY) {

				return TRUE;	//�Փ˂��Ă���	
			}
			else {

				return FALSE;	//�Փ˂��Ă��Ȃ�
			}
		}
		else {

			return FALSE;	//�Փ˂��Ă��Ȃ�
		}
	};

	//�ΏۂɃ_���[�W��^����
	int CalcDamage(int targetX, int targetY, int targetWidth, int targetHeight, double powerCoeff) {	

		int damage = power * powerCoeff;	//�^����_���[�W

		//�Փ˔���
		if (CheckHit(targetX, targetY, targetWidth, targetHeight) == TRUE) {	//�Փ˂��Ă�����

			return damage;	//�_���[�W��damage
		}
		else {	//�Փ˂��Ă��Ȃ�������

			return 0;	//�_���[�W��0
		}
	};

	//X���W�ipos[0]�j���擾
		int GetPosX() {

		return pos[0];
	};

	//Y���W�ipos[1]�j���擾
	int GetPosY() {

		return pos[1];
	};

	//�e�����擾
	int GetSpeedX() {

		return speedX;
	};

	//�e�����擾
	int GetSpeedY() {

		return speedY;
	};

	//�e�̃_���[�W���擾
	int GetPower() {

		return power;
	};

	//�e�̕����擾
	int GetWidth() {

		return width;
	};

	//�e�̍������擾
	int GetHeight() {

		return height;
	};
};