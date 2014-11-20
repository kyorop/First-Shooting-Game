//ファイルわけの練習
//以下#のついたものは二重インクルード防止コード

#ifndef CHECKHIT_H
#define CHECKHIT_H
#include <stdbool.h>

typedef struct Shot Shot;
typedef struct Enemy Enemy;
typedef struct Player Player;
typedef struct Boss Boss;
typedef struct ImgSize ImgSize;

bool CheckHit(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
bool CheckHitShot(const Shot* shot, const Enemy* enemy);
bool CheckHitShot(const Shot* shot, const Player* player);
bool CheckHitShot(const Shot *shot, ImgSize *shotSize, const Boss *boss, ImgSize *bossSize);

#endif // !CHECKHIT_H