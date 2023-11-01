#pragma once

#include "DxLib.h"
#include "Block.cpp"
#include "Player.cpp"
#include "Enemy.cpp"
#include "EnemyMoveInterface.cpp"
#include "EnemyShootInterface.cpp"
#include <random>
#include <time.h>
#include <stdlib.h>
#include <vector>


#define MAXBLOCKNUM 120
#define BLOCKTYPENUM 7
#define HEIGHT 1000
#define WIDTH 300
#define YSIZE 20
#define XSIZE 6
#define x0 810	//移動可能範囲内の最小のx　フィールドの左端
#define CELLSIZE 50