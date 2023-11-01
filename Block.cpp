#pragma once

#include "block.h";

//�u���b�N�N���X �e�N���X
class Block {

protected:

	int imageHandle;	//�摜�ԍ�

	int pos[2];			//�u���b�N�̍��W(x,y)
	int size;			//�u���b�N��1�ӂ̑傫���i���ƍ����j

	int hp;				//HP�@�u���b�N�̑ϋv�l
	int power;			//�u���b�N�ƏՓ˂����ۂ̃_���[�W

	bool isFalling;		//���������ǂ���
	bool isStacked;		//�ς݂������Ă��邩�ǂ���
	bool isChecked;		//�������莞�̒T���t���O

	int index;			//blocks�z��ɂ����鎩�g�̃C���f�b�N�X	

public:

	//�_�~�[�p�I�u�W�F�N�g��������
	void InitDummy(int imageHandle, int posX, int posY,int size, int hp, int power, bool isFalling, bool isStacked, bool isChecked, int index) {

		this->imageHandle = imageHandle;
		this->pos[0] = posX;
		this->pos[1] = posY;
		this->hp = hp;
		this->isFalling = isFalling;
		this->isStacked = isStacked;
		this->isChecked = isChecked;
		this->index = index;
	};

	//�u���b�N�̕`��
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);
	};

	//�u���b�N�̗���
	void fall(int fallSpeed) {

		pos[1] += fallSpeed;
	};

	//�_���[�W���󂯂�
	void RecieveDamage(int damage) {

		hp = hp - damage;
	};
	
	//y���W���X�V
	void SetPosY(int y) {
		pos[1] = y;
	};

	//���������ǂ������X�V
	void SetIsFalling(bool isFalling) {

		this->isFalling = isFalling;
	};

	//�ς݂������Ă��邩�ǂ������X�V
	void SetIsStacked(bool isStacked) {

		this->isStacked = isStacked;
	};

	//�T���t���O���X�V
	void SetIsChecked(bool isChecked) {

		this->isChecked = isChecked;
	};

	//�C���f�b�N�X�̍X�V
	void SetIndex(int index) {

		this->index = index;
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
	int GetSize() {

		return size;
	};

	//HP�擾
	int GetHp() {

		return hp;
	};

	//�p���[�擾
	int GetPower() {

		return power;
	};
	
	//���������ǂ�����m��
	bool GetIsFalling() {

		return isFalling;
	};

	//�ς݂������Ă��邩�ǂ�����m��
	bool GetIsStacked() {

		return isStacked;
	};

	//�T���t���O���擾
	bool GetIsChecked() {
		return isChecked;
	};

	//�u���b�N�̎�ނ��擾
	virtual int GetType() {

		return -1;
	};
};

//�X�J�u���b�N�N���X�@�q�N���X
class Suka : public Block {

public:

	//�R���X�g���N�^
	Suka(int x, int y, int imageHandle, int blockNum) {

		this->imageHandle = imageHandle;

		pos[0] = x;
		pos[1] = y;
		size = 50;

		hp = 300;
		power = 20;
		
		isFalling = TRUE;
		isStacked = FALSE;
		isChecked = FALSE;

		index = blockNum;		
	}

	//�u���b�N�̎�ނ��擾
	int GetType() {

		return 0;
	};
};

//���e�u���b�N�N���X�@�q�N���X
class Bomb : public Block {

public:

	//�R���X�g���N�^
	Bomb(int x, int y, int imageHandle, int blockNum) {

		this->imageHandle = imageHandle;

		pos[0] = x;
		pos[1] = y;
		size = 50;

		hp = 800;
		power = 20;
		
		isFalling = TRUE;
		isStacked = FALSE;
		isChecked = FALSE;

		index = blockNum;
	}

	//�u���b�N�̎�ނ��擾
	int GetType() {

		return 1;
	};
};

//�n�[�g�u���b�N�N���X�@�q�N���X
class Heart : public Block {

public:

	//�R���X�g���N�^
	Heart(int x, int y, int imageHandle, int blockNum) {

		this->imageHandle = imageHandle;

		pos[0] = x;
		pos[1] = y;
		size = 50;

		hp = 800;
		power = 20;

		isFalling = TRUE;
		isStacked = FALSE;
		isChecked = FALSE;

		index = blockNum;
	}
	
	//�u���b�N�̎�ނ��擾
	int GetType() {

		return 2;
	};
};

//�p���[�u���b�N�N���X�@�q�N���X
class Power : public Block {

public:

	//�R���X�g���N�^
	Power(int x, int y, int imageHandle, int blockNum) {

		this->imageHandle = imageHandle;

		pos[0] = x;
		pos[1] = y;
		size = 50;

		hp = 500;
		power = 20;

		isFalling = TRUE;
		isStacked = FALSE;
		isChecked = FALSE;

		index = blockNum;
	}

	//�u���b�N�̎�ނ��擾
	int GetType() {

		return 3;
	};
};

//�X�s�[�h�u���b�N�N���X�@�q�N���X
class Speed : public Block {

public:

	//�R���X�g���N�^
	Speed(int x, int y, int imageHandle, int blockNum) {

		this->imageHandle = imageHandle;

		pos[0] = x;
		pos[1] = y;
		size = 50;

		hp = 500;
		power = 20;

		isFalling = TRUE;
		isStacked = FALSE;
		isChecked = FALSE;

		index = blockNum;
	}

	//�u���b�N�̎�ނ��擾
	int GetType() {

		return 4;
	};
};

//�o�u���u���b�N�N���X�@�q�N���X
class Bubble : public Block {

public:

	//�R���X�g���N�^
	Bubble(int x, int y, int imageHandle, int blockNum) {

		this->imageHandle = imageHandle;

		pos[0] = x;
		pos[1] = y;
		size = 50;

		hp = 1000;
		power = 20;

		isFalling = TRUE;
		isStacked = FALSE;
		isChecked = FALSE;

		index = blockNum;
	}

	//�u���b�N�̎�ނ��擾
	int GetType() {

		return 5;
	};
};

//�_�u���u���b�N�N���X�@�q�N���X
class Double : public Block {

public:

	//�R���X�g���N�^
	Double(int x, int y, int imageHandle, int blockNum) {

		this->imageHandle = imageHandle;

		pos[0] = x;
		pos[1] = y;
		size = 50;

		hp = 800;
		power = 20;

		isFalling = TRUE;
		isStacked = FALSE;
		isChecked = FALSE;

		index = blockNum;
	}

	//�u���b�N�̎�ނ��擾
	int GetType() {

		return 6;
	};
};