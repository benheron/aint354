#include "SliderSquare.h"

SliderSquare::SliderSquare(Texture * texture, Vec2 pos) : Entity(texture, pos)
{

}


SliderSquare::SliderSquare(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{

}


SliderSquare::SliderSquare(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{

}


SliderSquare::SliderSquare(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions) : Entity(texture, pos, dimensions, spritePos, spriteDimensions)
{

}

SliderSquare::~SliderSquare()
{

}


void SliderSquare::update(float dt)
{

}

void SliderSquare::render(SDL_Renderer *renderer)
{
	texture->pushToScreen(renderer, pos, dimensions);
	
}