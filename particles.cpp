//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#include "particles.h"
using namespace particlesNS;
//=============================================================================
// default constructor
//=============================================================================

Particles::Particles() : Entity()
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
	frameDelay = PARTICLE_ANIMATION_DELAY;
	startFrame = PARTICLE_START_FRAME;     // first frame of ship animation
	endFrame = PARTICLE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	//radius = shipNS::WIDTH / 2.0;
	mass = MASS;
	collisionType = entityNS::CIRCLE;
	radius = WIDTH / 2;
}

//=============================================================================
// Initialize the Wall.
// Post: returns true if successful, false if failed
//=============================================================================
bool Particles::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the wall
//=============================================================================
void Particles::draw()
{
	Image::draw();              // draw wall
}

bool Particles::getdel()
{
	return false;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Particles::update(float frameTime)
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
	velocity.x = velocity.x - ((1 - particlesNS::DRAG) *velocity.x) * frameTime;
	velocity.y = velocity.y - ((1 - particlesNS::DRAG) *velocity.y) * frameTime;   //Implementation of "Air" Resistance

	//SHIP LOCATION UPDATEb
	spriteData.x += (velocity.x  * frameTime); // Update Ship X location
	spriteData.y += (velocity.y  * frameTime); // Update Ship Y location
}

void Particles::setAngle(float a)
{
	spriteData.angle = a;
}

