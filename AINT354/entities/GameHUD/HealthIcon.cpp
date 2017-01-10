#include "HealthIcon.h"


HealthIcon::HealthIcon(Texture* texture, Vec2 pos, Character *player) : Entity(texture, pos)
{
	this->player = player;
}

HealthIcon::HealthIcon(Texture* texture, Vec2 pos, Vec2 dimensions, Character *player) : Entity(texture, pos, dimensions)
{

}


HealthIcon::HealthIcon(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Character *player) : Entity(texture, pos, dimensions, spritePos)
{

}

HealthIcon::~HealthIcon()
{

}

void HealthIcon::update(float dt)
{
}


void HealthIcon::render(SDL_Renderer *renderer)
{
	for (int i = 0; i < player->getHealth(); i++)
	{
		texture->pushSpriteToScreen(renderer, Vec2(pos.x + i * 22, pos.y) , spritePos, spriteDimensions);
	}


}