#include "stdlib.h"
#include "iostream"
#include "MazeController.h"
#include "Dungeon.h"

using namespace std;

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
	Dungeon d;
	
}
void MazeController::FileMaze(void)
{

}
void MazeController::RandomMaze(void)
{

}