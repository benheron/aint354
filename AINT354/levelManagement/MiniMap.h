#pragma once

#include "RandMap.h"
#include <vector>
#include "MapRoom.h"

#include "../Texture.h"
#include "../Vec2.h"

class MiniMap
{
public:
	MiniMap(SDL_Renderer* renderer);
	~MiniMap();

	void buildMiniMap(RandMap *mapFloor);

	/**
	@brief Update the Map.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief Render the Tile objects in the map.
	@param renderer A pointer to the renderer.
	*/
	void render(SDL_Renderer* renderer);

protected:
	std::vector<std::vector<int>> map;


	Texture *tmpTexture;
	Texture *roomOnTexture;


	Vec2 curRoomPos;

	RandMap *mf;
};