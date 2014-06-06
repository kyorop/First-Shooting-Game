#include "DxLib.h"

#define PLAYER_SPEED 3


// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	int handle_player = LoadGraph("img/Ball.png");
	int player_x;
	int player_y;

	int handle_enemy = LoadGraph("img/Sikaku.png");
	int enemy_x;
	int enemy_y;

	player_x = 288;
	player_y = 0;

	enemy_x = 0;
	enemy_y = 50;
	
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_UP)) 
			player_y -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN)) 
			player_y += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT)) 
			player_x -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT)) 
			player_x += PLAYER_SPEED;

		if (player_x < 0) 
			player_x = 0;
		if (player_x > 640 - 64)
			player_x = 640 - 64;
		if (player_y < 0) 
			player_y = 0;
		if (player_y > 480 - 64) 
			player_y = 480 - 64;

		// ボール君を描画
		DrawGraph(player_x, player_y, handle_player, FALSE);

		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}