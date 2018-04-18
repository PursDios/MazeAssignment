#include "stdlib.h"
#include "iostream"
#include "MazeController.h"
#include "Maze.h"
#include "string"
#include "vector"
#include "fstream"
#include <random>

using namespace std;
Maze m;
MazeController::MazeController(void)
{
	//calls the main menu
	MainMenu();
}
///the main menu for the program.
void MazeController::MainMenu(void)
{
	int choice;
	bool exit = false;
	do
	{
		system("CLS");
		cout << "Please select which maze you would like to do:" << endl;
		cout << "1)Static Maze\n2)File Maze\n3)Random Maze\n99)exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			StaticMaze();
			break;
		case 2:
			FileMaze();
			break;
		case 3:
			RandomMaze();
			break;
		case 99:
			exit = true;
			break;
		default:
			cout << "Invalid Selection please try again" << endl;
			system("PAUSE");
			break;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (!exit);
}
///a statically designed maze.
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
	//Creating a special room
	SpecialRoom* r = new SpecialRoom();
	//setting the special room using the unique method unique to the subclass
	r->setSpecial(*rooms[6]);
	//assigning it to element 2 in the vector
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
	rooms[6]->Link(1, *rooms[2]); //G to C
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

	m.setRoomList(rooms);
	m.setFinish(rooms[13]);
	m.Play();
}
///reads in a maze from a file
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
	string line, delimiter = "/", token; //the delimiter the program will search for.
	size_t pos = 0;
	string NESW[4];

	int i = 0, x = 0;
	try
	{
		//try and open the file.
		if (fileLoc.is_open())
		{
			//while there are still lines to get.
			while (getline(fileLoc, line))
			{
				//for each delimiter on that line.
				while ((pos = line.find(delimiter)) != string::npos)
				{
					token = line.substr(0, pos);
					//store information before the next delimiter in NESW[i]
					NESW[i] = token;
					//Cannot make links here otherwise all directions will be set to the same room
					line.erase(0, pos + delimiter.length());
					i++;
				}
				i = 0;
				//http://www.cplusplus.com/reference/string/stoi/     CONVERT FROM STRING TO INT
				//if the NESW value is not a dash and is not an exclimation mark then create a link.
				if (NESW[0] != "-" && NESW[0] != "!")
					rooms[x]->Link(1, *rooms[stoi(NESW[0])]);
				if (NESW[1] != "-" && NESW[0] != "!")
					rooms[x]->Link(2, *rooms[stoi(NESW[1])]);
				if (NESW[2] != "-" && NESW[0] != "!")
					rooms[x]->Link(3, *rooms[stoi(NESW[2])]);
				if (NESW[3] != "-" && NESW[0] != "!")
					rooms[x]->Link(4, *rooms[stoi(NESW[3])]);
				x++;
				if (NESW[0] == "!")
					m.setFinish(rooms[stoi(NESW[1])]);
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
///randomly generates the maze.
void MazeController::RandomMaze(void)
{
	vector<Room*> rooms;
	random_device rd; // seed
	mt19937 rng(rd()); // random-number engine
	uniform_int_distribution<int> Limit(1, 50); //Used to generate the totalRooms.
	uniform_int_distribution<int> otherRan(1, 4);
	int totalRooms = Limit(rng);
	uniform_int_distribution<int> linkNum(1, totalRooms);
	rooms.resize(totalRooms);
	for (int i = 0; i < totalRooms; i++)
	{
		rooms[i] = new Room();
	}
	int i = 0;
	for (Room* r : rooms)
	{
		int j = 0, connections = otherRan(rng), link = -1;
		switch (connections)
		{
		case 1:
			link = linkNum(rng);
			while (link < i || link - 1 == i)
			{
				link = linkNum(rng);
			}
			if (r->getNorth() == nullptr && rooms[link - 1]->getSouth() == nullptr)
			{
				r->Link(1, *rooms[link - 1]);
				rooms[link - 1]->Link(3, *r);
			}
			else if (r->getEast() == nullptr && rooms[link - 1]->getWest() == nullptr)
			{
				r->Link(2, *rooms[link - 1]);
				rooms[link - 1]->Link(4, *r);
			}
			else if (r->getSouth() == nullptr && rooms[link - 1]->getSouth() == nullptr)
			{
				r->Link(3, *rooms[link - 1]);
				rooms[link - 1]->Link(1, *r);
			}
			else if (r->getWest() == nullptr && rooms[link - 1]->getWest() == nullptr)
			{
				r->Link(4, *rooms[link - 1]);
				rooms[link - 1]->Link(2, *r);
			}
			break;
		case 2:
			while (j != 2)
			{
				link = linkNum(rng);
				while (link < i || link - 1 == i)
				{
					link = linkNum(rng);
				}
				if (r->getNorth() == nullptr && rooms[link -1]->getSouth() == nullptr)
				{
					r->Link(1, *rooms[link - 1]);
					rooms[link - 1]->Link(3, *r);
				}
				else if (r->getEast() == nullptr && rooms[link -1]->getWest() == nullptr)
				{
					r->Link(2, *rooms[link - 1]);
					rooms[link - 1]->Link(4, *r);
				}
				else if (r->getSouth() == nullptr && rooms[link-1]->getSouth() == nullptr)
				{
					r->Link(3, *rooms[link - 1]);
					rooms[link - 1]->Link(1, *r);
				}
				else if (r->getWest() == nullptr && rooms[link-1]->getWest() == nullptr)
				{
					r->Link(4, *rooms[link - 1]);
					rooms[link - 1]->Link(2, *r);
				}
				j++;
			}
			break;
		case 3:
			while (j != 3)
			{
				link = linkNum(rng);
				while (link < i || link - 1 == i)
				{
					link = linkNum(rng);
				}
				if (r->getNorth() == nullptr && rooms[link - 1]->getSouth() == nullptr)
				{
					r->Link(1, *rooms[link - 1]);
					rooms[link - 1]->Link(3, *r);
				}
				else if (r->getEast() == nullptr && rooms[link - 1]->getWest() == nullptr)
				{
					r->Link(2, *rooms[link - 1]);
					rooms[link - 1]->Link(4, *r);
				}
				else if (r->getSouth() == nullptr && rooms[link - 1]->getSouth() == nullptr)
				{
					r->Link(3, *rooms[link - 1]);
					rooms[link - 1]->Link(1, *r);
				}
				else if (r->getWest() == nullptr && rooms[link - 1]->getWest() == nullptr)
				{
					r->Link(4, *rooms[link - 1]);
					rooms[link - 1]->Link(2, *r);
				}
				j++;
			}
			break;
		case 4:
			while (j != 4)
			{
				link = linkNum(rng);
				while (link < i || link - 1 == i)
				{
					link = linkNum(rng);
				}
				if (r->getNorth() == nullptr && rooms[link - 1]->getSouth() == nullptr)
				{
					r->Link(1, *rooms[link - 1]);
					rooms[link - 1]->Link(3, *r);
				}
				else if (r->getEast() == nullptr && rooms[link - 1]->getWest() == nullptr)
				{
					r->Link(2, *rooms[link - 1]);
					rooms[link - 1]->Link(4, *r);
				}
				else if (r->getSouth() == nullptr && rooms[link - 1]->getSouth() == nullptr)
				{
					r->Link(3, *rooms[link - 1]);
					rooms[link - 1]->Link(1, *r);
				}
				else if (r->getWest() == nullptr && rooms[link - 1]->getWest() == nullptr)
				{
					r->Link(4, *rooms[link - 1]);
					rooms[link - 1]->Link(2, *r);
				}
				j++;
			}
			break;

		default:
			cout << "You did not randomly generate a number between 1 and 4" << endl;
			break;
		}
		i++;
	}
	m.setRoomList(rooms);
	m.setFinish(rooms[totalRooms -1]);
	m.Play();
}