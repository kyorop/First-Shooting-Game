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

struct Player
{
	int x;
	int y;
	int handle;
};

struct Enemy
{
	int x;
	int y;
	int handle;
	int muki;
};

struct Shot
{
	int x;
	int y;
	int flag;
	int handle;
};


// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	Player player;
	player.handle = LoadGraph("img/Ball.png");

	Enemy enemy;
	enemy.handle = LoadGraph("img/Sikaku.png");
	Enemy enemy2;

	Enemy enemise[10];

	enemise[0].x;
	enemise[1].x;


	Shot shot;
	shot.handle = LoadGraph("img/Shot.png");

	player.x = 288;
	player.y = 0;

	enemy.x = 0;
	enemy.y = 50;
	enemy.muki = RIGHT;

	shot.x = 0;
	shot.y = 0;
	shot.flag = 0;
	
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//更新=================================
		if (CheckHitKey(KEY_INPUT_UP)) 
			player.y -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN)) 
			player.y += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT)) 
			player.x -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT)) 
			player.x += PLAYER_SPEED;

		if (CheckHitKey(KEY_INPUT_Z) && shot.flag == 0)
		{
			shot.x = player.x + PLAYER_SIZE / 2;
			shot.y = player.y + SHOT_SIZE / 2;

			shot.flag = 1;
		}
		if (shot.flag)
			shot.y -= SHOT_SPEED;

		if (enemy.muki == RIGHT)
			enemy.x += ENEMY_SPEED;
		else if (enemy.muki == LEFT)
			enemy.x -= ENEMY_SPEED;

		//あたり判定=================================
		if (enemy.x > 576)
		{
			enemy.x = 576;
			enemy.muki = LEFT;
		}
		
		if (enemy.x < 0)
		{
			enemy.x = 0;
			enemy.muki = RIGHT;
		}

		if (player.x < 0) 
			player.x = 0;
		if (player.x > 640 - 64)
			player.x = 640 - 64;
		if (player.y < 0) 
			player.y = 0;
		if (player.y > 480 - 64) 
			player.y = 480 - 64;

		if (shot.flag && shot.y < -10)
			shot.flag = 0;

		//描画=================================
		DrawGraph(player.x, player.y, player.handle, FALSE);
		DrawGraph(enemy.x, enemy.y, enemy.handle, FALSE);
		if (shot.flag)
			DrawGraph(shot.x, shot.y, shot.handle, FALSE);

		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}