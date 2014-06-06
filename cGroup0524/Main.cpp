#include "DxLib.h"

#define PLAYER_SPEED 3
#define ENEMY_SPEED 3
#define SHOT_SPEED 3

#define PLAYER_SIZE 64
#define ENEMY_SIZE 64
#define SHOT_SIZE 16


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

	//ゲームで使う変数の初期化=================================
	int handle_player = LoadGraph("img/Ball.png");
	int player_x = 288;
	int player_y = 0;

	int handle_enemy = LoadGraph("img/Sikaku.png");
	int enemy_x = 0;
	int enemy_y = 50;
	int enemy_muki = RIGHT;

	int handle_shot = LoadGraph("img/Shot.png");
	int shot_x = 0;
	int shot_y = 0;
	int shotFlag = 0;

	int shot2_x = 0;
	int shot2_y = 0;
	int shot2Flag = 0;
	
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

			if ( ! shotFlag)
			{
				shot_x = x;
				shot_y = y;
				shotFlag = 1;
			}
			else if ( ! shot2Flag)
			{
				shot2_x = x;
				shot2_y = y;
				shot2Flag = 1;
			}
		}

		if (shotFlag)
			shot_y -= SHOT_SPEED;
		if (shot2Flag)
			shot2_y -= SHOT_SPEED;

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

		if (shotFlag && shot_y < -10)
			shotFlag = 0;
		if (shot2Flag && shot2_y < -10)
			shot2Flag = 0;

		//描画=================================
		DrawGraph(player_x, player_y, handle_player, FALSE);
		DrawGraph(enemy_x, enemy_y, handle_enemy, FALSE);
		if (shotFlag)
			DrawGraph(shot_x, shot_y, handle_shot, FALSE);
		if (shot2Flag)
			DrawGraph(shot2_x, shot2_y, handle_shot, FALSE);

		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}