#include "DxLib.h"
#include "CharacterStruct.h"
#include "CheckHit.h"
#include "Constant.h"

enum Direction
{
	RIGHT,
	LEFT,
};

const int enemyNum = 50;

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

	Enemy enemies[enemyNum];
	Player player;
	//Player�̏�����
	player.x = 288;
	player.y = 400;
	player.flag = true;
	player.shot.flag = 0;
	//Enemy�̏�����
	SRand(GetNowCount());
	for (int i = 0; i < enemyNum; i++)
	{
		enemies[i].x = GetRand(600);
		const int enemyLimit = 2;
		if (i > enemyLimit)
		{
			enemies[i].y = ENEMY_SIZE * GetRand(enemyLimit);
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

		for (int i = 0; i < enemyNum; i++)
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
		for (int i = 0; i < enemyNum; i++)
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

		for (int i = 0; i < enemyNum; i++)
		{
			if (enemies[i].flag)
				DrawGraph(enemies[i].x, enemies[i].y, enemyHandle, TRUE);
		}
		for (int i = 0; i < enemyNum; i++)
		{
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