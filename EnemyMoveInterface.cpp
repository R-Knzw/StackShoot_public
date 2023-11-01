#pragma once

#define HEIGHT 1000
#define WIDTH 300
#define x0 810	//�ړ��\�͈͓��̍ŏ���x�@�t�B�[���h�̍��[

//�X�g���e�W�p�^�[���ɂ��G�̈ړ��p�^�[������
class EnemyMoveInterface {

protected:

	int frame;	//�o�߃t���[��
	int directionX;	//x�������̐���
	int directionY;	//Y�������̐���

public:

	virtual void Move(int dirX, int dirY, int width, int height, int* pos) = 0;
	virtual ~EnemyMoveInterface(){}
};

//�w������֓���������
class EnemyMove : public EnemyMoveInterface {

public:

	EnemyMove() {

		frame = 0;
	};

	void Move(int dirX, int dirY, int width, int height, int* pos) {

		pos[0] = pos[0] + dirX;
		pos[1] = pos[1] + dirY;
	};
};

//���E������
class EnemyMoveRoundTrip : public EnemyMoveInterface {

public:

	EnemyMoveRoundTrip() {

		frame = 0;
		directionX = 1;
	};

	void Move(int dirX, int dirY, int width, int height, int* pos) {

		if (pos[0] == x0 + WIDTH - width / 2) {

			directionX = -1;
		}
		else if(pos[0] == x0 - width /2){

			directionX = 1;
		}

		pos[0] = pos[0] + directionX * dirX;
	};
};

