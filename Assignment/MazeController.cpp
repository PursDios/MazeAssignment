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
	rooms[0]->Link(2, *rooms[2]);	//A TO C
	rooms[0]->Link(4, *rooms[5]);	//A TO F
	rooms[1]->Link(3, *rooms[2]);	//B TO C
	rooms[2]->Link(1, *rooms[1]);	//C TO B
	rooms[2]->Link(2, *rooms[3]);	//C TO D
	rooms[2]->Link(3, *rooms[7]);	//C TO H
	rooms[2]->Link(4, *rooms[0]);	//C TO A
	rooms[3]->Link(2, *rooms[4]);	//D TO E
	rooms[3]->Link(4, *rooms[2]);	//D TO C
	rooms[4]->Link(4, *rooms[3]);	//E TO D
	rooms[5]->Link(1, *rooms[0]);	//F TO A
	rooms[5]->Link(3, *rooms[10]);	//F TO K
	rooms[5]->Link(4, *rooms[9]);	//F TO J
	rooms[6]->Link(1, *rooms[2]);	//G to C
	rooms[7]->Link(1, *rooms[2]);	//H TO C
	rooms[7]->Link(2, *rooms[8]);	//H TO I
	rooms[7]->Link(3, *rooms[12]);	//H TO M
	rooms[7]->Link(4, *rooms[11]);	//H TO L
	rooms[8]->Link(4, *rooms[7]);	//I TO H
	rooms[9]->Link(1, *rooms[5]);	//J TO F
	rooms[10]->Link(1, *rooms[5]);	//K TO F
	rooms[10]->Link(2, *rooms[11]); //K TO L
	rooms[11]->Link(1, *rooms[7]);	//L TO H
	rooms[11]->Link(4, *rooms[10]);	//L TO K
	rooms[12]->Link(1, *rooms[7]);	//M TO H
	rooms[12]->Link(3, *rooms[13]); //M TO N
		
	m.setRoomList(rooms);
	m.setFinish(rooms[13]);
	m.Play();
}
///reads in a maze from a file
void MazeController::FileMaze(void)
{
	//http://www.cplusplus.com/doc/tutorial/files/    READING INPUT
	//filelocation (c# streamwriter)
	ifstream fileLoc("maze.txt");
	//the delimiter the program will search for.
	string line, delimiter = "/", token;
	size_t pos = 0;
	string NESW[4];

	vector<Room*> rooms;
	//counts the number of lines in a file
	fileLoc.open("maze.txt");
	//counts the number of \n characters then adds one for the first line
	int size = ((int)count(istreambuf_iterator<char>(fileLoc), istreambuf_iterator<char>(), '\n') + 1);
	fileLoc.close();
	rooms.resize(size);

	//rooms.resize(25);
	for (int i = 0; i < size; i++)
	{
		Room* r = new Room();
		rooms[i] = r;
	}

	int i = 0, x = 0;
	try
	{

		fileLoc.open("maze.txt");
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
	//seed
	random_device rd;		
	//random-number engine
	mt19937 rng(rd());		
	//Used to generate the totalRooms.
	uniform_int_distribution<int> Limit(4, 10);		
	//used to generate the number of connections a room can have
	uniform_int_distribution<int> otherRan(1, 4);				
	bool valid = false;			
	do
	{
		
		int totalRooms = Limit(rng);
		//set the vector the same size as the randomly generated number of total rooms.
		rooms.resize(totalRooms); 
		//populate the vector.
		for (int i = 0; i < totalRooms; i++)
		{
			rooms[i] = new Room();
		}
		int i = 0;
		//for each room make connections
		for (Room* r : rooms)
		{
			int connections = otherRan(rng);
			assignRandomConnections(&connections, r, rooms, &totalRooms);
			i++;
		}
		//sets the vector to the room vector we just created.
		m.setRoomList(rooms);
		//sets the end room
		m.setFinish(rooms[totalRooms - 1]);
		if (rooms[totalRooms - 1]->getNorth() != nullptr || rooms[totalRooms - 1]->getEast() != nullptr || rooms[totalRooms - 1]->getSouth() != nullptr || rooms[totalRooms - 1]->getWest() != nullptr)
		{
			valid = true;
			//calls the play method to start the maze.
			m.Play();
		}
	} while (!valid);
}
///Used to make the connections for each room dependant on the number of connections (Used for randomMaze)
void MazeController::assignRandomConnections(int* connections, Room* r, vector<Room*> rooms, int* totalRooms)
{
	//seed
	random_device rd;											
	mt19937 rng(rd());
	//used to generate a room that can be connected to.
	uniform_int_distribution<int> linkNum(1, *totalRooms);		
	int i = 0, link = -1;
	while (*connections != i)
	{
		while (link <= i)
		{
			//randomly generate a room to connect to
			link = linkNum(rng); 
		}
		--link;
		//if the room is not assigned to and the opposite room on the room it's trying to connect to is not taken 
		if (r->getNorth() == nullptr && rooms[link]->getSouth() == nullptr)
		{
			if (r->getEast() != rooms[link] || r->getSouth() != rooms[link] || r->getWest() != rooms[link])
			{
				r->Link(1, *rooms[link]);
				rooms[link]->Link(3, *r);
			}
		}
		else if (r->getEast() == nullptr && rooms[link]->getWest() == nullptr)
		{
			if (r->getNorth() != rooms[link] || r->getSouth() != rooms[link] || r->getWest() != rooms[link])
			{
				r->Link(2, *rooms[link]);
				rooms[link]->Link(4, *r);
			}
		}
		else if (r->getSouth() == nullptr && rooms[link]->getSouth() == nullptr)
		{
			if (r->getEast() != rooms[link] || r->getNorth() != rooms[link] || r->getWest() != rooms[link])
			{
				r->Link(3, *rooms[link]);
				rooms[link]->Link(1, *r);
			}
		}
		else if (r->getWest() == nullptr && rooms[link]->getWest() == nullptr)
		{
			if (r->getEast() != rooms[link] || r->getSouth() != rooms[link] || r->getNorth() != rooms[link])
			{
				r->Link(4, *rooms[link]);
				rooms[link]->Link(2, *r);
			}
		}
		i++;
	}
}