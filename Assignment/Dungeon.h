#include "Room.h"
#include <vector>
#pragma once

using namespace std;
class Dungeon
{
private:
	vector<Room*> roomList;
public:
	Dungeon();
	vector<Room*> getRoomList() { return roomList; }
};