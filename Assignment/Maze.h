#include "Room.h"
#include <vector>
#pragma once

using namespace std;
class Maze
{
private:
	vector<Room*> m_RoomList;
public:
	void setRoomList(vector<Room*> rooms);
	void Play();
	vector<Room*> getRoomList() { return m_RoomList; };
};