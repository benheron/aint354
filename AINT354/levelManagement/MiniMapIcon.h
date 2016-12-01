#pragma once

#include "../entities/Entity.h"

class MiniMapIcon : public Entity
{
public:


	/**
	@brief Constructs the MiniMapIcon object.
	@param texture A pointer to the MiniMapIcon Texture.
	@param pos The position of the  MiniMapIcon.
	*/
	MiniMapIcon(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions, bool exist);

	/**
	@brief MiniMapIcon destructor.
	*/
	~MiniMapIcon();

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
	@brief Set the occupied value for this icon
	@param o Occupied or not
	*/
	void setOccupied(bool o);

	/**
	@brief Get the exists value for this icon
	*/
	bool getExists();

	/**
	@brief Get the exists value for this icon
	@param e Exists or not
	*/
	void setExists(bool e);

private:
	///If the icon should show the occupied version or not
	bool occupied = false;

	bool exists;
};