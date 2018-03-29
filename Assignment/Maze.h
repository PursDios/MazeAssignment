#include "Room.h"
#include <vector>
#pragma once

using namespace std;
class Maze
{
private:
	vector<Room*> m_RoomList;
	Room* m_CurrentLocation;
	Room* m_Finish;
public:
	void setRoomList(vector<Room*> rooms);
	void setFinish(Room* room);
	void Play();
	vector<Room*> getRoomList();
	Room* getCurrentLocation();
	void setCurrentLocation(Room* room);
};