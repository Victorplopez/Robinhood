#ifndef _posPath
#define _posPath
#include "queue.h"

class posPath {
private:
	int x;
	int y;
	char *path; //i.e [nwse] n = north etc
	int *pathCount;
public:
	posPath();
	void setX(int var1);
	int getX();
	void setY(int var1);
	int getY();
	void updatePath(int a, int b, char dir);
	void displayPath();
	char* getPath();
	int getPathCount();
	void addDir(char a);
};

posPath::posPath()
{
	x = 0;
	y = 0;
	path = new char[200]; //may need to be set bigger if very large maze is created
	pathCount = new int (0);
	*pathCount = 0;
}

void posPath::setX(int var1)
{
	x = var1;
}

int posPath::getX()
{
	return x;
}

void posPath::setY(int var1)
{
	y = var1;
}

int posPath::getY()
{
	return y;
}

void posPath::updatePath(int a, int b, char dir)
{
	x = a;
	y = b;
	path[*(pathCount)] = dir;
	(*pathCount)++;
}

void posPath::displayPath()
{
	cout << "[";
	for (int i = 0; i < (*pathCount); i++)
	{
		cout << path[i];
	}
	cout << "]" << endl;
}

char* posPath::getPath()
{
	return path;
}

int posPath::getPathCount()
{
	return *(pathCount);
}

void posPath::addDir(char a) //adds direction to path
{
	path[(*pathCount)] = a;
	(*pathCount)++;
}
#endif
