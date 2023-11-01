#pragma once

#define HEIGHT 1000
#define WIDTH 300
#define x0 810	//移動可能範囲内の最小のx　フィールドの左端

//ストラテジパターンによる敵の移動パターン実装
class EnemyMoveInterface {

protected:

	int frame;	//経過フレーム
	int directionX;	//x軸方向の正負
	int directionY;	//Y軸方向の正負

public:

	virtual void Move(int dirX, int dirY, int width, int height, int* pos) = 0;
	virtual ~EnemyMoveInterface(){}
};

//指定方向へ動き続ける
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

//左右を往復
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

