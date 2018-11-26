#include "missile.h"
using namespace missileNS;

//=============================================================================
// default constructor
//=============================================================================
Missile::Missile() : Entity()
{
	spriteData.width = WIDTH;           // size of Ship1
	spriteData.height = HEIGHT;
	spriteData.x = X;                   // location on screen
	spriteData.y = Y;
	spriteData.rect.bottom = HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = WIDTH;
	velocity.x = X_SPEED;                             // velocity X
	velocity.y = Y_SPEED;                             // velocity Y
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

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Missile::update(float frameTime)
{
	Entity::update(frameTime);

//	//------------Handle Ship Rotation on Key Press--------------
//
//	//Keeping the ranges of the angle to 0<x<360
//	while (spriteData.angle < 0)
//	{
//		spriteData.angle += 2 * PI;			//Calculation done in radians
//	}
//
//	while (spriteData.angle > 2 * PI)
//	{
//		spriteData.angle -= 2 * PI;			//Calculation done in radians
//	}
//
//	//----------------------------------------------------------- Handling max rotation rate ---------------------------------------------
//
//	//if (ROTATION_RATE < MAX_ROTATION_RATE) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
//	//{
//	//	if (input->isKeyDown(ship1Right)) //and the D key is held
//	//	{
//	//		ROTATION_RATE += ROTATION_ACC_RATE * frameTime;	//Add rotation speed
//	//	}
//	//}
//
//	//if (ROTATION_RATE > -MAX_ROTATION_RATE) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
//	//{
//	//	if (input->isKeyDown(ship1Left)) //And the A key is held
//	//	{
//	//		ROTATION_RATE -= ROTATION_ACC_RATE * frameTime; //Add rotation speed
//	//	}
//	//}
//
//	//================================================= Ship Rotation Drag Handling =====================================
//
////	if (!input->isKeyDown(ship1Left) && !input->isKeyDown(ship1Right))			//If A or D is not being pressed
////	{
////		if (shipNS::ROTATION_RATE < -shipNS::ROTATION_DRAG * frameTime)			//if ship is rotating counter clockwise
////		{
////			shipNS::ROTATION_RATE += shipNS::ROTATION_DRAG * frameTime;			//Add clockwise drag
////		}
////
////		else if (shipNS::ROTATION_RATE > shipNS::ROTATION_DRAG * frameTime)			//if ship is rotating clockwise
////		{
////			shipNS::ROTATION_RATE -= shipNS::ROTATION_DRAG * frameTime;			//Add counter clockwise drag
////		}
////		else
////		{
////			shipNS::ROTATION_RATE = 0.0f;										//If speed is less than drag, set speed to 0
////		}
////	}
//
//
//	spriteData.angle = (spriteData.angle + ROTATION_RATE / 360 * 2 * PI * frameTime); // Final update ship rotation
//
//	//===================================== SHIP MOVEMENT =============================================
//
//	//if (input->isKeyDown(ship1Up)) //If the W key is held
//	//{
//	//	velocity.x += sin(spriteData.angle) * X_ACC * frameTime;
//	//	velocity.y -= cos(spriteData.angle) * Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
//	//}
//
//	//if (input->isKeyDown(ship1Down)) //If the S key is held
//	//{
//	//	velocity.x -= sin(spriteData.angle) * shipNS::X_ACC * frameTime;
//	//	velocity.y += cos(spriteData.angle) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
//	//}
//
//
//	velocity.x = velocity.x - ((1 - DRAG) *velocity.x) * frameTime;
//	velocity.y = velocity.y - ((1 - DRAG) *velocity.y) * frameTime;   //Implementation of "Air" Resistance
//
//
//// ============================================= Bounce off walls/Wall collision ==========================================================
//// X BASED COLLISION
//	if (spriteData.x > GAME_WIDTH - (WIDTH * SHIP_SCALE) + 1)    // if hit right screen edge
//	{
//		if (velocity.y > 0)	//Add random speed based on spin
//		{
//			ROTATION_RATE += 300 * (velocity.x / 400);		//add rotation based on X movement  (Random amount | Starting point)
//		}
//		else
//		{
//			ROTATION_RATE -= 300 * (velocity.x / 400);		//add random rotation based on X movement  (Random amount | Starting point)
//		}
//
//		spriteData.x = GAME_WIDTH - WIDTH;    // position at right screen edge
//		velocity.x = (-velocity.x) * DAMAGE_MULTIPLIER;                   // reverse X direction, Add knockback
//
//	}
//
//	else if (spriteData.x < 0)                    // else if hit left screen edge
//	{
//		if (velocity.y > 0)	//Add random speed based on spin
//		{
//			ROTATION_RATE += 300 * (velocity.x / 400);		//add rotation based on X movement  (Random amount | Starting point)
//		}
//		else
//		{
//			ROTATION_RATE -= 300 * (velocity.x / 400);		//add rotation based on X movement  (Random amount | Starting point)
//		}
//		spriteData.x = 0;                           // position at left screen edge
//		velocity.x = (-velocity.x) * DAMAGE_MULTIPLIER;                   // reverse X direction and add knockback
//	}
//
//
//	// Y BASED COLLISION
//	if (spriteData.y > GAME_HEIGHT - HEIGHT * SHIP_SCALE)  // if hit bottom screen edge
//	{
//		if (velocity.x > 0)	//Add random speed based on spin
//		{
//			ROTATION_RATE -= 300 * (velocity.y / 400);		//add rotation based on Y movement  
//		}
//		else
//		{
//			ROTATION_RATE += 300 * (velocity.y / 400);		//add rotation based on Y movement  
//		}
//		spriteData.y = GAME_HEIGHT - HEIGHT;  // position at bottom screen edge
//		velocity.y = (-velocity.y) * DAMAGE_MULTIPLIER;                   // reverse Y direction and add knockback
//	}
//	else if (spriteData.y < 0)                    // else if hit top screen edge
//	{
//		if (velocity.x > 0)	//Add random speed based on spin
//		{
//			ROTATION_RATE -= 300 * (velocity.y / 400);		//add rotation based on Y movement
//		}
//		else
//		{
//			ROTATION_RATE += 300 * (velocity.y / 400);		//add rotation based on Y movement 
//		}
//		spriteData.y = 0;                           // position at top screen edge
//		velocity.y = (-velocity.y) * DAMAGE_MULTIPLIER;                   // reverse Y direction and add knockback
//	}
//
//	//================================================= SHIP DASH TIMER =================================================
//	if (DASH_TIMER > 0)		//If timer is larger than 0
//	{
//		DASH_TIMER -= 1.0f * frameTime; //Timer goes down by 1 per second
//
//	}
//
//	//if (input->isKeyDown(SPACE) && DASH_TIMER <= 0)
//	//{
//	//	velocity.x += sin(spriteData.angle) * BOOST_AMT;
//	//	velocity.y -= cos(spriteData.angle) * BOOST_AMT;
//	//	DASH_TIMER = MAX_DASH_TIMER;
//
//	//}
//
//
//	//SHIP LOCATION UPDATEb
//	spriteData.x += (velocity.x * spriteData.scale * frameTime); // Update Ship X location
//	spriteData.y += (velocity.y * spriteData.scale * frameTime); // Update Ship Y location

}