#include "MapRoom.h"


MapRoom::MapRoom()
{

}

MapRoom::MapRoom(MapManager *mpmng, Vec2 pos, int e)
{
	RoomTemplate *rt = mpmng->getRandomMap();
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;

	exists = e;
}

MapRoom::~MapRoom()
{
	
}

void MapRoom::createRoom(MapManager *mpmng, Vec2 pos)
{
	RoomTemplate *rt = mpmng->getRandomMap();
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;

	exists = true;
}

void MapRoom::update(float dt)
{
}

void MapRoom::render(SDL_Renderer* renderer)
{


	//Load in all the map data
	//Loop through all of the Layer ID's
	for (unsigned int i = 0; i < layerIDs.size(); i++)
	{
		//Loop through all the map tiles
		for (unsigned int y = 0; y < roomTiles[layerIDs[i]].size(); y++)
		{
			for (unsigned int x = 0; x < roomTiles[layerIDs[i]][y].size(); x++)
			{
				roomTiles[layerIDs[i]][y][x]->render(renderer);
			}
		}
	}

	//load in the creature data

	for (unsigned int i = 0; i < roomCreatures.size(); i++)
	{
		roomCreatures[i]->render(renderer);
	}


	//load in the player data

	if (playerLoaded)
	{
		player->render(renderer);
	}
}

void MapRoom::loadPlayer(CharacterType *pt)
{
	player = new Character(pt->getTexture(), Vec2(25,25), pt);

	playerLoaded = true;
}


void MapRoom::setPos(Vec2 pos)
{

	roomPos = pos;
}

Vec2 MapRoom::getPos()
{
	return roomPos;
}

void MapRoom::setAccess(bool b)
{
	access = true;
}

bool MapRoom::getAccess()
{
	return access;
}