#include "DxLib.h"

#define PLAYER_SPEED 3
#define ENEMY_SPEED 3
#define SHOT_SPEED 3

#define PLAYER_SIZE 64
#define ENEMY_SIZE 64
#define SHOT_SIZE 16

#define SHOT_NUM 100

enum Direction
{
	RIGHT,
	LEFT,
};

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	//プログラムで使う変数の初期化=================================
	int handle_player = LoadGraph("img/Ball.png");
	int player_x = 288;
	int player_y = 0;

	int handle_enemy = LoadGraph("img/Sikaku.png");
	int enemy_x = 0;
	int enemy_y = 50;
	int enemy_muki = RIGHT;

	int handle_shot = LoadGraph("img/Shot.png");
	int shot_x[SHOT_NUM];
	int shot_y[SHOT_NUM];
	int shotFlag[SHOT_NUM];

	for (int i = 0; i < SHOT_NUM; i++)
	{
		shotFlag[i] = 0;
	}
	
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//更新=================================
		if (CheckHitKey(KEY_INPUT_UP)) 
			player_y -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN)) 
			player_y += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT)) 
			player_x -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT)) 
			player_x += PLAYER_SPEED;

		if (CheckHitKey(KEY_INPUT_Z))
		{
			int x = player_x + PLAYER_SIZE / 2;
			int y = player_y + SHOT_SIZE / 2;
			
			for (int i = 0; i < SHOT_NUM; i++)
			{
				if (shotFlag[i] == 0)
				{
					shot_x[i] = x;
					shot_y[i] = y;
					shotFlag[i] = 1;

					break;
				}
			}
		}

		for (int i = 0; i < SHOT_NUM; i++)
		{
			if (shotFlag[i])
				shot_y[i] -= SHOT_SPEED;
		}

		if (enemy_muki == RIGHT)
			enemy_x += ENEMY_SPEED;
		else if (enemy_muki == LEFT)
			enemy_x -= ENEMY_SPEED;

		//あたり判定=================================
		if (enemy_x > 576)
		{
			enemy_x = 576;
			enemy_muki = LEFT;
		}
		
		if (enemy_x < 0)
		{
			enemy_x = 0;
			enemy_muki = RIGHT;
		}

		if (player_x < 0) 
			player_x = 0;
		if (player_x > 640 - 64)
			player_x = 640 - 64;
		if (player_y < 0) 
			player_y = 0;
		if (player_y > 480 - 64) 
			player_y = 480 - 64;

		for (int i = 0; i < SHOT_NUM; i++)
		{
			if (shotFlag[i])
			{
				if (shot_y[i] < -10)
					shotFlag[i] = 0;
			}
		}

		//描画=================================
		DrawGraph(player_x, player_y, handle_player, FALSE);
		DrawGraph(enemy_x, enemy_y, handle_enemy, FALSE);
		for (int  i = 0; i < SHOT_NUM; i++)
		{
			if (shotFlag[i])
				DrawGraph(shot_x[i], shot_y[i], handle_shot, FALSE);
		}

		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}