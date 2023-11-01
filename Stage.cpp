#pragma once

#include "stage.h"

class Stage {

public:

	int blockImages[7];	//各種画像の番号
	int enemyImage;		//敵の画像番号

	Block* dummy;	//ダミー用ブロック
	std::vector<Block*> blocks;		//画面上にあるブロック
	int blockNum;					//画面上にあるブロック数
	int stack[XSIZE][YSIZE];		//その座標に積みあがったブロックの番号を格納

	bool columnsFilled[XSIZE];		//その列が一番上まで積みあがっているか

	Player* me;		//自機

	Enemy* enemy;	//敵

	int frame;		//経過フレーム
	int makeFrame;	//ブロック生成間隔

	int fallSpeed;	//ブロックの落下速度
	bool stacked;	//そのフレームでブロックが積まれたか

	//コンストラクタ
	Stage(int makeFrame, int fallSpeed, int StageNum, char* enemyImageFile, EnemyMoveInterface* move, EnemyShootInterface* shoot, std::vector<char*> bulletNums) {

		//乱数の初期化
		srand((unsigned)time(NULL));

		//ブロックの画像読み込み
		blockImages[0] = LoadGraph("./images/suka.png");
		blockImages[1] = LoadGraph("./images/bomb.png");
		blockImages[2] = LoadGraph("./images/heart.png");
		blockImages[3] = LoadGraph("./images/power.png");
		blockImages[4] = LoadGraph("./images/speed.png");
		blockImages[5] = LoadGraph("./images/bubble.png");
		blockImages[6] = LoadGraph("./images/double.png");

		//敵の画像読み込み
		enemyImage = LoadGraph(enemyImageFile);

		blockNum = 0;
		frame = 0;
		this->makeFrame = makeFrame;
		this->fallSpeed = fallSpeed;

		stacked = FALSE;

		dummy = new Block();	//ダミー用ブロック
		dummy->InitDummy(-1, -100, -100, 0, 999, 0, FALSE, FALSE, FALSE, -1);	//ダミーを初期化

		me = new Player();	//自機

		enemy = new Enemy(enemyImage, move, shoot, bulletNums);	//敵

		//デバッグ出力//
		//OutputDebugString("Made Enemy\n\n");

		//stackの初期化
		for (int i = 0; i < YSIZE; i++) {

			for (int j = 0; j < XSIZE; j++) {

				stack[j][i] = -1;

				//デバッグ出力//
				//char p[300];
				//sprintf_s(p, "%d ", stack[j][i]);
				//OutputDebugString(p);
			}

			//デバッグ出力//
			//OutputDebugString("\n");
		}

		//columnsFilledの初期化
		for (int j = 0; j < XSIZE; j++) {

			columnsFilled[j] = FALSE;
		}

		//ループによるステージの処理
		int loop();
	}

	//ブロック消去時の探索フラグを未探索に初期化
	void InitIsChecked() {

		for (int i = 0; i < YSIZE; i++) {

			for (int j = 0; j < XSIZE; j++) {

				int n = stack[j][i];

				if (n > -1) {	//その位置にブロックが積みあがっていれば

					blocks[n]->SetIsChecked(FALSE);	//その位置のブロックを未探索にする
				}

			}
		}
	};
	
	//ブロックの描画
	void DrawBlocks() {

		for (int i = 0; i < blockNum; i++) {

			blocks[i]->Draw();
		}
	};

	//画面の描画
	void DrawAll() {

		DrawBlocks();	//ブロックの描画
		me->Draw();	//自機と自機が撃った弾を描画
		me->WriteStats();	//自機の情報を表示
		enemy->Draw();	//敵と敵が撃った弾を描画
		enemy->WriteStats();	//敵の情報を表示
	};

	//ブロック生成が可能か判定
	bool CheckFrame() {

		if (frame % makeFrame == 0) {

			frame = 0;
			return TRUE;	//生成可能
		}
		else {

			return FALSE;	//生成不可
		}
	};

	void MakeBlock() {

		int blockType;		//ブロックの種類0-6
		int newX;			//ブロックの生成されるx座標
		int sX;				//newXのマス（stack[x][y]のx）

		
		if (blockNum < MAXBLOCKNUM) {	//ブロック数が最大なら作らないなら

			while(1) {	//ブロックを生成できるnewXになるまでnewXを設定しなおす
				
				sX = rand() % XSIZE;	//newXをランダムに決定
				newX = x0 + sX * CELLSIZE;	//newXをsXに変換

				//デバッグ出力//
				//char p[300];
				//sprintf_s(p, "new sX:%d\n", sX);
				//OutputDebugString(p);

				if (columnsFilled[sX] == FALSE) {	//ブロックを生成する列が空いていたら

					//デバッグ出力//
					//OutputDebugString("\n");

					break;
				}
			} 
			
			blockType = rand() % BLOCKTYPENUM;	//7種類の中からブロックの種類をランダムで決定
			//blockType = rand() % 3;	//ブロックの種類をランダムで決定
			//blockType = 3;			//ブロックの種類固定

			//ブロック生成
			if (blockType == 0) {

				blocks.push_back(new Suka(newX, -fallSpeed, blockImages[0], blockNum));	//スカブロック生成
			}
			else if (blockType == 1) {

				blocks.push_back(new Bomb(newX, -fallSpeed, blockImages[1], blockNum));	//爆弾ブロック生成
			}
			else if (blockType == 2) {

				blocks.push_back(new Heart(newX, -fallSpeed, blockImages[2], blockNum));	//ハートブロック生成
			}
			else if (blockType == 3) {

				blocks.push_back(new Power(newX, -fallSpeed, blockImages[3], blockNum));	//パワーブロック生成
			}
			else if (blockType == 4) {

				blocks.push_back(new Speed(newX, -fallSpeed, blockImages[4], blockNum));	//スピードブロック生成
			}
			else if (blockType == 5) {

				blocks.push_back(new Bubble(newX, -fallSpeed, blockImages[5], blockNum));	//バブルブロック生成
			}
			else if (blockType == 6) {

				blocks.push_back(new Double(newX, -fallSpeed, blockImages[6], blockNum));	//ダブルブロック生成
			}

			//デバッグ出力//
			//char p[300];
			//sprintf_s(p, "made block type:%d num:%d\n", blockType, blockNum);
			//sprintf_s(p, "size of blocks[]:%d\n", blocks.size());
			//OutputDebugString(p);

			blockNum++;	//ブロック数更新
		}
	};

	//ブロックを落下させる
	bool FallBlocks() {

		bool stacked = FALSE;	//そのフレームでブロックが積みあがったかどうか

		//ブロックの落下可否を判定
		for (int i = 0; i < blockNum; i++) {	//古いブロック（下の方）から判定

			if (blocks[i]->GetIsFalling() == TRUE) {	//判定対象のブロックが落下中なら

				for (int j = 0; j < blockNum; j++) {	//各ブロックと比較

					if (blocks[j]->GetIsFalling() == FALSE) {	//比較対象がすでに積みあがっているなら

						if (blocks[i]->GetPosX() == blocks[j]->GetPosX() && blocks[i]->GetPosY() + CELLSIZE >= blocks[j]->GetPosY()) {	//判定対象のブロックのすぐ真下に比較対象のブロックがあったら

							blocks[i]->SetIsFalling(FALSE);	//判定対象のブロックは落下をやめて積みあがる
							blocks[i]->SetIsStacked(TRUE);
							stack[(blocks[i]->GetPosX() - x0) / CELLSIZE][blocks[i]->GetPosY() / CELLSIZE] = i;	//stackに積みあがったブロックのblocksにおけるインデックスを保持させる
							stacked = TRUE;	//そのフレームでブロックが積みあがった

							break;
						}
					}
				}

				if (blocks[i]->GetIsFalling() == FALSE) {	//判定対象のブロックが落下中でなかったら（↑の処理で積みあがったら）

					continue;
				}
				else {	//判定対象のブロックが落下中なら（↑の処理で積みあがってなかったら）

					if (blocks[i]->GetPosY() + CELLSIZE == HEIGHT) {	//判定対象のブロックのすぐ真下が地面なら

						blocks[i]->SetIsFalling(FALSE);	//判定対象のブロックは落下をやめて積みあがる
						blocks[i]->SetIsStacked(TRUE);
						stack[(blocks[i]->GetPosX() - x0) / CELLSIZE][blocks[i]->GetPosY() / CELLSIZE] = i;	//stackに積みあがったブロックのblocksにおけるインデックスを保持させる
						stacked = TRUE;
					}
					else {	//判定対象のブロックのすぐ真下が地面でないなら

						blocks[i]->fall(fallSpeed);	//ブロックを落下させる
					}
				}
			}
		}

		return stacked;
	};

	//ブロックが上まで積みあがりきっているか判定
	int CheckColumns() {

		int n = 0;	//上まで積みあがりきっている列の下数

		for (int j = 0; j < XSIZE; j++) {	//各列について

			if (stack[j][0] > -1) {	//1番上の位置にブロックが積みあがっていれば

				columnsFilled[j] = TRUE;	//ブロックが上まで積みあがりきっている
				n++;
			}
			else {	//1番上の位置にブロックが積みあがっていなければ

				columnsFilled[j] = FALSE;	//ブロックが上まで積みあがりきっていない
			}
		}

		return n;
	};

	//ブロックの積みなおし（ブロック消去により空いたスペースを下に詰める）
	void Restack() {

		for (int i = 0; i < blockNum; i++) {	//古いブロック（下の方）から判定

			if (blocks[i]->GetIsStacked() == TRUE) {	//判定対象のブロックが積みあがっていたら

				int sx = (blocks[i]->GetPosX() - x0) / CELLSIZE;	//積みなおし前のstack配列におけるインデックスを計算
				int sy = blocks[i]->GetPosY() / CELLSIZE;

				while (sy < YSIZE - 1) {	//判定対象のブロックの真下にあるブロックと比較

					if (stack[sx][sy + 1] >= 0) {	//すぐ真下にブロックが積みあがっていたら

						break;	//何もしない（落下しない）
					}
					else {	//すぐ真下にブロックが積みあがっていないなら

						stack[sx][sy] = -1;	//その位置にブロックは積まれていないものとなる
						sy++;	//判定対象のブロックが落下
					}
				}

				stack[sx][sy] = i;	//判定対象のブロックのインデックスを新しい位置に格納
				blocks[i]->SetPosY(sy * CELLSIZE);	//積みなおし後の座標を更新
			}
		}

		WaitTimer(500);	//一時停止（演出）

		ClearDrawScreen();
		DrawBlocks();	//積みなおし後のブロックの描画
		ScreenFlip();
	};

	//消去可能な候補かどうか，ブロックを探索
	int CheckErasableBlock(int x, int y, int chainNum, int eraseList[MAXBLOCKNUM][2]) {

		int n;	//その位置に積みあがっているブロックのblocksにおけるインデックス（積みあがっていないなら-1となる）
		n = stack[x][y];

		//デバッグ出力//
		//char p[300];
		//sprintf_s(p, "visit (%d,%d)\n", x, y);
		//OutputDebugString(p);

		if (n > -1) {	//その位置にブロックが積みあがっていたら

			if (blocks[n]->GetIsChecked() == FALSE) {	//そのブロックが未探索なら

				blocks[n]->SetIsChecked(TRUE);	//探索フラグを探索済みにする

				if (y - 1 >= 0) {	//上に積みあがったブロックが存在し得るなら

					if (stack[x][y - 1] != -1) {	//上にブロックが積みあがっているなら

						if (blocks[stack[x][y - 1]]->GetType() == blocks[n]->GetType() && (blocks[stack[x][y - 1]]->GetIsChecked() == FALSE)) {	//上のブロックと探索中のブロックが同種類なら

							chainNum = CheckErasableBlock(x, y - 1, chainNum, eraseList);	//上のブロックを探索する

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

				eraseList[chainNum][0] = x;	//消す候補のリストに探索中のブロックの積みあがっている位置を入れる
				eraseList[chainNum][1] = y;

				return chainNum + 1;	//同種類のブロックで繋がっている個数を1個増やす
			}
			else {	//ブロックが探索済みなら

				return 0;	//同種類のブロックで繋がっている個数は0（探索済みなので探索しない）
			}
		}
		else {	//その位置にブロックが積みあがっていないなら

			return 0;	//同種類のブロックで繋がっている個数は0
		}
	};

	void SpliceVector() {	//Vectorの要素を詰める

		auto itr = blocks.begin();

		while (itr != blocks.end()) {

			if (*itr == dummy) {	//ブロックがダミーなら

				itr = blocks.erase(itr);	//vectorからその要素を消す
			}
			else {

				itr++;
			}
		}

		blockNum = blocks.size();	//ブロック数更新

		for (int i = 0; i < blockNum; i++) {	//インデックスを更新
			blocks[i]->SetIndex(i);
		}
	};
	
	//ブロック消去
	int EraseBlocks(int combos) {

		InitIsChecked();	//探索フラグの初期化
		bool erased = FALSE;	//消去に成功したかどうか

		//char p[300];

		for (int i = YSIZE - 1; i >= 0; i--) {	//右のブロックから

			for (int j = XSIZE - 1; j >= 0; j--) {	//下のブロックから

				int chainNum = 0;	//同種類のブロックで繋がっている個数
				int eraseList[MAXBLOCKNUM][2];	//消すブロックの候補

				
				chainNum = CheckErasableBlock(j, i, chainNum, eraseList);	//ブロックを探索し，同種類で繋がっている個数を得る

				//デバッグ出力//
				//sprintf_s(p, "position (%d,%d) chainNum:%d\n",j,i, chainNum);
				//OutputDebugString(p);
				
				if (chainNum >= 4) {	//4個以上で繋がっていたら

					me->GetEffect(blocks[stack[j][i]]->GetType(), chainNum, combos + 1);	//探索したブロックの種類，繋がっている個数，コンボ数に応じて効果を得る

					erased = TRUE;	//消去に成功

					//ブロックを消去
					for (int i = 0; i < chainNum; i++) {

						int x = eraseList[i][0];	//消す候補に入っている座標（stackのインデックス）
						int y = eraseList[i][1];

						//デバッグ出力//
						//OutputDebugString("erased\n");

						delete blocks[stack[x][y]];	//消去するブロックのオブジェクトを削除
						blocks[stack[x][y]] = dummy;	//削除するblocksの要素を一旦dummyにする
						stack[x][y] = -1;	//その位置にブロックはなくなる

					}
				}
			}
		}

		if (erased == TRUE) {	//消去に成功したら

			SpliceVector();	//dummyにしたblocksの要素を削除して詰める

			Restack();	//積みあがっていたブロックを下に詰める

			return combos + 1;	//コンボ数を1増やす
		}
		else {	//消去失敗

			return 0;	//コンボ数0
		}
	};

	//1番下の行のブロックを削除
	void EraseBottom() {

		for (int i = 0; i < XSIZE; i++) {	//右から

			if (stack[i][YSIZE - 1] != -1) {	//ブロックが積まれていたら

				delete blocks[stack[i][YSIZE - 1]];	//消去するブロックのオブジェクトを削除
				blocks[stack[i][YSIZE - 1]] = dummy;	//削除するblocksの要素を一旦dummyにする
				stack[i][YSIZE - 1] = -1;	//その位置にブロックはなくなる
			}
		}

		SpliceVector();	//dummyにしたblocksの要素を削除して詰める

		Restack();	//積みあがっていたブロックを下に詰める
	};

	//自機がブロックにダメージを与える
	void AttackBlocks(){

		auto itr = blocks.begin();

		while (itr != blocks.end()) {	//各ブロックに対し

			if ((*itr)->GetIsFalling() == TRUE) {	//落下中のブロックなら

				int damage;	//ダメージ

				damage = me->DealDamage((*itr)->GetPosX(), (*itr)->GetPosY(), (*itr)->GetSize(), (*itr)->GetSize());	//ダメージ計算
				(*itr)->RecieveDamage(damage);	//ダメージを与える

				if ((*itr)->GetHp() <= 0) {	//ブロックのHPが0以下になったら

					delete *itr;	//ブロックのオブジェクト削除
					itr = blocks.erase(itr);	//その要素を削除
				}
				else {	//ブロックのHPが0より大きかったら

					itr++;
				}
			}
			else {	//落下中のブロックじゃないなら

				itr++;
			}
		}

		blockNum = blocks.size();	//ブロック数更新
	};

	//自機が敵にダメージを与える
	void AttackEnemy() {

		int damage;	//ダメージ

		damage = me->DealDamage(enemy->GetPosX(), enemy->GetPosY(), enemy->GetWidth(), enemy->GetHeight());	//ダメージ計算
		enemy->RecieveDamage(damage);	//ダメージを与える
	};

	//自機がブロックや敵にダメージを与える
	void Attack() {

		AttackBlocks();
		AttackEnemy();
	};

	//自機がブロックからダメージを受ける
	void RecieveDamageFromBlocks() {

		for (int i = 0; i < blockNum; i++) {	//各ブロックに対し

			me->RecieveDamage(blocks[i]->GetPosX(), blocks[i]->GetPosY(), blocks[i]->GetSize(), blocks[i]->GetSize(), blocks[i]->GetPower());	//ダメージを受ける
		}
	};

	//自機が敵の弾からダメージを受ける
	void RecieveDamageFromBullets() {

		auto itr = enemy->GetBulletsBegin();

		while (itr != enemy->GetBulletsEnd()) {	//敵の各弾に対し

			me->RecieveDamage((*itr)->GetPosX(), (*itr)->GetPosY(), (*itr)->GetWidth(), (*itr)->GetHeight(), (*itr)->GetPower());
			itr++;
		}
	};

	//自機がブロックや敵からダメージを受ける
	void RecieveDamage() {

		RecieveDamageFromBlocks();
		me->RecieveDamage(enemy->GetPosX(), enemy->GetPosY(), enemy->GetWidth(), enemy->GetHeight(), enemy->GetPower());	//敵本体からダメージを受ける
		RecieveDamageFromBullets();		
	};

	//ループによるステージの処理
	int loop() {

		int result = 0;	//結果

		while (1) {

			int combos = 0;	//コンボ数（何回連続で消去が成功したか）

			ClearDrawScreen();	//画面の描画クリア

			//ブロック生成
			if (CheckFrame() == TRUE) {

				MakeBlock();
			}

			stacked = FallBlocks();	//ブロックの積みあげ


			//ブロック消去
			if (stacked == TRUE) {

				combos = EraseBlocks(combos);

				while (combos >= 1) {	//消去に失敗するまで

					//デバッグ用//
					//int k;
					//k = WaitKey();
					//if (k == KEY_INPUT_ESCAPE) {
					//	break;
					//}

					combos = EraseBlocks(combos);
				}
			};

			//自機の移動
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

			//敵の移動
			enemy->Move();
			
			//弾を移動
			me->MoveBullets();
			enemy->MoveBullets();

			//射撃
			me->Shoot();
			enemy->Shoot();

			//爆弾の使用
			if (me->UseBomb() == TRUE) {

				EraseBottom();
			}

			//ブロックや敵，弾との接触判定（自身がダメージを受ける）
			if (me->GetInvincibleTime() == 0) {

				RecieveDamage();
			}

			//自機のHPチェック
			if (me->GetHp() <= 0) {

				result = -1;

				break;
			}

			//ブロックや敵にダメージを与える
			Attack();

			//敵のHPチェック
			if (enemy->GetHp() <= 0) {

				result = 0;

				break;
			}

			//画面描画
			DrawAll();

			//画面描画の反映
			ScreenFlip();

			if (CheckColumns() == XSIZE) {

				result = -2;

				break;
			}

			//デバッグ用//
			//int k;
			//k = WaitKey();
			//if (k == KEY_INPUT_ESCAPE) {
			//	break;
			//}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

				result = 10;
				break;
			}

			frame++;		//フレーム経過

			me->Update();	//powerTimeなど各種変数を更新
		}

		//オブジェクトの削除
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