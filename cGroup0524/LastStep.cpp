#include "DxLib.h"

#define MAXWIDTH 10
#define MAXHEIGHT 7

#define IMGWIDTH 62
#define IMGHEIGHT 62

int fieldHandle;
int wallHandle;
int manHandle;
int keyHandle;
int goalHandle;

enum mapState
{
	FIELD,
	WALL,
	KEY,
	GOAL,
};

//�w�肵���}�b�v�̎�ނɐG��Ă��邩�𔻒肷��֐�
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

void DrawMap(int mapData[MAXHEIGHT][MAXWIDTH])
{
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			switch (mapData[i][j])
			{
			case FIELD:
				DrawGraph(IMGWIDTH * j, IMGHEIGHT * i, fieldHandle, FALSE);
				break;
			case WALL:
				DrawGraph(IMGWIDTH * j, IMGHEIGHT * i, wallHandle, FALSE);
				break;
			case GOAL:
				DrawGraph(IMGWIDTH * j, IMGHEIGHT * i, goalHandle, FALSE);
				break;
			}
		}
	}
}

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	fieldHandle = LoadGraph("img/field.png");
	wallHandle = LoadGraph("img/wall.png");
	manHandle = LoadGraph("img/man.png");
	keyHandle = LoadGraph("img/key.png");
	goalHandle = LoadGraph("img/goal.png");

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

	int imgWidth = 62;
	int imgHeight = 62;

	int keyFlag = 1;

	int manX = imgWidth * 6;
	int manY = imgHeight * 1;
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

		if ((0 <= newX && newX < MAXWIDTH * imgWidth) && (0 <= newY && newY < MAXHEIGHT * imgHeight))
		{
			int i = newY / imgHeight;
			int j = newX / imgWidth;
			int i2;
			int j2;
			if (newY % imgHeight == 0)
				i2 = i;
			else
				i2 = i + 1;
			if (newX % imgWidth == 0)
				j2 = j;
			else
				j2 = j + 1;

			if (!CheckMapHit(mapData, newX, newY, WALL))
			{
				manX = newX;
				manY = newY;
			}

			if (CheckMapHit(mapData, newX, newY, KEY))
			{
				isHaveKey = 1;
				keyFlag = 0;
			}

			if (CheckMapHit(mapData, newX, newY, GOAL))
			{
				isGoal = 1;
			}
		}

		DrawMap(mapData);

		if (keyFlag)
			DrawGraph(imgWidth * 4, imgHeight * 1, keyHandle, FALSE);
		else
			DrawGraph(imgWidth * 4, imgHeight * 1, fieldHandle, FALSE);

		DrawGraph(manX, manY, manHandle, FALSE);

		if (isGoal)
		{
			ClearDrawScreen();
			DrawString(640 / 2, 480 / 2, "GOAL!!", GetColor(255, 255, 255));
		}

		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}