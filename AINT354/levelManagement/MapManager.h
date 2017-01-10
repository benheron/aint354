#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Tile.h"
#include "Map.h"
#include "TileTypeManager.h"
#include "../entities/creatures/Creature.h"
#include "../entities/creatures/CreatureManager.h"
#include "../Utility.h"
#include "RoomTemplate.h"

/**
@brief Contains all the data and functions to manage the Map Objects.
*/
class MapManager 
{
public:
	/**
	@brief Creates the MapManager to load in the Map files
	@param filePath The path to the file which holds the initial map data.
	@param tileTypeManager* A pointer to the TileTypeManager.
	@param creatureManager A pointer to the CreatureManager
	*/
	MapManager(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager, int type);

	/**
	@brief MapManager destructor.
	*/
	~MapManager();

	/**
	@brief Loads in the Map data.
	@param filePath The path to the file which holds the map data.
	@param tileTypeManager* A pointer to the TileTypeManager.
	*/
	bool loadMapData(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager);

	/**
	@brief Gets the Map data.
	@param mapID The ID of the Map to return.
	@return The Map data.
	*/
	RoomTemplate* getMap(std::string mapID);

	/**
	@brief Gets the random Map data
	@return The Map data.
	*/
	RoomTemplate* getRandomMap();

	std::vector<Vec2> getRoomPositions();

	RoomTemplate* getRandomMapFromIndex(int i);

	int getNumberMaps();

private:

	void loadMapDataForLevel(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager);



	///A vector to hold all of the map IDs.
	std::vector<std::string> roomIDs;
	///A vector to hold all of the maps.
	std::unordered_map<std::string, RoomTemplate*> roomTemplates;

	///A different vector to hold maps for random lookups
	std::vector<RoomTemplate*> rMaps;

	std::vector<Vec2> roomPositions;


};