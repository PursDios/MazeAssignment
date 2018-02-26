#include "Room.h"
#pragma once
class Player
{
private:
	Room* m_CurrentLocation;
public:
	Room * getCurrentLocation() { return m_CurrentLocation; }
	void setCurrentLocation(Room* room);
};
