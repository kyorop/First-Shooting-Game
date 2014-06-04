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
	
	int keyFlag = 1;

	int manX = IMGWIDTH * 6;
	int manY = IMGHEIGHT * 1;
	int isHaveKey = 0;
	int isGoal = 0;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		int newX = manX;
		int newY = manY;

		char keyBuf[256];
		GetHitKeyStateAll(keyBuf);
		if (keyBuf[KEY_INPUT_UP])
			newY--;
		else if (keyBuf[KEY_INPUT_DOWN])
			newY++;
		else if (keyBuf[KEY_INPUT_RIGHT])
			newX++;
		else if (keyBuf[KEY_INPUT_LEFT])
			newX--;

		if ((0 <= newX && newX < MAXWIDTH * IMGWIDTH) && (0 <= newY && newY < MAXHEIGHT * IMGHEIGHT))
		{
			int i = newY / IMGHEIGHT;
			int j = newX / IMGWIDTH;
			int i2;
			int j2;
			if (newY % IMGHEIGHT == 0)
				i2 = i;
			else
				i2 = i + 1;
			if (newX % IMGWIDTH == 0)
				j2 = j;
			else
				j2 = j + 1;

			if (mapData[i][j] != 1 && mapData[i][j2] != 1 && mapData[i2][j] != 1 && mapData[i2][j2] != 1)
			{
				manX = newX;
				manY = newY;
			}
			


			if (mapData[i][j] == GOAL || mapData[i][j2] == GOAL || mapData[i2][j] == GOAL || mapData[i2][j2] == GOAL)
			{
				if (isHaveKey)
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
			DrawString(640/2, 480/2, "GOAL!!", GetColor(255, 255, 255));
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