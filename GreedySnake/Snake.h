#ifndef SNAKE
#define SNAKE

struct Snake
{
	int x;//����
	int y;
	int len;//�߳���
	int direction;//�ߵ�ǰ�ж�����
};
struct Food
{
	int x;
	int y;
	bool hasfood;
};
#endif