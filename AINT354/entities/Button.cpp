#include "Button.h"


Button::Button(Texture* texture, Vec2 pos, std::string text) : Entity(texture, pos)
{


}

Button::Button(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
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
	texture->pushToScreen(renderer, pos, dimensions);
}

bool Button::mouseCollide(int mouseX, int mouseY)
{
	if (mouseX > pos.x &&
		mouseX < (pos.x + dimensions.x) &&
		mouseY > pos.y &&
		mouseY < (pos.y + dimensions.y))
	{
		return true;
	}
	return false;


}