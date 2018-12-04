#include "ship.h"

//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
	spriteData.scale = shipNS::SCALE;
	spriteData.width = shipNS::WIDTH;           // size of Ship1
	spriteData.height = shipNS::HEIGHT;
	spriteData.x = shipNS::X;                   // location on screen
	spriteData.y = shipNS::Y;
	spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = shipNS::WIDTH;
	velocity.x = shipNS::X_SPEED;                             // velocity X
	velocity.y = shipNS::Y_SPEED;                             // velocity Y
	frameDelay = shipNS::SHIP_ANIMATION_DELAY;
	startFrame = shipNS::SHIP_START_FRAME;     // first frame of ship animation
	endFrame = shipNS::SHIP_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	damage = shipNS::DAMAGE_MULTIPLIER;
	
	
	//radius = shipNS::WIDTH / 2.0;
	shieldOn = false;
	mass = shipNS::MASS;
	
	collisionType = entityNS::ROTATED_BOX;
	edge.left = -spriteData.width / 2;
	edge.right = spriteData.width / 2;
	edge.top = -spriteData.height / 2;
	edge.bottom = spriteData.height / 2;
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
		spriteData.angle += 2 * PI;			//Calculation done in radians
	}

	while (spriteData.angle > 2 * PI)
	{
		spriteData.angle -= 2 * PI;			//Calculation done in radians
	}

	//----------------------------------------------------------- Handling max rotation rate ---------------------------------------------

	if (RotationRate < MaxRotationRate) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
	{
		if (input->isKeyDown(player1Right)) //and the D key is held
		{
			RotationRate += RotationAccRate * frameTime;	//Add rotation speed
		}
	}

	if (RotationRate > -MaxRotationRate) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
	{
		if (input->isKeyDown(player1Left)) //And the A key is held
		{
			RotationRate -= RotationAccRate * frameTime; //Add rotation speed
		}
	}

	//================================================= Ship Rotation Drag Handling =====================================

	if (!input->isKeyDown(player1Left) && RotationRate < -RotationDrag * frameTime)			//If A is not being pressed and ship is rotating counter clockwise
	{
		RotationRate += RotationDrag * frameTime;			//Add clockwise drag
	}
	else if (!input->isKeyDown(player1Right) && RotationRate > RotationDrag * frameTime)	//if D is not being pressed and ship is rotating clockwise
	{
		RotationRate -= RotationDrag * frameTime;			//Add counter clockwise drag
	}
	else if (!input->isKeyDown(player1Left) && !input->isKeyDown(player1Right) && RotationRate < RotationDrag * frameTime && RotationRate > -RotationDrag * frameTime)
	{
		RotationRate = 0.0f;										//If speed is less than drag, set speed to 0
	}


	spriteData.angle = (spriteData.angle + RotationRate / 360 * 2 * PI * frameTime); // Final update ship rotation

	//===================================== SHIP MOVEMENT =============================================

	if (input->isKeyDown(player1Up)) //If the W key is held
	{
		velocity.x += sin(spriteData.angle) * shipNS::X_ACC * frameTime;
		velocity.y -= cos(spriteData.angle) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}

	if (input->isKeyDown(player1Down)) //If the S key is held
	{
		velocity.x -= sin(spriteData.angle) * shipNS::X_ACC * frameTime;
		velocity.y += cos(spriteData.angle) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}


	velocity.x = velocity.x - ((1 - shipNS::DRAG) *velocity.x) * frameTime;
	velocity.y = velocity.y - ((1 - shipNS::DRAG) *velocity.y) * frameTime;   //Implementation of "Air" Resistance




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



	if (shipNS::MISSILE_TIMER > 0)
	{
		shipNS::MISSILE_TIMER -= 1.0f * frameTime;
	}

	if (shipNS::BULLET_TIMER > 0)
	{ 
		shipNS::BULLET_TIMER -= 1.0f * frameTime;
	}

	if (shipNS::MINE_TIMER > 0)
	{
		shipNS::MINE_TIMER -= 1.0f * frameTime;
	}

	//SHIP LOCATION UPDATE

	spriteData.x += (velocity.x  * frameTime); // Update Ship X location
	spriteData.y += (velocity.y  * frameTime); // Update Ship Y location
}

void Ship::spawnmissile()
{
	missileList.push_back (new Missile());
	shipNS::MISSILE_TIMER = shipNS::MAX_MISSILE_TIMER;
}

void Ship::spawnbullet()
{
	bulletList.push_back(new Bullet());
	shipNS::BULLET_TIMER = shipNS::MAX_BULLET_TIMER;
}

void Ship::spawnmine()
{
	mineList.push_back(new Mine());
	shipNS::MINE_TIMER = shipNS::MAX_MINE_TIMER;
}

void Ship::setMissileXY()
{
	missileList[missileList.size() - 1]->setX(getCenterX() - ((missileList[missileList.size() - 1]->getWidth())*(missileList[missileList.size() - 1]->getScale()) / 2));
	missileList[missileList.size() - 1]->setY(getCenterY() - ((missileList[missileList.size() - 1]->getHeight())*(missileList[missileList.size() - 1]->getScale()) / 2));
	missileList[missileList.size() - 1]->setAngle(spriteData.angle);
}

void Ship::setBulletXY()
{
	bulletList[bulletList.size() - 1]->setX(getCenterX() - ((bulletList[bulletList.size() - 1]->getWidth())*(bulletList[bulletList.size() - 1]->getScale()) / 2));
	bulletList[bulletList.size() - 1]->setY(getCenterY() - ((bulletList[bulletList.size() - 1]->getHeight())*(bulletList[bulletList.size() - 1]->getScale()) / 2));
	bulletList[bulletList.size() - 1]->setAngle(spriteData.angle);
}

void Ship::setMineXY()
{
	mineList[mineList.size() - 1]->setX(getCenterX() - ((mineList[mineList.size() - 1]->getWidth())*(mineList[mineList.size() - 1]->getScale()) / 2));
	mineList[mineList.size() - 1]->setY(getCenterY() - ((mineList[mineList.size() - 1]->getHeight())*(mineList[mineList.size() - 1]->getScale()) / 2));
	mineList[mineList.size() - 1]->setAngle(spriteData.angle);

	mineList[mineList.size() - 1]->setVelocityX(mineList[mineList.size() - 1]->getVelocityX()*sin(mineList[mineList.size() - 1]->getRadians()));
	mineList[mineList.size() - 1]->setVelocityY(mineList[mineList.size() - 1]->getVelocityY()*-cos(mineList[mineList.size() - 1]->getRadians()));
}

int Ship::getmaxmines()
{
	return shipNS::MAX_MINES;
}

float Ship::getmissiletimer()
{
	return shipNS::MISSILE_TIMER;
}

float Ship::getbullettimer()
{
	return shipNS::BULLET_TIMER;
}

float Ship::getminetimer()
{
	return shipNS::MINE_TIMER;
}

void Ship::topbottomrotatebounce()	//rotation when hitting top and bottom walls
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
void Ship::leftrightrotatebounce()	//rotation when hitting left and right walls 
{
	if (velocity.y > 0)	
	{
		RotationRate -= damage * 300 * (velocity.x / 200);
	}
	else
	{
		RotationRate += damage * 300 * (velocity.x / 200);
	}
}

void Ship::dash()
{
	if (shipNS::DASH_TIMER <= 0)
	{
		velocity.x += sin(spriteData.angle) * shipNS::BOOST_AMT;
		velocity.y -= cos(spriteData.angle) * shipNS::BOOST_AMT;
		shipNS::DASH_TIMER = shipNS::MAX_DASH_TIMER;

	}
}

void Ship::boost(bool b)
{
	if (b)
	{
		shipNS::X_ACC = shipNS::BOOSTED_X;
		shipNS::Y_ACC = shipNS::BOOSTED_Y;
	}
	else
	{
		shipNS::X_ACC = shipNS::ORIGINAL_X;
		shipNS::Y_ACC = shipNS::ORIGINAL_Y;
	}
}