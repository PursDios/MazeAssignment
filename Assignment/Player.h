#include "Room.h"
#pragma once
class Player
{
private:
	Room * m_CurrentLocation;
public:
	Room * getCurrentLocation();
	void setCurrentLocation(Room* room);
};
