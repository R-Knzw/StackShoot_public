#pragma once

#include "stage.h"

class Stage {

public:

	int blockImages[7];	//�e��摜�̔ԍ�
	int enemyImage;		//�G�̉摜�ԍ�

	Block* dummy;	//�_�~�[�p�u���b�N
	std::vector<Block*> blocks;		//��ʏ�ɂ���u���b�N
	int blockNum;					//��ʏ�ɂ���u���b�N��
	int stack[XSIZE][YSIZE];		//���̍��W�ɐς݂��������u���b�N�̔ԍ����i�[

	bool columnsFilled[XSIZE];		//���̗񂪈�ԏ�܂Őς݂������Ă��邩

	Player* me;		//���@

	Enemy* enemy;	//�G

	int frame;		//�o�߃t���[��
	int makeFrame;	//�u���b�N�����Ԋu

	int fallSpeed;	//�u���b�N�̗������x
	bool stacked;	//���̃t���[���Ńu���b�N���ς܂ꂽ��

	//�R���X�g���N�^
	Stage(int makeFrame, int fallSpeed, int StageNum, char* enemyImageFile, EnemyMoveInterface* move, EnemyShootInterface* shoot, std::vector<char*> bulletNums) {

		//�����̏�����
		srand((unsigned)time(NULL));

		//�u���b�N�̉摜�ǂݍ���
		blockImages[0] = LoadGraph("./images/suka.png");
		blockImages[1] = LoadGraph("./images/bomb.png");
		blockImages[2] = LoadGraph("./images/heart.png");
		blockImages[3] = LoadGraph("./images/power.png");
		blockImages[4] = LoadGraph("./images/speed.png");
		blockImages[5] = LoadGraph("./images/bubble.png");
		blockImages[6] = LoadGraph("./images/double.png");

		//�G�̉摜�ǂݍ���
		enemyImage = LoadGraph(enemyImageFile);

		blockNum = 0;
		frame = 0;
		this->makeFrame = makeFrame;
		this->fallSpeed = fallSpeed;

		stacked = FALSE;

		dummy = new Block();	//�_�~�[�p�u���b�N
		dummy->InitDummy(-1, -100, -100, 0, 999, 0, FALSE, FALSE, FALSE, -1);	//�_�~�[��������

		me = new Player();	//���@

		enemy = new Enemy(enemyImage, move, shoot, bulletNums);	//�G

		//�f�o�b�O�o��//
		//OutputDebugString("Made Enemy\n\n");

		//stack�̏�����
		for (int i = 0; i < YSIZE; i++) {

			for (int j = 0; j < XSIZE; j++) {

				stack[j][i] = -1;

				//�f�o�b�O�o��//
				//char p[300];
				//sprintf_s(p, "%d ", stack[j][i]);
				//OutputDebugString(p);
			}

			//�f�o�b�O�o��//
			//OutputDebugString("\n");
		}

		//columnsFilled�̏�����
		for (int j = 0; j < XSIZE; j++) {

			columnsFilled[j] = FALSE;
		}

		//���[�v�ɂ��X�e�[�W�̏���
		int loop();
	}

	//�u���b�N�������̒T���t���O�𖢒T���ɏ�����
	void InitIsChecked() {

		for (int i = 0; i < YSIZE; i++) {

			for (int j = 0; j < XSIZE; j++) {

				int n = stack[j][i];

				if (n > -1) {	//���̈ʒu�Ƀu���b�N���ς݂������Ă����

					blocks[n]->SetIsChecked(FALSE);	//���̈ʒu�̃u���b�N�𖢒T���ɂ���
				}

			}
		}
	};
	
	//�u���b�N�̕`��
	void DrawBlocks() {

		for (int i = 0; i < blockNum; i++) {

			blocks[i]->Draw();
		}
	};

	//��ʂ̕`��
	void DrawAll() {

		DrawBlocks();	//�u���b�N�̕`��
		me->Draw();	//���@�Ǝ��@���������e��`��
		me->WriteStats();	//���@�̏���\��
		enemy->Draw();	//�G�ƓG���������e��`��
		enemy->WriteStats();	//�G�̏���\��
	};

	//�u���b�N�������\������
	bool CheckFrame() {

		if (frame % makeFrame == 0) {

			frame = 0;
			return TRUE;	//�����\
		}
		else {

			return FALSE;	//�����s��
		}
	};

	void MakeBlock() {

		int blockType;		//�u���b�N�̎��0-6
		int newX;			//�u���b�N�̐��������x���W
		int sX;				//newX�̃}�X�istack[x][y]��x�j

		
		if (blockNum < MAXBLOCKNUM) {	//�u���b�N�����ő�Ȃ���Ȃ��Ȃ�

			while(1) {	//�u���b�N�𐶐��ł���newX�ɂȂ�܂�newX��ݒ肵�Ȃ���
				
				sX = rand() % XSIZE;	//newX�������_���Ɍ���
				newX = x0 + sX * CELLSIZE;	//newX��sX�ɕϊ�

				//�f�o�b�O�o��//
				//char p[300];
				//sprintf_s(p, "new sX:%d\n", sX);
				//OutputDebugString(p);

				if (columnsFilled[sX] == FALSE) {	//�u���b�N�𐶐�����񂪋󂢂Ă�����

					//�f�o�b�O�o��//
					//OutputDebugString("\n");

					break;
				}
			} 
			
			blockType = rand() % BLOCKTYPENUM;	//7��ނ̒�����u���b�N�̎�ނ������_���Ō���
			//blockType = rand() % 3;	//�u���b�N�̎�ނ������_���Ō���
			//blockType = 3;			//�u���b�N�̎�ތŒ�

			//�u���b�N����
			if (blockType == 0) {

				blocks.push_back(new Suka(newX, -fallSpeed, blockImages[0], blockNum));	//�X�J�u���b�N����
			}
			else if (blockType == 1) {

				blocks.push_back(new Bomb(newX, -fallSpeed, blockImages[1], blockNum));	//���e�u���b�N����
			}
			else if (blockType == 2) {

				blocks.push_back(new Heart(newX, -fallSpeed, blockImages[2], blockNum));	//�n�[�g�u���b�N����
			}
			else if (blockType == 3) {

				blocks.push_back(new Power(newX, -fallSpeed, blockImages[3], blockNum));	//�p���[�u���b�N����
			}
			else if (blockType == 4) {

				blocks.push_back(new Speed(newX, -fallSpeed, blockImages[4], blockNum));	//�X�s�[�h�u���b�N����
			}
			else if (blockType == 5) {

				blocks.push_back(new Bubble(newX, -fallSpeed, blockImages[5], blockNum));	//�o�u���u���b�N����
			}
			else if (blockType == 6) {

				blocks.push_back(new Double(newX, -fallSpeed, blockImages[6], blockNum));	//�_�u���u���b�N����
			}

			//�f�o�b�O�o��//
			//char p[300];
			//sprintf_s(p, "made block type:%d num:%d\n", blockType, blockNum);
			//sprintf_s(p, "size of blocks[]:%d\n", blocks.size());
			//OutputDebugString(p);

			blockNum++;	//�u���b�N���X�V
		}
	};

	//�u���b�N�𗎉�������
	bool FallBlocks() {

		bool stacked = FALSE;	//���̃t���[���Ńu���b�N���ς݂����������ǂ���

		//�u���b�N�̗����ۂ𔻒�
		for (int i = 0; i < blockNum; i++) {	//�Â��u���b�N�i���̕��j���画��

			if (blocks[i]->GetIsFalling() == TRUE) {	//����Ώۂ̃u���b�N���������Ȃ�

				for (int j = 0; j < blockNum; j++) {	//�e�u���b�N�Ɣ�r

					if (blocks[j]->GetIsFalling() == FALSE) {	//��r�Ώۂ����łɐς݂������Ă���Ȃ�

						if (blocks[i]->GetPosX() == blocks[j]->GetPosX() && blocks[i]->GetPosY() + CELLSIZE >= blocks[j]->GetPosY()) {	//����Ώۂ̃u���b�N�̂����^���ɔ�r�Ώۂ̃u���b�N����������

							blocks[i]->SetIsFalling(FALSE);	//����Ώۂ̃u���b�N�͗�������߂Đς݂�����
							blocks[i]->SetIsStacked(TRUE);
							stack[(blocks[i]->GetPosX() - x0) / CELLSIZE][blocks[i]->GetPosY() / CELLSIZE] = i;	//stack�ɐς݂��������u���b�N��blocks�ɂ�����C���f�b�N�X��ێ�������
							stacked = TRUE;	//���̃t���[���Ńu���b�N���ς݂�������

							break;
						}
					}
				}

				if (blocks[i]->GetIsFalling() == FALSE) {	//����Ώۂ̃u���b�N���������łȂ�������i���̏����Őς݂���������j

					continue;
				}
				else {	//����Ώۂ̃u���b�N���������Ȃ�i���̏����Őς݂������ĂȂ�������j

					if (blocks[i]->GetPosY() + CELLSIZE == HEIGHT) {	//����Ώۂ̃u���b�N�̂����^�����n�ʂȂ�

						blocks[i]->SetIsFalling(FALSE);	//����Ώۂ̃u���b�N�͗�������߂Đς݂�����
						blocks[i]->SetIsStacked(TRUE);
						stack[(blocks[i]->GetPosX() - x0) / CELLSIZE][blocks[i]->GetPosY() / CELLSIZE] = i;	//stack�ɐς݂��������u���b�N��blocks�ɂ�����C���f�b�N�X��ێ�������
						stacked = TRUE;
					}
					else {	//����Ώۂ̃u���b�N�̂����^�����n�ʂłȂ��Ȃ�

						blocks[i]->fall(fallSpeed);	//�u���b�N�𗎉�������
					}
				}
			}
		}

		return stacked;
	};

	//�u���b�N����܂Őς݂����肫���Ă��邩����
	int CheckColumns() {

		int n = 0;	//��܂Őς݂����肫���Ă����̉���

		for (int j = 0; j < XSIZE; j++) {	//�e��ɂ���

			if (stack[j][0] > -1) {	//1�ԏ�̈ʒu�Ƀu���b�N���ς݂������Ă����

				columnsFilled[j] = TRUE;	//�u���b�N����܂Őς݂����肫���Ă���
				n++;
			}
			else {	//1�ԏ�̈ʒu�Ƀu���b�N���ς݂������Ă��Ȃ����

				columnsFilled[j] = FALSE;	//�u���b�N����܂Őς݂����肫���Ă��Ȃ�
			}
		}

		return n;
	};

	//�u���b�N�̐ς݂Ȃ����i�u���b�N�����ɂ��󂢂��X�y�[�X�����ɋl�߂�j
	void Restack() {

		for (int i = 0; i < blockNum; i++) {	//�Â��u���b�N�i���̕��j���画��

			if (blocks[i]->GetIsStacked() == TRUE) {	//����Ώۂ̃u���b�N���ς݂������Ă�����

				int sx = (blocks[i]->GetPosX() - x0) / CELLSIZE;	//�ς݂Ȃ����O��stack�z��ɂ�����C���f�b�N�X���v�Z
				int sy = blocks[i]->GetPosY() / CELLSIZE;

				while (sy < YSIZE - 1) {	//����Ώۂ̃u���b�N�̐^���ɂ���u���b�N�Ɣ�r

					if (stack[sx][sy + 1] >= 0) {	//�����^���Ƀu���b�N���ς݂������Ă�����

						break;	//�������Ȃ��i�������Ȃ��j
					}
					else {	//�����^���Ƀu���b�N���ς݂������Ă��Ȃ��Ȃ�

						stack[sx][sy] = -1;	//���̈ʒu�Ƀu���b�N�͐ς܂�Ă��Ȃ����̂ƂȂ�
						sy++;	//����Ώۂ̃u���b�N������
					}
				}

				stack[sx][sy] = i;	//����Ώۂ̃u���b�N�̃C���f�b�N�X��V�����ʒu�Ɋi�[
				blocks[i]->SetPosY(sy * CELLSIZE);	//�ς݂Ȃ�����̍��W���X�V
			}
		}

		WaitTimer(500);	//�ꎞ��~�i���o�j

		ClearDrawScreen();
		DrawBlocks();	//�ς݂Ȃ�����̃u���b�N�̕`��
		ScreenFlip();
	};

	//�����\�Ȍ�₩�ǂ����C�u���b�N��T��
	int CheckErasableBlock(int x, int y, int chainNum, int eraseList[MAXBLOCKNUM][2]) {

		int n;	//���̈ʒu�ɐς݂������Ă���u���b�N��blocks�ɂ�����C���f�b�N�X�i�ς݂������Ă��Ȃ��Ȃ�-1�ƂȂ�j
		n = stack[x][y];

		//�f�o�b�O�o��//
		//char p[300];
		//sprintf_s(p, "visit (%d,%d)\n", x, y);
		//OutputDebugString(p);

		if (n > -1) {	//���̈ʒu�Ƀu���b�N���ς݂������Ă�����

			if (blocks[n]->GetIsChecked() == FALSE) {	//���̃u���b�N�����T���Ȃ�

				blocks[n]->SetIsChecked(TRUE);	//�T���t���O��T���ς݂ɂ���

				if (y - 1 >= 0) {	//��ɐς݂��������u���b�N�����݂�����Ȃ�

					if (stack[x][y - 1] != -1) {	//��Ƀu���b�N���ς݂������Ă���Ȃ�

						if (blocks[stack[x][y - 1]]->GetType() == blocks[n]->GetType() && (blocks[stack[x][y - 1]]->GetIsChecked() == FALSE)) {	//��̃u���b�N�ƒT�����̃u���b�N������ނȂ�

							chainNum = CheckErasableBlock(x, y - 1, chainNum, eraseList);	//��̃u���b�N��T������

						}
					}
				}
				if (y + 1 < YSIZE) {

					if (stack[x][y + 1] != -1) {

						if (blocks[stack[x][y + 1]]->GetType() == blocks[n]->GetType() && (blocks[stack[x][y + 1]]->GetIsChecked() == FALSE)) {

							chainNum = CheckErasableBlock(x, y + 1, chainNum, eraseList);

						}
					}
				}
				if (x - 1 >= 0) {

					if (stack[x - 1][y] != -1) {

						if (blocks[stack[x - 1][y]]->GetType() == blocks[n]->GetType() && (blocks[stack[x - 1][y]]->GetIsChecked() == FALSE)) {

							chainNum = CheckErasableBlock(x - 1, y, chainNum, eraseList);

						}
					}
				}
				if (x + 1 < XSIZE) {

					if (stack[x + 1][y] != -1) {

						if (blocks[stack[x + 1][y]]->GetType() == blocks[n]->GetType() && (blocks[stack[x + 1][y]]->GetIsChecked() == FALSE)) {

							chainNum = CheckErasableBlock(x + 1, y, chainNum, eraseList);

						}
					}
				}

				eraseList[chainNum][0] = x;	//�������̃��X�g�ɒT�����̃u���b�N�̐ς݂������Ă���ʒu������
				eraseList[chainNum][1] = y;

				return chainNum + 1;	//����ނ̃u���b�N�Ōq�����Ă������1���₷
			}
			else {	//�u���b�N���T���ς݂Ȃ�

				return 0;	//����ނ̃u���b�N�Ōq�����Ă������0�i�T���ς݂Ȃ̂ŒT�����Ȃ��j
			}
		}
		else {	//���̈ʒu�Ƀu���b�N���ς݂������Ă��Ȃ��Ȃ�

			return 0;	//����ނ̃u���b�N�Ōq�����Ă������0
		}
	};

	void SpliceVector() {	//Vector�̗v�f���l�߂�

		auto itr = blocks.begin();

		while (itr != blocks.end()) {

			if (*itr == dummy) {	//�u���b�N���_�~�[�Ȃ�

				itr = blocks.erase(itr);	//vector���炻�̗v�f������
			}
			else {

				itr++;
			}
		}

		blockNum = blocks.size();	//�u���b�N���X�V

		for (int i = 0; i < blockNum; i++) {	//�C���f�b�N�X���X�V
			blocks[i]->SetIndex(i);
		}
	};
	
	//�u���b�N����
	int EraseBlocks(int combos) {

		InitIsChecked();	//�T���t���O�̏�����
		bool erased = FALSE;	//�����ɐ����������ǂ���

		//char p[300];

		for (int i = YSIZE - 1; i >= 0; i--) {	//�E�̃u���b�N����

			for (int j = XSIZE - 1; j >= 0; j--) {	//���̃u���b�N����

				int chainNum = 0;	//����ނ̃u���b�N�Ōq�����Ă����
				int eraseList[MAXBLOCKNUM][2];	//�����u���b�N�̌��

				
				chainNum = CheckErasableBlock(j, i, chainNum, eraseList);	//�u���b�N��T�����C����ނŌq�����Ă�����𓾂�

				//�f�o�b�O�o��//
				//sprintf_s(p, "position (%d,%d) chainNum:%d\n",j,i, chainNum);
				//OutputDebugString(p);
				
				if (chainNum >= 4) {	//4�ȏ�Ōq�����Ă�����

					me->GetEffect(blocks[stack[j][i]]->GetType(), chainNum, combos + 1);	//�T�������u���b�N�̎�ށC�q�����Ă�����C�R���{���ɉ����Č��ʂ𓾂�

					erased = TRUE;	//�����ɐ���

					//�u���b�N������
					for (int i = 0; i < chainNum; i++) {

						int x = eraseList[i][0];	//�������ɓ����Ă�����W�istack�̃C���f�b�N�X�j
						int y = eraseList[i][1];

						//�f�o�b�O�o��//
						//OutputDebugString("erased\n");

						delete blocks[stack[x][y]];	//��������u���b�N�̃I�u�W�F�N�g���폜
						blocks[stack[x][y]] = dummy;	//�폜����blocks�̗v�f����Udummy�ɂ���
						stack[x][y] = -1;	//���̈ʒu�Ƀu���b�N�͂Ȃ��Ȃ�

					}
				}
			}
		}

		if (erased == TRUE) {	//�����ɐ���������

			SpliceVector();	//dummy�ɂ���blocks�̗v�f���폜���ċl�߂�

			Restack();	//�ς݂������Ă����u���b�N�����ɋl�߂�

			return combos + 1;	//�R���{����1���₷
		}
		else {	//�������s

			return 0;	//�R���{��0
		}
	};

	//1�ԉ��̍s�̃u���b�N���폜
	void EraseBottom() {

		for (int i = 0; i < XSIZE; i++) {	//�E����

			if (stack[i][YSIZE - 1] != -1) {	//�u���b�N���ς܂�Ă�����

				delete blocks[stack[i][YSIZE - 1]];	//��������u���b�N�̃I�u�W�F�N�g���폜
				blocks[stack[i][YSIZE - 1]] = dummy;	//�폜����blocks�̗v�f����Udummy�ɂ���
				stack[i][YSIZE - 1] = -1;	//���̈ʒu�Ƀu���b�N�͂Ȃ��Ȃ�
			}
		}

		SpliceVector();	//dummy�ɂ���blocks�̗v�f���폜���ċl�߂�

		Restack();	//�ς݂������Ă����u���b�N�����ɋl�߂�
	};

	//���@���u���b�N�Ƀ_���[�W��^����
	void AttackBlocks(){

		auto itr = blocks.begin();

		while (itr != blocks.end()) {	//�e�u���b�N�ɑ΂�

			if ((*itr)->GetIsFalling() == TRUE) {	//�������̃u���b�N�Ȃ�

				int damage;	//�_���[�W

				damage = me->DealDamage((*itr)->GetPosX(), (*itr)->GetPosY(), (*itr)->GetSize(), (*itr)->GetSize());	//�_���[�W�v�Z
				(*itr)->RecieveDamage(damage);	//�_���[�W��^����

				if ((*itr)->GetHp() <= 0) {	//�u���b�N��HP��0�ȉ��ɂȂ�����

					delete *itr;	//�u���b�N�̃I�u�W�F�N�g�폜
					itr = blocks.erase(itr);	//���̗v�f���폜
				}
				else {	//�u���b�N��HP��0���傫��������

					itr++;
				}
			}
			else {	//�������̃u���b�N����Ȃ��Ȃ�

				itr++;
			}
		}

		blockNum = blocks.size();	//�u���b�N���X�V
	};

	//���@���G�Ƀ_���[�W��^����
	void AttackEnemy() {

		int damage;	//�_���[�W

		damage = me->DealDamage(enemy->GetPosX(), enemy->GetPosY(), enemy->GetWidth(), enemy->GetHeight());	//�_���[�W�v�Z
		enemy->RecieveDamage(damage);	//�_���[�W��^����
	};

	//���@���u���b�N��G�Ƀ_���[�W��^����
	void Attack() {

		AttackBlocks();
		AttackEnemy();
	};

	//���@���u���b�N����_���[�W���󂯂�
	void RecieveDamageFromBlocks() {

		for (int i = 0; i < blockNum; i++) {	//�e�u���b�N�ɑ΂�

			me->RecieveDamage(blocks[i]->GetPosX(), blocks[i]->GetPosY(), blocks[i]->GetSize(), blocks[i]->GetSize(), blocks[i]->GetPower());	//�_���[�W���󂯂�
		}
	};

	//���@���G�̒e����_���[�W���󂯂�
	void RecieveDamageFromBullets() {

		auto itr = enemy->GetBulletsBegin();

		while (itr != enemy->GetBulletsEnd()) {	//�G�̊e�e�ɑ΂�

			me->RecieveDamage((*itr)->GetPosX(), (*itr)->GetPosY(), (*itr)->GetWidth(), (*itr)->GetHeight(), (*itr)->GetPower());
			itr++;
		}
	};

	//���@���u���b�N��G����_���[�W���󂯂�
	void RecieveDamage() {

		RecieveDamageFromBlocks();
		me->RecieveDamage(enemy->GetPosX(), enemy->GetPosY(), enemy->GetWidth(), enemy->GetHeight(), enemy->GetPower());	//�G�{�̂���_���[�W���󂯂�
		RecieveDamageFromBullets();		
	};

	//���[�v�ɂ��X�e�[�W�̏���
	int loop() {

		int result = 0;	//����

		while (1) {

			int combos = 0;	//�R���{���i����A���ŏ����������������j

			ClearDrawScreen();	//��ʂ̕`��N���A

			//�u���b�N����
			if (CheckFrame() == TRUE) {

				MakeBlock();
			}

			stacked = FallBlocks();	//�u���b�N�̐ς݂���


			//�u���b�N����
			if (stacked == TRUE) {

				combos = EraseBlocks(combos);

				while (combos >= 1) {	//�����Ɏ��s����܂�

					//�f�o�b�O�p//
					//int k;
					//k = WaitKey();
					//if (k == KEY_INPUT_ESCAPE) {
					//	break;
					//}

					combos = EraseBlocks(combos);
				}
			};

			//���@�̈ړ�
			if (CheckHitKey(KEY_INPUT_UP) == 1) {

				me->Move(0, -1);
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) {

				me->Move(0, 1);
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {

				me->Move(1, 0);
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {

				me->Move(-1, 0);
			}

			//�G�̈ړ�
			enemy->Move();
			
			//�e���ړ�
			me->MoveBullets();
			enemy->MoveBullets();

			//�ˌ�
			me->Shoot();
			enemy->Shoot();

			//���e�̎g�p
			if (me->UseBomb() == TRUE) {

				EraseBottom();
			}

			//�u���b�N��G�C�e�Ƃ̐ڐG����i���g���_���[�W���󂯂�j
			if (me->GetInvincibleTime() == 0) {

				RecieveDamage();
			}

			//���@��HP�`�F�b�N
			if (me->GetHp() <= 0) {

				result = -1;

				break;
			}

			//�u���b�N��G�Ƀ_���[�W��^����
			Attack();

			//�G��HP�`�F�b�N
			if (enemy->GetHp() <= 0) {

				result = 0;

				break;
			}

			//��ʕ`��
			DrawAll();

			//��ʕ`��̔��f
			ScreenFlip();

			if (CheckColumns() == XSIZE) {

				result = -2;

				break;
			}

			//�f�o�b�O�p//
			//int k;
			//k = WaitKey();
			//if (k == KEY_INPUT_ESCAPE) {
			//	break;
			//}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

				result = 10;
				break;
			}

			frame++;		//�t���[���o��

			me->Update();	//powerTime�ȂǊe��ϐ����X�V
		}

		//�I�u�W�F�N�g�̍폜
		delete dummy;

		auto itr1 = blocks.begin();
		while (itr1 != blocks.end()) {

			delete* itr1;
			itr1++;
		}

		auto itr2 = me->GetBulletsBegin();
		while (itr2 != me->GetBulletsEnd()) {

			delete* itr2;
			itr2++;
		}
		delete me;
/*
		auto itr3 = enemy->GetBulletsBegin();
		while (itr3 != me->GetBulletsEnd()) {

			delete* itr3;
			itr3++;
		}
		delete enemy;
		*/
		return result;
	};
};