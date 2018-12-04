#include "blackhole.h"
#include "wall.h"
using namespace blackholeNS;

//=============================================================================
// default constructor
//=============================================================================
Blackhole::Blackhole() : Entity()
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
	frameDelay = BLACKHOLE_ANIMATION_DELAY;
	startFrame = BLACKHOLE_START_FRAME;     // first frame of ship animation
	endFrame = BLACKHOLE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	//radius = shipNS::WIDTH / 2.0;
	mass = MASS;
	collisionType = entityNS::CIRCLE;
	radius = WIDTH / 2;

	damage = DAMAGE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Blackhole::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Blackhole::draw()
{
	Image::draw();              // draw missile
}

bool Blackhole::getdel()
{
	return false;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Blackhole::update(float frameTime)
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


	//SHIP LOCATION UPDATEb
	//spriteData.x += (velocity.x * sin(spriteData.angle) * frameTime); // Update Ship X location
	//spriteData.y += (velocity.y * -cos(spriteData.angle) * frameTime); // Update Ship Y location

}
void Blackhole::setAngle(float a)
{
	spriteData.angle = a + ((rand() % 7 - 3) / 360 * 2 * PI);
}

float Blackhole::getDamage()
{
	return DAMAGE;
}