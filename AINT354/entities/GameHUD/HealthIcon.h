#pragma once

#include <string>
#include "../Entity.h"
#include "../creatures/Character.h"

class HealthIcon : public Entity
{
public:
	/**
	@brief Create the HealthIcon using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the HealthIcon.
	*/
	HealthIcon(Texture* texture, Vec2 pos, Character *player);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the HealthIcon.
	@param dimensions The dimensions of the HealthIcon.
	*/
	HealthIcon(Texture* texture, Vec2 pos, Vec2 dimensions, Character *player);



	/**
	@brief Create the HealthIcon with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the HealthIcon.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	HealthIcon(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Character *player);

	/**
	@brief Create the HealthIcon with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the HealthIcon.
	@param dimensions The dimensions of the HealthIcon.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	HealthIcon(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions, Character *player);
	
	virtual ~HealthIcon();
	
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

protected:
	Character *player;

};