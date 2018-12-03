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

	if (abs(sin(spriteData.angle)*velocity.x)<= abs(sin(spriteData.angle)*maxvel) && abs(cos(spriteData.angle)*velocity.y) <= abs(cos(spriteData.angle)*maxvel))
	{
		velocity.x += sin(spriteData.angle) * X_ACC * frameTime;
		velocity.y -= cos(spriteData.angle) * Y_ACC * frameTime;   //Position update
	}



	//================================================= SHIP DASH TIMER =================================================
	if (DASH_TIMER > 0)		//If timer is larger than 0
	{
		DASH_TIMER -= 1.0f * frameTime; //Timer goes down by 1 per second

	}

	//if (input->isKeyDown(SPACE) && DASH_TIMER <= 0)
	//{
	//	velocity.x += sin(spriteData.angle) * BOOST_AMT;
	//	velocity.y -= cos(spriteData.angle) * BOOST_AMT;
	//	DASH_TIMER = MAX_DASH_TIMER;

	//}


	//SHIP LOCATION UPDATEb
	spriteData.x += (velocity.x * spriteData.scale * frameTime); // Update Ship X location
	spriteData.y += (velocity.y * spriteData.scale * frameTime); // Update Ship Y location

}
void Missile::setAngle(float a)
{
	spriteData.angle = a+ ((rand() % 7 - 3)/360*2*PI);
}

float Missile::getDamage()
{
	return DAMAGE;
}