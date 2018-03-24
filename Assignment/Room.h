#include "string"
#pragma once

using namespace std;
class Room
{
private:
	string m_roomName;
	Room* m_North;
	Room* m_East;
	Room* m_South;
	Room* m_West;
public:
	Room();
	void Link(int p_NESW, Room &p_room);
	void generateName();
	string getName();
	Room* getNorth();
	Room* getEast();
	Room* getSouth();
	Room* getWest();
	virtual void printConnectedRooms();
};
class SpecialRoom : public Room
{
private:
	Room * m_special;
public:
	Room * getSpecial();
	void setSpecial(Room&p_room);
	void printConnectedRooms();
};
