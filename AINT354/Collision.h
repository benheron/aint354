#pragma once

#include "Vec2.h"


/**
@brief A collection of collision functions
*/
namespace Collision
{
	/**
	@brief Collision between a single point and a box
	@param posA The position of the point
	@param posB The position of the box
	@param dimenB The dimensions of this box
	*/
	bool pointBoxCollision(Vec2 posA, Vec2 posB, Vec2 dimenB);


	/**
	@brief Collision between two boxes
	@param posA The position of the first box
	@param dimenA The dimensions of the first box
	@param posB The position of the second box
	@param dimenB The dimensions of the second box
	*/
	bool boxBoxCollision(Vec2 posA, Vec2 dimenA, Vec2 posB, Vec2 dimenB);

	
}
