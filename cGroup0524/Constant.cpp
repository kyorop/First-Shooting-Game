/*
c++�ɂ����Ă�const�񏊑��I�u�W�F�N�g�͓��������ɂȂ��Ă��܂��B
������O�������ɂ���ɂ�extern������Ηǂ��B
���Ȃ݂ɔ񏊑��I�u�W�F�N�g�Ƃ����̂́A�֐��̊O�Ő錾���ꂽ�I�u�W�F�N�g�̂��ƁB

���̂悤�Ƀw�b�_�t�@�C��(Constant.h)�Ǝ����t�@�C��(Constant.cpp)�𕪂��邱�ƂŁA�萔�ɑ������Ă���l��ς��Ă�Constant.h���C���N���[�h���Ă���t�@�C�����ăR���p�C������Ȃ��B
�t�@�C�������c��ɂȂ��Ă�����ăR���p�C���ɂ����鎞�Ԃ�����肸���Ƒ傫���Ȃ��Ă��܂��̂ŁA���̎�@�͈Ӗ�������B

�ăR���p�C�����N���闝�R
#include�̓v���v���Z�b�T���߂ł���A�R���p�C�������O�ɍs���鏈���ł���B
���̏������e�͂Ƃ����ƁA�����ď������t�@�C�����̒��g���A�����ɂ��̂܂܂�������@�B�I�ɓW�J����(���ߍ���)���Ƃł���B
���̂��߁A����w�b�_�t�@�C����ύX����ƁA���̃w�b�_�t�@�C�����C���N���[�h���Ă����t�@�C��(�R���p�C����)�͕ύX�O�̃w�b�_���e�����ߍ��܂ꂽ���̂�����A
�ύX���ꂽ�w�b�_��������x���ߍ���ŃR���p�C������K�v������B
���̂悤�ȗ��R�ŁA�w�b�_��ҏW����ƍăR���p�C�����N����B
*/


//�����萔
extern const int PLAYER_SPEED = 5;
extern const int ENEMY_SPEED = 3;
extern const int SHOT_SPEED = 3;
//�摜�T�C�Y�萔
extern const int PLAYER_SIZE = 64;
extern const int ENEMY_SIZE = 64;
extern const int SHOT_SIZE = 16;