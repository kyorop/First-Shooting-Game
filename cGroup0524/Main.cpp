#include "DxLib.h"

//�����}�N��
#define PLAYER_SPEED 3
#define ENEMY_SPEED 3
#define SHOT_SPEED 3
//���̃}�N��
#define ENEMY_NUM 25
//�摜�T�C�Y�̃}�N��
#define PLAYER_SIZE 64
#define ENEMY_SIZE 64
#define SHOT_SIZE 16

enum Direction
{
	RIGHT,
	LEFT,
};

struct Shot
{
	int x;
	int y;
	bool flag;
};

struct Player
{
	int x;
	int y;
	bool flag;
	Shot shot;
};

struct Enemy
{
	int x;
	int y;
	int muki;
	bool flag;
	Shot shot;
};

bool CheckHit(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
bool CheckHitShot(const Shot* shot, const Enemy* enemy);
bool CheckHitShot(const Shot* shot, const Player* player);

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	const int playerHandle = LoadGraph("img/Ball.png");
	const int enemyHandle = LoadGraph("img/Sikaku.png");
	const int shotHandle = LoadGraph("img/Shot.png");

	Enemy enemies[ENEMY_NUM];
	Player player;
	//Player�̏�����
	player.x = 288;
	player.y = 400;
	player.flag = true;
	player.shot.flag = 0;
	//Enemy�̏�����
	SRand(GetNowCount());
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemies[i].x = GetRand(600);
		if (i > 4)
		{
			enemies[i].y = ENEMY_SIZE * GetRand(4);
		}
		else
			enemies[i].y = ENEMY_SIZE * i;
		enemies[i].muki = GetRand(1);
		enemies[i].shot.flag = 0;
		enemies[i].flag = true;
	}
	
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//�X�V=================================
		//�v���C���[�X�V
		if (CheckHitKey(KEY_INPUT_UP)) 
			player.y -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_DOWN)) 
			player.y += PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT)) 
			player.x -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT)) 
			player.x += PLAYER_SPEED;

		if (player.flag && CheckHitKey(KEY_INPUT_Z) && player.shot.flag == 0)
		{
			player.shot.x = player.x + PLAYER_SIZE / 2;
			player.shot.y = player.y + SHOT_SIZE / 2;
			player.shot.flag = 1;
		}
		if (player.shot.flag)
			player.shot.y -= SHOT_SPEED;

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemies[i].flag)
			{
				if (enemies[i].muki == RIGHT)
					enemies[i].x += ENEMY_SPEED;
				else if (enemies[i].muki == LEFT)
					enemies[i].x -= ENEMY_SPEED;
				//���ˏ���
				if (enemies[i].shot.flag == 0)
				{
					enemies[i].shot.x = enemies[i].x + ENEMY_SIZE / 2;
					enemies[i].shot.y = enemies[i].y + SHOT_SIZE / 2;
					enemies[i].shot.flag = 1;
				}
			}
			//�G�e����
			if (enemies[i].shot.flag)
				enemies[i].shot.y += SHOT_SPEED;
			if (enemies[i].shot.flag && enemies[i].shot.y > 480)
				enemies[i].shot.flag = 0;
		}

		//�����蔻��=================================
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemies[i].flag)
			{
				if (enemies[i].x > 576)
				{
					enemies[i].x = 576;
					enemies[i].muki = LEFT;
				}
				if (enemies[i].x < 0)
				{
					enemies[i].x = 0;
					enemies[i].muki = RIGHT;
				}
				//���@�̒e�ƓG�Ƃ̂����蔻��
				if (CheckHitShot(&player.shot, &enemies[i]))
					enemies[i].flag = 0;
			}
			//���@�ƓG�̒e�̂����蔻��
			if (CheckHitShot(&enemies[i].shot, &player))
				player.flag = 0;
		}
	

		if (player.x < 0) 
			player.x = 0;
		if (player.x > 640 - 64)
			player.x = 640 - 64;
		if (player.y < 0) 
			player.y = 0;
		if (player.y > 480 - 64) 
			player.y = 480 - 64;

		if (player.shot.flag && player.shot.y < -SHOT_SIZE)
			player.shot.flag = 0;

		//�`��=================================
		if (player.flag)
			DrawGraph(player.x, player.y, playerHandle, TRUE);

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemies[i].flag)
				DrawGraph(enemies[i].x, enemies[i].y, enemyHandle, TRUE);
			if (enemies[i].shot.flag)
				DrawGraph(enemies[i].shot.x, enemies[i].shot.y, shotHandle, TRUE);
		}

		if (player.shot.flag)
			DrawGraph(player.shot.x, player.shot.y, shotHandle, TRUE);

		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();
	// �\�t�g�̏I��
	return 0;
}

bool CheckHitShot(const Shot* shot,const Enemy* enemy)
{
	return CheckHit(shot->x, shot->y, SHOT_SIZE, SHOT_SIZE, enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE);
}

bool CheckHitShot(const Shot* shot, const Player* player)
{
	int h = 15;//�␳��h
	int shotSize = SHOT_SIZE - h;
	int playerSize = PLAYER_SIZE - h;
	return CheckHit(shot->x + h, shot->y + h, shotSize, shotSize, player->x + h, player->y + h, playerSize, playerSize);
}

bool CheckHit(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 + height1 > y2 && y1 < y2 + height2);
}