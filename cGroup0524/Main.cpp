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

	int manX = 62;
	int manY = 0;

	char keyBuf[256];

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		GetHitKeyStateAll(keyBuf);
		if (keyBuf[KEY_INPUT_UP])
		{
			manY--;
		}
		else if (keyBuf[KEY_INPUT_DOWN])
		{
			manY++;
		}
		else if (keyBuf[KEY_INPUT_RIGHT])
		{
			manX++;
		}
		else if (keyBuf[KEY_INPUT_LEFT])
		{
			manX--;
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