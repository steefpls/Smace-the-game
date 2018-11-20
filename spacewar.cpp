
#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	
		// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// ship
	if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
	ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	ship1.setX(GAME_WIDTH / 4);
	ship1.setY(GAME_HEIGHT / 4);
	//ship1.setVelocity(VECTOR2(shipNS::SPEED, -shipNS::SPEED)); // VECTOR2(X, Y)

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//Scale Nebula to fullscreen
	nebula.setScale(GAME_WIDTH/nebula.getWidth() );

	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	//// ship texture
//if (!shipTexture.initialize(graphics, SHIP_IMAGE))
//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	//// ship
	//if (!ship.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));

	////Ship animation
	//ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames 
	//ship.setCurrentFrame(SHIP_START_FRAME);             // starting frame
	//ship.setFrameDelay(SHIP_ANIMATION_DELAY);

	//// place ship in center left of screen
	//ship.setX(GAME_WIDTH*0.33f - ship.getWidth()*0.5f);
	//ship.setY(GAME_HEIGHT*0.5f - ship.getHeight()*0.5f);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	ship1.update(frameTime); //update ship frames
	if (input->isKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}


	
	//------------Handle Ship Rotation on Key Press--------------

	//Keeping the ranges of the angle to 0<x<360
	/*while (ship1.getDegrees() < 0)
	{
		ship1.setDegrees(ship1.getDegrees() + 360);
	}
	while (ship1.getDegrees() > 360)
	{
		ship1.setDegrees(ship1.getDegrees() - 360);
	}*/

	//if (SHIP1_ROTATION_RATE < 240) //if ship is rotating at a speed of less than 5 degrees per frame
	//{
	//	if (input->isKeyDown(D)) //and the D key is held
	//	{
	//		SHIP1_ROTATION_RATE += SHIP1_ROTATION_ACCELERATION_RATE* frameTime;
	//	}
	//	
	//}

	//if (SHIP1_ROTATION_RATE > -240) //if ship is rotating at a speed of less than -5 degrees per frame
	//{
	//	if (input->isKeyDown(A)) //And the A key is held
	//	{
	//		SHIP1_ROTATION_RATE -= SHIP1_ROTATION_ACCELERATION_RATE* frameTime;
	//	}

	//}
	//ship.setDegrees(ship.getDegrees() + SHIP1_ROTATION_RATE * frameTime); //update ship rotation

	//SHIP1_ROTATION_RATE = SHIP1_ROTATION_RATE - ((1 - SHIP1_ROTATION_DRAG) *SHIP1_ROTATION_RATE) * frameTime;// Update ship rotation rate due to air resistance

	//----------------------------Handle Ship acceleration on Key Press-------------------------------------------

	

	//if (input->isKeyDown(W)) //If the W key is held
	//{
	//	SHIP1_X_SPEED += sin(ship.getDegrees() / 360 * 2 * PI) * SHIP1_X_ACC * frameTime;
	//	SHIP1_Y_SPEED -= cos(ship.getDegrees() / 360 * 2 * PI) * SHIP1_Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	//}

	//if (input->isKeyDown(S)) //If the S key is held
	//{
	//	SHIP1_X_SPEED -= sin(ship.getDegrees() / 360 * 2 * PI) * SHIP1_X_ACC * frameTime;
	//	SHIP1_Y_SPEED += cos(ship.getDegrees() / 360 * 2 * PI) * SHIP1_Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	//}


	//----------------------------------Ship Location Wrapping-------------------------------------
	//SHIP LOCATION UPDATE
	//ship.setX(ship.getX() + SHIP1_X_SPEED * ship.getScale() * frameTime); // Update Ship X location
	//ship.setY(ship.getY() + SHIP1_Y_SPEED * ship.getScale() * frameTime); // Update Ship Y location
	   
	
	//if (ship.getX() > GAME_WIDTH)               // if off screen right
	//{
	//	ship.setX((float)-ship.getWidth()*ship.getScale());     // position off screen left
	//	
	//}
	//if (ship.getX() < -ship.getWidth()*ship.getScale() -1)               // if off screen left
	//{
	//	ship.setX(GAME_WIDTH);     // position off screen right

	//}

	//if (ship.getY() < -ship.getHeight()*ship.getScale() - 1)               // if off screen up
	//{
	//	ship.setY(GAME_HEIGHT);     // position off screen up
	//}
	//if (ship.getY() > GAME_HEIGHT )               // if off screen down
	//{
	//	ship.setY((float)-ship.getHeight()*ship.getScale());	// position off screen Down
	//}

	//SHIP1_X_SPEED = SHIP1_X_SPEED - ((1 - DRAG) *SHIP1_X_SPEED) * frameTime;
	//SHIP1_Y_SPEED = SHIP1_Y_SPEED - ((1 - DRAG) *SHIP1_Y_SPEED) * frameTime;   //Implementation of "Air" Resistance
}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{

	//// if collision between ships
	//if (ship1.collidesWith(ship2, collisionVector))
	//{
	//	// bounce off ship
	//	ship1.bounce(collisionVector, ship2);
	//	ship1.damage(SHIP);
	//	// change the direction of the collisionVector for ship2
	//	ship2.bounce(collisionVector*-1, ship1);
	//	ship2.damage(SHIP);
	//}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{
	
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	nebula.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene

	ship1.draw();							// add the ship to the scene

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();

    Game::resetAll();
    return;
}
