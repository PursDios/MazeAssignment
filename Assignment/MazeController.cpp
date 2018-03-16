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
	for (int i = 0; i < 25; i++)
	{
		Room* r = new Room();
		rooms[i] = r;
	}
	SpecialRoom* r = new SpecialRoom();
	r->setSpecialRoom(*rooms[6]);
	rooms[2] = r;

	//links all the rooms to one another based on direction (North(1),East(2),South(3),West(4))
	rooms[0]->Link(2, *rooms[2]); //A TO C
	rooms[0]->Link(4, *rooms[5]); //A TO F
	rooms[1]->Link(3, *rooms[2]); //B TO C
	rooms[2]->Link(1, *rooms[1]); //C TO B
	rooms[2]->Link(2, *rooms[3]); //C TO D
	rooms[2]->Link(3, *rooms[7]); //C TO H
	rooms[2]->Link(4, *rooms[0]); //C TO A
	rooms[3]->Link(2, *rooms[4]); //D TO E
	rooms[3]->Link(4, *rooms[2]); //D TO C
	rooms[4]->Link(4, *rooms[3]); //E TO D
	rooms[5]->Link(1, *rooms[0]); //F TO A
	rooms[5]->Link(3, *rooms[10]); //F TO K
	rooms[5]->Link(4, *rooms[9]); //F TO J
	rooms[6]->Link(1, *rooms[5]); //G to F
	rooms[7]->Link(1, *rooms[2]); //H TO C
	rooms[7]->Link(2, *rooms[8]); //H TO I
	rooms[7]->Link(3, *rooms[12]); //H TO M
	rooms[7]->Link(4, *rooms[11]); //H TO L
	rooms[8]->Link(4, *rooms[7]); //I TO H
	rooms[9]->Link(1, *rooms[5]); //J TO F
	rooms[10]->Link(1, *rooms[5]); //K TO F
	rooms[10]->Link(2, *rooms[11]); //K TO L
	rooms[11]->Link(1, *rooms[7]); //L TO H
	rooms[11]->Link(4, *rooms[10]); //L TO K
	rooms[12]->Link(1, *rooms[7]); //M TO H
	rooms[12]->Link(3, *rooms[13]); //M TO N

	//sets the rooms vector to the private one in Maze.
	rooms[13]->setWinningRoom();
	m.setRoomList(rooms);
	m.Play();
}
void MazeController::FileMaze(void)
{
	vector<Room*> rooms;
	rooms.resize(25);
	for (int i = 0; i < 25; i++)
	{
		Room* r = new Room();
		rooms[i] = r;
	}
	rooms[1]->Link(2, *rooms[3]);
	//http://www.cplusplus.com/doc/tutorial/files/    READING INPUT
	ifstream fileLoc("maze.txt"); //filelocation (c# streamwriter)
	string line, delimiter="/", token;
	size_t pos = 0;
	string NESW[4];

	int i=0, x=0;
	try
	{
		if (fileLoc.is_open())
		{
			while (getline (fileLoc,line))
			{
				while ((pos = line.find(delimiter)) != string::npos)
				{
					token = line.substr(0, pos);
					NESW[i] = token;
					//Cannot make links here otherwise all directions will be set to the same room
					line.erase(0, pos + delimiter.length());
					i++;
				}
				i = 0;
				//http://www.cplusplus.com/reference/string/stoi/     CONVERT FROM STRING TO INT
				if(NESW[0] != "-")
					rooms[x]->Link(1, *rooms[stoi(NESW[0])]);
				if (NESW[1] != "-")
					rooms[x]->Link(2, *rooms[stoi(NESW[1])]);
				if (NESW[2] != "-")
					rooms[x]->Link(3, *rooms[stoi(NESW[2])]);
				if (NESW[3] != "-")
					rooms[x]->Link(4, *rooms[stoi(NESW[3])]);
				x++;
				if (NESW[0] == "!")
					rooms[stoi(NESW[1])]->setWinningRoom();
			}
		}
		fileLoc.close();
	}
	catch (exception e)
	{
		cout << "An error has occured when trying to read the file." << endl;
	}
	m.setRoomList(rooms);
	m.Play();
}
void MazeController::RandomMaze(void)
{

}