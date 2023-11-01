#pragma once

#include "Bullet.cpp"
#include <vector>

//�X�g���e�W�p�^�[���ɂ��G�̎ˌ��p�^�[������
class EnemyShootInterface {

protected:

	int frame; //�o�߃t���[��
	int shootFrame;	//�ˌ��Ԋu

public:

	virtual void Shoot(int x, int y, int speedX, int speedY, int power, std::vector<int>* bulletImageHandle, std::vector<Bullet*>* bullets) = 0;
	virtual ~EnemyShootInterface() {}
};

//�e�𔭎�
class EnemyShoot : public EnemyShootInterface {

public:

	EnemyShoot() {

		frame = 0;
		shootFrame = 30;
	};

	void Shoot(int x, int y, int speedX, int speedY, int power, std::vector<int>* bulletImageHandle, std::vector<Bullet*>* bullets) {

		if (frame < shootFrame) {

			frame++;			
		}
		else {

			bullets->push_back(new Bullet(x, y, speedX, speedY, power, (*bulletImageHandle)[0]));
			frame = 0;
		}
	};
};