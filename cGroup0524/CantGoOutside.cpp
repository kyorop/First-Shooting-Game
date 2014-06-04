#include "DxLib.h"

#define MAXWIDTH 10
#define MAXHEIGHT 7

enum mapState
{
	FIELD,
	WALL,
	KEY,
	GOAL,
};

enum muki
{
	UP,
	DOWN,
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

	int imgWidth = 62;
	int imgHeight = 62;
	int fieldHandle = LoadGraph("img/field.png");
	int wallHandle = LoadGraph("img/wall.png");
	int manHandle = LoadGraph("img/man.png");
	int keyHandle = LoadGraph("img/key.png");
	int goalHandle = LoadGraph("img/goal.png");

	int mapData[MAXHEIGHT][MAXWIDTH] =
	{
		1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 0, 0, 0, 1, 3, 1,
		1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	int manX = imgWidth;
	int manY = imgHeight;
	int muki;

	char keyBuf[256];

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		int newX = manX;
		int newY = manY;
		GetHitKeyStateAll(keyBuf);
		if (keyBuf[KEY_INPUT_UP])
		{
			newY--;
			manY--;
			muki = UP;
		}
		else if (keyBuf[KEY_INPUT_DOWN])
		{
			newY++;
			manY++;
			muki = DOWN;
		}
		else if (keyBuf[KEY_INPUT_RIGHT])
		{
			newX++;
			manX++;
			muki = RIGHT;
		}
		else if (keyBuf[KEY_INPUT_LEFT])
		{
			newX--;
			manX--;
			muki = LEFT;
		}

		if ( (0 <= newX && newX < MAXWIDTH * imgWidth) && (0 <= newY && newY < MAXHEIGHT * imgHeight) )
		{
			int i = manX / imgWidth;
			int j = manY / imgHeight;

			switch (muki)
			{
			case UP:
				if (mapData[i][j] == 1)
					manY = imgHeight * (i);
				break;
			case RIGHT:
				if (mapData[i][j+1] == 1)
					manX = imgWidth * (j+1);
				break;
			case DOWN:
				if (mapData[i+1][j] == 1)
					manY = imgHeight * (i);
				break;
			case LEFT:
				if (mapData[i][j] == 1)
					manX = imgWidth * j;
				break;
			}
		}

		for (int i = 0; i < MAXHEIGHT; i++)
		{
			for (int j = 0; j < MAXWIDTH; j++)
			{
				switch (mapData[i][j])
				{
				case FIELD:
					DrawGraph(imgWidth * j, imgHeight * i, fieldHandle, FALSE);
					break;
				case WALL:
					DrawGraph(imgWidth * j, imgHeight * i, wallHandle, FALSE);
					break;
				case KEY:
					DrawGraph(imgWidth * j, imgHeight * i, keyHandle, FALSE);
					break;
				case GOAL:
					DrawGraph(imgWidth * j, imgHeight * i, goalHandle, FALSE);
					break;
				}
			}

			DrawGraph(manX, manY, manHandle, FALSE);
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