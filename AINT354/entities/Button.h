#pragma once
#include "Entity.h"
#include "SDL_ttf.h"


class Button : public Entity
{
public:

	Button();
	virtual ~Button();

	/**
	@brief Create the Button using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Button.
	*/
	Button(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Button.
	@param dimensions The dimensions of the Button.
	*/
	Button(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the Button with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the Button.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	Button(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the Button with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Button.
	@param dimensions The dimensions of the Button.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	Button(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);




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


	/**
	@brief Get the hover value
	*/
	bool isHover();

	/**
	@brief Sets the hover value
	@param h The hover value to set to
	*/
	void setHover(bool h);

protected:
	void buildButton();

	Texture *buttonBgr;

	TTF_Font *font = NULL;

	bool hover = false;


};