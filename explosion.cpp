#include "explosion.h"

//=============================================================================
// default constructor
//=============================================================================

Explosion::Explosion() : Entity()
{
	spriteData.scale = explosionNS::SCALE;
	spriteData.width = explosionNS::WIDTH;	//size of wall
	spriteData.height = explosionNS::HEIGHT;
	radius = explosionNS::WIDTH/2;
	spriteData.x = explosionNS::X;
	spriteData.y = explosionNS::Y;
	//mass = explosionNS::MASS;
	active = explosionNS::ACTIVE;
	collisionType = entityNS::CIRCLE;
	/*edge.left = -explosionNS::WIDTH / 2;
	edge.right = explosionNS::WIDTH / 2;
	edge.top = -explosionNS::HEIGHT / 2;
	edge.bottom = explosionNS::HEIGHT / 2;*/
	//maxhp = explosionNS::MAX_HP;
	//hp = explosionNS::HP;
	//hppercentage = explosionNS::HP_PERCENTAGE;
}

//=============================================================================
// Initialize the Wall.
// Post: returns true if successful, false if failed
//=============================================================================
bool Explosion::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the wall
//=============================================================================
void Explosion::draw()
{
	Image::draw();              // draw wall
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Explosion::update(float frameTime)
{
	Entity::update(frameTime);
}
