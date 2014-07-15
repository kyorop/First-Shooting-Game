#include "CheckHit.h"
#include "CharacterStruct.h"
#include "Constant.h"
#include "Boss.h"

bool CheckHit(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 + height1 > y2 && y1 < y2 + height2);
}

bool CheckHitShot(const Shot* shot, const Enemy* enemy)
{
	return CheckHit(shot->x, shot->y, SHOT_SIZE, SHOT_SIZE, enemy->x, enemy->y, ENEMY_SIZE, ENEMY_SIZE);
}

bool CheckHitShot(const Shot* shot, const Player* player)
{
	int h = 15;//•â³‚Ìh
	int shotSize = SHOT_SIZE - h;
	int playerSize = PLAYER_SIZE - h;
	return CheckHit(shot->x + h, shot->y + h, shotSize, shotSize, player->x + h, player->y + h, playerSize, playerSize);
}

bool CheckHitShot(const Shot *shot, const Boss *boss)
{
	return 1;
}