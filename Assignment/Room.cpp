#include "Room.h"
#include "random"
#include "fstream"
#include "string"
#include "iostream"

using namespace std;
Room::Room()
{
	generateName();
}
void Room::Link(int p_NESW, Room &p_room)
{
	switch (p_NESW)
	{
	case 1:
		m_North = &p_room;
		break;
	case 2:
		m_East = &p_room;
		break;
	case 3:
		m_South = &p_room;
		break;
	case 4:
		m_West = &p_room;
		break;
	default:
		break;
	}
}
string Room::getName()
{
	return m_roomName;
}
Room* Room::getNorth()
{
	return m_North;
}

Room*  Room::getEast()
{
	return m_East;
}

Room * Room::getSouth()
{
	return m_South;
}

Room * Room::getWest()
{
	return m_West;
}
///randomly generates a rooms name
void Room::generateName()
{
	ifstream fileLoc("roomnames.txt"); //filelocation (c# streamwriter)
	random_device rd; // seed
	mt19937 rng(rd()); // random-number engine
	uniform_int_distribution<int> ranNum(0, 54);
	string line;
	int random = ranNum(rng);
	//https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library

	if (fileLoc.is_open()) //if file can be opened
	{
		int num = 0; //line num
		while (getline(fileLoc, line))
		{
			if (num == random) //if the line number is the same as the randomly generated number
			{
				m_roomName = line;
				break;
			}
			num++;
		}
		fileLoc.close(); //close file.
	}
	//https://www.uow.edu.au/~lukes/TEXTBOOK/notes-cpp/io/readtextfile.html
}
///printed the rooms connected to the room
void Room::printConnectedRooms()
{
	if (m_North != nullptr)
		cout << "1)N: " << m_North->getName() << endl;
	else
		cout << "1)N: Nothing" << endl;

	if (m_East != nullptr)
		cout << "2)E: " << m_East->getName() << endl;
	else
		cout << "2)E: Nothing" << endl;

	if (m_South != nullptr)
		cout << "3)S: " << m_South->getName() << endl;
	else
		cout << "3)S: Nothing" << endl;

	if (m_West != nullptr)
		cout << "4)W: " << m_West->getName() << endl;
	else
		cout << "4)W: Nothing" << endl;
}
Room* SpecialRoom::getSpecial()
{
	return m_special;
}
void SpecialRoom::setSpecial(Room& p_room)
{
	m_special = &p_room;
}
void SpecialRoom::printConnectedRooms()
{
	Room::printConnectedRooms();
	if (m_special != nullptr)
		cout << "5)X: There seems to be something off about that wall..." << endl;
	else
		cout << "5)X: Nothing seems out of place in this room" << endl;
}
