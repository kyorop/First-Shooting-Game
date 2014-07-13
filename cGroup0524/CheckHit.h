//�t�@�C���킯�̗��K
//�ȉ�#�̂������͓̂�d�C���N���[�h�h�~�R�[�h

#ifndef CHECKHIT_H
#define CHECKHIT_H

struct Shot;
struct Enemy;
struct Player;

bool CheckHit(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
bool CheckHitShot(const Shot* shot, const Enemy* enemy);
bool CheckHitShot(const Shot* shot, const Player* player);

#endif // !CHECKHIT_H