#ifndef SNAKE
#define SNAKE

struct Snake
{
	int x;//坐标
	int y;
	int len;//蛇长度
	int direction;//蛇当前行动方向
};
struct Food
{
	int x;
	int y;
	bool hasfood;
};
#endif