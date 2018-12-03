#include "mine.h"

//=============================================================================
// default constructor
//=============================================================================

Mine::Mine() : Entity()
{
	spriteData.scale = mineNS::SCALE;
	spriteData.width = mineNS::WIDTH;	//size of wall
	spriteData.height = mineNS::HEIGHT;
	//radius = wallNS::WIDTH;
	spriteData.x = mineNS::X;
	spriteData.y = mineNS::Y;
	mass = mineNS::MASS;
	active = mineNS::ACTIVE;
	collisionType = entityNS::ROTATED_BOX;
	edge.left = -mineNS::WIDTH / 2;
	edge.right = mineNS::WIDTH / 2;
	edge.top = -mineNS::HEIGHT / 2;
	edge.bottom = mineNS::HEIGHT / 2;
	maxhp = mineNS::MAX_HP;
	hp = mineNS::HP;
	hppercentage = mineNS::HP_PERCENTAGE;
}

//=============================================================================
// Initialize the Wall.
// Post: returns true if successful, false if failed
//=============================================================================
bool Mine::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the wall
//=============================================================================
void Mine::draw()
{
	Image::draw();              // draw wall
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Mine::update(float frameTime)
{
	Entity::update(frameTime);

	//hppercentage = (hp / maxhp) * 100;
	//if (hppercentage > 75)
	//{
	//	setCurrentFrame(0);
	//}

	//else if (hppercentage <= 75 && hppercentage > 50)
	//{
	//	setCurrentFrame(1);
	//}
	//else if (hppercentage <= 50 && hppercentage > 25)
	//{
	//	setCurrentFrame(2);
	//}
	//else
	//{
	//	setCurrentFrame(3);
	//}

}

