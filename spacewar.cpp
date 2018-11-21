
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

	// ship texture
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));



	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// ship1
	if (!ship.initialize(graphics, SHIP1_WIDTH, SHIP1_HEIGHT, SHIP1_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));

	//Scale Nebula to fullscreen
	nebula.setScale(GAME_WIDTH/nebula.getWidth());

	//Scale Ship to Intended Size
	ship.setScale(SHIP1_SET_WIDTH / ship.getWidth());

	//Ship animation
	ship.setFrames(SHIP1_START_FRAME, SHIP1_END_FRAME);   // animation frames 
	ship.setCurrentFrame(SHIP1_START_FRAME);             // starting frame
	ship.setFrameDelay(SHIP1_ANIMATION_DELAY);



	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	// place ship in center left of screen
	ship.setX(GAME_WIDTH*0.33f - ship.getWidth()*0.5f);
	ship.setY(GAME_HEIGHT*0.5f - ship.getHeight()*0.5f);
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	ship.update(frameTime); //update ship frames
	if (input->isKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}

	//------------Handle Ship Rotation on Key Press--------------

	//Keeping the ranges of the angle to 0<x<360
	while (ship.getDegrees() < 0)
	{
		ship.setDegrees(ship.getDegrees() + 360);
	}
	while (ship.getDegrees() > 360)
	{
		ship.setDegrees(ship.getDegrees() - 360);
	}

	if (SHIP1_ROTATION_RATE < 240) //if ship is rotating at a speed of less than 5 degrees per frame
	{
		if (input->isKeyDown(D)) //and the D key is held
		{
			SHIP1_ROTATION_RATE += SHIP1_ROTATION_ACCELERATION_RATE * frameTime;
		}

	}

	if (SHIP1_ROTATION_RATE > -240) //if ship is rotating at a speed of less than -5 degrees per frame
	{
		if (input->isKeyDown(A)) //And the A key is held
		{
			SHIP1_ROTATION_RATE -= SHIP1_ROTATION_ACCELERATION_RATE * frameTime;
		}

	}

	// SHIP ROTATION CALCULATION-----------------------------------------------



	if (!input->isKeyDown(A) && !input->isKeyDown(D))
	{
		if (SHIP1_ROTATION_RATE < -SHIP1_ROTATION_DRAG *frameTime)
		{
			SHIP1_ROTATION_RATE += SHIP1_ROTATION_DRAG * frameTime;
		}
		else if (SHIP1_ROTATION_RATE > SHIP1_ROTATION_DRAG*frameTime)
		{
			SHIP1_ROTATION_RATE -= SHIP1_ROTATION_DRAG * frameTime;
		}
		else
		{
			SHIP1_ROTATION_RATE = 0;
		}
	}

	ship.setDegrees(ship.getDegrees() + SHIP1_ROTATION_RATE * frameTime);	//update ship rotation 

	

	//----------------------------Handle Ship acceleration on Key Press-------------------------------------------

	

	if (input->isKeyDown(W)) //If the W key is held
	{
		SHIP1_X_SPEED += sin(ship.getDegrees() / 360 * 2 * PI) * SHIP1_X_ACC * frameTime;
		SHIP1_Y_SPEED -= cos(ship.getDegrees() / 360 * 2 * PI) * SHIP1_Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}

	if (input->isKeyDown(S)) //If the S key is held
	{
		SHIP1_X_SPEED -= sin(ship.getDegrees() / 360 * 2 * PI) * SHIP1_X_ACC * frameTime;
		SHIP1_Y_SPEED += cos(ship.getDegrees() / 360 * 2 * PI) * SHIP1_Y_ACC * frameTime;		//Sets the ship X and Y speed based on angle
	}


	//----------------------------------Ship Location Wrapping-------------------------------------
	//SHIP LOCATION UPDATE
	ship.setX(ship.getX() + SHIP1_X_SPEED  * frameTime); // Update Ship X location
	ship.setY(ship.getY() + SHIP1_Y_SPEED  * frameTime); // Update Ship Y location
	   
	
	if (ship.getX() > GAME_WIDTH)               // if off screen right
	{
		ship.setX((float)-ship.getWidth()*ship.getScale());     // position off screen left
		
	}
	if (ship.getX() < -ship.getWidth()*ship.getScale() -1)               // if off screen left
	{
		ship.setX(GAME_WIDTH);     // position off screen right

	}

	if (ship.getY() < -ship.getHeight()*ship.getScale() - 1)               // if off screen up
	{
		ship.setY(GAME_HEIGHT);     // position off screen up
	}
	if (ship.getY() > GAME_HEIGHT )               // if off screen down
	{
		ship.setY((float)-ship.getHeight()*ship.getScale());	// position off screen Down
	}

	SHIP1_X_SPEED = SHIP1_X_SPEED - ((1 - DRAG) *SHIP1_X_SPEED) * frameTime;
	SHIP1_Y_SPEED = SHIP1_Y_SPEED - ((1 - DRAG) *SHIP1_Y_SPEED) * frameTime;   //Implementation of "Air" Resistance
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{
	
}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	nebula.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene

	ship.draw();							// add the ship to the scene

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
