#include "wall.h"

//=============================================================================
// default constructor
//=============================================================================

Wall::Wall() : Entity() 
{
	spriteData.width = wallNS::WIDTH;	//size of wall
	spriteData.height = wallNS::HEIGHT;
	spriteData.x = wallNS::X;
	spriteData.y = wallNS::Y;


	collisionType = entityNS::BOX;
}