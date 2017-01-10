#include "MapManager.h"


MapManager::MapManager(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager, int type)
{
	int c = 1;
	if (type == 0)
	{
	
		bool done = false;
		while (!done)
		{
			std::ostringstream oss;
			oss << c;
			std::string newFilePath = filePath + "/map" + oss.str() + ".txt";
			done = !loadMapData(newFilePath, tileTypeManager, creatureManager);

			Utility::log(Utility::I, "Using file path : " + newFilePath);


			c++;
		}
			
	}
	else if (type == 1)
	{
		loadMapDataForLevel(filePath, tileTypeManager, creatureManager);
	}
}

MapManager::~MapManager()
{
	for (int i = 0; i < rMaps.size(); i++)
	{
		delete rMaps[i];
	}
}

bool MapManager::loadMapData(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager)
{
	//A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;

	//A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> mapTiles;
	//std::unordered_map<std::string, std::vector<std::vector<Creature*>>> mapCreatures;
	std::vector<Creature*> mapCreatures;


	std::unordered_map<std::string, std::vector<std::vector<std::string>>> mapTileStrings;
	std::vector<std::string> mapCreatureStrings;

	Utility::log(Utility::I, "Loading map data : " + filePath);

	std::ifstream mapFile(filePath);

	if (mapFile.is_open())
	{
		std::string roomID;
		Vec2 mapIndexDimensions;
		int numberOfLayers;
		Vec2 tileDimensions;

		mapFile >> roomID;
		mapFile >> mapIndexDimensions.x;
		mapFile >> mapIndexDimensions.y;
		mapFile >> numberOfLayers;
		mapFile >> tileDimensions.x;
		mapFile >> tileDimensions.y;

		//store the map ID
		roomIDs.push_back(roomID);

		for (int i = 0; i < numberOfLayers; i++)
		{
			//Store the ID of the layer
			std::string layerID;
			mapFile >> layerID;
			layerIDs.push_back(layerID);

			for (int y = 0; y < mapIndexDimensions.y; y++)
			{
				if (layerID == "O" || layerID == "B")
				{
					std::vector<Tile*> tiles;
					mapTiles[layerID].push_back(tiles);

					//text version
					std::vector<std::string> tileStrings;
					mapTileStrings[layerID].push_back(tileStrings);

					for (int x = 0; x < mapIndexDimensions.x; x++)
					{


						//Get the tile
						std::string tileID;
						mapFile >> tileID;

						//Get the data to load into the new tile
						TileType* tileType = tileTypeManager->getTileType(tileID);
						Vec2 spriteDimensions = tileType->getSpriteDimensions();
						Vec2 spritePos = tileType->getSpritePos();
						Texture* tileTexture = tileType->getTexture();

						//Store tile
						mapTiles[layerID][y].push_back(
							new Tile(tileTexture, Vec2((x * tileDimensions.x), (y * tileDimensions.y)), tileDimensions, spritePos, spriteDimensions, tileType)
						);
						



						//store tile text version
						mapTileStrings[layerID][y].push_back(tileID);
					}
				}
				else if (layerID == "C")
				{
					//std::vector<Creature*> creatures;
					//mapCreatures[layerID].push_back(creatures);
					for (int x = 0; x < mapIndexDimensions.x; x++)
					{
						//Get the creature
						std::string creatureID;
						mapFile >> creatureID;

						//if (creatureID != "XX")
						//{
						/*	Vec2 pos = Vec2((x * tileDimensions.x), (y * tileDimensions.y));

							CreatureType* creatureType = creatureManager->getCreatureType(creatureID);
							Vec2 spriteDimensions = creatureType->getSpriteDimensions();
							Texture* creatureTexture = creatureType->getTexture();

							mapCreatures.push_back(
								new Creature(creatureTexture, pos, spriteDimensions, creatureType));*/

							mapCreatureStrings.push_back(creatureID);
						//}
					}
				}
				
			}
		}

		std::string p;
		Vec2 playerCoords;
		mapFile >> p;

		if (p == "P")
		{
			mapFile >> playerCoords.x;
			mapFile >> playerCoords.y;
			Utility::log(Utility::I, "Player spawn coordinates: X: " + Utility::floatToString(playerCoords.x) + " Y: " + Utility::floatToString(playerCoords.y));
		}
		else {
			Utility::log(Utility::E, "Dammit, we're corrupt");
		}
		mapFile.close();

		//Store the map
	/*	roomTemplates[roomID] = new RoomTemplate(mapTiles, mapCreatures, layerIDs, playerCoords);*/

		//rMaps.push_back(new RoomTemplate(mapTiles, mapCreatures, layerIDs, playerCoords));

		rMaps.push_back(new RoomTemplate(mapTileStrings, mapCreatureStrings, layerIDs));

		Utility::log(Utility::I, "Map data loaded");

		return true;
	}
	else 
	{
		//Error
		Utility::log(Utility::E, "Unable to open map file : " + filePath);
		return false;
	}
}

RoomTemplate* MapManager::getMap(std::string mapID)
{
	return roomTemplates[mapID];
}

RoomTemplate* MapManager::getRandomMap()
{
	return rMaps[Utility::randomInt(0, (rMaps.size() - 1))];
}

RoomTemplate* MapManager::getRandomMapFromIndex(int i)
{
	return rMaps[i];
}


void MapManager::loadMapDataForLevel(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager)
{

	Utility::log(Utility::I, "Loading level data : " + filePath);

	std::ifstream levelFile(filePath);

	if (levelFile.is_open())
	{
		int numRooms;

		levelFile >> numRooms;

		for (int i = 0; i < numRooms; i++)
		{

			//A vector to hold all of the layer IDs.
			std::vector<std::string> layerIDs;
			//A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
			std::unordered_map<std::string, std::vector<std::vector<Tile*>>> mapTiles;
			//std::unordered_map<std::string, std::vector<std::vector<Creature*>>> mapCreatures;
			std::vector<Creature*> mapCreatures;

			std::unordered_map<std::string, std::vector<std::vector<std::string>>> mapTileStrings;
			std::vector<std::string> mapCreatureStrings;

			

			Vec2 roomPos;
			levelFile >> roomPos.x;
			levelFile >> roomPos.y;

			roomPositions.push_back(roomPos);

			for (int j = 0; j < 3; j++)
			{
				std::string layerID;
				levelFile >> layerID;
				layerIDs.push_back(layerID);

				for (int y = 0; y < 15; y++)
				{
					if (layerID == "O" || layerID == "B")
					{
						//text version
						std::vector<std::string> tileStrings;
						mapTileStrings[layerID].push_back(tileStrings);

						for (int x = 0; x < 20; x++)
						{


							Vec2 tileDimensions = Vec2(32, 32);

							//Get the tile
							std::string tileID;
							levelFile >> tileID;

							//Get the data to load into the new tile
							TileType* tileType = tileTypeManager->getTileType(tileID);
							Vec2 spriteDimensions = tileType->getSpriteDimensions();
							Vec2 spritePos = tileType->getSpritePos();
							Texture* tileTexture = tileType->getTexture();

	

							//store tile text version
							mapTileStrings[layerID][y].push_back(tileID);
						}
					}
					else if (layerID == "C")
					{
						//std::vector<Creature*> creatures;
						//mapCreatures[layerID].push_back(creatures);
						for (int x = 0; x < 20; x++)
						{
							//Get the creature
							std::string creatureID;
							levelFile >> creatureID;

							mapCreatureStrings.push_back(creatureID);
						}
					}
				}
			}
			rMaps.push_back(new RoomTemplate(mapTileStrings, mapCreatureStrings, layerIDs));
		}



		levelFile.close();
		
		Utility::log(Utility::I, "Level data loaded");

	}
	else
	{
		//Error
		Utility::log(Utility::E, "Unable to open level file : " + filePath);
	}
}

std::vector<Vec2> MapManager::getRoomPositions()
{
	return roomPositions;
}

int MapManager::getNumberMaps()
{
	return rMaps.size();
}