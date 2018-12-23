/////////////////////////////////////////////
//// Michael Osborne, Victor Lopez CSCI 115 Project 2
//// Turned Based Robinhood: Using Breadth First Search
//// This program is menu driven, the user can select
//// an option (1-4) Easy, Medium, Hard.
//// Use W for up, A for left, S for down and D for right
//// 1 pulls out bow and WASD used to shoot a certain direction.
/////////////////////////////////////////////

#include <iostream>
#include "maze.h" //contains matrix
#include "player.h"
#include <fstream> //used to put textfile into matrix
#include <string>
#include "queue.h" //used for frontier in Breadth First Search
#include "posPath.h" //stores positions (x,y) and path [nnee]... etc
#include <limits> //used for user input type checking

using namespace std;

void loadLevel(int size, maze aMaze, string fName); //reads text file
void option(char wasd, maze aMaze); //takes in user input
bool inExp(int x, int y, int count, posPath* exp); //helper function to determine if coordinate has been explored

int main()
{
	bool quit = false;


	while (quit != true)
	{
		int choice;

		cout << "Choose a level:" << endl;
		cout << "(1) Easy" << endl;
		cout << "(2) Medium" << endl;
		cout << "(3) Hard" << endl;
		cout << "(4) Exit" << endl;

		while (!(cin >> choice)) { //protects program from crashing due to invalid type input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter (int) value: ";
		}

		switch (choice)
		{
		case 1: //Easy
		{
			maze myMaze1(10); //current map is 10x10
			char dir; //direction
			bool cont = true;

			loadLevel(10, myMaze1, "easy.txt");

			myMaze1.playerInfo();
			myMaze1.displayMaze();

			while (myMaze1.alive() == true && myMaze1.win() == false) //end of game conditions
			{
				cout << "Direction (w,a,s,d), 1 to pull out bow." << endl;
				cin >> dir;
				cout << endl;

				option(dir, myMaze1);
				cout << endl;
			}
			break;
		}
		case 2: //Medium
		{
			maze myMaze2(15); //current map is 15x15
			char dir; //direction
			bool cont = true;

			loadLevel(15, myMaze2, "medium.txt");

			myMaze2.playerInfo();
			myMaze2.displayMaze();

			while (myMaze2.alive() == true && myMaze2.win() == false) //end of game conditions
			{
				cout << "Direction (w,a,s,d), 1 to pull out bow." << endl;
				cin >> dir;
				cout << endl;

				option(dir, myMaze2);
				cout << endl;
			}
			break;
		}
		case 3: //Hard
		{
			maze myMaze3(20); //current map is 20x20
			char dir; //direction
			bool cont = true;

			loadLevel(20, myMaze3, "hard.txt");

			myMaze3.playerInfo();
			myMaze3.displayMaze();

			while (myMaze3.alive() == true && myMaze3.win() == false) //end of game conditions
			{
				cout << "Direction (w,a,s,d), 1 to pull out bow." << endl;
				cin >> dir;
				cout << endl;

				option(dir, myMaze3);
				cout << endl;
			}
			break;
		}
		case 4: //Exit
		{
			quit = true;
			break;
		}
		default:
		{
			cout << "Invalid Entry" << endl;
			break;
		}
		}
	}

	system("pause");
	return 0;
}

void loadLevel(int size, maze aMaze, string fName) //only designed for equal length and width grid
{
	string line;
	ifstream textfile;
	int i = 0;

	textfile.open(fName);

	if (textfile.is_open())
	{
		while (!textfile.eof()) //fill maze with elements of textfile
		{
			getline(textfile, line);

			if (line.length() == size) //make sure text file line and maze size match
			{
				aMaze.createMazeLine(i, line);
				i++;
			}
			else
			{
				cout << "Invalid line length!" << endl;
			}
		}
	}
	else
	{
		cout << "Filename doesn't match!" << endl;
	}
}

void option(char wasd, maze aMaze)
{
	char shootDir;
	int numEnemy = aMaze.getEnemyCount();

	if (wasd == 'w')
	{
		aMaze.moveUp();
		aMaze.playerInfo();
	}
	else if (wasd == 'a')
	{
		aMaze.moveLeft();
		aMaze.playerInfo();
	}
	else if (wasd == 's')
	{
		aMaze.moveDown();
		aMaze.playerInfo();
	}
	else if (wasd == 'd')
	{
		aMaze.moveRight();
		aMaze.playerInfo();
	}
	else if (wasd == '1')
	{
		cout << "Shoot Direction (w,a,s,d)" << endl;
		cin >> shootDir;
		cout << endl;

		if (shootDir == 'w')
		{
			aMaze.shootUp();
			aMaze.playerInfo();
		}
		else if (shootDir == 'a')
		{
			aMaze.shootLeft();
			aMaze.playerInfo();
		}
		else if (shootDir == 's')
		{
			aMaze.shootDown();
			aMaze.playerInfo();
		}
		else if (shootDir == 'd')
		{
			aMaze.shootRight();
			aMaze.playerInfo();
		}

	}
	else
	{
		cout << "Invalid key! (wasd or 1 only)!" << endl;
	}

	if (aMaze.win() == false && aMaze.alive() == true)
	{

		for (int i = 0; i < numEnemy; i++)
		{
			posPath explored[250]; //would need to increase size if larger maps are implemented
			Queue<posPath> frontier;
			posPath startState;
			startState.setX(aMaze.getEnemyX(i));
			startState.setY(aMaze.getEnemyY(i));

			frontier.enqueue(startState);

			int count = 0; //used to track # of elements in explored
			bool madeMove = false; //used to determine if direction has been chosen in while loop

			while (!frontier.isEmpty() && madeMove == false) //enter only if frontier is not empty and enemy hasn't made move
			{
				int xPos = frontier.peekFront().getX();
				int yPos = frontier.peekFront().getY();
				char* path = frontier.peekFront().getPath(); //pulls path of posPath in front of frontier(queue)
				int pathCount = frontier.peekFront().getPathCount();
				bool inExplored = false;

				frontier.dequeue(); //aka pop

				inExplored = inExp(xPos, yPos, count, explored); //checks if the location is already in explored

				if ((aMaze.getPlayerX() == xPos && aMaze.getPlayerY() == yPos) && inExplored == false) //killing player is the goal!
				{
					char dir = path[0]; //we only return first direction of path because enemies are only allowed one move per turn

					if (dir == 'n')
					{
						aMaze.enemyUp(i);
					}
					else if (dir == 's')
					{
						aMaze.enemyDown(i);
					}
					else if (dir == 'e')
					{
						aMaze.enemyRight(i);
					}
					else if (dir == 'w')
					{
						aMaze.enemyLeft(i);
					}
					else
					{
						cout << "invalid enemy direction!" << endl;
					}
					madeMove = true;
				}
				else
				{
					if (inExplored == false) //don't add duplicates to explored, saves space and time
					{
						explored[count].setX(xPos); 
						explored[count].setY(yPos);
						count++;
					}
				}
				// below adds all valid directions for a particular cell in the matrix, unless there is a wall
				if (madeMove == false && inExplored == false) //inExplored check optimizes runtime
				{
					posPath nextUp;
					posPath nextRight;
					posPath nextDown;
					posPath nextLeft;
					int x = xPos;
					int y = yPos - 1;

					if (!aMaze.isWall(x, y))
					{
						nextUp.setX(x);
						nextUp.setY(y);
						for (int k = 0; k < pathCount; k++)
						{
							nextUp.addDir(path[k]); //enemy move north
						}
						nextUp.addDir('n');

						frontier.enqueue(nextUp);
					}


					x++;
					y++;

					if (!aMaze.isWall(x, y))
					{
						nextRight.setX(x);
						nextRight.setY(y);
						for (int k = 0; k < pathCount; k++)
						{
							nextRight.addDir(path[k]); //enemy move east
						}

						nextRight.addDir('e');

						frontier.enqueue(nextRight);
					}

					y++;
					x--;

					if (!aMaze.isWall(x, y))
					{
						nextDown.setX(x);
						nextDown.setY(y);
						for (int k = 0; k < pathCount; k++)
						{
							nextDown.addDir(path[k]); //enemy move south
						}
						nextDown.addDir('s');

						frontier.enqueue(nextDown);
					}

					x--;
					y--;

					if (!aMaze.isWall(x, y))
					{
						nextLeft.setX(x);
						nextLeft.setY(y);
						for (int k = 0; k < pathCount; k++)
						{
							nextLeft.addDir(path[k]); //enemy move west
						}
						nextLeft.addDir('w');

						frontier.enqueue(nextLeft);
					}
				}
			}
		}
	}
	aMaze.displayMaze(); //display maze after all enemies move
}

	bool inExp(int x, int y, int count, posPath* exp)
	{
		posPath* explored = exp;

		for (int j = 0; j < count; j++) //in explored?
		{
			if (x == explored[j].getX() && y == explored[j].getY())
			{
				return true;
			}
		}
		return false;
	}