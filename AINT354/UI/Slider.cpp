#include "Slider.h"
#include "../Collision.h"
#include "../Utility.h"

Slider::Slider(Texture *t, Vec2 p, Vec2 d, int v)
{
	pos = p;
	dimens = d;
	texture = t;

	half = Vec2(((2 * pos.x) + dimens.x) / 2, (dimens.y + 2 * (pos.y)) / 2);

	//Utility::log(Utility::I, "Slider: " + Utility::floatToString(g));

	squarePos = Vec2(half.x-(squareDimens.x/2), half.y - (squareDimens.y/2));
	square = new SliderSquare(t, squarePos, squareDimens);

	value = v;

	buildSlider();
}

Slider::~Slider()
{

}

void Slider::buildSlider()
{
	
}


void Slider::render(SDL_Renderer* renderer)
{
	float mid = (dimens.y + 2*(pos.y)) / 2;


	texture->pushToScreen(renderer, pos, Vec2(1.0f, dimens.y));
	texture->pushToScreen(renderer, Vec2(pos.x+ dimens.x, pos.y), Vec2(1.0f, dimens.y));


	texture->pushToScreen(renderer, Vec2(pos.x, mid), Vec2(dimens.x, 1.0f));

	square->render(renderer);
}

void Slider::changeValue(Vec2 p)
{
	square->setPosition(Vec2(p.x - (square->getDimensions().x/2), square->getPosition().y));


	Vec2 tmp = square->getPosition() - pos + (square->getDimensions() / 2);
	int tmpx = tmp.x;

	float v = tmpx / dimens.x;

	//cannot be 0
	value = (v * 39) + 2;


	if (Collision::pointBoxCollision(p, square->getPosition(), square->getDimensions()))
	{

	}
}


int Slider::getValue()
{
	return value;
}


void Slider::setPosition(Vec2 p)
{
	pos = p;
	square->setPosition(Vec2(half.x - (squareDimens.x / 2), half.y - (squareDimens.y / 2)));
}

Vec2 Slider::getPosition()
{
	return pos;
}

Vec2 Slider::getDimensions()
{
	return dimens;
}