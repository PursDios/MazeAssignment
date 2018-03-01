#include "stdlib.h"
#include "iostream"
#include "MazeController.h"
#include "Maze.h"
#include "string"
#include "vector"
#include "Player.h"
#include "fstream"

using namespace std;
Maze m;
MazeController::MazeController(void)
{
	MainMenu();
}
void MazeController::MainMenu(void)
{
	int choice;
	bool valid = false;
	do
	{
		system("CLS");
		cout << "Please select which maze you would like to do:" << endl;
		cout << "1)Static Maze\n2)File Maze\n3)Random Maze" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			StaticMaze();
			valid = true;
			break;
		case 2:
			FileMaze();
			valid = true;
			break;
		case 3:
			RandomMaze();
			valid = true;
			break;
		default:
			cout << "Invalid Selection please try again" << endl;
			system("PAUSE");
			break;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (!valid);
}
void MazeController::StaticMaze(void)
{
	//makes a list of rooms(vector)
	vector<Room*> rooms;
	rooms.resize(25);
	//adds rooms to the list
	for (int i = 0; i < 14; i++)
	{
		Room* r = new Room();
		rooms[i] = r;
	}

	Player p;
	//links all the rooms to one another based on direction (North(1),East(2),South(3),West(4))
	rooms[0]->Link(2, *rooms[2]); //A TO C
	rooms[0]->Link(4, *rooms[5]); //A TO F
	rooms[1]->Link(3, *rooms[2]); //B TO C
	rooms[2]->Link(1, *rooms[1]); //C TO B
	rooms[2]->Link(2, *rooms[3]); //C TO D
	rooms[2]->Link(3, *rooms[7]); //C TO H
	rooms[2]->Link(4, *rooms[0]); //C TO A
	rooms[3]->Link(4, *rooms[2]); //D TO C
	rooms[3]->Link(2, *rooms[4]); //D TO E
	rooms[4]->Link(4, *rooms[3]); //E TO D
	rooms[5]->Link(3, *rooms[10]); //F TO K
	rooms[5]->Link(4, *rooms[9]); //F TO J
	rooms[5]->Link(1, *rooms[0]); //F TO A
								  //G?
	rooms[7]->Link(2, *rooms[8]); //H TO I
	rooms[7]->Link(3, *rooms[12]); //H TO M
	rooms[7]->Link(4, *rooms[11]); //H TO L
	rooms[7]->Link(1, *rooms[2]); //H TO C
	rooms[8]->Link(4, *rooms[7]); //I TO H
	rooms[9]->Link(1, *rooms[5]); //J TO F
	rooms[11]->Link(1, *rooms[7]); //L TO H
	rooms[11]->Link(4, *rooms[10]); //L TO K
	rooms[10]->Link(2, *rooms[11]); //K TO L
	rooms[10]->Link(1, *rooms[5]); //K TO F
	rooms[12]->Link(3, *rooms[13]); //M TO N
	rooms[12]->Link(1, *rooms[7]); //M TO H

	//sets the rooms vector to the private one in Maze.
	m.setRoomList(rooms);
	m.Play();
}
void MazeController::FileMaze(void)
{
	vector<Room*> rooms;
	rooms.resize(25);
	//http://www.cplusplus.com/doc/tutorial/files/    READING INPUT
	ifstream fileLoc("maze"); //filelocation (c# streamwriter)
	string line, delimiter="/", token;
	size_t pos = 0;
	string NESW[4];

	int i=0, x;
	try
	{
		if (fileLoc.is_open)
		{
			while (getline (fileLoc,line))
			{
				while ((pos = line.find(delimiter)) != string::npos)
				{
					token = line.substr(0, pos);
					if (token != "-")
					{
						NESW[i] = token;
						//Cannot make links here otherwise all directions will be set to the same room
					}
					line.erase(0, pos + delimiter.length());
				}
				//http://www.cplusplus.com/reference/string/stoi/     CONVERT FROM STRING TO INT
				rooms[i]->Link(1, *rooms[stoi(NESW[1])]);
				rooms[i]->Link(2, *rooms[stoi(NESW[1])]);
				rooms[i]->Link(3, *rooms[stoi(NESW[1])]);
				rooms[i]->Link(4, *rooms[stoi(NESW[1])]);
				i++;
			}
		}
	}
	catch (exception e)
	{
		cout << e.~exception << endl;
	}
	m.setRoomList(rooms);
}
void MazeController::RandomMaze(void)
{

}