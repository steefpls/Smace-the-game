#include "bullet.h"
#include "wall.h"
using namespace bulletNS;

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
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
	frameDelay = BULLET_ANIMATION_DELAY;
	startFrame = BULLET_START_FRAME;     // first frame of ship animation
	endFrame = BULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	//radius = shipNS::WIDTH / 2.0;
	mass = MASS;
	collisionType = entityNS::ROTATED_BOX;
	edge.left = -WIDTH / 2;
	edge.right = WIDTH / 2;
	edge.top = -HEIGHT / 2;
	edge.bottom = HEIGHT / 2;
	bounce = BOUNCES;
	RotationRate = bulletNS::ROTATION_RATE;
	
	damage = DAMAGE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Bullet::draw()
{
	Image::draw();              // draw missile
}

bool Bullet::getdel()
{
	return false;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime)
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
	spriteData.x += (velocity.x * sin(spriteData.angle) * frameTime); // Update Ship X location
	spriteData.y += (velocity.y * -cos(spriteData.angle) * frameTime); // Update Ship Y location

}
void Bullet::setAngle(float a)
{
	spriteData.angle = a + ((rand() % 7 - 3) / 360 * 2 * PI);
}

float Bullet::getDamage()
{
	return DAMAGE;
}

void Bullet::topbottombounce()	//rotation when hitting top and bottom walls
{
	if (velocity.x > 0)
	{
		RotationRate += damage * 300 * (velocity.y / 200);
	}
	else
	{
		RotationRate -= damage * 300 * (velocity.y / 200);
	}
}

void Bullet::leftrightbounce()	//rotation when hitting left and right walls 
{
	if (velocity.y > 0)
	{
		RotationRate -= (velocity.x / 200);
	}
	else
	{
		RotationRate += (velocity.x / 200);
	}
}

