#ifndef CHARACTERSTRUCT_H
#define CHARACTERSTRUCT_H

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

struct ImgSize
{
	int w;
	int h;
};

#endif // !CHARACTERSTRUCT_H
