#include "Room.h"
#include <vector>
#pragma once

using namespace std;
class Maze
{
private:
	vector<Room*> m_RoomList;
	Room* m_Finish;
public:
	void setRoomList(vector<Room*> rooms);
	void setFinish(Room* room);
	void Play();
	vector<Room*> getRoomList() { return m_RoomList; };
};