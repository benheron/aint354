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
	MapManager(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager);

	/**
	@brief MapManager destructor.
	*/
	~MapManager();

	/**
	@brief Loads in the Map data.
	@param filePath The path to the file which holds the map data.
	@param tileTypeManager* A pointer to the TileTypeManager.
	*/
	void loadMapData(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager);

	/**
	@brief Gets the Map data.
	@param mapID The ID of the Map to return.
	@return The Map data.
	*/
	Map* getMap(std::string mapID);

	/**
	@brief Gets the random Map data
	@return The Map data.
	*/
	Map* getRandomMap();

private:
	///A vector to hold all of the map IDs.
	std::vector<std::string> mapIDs;
	///A vector to hold all of the maps.
	std::unordered_map<std::string, Map*> maps;

	///A different vector to hold maps for random lookups
	std::vector<Map*> rMaps;

};