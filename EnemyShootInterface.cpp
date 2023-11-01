#pragma once

#include "Bullet.cpp"
#include <vector>

//ストラテジパターンによる敵の射撃パターン実装
class EnemyShootInterface {

protected:

	int frame; //経過フレーム
	int shootFrame;	//射撃間隔

public:

	virtual void Shoot(int x, int y, int speedX, int speedY, int power, std::vector<int>* bulletImageHandle, std::vector<Bullet*>* bullets) = 0;
	virtual ~EnemyShootInterface() {}
};

//弾を発射
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