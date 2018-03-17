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
	Room* m_Secret;
	bool winningRoom;
public:
	Room();
	void setWinningRoom();
	void Link(int p_NESW, Room &p_room);
	void generateName();
	string getName();
	bool getWinningRoom();
	Room& getNorth();
	Room& getEast();
	Room& getSouth();
	Room& getWest();
	Room& getSecret();
};
