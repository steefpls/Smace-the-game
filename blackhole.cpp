//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       your name
//  Student Number:     your student number

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
	maxscale = MAX_SCALE;
	shrinkrate = BLACKHOLE_SHRINK_RATE;
	growthrate = BLACKHOLE_GROWTH_RATE;
	lifetime = LIFETIME;
	maxlifetime = MAX_LIFETIME;
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

	//Keeping the ranges of the angle to 0<x<360
	while (spriteData.angle < 0)
	{
		spriteData.angle += 2 * PI;			//Calculation done in radians
	}

	while (spriteData.angle > 2 * PI)
	{
		spriteData.angle -= 2 * PI;			//Calculation done in radians
	}
	//Scale update
	lifetime += frameTime;
	if (spriteData.scale < maxscale && lifetime < maxlifetime)
	{
		spriteData.scale += growthrate *frameTime;
		spriteData.x = spriteData.x - (growthrate  * spriteData.width / 2 * frameTime) ;
		spriteData.y = spriteData.y - (growthrate  * spriteData.height / 2 * frameTime) ;
	}

	//lifetime update

	if (lifetime >= maxlifetime)
	{
		spriteData.scale -= growthrate * frameTime	*	10;
		spriteData.x = spriteData.x + (growthrate  * spriteData.width / 2 * frameTime*10);
		spriteData.y = spriteData.y + (growthrate  * spriteData.height / 2 * frameTime*10);
	}

	//bullet direction update
	if (velocity.x >= 0)
	{
		spriteData.angle = atan(velocity.y / velocity.x) + PI / 2;
	}
	else
	{
		spriteData.angle = atan(velocity.y / velocity.x) - PI / 2;
	}

	//Black hole Drag
	velocity.x = velocity.x - ((1 - blackholeNS::DRAG) *velocity.x) * frameTime;
	velocity.y = velocity.y - ((1 - blackholeNS::DRAG) *velocity.y) * frameTime;   //Implementation of "Air" Resistance

	//SHIP LOCATION UPDATE
	
	spriteData.x += (velocity.x  * frameTime); // Update Ship X location
	spriteData.y += (velocity.y  * frameTime); // Update Ship Y location

}
void Blackhole::setAngle(float a)
{
	spriteData.angle = a;
}

float Blackhole::getDamage()
{
	return DAMAGE;
}

float Blackhole::getsuckstrength()
{
	return blackholeNS::BLACKHOLE_SUCK_STRENGTH;
}