#pragma once

#include "block.h";

//ブロッククラス 親クラス
class Block {

protected:

	int imageHandle;	//画像番号

	int pos[2];			//ブロックの座標(x,y)
	int size;			//ブロックの1辺の大きさ（幅と高さ）

	int hp;				//HP　ブロックの耐久値
	int power;			//ブロックと衝突した際のダメージ

	bool isFalling;		//落下中かどうか
	bool isStacked;		//積みあがっているかどうか
	bool isChecked;		//消去判定時の探索フラグ

	int index;			//blocks配列における自身のインデックス	

public:

	//ダミー用オブジェクトを初期化
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

	//ブロックの描画
	void Draw() {

		DrawGraph(pos[0], pos[1], imageHandle, TRUE);
	};

	//ブロックの落下
	void fall(int fallSpeed) {

		pos[1] += fallSpeed;
	};

	//ダメージを受ける
	void RecieveDamage(int damage) {

		hp = hp - damage;
	};
	
	//y座標を更新
	void SetPosY(int y) {
		pos[1] = y;
	};

	//落下中かどうかを更新
	void SetIsFalling(bool isFalling) {

		this->isFalling = isFalling;
	};

	//積みあがっているかどうかを更新
	void SetIsStacked(bool isStacked) {

		this->isStacked = isStacked;
	};

	//探索フラグを更新
	void SetIsChecked(bool isChecked) {

		this->isChecked = isChecked;
	};

	//インデックスの更新
	void SetIndex(int index) {

		this->index = index;
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
	int GetSize() {

		return size;
	};

	//HP取得
	int GetHp() {

		return hp;
	};

	//パワー取得
	int GetPower() {

		return power;
	};
	
	//落下中かどうかを知る
	bool GetIsFalling() {

		return isFalling;
	};

	//積みあがっているかどうかを知る
	bool GetIsStacked() {

		return isStacked;
	};

	//探索フラグを取得
	bool GetIsChecked() {
		return isChecked;
	};

	//ブロックの種類を取得
	virtual int GetType() {

		return -1;
	};
};

//スカブロッククラス　子クラス
class Suka : public Block {

public:

	//コンストラクタ
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

	//ブロックの種類を取得
	int GetType() {

		return 0;
	};
};

//爆弾ブロッククラス　子クラス
class Bomb : public Block {

public:

	//コンストラクタ
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

	//ブロックの種類を取得
	int GetType() {

		return 1;
	};
};

//ハートブロッククラス　子クラス
class Heart : public Block {

public:

	//コンストラクタ
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
	
	//ブロックの種類を取得
	int GetType() {

		return 2;
	};
};

//パワーブロッククラス　子クラス
class Power : public Block {

public:

	//コンストラクタ
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

	//ブロックの種類を取得
	int GetType() {

		return 3;
	};
};

//スピードブロッククラス　子クラス
class Speed : public Block {

public:

	//コンストラクタ
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

	//ブロックの種類を取得
	int GetType() {

		return 4;
	};
};

//バブルブロッククラス　子クラス
class Bubble : public Block {

public:

	//コンストラクタ
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

	//ブロックの種類を取得
	int GetType() {

		return 5;
	};
};

//ダブルブロッククラス　子クラス
class Double : public Block {

public:

	//コンストラクタ
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

	//ブロックの種類を取得
	int GetType() {

		return 6;
	};
};