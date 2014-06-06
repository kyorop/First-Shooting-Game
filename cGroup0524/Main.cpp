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

struct Shot
{
	int x;
	int y;
	int handle;
};

struct Player
{
	int x;
	int y;
	int handle;
	Shot shot[SHOT_NUM];
};

struct Enemy
{
	int x;
	int y;
	int handle;
	int direction;
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
	Player player = 
	{
		288,
		500,
		LoadGraph("img/Ball.png"),
		0
	};
	Enemy enemy = 
	{
		0,
		50,
		LoadGraph("img/Ball.png"),
		RIGHT
	};

	player.handle = LoadGraph("img/Ball.png");
	player.x = 288;
	player.y = 500;

	int handle_shot = LoadGraph("img/Shot.png");
	int shot_x[SHOT_NUM];
	int shot_y[SHOT_NUM];
	int shotFlag[SHOT_NUM];
	int shotBeforeFlag = 0;
	for (int i = 0; i < SHOT_NUM; i++)
	{
		shotFlag[i] = 0;
	}
	
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

		if (CheckHitKey(KEY_INPUT_Z))
		{
			int x = player.x + PLAYER_SIZE / 2;
			int y = player.y + SHOT_SIZE / 2;

			if (shotBeforeFlag == 0)
			{
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
				shotBeforeFlag = 1;
			}
		}
		else
			shotBeforeFlag = 0;

		for (int i = 0; i < SHOT_NUM; i++)
		{
			if (shotFlag[i])
				shot_y[i] -= SHOT_SPEED;
		}

		if (enemy.direction == RIGHT)
			enemy.x += ENEMY_SPEED;
		else if (enemy.direction == LEFT)
			enemy.x -= ENEMY_SPEED;

		//あたり判定=================================
		if (enemy.x > 576)
		{
			enemy.x = 576;
			enemy.direction = LEFT;
		}
		
		if (enemy.x < 0)
		{
			enemy.x = 0;
			enemy.direction = RIGHT;
		}

		if (player.x < 0) 
			player.x = 0;
		if (player.x > 640 - 64)
			player.x = 640 - 64;
		if (player.y < 0) 
			player.y = 0;
		if (player.y > 480 - 64) 
			player.y = 480 - 64;

		for (int i = 0; i < SHOT_NUM; i++)
		{
			if (shotFlag[i])
			{
				if (shot_y[i] < -10)
					shotFlag[i] = 0;
			}
		}

		//描画=================================
		DrawGraph(player.x, player.y, player.handle, FALSE);
		DrawGraph(enemy.x, enemy.y, player.handle, FALSE);
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