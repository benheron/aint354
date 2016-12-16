#include "Button.h"


Button::Button(Texture* texture, Vec2 pos) : Entity(texture, pos)
{


}

Button::Button(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{

}


Button::Button(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{

}

Button::~Button()
{

}

void Button::buildButton()
{

}

void Button::update(float dt)
{
}


void Button::render(SDL_Renderer *renderer)
{
	if (hover) {
		texture->pushSpriteToScreen(renderer, pos, Vec2(spritePos.x, spriteDimensions.y), spriteDimensions);
	}
	else if  (selected) {
		/************************************************************************/
		/*         Need to change for all buttons                               */
		/************************************************************************/
		
		texture->pushSpriteToScreen(renderer, pos, Vec2(spritePos.x, spriteDimensions.y), spriteDimensions);
	}
	else {
		texture->pushSpriteToScreen(renderer, pos, spritePos, spriteDimensions);
	}
	
}


bool Button::isHover()
{
	return hover;
}

void Button::setHover(bool h)
{
	hover = h;
}

void Button::setSelected(bool s)
{
	selected = s;
}

bool Button::getSelected()
{
	return selected;
}