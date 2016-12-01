#include "RoomTemplate.h"

RoomTemplate::RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles, std::vector<Creature*> roomCreatures, std::vector<std::string> layerIDs, Vec2 spawnPoint) : roomTiles(roomTiles), roomCreatures(roomCreatures), layerIDs(layerIDs), spawnPoint(spawnPoint)
{
}

RoomTemplate::RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<std::string>>> roomTilesData, std::vector<std::string> roomCreaturesData, std::vector<std::string> layerIDs) : roomTilesData(roomTilesData), roomCreaturesData(roomCreaturesData), layerIDs(layerIDs), spawnPoint(spawnPoint)
{
}

RoomTemplate::RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles, std::vector<Creature*> roomCreatures, std::vector<std::string> layerIDs, Vec2 spawnPoint, Vec2 mapPos) : roomTiles(roomTiles), roomCreatures(roomCreatures), layerIDs(layerIDs), spawnPoint(spawnPoint), mapPos(mapPos)
{
}


RoomTemplate::~RoomTemplate()
{
	delete player;
}

void RoomTemplate::update(float dt)
{
}

void RoomTemplate::render(SDL_Renderer* renderer)
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

void RoomTemplate::loadPlayer(CharacterType *pt)
{
	player = new Character(pt->getTexture(), Vec2(225,225), pt);

	playerLoaded = true;
}


void RoomTemplate::setPos(Vec2 pos)
{

	mapPos = pos;
}

Vec2 RoomTemplate::getPos()
{
	return mapPos;
}

void RoomTemplate::setAccess(bool b)
{
	access = true;
}

bool RoomTemplate::getAccess()
{
	return access;
}

std::unordered_map<std::string, std::vector<std::vector<Tile*>>> RoomTemplate::getRoomTiles()
{
	return roomTiles;
}

std::vector<std::string> RoomTemplate::getLayerIDs()
{
	return layerIDs;
}

std::vector<Creature*> RoomTemplate::getCreatures()
{
	return roomCreatures;
}

std::unordered_map<std::string, std::vector<std::vector<std::string>>> RoomTemplate::getRoomTileData()
{
	return roomTilesData;
}

std::vector<std::string> RoomTemplate::getCreatureData()
{
	return roomCreaturesData;
}