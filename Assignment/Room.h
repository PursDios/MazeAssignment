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
	void link();
	string getString() { return m_roomName; }
	Room getNorth() { return *m_North; }
	Room getEast() { return *m_East; }
	Room getSouth() { return *m_South; }
	Room getWest() { return *m_West; }
};

class SpecialRoom : Room
{
private:
	Room* Special;
public:
	Room getSpecial() { return *Special; }
};
