#include "RandMap.h"

RandMap::RandMap()
{
//	createFloor();
}

RandMap::RandMap(MapManager *mpmng)
{
	curRoomPos = Vec2(4, 4);
	//createFloor(mpmng);
}

RandMap::RandMap(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng)
{
	curRoomPos = Vec2(4, 4);
	createFloor(mpmng, ttmng, cmng);
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

MapRoom* RandMap::getCurMap()
{
	return thisFloor[curRoomPos.x][curRoomPos.y];
}

Vec2 RandMap::getCurRoomPos()
{
	return curRoomPos;
}

void RandMap::setCurRoomPos(Vec2 xy)
{
	curRoomPos = xy;

}

void RandMap::createFloor(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng)
{

	int test[5][5] = {
		{ 1,1,1,1,1 },
		{ 1,0,0,1,1 },
		{ 1,1,0,1,1 },
		{ 1,1,1,0,0 },
		{ 1,1,1,1,1 }
	};

	//max width/height
	int maxSize = 10;
	int numRooms = 8;


	std::vector<std::vector<int>> floorArray;

	for (int i = 0; i < maxSize; i++)
	{
		std::vector<MapRoom*> tmpV;
		thisFloor.push_back(tmpV);

		std::vector<int> tmpI;
		floorArray.push_back(tmpI);
		for (int j = 0; j < maxSize; j++) {
			//thisFloor[i].push_back(new MapRoom(mpmng, Vec2(i, j), test[i][j]));
			floorArray[i].push_back(0);
			thisFloor[i].push_back(new MapRoom());
		}
	}
	
	std::vector<MapRoom*> currentRooms;

	MapRoom *firstRoom = thisFloor[maxSize / 2][ maxSize / 2];
	firstRoom->createRoom(mpmng, ttmng, cmng, Vec2(maxSize / 2, maxSize / 2));
		
	//new MapRoom(mpmng, Vec2(maxSize / 2, maxSize / 2), 1);
	currentRooms.push_back(firstRoom);

	curRoomPos = Vec2(maxSize/2, maxSize/2);

	for (int i = 0; i < numRooms - 1; i++)
	{
		bool addedRoom = false;
		while (!addedRoom)
		{
			//find a random integer between 0 and the number of current rooms
			//this is the room we will add another room to
			int rand = 0;
			if (currentRooms.size() > 1)
			{
				rand = Utility::randomInt(0, currentRooms.size() - 1);
			}

			//find a random integer between - and 3 inclusive
			//this is the edge to add to (N,E,S,W)
			int ranEdge = Utility::randomInt(0, 3);

			Vec2 thisRoomPos = currentRooms[rand]->getPos();

			MapRoom *nMap;

			switch (ranEdge)
			{

			case 0:
				//north exit
				//up
				if (thisRoomPos.y > 0)
				{
					if (!thisFloor[thisRoomPos.x][thisRoomPos.y - 1]->getAccess())
					{
						nMap = thisFloor[thisRoomPos.x][thisRoomPos.y - 1];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x, thisRoomPos.y - 1));
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
					if (!thisFloor[thisRoomPos.x + 1][thisRoomPos.y]->getAccess())
					{
						nMap = thisFloor[thisRoomPos.x + 1][thisRoomPos.y];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x + 1, thisRoomPos.y));
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
					if (!thisFloor[thisRoomPos.x][thisRoomPos.y + 1]->getAccess())
					{
						nMap = thisFloor[thisRoomPos.x][thisRoomPos.y + 1];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x, thisRoomPos.y + 1));
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
					if (!thisFloor[thisRoomPos.x - 1][thisRoomPos.y]->getAccess())
					{
						nMap = thisFloor[thisRoomPos.x - 1][thisRoomPos.y];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x - 1, thisRoomPos.y));
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


std::vector<std::vector<MapRoom*>> RandMap::getMap()
{
	return thisFloor;
}