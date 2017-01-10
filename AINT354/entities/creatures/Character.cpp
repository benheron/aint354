#include "Character.h"
#include "../../Utility.h"

Character::Character(Texture* texture, Vec2 pos, CharacterType *characterType) :Entity(texture, pos), characterType(characterType)
{

}

Character::Character(Texture* texture, Vec2 pos, Vec2 dimensions, CharacterType *characterType) : Entity(texture, pos, dimensions), characterType(characterType)
{

}

Character::Character(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spriteDimensions, CharacterType *characterType) : Entity(texture, pos, dimensions, Vec2(0, 0), spriteDimensions), characterType(characterType)
{

}
Character::~Character()
{
}

void Character::update(float dt)
{
	if (!canDmg)
	{

		timer -= dt;
		if (timer < 0)
		{
			canDmg = true;
			
		}
	}
}

void Character::render(SDL_Renderer* renderer)
{
	//times by 1000 so can use mod
	int timerCheck = timer * 1000;

	//creates flashing effect on hit
	if (timerCheck % 10 < 5)
	{
		characterType->render(renderer, pos, dimensions, state, frame);
	}
	
	
}

void Character::setHealth(int h)
{
	health = h;
}

int Character::getHealth()
{
	return health;
}

void Character::setHit(bool b)
{
	hit = b;
	health -= 1;
	timer = 1.2f;
}

bool Character::isHit()
{
	return hit;
}

void Character::setCanDamage(bool d)
{
	canDmg = d;
}

bool Character::canDamage()
{
	return canDmg;
}



