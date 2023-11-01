#pragma once

#include "stackshoot.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1){		// ＤＸライブラリ初期化処理
	
		return -1;			// エラーが起きたら直ちに終了
	}

	//デバッグ出力用文字列//
	//char p[300];

	// 画面モードの設定
	SetGraphMode(1920, 1080, 16);

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//移動パターンを生成
	//OutputDebugString("Make Movements\n\n");
	std::vector<EnemyMoveInterface*> movements;
	movements.push_back(new EnemyMove());
	movements.push_back(new EnemyMoveRoundTrip());

	//射撃パターンを生成
	std::vector<EnemyShootInterface*> shoots;
	shoots.push_back(new EnemyShoot());

	int stageNum = 1;	//ステージ番号
	int result;	//クリアor失敗

	char enemyImageFile[256];	//敵の画像ファイル名
	int movement;	//敵の行動パターン番号
	int shoot;		//敵の射撃パターン番号
	std::vector <char*> bulletNums;

	int FileHandle;	//読み込むファイル番号
	char file[256];	//各ステージの情報が書かれているファイル名
	char str[256];	//読み込んだ行

	// ステージ番号をもとに外部ファイルから 敵の画像ファイル，行動パターンvectorのインデックスを読み込む
	sprintf_s(file, "./%s", FILE);	//ファイル指定
	
	//デバッグ出力//
	//OutputDebugString("Open File\n\n");

	FileHandle = FileRead_open(file);	//ファイルを開く
	
	//デバッグ出力//
	//sprintf_s(p, "Opened %s\n\n", file);
	//OutputDebugString(p);

	for (int i = 0; i < stageNum; i++) {	//そのステージ番号の情報が書かれている行まで

		FileRead_gets(str, 256, FileHandle);	// 一行読む

		//デバッグ出力//
		//OutputDebugString(str);
		//OutputDebugString("\n");
	}
	char* ntok;
	char* tok = strtok_s(str, ",", &ntok);	//敵の画像ファイル名を取得
	
	sprintf_s(enemyImageFile, "./images/%s.png", tok);

	//デバッグ出力
	//OutputDebugString(enemyImageFile);

	tok = strtok_s(NULL, ",", &ntok);	//行動パターン番号を取得
	movement = atoi(tok);

	//射撃パターン番号を取得
	tok = strtok_s(NULL, ",", &ntok);	//射撃パターン番号を取得
	shoot = atoi(tok);

	//弾の番号たちを取得
	tok = strtok_s(NULL, ",", &ntok);	//弾の画像ファイル番号を取得
	while (tok != NULL) {

		bulletNums.push_back(tok);
		tok = strtok_s(NULL, ",", &ntok);	//弾の画像ファイル番号を取得

		//デバッグ出力//
		//OutputDebugString("Add Info to buletNums\n");
	}

	//デバッグ出力//
	//sprintf_s(p, "read %s\n\n", file);
	//OutputDebugString(p);

	//ゲーム開始
	Stage stage = Stage(100, 5, 1, enemyImageFile, movements[movement], shoots[shoot], bulletNums);	//第二引数fallSpeedは50の約数 第一引数makeFrameは50/fallSpeed < makeFrame 第三引数ステージ番号

	result = stage.loop();	//ステージのループ処理

	if (result == 0) {

		OutputDebugString("\n\nClear!!\n\n");	//クリア
	}
	else if (result == -1) {

		OutputDebugString("\n\nDefeated :(\n\n");	//敗北
	}
	else if (result == -2) {

		OutputDebugString("\n\nStack Over Flow :(\n\n");	//ブロックが積みあがりきった
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}


