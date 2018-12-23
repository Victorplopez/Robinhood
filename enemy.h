#ifndef _enemy
#define _enemy

class enemy
{
private:
	char name; //A-J
	int x; // x coordinate
	int y; // y coordinate
	bool alive;
	bool arrow; //restore arrow to maze
	bool chest; //restore chest to maze
public:
	enemy();
	~enemy();
	void setName(char value);
	char getName();
	void setX(int value);
	int getX();
	void setY(int value);
	int getY();
	bool isAlive();
	void setFate(bool option);
	bool hasArrow();
	void setArrow(bool option);
	bool hasChest();
	void setChest(bool option);
};

enemy::enemy()
{
	name = 'Z'; //unassigned name
	x = 0;
	y = 0;
	alive = true;
	arrow = false;
	chest = false;
}

enemy::~enemy()
{
}

void enemy::setName(char value)
{
	name = value;
}

char enemy::getName()
{
	return name;
}

void enemy::setX(int value)
{
	x = value;
}

int enemy::getX()
{
	return x;
}

void enemy::setY(int value)
{
	y = value;
}

int enemy::getY()
{
	return y;
}

bool enemy::isAlive()
{
	return alive;
}

void enemy::setFate(bool option)
{
	alive = option;
}

bool enemy::hasArrow()
{
	return arrow;
}

void enemy::setArrow(bool option)
{
	arrow = option;
}

bool enemy::hasChest()
{
	return chest;
}

void enemy::setChest(bool option)
{
	chest = option;
}

#endif