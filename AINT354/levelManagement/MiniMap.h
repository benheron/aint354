#pragma once

#include "RandMap.h"
#include <vector>
#include "MapRoom.h"

#include "../Texture.h"
#include "../Vec2.h"
#include "MiniMapIcon.h"

class MiniMap
{
public:
	MiniMap(SDL_Renderer* renderer, int m);
	~MiniMap();

	void buildMiniMap(RandMap *mapFloor, Vec2 pos);

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


	bool mouseCollide(int mouseX, int mouseY);


	Vec2 changeRoom(int mouseX, int mouseY);


protected:

	std::vector<std::vector<MiniMapIcon*>> map;


	Texture *tmpTexture;
	Texture *roomOnTexture;

	Texture *mapIcon;



	Vec2 curRoomPos;

	RandMap *mf;

	Vec2 pos;
	Vec2 dimensions;

	int mode;
};