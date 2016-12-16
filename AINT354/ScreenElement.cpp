#include "ScreenElement.h"

ScreenElement::ScreenElement(Vec2 pos)
	:  pos(pos)
{
	
}

ScreenElement::ScreenElement( Vec2 pos, Vec2 dimensions)
	:  pos(pos), dimensions(dimensions)
{
	
}

ScreenElement::~ScreenElement()
{
}

void ScreenElement::render(SDL_Renderer* renderer)
{
	
}

void ScreenElement::setPosition(Vec2 pos)
{
	
}

void ScreenElement::setDimensions(Vec2 dimensions)
{
	this->dimensions = dimensions;
}

Vec2 ScreenElement::getPosition()
{
	return pos;
}

Vec2 ScreenElement::getDimensions()
{
	return dimensions;
}