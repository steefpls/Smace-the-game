//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F	

#include "ship.h"
#include <string>

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

	damageTimer = shipNS::DMG_TIMER;
	dashTimer = shipNS::DASH_TIMER;
	missileTimer = shipNS::MISSILE_TIMER;
	bulletTimer = shipNS::BULLET_TIMER;
	mineTimer = shipNS::MINE_TIMER;
	blackholeTimer = shipNS::BLACKHOLE_TIMER;
	particlesTimer = shipNS::PARTICLES_TIMER;
	blackholesuccmultiplier = shipNS::BLACK_HOLE_SUCC_MULTIPLIER;

	//radius = shipNS::WIDTH / 2.0;
	shieldOn = false;
	mass = shipNS::MASS;
	
	collisionType = entityNS::ROTATED_BOX;
	edge.left = -spriteData.width / 2;
	edge.right = spriteData.width / 2;
	edge.top = -spriteData.height / 2;
	edge.bottom = spriteData.height / 2;
	damagemultiplier = getKnockBack();
	prevhp = shipNS::HP;
	hp = shipNS::HP;
	maxhp = shipNS::MAX_HP;

	lifeCount = shipNS::LIFE_COUNT;
	//damageResistance = shipNS::DAMAGE_RESISTANCE;
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

	damagemultiplier = getKnockBack();
	if (hp < 0)
	{
		hp = 0;
	}
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
	if (RotationRate > shipNS::ROTATION_RATE_CAP)
	{
		RotationRate = shipNS::ROTATION_RATE_CAP;
	}
	if (RotationRate < -shipNS::ROTATION_RATE_CAP)
	{
		RotationRate = -shipNS::ROTATION_RATE_CAP;
	}


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
		velocity.x += sin(spriteData.angle) * x_acc * frameTime;
		velocity.y -= cos(spriteData.angle) * y_acc * frameTime;		//Sets the ship X and Y speed based on angle
	}

	if (input->isKeyDown(player1Down)) //If the S key is held
	{
		velocity.x -= sin(spriteData.angle) * x_acc * frameTime;
		velocity.y += cos(spriteData.angle) * y_acc * frameTime;		//Sets the ship X and Y speed based on angle
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

	if (prevhp > hp || damageTimer > 0)
	{
		currentFrame = 1;
		damageTimer = shipNS::MAX_DMG_TIMER;
	}
	else currentFrame = 0;

	//================================================= SHIP TIMERS =================================================
	if (damageTimer > 0)
	{
		damageTimer -= 1.0f * frameTime;
	}

	if (dashTimer > 0)		//If timer is larger than 0
	{
		dashTimer -= 1.0f * frameTime; //Timer goes down by 1 per second
	}

	if (missileTimer > 0)
	{
		missileTimer-= 1.0f * frameTime;
	}

	if (bulletTimer > 0)
	{ 
		bulletTimer -= 1.0f * frameTime;
	}

	if (mineTimer > 0)
	{
		mineTimer -= 1.0f * frameTime;
	}

	if (blackholeTimer > 0)
	{
		blackholeTimer -= 1.0f * frameTime;
	}

	if (particlesTimer > 0)
	{
		particlesTimer -= 1.0f*frameTime;
	}


	//SHIP LOCATION UPDATE

	spriteData.x += (velocity.x  * frameTime); // Update Ship X location
	spriteData.y += (velocity.y  * frameTime); // Update Ship Y location

	prevhp = hp;
}

void Ship::spawnmissile()
{
	missileList.push_back (new Missile());
	missileTimer = shipNS::MAX_MISSILE_TIMER;
}

void Ship::spawnbullet()
{
	bulletList.push_back(new Bullet());
	bulletTimer = shipNS::MAX_BULLET_TIMER;
}

void Ship::spawnmine()
{
	mineList.push_back(new Mine());
	mineTimer = shipNS::MAX_MINE_TIMER;
}

void Ship::spawnblackhole()
{
	blackholeList.push_back(new Blackhole());
	blackholeTimer = shipNS::MAX_BLACKHOLE_TIMER;
}

void Ship::spawnparticles()
{
	particleList.push_back(new Particles);
	particlesTimer = shipNS::MAX_PARTICLES_TIMER;
}

void Ship::setMissileXY()
{
	missileList[missileList.size() - 1]->setX(getCenterX() - ((missileList[missileList.size() - 1]->getWidth())*(missileList[missileList.size() - 1]->getScale()) / 2));
	missileList[missileList.size() - 1]->setY(getCenterY() - ((missileList[missileList.size() - 1]->getHeight())*(missileList[missileList.size() - 1]->getScale()) / 2));
	missileList[missileList.size() - 1]->setAngle(spriteData.angle);
}

void Ship::setBulletXY(double b)
{
	bulletList[bulletList.size() - 1]->setX(getCenterX() - ((bulletList[bulletList.size() - 1]->getWidth())*(bulletList[bulletList.size() - 1]->getScale()) / 2));
	bulletList[bulletList.size() - 1]->setY(getCenterY() - ((bulletList[bulletList.size() - 1]->getHeight())*(bulletList[bulletList.size() - 1]->getScale()) / 2));
	bulletList[bulletList.size() - 1]->setAngle(spriteData.angle+((b/360)*2*PI));
	
	bulletList[bulletList.size() - 1]->setVelocityX(sin(bulletList[bulletList.size() - 1]->getRadians())*bulletList[bulletList.size() - 1]->getVelocityX());
	bulletList[bulletList.size() - 1]->setVelocityY(-cos(bulletList[bulletList.size() - 1]->getRadians())*bulletList[bulletList.size() - 1]->getVelocityY());
}

void Ship::setMineXY()
{
	mineList[mineList.size() - 1]->setX(getCenterX() - ((mineList[mineList.size() - 1]->getWidth())*(mineList[mineList.size() - 1]->getScale()) / 2));
	mineList[mineList.size() - 1]->setY(getCenterY() - ((mineList[mineList.size() - 1]->getHeight())*(mineList[mineList.size() - 1]->getScale()) / 2));
	mineList[mineList.size() - 1]->setAngle(spriteData.angle);

	mineList[mineList.size() - 1]->setVelocityX(mineList[mineList.size() - 1]->getVelocityX()*sin(mineList[mineList.size() - 1]->getRadians()));
	mineList[mineList.size() - 1]->setVelocityY(mineList[mineList.size() - 1]->getVelocityY()*-cos(mineList[mineList.size() - 1]->getRadians()));

	mineList[mineList.size() - 1]->setVelocityY(mineList[mineList.size() - 1]->getVelocityY() + getVelocityY());
	mineList[mineList.size() - 1]->setVelocityX(mineList[mineList.size() - 1]->getVelocityX() + getVelocityX());
}

void Ship::setBlackholeXY()
{
	blackholeList[blackholeList.size() - 1]->setX(getCenterX() - ((blackholeList[blackholeList.size() - 1]->getWidth())*(blackholeList[blackholeList.size() - 1]->getScale()) / 2));
	blackholeList[blackholeList.size() - 1]->setY(getCenterY() - ((blackholeList[blackholeList.size() - 1]->getHeight())*(blackholeList[blackholeList.size() - 1]->getScale()) / 2));
	blackholeList[blackholeList.size() - 1]->setAngle(spriteData.angle);

	blackholeList[blackholeList.size() - 1]->setVelocityX(blackholeList[blackholeList.size() - 1]->getVelocityX()*sin(blackholeList[blackholeList.size() - 1]->getRadians()));
	blackholeList[blackholeList.size() - 1]->setVelocityY(blackholeList[blackholeList.size() - 1]->getVelocityY()*-cos(blackholeList[blackholeList.size() - 1]->getRadians()));
}

void Ship::setParticlesXY()
{
	particleList[particleList.size() - 1]->setX(getCenterX() - ((particleList[particleList.size() - 1]->getWidth())*(particleList[particleList.size() - 1]->getScale()) / 2));
	particleList[particleList.size() - 1]->setY(getCenterY() - ((particleList[particleList.size() - 1]->getHeight())*(particleList[particleList.size() - 1]->getScale()) / 2));
	particleList[particleList.size() - 1]->setAngle(rand() % 359 + 1);
	
	particleList[particleList.size() - 1]->setVelocityX(particleList[particleList.size() - 1]->getVelocityX()*sin(particleList[particleList.size() - 1]->getRadians()));
	particleList[particleList.size() - 1]->setVelocityY(particleList[particleList.size() - 1]->getVelocityY()*sin(particleList[particleList.size() - 1]->getRadians()));
	
}

int Ship::getmaxmines()
{
	return shipNS::MAX_MINES;
}

float Ship::getDamageTimer()
{
	return damageTimer;
}

float Ship::getmissiletimer()
{
	return missileTimer;
}

float Ship::getbullettimer()
{
	return bulletTimer;
}

float Ship::getminetimer()
{
	return mineTimer;
}

float Ship::getblackholetimer()
{
	return blackholeTimer;
}

float Ship::getparticlestimer()
{
	return particlesTimer;
}

void Ship::topbottomrotatebounce()	//rotation when hitting top and bottom walls
{
	if (velocity.x > 0)	
	{
		RotationRate += getKnockBack() * 300 * (velocity.y / 200);	 
	}
	else
	{
		RotationRate -= getKnockBack() * 300 * (velocity.y / 200);
	}
}
void Ship::leftrightrotatebounce()	//rotation when hitting left and right walls 
{
	if (velocity.y > 0)	
	{
		RotationRate -= getKnockBack() * 300 * (velocity.x / 200);
	}
	else
	{
		RotationRate += getKnockBack() * 300 * (velocity.x / 200);
	}
}

void Ship::dash()
{
	if (dashTimer <= 0)
	{
		velocity.x += sin(spriteData.angle) * shipNS::BOOST_AMT;
		velocity.y -= cos(spriteData.angle) * shipNS::BOOST_AMT;
		dashTimer = shipNS::MAX_DASH_TIMER;
	}
}

void Ship::boost(bool b)
{
	if (b)
	{
		x_acc = shipNS::BOOSTED_X_ACC;
		y_acc = shipNS::BOOSTED_Y_ACC;
	}
	else
	{
		x_acc = shipNS::ORIGINAL_X_ACC;
		y_acc = shipNS::ORIGINAL_Y_ACC;
	}
}

int Ship::getnoofbullets()
{
	return noOfBullets;
}

double Ship::getdegreespread()
{
	return bulletDegreeSpread;
}

float Ship::getDamageResistance()
{
	return damageResistance;
}

double Ship::getKnockBack()
{
	return 3.00 - (hp / maxhp) * 2.00;
}

string Ship::getdamagestring()
{
	double damagestring = getKnockBack()*100.0-100;
	string str = std::to_string(damagestring);
	return str + "%";
}

float Ship::getLifeCount()
{
	return lifeCount;
}

void Ship::setLifeCount(float lc)
{
	lifeCount = lc;
}

double Ship::getMaxHP()
{
	return maxhp;
}

double Ship::getblackholesuckmultiplier()
{
	return blackholesuccmultiplier;
}

void Ship::setPrevHP(int hp)
{
	prevhp = hp;
}
