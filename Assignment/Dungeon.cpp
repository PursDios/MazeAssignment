#include "Dungeon.h"

Dungeon::Dungeon()
{

}
void Dungeon::Populate()
{
	for (int i = 0; i < 14; i++)
	{
		if (i == 2)
		{
			SpecialRoom r;
			roomList.push_back(&r);
		}
		else
			roomList.push_back(new Room());
	}
}