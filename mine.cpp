//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#include "mine.h"
using namespace mineNS;
//=============================================================================
// default constructor
//=============================================================================

Mine::Mine() : Entity()
{
	spriteData.scale = SCALE;
	spriteData.width = WIDTH;           // size of Ship1
	spriteData.height = HEIGHT;
	spriteData.x = X;                   // location on screen
	spriteData.y = Y;
	spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH;
	velocity.x = X_SPEED;                             // velocity X
	velocity.y = Y_SPEED;                             // velocity Y
	maxvel = MAX_VELOCITY;							// Max Velocity
	frameDelay = MINE_ANIMATION_DELAY;
	startFrame = MINE_START_FRAME;     // first frame of ship animation
	endFrame = MINE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	//radius = shipNS::WIDTH / 2.0;
	mass = MASS;
	collisionType = entityNS::CIRCLE;
	radius = WIDTH / 2;
	damage = DAMAGE;
	hp = HP;
	activationRadius = ACTIVATION_RADIUS;	//radius of the circle around the mine in which the mine detects the player to follow
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

bool Mine::getdel()
{
	return false;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Mine::update(float frameTime)
{
	Entity::update(frameTime);

	//------------Handle Ship Rotation on Key Press--------------

	//Keeping the ranges of the angle to 0<x<360
	while (spriteData.angle < 0)
	{
		spriteData.angle += 2 * PI;			//Calculation done in radians
	}

	while (spriteData.angle > 2 * PI)
	{
		spriteData.angle -= 2 * PI;			//Calculation done in radians
	}

	spriteData.angle = (spriteData.angle + ROTATION_RATE / 360 * 2 * PI * frameTime); // Final update missile rotation

	//Mine Drag
	velocity.x = velocity.x - ((1 - mineNS::DRAG) *velocity.x) * frameTime;
	velocity.y = velocity.y - ((1 - mineNS::DRAG) *velocity.y) * frameTime;   //Implementation of "Air" Resistance

	//SHIP LOCATION UPDATEb
	spriteData.x += (velocity.x  * frameTime); // Update Ship X location
	spriteData.y += (velocity.y  * frameTime); // Update Ship Y location
}

void Mine::setAngle(float a)
{
	spriteData.angle = a;
}

float Mine::getDamage()
{
	return DAMAGE;
}

float Mine::getActivationRadius()
{
	return activationRadius;
}


