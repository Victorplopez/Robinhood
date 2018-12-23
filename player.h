#ifndef _player
#define _player

class player
{
private:
	int x; //x coordinate
	int y; //y coordinate
	int arrows;
	bool alive;
	bool win;
public:
	player();
	~player();
	int getX();
	int getY();
	void setX(int var1);
	void setY(int var2);
	int getArrows();
	void setArrows(int num);
	bool isAlive();
	void setFate(bool option); //set if alive or dead
	bool isWin();
	void setWin(bool option);
};

player::player()
{
	x = 1;
	y = 1;
	arrows = 0;
	alive = true;
	win = false;
}

player::~player()
{
	
}

int player::getX()
{
	return x;
}

int player::getY()
{
	return y;
}

void player::setX(int var1)
{
	x = var1;
}

void player::setY(int var2)
{
	y = var2;
}

int player::getArrows()
{
	return arrows;
}

void player::setArrows(int num)
{
	arrows = num;
}

bool player::isAlive()
{
	return alive;
}

void player::setFate(bool option)
{
	alive = option;
}


bool player::isWin()
{
	return win;
}

void player::setWin(bool option)
{
	win = option;
}

#endif
