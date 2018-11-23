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
	shield.setLoop(true);                  // do not loop animation
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
		spriteData.angle += 2*PI;			//Calculation done in radians
	}
	
	while (spriteData.angle > 2 * PI)
	{
		spriteData.angle -= 2 * PI;			//Calculation done in radians
	}

	//----------------------------------------------------------- Handling max rotation rate ---------------------------------------------

	if (shipNS::ROTATION_RATE < shipNS::MAX_ROTATION_RATE) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
	{
		if (input->isKeyDown(ship1Right)) //and the D key is held
		{
			shipNS::ROTATION_RATE += shipNS::ROTATION_ACC_RATE * frameTime;	//Add rotation speed
		}
	}

	if (shipNS::ROTATION_RATE > -shipNS::MAX_ROTATION_RATE) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
	{
		if (input->isKeyDown(ship1Left)) //And the A key is held
		{
			shipNS::ROTATION_RATE -= shipNS::ROTATION_ACC_RATE * frameTime; //Add rotation speed
		}
	}
	
	//================================================= Ship Rotation Drag Handling =====================================

	if (!input->isKeyDown(ship1Left) && !input->isKeyDown(ship1Right))			//If A or D is not being pressed
	{
		if (shipNS::ROTATION_RATE < -shipNS::ROTATION_DRAG * frameTime)			//if ship is rotating counter clockwise
		{
			shipNS::ROTATION_RATE += shipNS::ROTATION_DRAG * frameTime;			//Add clockwise drag
		}

		else if (shipNS::ROTATION_RATE > shipNS::ROTATION_DRAG * frameTime)			//if ship is rotating clockwise
		{
			shipNS::ROTATION_RATE -= shipNS::ROTATION_DRAG * frameTime;			//Add counter clockwise drag
		}
		else
		{
			shipNS::ROTATION_RATE = 0.0f;										//If speed is less than drag, set speed to 0
		}
	}


	spriteData.angle=(spriteData.angle + shipNS::ROTATION_RATE / 360 * 2 * PI * frameTime); // Final update ship rotation
	
	//===================================== SHIP MOVEMENT =============================================

		if (input->isKeyDown(ship1Up)) //If the W key is held
		{
			shipNS::X_SPEED += sin(spriteData.angle ) * shipNS::X_ACC * frameTime ;		
			shipNS::Y_SPEED -= cos(spriteData.angle ) * shipNS::Y_ACC * frameTime ;		//Sets the ship X and Y speed based on angle
		}

		if (input->isKeyDown(ship1Down)) //If the S key is held
		{
			shipNS::X_SPEED -= sin(spriteData.angle) * shipNS::X_ACC * frameTime;
			shipNS::Y_SPEED += cos(spriteData.angle) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
		}


	shipNS::X_SPEED = shipNS::X_SPEED - ((1 - shipNS::DRAG) *shipNS::X_SPEED) * frameTime;
	shipNS::Y_SPEED = shipNS::Y_SPEED - ((1 - shipNS::DRAG) *shipNS::Y_SPEED) * frameTime;   //Implementation of "Air" Resistance


	// ============================================= Bounce off walls/Wall collision ==========================================================
	// X BASED COLLISION
	if (spriteData.x > GAME_WIDTH - (shipNS::WIDTH * shipNS::SHIP_SCALE) + 1)    // if hit right screen edge
	{
		if (shipNS::Y_SPEED > 0)	//Add random speed based on spin
		{
			shipNS::ROTATION_RATE += 300 * (shipNS::X_SPEED / 400);		//add rotation based on X movement  (Random amount | Starting point)
		}
		else
		{
			shipNS::ROTATION_RATE -= 300 * (shipNS::X_SPEED / 400);		//add random rotation based on X movement  (Random amount | Starting point)
		}

		spriteData.x = GAME_WIDTH - shipNS::WIDTH;    // position at right screen edge
		shipNS::X_SPEED = (-shipNS::X_SPEED) * shipNS::DAMAGE_MULTIPLIER;                   // reverse X direction, Add knockback

	}

	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		if (shipNS::Y_SPEED > 0)	//Add random speed based on spin
		{
			shipNS::ROTATION_RATE += 300 * (shipNS::X_SPEED / 400);		//add rotation based on X movement  (Random amount | Starting point)
		}
		else
		{
			shipNS::ROTATION_RATE -= 300 * (shipNS::X_SPEED / 400);		//add rotation based on X movement  (Random amount | Starting point)
		}
		spriteData.x = 0;                           // position at left screen edge
		shipNS::X_SPEED = (-shipNS::X_SPEED) * shipNS::DAMAGE_MULTIPLIER;                   // reverse X direction and add knockback
	}


	// Y BASED COLLISION
	if (spriteData.y > GAME_HEIGHT - shipNS::HEIGHT * shipNS::SHIP_SCALE)  // if hit bottom screen edge
	{
		if (shipNS::X_SPEED > 0)	//Add random speed based on spin
		{
			shipNS::ROTATION_RATE -= 300 * (shipNS::Y_SPEED / 400);		//add rotation based on Y movement  
		}
		else
		{
			shipNS::ROTATION_RATE += 300 * (shipNS::Y_SPEED / 400);		//add rotation based on Y movement  
		}
		spriteData.y = GAME_HEIGHT - shipNS::HEIGHT;  // position at bottom screen edge
		shipNS::Y_SPEED = (-shipNS::Y_SPEED) * shipNS::DAMAGE_MULTIPLIER;                   // reverse Y direction and add knockback
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		if (shipNS::X_SPEED > 0)	//Add random speed based on spin
		{
			shipNS::ROTATION_RATE -= 300 * (shipNS::Y_SPEED / 400);		//add rotation based on Y movement
		}
		else
		{
			shipNS::ROTATION_RATE += 300 * (shipNS::Y_SPEED / 400);		//add rotation based on Y movement 
		}
		spriteData.y = 0;                           // position at top screen edge
		shipNS::Y_SPEED = (-shipNS::Y_SPEED) * shipNS::DAMAGE_MULTIPLIER;                   // reverse Y direction and add knockback
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

	//================================================= SHIP DASH TIMER =================================================
	if (shipNS::DASH_TIMER > 0)		//If timer is larger than 0
	{
		shipNS::DASH_TIMER -= 1.0f * frameTime; //Timer goes down by 1 per second
		
	}

	if (input->isKeyDown(SPACE) && shipNS::DASH_TIMER<=0)
	{
		shipNS::X_SPEED += sin(spriteData.angle) * shipNS::BOOST_AMT ;
		shipNS::Y_SPEED -= cos(spriteData.angle) * shipNS::BOOST_AMT ;
		shipNS::DASH_TIMER = shipNS::MAX_DASH_TIMER;
		
	}


	//SHIP LOCATION UPDATEb
	spriteData.x += (shipNS::X_SPEED * spriteData.scale * frameTime); // Update Ship X location
	spriteData.y += (shipNS::Y_SPEED * spriteData.scale * frameTime); // Update Ship Y location

}

//=============================================================================
// damage
//=============================================================================
void Ship::damage(WEAPON weapon)
{
	shieldOn = true;
}