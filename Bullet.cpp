#pragma once

#include "bullet.h"

//弾クラス
class Bullet {

private:

	int imageHandle;	//画像番号

	int pos[2];	//弾の座標(x,y)
	int width;	//弾の幅（横の大きさ）
	int height;	//弾の高さ（縦の大きさ）

	int speedX;	//横方向の弾速
	int speedY;	//縦方向の弾速

	int power;	//弾のダメージ

public:
	
	//コンストラクタ
	Bullet(int x, int y, int speedX, int speedY, int power, int imageHandle) {

		this->imageHandle = imageHandle;

		GetGraphSize(imageHandle, &width, &height);
		pos[0] = x - width / 2;
		pos[1] = y;
		
		this->speedX = speedX;
		this->speedY = speedY;
		this->power = power;
	}

	//弾の描画
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);
	};

	//弾の移動
	void Move() {

		pos[0] += speedX;
		pos[1] += speedY;
	};

	//対象との衝突判定
	bool CheckHit(int targetX, int targetY, int targetWidth, int targetHeight) {

		if (pos[0] <= targetX + targetWidth && pos[0] + width >= targetX) {

			if (pos[1] <= targetY + targetHeight && pos[1] + height >= targetY) {

				return TRUE;	//衝突している	
			}
			else {

				return FALSE;	//衝突していない
			}
		}
		else {

			return FALSE;	//衝突していない
		}
	};

	//対象にダメージを与える
	int CalcDamage(int targetX, int targetY, int targetWidth, int targetHeight, double powerCoeff) {	

		int damage = power * powerCoeff;	//与えるダメージ

		//衝突判定
		if (CheckHit(targetX, targetY, targetWidth, targetHeight) == TRUE) {	//衝突していたら

			return damage;	//ダメージはdamage
		}
		else {	//衝突していなかったら

			return 0;	//ダメージは0
		}
	};

	//X座標（pos[0]）を取得
		int GetPosX() {

		return pos[0];
	};

	//Y座標（pos[1]）を取得
	int GetPosY() {

		return pos[1];
	};

	//弾速を取得
	int GetSpeedX() {

		return speedX;
	};

	//弾速を取得
	int GetSpeedY() {

		return speedY;
	};

	//弾のダメージを取得
	int GetPower() {

		return power;
	};

	//弾の幅を取得
	int GetWidth() {

		return width;
	};

	//弾の高さを取得
	int GetHeight() {

		return height;
	};
};