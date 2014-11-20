#ifndef CHARACTERSTRUCT_H
#define CHARACTERSTRUCT_H
#include <stdbool.h>

typedef struct 
{
	int x;
	int y;
	char flag;
}Shot;

typedef struct
{
	int x;
	int y;
	bool flag;
	Shot shot;
}Player;

typedef struct
{
	int x;
	int y;
	int muki;
	bool flag;
	Shot shot;
}Enemy;

typedef struct
{
	int w;
	int h;
}ImgSize;

#endif // !CHARACTERSTRUCT_H
