#pragma once

#include "enemy.h"

class Enemy {

private:

	int imageHandle;	//敵の画像番号
	std::vector<char*> bulletImageIndex;	//弾の画像ファイルのインデックス
	std::vector<int> bulletImageHandle;	//弾の画像番号

	int pos[2];	//敵の座標
	int width;	//敵の幅（横の大きさ）
	int height;	//敵の高さ（縦の大きさ）
	
	std::vector<Bullet*> bullets;		//撃った弾たち

	int hp;		//体力
	int power;	//敵に触れた時のダメージ

	int frame;	//経過フレーム

	EnemyMoveInterface* move;	//行動パターン
	EnemyShootInterface* shoot;	//射撃パターン

public:

	//コンストラクタ
	Enemy(int imageHandle, EnemyMoveInterface* move, EnemyShootInterface* shoot, std::vector<char*> bulletNums) {

		this->imageHandle = imageHandle;

		GetGraphSize(imageHandle, &width, &height);
		pos[0] = (WIDTH / 2 - width / 2) + x0;
		pos[1] = 0;

		//デバッグ出力
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

	//描画
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);	//敵の描画

		for (int i = 0; i < bullets.size(); i++) {

			bullets[i]->Draw();	//弾の描画
		}
	};

	//各種情報の表示
	void WriteStats() {

		unsigned int color = GetColor(255, 255, 255);	//白文字を使う

		DrawFormatString(600, 50, color, "HP:%d", hp);
	};

	void Move() {

		move->Move(1, 0, width, height, pos);
	};

	//弾を移動
	void MoveBullets() {

		//画面外に出た弾を削除
		EraseBullets();

		//各弾の座標を更新
		for (int i = 0; i < bullets.size(); i++) {

			bullets[i]->Move();
		}
	};

	//画面外に出た弾を削除
	void EraseBullets() {

		auto itr = bullets.begin();

		while (itr != bullets.end()) {

			if ((*itr)->GetPosX() < x0 -(*itr)->GetWidth() || (*itr)->GetPosX() > x0 + WIDTH || (*itr)->GetPosY() < - (*itr)->GetSpeedY() || (*itr)->GetPosY() > HEIGHT + (*itr)->GetHeight()) {	//画面外なら

				delete* itr;				//弾を削除
				itr = bullets.erase(itr);
			}
			else {	//画面内なら

				itr++;	//何もせず次の弾へ
			}
		}
	};

	//弾を撃つ
	void Shoot() {

		shoot->Shoot(pos[0] + width / 2, pos[1] + height / 2, 0, 5, 20, &bulletImageHandle, &bullets);

		//デバッグ出力
		//char p[256];
		//sprintf_s(p, "enemy bullets[] size:%d\n\n", bullets.size());
		//OutputDebugString(p);
	};

	//ダメージを受ける
	void RecieveDamage(int damage) {

		hp = hp - damage;
	};

	//x座標を取得
	int GetPosX() {

		return pos[0];
	};

	//y座標を取得
	int GetPosY() {

		return pos[1];
	};

	//大きさを取得
	int GetWidth() {

		return width;
	};

	//HP取得
	int GetHp() {

		return hp;
	};

	//幅を取得
	int GetHeight() {

		return height;
	};

	//高さを取得
	int GetPower() {

		return power;
	};

	//bulletsの先頭イテレータ取得
	auto GetBulletsBegin() {

		return bullets.begin();
	};

	//bulletsの末尾イテレータ取得
	auto GetBulletsEnd() {

		return bullets.end();
	};
};

