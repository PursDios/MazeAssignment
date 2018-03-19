#include "Maze.h"
#include "iostream"
#include "stdlib.h"
#include "MazeController.h"
#include "Player.h"
#include "Room.h"

using namespace std;
///Maze Constructor
Maze::Maze()
{

}
///Sets the priate roomlist to the given roomlist.
void Maze::setRoomList(vector<Room*> p_roomlist)
{
	m_RoomList = p_roomlist;
}
///takes the current maze that's saved and uses it to play the game. 
void Maze::Play()
{
	vector<Room*> rooms = m_RoomList;
	Player p;
	p.setCurrentLocation(rooms[0]);
	bool finished = false, win = false;
	int choice;
	system("cls");

	system("pause");
	while (!finished)
	{
		if (p.getCurrentLocation() != rooms[13])
		{
			/*cout << "You are Currently at the: " << p.getCurrentLocation()->getName() << "\n" << endl;
			cout << "Where would you like to go?" << endl;

			if (p.getCurrentLocation()->getNorth() != NULL)
			{
				cout << "1)North to the: " << p.getCurrentLocation()->getNorth()->getName() << endl;
			}
			else
			{
				cout << "1)There is Nothing to the North" << endl;
			}
			if (p.getCurrentLocation()->getEast() != NULL)
			{
				cout << "2)East to the: " << p.getCurrentLocation()->getEast()->getName() << endl;
			}
			else
			{
				cout << "2)There is Nothing to the East" << endl;
			}
			if (p.getCurrentLocation()->getSouth() != NULL)
			{
				cout << "3)South to the: " << p.getCurrentLocation()->getSouth()->getName() << endl;
			}
			else
			{
				cout << "3)There is Nothing to the South" << endl;
			}
			if (p.getCurrentLocation()->getWest() != NULL)
			{
				cout << "4)West to the: " << p.getCurrentLocation()->getWest()->getName() << endl;
			}
			else
			{
				cout << "4)There is Nothing to the West" << endl;
			}
			cout << "5)Search for secret enterances" << endl;
			*/
			p.getCurrentLocation()->printConnectedRooms();
			cout << "99)Quit" << endl;
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (choice)
			{
			case 1:
				if (p.getCurrentLocation()->getNorth() != NULL)
				{
					p.setCurrentLocation(p.getCurrentLocation()->getNorth());
					cout << "You walk north" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;

				break;
			case 2:
				if (p.getCurrentLocation()->getEast() != NULL)
				{
					p.setCurrentLocation(p.getCurrentLocation()->getEast());
					cout << "You walk east" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;
				
				break;
			case 3:
				if (p.getCurrentLocation()->getSouth() != NULL)
				{
					p.setCurrentLocation(p.getCurrentLocation()->getSouth());
					cout << "You walk south" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;
				
				break;
			case 4:
				if (p.getCurrentLocation()->getWest() != NULL)
				{
					p.setCurrentLocation(p.getCurrentLocation()->getWest());
					cout << "You walk West" << endl;
				}
				else
					cout << "You walk into the wall. Does that make you feel good about yourself?" << endl;
				
				break;
			case 5:
				if (typeid(*p.getCurrentLocation()) == typeid(SpecialRoom))
				{
					cout << "You find a secret room" << endl;
					SpecialRoom* sr = dynamic_cast<SpecialRoom*>(p.getCurrentLocation());
					p.setCurrentLocation(sr->getSpecial());
				}
				else
					cout << "Invalid Response" << endl;
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
	system("pause");
}