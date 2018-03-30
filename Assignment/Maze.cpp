#include "Maze.h"
#include "iostream"
#include "stdlib.h"
#include "MazeController.h"
#include "Room.h"

using namespace std;
///Sets the priate roomlist to the given roomlist.
void Maze::setRoomList(vector<Room*> p_roomlist)
{
	m_RoomList = p_roomlist;
}
Room* Maze::getCurrentLocation()
{
	return m_CurrentLocation;
}
void Maze::setCurrentLocation(Room* room)
{
	m_CurrentLocation = room;
}
void Maze::setFinish(Room* room)
{
	m_Finish = room;
}
///takes the current maze that's saved and uses it to play the game. 
void Maze::Play()
{
	vector<Room*> rooms = m_RoomList;
	setCurrentLocation(rooms[0]);
	bool finished = false, win = false;
	int choice;
	system("cls");

	//loops while the maze is unfinished (until you get to the end or the player chooses to quit
	while (!finished)
	{
		//if the players current location is not the winning room.
		if (getCurrentLocation() != m_Finish)
		{
			cout << "You are currently in the: " << getCurrentLocation()->getName() << endl;
			//Prints the locations and directions of all the rooms that are connected to the current room.
			getCurrentLocation()->printConnectedRooms();
			cout << "88)Help\n99)Quit" << endl;
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//will move the player based on where the user has selected.
			switch (choice)
			{
			case 1:
				if (getCurrentLocation()->getNorth() != NULL)
				{
					setCurrentLocation(getCurrentLocation()->getNorth());
					cout << "You walk north" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;

				break;
			case 2:
				if (getCurrentLocation()->getEast() != NULL)
				{
					setCurrentLocation(getCurrentLocation()->getEast());
					cout << "You walk east" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;

				break;
			case 3:
				if (getCurrentLocation()->getSouth() != NULL)
				{
					setCurrentLocation(getCurrentLocation()->getSouth());
					cout << "You walk south" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;

				break;
			case 4:
				if (getCurrentLocation()->getWest() != NULL)
				{
					setCurrentLocation(getCurrentLocation()->getWest());
					cout << "You walk West" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;

				break;
			case 5:
				if (typeid(*getCurrentLocation()) == typeid(SpecialRoom))
				{
					cout << "You find a secret room" << endl;
					SpecialRoom* sr = dynamic_cast<SpecialRoom*>(getCurrentLocation());
					setCurrentLocation(sr->getSpecial());
				}
				else
					cout << "Invalid Response" << endl;
				break;
			case 88:
				cout << "You are in a maze, your job is to try and escape the maze. \nPress a number to select which direction you would like to travel in e.g. 1) is north, 3) is south etc.\nWhen you reach the end you will be notified and will be returned to the main menu." << endl;
				break;
			case 99:
				finished = true;
				break;
			default:
				cout << "Invalid Response" << endl;
				break;
			}
			system("pause");
			system("CLS");
		}
		else
		{
			finished = true;

			win = true;
		}

	}
	if (win)
		cout << "You escaped the maze" << endl;
	else
		cout << "You died in the maze" << endl;

	cout << "Press any key to continue..." << endl;
}

vector<Room*> Maze::getRoomList()
{
	return m_RoomList;
}
