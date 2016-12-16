#pragma once

#include <string>
#include "../entities/Entity.h"
#include "TileType.h"
#include "TileTypeManager.h"

/**
@brief Contains all the data and functions dealing with the Tile objects.
*/
class Tile : public Entity
{
public:

	Tile(Vec2 pos, Vec2 dimensions, TileType *tileType);

	Tile(Texture* texture, Vec2 pos, Vec2 dimensions, TileType *tileType);


	
	/**
	@brief Constructs the Tile object.
	@param texture A pointer to the Tile Texture.
	@param pos The position of the Tile.
	@param dimensions The dimensions of the Tile.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	@param tileType A pointer to the TileType.
	*/
	Tile(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions, TileType* tileType);

	/**
	@brief Tile destructor.
	*/
	~Tile();

	/**
	@brief Updates the Tile.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief Render the Tile.
	@param renderer A pointer to the renderer.
	*/
	void render(SDL_Renderer* renderer);

	/**
	@brief checks if the TileID is blank
	@return True if ID is XX, False if not
	*/
	bool haveBlankID();


	void setTileType(std::string ID, TileTypeManager *ttmng);

	std::string getTileTypeID();

private:
	///Reference to tile type.
	TileType* tileType;
};