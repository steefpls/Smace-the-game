#include "wall.h"

//=============================================================================
// default constructor
//=============================================================================

Wall::Wall() : Entity() 
{
	spriteData.width = wallNS::WIDTH;	//size of wall
	spriteData.height = wallNS::HEIGHT;
	//radius = wallNS::WIDTH;
	spriteData.x = wallNS::X;
	spriteData.y = wallNS::Y;
	mass = wallNS::MASS;
	active = wallNS::ACTIVE;
	collisionType = entityNS::ROTATED_BOX;
	edge.left = -wallNS::WIDTH / 2;
	edge.right = wallNS::WIDTH / 2;
	edge.top = -wallNS::HEIGHT / 2;
	edge.bottom = wallNS::HEIGHT / 2;
	hp = wallNS::HP;
}

//=============================================================================
// Initialize the Wall.
// Post: returns true if successful, false if failed
//=============================================================================
bool Wall::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the wall
//=============================================================================
void Wall::draw()
{
	Image::draw();              // draw wall
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Wall::update(float frameTime)
{
	Entity::update(frameTime);
	
}

