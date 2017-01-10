#pragma once

#include "../Entity.h"
#include "CharacterType.h"

/**
@brief Creates all data for the character
*/
class Character : public Entity
{
public:

	/**
	@brief Create the character using the size of the Texture as the size of the character.
	@param texture A pointer to the Texture.
	@param pos The position of the character.
	*/
	Character(Texture* texture, Vec2 pos, CharacterType *characterType);

	/**
	@brief Create the character.
	@param texture A pointer to the Texture.
	@param pos The position of the character.
	@param dimensions The dimensions of the character.
	*/
	Character(Texture* texture, Vec2 pos, Vec2 dimensions, CharacterType *characterType);

	/**
	@brief Create the character with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the character.
	@param dimensions The dimensions of the character.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	
	Character(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spriteDimensions, CharacterType *characterType);

	~Character();

	/**
	@brief Update the Character.
	@param dt The delta time.
	*/
	virtual void update(float dt);


	/**
	@brief Render the Character.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);

	/**
	@brief Set the character type
	@param charType The character type
	*/
	void setCharacterType(CharacterType* charType);


	/**
	@brief Get the character type
	@return The character type
	*/
	CharacterType* getCharacterType();

	/**
	@brief Set the character health
	@param h The health to set to
	*/
	void setHealth(int h);

	/**
	@brief Get the character health
	@return The character health
	*/
	int getHealth();

	/**
	@brief Set if the character has been hit
	@param b If the character has been hit
	*/
	void setHit(bool b);

	/**
	@brief Get if the character has been hit
	@return True if hit false if not
	*/
	bool isHit();

	/**
	@brief Set if the character can be damaged
	@param d If the character has been hit

	*/
	void setCanDamage(bool d);

	/**
	@brief Check if the character can be hit
	@return true if can hit false if not
	*/
	bool canDamage();
private:
	///Reference to CharacterType
	CharacterType *characterType;

	Vec2 lastPos = Vec2(0);

	///The health of the character
	int health = 3;


	///if the character has been hit
	bool hit = false;

	///if the character can currently be damaged
	bool canDmg = true;


	///timer value
	float timer;
};