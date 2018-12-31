#include "startscreen.h"
#include "entity.h"

//=============================================================================
// Constructor
//=============================================================================
Startscreen::Startscreen()
{}

//=============================================================================
// Destructor
//=============================================================================
Startscreen::~Startscreen()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Startscreen::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

			// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
		// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
	//Scale Nebula to fullscreen
	nebula.setScale(GAME_WIDTH / nebula.getWidth());

}

//==========================================================================================================================================================================================================================
// Update all game items
//==========================================================================================================================================================================================================================
void Startscreen::update()
{
	if (input->isKeyDown(SPACE))
	{
		newGame.initialize(NULL);
	}

	if (input->isKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}
}

//=============================================================================
// Handle collisions
//=============================================================================

void Startscreen::collisions()
{
	VECTOR2 collisionVector;
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Startscreen::ai()
{

}

//=============================================================================
// Render game items
//=============================================================================
void Startscreen::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	nebula.draw();                          // add the orion nebula to the scene

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Startscreen::releaseAll()
{
	nebulaTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Startscreen::resetAll()
{
	nebulaTexture.onResetDevice();

	Game::resetAll();
	return;
}