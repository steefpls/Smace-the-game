#include "spaceWar.h"
#include "ship.h"
#include "entity.h"

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

	//ship1Textures
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1 texture"));

	// ship
	if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
	ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	ship1.setX(GAME_WIDTH / 4);
	ship1.setY(GAME_HEIGHT /4);

	//Wall texture
	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	
	//the walls on the top and bottom sides of the screen
	for (int i = 0; i < GAME_WIDTH / (wallNS::WIDTH*wallNS::SCALE); i++)
	{	
		wallListTop.push_back(new Wall());
		wallListBottom.push_back(new Wall());
		
		wallListTop[wallListTop.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListTop[wallListTop.size() - 1]->setX(i*(wallNS::WIDTH*wallNS::SCALE));
		wallListTop[wallListTop.size() - 1]->setY(0);

		wallListBottom[wallListBottom.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListBottom[wallListBottom.size() - 1]->setX(i*(wallNS::WIDTH*wallNS::SCALE));
		wallListBottom[wallListBottom.size() - 1]->setY(GAME_HEIGHT- (wallNS::HEIGHT*wallNS::SCALE));
	}

	//the walls on the left and right side of the screen
	for (int i = 0; i < (GAME_HEIGHT-wallNS::HEIGHT) / (wallNS::HEIGHT*wallNS::SCALE); i++)
	{
		wallListLeft.push_back(new Wall());
		wallListRight.push_back(new Wall());

		wallListLeft[wallListLeft.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListLeft[wallListLeft.size() - 1]->setX(0);
		wallListLeft[wallListLeft.size() - 1]->setY((i + 1)*(wallNS::HEIGHT*wallNS::SCALE));

		wallListRight[wallListRight.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListRight[wallListRight.size() - 1]->setX(GAME_WIDTH-(wallNS::WIDTH*wallNS::SCALE));
		wallListRight[wallListRight.size() - 1]->setY((i + 1)*(wallNS::HEIGHT*wallNS::SCALE));
	}

	wallListList.push_back(wallListTop);		//wallListList[3] = wallListTop
	wallListList.push_back(wallListBottom);		//wallListList[2] = wallListBottom
	wallListList.push_back(wallListLeft);		//wallListList[1] = wallListLeft
	wallListList.push_back(wallListRight);		//wallListList[0] = wallListRight

	//missile texture
	if (!missileTexture.initialize(graphics, MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile texture"));

	//missile
	if (!missile1.initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile"));
	missile1.setFrames(missileNS::MISSILE_START_FRAME, missileNS::MISSILE_END_FRAME);
	missile1.setCurrentFrame(missileNS::MISSILE_START_FRAME);
	missile1.setX(GAME_WIDTH / 6);
	missile1.setY(600);
	
	
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
	//bullet1.update(frameTime); //update bullet frames

	ship1.update(frameTime);	//update ship frames

	for each (std::vector<Wall*> list in wallListList)
	{
		for each(Wall* w in list)
		{
			w->update(frameTime);	//update top wall frames
		}
	}

	missile1.update(frameTime);	//update missile frames
								

	if (input->isKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}
	
}

//=============================================================================
// Handle collisions
//=============================================================================

void Spacewar::collisions()
{
	VECTOR2 collisionVector;

	for (int i = 0; i<(wallListList.size());i++)
	{
		for (int j =0; j<(wallListList[i].size());j++)
		{
			if (ship1.collidesWith(*wallListList[i][j] , collisionVector))	//If ship collides with wall
			{
				int check = (wallListList[i][j]->squarebounce(ship1));
				if (check == 1 || check == 3)
				{
					ship1.topbottomrotatebounce();
				}
				else if (check == 2 || check == 4)
				{
					ship1.leftrightrotatebounce();
				}
				//wallListList[i][j]->hp
				wallListList[i].erase(wallListList[i].begin() + j);
			}
		}
	}

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
	missile1.draw();

	for (int i = 0; i<(wallListList.size());i++)
	{
		for(int j = 0; j<(wallListList[i].size());j++)
		{
			wallListList[i][j]->draw();
		}
	}

	//bullet1.draw();				
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

//for (i = 0; i < wall list amount; i++) { wall[i].CollidesWith