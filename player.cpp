#include "player.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
}

//=============================================================================
// Initialize the Player.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);

	//----------------------------------------------------------- Handling max rotation rate ---------------------------------------------

	if (shipNS::ROTATION_RATE < shipNS::MAX_ROTATION_RATE) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
	{
		if (input->isKeyDown(playerNS::player1Right)) //and the D key is held
		{
			shipNS::ROTATION_RATE += shipNS::ROTATION_ACC_RATE * frameTime;	//Add rotation speed
		}
	}

	if (shipNS::ROTATION_RATE > -shipNS::MAX_ROTATION_RATE) //if ship is rotating at a speed less than the MAX_ROTATION_RATE
	{
		if (input->isKeyDown(playerNS::player1Left)) //And the A key is held
		{
			shipNS::ROTATION_RATE -= shipNS::ROTATION_ACC_RATE * frameTime; //Add rotation speed
		}
	}

	//================================================= Ship Rotation Drag Handling =====================================

	if (!input->isKeyDown(playerNS::player1Left) && shipNS::ROTATION_RATE < -shipNS::ROTATION_DRAG * frameTime)			//If A is not being pressed and ship is rotating counter clockwise
	{


		shipNS::ROTATION_RATE += shipNS::ROTATION_DRAG * frameTime;			//Add clockwise drag


	}
	else if (!input->isKeyDown(playerNS::player1Right) && shipNS::ROTATION_RATE > shipNS::ROTATION_DRAG * frameTime)	//if D is not being pressed and ship is rotating clockwise
	{
		shipNS::ROTATION_RATE -= shipNS::ROTATION_DRAG * frameTime;			//Add counter clockwise drag
	}
	else if (!input->isKeyDown(playerNS::player1Left) && !input->isKeyDown(playerNS::player1Right) && shipNS::ROTATION_RATE < shipNS::ROTATION_DRAG * frameTime && shipNS::ROTATION_RATE > -shipNS::ROTATION_DRAG * frameTime)
	{
		shipNS::ROTATION_RATE = 0.0f;										//If speed is less than drag, set speed to 0
	}


	spriteData.angle = (spriteData.angle + shipNS::ROTATION_RATE / 360 * 2 * PI * frameTime); // Final update ship rotation

	//===================================== SHIP MOVEMENT =============================================

	if (input->isKeyDown(playerNS::player1Up)) //If the W key is held
	{
		velocity.x += sin(spriteData.angle) * shipNS::X_ACC * frameTime;
		velocity.y -= cos(spriteData.angle) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}

	if (input->isKeyDown(playerNS::player1Down)) //If the S key is held
	{
		velocity.x -= sin(spriteData.angle) * shipNS::X_ACC * frameTime;
		velocity.y += cos(spriteData.angle) * shipNS::Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}


	velocity.x = velocity.x - ((1 - shipNS::DRAG) *velocity.x) * frameTime;
	velocity.y = velocity.y - ((1 - shipNS::DRAG) *velocity.y) * frameTime;   //Implementation of "Air" Resistance
}

void Player::draw()
{
	Image::draw();
}