#ifndef _maze
#define _maze
#include<iostream>
#include"player.h"
#include"enemy.h"
using namespace std;

class maze
{
private:
	int size; //has to be equal height and length (square)
	char **mazeData; //matrix of characters
	player *player1; //only one player
	enemy *enemies; //up to ten enemies
	int *enemyCount;
public:
	maze(); //deafault constructor
	maze(int value); //copy constructor
	~maze();
	void displayMaze();
	void createMazeLine(int line, string c); //read line from txt file
	void playerInfo(); //displays (x,y) and # of Arrows
	bool alive(); //checks player1 object status
	bool win(); //checks if player is set to win
	//functions for player
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();

	void shootRight();
	void shootLeft();
	void shootDown();
	void shootUp();
	//functions for enemies
	char enemyRight(int index); //needs enemy index from enemies array
	char enemyLeft(int index);
	char enemyUp(int index);
	char enemyDown(int index);

	void enemyInfo(); //used for testing only
	void swapEnemy(int index);//swap dead enemy to end of enemies list
	int getEnemyCount();
	int getEnemyX(int index);
	int getEnemyY(int index);

	int getPlayerX();
	int getPlayerY();
	bool isWall(int x, int y);
};


maze::maze()
{
	size = 0;
	mazeData = new char *[size];
	for (int i = 0; i < size; i++)
	{
		mazeData[i] = new char[size];
	}

	player1 = new player;
	enemies = new enemy[10];
	enemyCount = new int;
	*enemyCount = 0;
}

maze::maze(int value)
{
	size = value;
	mazeData = new char *[size];
	for (int i = 0; i < size; i++)
	{
		mazeData[i] = new char[size];
	}

	player1 = new player;
	enemies = new enemy[10];
	enemyCount = new int;
	*enemyCount = 0;
}

maze::~maze()
{

}

void maze::displayMaze()
{
	for (int i = 0; i < size; i++)
	{
		cout << "";
		for (int j = 0; j < size; j++)
		{
			cout << " " << mazeData[i][j] << " "; //display one decimal point
		}
		cout << endl;
	}
	cout << endl;
}

void maze::createMazeLine(int line, string c)//update enemy coordinates
{
	for (int i = 0; i < size; i++)
	{
		mazeData[line][i] = c[i];

		if (c[i] == '@') //Updates player location
		{
			player1->setX(i);
			player1->setY(line);
		}
		else if (c[i] == 'A')
		{
			enemies[0].setX(i);
			enemies[0].setY(line);
			enemies[0].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'B')
		{
			enemies[1].setX(i);
			enemies[1].setY(line);
			enemies[1].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'C')
		{
			enemies[2].setX(i);
			enemies[2].setY(line);
			enemies[2].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'D')
		{
			enemies[3].setX(i);
			enemies[3].setY(line);
			enemies[3].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'E')
		{
			enemies[4].setX(i);
			enemies[4].setY(line);
			enemies[4].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'F')
		{
			enemies[5].setX(i);
			enemies[5].setY(line);
			enemies[5].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'G')
		{
			enemies[6].setX(i);
			enemies[6].setY(line);
			enemies[6].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'H')
		{
			enemies[7].setX(i);
			enemies[7].setY(line);
			enemies[7].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'I')
		{
			enemies[8].setX(i);
			enemies[8].setY(line);
			enemies[8].setName(c[i]);
			(*enemyCount)++;
		}
		else if (c[i] == 'J')
		{
			enemies[9].setX(i);
			enemies[9].setY(line);
			enemies[9].setName(c[i]);
			(*enemyCount)++;
		}
	}
}

void maze::playerInfo()
{
	cout << "(" << player1->getX() << "," << player1->getY() << ")" << endl;
	cout << "#Arrows: " << player1->getArrows() << endl;
}

bool maze::alive()
{
	return player1->isAlive();
}

bool maze::win()
{
	return player1->isWin();
}

void maze::moveRight() //returns true if valid move
{
	char rightCell = mazeData[player1->getY()][player1->getX() + 1]; //char content of cell to right of player
	char curCell = mazeData[player1->getY()][player1->getX()]; //char content of current player cell

	if (rightCell == ' ')//empty space case
	{
		mazeData[player1->getY()][player1->getX() + 1] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setX(player1->getX() + 1); //sets player's new x value
	}

	else if (rightCell == '+')//arrow case
	{
		mazeData[player1->getY()][player1->getX() + 1] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze
		player1->setArrows(player1->getArrows() + 1); //add an arrow

		player1->setX(player1->getX() + 1); //sets player's new x value
	}

	else if (rightCell == '$') //chest case
	{
		mazeData[player1->getY()][player1->getX() + 1] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setX(player1->getX() + 1); //sets player's new x value

		cout << "Congratulations, you've won the game!" << endl;
		player1->setWin(true);
	}

	else if (rightCell == '~') //for walls
	{
		cout << "Invalid Move" << endl;
	}

	else //i.e any enemy A-J
	{
		char temp;

		temp = mazeData[player1->getY()][player1->getX() + 1]; // temp = next space which is an enemy

		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setX(player1->getX() + 1); //sets player's new x value, corpse location

		cout << "Enemy " << temp << " killed you!" << endl;
		player1->setFate(false); //false = dead
	}
}

void maze::moveLeft()
{
	char leftCell = mazeData[player1->getY()][player1->getX() - 1]; //char content of cell to left of player
	char curCell = mazeData[player1->getY()][player1->getX()]; //char content of current player cell

	if (leftCell == ' ')//empty space case
	{
		mazeData[player1->getY()][player1->getX() - 1] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setX(player1->getX() - 1); //sets player's new x value
	}

	else if (leftCell == '+')//arrow case
	{
		mazeData[player1->getY()][player1->getX() - 1] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze
		player1->setArrows(player1->getArrows() + 1); //add an arrow

		player1->setX(player1->getX() - 1); //sets player's new x value
	}

	else if (leftCell == '$') //chest case
	{
		mazeData[player1->getY()][player1->getX() - 1] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setX(player1->getX() - 1); //sets player's new x value

		cout << "Congratulations, you've won the game!" << endl;
		player1->setWin(true);
	}

	else if (leftCell == '~') //for walls
	{
		cout << "Invalid Move" << endl;
	}

	else //i.e any enemy A-J
	{
		char temp;

		temp = mazeData[player1->getY()][player1->getX() - 1]; // temp = next space which is an enemy

		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setX(player1->getX() - 1); //sets player's new x value, corpse location

		cout << "Enemy " << temp << " killed you!" << endl;
		player1->setFate(false); //false == dead
	}
}

void maze::moveDown()
{
	char downCell = mazeData[player1->getY() + 1][player1->getX()]; //char content of cell to left of player
	char curCell = mazeData[player1->getY()][player1->getX()]; //char content of current player cell

	if (downCell == ' ')//empty space case
	{
		mazeData[player1->getY() + 1][player1->getX()] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setY(player1->getY() + 1); //sets player's new y value
	}

	else if (downCell == '+')//arrow case
	{
		mazeData[player1->getY() + 1][player1->getX()] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze
		player1->setArrows(player1->getArrows() + 1); //add an arrow

		player1->setY(player1->getY() + 1); //sets player's new y value
	}

	else if (downCell == '$') //chest case
	{
		mazeData[player1->getY() + 1][player1->getX()] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setY(player1->getY() + 1); //sets player's new y value

		cout << "Congratulations, you've won the game!" << endl;
player1->setWin(true);
	}

	else if (downCell == '~') //for walls
	{
		cout << "Invalid Move" << endl;
	}

	else //i.e any enemy A-J
	{
		char temp;

		temp = mazeData[player1->getY() + 1][player1->getX()]; // temp = next space which is an enemy

		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setY(player1->getY() + 1); //sets player's new y value, corpse location

		cout << "Enemy " << temp << " killed you!" << endl;
		player1->setFate(false); //false == dead
	}
}

void maze::moveUp()
{
	char upCell = mazeData[player1->getY() - 1][player1->getX()]; //char content of cell to left of player
	char curCell = mazeData[player1->getY()][player1->getX()]; //char content of current player cell

	if (upCell == ' ')//empty space case
	{
		mazeData[player1->getY() - 1][player1->getX()] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setY(player1->getY() - 1); //sets player's new y value
	}

	else if (upCell == '+')//arrow case
	{
		mazeData[player1->getY() - 1][player1->getX()] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze
		player1->setArrows(player1->getArrows() + 1); //add an arrow

		player1->setY(player1->getY() - 1); //sets player's new y value
	}

	else if (upCell == '$') //chest case
	{
		mazeData[player1->getY() - 1][player1->getX()] = '@'; //update maze
		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setY(player1->getY() - 1); //sets player's new y value

		cout << "Congratulations, you've won the game!" << endl;
		player1->setWin(true);
	}

	else if (upCell == '~') //for walls
	{
		cout << "Invalid Move" << endl;
	}

	else //i.e any enemy A-J
	{
		char temp;

		temp = mazeData[player1->getY() - 1][player1->getX()]; // temp = next space which is an enemy

		mazeData[player1->getY()][player1->getX()] = ' '; //update maze

		player1->setY(player1->getY() - 1); //sets player's new y value, corpse location

		cout << "Enemy " << temp << " killed you!" << endl;
		player1->setFate(false); //false == dead
	}
}

void maze::shootRight()//use enemy count to declare arrow miss!
{
	char temp = mazeData[player1->getY()][player1->getX() + 1]; //initialize as player location one cell to right
	int count = player1->getX() + 1;
	int tempEnemyCount = *enemyCount; //for missing shot

	if (player1->getArrows() > 0)
	{
		player1->setArrows(player1->getArrows() - 1); //remove one arrow from inventory

		while (temp != '~')
		{
			if (temp == '+' || temp == ' ' || temp == '$')
			{
				count++;
				temp = mazeData[player1->getY()][count]; //cell to right
			}
			else
			{
				cout << "Enemy " << temp << " killed!" << endl;

				for (int i = 0; i < (*enemyCount); i++)
				{
					if (enemies[i].getName() == temp)
					{
						if (enemies[i].hasArrow())
						{
							mazeData[player1->getY()][count] = '+'; //enemy cell turned to arrow
						}
						else if (enemies[i].hasChest())
						{
							mazeData[player1->getY()][count] = '$'; //enemy cell turned to chest
						}
						else
						{
							mazeData[player1->getY()][count] = ' '; //enemy cell turned to empty space
						}
						enemies[i].setFate(false);
						swapEnemy(i); //move dead enemy to end of list
					}
				}

				(*enemyCount)--;

				if ((*enemyCount) == 0)
				{
					cout << "You've won the game!" << endl;
					player1->setWin(true);
				}

				temp = '~'; //dummy value to stop loop otherwise all enemies in row will die
			}
		}
		if (tempEnemyCount == (*enemyCount))
		{
			cout << "You Missed!" << endl;
		}
	}
	else
	{
		cout << "No arrows!" << endl;
	}
}

void maze::shootLeft()//use enemy count to declare arrow miss!
{
	char temp = mazeData[player1->getY()][player1->getX() - 1]; //initialize as player location one cell to left
	int count = player1->getX() - 1;
	int tempEnemyCount = *enemyCount;

	if (player1->getArrows() > 0)
	{
		player1->setArrows(player1->getArrows() - 1); //remove one arrow from inventory

		while (temp != '~')
		{
			if (temp == '+' || temp == ' ' || temp == '$')
			{
				count--;
				temp = mazeData[player1->getY()][count]; //cell to left
			}
			else
			{
				cout << "Enemy " << temp << " killed!" << endl;

				for (int i = 0; i < (*enemyCount); i++)
				{
					if (enemies[i].getName() == temp)
					{
						if (enemies[i].hasArrow())
						{
							mazeData[player1->getY()][count] = '+'; //enemy cell turned to arrow
						}
						else if (enemies[i].hasChest())
						{
							mazeData[player1->getY()][count] = '$'; //enemy cell turned to chest
						}
						else
						{
							mazeData[player1->getY()][count] = ' '; //enemy cell turned to empty space
						}
						enemies[i].setFate(false);
						swapEnemy(i); //move dead enemy to end of list
					}
				}

				(*enemyCount)--;

				if ((*enemyCount) == 0)
				{
					cout << "You've won the game!" << endl;
					player1->setWin(true);
				}

				temp = '~'; //dummy value to stop loop
			}
		}
		if (tempEnemyCount == (*enemyCount))
		{
			cout << "You Missed!" << endl;
		}
	}
	else
	{
		cout << "No arrows!" << endl;
	}
}

void maze::shootDown()//use enemy count to declare arrow miss!
{
	char temp = mazeData[player1->getY() + 1][player1->getX()]; //initialize as player location one cell below
	int count = player1->getY() + 1;
	int tempEnemyCount = *enemyCount;

	if (player1->getArrows() > 0)
	{
		player1->setArrows(player1->getArrows() - 1); //remove one arrow from inventory

		while (temp != '~')
		{
			if (temp == '+' || temp == ' ' || temp == '$')
			{
				count++;
				temp = mazeData[count][player1->getX()]; //cell to right
			}
			else
			{
				cout << "Enemy " << temp << " killed!" << endl;

				for (int i = 0; i < (*enemyCount); i++)
				{
					if (enemies[i].getName() == temp)
					{
						if (enemies[i].hasArrow())
						{
							mazeData[count][player1->getX()] = '+'; //enemy cell turned to arrow
						}
						else if (enemies[i].hasChest())
						{
							mazeData[count][player1->getX()] = '$'; //enemy cell turned to chest
						}
						else
						{
							mazeData[count][player1->getX()] = ' '; //enemy cell turned to empty space
						}
						enemies[i].setFate(false);
						swapEnemy(i); //move dead enemy to end of list
					}
				}

				(*enemyCount)--;

				if ((*enemyCount) == 0)
				{
					cout << "You've won the game!" << endl;
					player1->setWin(true);
				}

				temp = '~'; //dummy value to stop loop
			}
		}
		if (tempEnemyCount == (*enemyCount))
		{
			cout << "You Missed!" << endl;
		}
	}
	else
	{
		cout << "No arrows!" << endl;
	}
}

void maze::shootUp()//use enemy count to declare arrow miss!
{
	char temp = mazeData[player1->getY() - 1][player1->getX()]; //initialize as player location one cell below
	int count = player1->getY() - 1;
	int tempEnemyCount = *enemyCount;

	if (player1->getArrows() > 0)
	{
		player1->setArrows(player1->getArrows() - 1); //remove one arrow from inventory

		while (temp != '~')
		{
			if (temp == '+' || temp == ' ' || temp == '$')
			{
				count--;
				temp = mazeData[count][player1->getX()]; //cell to right
			}
			else
			{
				cout << "Enemy " << temp << " killed!" << endl;

				for (int i = 0; i < (*enemyCount); i++)
				{
					if (enemies[i].getName() == temp)
					{
						if (enemies[i].hasArrow())
						{
							mazeData[count][player1->getX()] = '+'; //enemy cell turned to arrow
						}
						else if (enemies[i].hasChest())
						{
							mazeData[count][player1->getX()] = '$'; //enemy cell turned to chest
						}
						else
						{
							mazeData[count][player1->getX()] = ' '; //enemy cell turned to empty space
						}
						enemies[i].setFate(false);
						swapEnemy(i); //move dead enemy to end of list
					}
				}

				(*enemyCount)--;

				if ((*enemyCount) == 0)
				{
					cout << "You've won the game!" << endl;
					player1->setWin(true);
				}

				temp = '~'; //dummy value to stop loop
			}
		}
		if (tempEnemyCount == (*enemyCount))
		{
			cout << "You Missed!" << endl;
		}
	}
	else
	{
		cout << "No arrows!" << endl;
	}
}

void maze::enemyInfo()
{
	for (int i = 0; i < 4; i++)
	{
		cout << "Enemy " << enemies[i].getName() << endl;
		cout << "(" << enemies[i].getX() << "," << enemies[i].getY() << ")" << endl;
		cout << "Alive? " << enemies[i].isAlive() << endl;
	}
}

char maze::enemyRight(int index)
{
	if (enemies[index].isAlive() == true)
	{
		char rightCell = mazeData[enemies[index].getY()][enemies[index].getX() + 1]; //char content of cell to right of enemy
		char curCell = mazeData[enemies[index].getY()][enemies[index].getX()]; //char content of current enemy cell

		if (rightCell == ' ')//empty space case
		{
			mazeData[enemies[index].getY()][enemies[index].getX() + 1] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' '; //update maze
			}

			enemies[index].setX(enemies[index].getX() + 1); //sets enemies's new x value
		}

		else if (rightCell == '+')//arrow case
		{
			mazeData[enemies[index].getY()][enemies[index].getX() + 1] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
				enemies[index].setArrow(true); //add an arrow
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setArrow(true); //add an arrow
			}
			enemies[index].setX(enemies[index].getX() + 1); //sets enemy new x value
		}

		else if (rightCell == '$')//chest case
		{
			mazeData[enemies[index].getY()][enemies[index].getX() + 1] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			enemies[index].setX(enemies[index].getX() + 1); //sets enemy new x value
		}

		else if (rightCell == '~') //for walls
		{
			cout << "Invalid Move" << endl;
		}

		else if (rightCell == '@') //player case
		{
			char temp;

			temp = mazeData[enemies[index].getY()][enemies[index].getX()]; // temp = enemy name

			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else //another enemy
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
			}
			mazeData[enemies[index].getY()][enemies[index].getX() + 1] = temp; //update maze

			enemies[index].setX(enemies[index].getX() + 1); //sets enemy new x value, player corpse location

			cout << "Enemy " << temp << " killed you!" << endl;
			player1->setFate(false); //false = dead
		}
		else
		{//for testing enemy collisions
			//cout << "Enemy " << mazeData[enemies[index].getY()][enemies[index].getX() + 1] << " obstruction!" << endl;
		}
	}
	return 'e';
}

char maze::enemyLeft(int index)
{
	if (enemies[index].isAlive() == true)
	{
		char leftCell = mazeData[enemies[index].getY()][enemies[index].getX() - 1]; //char content of cell to left of enemy
		char curCell = mazeData[enemies[index].getY()][enemies[index].getX()]; //char content of current enemy cell

		if (leftCell == ' ')//empty space case
		{
			mazeData[enemies[index].getY()][enemies[index].getX() - 1] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' '; //update maze
			}

			enemies[index].setX(enemies[index].getX() - 1); //sets enemies's new x value
		}

		else if (leftCell == '+')//arrow case
		{
			mazeData[enemies[index].getY()][enemies[index].getX() - 1] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
				enemies[index].setArrow(true); //add an arrow
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setArrow(true); //add an arrow
			}
			enemies[index].setX(enemies[index].getX() - 1); //sets enemy new x value
		}

		else if (leftCell == '$')//chest case
		{
			mazeData[enemies[index].getY()][enemies[index].getX() - 1] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			enemies[index].setX(enemies[index].getX() - 1); //sets enemy new x value
		}

		else if (leftCell == '~') //for walls
		{
			cout << "Invalid Move" << endl;
		}

		else if (leftCell == '@') //player case
		{
			char temp;

			temp = mazeData[enemies[index].getY()][enemies[index].getX()]; // temp = enemy name

			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else //another enemy
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
			}
			mazeData[enemies[index].getY()][enemies[index].getX() - 1] = temp; //update maze

			enemies[index].setX(enemies[index].getX() - 1); //sets enemy new x value, player corpse location

			cout << "Enemy " << temp << " killed you!" << endl;
			player1->setFate(false); //false = dead
		}
		else
		{//test for enemy collisions
			//cout << "Enemy " << mazeData[enemies[index].getY()][enemies[index].getX() - 1] << " obstruction!" << endl;
		}
	}
	return 'w';
}

char maze::enemyUp(int index)
{
	if (enemies[index].isAlive() == true)
	{
		char UpCell = mazeData[enemies[index].getY() - 1][enemies[index].getX()]; //char content of cell above enemy
		char curCell = mazeData[enemies[index].getY()][enemies[index].getX()]; //char content of current enemy cell

		if (UpCell == ' ')//empty space case
		{
			mazeData[enemies[index].getY() - 1][enemies[index].getX()] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' '; //update maze
			}

			enemies[index].setY(enemies[index].getY() - 1); //sets enemies's new x value
		}

		else if (UpCell == '+')//arrow case
		{
			mazeData[enemies[index].getY() - 1][enemies[index].getX()] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
				enemies[index].setArrow(true); //add an arrow
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setArrow(true); //add an arrow
			}
			enemies[index].setY(enemies[index].getY() - 1); //sets enemy new x value
		}

		else if (UpCell == '$')//chest case
		{
			mazeData[enemies[index].getY() - 1][enemies[index].getX()] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			enemies[index].setY(enemies[index].getY() - 1); //sets enemy new x value
		}

		else if (UpCell == '~') //for walls
		{
			cout << "Invalid Move" << endl;
		}

		else if (UpCell == '@') //player case
		{
			char temp;

			temp = mazeData[enemies[index].getY()][enemies[index].getX()]; // temp = enemy name

			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else //another enemy
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
			}
			mazeData[enemies[index].getY() - 1][enemies[index].getX()] = temp; //update maze

			enemies[index].setY(enemies[index].getY() - 1); //sets enemy new x value, player corpse location

			cout << "Enemy " << temp << " killed you!" << endl;
			player1->setFate(false); //false = dead
		}
		else
		{//test for enemy collisions
			//cout << "Enemy " << mazeData[enemies[index].getY() - 1][enemies[index].getX()] << " obstruction!" << endl;
		}
	}
	return 'n';
}

char maze::enemyDown(int index)
{
	if (enemies[index].isAlive() == true)
	{
		char DownCell = mazeData[enemies[index].getY() + 1][enemies[index].getX()]; //char content of cell to down of enemy
		char curCell = mazeData[enemies[index].getY()][enemies[index].getX()]; //char content of current enemy cell

		if (DownCell == ' ')//empty space case
		{
			mazeData[enemies[index].getY() + 1][enemies[index].getX()] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' '; //update maze
			}

			enemies[index].setY(enemies[index].getY() + 1); //sets enemies's new x value
		}

		else if (DownCell == '+')//arrow case
		{
			mazeData[enemies[index].getY() + 1][enemies[index].getX()] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
			}
			else if (enemies[index].hasChest())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
				enemies[index].setArrow(true); //add an arrow
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setArrow(true); //add an arrow
			}
			enemies[index].setY(enemies[index].getY() + 1); //sets enemy new y value
		}

		else if (DownCell == '$')//chest case
		{
			mazeData[enemies[index].getY() + 1][enemies[index].getX()] = enemies[index].getName(); //update maze with enemy name A-J
			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
			}
			else
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
				enemies[index].setChest(true); //add chest to enemy inventory
			}
			enemies[index].setY(enemies[index].getY() + 1); //sets enemy new y value
		}

		else if (DownCell == '~') //for walls
		{
			cout << "Invalid Move" << endl;
		}

		else if (DownCell == '@') //player case
		{
			char temp;

			temp = mazeData[enemies[index].getY()][enemies[index].getX()]; // temp = enemy name

			if (enemies[index].hasArrow())
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '+';
				enemies[index].setArrow(false); //reset
			}
			else if (enemies[index].hasChest()) //in case we implement multiple chests
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = '$';
				enemies[index].setChest(false); //reset
			}
			else //another enemy
			{
				mazeData[enemies[index].getY()][enemies[index].getX()] = ' ';
			}
			mazeData[enemies[index].getY() + 1][enemies[index].getX()] = temp; //update maze

			enemies[index].setY(enemies[index].getY() + 1); //sets enemy new y value, player corpse location

			cout << "Enemy " << temp << " killed you!" << endl;
			player1->setFate(false); //false = dead
		}
		else
		{//test for enemy collisions
			//cout << "Enemy " << mazeData[enemies[index].getY() + 1][enemies[index].getX()] << " obstruction!" << endl;
		}
	}
	return 's';
}

void maze::swapEnemy(int index) //swapping enemies to end of array
{
	enemy temp = enemies[index];

	enemies[index] = enemies[(*enemyCount)-1]; //last index
	enemies[(*enemyCount)-1] = temp;
}

int maze::getEnemyCount()
{
	return (*enemyCount);
}

int maze::getEnemyX(int index)
{
	return enemies[index].getX();
}

int maze::getEnemyY(int index)
{
	return enemies[index].getY();
}

int maze::getPlayerX()
{
	return player1->getX();
}

int maze::getPlayerY()
{
	return player1->getY();
}

bool maze::isWall(int x, int y)
{
	if (mazeData[y][x] == '~')
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif