#include "Maze.h"
#include "iostream"
#include "stdlib.h"
#include "MazeController.h"
#include "Player.h"
#include "Room.h"

using namespace std;

Maze::Maze()
{

}
void Maze::Populate()
{
	m_RoomList.resize(14);
	for (int i = 0; i < 14; i++)
	{
		Room* r = new Room();
		m_RoomList[i] = r;
	}
}
void Maze::setRoomList(vector<Room*> p_roomlist)
{
	m_RoomList = p_roomlist;
}
void Maze::Play()
{
	vector<Room*> rooms = m_RoomList;
	Player p;
	p.setCurrentLocation(rooms[0]);
	bool finished = false;
	int choice;

	while (!finished)
	{
		system("CLS");
		if (p.getCurrentLocation() != rooms[13])
		{
			cout << "You are Currently at the: " << p.getCurrentLocation()->getName() << "\n" << endl;
			cout << "Where would you like to go?" << endl;

			if (&p.getCurrentLocation()->getNorth() != NULL)
			{
				cout << "1)North to the: " << p.getCurrentLocation()->getNorth().getName() << endl;
			}
			else
			{
				cout << "1)There is Nothing to the North" << endl;
			}
			if (&p.getCurrentLocation()->getEast() != NULL)
			{
				cout << "2)East to the: " << p.getCurrentLocation()->getEast().getName() << endl;
			}
			else
			{
				cout << "1)There is Nothing to the East" << endl;
			}
			if (&p.getCurrentLocation()->getSouth() != NULL)
			{
				cout << "3)South to the: " << p.getCurrentLocation()->getSouth().getName() << endl;
			}
			else
			{
				cout << "1)There is Nothing to the South" << endl;
			}
			if (&p.getCurrentLocation()->getWest() != NULL)
			{
				cout << "4)West to the: " << p.getCurrentLocation()->getWest().getName() << endl;
			}
			else
			{
				cout << "1)There is Nothing to the West" << endl;
			}
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (choice)
			{
			case 1:
				p.setCurrentLocation(&p.getCurrentLocation()->getNorth());
				break;
			case 2:
				p.setCurrentLocation(&p.getCurrentLocation()->getEast());
				break;
			case 3:
				p.setCurrentLocation(&p.getCurrentLocation()->getSouth());
				break;
			case 4:
				p.setCurrentLocation(&p.getCurrentLocation()->getWest());
				break;
			default:
				break;
			}
		}
		else
			finished = true;
	}
}