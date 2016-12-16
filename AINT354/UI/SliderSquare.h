#pragma once
#include "../entities/Entity.h"

class SliderSquare : public Entity
{
public:

	virtual ~SliderSquare();

	/**
	@brief Create the SliderSquare using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the SliderSquare.
	*/
	SliderSquare(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the SliderSquare.
	@param dimensions The dimensions of the SliderSquare.
	*/
	SliderSquare(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the SliderSquare with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the SliderSquare.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	SliderSquare(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the SliderSquare with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the SliderSquare.
	@param dimensions The dimensions of the SliderSquare.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	SliderSquare(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);




	/**
	@brief Update the Creature.
	@param dt The delta time.
	*/
	virtual void update(float dt);


	/**
	@brief Render the Creature.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);

	//bool mouseCollide(int mouseX, int mouseY);

protected:
	

};