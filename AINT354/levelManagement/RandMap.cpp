#include "RandMap.h"

RandMap::RandMap()
{
//	createFloor();
}

RandMap::RandMap(MapManager *mpmng)
{
	createFloor(mpmng);
}

RandMap::~RandMap()
{
}

void RandMap::update(float dt)
{
}

void RandMap::render(SDL_Renderer* renderer)
{

}

void RandMap::loadPlayer(CharacterType *pt)
{

}

Map* RandMap::getCurMap()
{
	return thisFloor[3][5];
}

void RandMap::createFloor(MapManager *mpmng)
{


	//max width/height
	int maxSize = 10;
	int numRooms =  8;

	for (int i = 0; i < maxSize; i++)
	{
		std::vector<Map*> tmpV;
		thisFloor.push_back(tmpV);
		for (int j = 0; j < maxSize; j++)
		{
			thisFloor[i].push_back(mpmng->getRandomMap());
		}
	}

	
	std::vector<Map*> currentRooms;

	Map *firstRoom = mpmng->getRandomMap();
	currentRooms.push_back(firstRoom);

	for (int i = 0; i < numRooms - 1; i++)
	{
		bool addedRoom = false;
		while (!addedRoom)
		{
			int rand = 0;
			if (currentRooms.size() < 1)
			{
				rand = Utility::randomInt(0, currentRooms.size() - 1);
			}
			

			int ranEdge = Utility::randomInt(0, 3);

			Vec2 thisRoomPos = currentRooms[rand]->getPos();

			Map *nMap = mpmng->getRandomMap();

			switch (ranEdge)
			{

			case 0:
				//north exit
				//up
				if (thisRoomPos.y > 0)
				{
					if (thisFloor[thisRoomPos.x][thisRoomPos.y - 1]->getAccess())
					{
						nMap->setPos(Vec2(thisRoomPos.x, thisRoomPos.y - 1));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						addedRoom = true;
					}
				}
			
				break;
			case 1:
				//east exit
				//right
				if ((thisRoomPos.x + 1) < maxSize)
				{
					if (thisFloor[thisRoomPos.x + 1][thisRoomPos.y]->getAccess())
					{
						nMap->setPos(Vec2(thisRoomPos.x + 1, thisRoomPos.y));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						addedRoom = true;
					}
				}
				
				break;

			case 2:
				//south exit
				//down
				if ((thisRoomPos.y + 1) < maxSize)
				{
					if (thisFloor[thisRoomPos.x][thisRoomPos.y + 1]->getAccess())
					{
						nMap->setPos(Vec2(thisRoomPos.x, thisRoomPos.y + 1));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						addedRoom = true;
					}
				}
				
				break;
			case 3:
				//west exit
				//left
				if (thisRoomPos.x > 0)
				{
					if (thisFloor[thisRoomPos.x - 1][thisRoomPos.y]->getAccess())
					{
						nMap->setPos(Vec2(thisRoomPos.x - 1, thisRoomPos.y - 1));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						addedRoom = true;
					}
				}
				break;
			default:
				break;
			}
		}
		

	}



}
