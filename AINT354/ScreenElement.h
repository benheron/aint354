#pragma once

#include "Vec2.h"
#include "Texture.h"

/**
@brief Contains multiple entities together for one element
*/
class ScreenElement
{
public:
	/**
	@brief Create the ScreenElement using the size of the Texture as the size of the ScreenElement.
	@param texture A pointer to the Texture.
	@param pos The position of the ScreenElement.
	*/
	ScreenElement(Vec2 pos);

	/**
	@brief Create the ScreenElement.
	@param texture A pointer to the Texture.
	@param pos The position of the ScreenElement.
	@param dimensions The dimensions of the ScreenElement.
	*/
	ScreenElement(Vec2 pos, Vec2 dimensions);


	virtual ~ScreenElement();

	/**
	@brief Update the ScreenElement.
	@param dt The delta time.
	*/
	virtual void update(float dt) = 0;

	/**
	@brief Render the ScreenElement.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);

	/**
	@brief Set the position of the ScreenElement.
	@param pos The position of the ScreenElement.
	*/
	void setPosition(Vec2 pos);

	/**
	@brief Set the dimensions of the ScreenElement.
	@param dimensions The dimensions of the ScreenElement.
	*/
	void setDimensions(Vec2 dimensions);

	/**
	@brief Get the position of the ScreenElement.
	@return The position of the ScreenElement.
	*/
	Vec2 getPosition();

	/**
	@brief Get the dimensions of the ScreenElement.
	@return The dimensions of the ScreenElement.
	*/
	Vec2 getDimensions();


protected:
	///The XY position of the ScreenElement.
	Vec2 pos;
	///The dimensions of the ScreenElement.
	Vec2 dimensions;

};