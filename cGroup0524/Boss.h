#ifndef BOSS_H
#define BOSS_H

typedef struct
{
	int x;
	int y;
	int flag;
	int life;
	int isVisible;
}Boss;

void BossUpdate(Boss *boss);

#endif // !BOSS_H
