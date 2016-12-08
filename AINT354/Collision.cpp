#include "Collision.h"
#include "Utility.h"

bool Collision::pointBoxCollision(Vec2 posA, Vec2 posB, Vec2 dimenB)
{
	if (posA.x > posB.x &&
		posA.x < (posB.x + dimenB.x) &&
		posA.y > posB.y &&
		posA.y < (posB.y + dimenB.y))
	{
		return true;
	}
	return false;
}


bool Collision::boxBoxCollision(Vec2 posA, Vec2 dimenA, Vec2 posB, Vec2 dimenB)
{
	if ((posA.x + dimenA.x) < posB.x ||
		posA.x > (posB.x + dimenB.x) ||
		(posA.y + dimenA.y) < posB.y ||
		posA.y > (posB.y + dimenB.y))
	{
		return false;
	}
/*
	Utility::log(Utility::I, "Player X: " + Utility::floatToString(posA.x) + ", Player Y: " + Utility::floatToString(posA.y));
	Utility::log(Utility::I, "Player Width " + Utility::floatToString(dimenA.x) + ", Player Height: " + Utility::floatToString(dimenA.y));
	Utility::log(Utility::I, "Tile X: " + Utility::floatToString(posB.x) + ", Tile Y: " + Utility::floatToString(posB.y));
	Utility::log(Utility::I, "Tile Width " + Utility::floatToString(dimenB.x) + ", Tile Height: " + Utility::floatToString(dimenB.y));*/

	return true;
}