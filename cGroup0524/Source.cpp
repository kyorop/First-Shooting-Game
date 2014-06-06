#include "DxLib.h"

#define MAXWIDTH 10
#define MAXHEIGHT 7

#define IMGWIDTH 62
#define IMGHEIGHT 62

enum mapState
{
	FIELD,
	WALL,
	KEY,
	GOAL,
};

//指定した種類のマップに触れているかを判定する関数
int CheckMapHit(int mapData[MAXHEIGHT][MAXWIDTH], int x, int y, mapState map)
{
	if ((0 <= x && x < MAXWIDTH * IMGWIDTH) && (0 <= y && y < MAXHEIGHT * IMGHEIGHT))
	{
		int i = y / IMGHEIGHT;
		int j = x / IMGWIDTH;
		int i2;
		int j2;
		if (y % IMGHEIGHT == 0)
			i2 = i;
		else
			i2 = i + 1;
		if (x % IMGWIDTH == 0)
			j2 = j;
		else
			j2 = j + 1;

		if (mapData[i][j] == map || mapData[i][j2] == map || mapData[i2][j] == map || mapData[i2][j2] == map)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	int mapData[MAXHEIGHT][MAXWIDTH] =
	{
		1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 2, 0, 0, 1, 3, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	int handle_field = LoadGraph("img/field.png");
	int handle_wall = LoadGraph("img/wall.png");
	int handle_man = LoadGraph("img/man.png");
	int handle_key = LoadGraph("img/key.png");
	int handle_goal = LoadGraph("img/goal.png");

	int manX = IMGWIDTH * 1;
	int manY = IMGHEIGHT * 0;
	int isGoal = 0;
	int keyFlag = 1;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		int newX = manX;
		int newY = manY;
		if (CheckHitKey(KEY_INPUT_UP))
			newY--;
		else if (CheckHitKey(KEY_INPUT_DOWN))
			newY++;
		else if (CheckHitKey(KEY_INPUT_RIGHT))
			newX++;
		else if (CheckHitKey(KEY_INPUT_LEFT))
			newX--;

		if ((0 <= newX && newX < MAXWIDTH * IMGWIDTH) && (0 <= newY && newY < MAXHEIGHT * IMGHEIGHT))
		{
			if (!CheckMapHit(mapData, newX, newY, WALL))
			{
				manX = newX;
				manY = newY;
			}

			if (CheckMapHit(mapData, newX, newY, KEY))
			{
				keyFlag = 0;
			}

			if (CheckMapHit(mapData, newX, newY, GOAL))
			{
				if (keyFlag == 0)
					isGoal = 1;
			}
		}

		for (int i = 0; i < MAXHEIGHT; i++)
		{
			for (int j = 0; j < MAXWIDTH; j++)
			{
				switch (mapData[i][j])
				{
				case FIELD:
					DrawGraph(IMGWIDTH * j, IMGHEIGHT * i, handle_field, FALSE);
					break;
				case WALL:
					DrawGraph(IMGWIDTH * j, IMGHEIGHT * i, handle_wall, FALSE);
					break;
				case GOAL:
					DrawGraph(IMGWIDTH * j, IMGHEIGHT * i, handle_goal, FALSE);
					break;
				}
			}
		}

		if (keyFlag)
			DrawGraph(IMGWIDTH * 4, IMGHEIGHT * 1, handle_key, FALSE);
		else
			DrawGraph(IMGWIDTH * 4, IMGHEIGHT * 1, handle_field, FALSE);

		DrawGraph(manX, manY, handle_man, FALSE);

		if (isGoal)
		{
			ClearDrawScreen();
			DrawString(640 / 2, 480 / 2, "GOAL!!", GetColor(255, 255, 255));
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