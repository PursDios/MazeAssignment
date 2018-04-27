#pragma once
#include "Room.h"
#include "vector"
class MazeController
{
public:
	MazeController();
	void MainMenu();
	void StaticMaze();
	void FileMaze();
	void RandomMaze();
	void assignRandomConnections(int* connections, Room* r, vector<Room*> rooms, int* totalRooms);
};