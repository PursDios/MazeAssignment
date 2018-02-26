#include "stdlib.h"
#include "iostream"
#include "MazeController.h"
#include "Dungeon.h"
#include "string"
#include "vector"

using namespace std;
Dungeon d;
MazeController::MazeController(void)
{
	MainMenu();
}
void MazeController::MainMenu(void)
{
	int choice;
	bool valid = false;
	do
	{
		system("CLS");
		cout << "Please select which maze you would like to do:" << endl;
		cout << "1)Static Maze\n2)File Maze\n3)Random Maze" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			StaticMaze();
			valid = true;
			break;
		case 2:
			FileMaze();
			valid = true;
			break;
		case 3:
			RandomMaze();
			valid = true;
			break;
		default:
			cout << "Invalid Selection please try again" << endl;
			system("PAUSE");
			break;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (!valid);
}
void MazeController::StaticMaze(void)
{
	d.Populate();
	vector<Room*> rooms = d.getRoomList();
	Player p;

	rooms[0]->Link(2, *rooms[2]); //A TO C
	rooms[2]->Link(1, *rooms[1]); //C TO B
	rooms[2]->Link(2, *rooms[3]); //C TO D
	rooms[2]->Link(3, *rooms[7]); //C TO H
	rooms[2]->Link(4, *rooms[0]); //C TO A
	rooms[3]->Link(2, *rooms[4]); //D TO E
	rooms[7]->Link(2, *rooms[8]); //H TO I
	rooms[7]->Link(3, *rooms[12]); //H TO M
	rooms[7]->Link(4, *rooms[11]); //H TO L
	rooms[7]->Link(1, *rooms[2]); //H TO C
	rooms[11]->Link(1, *rooms[7]); //L TO H
	rooms[11]->Link(4, *rooms[10]); //L TO K
	rooms[10]->Link(2, *rooms[11]); //K TO L
	rooms[10]->Link(1, *rooms[5]); //K TO F
	rooms[5]->Link(3, *rooms[10]); //F TO K
	rooms[5]->Link(4, *rooms[9]); //F TO J
	rooms[5]->Link(1, *rooms[0]); //F TO A
	rooms[12]->Link(3, *rooms[13]); //M TO N
	rooms[12]->Link(1, *rooms[7]); //M TO H
}
void MazeController::FileMaze(void)
{

}
void MazeController::RandomMaze(void)
{

}