#include "DxLib.h"
#include "CharacterStruct.h"
#include "CheckHit.h"
#include "Constant.h"
#include "Boss.h"

enum Direction
{
	RIGHT,
	LEFT,
};

const int enemyNum = 1;

enum ImgId
{
	player,
	enemy,
	shot,
	droiDragon,
};

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return -1;
	SetGraphMode(640, 480, 16);
	SetDrawScreen(DX_SCREEN_BACK);

	const int imgHandleNum = 4;
	char *imgPass[] =
	{
		"img/Ball.png",
		"img/Sikaku.png",
		"img/Shot.png",
		"img/DroiDragon.png",
	};
	ImgSize imgSizes[imgHandleNum];
	int imgHandles[imgHandleNum];
	for (int i = 0; i < imgHandleNum; i++)
	{
		imgHandles[i] = LoadGraph(imgPass[i]);
		GetGraphSize(imgHandles[i], &imgSizes[i].w, &imgSizes[i].h);
	}

	Enemy enemies[enemyNum];
	Player player;
	Boss boss;

	//Playerの初期化
	player.x = 288;
	player.y = 400;
	player.flag = true;
	player.shot.flag = 0;
	//Enemyの初期化
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
	//bossの初期化
	boss.isVisible = 0;
	boss.flag = 0;
	boss.life = 3;
	
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//更新=================================
		//プレイヤー更新
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
		//エネミー更新
		for (int i = 0; i < enemyNum; i++)
		{
			if (enemies[i].flag)
			{
				if (enemies[i].muki == RIGHT)
					enemies[i].x += ENEMY_SPEED;
				else if (enemies[i].muki == LEFT)
					enemies[i].x -= ENEMY_SPEED;
				//発射処理
				if (enemies[i].shot.flag == 0)
				{
					enemies[i].shot.x = enemies[i].x + ENEMY_SIZE / 2;
					enemies[i].shot.y = enemies[i].y + SHOT_SIZE / 2;
					enemies[i].shot.flag = 1;
				}
			}
			//敵弾制御
			if (enemies[i].shot.flag)
				enemies[i].shot.y += SHOT_SPEED;
			if (enemies[i].shot.flag && enemies[i].shot.y > 480)
				enemies[i].shot.flag = 0;
		}
		//ボス更新
		if (! boss.isVisible)
		{
			int enemyCount = 0;
			for (int i = 0; i < enemyNum; i++)
			{
				if (!enemies[i].flag)
					enemyCount++;
			}
			if (enemyCount == enemyNum)
			{
				boss.isVisible = 1;
				boss.y = -imgSizes[ImgId::droiDragon].h*2;
				boss.x = 640 / 2 - imgSizes[ImgId::droiDragon].w / 2;
			}
		}
		else if (boss.y < 10)
		{
			boss.y += 1;
			boss.flag = 1;
		}

		if (boss.flag && boss.life <= 0)
			boss.flag = 0;
		
		//あたり判定=================================
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
				//自機の弾と敵とのあたり判定
				if (CheckHitShot(&player.shot, &enemies[i]))
					enemies[i].flag = 0;
			}
			//自機と敵の弾のあたり判定
			if (CheckHitShot(&enemies[i].shot, &player))
				player.flag = 0;
		}
		if (boss.flag && player.shot.flag)
		{
			if (CheckHitShot(&player.shot, &imgSizes[ImgId::shot], &boss, &imgSizes[ImgId::droiDragon]) && boss.flag)
			{
				boss.life--;
				player.shot.flag = 0;
			}
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

		//描画=================================
		if (player.flag)
			DrawGraph(player.x, player.y, imgHandles[ImgId::player], TRUE);

		for (int i = 0; i < enemyNum; i++)
		{
			if (enemies[i].flag)
				DrawGraph(enemies[i].x, enemies[i].y, imgHandles[ImgId::enemy], TRUE);
		}
		for (int i = 0; i < enemyNum; i++)
		{
			if (enemies[i].shot.flag)
				DrawGraph(enemies[i].shot.x, enemies[i].shot.y, imgHandles[ImgId::shot], TRUE);
		}
		if (player.shot.flag)
			DrawGraph(player.shot.x, player.shot.y, imgHandles[ImgId::shot], TRUE);
		if (boss.flag)
			DrawGraph(boss.x, boss.y, imgHandles[ImgId::droiDragon], TRUE);

		ScreenFlip();
		if (ProcessMessage() == -1)
			break;
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	// ソフトの終了
	return 0;
}