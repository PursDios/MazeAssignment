#include "Room.h"
#include "random"
#include "fstream"
#include "string"

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
Room& Room::getNorth()
{
	return *m_North;
}

Room & Room::getEast()
{
	return *m_East;
}

Room & Room::getSouth()
{
	return *m_South;
}

Room & Room::getWest()
{
	return *m_West;
}
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

SpecialRoom::SpecialRoom() : Room()
{

}
