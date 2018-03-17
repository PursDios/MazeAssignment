#include "Player.h"
///Sets the room that the user is currently in.
void Player::setCurrentLocation(Room* room)
{
	m_CurrentLocation = room;
}
Room* Player::getCurrentLocation()
{
	return m_CurrentLocation;
}