#include "ship.h"

//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
	spriteData.width = shipNS::WIDTH;           // size of Ship1
	spriteData.height = shipNS::HEIGHT;
	spriteData.x = shipNS::X;                   // location on screen
	spriteData.y = shipNS::Y;
	spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = shipNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = shipNS::SHIP_ANIMATION_DELAY;
	startFrame = shipNS::SHIP1_START_FRAME;     // first frame of ship animation
	endFrame = shipNS::SHIP1_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = shipNS::WIDTH / 2.0;
	shieldOn = false;
	mass = shipNS::MASS;
	collisionType = entityNS::ROTATED_BOX;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ship::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	shield.setFrames(shipNS::SHIELD_START_FRAME, shipNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(shipNS::SHIELD_START_FRAME);
	shield.setFrameDelay(shipNS::SHIELD_ANIMATION_DELAY);
	shield.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Ship::draw()
{
	Image::draw();              // draw ship
	if (shieldOn)
		// draw shield using colorFilter 50% alpha
		shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ship::update(float frameTime)
{
	Entity::update(frameTime);

	//------------Handle Ship Rotation on Key Press--------------

	//Keeping the ranges of the angle to 0<x<360
	while (spriteData.angle < 0) 
	{
		spriteData.angle += 360;
	}
	
	while (spriteData.angle > 360)
	{
		spriteData.angle -= 360;
	}

	if (shipNS::ROTATION_RATE < 240) //if ship is rotating at a speed of less than 5 degrees per frame
	{
		if (input->isKeyDown(ship1Right)) //and the D key is held
		{
			shipNS::ROTATION_RATE += shipNS::ROTATION_ACC_RATE * frameTime;
		}
	}

	if (shipNS::ROTATION_RATE > -240) //if ship is rotating at a speed of less than -5 degrees per frame
	{
		if (input->isKeyDown(ship1Left)) //And the A key is held
		{
			shipNS::ROTATION_RATE -= shipNS::ROTATION_ACC_RATE * frameTime;
		}
	}

	spriteData.angle=(spriteData.angle + shipNS::ROTATION_RATE * frameTime); //update ship rotation

	shipNS::ROTATION_RATE = shipNS::ROTATION_RATE - ((1 - shipNS::ROTATION_DRAG) *shipNS::ROTATION_RATE) * frameTime;// Update ship rotation rate due to air resistance

	if (input->isKeyDown(ship1Up)) //If the W key is held
	{
		shipNS::X_SPEED += sin(spriteData.angle / 360 * 2 * PI) * shipNS::X_ACC * frameTime;
		shipNS::Y_SPEED -= cos(spriteData.angle / 360 * 2 * PI) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}

	if (input->isKeyDown(ship1Down)) //If the S key is held
	{
		shipNS::X_SPEED -= sin(spriteData.angle / 360 * 2 * PI) * shipNS::X_ACC * frameTime;
		shipNS::Y_SPEED += cos(spriteData.angle / 360 * 2 * PI) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}

	//----------------------------------Ship Location Wrapping-------------------------------------
	//SHIP LOCATION UPDATE
	spriteData.x = (spriteData.x + shipNS::X_SPEED * spriteData.scale * frameTime); // Update Ship X location
	spriteData.y = (spriteData.y + shipNS::Y_SPEED * spriteData.scale * frameTime); // Update Ship Y location

	shipNS::X_SPEED = shipNS::X_SPEED - ((1 - shipNS::DRAG) *shipNS::X_SPEED) * frameTime;
	shipNS::Y_SPEED = shipNS::Y_SPEED - ((1 - shipNS::DRAG) *shipNS::Y_SPEED) * frameTime;   //Implementation of "Air" Resistance

	//spriteData.angle += frameTime * shipNS::ROTATION_RATE;  // rotate the ship
	//spriteData.x += frameTime * velocity.x;         // move ship along X 
	//spriteData.y += frameTime * velocity.y;         // move ship along Y

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - shipNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - shipNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - shipNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - shipNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}

	if (shieldOn)
	{
		shield.update(frameTime);
		if (shield.getAnimationComplete())
		{
			shieldOn = false;
			shield.setAnimationComplete(false);
		}
	}
}

//=============================================================================
// damage
//=============================================================================
void Ship::damage(WEAPON weapon)
{
	shieldOn = true;
}