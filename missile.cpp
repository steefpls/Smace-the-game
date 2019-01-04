//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#include "missile.h"
using namespace missileNS;

//=============================================================================
// default constructor
//=============================================================================
Missile::Missile() : Entity()
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
	xacc = X_ACC;
	yacc = Y_ACC;

	maxvel = MAX_VELOCITY;							// Max Velocity
	frameDelay = MISSILE_ANIMATION_DELAY;
	startFrame = MISSILE_START_FRAME;     // first frame of ship animation
	endFrame = MISSILE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	//radius = shipNS::WIDTH / 2.0;
	mass = MASS;
	collisionType = entityNS::ROTATED_BOX;
	edge.left = -WIDTH / 2;
	edge.right = WIDTH / 2;
	edge.top = -HEIGHT / 2;
	edge.bottom = HEIGHT / 2;
	particlesTimer = PARTICLES_TIMER;

	
	damage = DAMAGE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Missile::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Missile::draw()
{
	Image::draw();              // draw missile
}

bool Missile::getdel()
{
	return false;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Missile::update(float frameTime)
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

	if (abs(velocity.x*sin(spriteData.angle)) < abs(missileNS::MAX_VELOCITY*sin(spriteData.angle)))
	{
		velocity.x += xacc * sin(spriteData.angle)*frameTime;
	}
	if (abs(velocity.y*-cos(spriteData.angle)) < abs(missileNS::MAX_VELOCITY*-cos(spriteData.angle)))
	{
		velocity.y += yacc * -cos(spriteData.angle)*frameTime;
	}
	
	if (particlesTimer > 0)
	{
		particlesTimer -= 1.0f*frameTime;
	}

	//MISSILE LOCATION UPDATE
	spriteData.x += (velocity.x  * frameTime); // Update Ship X location
	spriteData.y += (velocity.y  * frameTime); // Update Ship Y location

}
void Missile::setAngle(float a)
{
	spriteData.angle = a;
}

float Missile::getDamage()
{
	return DAMAGE;
}

float Missile::getparticlestimer()
{
	return particlesTimer;
}

void Missile::spawnparticles()
{
	particleList.push_back(new Particles);
	particlesTimer = MAX_PARTICLES_TIMER;
}

void Missile::setParticlesXY()
{
	particleList[particleList.size() - 1]->setX(getCenterX() - ((particleList[particleList.size() - 1]->getWidth())*(particleList[particleList.size() - 1]->getScale()) / 2));
	particleList[particleList.size() - 1]->setY(getCenterY() - ((particleList[particleList.size() - 1]->getHeight())*(particleList[particleList.size() - 1]->getScale()) / 2));
	particleList[particleList.size() - 1]->setAngle(rand() % 359 + 1);
	particleList[particleList.size() - 1]->setScale(0.5);

	particleList[particleList.size() - 1]->setVelocityX(-particleList[particleList.size() - 1]->getVelocityX()*(rand() % 5 + 8) / 10 * sin(getRadians()));
	particleList[particleList.size() - 1]->setVelocityY(-particleList[particleList.size() - 1]->getVelocityY()*(rand() % 5 + 8) / 10 * -cos(getRadians()));
}
