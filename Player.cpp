#pragma once

#include "player.h"

class Player {

private:

	int imageHandle;	//自機の画像番号

	int pos[2];	//自機の座標
	int width;	//自機の幅（横の大きさ）
	int height;	//自機の高さ（縦の大きさ）

	int bulletImageHandle;	//弾の画像番号

	std::vector<Bullet*> bullets;		//撃った弾たち

	int hp;		//体力
	int bombNum;	//所持している爆弾の数
	int speed;	//移動速度
	double speedCoeff;	//移動速度係数
	double powerCoeff;	//弾の威力係数
	int speedTime;	//スピードアップ状態の残り時間
	int powerTime;	//パワーアップ状態の残り時間
	int bubbleTime;	//バブル状態の残り時間
	int doubleTime;	//ダブル状態の残り時間

	int frame;		//経過フレーム
	int shootFrame;	//射撃間隔

	int invincibleTime;	//被弾後の残り無敵時間

public:

	//コンストラクタ
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

		//デバッグ出力
		//char p[300];
		//sprintf_s(p, "player:%d,%d\n\n", pos[0], pos[1]);
		//OutputDebugString(p);
	}

	//自機と弾の描画
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);	//自機の描画

		for (int i = 0; i < bullets.size(); i++) {

			bullets[i]->Draw();	//弾の描画
		}
	};

	//各種情報の表示
	void WriteStats() {

		unsigned int color = GetColor(255, 255, 255);	//白文字を使う

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

	//自機の移動
	void Move(int x, int y) {

		//移動先の計算
		pos[0] += speedCoeff * speed * x;
		pos[1] += speedCoeff * speed * y;

		//移動範囲外に行かないようにする
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

			if ((*itr)->GetPosY() < - (*itr)->GetHeight()) {	//画面外なら

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

		if (frame < shootFrame) {	//射撃可能なフレームでなければ

			frame++;	//frame更新
		}
		else {	//射撃可能なフレームなら

			if (CheckHitKey(KEY_INPUT_RSHIFT) == 1) {	//キー入力を受け付ける

				bullets.push_back(new Bullet(pos[0] + width / 2, pos[1], 0, -30, 50, bulletImageHandle));	//弾を生成
			}

			frame = 0;
		}

		//デバッグ出力//
		//char p[300];
		//sprintf_s(p, "%d ", bullets.size());
		//OutputDebugString(p);
	};

	//爆弾を使う
	bool UseBomb() {

		if (CheckHitKey(KEY_INPUT_S) == 1) {	//Sキー入力があったら

			if (bombNum > 0) {	//爆弾を持っていたら

				bombNum--;	//爆弾を消費

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

	//対象にダメージを与える
	int DealDamage(int targetX, int targetY, int targetWidth, int targetHeight) {

		int damage = 0;	//各弾が与えるダメージ
		int damageSum = 0;	//与える総ダメージ

		auto itr = bullets.begin();

		while (itr != bullets.end()) {

			damage = (*itr)->CalcDamage(targetX, targetY, targetWidth, targetHeight, powerCoeff);	//各弾が与えるダメージを計算

			if (damage > 0) {	//ダメージが0より大きい（対象に弾が当たっている）なら

				damageSum += damage;	//与えるダメージを加算
				delete* itr;			//当たった弾を削除
				itr = bullets.erase(itr);
			}
			else {	//ダメージが0以下（対象に弾が当たっていない）なら

				itr++;	//何もせず次の弾へ
			}
		}

		return damageSum;	//ダメージを与える
	};

	//自機が対象からダメージを受ける
	void RecieveDamage(int targetX, int targetY, int targetWidth, int targetHeight, int power) {


		//対象との衝突判定
		if (pos[0] <= targetX + targetWidth && pos[0] + width >= targetX) {

			if (pos[1] <= targetY + targetHeight && pos[1] + height >= targetY) {

				if (bubbleTime > 0) {	//バブル状態だったら

					bubbleTime--;	//バブルの残り時間が減るにする（バブル状態の残り時間が速く減少する）
				}
				else {	//バブル状態じゃなかったら

					hp -= power;	//ダメージを受ける
					invincibleTime = 1000;	//無敵時間に入る
				}
			}
		}
	};

	//ブロック消去の効果を得る
	void GetEffect(int blockType, int chainNum, int combos) {

		if (blockType == 1) {	//爆弾ブロックを消したなら

			GetBombEffect(chainNum);
		}
		else if (blockType == 2) {	//ハートブロックを消したなら

			GetHeartEffect(chainNum, combos);
		}
		else if (blockType == 3) {	//パワーブロックを消したなら

			GetPowerEffect(chainNum, combos);
		}
		else if (blockType == 4) {	//スピードブロックを消したなら

			GetSpeedEffect(chainNum, combos);
		}
		else if (blockType == 5) {	//バブルブロックを消したなら

			GetBubbleEffect(chainNum, combos);
		}
		else if (blockType == 6) {	//ダブルブロックを消したなら

			GetDoubleEffect(chainNum, combos);
		}
	};

	//爆弾ブロック消去の効果を得る
	void GetBombEffect(int chainNum) {

		bombNum = bombNum + (chainNum / 4);	//消去数に応して爆弾を入手

		//デバッグ出力
		//char p[300];
		//sprintf_s(p, "add %d bombs\n", chainNum % 4);
		//OutputDebugString(p);
	};

	//ハートブロック消去の効果を得る
	void GetHeartEffect(int chainNum, int combos) {
	
		int cure;	//回復量

		cure = 5 * combos * chainNum;	//回復量の計算

		hp = hp + cure;	//HPを回復

		//デバッグ出力
		//char p[300];
		//sprintf_s(p, "cure:%d, new hp:%d\n", cure, hp);
		//OutputDebugString(p);
	};

	//パワーブロック消去の効果を得る
	void GetPowerEffect(int chainNum, int combos) {

		powerCoeff = 0.5 * (double)combos + 1;	//コンボ数に応じて係数を更新
		powerTime = powerTime + (1000 + 50 * (chainNum - 4));	//消去数に応じてパワーアップ時間を更新

		//デバッグ出力
		//char p[300];
		//sprintf_s(p, "power up  coeff:%f, powerTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};

	//スピードブロック消去の効果を得る
	void GetSpeedEffect(int chainNum, int combos) {

		speedCoeff = 0.5 * (double)combos + 1;	//コンボ数に応じて係数を更新
		speedTime = speedTime + (1000 + 50 * (chainNum - 4));	//消去数に応じてスピードアップ時間を更新

		//デバッグ出力
		//char p[300];
		//sprintf_s(p, "speed up  coeff:%f, speedTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};

	//バブルブロック消去の効果を得る
	void GetBubbleEffect(int chainNum, int combos) {

		bubbleTime = bubbleTime + (800 + 50 * (chainNum - 4));	//消去数に応じてバブル状態の時間を更新
		invincibleTime = 0;	//無敵時間を0にする

		//デバッグ出力
		//char p[300];
		//sprintf_s(p, "bubbleTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};

	//ダブルブロック消去の効果を得る
	void GetDoubleEffect(int chainNum, int combos) {

		doubleTime = doubleTime + (900 + 50 * (chainNum - 4));	//消去数に応じてダブル状態の時間を更新
		shootFrame = 2;	//射撃間隔が半分になる

		//デバッグ出力
		//char p[300];
		//sprintf_s(p, "doubleTime:%d\n", powerCoeff, powerTime);
		//OutputDebugString(p);
	};
	
	//各種変数の更新
	void Update() {

		if (powerTime > 0) {	//パワーアップ時間が0より大きかったら

			powerTime--;	//パワーアップ時間減少
		}
		else {	//パワーアップ時間が0以下だったら

			powerCoeff = 1;	//係数を1に戻す
		}

		if (speedTime > 0) {	//スピードアップ時間が0より大きかったら

			speedTime--;	//スピードアップ時間減少
		}
		else {	//スピードアップ時間が0以下だったら

			speedCoeff = 1;	//係数を1に戻す
		}

		if (bubbleTime > 0) {	//バブル状態の残り時間が0より大きかったら

			bubbleTime--;	//残り時間減少
		}

		if (doubleTime > 0) {	//ダブル状態の残り時間が0より大きかったら

			doubleTime--;	//残り時間減少
		}
		else {	//ダブル状態の残り時間が0以下だったら

			shootFrame = 4;	//射撃間隔を戻す
		}

		if (invincibleTime > 0) {	//無敵時間が0より大きかったら

			invincibleTime--;	//無敵時間減少
		}
	};

	//bulletsの先頭イテレータ取得
	auto GetBulletsBegin() {

		return bullets.begin();
	};

	//bulletsの末尾イテレータ取得
	auto GetBulletsEnd() {

		return bullets.end();
	};

	//HPを取得
	int GetHp() {

		return hp;
	};

	//無敵時間を取得
	int GetInvincibleTime() {

		return invincibleTime;
	};
};