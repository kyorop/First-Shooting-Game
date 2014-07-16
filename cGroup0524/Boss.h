#ifndef BOSS_H
#define BOSS_H

struct Boss
{
	int x;
	int y;
	int flag;
	int life;
	int isVisible;
};

void BossUpdate(Boss *boss);

#endif // !BOSS_H
