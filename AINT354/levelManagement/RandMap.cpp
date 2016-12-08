#include "RandMap.h"
#include "../Utility.h"

RandMap::RandMap()
{
	createEmptyFloor();
	curRoomPos = Vec2(0, 0);
}

RandMap::RandMap(MapManager *mpmng)
{
	curRoomPos = Vec2(4, 4);
	//createFloor(mpmng);
}

RandMap::RandMap(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng)
{
	
	int a = Utility::randomInt(1, 9);
	int b = Utility::randomInt(1, 9);
	
	curRoomPos = Vec2(maxSize/2, maxSize / 2);
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


	

	MapRoom *firstRoom = thisFloor[curRoomPos.x][curRoomPos.y];
	firstRoom->createRoom(mpmng, ttmng, cmng, Vec2(curRoomPos.x, curRoomPos.y));
	firstRoom->setAccess(true);

	currentRooms.push_back(firstRoom);

	//get number of rooms that are allowed to be next to more than one when built
	int newR = numRooms - std::abs((numRooms - 1) / 50);
	int c = 0;
	
	for (int i = 0; i < numRooms-1; i++)
	{
		if (c < newR)
		{
			addRooms(mpmng, ttmng, cmng, 1);
		}
		else {
			addRooms(mpmng, ttmng, cmng, 0);
		}
		c++;
	}

	int d = c;

	//find furthest room from origin

	//origin is the room you spawn in
	Vec2 origin = curRoomPos;

	//vector to hold the position of the furthest away room
	//this will be used to make an exit room
	Vec2 largest;

	int dist = 0;

	for (int i = 0; i < roomPositions.size(); i++)
	{
		int nx = std::abs(origin.x - roomPositions[i].x);
		int ny = std::abs(origin.y - roomPositions[i].y);

		int nxy = nx + ny;
		if (dist < nxy)
		{
			dist = nxy;
			largest = roomPositions[i];
		}
	}

	//create special rooms

	//create end room
/*
	bool addedEndRoom = false;
	while (!addedEndRoom)
	{
		addedEndRoom = addToSingleRoom(mpmng, ttmng, cmng, largest, 1);
	}*/

}


std::vector<std::vector<MapRoom*>> RandMap::getMap()
{
	return thisFloor;
}

void RandMap::createEmptyFloor()
{
	int maxSize = 10;

	for (int i = 0; i < maxSize; i++)
	{
		std::vector<MapRoom*> tmpV;
		thisFloor.push_back(tmpV);
		for (int j = 0; j < maxSize; j++) {
			thisFloor[i].push_back(new MapRoom());
		}
	}
}


void RandMap::addRooms(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, int type)
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

		//vector to hold the position of the room to add another room to
		Vec2 roomToAddTo = currentRooms[rand]->getPos();

		addedRoom = addToSingleRoom(mpmng, ttmng, cmng, roomToAddTo, type);

		
	}
}



bool RandMap::addToSingleRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, Vec2 thisRoomPos, int type)
{
	
	MapRoom *nMap;

	//find a random integer between - and 3 inclusive
	//this is the edge to add to (N,E,S,W)
	int ranEdge = Utility::randomInt(0, 3);

	switch (ranEdge)
	{

	case 0:
		//north exit
		//up
		//make sure not to create a room above the map
		if (thisRoomPos.y > 0)
		{
			if (!thisFloor[thisRoomPos.x][thisRoomPos.y - 1]->getAccess())
			{
				if (type == 0)
				{
					nMap = thisFloor[thisRoomPos.x][thisRoomPos.y - 1];
					nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x, thisRoomPos.y - 1));
					nMap->setAccess(true);
					currentRooms.push_back(nMap);

					Vec2 rp = Vec2(thisRoomPos.x, thisRoomPos.y - 1);
					roomPositions.push_back(rp);
				}
				else if (type == 1)
				{
					Vec2 roomToCheck = Vec2(thisRoomPos.x, thisRoomPos.y - 1);

					int roomConnections = checkRoomConnections(roomToCheck);

					if (roomConnections == 1)
					{
						nMap = thisFloor[roomToCheck.x][roomToCheck.y];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(roomToCheck.x, roomToCheck.y));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						Vec2 rp = Vec2(roomToCheck.x, roomToCheck.y);
						roomPositions.push_back(rp);
					}
					else {
						return false;
					}
				}
				return true;
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
				if (type == 0)
				{
					nMap = thisFloor[thisRoomPos.x + 1][thisRoomPos.y];
					nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x + 1, thisRoomPos.y));
					nMap->setAccess(true);
					currentRooms.push_back(nMap);


					Vec2 rp = Vec2(thisRoomPos.x + 1, thisRoomPos.y);
					roomPositions.push_back(rp);
				}
				else if (type == 1)
				{
					Vec2 roomToCheck = Vec2(thisRoomPos.x + 1, thisRoomPos.y);

					int roomConnections = checkRoomConnections(roomToCheck);

					if (roomConnections == 1)
					{
						nMap = thisFloor[roomToCheck.x][roomToCheck.y];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(roomToCheck.x, roomToCheck.y));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						Vec2 rp = Vec2(roomToCheck.x, roomToCheck.y);
						roomPositions.push_back(rp);
					}
					else {
						return false;
					}
				}
				return true;
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
				if (type == 0)
				{
					nMap = thisFloor[thisRoomPos.x][thisRoomPos.y + 1];
					nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x, thisRoomPos.y + 1));
					nMap->setAccess(true);
					currentRooms.push_back(nMap);
					Vec2 rp = Vec2(thisRoomPos.x, thisRoomPos.y + 1);
					roomPositions.push_back(rp);
				}
				else if (type == 1)
				{
					Vec2 roomToCheck = Vec2(thisRoomPos.x, thisRoomPos.y + 1);

					int roomConnections = checkRoomConnections(roomToCheck);

					if (roomConnections == 1)
					{
						nMap = thisFloor[roomToCheck.x][roomToCheck.y];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(roomToCheck.x, roomToCheck.y));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						Vec2 rp = Vec2(roomToCheck.x, roomToCheck.y);
						roomPositions.push_back(rp);
					}
					else {
						return false;
					}
				}
				

				return true;
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

				if (type == 0)
				{
					nMap = thisFloor[thisRoomPos.x - 1][thisRoomPos.y];
					nMap->createRoom(mpmng, ttmng, cmng, Vec2(thisRoomPos.x - 1, thisRoomPos.y));
					nMap->setAccess(true);
					currentRooms.push_back(nMap);

					Vec2 rp = Vec2(thisRoomPos.x - 1, thisRoomPos.y);
					roomPositions.push_back(rp);

					
				}
				else if (type == 1)
				{
					Vec2 roomToCheck = Vec2(thisRoomPos.x - 1, thisRoomPos.y);

					int roomConnections = checkRoomConnections(roomToCheck);

					if (roomConnections == 1)
					{
						nMap = thisFloor[roomToCheck.x][roomToCheck.y];
						nMap->createRoom(mpmng, ttmng, cmng, Vec2(roomToCheck.x, roomToCheck.y));
						nMap->setAccess(true);
						currentRooms.push_back(nMap);
						Vec2 rp = Vec2(roomToCheck.x, roomToCheck.y);
						roomPositions.push_back(rp);
					}
					else {
						return false;
					}
				}
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

int RandMap::checkRoomConnections(Vec2 roomPos)
{
	int roomsConnected = 0;

	if (roomPos.y > 0)
	{
		if (thisFloor[roomPos.x][roomPos.y - 1]->getAccess())
		{
			roomsConnected += 1;
		}
	}

	if ((roomPos.y + 1) < maxSize)
	{
		if (thisFloor[roomPos.x][roomPos.y + 1]->getAccess())
		{
			roomsConnected += 1;
		}
	}

	if (roomPos.x > 0)
	{
		if (thisFloor[roomPos.x - 1][roomPos.y]->getAccess())
		{
			roomsConnected += 1;
		}
	}

	if ((roomPos.x + 1) < maxSize)
	{
		if (thisFloor[roomPos.x + 1][roomPos.y]->getAccess())
		{
			roomsConnected += 1;
		}
	}
	return roomsConnected;
}