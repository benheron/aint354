#include "MiniMapIcon.h"



MiniMapIcon::MiniMapIcon(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions, bool e) : Entity(texture, pos, dimensions, spritePos, spriteDimensions )
{
	exists = e;
}

MiniMapIcon::~MiniMapIcon()
{

}

void MiniMapIcon::update(float dt)
{
}

void MiniMapIcon::render(SDL_Renderer *renderer)
{
	if (occupied)
	{
		texture->pushSpriteToScreen(renderer, pos, dimensions, spritePos+ Vec2(0, 15), spriteDimensions);
	}
	else {
		texture->pushSpriteToScreen(renderer, pos, dimensions, spritePos, spriteDimensions);
	}
}

void MiniMapIcon::setOccupied(bool o)
{
	occupied = o;
}

void MiniMapIcon::setExists(bool e)
{
	exists = e;
}


bool MiniMapIcon::getExists()
{
	return exists;
}
