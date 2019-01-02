//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#include "spacewar.h"
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

	audio->playCue(BGM);
	
		// blue heart texture
	if (!blueHeartTexture.initialize(graphics,BLUEHEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing blue heart texture"));

		//red heart texture
	if (!redHeartTexture.initialize(graphics, REDHEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing red heart texture"));

		// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULABACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// nebulabackground texture
	if (!nebulabackgroundTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
	

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// nebulabackground
	if (!nebulabackground1.initialize(graphics, 0, 0, 0, &nebulabackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebulabackground"));
	// nebulabackground
	if (!nebulabackground2.initialize(graphics, 0, 0, 0, &nebulabackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebulabackground"));

	//// planet texture
	//if (!planetTexture.initialize(graphics, PLANET_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	//ship1Textures
	if (!ship1Texture.initialize(graphics, SHIP1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1 texture"));

	//ship2Textures
	if (!ship2Texture.initialize(graphics, SHIP2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2 texture"));

	// ship1
	if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &ship1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	ship1.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);
	ship1.setCurrentFrame(shipNS::SHIP_START_FRAME);
	ship1.setX(GAME_WIDTH / 4);
	ship1.setY(GAME_HEIGHT /4);
	ship1.player1Down = 'S';
	ship1.player1Up = 'W';
	ship1.player1Left = 'A';
	ship1.player1Right = 'D';
	for (int i = 0; i < ship1.getLifeCount(); i++)
	{
		ship1.lifeList.push_back(new Image);
		ship1.lifeList[i]->initialize(graphics, 0, 0, 0, &blueHeartTexture);
		ship1.lifeList[i]->setScale(0.1);
		ship1.lifeList[i]->setX((wallNS::WIDTH*wallNS::SCALE)+i*(ship1.lifeList[i]->getWidth()*ship1.lifeList[i]->getScale()));
		ship1.lifeList[i]->setY(GAME_HEIGHT - (wallNS::WIDTH*wallNS::SCALE) - (ship1.lifeList[i]->getHeight()*ship1.lifeList[i]->getScale()));
	}

	//ship2
	if (!ship2.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &ship2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));
	ship2.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);
	ship2.setCurrentFrame(shipNS::SHIP_START_FRAME);
	ship2.setX(3 * GAME_WIDTH / 4);
	ship2.setY(GAME_HEIGHT / 4);
	ship2.player1Down = VK_DOWN;
	ship2.player1Up = VK_UP;
	ship2.player1Left = VK_LEFT;
	ship2.player1Right = VK_RIGHT;

	for (int i = 0; i < ship2.getLifeCount(); i++)
	{
		ship2.lifeList.push_back(new Image);
		ship2.lifeList[i]->initialize(graphics, 0, 0, 0, &redHeartTexture);
		ship2.lifeList[i]->setScale(0.1);
		ship2.lifeList[i]->setX(GAME_WIDTH - (wallNS::WIDTH*wallNS::SCALE) - (i+1) *(ship2.lifeList[i]->getWidth()*ship2.lifeList[i]->getScale()));
		ship2.lifeList[i]->setY(GAME_HEIGHT - (wallNS::WIDTH*wallNS::SCALE) - (ship2.lifeList[i]->getHeight()*ship2.lifeList[i]->getScale()));
	}

	//Title texture
	if (!titleTexture.initialize(graphics, TITLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing title texture"));

	if (!title.initialize(graphics, 0, 0, 0, &titleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing title"));

	titleScale = 0.5;
	titleScaleIncrease = false;
	//Wall texture
	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	

	//the walls on the top and bottom sides of the screen
	for (int i = 0; i < GAME_WIDTH / (wallNS::WIDTH*wallNS::SCALE); i++)
	{
		wallListTop.push_back(new Wall());

		wallListTop[wallListTop.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListTop[wallListTop.size() - 1]->setX(i*(wallNS::WIDTH*wallNS::SCALE));
		wallListTop[wallListTop.size() - 1]->setY(0);

		wallListTop[wallListTop.size() - 1]->setRadians(wallListTop[wallListTop.size() - 1]->getRadians() + PI);
	}

	for (int i = 0; i < GAME_WIDTH / (wallNS::WIDTH*wallNS::SCALE); i++)
	{
		wallListBottom.push_back(new Wall());

		wallListBottom[wallListBottom.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListBottom[wallListBottom.size() - 1]->setX(i*(wallNS::WIDTH*wallNS::SCALE));
		wallListBottom[wallListBottom.size() - 1]->setY(GAME_HEIGHT - (wallNS::HEIGHT*wallNS::SCALE));
	}

	//the walls on the left and right side of the screen
	for (int i = 0; i < (GAME_HEIGHT - wallNS::HEIGHT) / (wallNS::HEIGHT*wallNS::SCALE); i++)
	{
		wallListLeft.push_back(new Wall());

		wallListLeft[wallListLeft.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListLeft[wallListLeft.size() - 1]->setX(0);
		wallListLeft[wallListLeft.size() - 1]->setY((i + 1)*(wallNS::HEIGHT*wallNS::SCALE));

		wallListLeft[wallListLeft.size() - 1]->setRadians(wallListLeft[wallListLeft.size() - 1]->getRadians() + (PI/2));
	}

	for (int i = 0; i < (GAME_HEIGHT - wallNS::HEIGHT) / (wallNS::HEIGHT*wallNS::SCALE); i++)
	{
		wallListRight.push_back(new Wall());

		wallListRight[wallListRight.size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListRight[wallListRight.size() - 1]->setX(GAME_WIDTH - (wallNS::WIDTH*wallNS::SCALE));
		wallListRight[wallListRight.size() - 1]->setY((i + 1)*(wallNS::HEIGHT*wallNS::SCALE));
		wallListRight[wallListRight.size() - 1]->setRadians(wallListRight[wallListRight.size() - 1]->getRadians() + ((3 * PI) / 2));
	}

	wallListList.push_back(wallListTop);		//wallListList[3] = wallListTop
	wallListList.push_back(wallListBottom);		//wallListList[2] = wallListBottom
	wallListList.push_back(wallListLeft);		//wallListList[1] = wallListLeft
	wallListList.push_back(wallListRight);		//wallListList[0] = wallListRight


	//missile texture
	if (!missileTexture.initialize(graphics, MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile texture"));

	//explosion texture
	if (!explosionTexture.initialize(graphics, EXPLOSION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion texture"));

	//explosion object
	//if (!explosion1.initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion1"));
	//explosion1.setFrames(explosionNS::EXPLOSION_START_FRAME, explosionNS::EXPLOSION_END_FRAME);
	//explosion1.setX(GAME_WIDTH / 2);
	//explosion1.setY(GAME_HEIGHT / 2);

	//bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	//mine texture
	if (!mineTexture.initialize(graphics, MINE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mine texture"));

	//blackhole texture
	if(!blackholeTexture.initialize(graphics,BLACKHOLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing black hole texture"));

	Player1Label.initialize(graphics, spacewarNS::FONT_SIZE, false, false, spacewarNS::FONT);		//Initialises text font =======================================
	Player1Label.setFontColor(SETCOLOR_ARGB(255, 199, 24, 24));
	

	Player1DamagePercent.initialize(graphics, spacewarNS::FONT_SIZE, false, false, spacewarNS::FONT);		//Initialises text font =======================================
	Player1DamagePercent.setFontColor(SETCOLOR_ARGB(255, 199, 24, 24));

	Player2Label.initialize(graphics, spacewarNS::FONT_SIZE, false, false, spacewarNS::FONT);		//Initialises text font =======================================
	Player2Label.setFontColor(SETCOLOR_ARGB(255, 39, 45, 208));

	Player2DamagePercent.initialize(graphics, spacewarNS::FONT_SIZE, false, false, spacewarNS::FONT);		//Initialises text font =======================================
	Player2DamagePercent.setFontColor(SETCOLOR_ARGB(255, 39, 45, 208));

	gameOverText.initialize(graphics, spacewarNS::FONT_SIZE, false, false, spacewarNS::FONT);		//Initialises text font =======================================
	gameOverText.setFontColor(SETCOLOR_ARGB(255, 60, 47, 55));

	PressEnterToStart.initialize(graphics, spacewarNS::FONT_SIZE, false, false, spacewarNS::FONT);
	PressEnterToStart.setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
	PETSalpha = 255;
	alphaIncrease = false;

	nebula.setX(0);
	nebula.setY(0);
	
	nebula.setScale(1.08);

	double nebulaoffset1 = 0;
	double nebulaoffset2 = GAME_WIDTH;

	nebulabackground1.setX(0);
	nebulabackground1.setY(0);
	nebulabackground1.setScale(1.08);
	nebulabackground2.setX(2000*1.08);
	nebulabackground2.setY(0);
	nebulabackground2.setScale(1.08);
	//// planet
	//if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//// place planet in center of screen
	//planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	//planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	title.setScale(0.5);
	title.setX(GAME_WIDTH*0.5f - title.getWidth()*title.getScale()*0.5f);
	title.setY(GAME_HEIGHT*0.5f - title.getHeight()*title.getScale()*0.5f);

	return;
}

//==========================================================================================================================================================================================================================
// Update all game items
//==========================================================================================================================================================================================================================
void Spacewar::update()
{
	//bullet1.update(frameTime); //update bullet frames
	if (input->isKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}
	nebulabackground1.setX(nebulabackground1.getX() - 100 * frameTime);
	nebulabackground2.setX(nebulabackground2.getX() - 100 * frameTime);

	if (nebulabackground1.getX() <= (-2000 * 1.08))
	{
		nebulabackground1.setX(2000 * 1.08);
	}
	if (nebulabackground2.getX() <= (-2000 * 1.08))
	{
		nebulabackground2.setX(2000 * 1.08);
	}
	if (startscreenon == true)
	{
		
		

		if (input->isKeyDown(VK_RETURN))
		{
			startscreenon = false;
		}

		if (titleScale >= 0.45 && titleScaleIncrease == false)
		{
			titleScale -= 0.0003;
		}
		else if (titleScale <= 0.55 && titleScaleIncrease == true)
		{
			titleScale += 0.0003;
		}

		if (titleScale <= 0.45)
			titleScaleIncrease = true;
		else if (titleScale >= 0.55)
			titleScaleIncrease = false;

		title.setScale(titleScale);
		title.setX(GAME_WIDTH*0.5f - title.getWidth()*title.getScale()*0.5f);
		title.setY(GAME_HEIGHT*0.5f - title.getHeight()*title.getScale()*0.5f);

		if (PETSalpha > 0 && alphaIncrease == false)
		{
			PETSalpha -= 1;
		}
		else if (PETSalpha <= 255 && alphaIncrease == true)
		{
			PETSalpha += 1;
		}
		
		if (PETSalpha == 0) alphaIncrease = true;
		else if (PETSalpha == 255) alphaIncrease = false;
		PressEnterToStart.setFontColor(SETCOLOR_ARGB(PETSalpha, PETSalpha, PETSalpha, PETSalpha));
	}

	if (startscreenon == false)
	{
		if (input->isKeyDown('E'))
		{
			resetGame();
		}

		ship1.update(frameTime);	//update ship1 frames
		ship2.update(frameTime);	//update ship2 frames

		for (int i = 0; i < explosionList.size(); i++)	//update all explosion frames
		{
			if (explosionList[i] != NULL)
			{
				explosionList[i]->update(frameTime);
				if (explosionList[i]->getCurrentFrame() == explosionList[i]->getEndFrame())
				{
					SAFE_DELETE(explosionList[i]);
					explosionList.erase(explosionList.begin() + i);

				}
			}
		}

		for (int i = 0; i < wallListList.size(); i++)
		{
			for (int j = 0; j < wallListList[i].size(); j++)
			{
				wallListList[i][j]->update(frameTime);	//update top wall frames
			}
		}

		//==========================================================================================================
		// if SHIP 1 leaves boundary
		//==========================================================================================================
		if (ship1.getX() > GAME_WIDTH || ship1.getX() < 0 - ship1.getWidth()*ship1.getScale())
		{
			ship1.setX(GAME_WIDTH / 2);
			ship1.setY(GAME_HEIGHT / 2);
			ship1.setVelocityX(0);
			ship1.setVelocityY(0);
			ship1.setRadians(0);
			ship1.setLifeCount(ship1.getLifeCount() - 1);
			ship1.setHP(ship1.getMaxHP());
			if (ship1.lifeList.size() >= 1)
			{
				ship1.lifeList.erase(ship1.lifeList.begin() + ship1.lifeList.size() - 1);
			}
		}
		else if (ship1.getY() > GAME_HEIGHT || ship1.getY() < 0 - ship1.getHeight()*ship1.getScale())
		{
			ship1.setX(GAME_WIDTH / 2);
			ship1.setY(GAME_HEIGHT / 2);
			ship1.setVelocityX(0);
			ship1.setVelocityY(0);
			ship1.setRadians(0);
			ship1.setLifeCount(ship1.getLifeCount() - 1);
			ship1.setHP(ship1.getMaxHP());

			if (ship1.lifeList.size() >= 1)
			{
				ship1.lifeList.erase(ship1.lifeList.begin() + ship1.lifeList.size() - 1);
			}
		}

		//==========================================================================================================
		// if SHIP 2 leaves boundary
		//==========================================================================================================
		if (ship2.getX() > GAME_WIDTH || ship2.getX() < 0 - ship2.getWidth()*ship2.getScale())
		{
			ship2.setX(GAME_WIDTH / 2);
			ship2.setY(GAME_HEIGHT / 2);
			ship2.setVelocityX(0);
			ship2.setVelocityY(0);
			ship2.setRadians(0);
			ship2.setLifeCount(ship2.getLifeCount() - 1);
			ship2.setHP(ship2.getMaxHP());
			if (ship2.lifeList.size() >= 1)
			{
				ship2.lifeList.erase(ship2.lifeList.begin() + ship2.lifeList.size() - 1);
			}
		}
		else if (ship2.getY() > GAME_HEIGHT || ship2.getY() < 0 - ship2.getHeight()*ship2.getScale())
		{
			ship2.setX(GAME_WIDTH / 2);
			ship2.setY(GAME_HEIGHT / 2);
			ship2.setVelocityX(0);
			ship2.setVelocityY(0);
			ship2.setRadians(0);
			ship2.setLifeCount(ship1.getLifeCount() - 1);
			ship2.setHP(ship2.getMaxHP());

			if (ship2.lifeList.size() >= 1)
			{
				ship2.lifeList.erase(ship2.lifeList.begin() + ship2.lifeList.size() - 1);
			}
		}

		//===========================================================================================================
		//  Inputs FOR SHIP 1
		//===========================================================================================================

		//SHIP
		if (input->isKeyDown(SHIFT_KEY))													//if shift is pressed, ship 1 dashes
		{
			ship1.dash();
		}


		if (input->isKeyDown(player1Secondary) && ship1.getmissiletimer() < 0)				//If player is pressing X, shoot missiles
		{
			audio->playCue(MISSILE);
			ship1.spawnmissile();
			ship1.missileList[ship1.missileList.size() - 1]->initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture);
			ship1.setMissileXY();
		}

		for (int i = 0; i < ship1.missileList.size(); i++)									//Update all ship1 missile objects
		{
			ship1.missileList[i]->update(frameTime);
		}

		for (int i = 0; i < ship1.missileList.size(); i++)				//check if missile is out of bounds
		{
			if (ship1.missileList[i] != NULL)
			{
				if (ship1.missileList[i]->getX() > GAME_WIDTH || ship1.missileList[i]->getX() < 0 - ship1.missileList[i]->getWidth()*ship1.missileList[i]->getScale())
				{
					if (ship1.missileList[i] != NULL)
					{
						SAFE_DELETE(ship1.missileList[i]);
						ship1.missileList.erase(ship1.missileList.begin() + i);
					}
				}

				else if (ship1.missileList[i]->getY() > GAME_HEIGHT || ship1.missileList[i]->getY() < 0 - ship1.missileList[i]->getHeight()*ship1.missileList[i]->getScale())
				{
					if (ship1.missileList[i] != NULL)
					{
						SAFE_DELETE(ship1.missileList[i]);
						ship1.missileList.erase(ship1.missileList.begin() + i);
					}
				}
			}
		}

		//MINE
		if (input->isKeyDown(player1Primary) && ship1.getminetimer() < 0)				//If player is pressing X, shoot mines
		{
			ship1.spawnmine();
			audio->playCue(MINEBLEEP);
			ship1.mineList[ship1.mineList.size() - 1]->initialize(this, mineNS::WIDTH, mineNS::HEIGHT, mineNS::TEXTURE_COLS, &mineTexture);


			if (ship1.mineList.size() > ship1.getmaxmines())
			{
				if (ship1.mineList[0] != NULL)
				{
					SAFE_DELETE(ship1.mineList[0]);
					ship1.mineList.erase(ship1.mineList.begin() + 0);
				}
			}
			ship1.setMineXY();
		}

		if (ship1.mineList.size() <= 0)
		{
			audio->stopCue(MINEBLEEP);
		}

		for (int i = 0; i < ship1.mineList.size(); i++)								//Update all ship1 mine objects
		{
			ship1.mineList[i]->update(frameTime);
		}

		for (int i = 0; i < ship1.mineList.size(); i++)	//MINE Deletion when exits boundaries
		{
			if (ship1.mineList[i] != NULL)
			{
				if (ship1.mineList[i]->getX() > GAME_WIDTH || ship1.mineList[i]->getX() < 0 - ship1.mineList[i]->getWidth()* ship1.mineList[i]->getScale())
				{
					if (ship1.mineList[i] != NULL)
					{
						SAFE_DELETE(ship1.mineList[i]);
						ship1.mineList.erase(ship1.mineList.begin() + i);

					}
				}
				else if (ship1.mineList[i]->getY() > GAME_HEIGHT || ship1.mineList[i]->getY() < 0 - ship1.mineList[i]->getHeight()* ship1.mineList[i]->getScale())
				{
					if (ship1.mineList[i] != NULL)
					{
						SAFE_DELETE(ship1.mineList[i]);
						ship1.mineList.erase(ship1.mineList.begin() + i);

					}
				}
			}
		}

		//================================================================================================
		// Inputs FOR SHIP 2
		//=================================================================================================
		for (int i = 0; i < ship2.bulletList.size(); i++)	//Update all ship2 bullets
		{
			ship2.bulletList[i]->update(frameTime);
		}

		ship2.boost(input->isKeyDown(CTRL));				//Checking if boost button is pressed

		if (input->isKeyDown(SPACE) && ship2.getbullettimer() < 0)	//if Space is pressed, shoot bullets
		{
			audio->playCue(BULLETSHOT);
			if (ship2.getnoofbullets() > 1)
			{
				double degdiff = ship2.getdegreespread() / (ship2.getnoofbullets() - 1);


				for (int i = 0; i < (ship2.getnoofbullets()); i++)
				{
					ship2.spawnbullet();
					ship2.bulletList[ship2.bulletList.size() - 1]->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
					ship2.setBulletXY((-ship2.getdegreespread() / 2) + i * degdiff);
				}
			}
			else if (ship2.getnoofbullets() == 1)
			{
				ship2.spawnbullet();
				ship2.bulletList[ship2.bulletList.size() - 1]->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
				ship2.setBulletXY((0));
			}
		}

		for (int i = 0; i < ship2.bulletList.size(); i++)	//Bullet Deletion when exits boundaries
		{
			if (ship2.bulletList[i] != NULL)
			{
				if (ship2.bulletList[i]->getX() > GAME_WIDTH || ship2.bulletList[i]->getX() < 0 - ship2.bulletList[i]->getHeight())
				{
					if (ship2.bulletList[i] != NULL)
					{
						SAFE_DELETE(ship2.bulletList[i]);
						ship2.bulletList.erase(ship2.bulletList.begin() + i);
					}
				}
				else if (ship2.bulletList[i]->getY() > GAME_HEIGHT || ship2.bulletList[i]->getY() < 0 - ship2.bulletList[i]->getHeight())
				{
					if (ship2.bulletList[i] != NULL)
					{
						SAFE_DELETE(ship2.bulletList[i]);
						ship2.bulletList.erase(ship2.bulletList.begin() + i);
					}
				}
			}
		}
		//Shoot black hole
		if (input->isKeyDown(player2Secondary) && ship2.getblackholetimer() <= 0)
		{
			ship2.spawnblackhole();
			ship2.blackholeList[ship2.blackholeList.size() - 1]->initialize(this, blackholeNS::WIDTH, blackholeNS::HEIGHT, blackholeNS::TEXTURE_COLS, &blackholeTexture);
			ship2.blackholeList[ship2.blackholeList.size() - 1]->setScale(0.3);
			ship2.setBlackholeXY();

		}
		//Update all ship2 blackhole objects
		for (int i = 0; i < ship2.blackholeList.size(); i++)
		{
			if (ship2.blackholeList[i] != NULL)
			{
				ship2.blackholeList[i]->update(frameTime);
				if (ship2.blackholeList[i]->getScale() <= 0)
				{

					SAFE_DELETE(ship2.blackholeList[i]);
					ship2.blackholeList.erase(ship2.blackholeList.begin() + i);

				}
			}
		}
	}
}
	

//=============================================================================
// Handle collisions
//=============================================================================

void Spacewar::collisions()
{
	VECTOR2 collisionVector;

	//WALL COLLISION
	for (int i = 0; i<(wallListList.size());i++)
	{
		//for ship1
		for (int j =0; j<(wallListList[i].size());j++)
		{
			if (ship1.collidesWith(*wallListList[i][j] , collisionVector))	//If ship collides with wall
			{
				int check = (wallListList[i][j]->squarebounce(ship1));
				
				if (check == 1 || check == 3)
				{
					wallListList[i][j]->setHP(wallListList[i][j]->getHP() - abs(ship1.getVelocityY()));
					ship1.topbottomrotatebounce();
					ship1.setHP(ship1.getHP() - abs(ship1.getVelocityY()) / 3);
				}
				else if (check == 2 || check == 4)
				{
					wallListList[i][j]->setHP(wallListList[i][j]->getHP() - abs(ship1.getVelocityX()));
					ship1.leftrightrotatebounce();
					ship1.setHP(ship1.getHP() - abs(ship1.getVelocityX()) / 3);
				}				
			}

			for (int x = 0; x < (ship1.missileList.size()); x++)													//If missile collides with wall
			{
				if (ship1.missileList[x] != NULL)
				{
					if (ship1.missileList[x]->collidesWith(*wallListList[i][j], collisionVector))
					{

						explosionList.push_back(new Explosion);
						explosionList[explosionList.size() - 1]->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
						explosionList[explosionList.size() - 1]->setFrames(explosionNS::EXPLOSION_START_FRAME, explosionNS::EXPLOSION_END_FRAME);

						explosionList[explosionList.size() - 1]->setX(ship1.missileList[x]->getScale()*ship1.missileList[x]->getHeight() / 2 *  sin(ship1.missileList[x]->getRadians()) +(ship1.missileList[x]->getCenterX()) - (explosionList[explosionList.size() - 1]->getHeight()/2* explosionList[explosionList.size() - 1]->getScale()));
						explosionList[explosionList.size() - 1]->setY(ship1.missileList[x]->getScale()*ship1.missileList[x]->getHeight() / 2 * -cos(ship1.missileList[x]->getRadians()) + (ship1.missileList[x]->getCenterY()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));

						wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship1.missileList[x]->getDamage());
						audio->playCue(BOOM);
						SAFE_DELETE(ship1.missileList[x]);
						ship1.missileList.erase(ship1.missileList.begin() + x);

					}
				}
			}

			for (int x = 0; x < (ship1.mineList.size()); x++)
			{
				if (ship1.mineList[x]->collidesWith(*wallListList[i][j], collisionVector))
				{
					double check = (wallListList[i][j]->bulletbounce(*ship1.mineList[x]));
					{
						if (check >= 315.0 || check < 45)				//hitting de bottam woll
						{
							if (ship1.mineList[x]->getVelocityY() > 0)
							{
								//wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship1.mineList[x]->getDamage());
								//ship1.mineList[x]->bounceCounter -= 1;
								ship1.mineList[x]->setVelocityY(-ship1.mineList[x]->getVelocityY());
							}
						}

						if (check >= 45 && check < 135)				//hitting de left woll
						{
							if (ship1.mineList[x]->getVelocityX() < 0)
							{
								//wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship1.mineList[x]->getDamage());
								//ship1.mineList[x]->bounceCounter -= 1;
								ship1.mineList[x]->setVelocityX(-ship1.mineList[x]->getVelocityX());
							}
						}

						if (check >= 135 && check < 225)			//hitting de tap woll
						{
							if (ship1.mineList[x]->getVelocityY() < 0)
							{
								//wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship1.mineList[x]->getDamage());
								//ship1.mineList[x]->bounceCounter -= 1;
								ship1.mineList[x]->setVelocityY(-ship1.mineList[x]->getVelocityY());
							}
						}

						if (check >= 225 && check < 315)			//hitting de right woll
						{
							if (ship1.mineList[x]->getVelocityX() > 0)
							{
								//wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship1.mineList[x]->getDamage());
								//ship1.mineList[x]->bounceCounter -= 1;
								ship1.mineList[x]->setVelocityX(-ship1.mineList[x]->getVelocityX());
							}
						}
					}
				}
			}

			if (wallListList[i][j] != NULL)
			{
				if (wallListList[i][j]->getHP() <= 0)
				{

					SAFE_DELETE(wallListList[i][j]);
					wallListList[i].erase(wallListList[i].begin() + j);
				}
			}
		}

		// for ship 2
		for (int j = 0; j < (wallListList[i].size()); j++)
		{
			if (ship2.collidesWith(*wallListList[i][j], collisionVector))	//If ship collides with wall
			{
				int check = (wallListList[i][j]->squarebounce(ship2));

				if (check == 1 || check == 3)
				{
					wallListList[i][j]->setHP(wallListList[i][j]->getHP() - abs(ship2.getVelocityY()));
					ship2.topbottomrotatebounce();
					ship2.setHP(ship2.getHP() - abs(ship2.getVelocityY()) / 3);
				}
				else if (check == 2 || check == 4)
				{
					wallListList[i][j]->setHP(wallListList[i][j]->getHP() - abs(ship2.getVelocityX()));
					ship2.leftrightrotatebounce();
					ship2.setHP(ship2.getHP() - abs(ship2.getVelocityX())/3);
				}
			}

			for (int x = 0; x < (ship2.bulletList.size()); x++)
			{
				if (ship2.bulletList[x]->collidesWith(*wallListList[i][j], collisionVector))
				{
					if (ship2.bulletList[x]->bounceCounter > 0)
					{
						double check = (wallListList[i][j]->bulletbounce(*ship2.bulletList[x]));
						{
							if (check >= 315.0 || check < 45)				//hitting de bottam woll
							{
								if (ship2.bulletList[x]->getVelocityY() > 0)
								{
									wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship2.bulletList[x]->getDamage());
									ship2.bulletList[x]->bounceCounter -= 1;
									ship2.bulletList[x]->setVelocityY(-ship2.bulletList[x]->getVelocityY());
								}
							}

							if (check >= 45 && check < 135)				//hitting de left woll
							{
								if (ship2.bulletList[x]->getVelocityX() < 0)
								{
									wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship2.bulletList[x]->getDamage());
									ship2.bulletList[x]->bounceCounter -= 1;
									ship2.bulletList[x]->setVelocityX(-ship2.bulletList[x]->getVelocityX());
								}
							}

							if (check >= 135 && check < 225)			//hitting de tap woll
							{
								if (ship2.bulletList[x]->getVelocityY() < 0)
								{
									wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship2.bulletList[x]->getDamage());
									ship2.bulletList[x]->bounceCounter -= 1;
									ship2.bulletList[x]->setVelocityY(-ship2.bulletList[x]->getVelocityY());
								}
							}

							if (check >= 225 && check < 315)			//hitting de right woll
							{
								if (ship2.bulletList[x]->getVelocityX() > 0)
								{
									wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship2.bulletList[x]->getDamage());
									ship2.bulletList[x]->bounceCounter -= 1;
									ship2.bulletList[x]->setVelocityX(-ship2.bulletList[x]->getVelocityX());
								}
							}
						}
					}
					else
					{
						if (ship2.bulletList[x] != NULL)
						{
							wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship2.bulletList[x]->getDamage());
							SAFE_DELETE(ship2.bulletList[x]);
							ship2.bulletList.erase(ship2.bulletList.begin() + x);
						}
					}
				}
			}

			for (int x = 0; x < explosionList.size(); x++)
			{
				if (wallListList[i][j]->collidesWith(*explosionList[x], collisionVector) /*&& explosionList[x]->getCurrentFrame()==0*/)
				{
					wallListList[i][j]->setHP(wallListList[i][j]->getHP() - explosionList[x]->getDamage());
				}
			}
			if (wallListList[i][j] != NULL)
			{
				if (wallListList[i][j]->getHP() <= 0)
				{

					SAFE_DELETE(wallListList[i][j]);
					wallListList[i].erase(wallListList[i].begin() + j);

				}
			}
		}
	}

	//MINE COLLISION
	for (int i = 0; i < (ship1.mineList.size()); i++)
	{
		for (int j = 0; j < (ship2.bulletList.size()); j++)
		{
			if (ship2.bulletList[j] != NULL)
			{
				if (ship1.mineList[i]->collidesWith(*ship2.bulletList[j], collisionVector))
				{
					ship1.mineList[i]->bounce(collisionVector, *ship2.bulletList[j]);
					ship1.mineList[i]->setHP(ship1.mineList[i]->getHP() - ship2.bulletList[j]->getDamage());

					SAFE_DELETE(ship2.bulletList[j]);
					ship2.bulletList.erase(ship2.bulletList.begin() + j);
					
				}
			}
		}

		for (int j = 0; j < (ship1.mineList.size()); j++)
		{
			if (i != j)
			{
				if (ship1.mineList[i]->collidesWith(*ship1.mineList[j], collisionVector))
				{
					ship1.mineList[i]->bounce(collisionVector, *ship1.mineList[j]);
				}
			}
		}

		for (int j = 0; j < (ship1.missileList.size()); j++)
		{
			if (ship1.missileList[j] != NULL)
			{
				if (ship1.mineList[i]->collidesWith(*ship1.missileList[j], collisionVector))
				{
					ship1.mineList[i]->setHP(ship1.mineList[i]->getHP() - ship1.missileList[j]->getDamage());

					explosionList.push_back(new Explosion);
					explosionList[explosionList.size() - 1]->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
					explosionList[explosionList.size() - 1]->setFrames(explosionNS::EXPLOSION_START_FRAME, explosionNS::EXPLOSION_END_FRAME);

					explosionList[explosionList.size() - 1]->setX(ship1.missileList[j]->getScale()*ship1.missileList[j]->getHeight() / 2 * sin(ship1.missileList[j]->getRadians()) + (ship1.missileList[j]->getCenterX()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));
					explosionList[explosionList.size() - 1]->setY(ship1.missileList[j]->getScale()*ship1.missileList[j]->getHeight() / 2 * -cos(ship1.missileList[j]->getRadians()) + (ship1.missileList[j]->getCenterY()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));


					SAFE_DELETE(ship1.missileList[j]);
					ship1.missileList.erase(ship1.missileList.begin() + j);

				}
			}
		}

		if (ship1.mineList[i]->collidesWith(ship2,collisionVector))
		{
			ship1.mineList[i]->setHP(0);
		}

		for (int j = 0; j < (explosionList.size()); j++)
		{
			if (ship1.mineList[i]->collidesWith(*explosionList[j], collisionVector) && explosionList[j]->getCurrentFrame() == 0)
			{
				ship1.mineList[i]->setHP(0);
			}
		}
		if (ship1.mineList[i] != NULL)
		{
			if (ship1.mineList[i]->getHP() <= 0)
			{
				explosionList.push_back(new Explosion);
				explosionList[explosionList.size() - 1]->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
				explosionList[explosionList.size() - 1]->setFrames(explosionNS::EXPLOSION_START_FRAME, explosionNS::EXPLOSION_END_FRAME);

				explosionList[explosionList.size() - 1]->setX( (ship1.mineList[i]->getCenterX()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));
				explosionList[explosionList.size() - 1]->setY((ship1.mineList[i]->getCenterY()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));

				audio->playCue(BOOM);
				SAFE_DELETE(ship1.mineList[i]);
				//audio->stopCue(MINEBLEEP);
				ship1.mineList.erase(ship1.mineList.begin() + i);

			}
		}
	}

	//BULLET COLLISION
	for (int i = 0; i < (ship2.bulletList.size()); i++)
	{
		if (ship2.bulletList[i] != NULL)
		{
			if (ship1.collidesWith(*ship2.bulletList[i], collisionVector))			//If ship1 collides with bullet
			{
				ship1.setVelocityX(ship1.getVelocityX() + sin(ship2.bulletList[i]->getRadians()) *  (ship2.bulletList[i]->getDamage())*ship1.getKnockBack());
				ship1.setVelocityY(ship1.getVelocityY() + -cos(ship2.bulletList[i]->getRadians()) *  (ship2.bulletList[i]->getDamage())*ship1.getKnockBack());


				ship1.setHP(ship1.getHP() - (ship2.bulletList[i]->getDamage()));

				SAFE_DELETE(ship2.bulletList[i]);
				ship2.bulletList.erase(ship2.bulletList.begin() + i);
				continue;

			}
			
		}
		
		for (int j = 0; j < (ship1.missileList.size()); j++)
		{
			if (ship1.missileList[j] != NULL && ship2.bulletList[i] != NULL)
			{
				if (ship2.bulletList[i]->collidesWith(*ship1.missileList[j], collisionVector))
				{
					explosionList.push_back(new Explosion);
					explosionList[explosionList.size() - 1]->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
					explosionList[explosionList.size() - 1]->setFrames(explosionNS::EXPLOSION_START_FRAME, explosionNS::EXPLOSION_END_FRAME);

					explosionList[explosionList.size() - 1]->setX(ship1.missileList[j]->getScale()*ship1.missileList[j]->getHeight() / 2 * sin(ship1.missileList[j]->getRadians()) + (ship1.missileList[j]->getCenterX()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));
					explosionList[explosionList.size() - 1]->setY(ship1.missileList[j]->getScale()*ship1.missileList[j]->getHeight() / 2 * -cos(ship1.missileList[j]->getRadians()) + (ship1.missileList[j]->getCenterY()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));
					audio->playCue(BOOM);

					SAFE_DELETE(ship1.missileList[j]);
					ship1.missileList.erase(ship1.missileList.begin() + j);

				}
			}
		}
	}

	//MISSILE COLLISION
	for (int i = 0; i < (ship1.missileList.size()); i++)
	{
		if (ship2.collidesWith(*ship1.missileList[i], collisionVector))
		{
			//ship2.bounce(collisionVector, *ship1.missileList[i]);
		}
		if (ship1.missileList[i] != NULL)
		{
			if (ship1.missileList[i]->collidesWith(ship2, collisionVector))
			{
				ship2.setHP(ship2.getHP() - ship1.missileList[i]->getDamage());
				
				explosionList.push_back(new Explosion);
				explosionList[explosionList.size() - 1]->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
				explosionList[explosionList.size() - 1]->setFrames(explosionNS::EXPLOSION_START_FRAME, explosionNS::EXPLOSION_END_FRAME);

				explosionList[explosionList.size() - 1]->setX(ship1.missileList[i]->getScale()*ship1.missileList[i]->getHeight() / 2 * sin(ship1.missileList[i]->getRadians()) + (ship1.missileList[i]->getCenterX()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));
				explosionList[explosionList.size() - 1]->setY(ship1.missileList[i]->getScale()*ship1.missileList[i]->getHeight() / 2 * -cos(ship1.missileList[i]->getRadians()) + (ship1.missileList[i]->getCenterY()) - (explosionList[explosionList.size() - 1]->getHeight() / 2 * explosionList[explosionList.size() - 1]->getScale()));


				audio->playCue(BOOM);

				SAFE_DELETE(ship1.missileList[i]);
				ship1.missileList.erase(ship1.missileList.begin() + i);

			}
		}
	}

	//BLACKHOLE COLLISION
	for (int i = 0; i < (ship2.blackholeList.size()); i++)
	{
		for (int j = 0; j < (ship2.bulletList.size()); j++)						//if collide with ship2.bullets
		{
			if (ship2.blackholeList[i]->collidesWith(*ship2.bulletList[j], collisionVector))
			{
				
				double angbet = ship2.blackholeList[i]->anglebetween(*ship2.bulletList[j]);
				angbet += 180.0;
				if (angbet > 360) { angbet -= 360; }

				
				ship2.bulletList[j]->setVelocityX(ship2.bulletList[j]->getVelocityX() + ((sin(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength() )*frameTime));
				ship2.bulletList[j]->setVelocityY(ship2.bulletList[j]->getVelocityY() - ((cos(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength() )*frameTime));
				
			}
		}
		for (int j = 0; j < (ship1.mineList.size()); j++)						//if collide with ship1.mines
		{
			if (ship2.blackholeList[i]->collidesWith(*ship1.mineList[j], collisionVector))
			{
				
				double angbet = ship2.blackholeList[i]->anglebetween(*ship1.mineList[j]);
				angbet += 180.0;
				if (angbet > 360) { angbet -= 360; }

				ship1.mineList[j]->setVelocityX(ship1.mineList[j]->getVelocityX() + ((sin(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));
				ship1.mineList[j]->setVelocityY(ship1.mineList[j]->getVelocityY() - ((cos(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));

				
			}
		}
		for (int j = 0; j < (ship1.missileList.size()); j++)						//if collide with ship1.missiles
		{
			if (ship2.blackholeList[i]->collidesWith(*ship1.missileList[j], collisionVector))
			{

				double angbet = ship2.blackholeList[i]->anglebetween(*ship1.missileList[j]);
				angbet += 180.0;
				if (angbet > 360) { angbet -= 360; }
				
				ship1.missileList[j]->setVelocityX(ship1.missileList[j]->getVelocityX() + ((sin(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));
				ship1.missileList[j]->setVelocityY(ship1.missileList[j]->getVelocityY() - ((cos(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));


			}
		}
		//==============if collide with ship1===============
		if (ship2.blackholeList[i]->collidesWith(ship1, collisionVector))		//Ships are less affected by black holes, so multiply by ship.blackholesuckmultiplier
		{																		
			double angbet = ship2.blackholeList[i]->anglebetween(ship1);
			angbet += 180.0;
			if (angbet > 360) { angbet -= 360; }

			ship1.setVelocityX(ship1.getVelocityX() + ship1.getblackholesuckmultiplier()*((sin(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));
			ship1.setVelocityY(ship1.getVelocityY() - ship1.getblackholesuckmultiplier()*((cos(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));
		}

		//==============if collide with ship2===============
		if (ship2.blackholeList[i]->collidesWith(ship2, collisionVector))		//Ships are less affected by black holes, so multiply by ship.blackholesuckmultiplier
		{
			double angbet = ship2.blackholeList[i]->anglebetween(ship2);
			angbet += 180.0;
			if (angbet > 360) { angbet -= 360; }

			ship2.setVelocityX(ship2.getVelocityX() + ship2.getblackholesuckmultiplier()*((sin(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));
			ship2.setVelocityY(ship2.getVelocityY() - ship2.getblackholesuckmultiplier()*((cos(angbet / 360 * 2 * PI)*ship2.blackholeList[i]->getsuckstrength())*frameTime));
		}
		
	}

	//EXPLOSION COLLISION
	for (int i = 0; i < (explosionList.size()); i++)
	{
		if (ship1.collidesWith(*explosionList[i], collisionVector) /*&& explosionList[i]->getCurrentFrame() == 18*/)
		{
			ship1.setHP(ship1.getHP() - explosionList[i]->getDamage());
			explosionList[i]->getExplosionBlast(ship1, ship1.getKnockBack());
		}

		if (ship2.collidesWith(*explosionList[i], collisionVector) /*&& explosionList[i]->getCurrentFrame() == 18*/)
		{
			ship2.setHP(ship2.getHP() - explosionList[i]->getDamage());
			explosionList[i]->getExplosionBlast(ship2, ship2.getKnockBack());
		}

		for (int j = 0; j < ship2.bulletList.size(); j++)
		{
			if (ship2.bulletList[j] != NULL)
			{
				if (ship2.bulletList[j]->collidesWith(*explosionList[i], collisionVector)/* && explosionList[i]->getCurrentFrame() == 1*/)
				{

					SAFE_DELETE(ship2.bulletList[j]);
					ship2.bulletList.erase(ship2.bulletList.begin() + j);

				}
			}
		}

		for (int j = 0; j < ship1.missileList.size(); j++)
		{
			if (ship1.missileList[j] != NULL)
			{
				if (ship1.missileList[j]->collidesWith(*explosionList[i], collisionVector)/* && explosionList[i]->getCurrentFrame() == 1*/)
				{
					SAFE_DELETE(ship1.missileList[j]);
					ship1.missileList.erase(ship1.missileList.begin() + j);
				}
			}
		}


	}

	if (ship1.collidesWith(ship2, collisionVector))
	{
		ship1.bounce(collisionVector, ship2);
		audio->playCue(SHIPHITSHIP);
	}

	if (ship2.collidesWith(ship1, collisionVector))
	{
		ship2.bounce(collisionVector, ship1);
		audio->playCue(SHIPHITSHIP);
	}

	ship1.setPrevHP(ship1.getHP());
	ship2.setPrevHP(ship2.getHP());
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
	nebula.draw();

	nebulabackground1.draw();
	nebulabackground2.draw();

	                       // add the orion nebula to the scene

	
	//planet.draw();                          // add the planet to the scene
	if (startscreenon == true)
	{
		title.draw();
		PressEnterToStart.print("Press Enter to Start", GAME_WIDTH/2 -4.5 * spacewarNS::FONT_SIZE, (GAME_HEIGHT/2)+5*spacewarNS::FONT_SIZE);
	}
	else if (startscreenon == false)
	{
		for (int i = 0; i < ship1.lifeList.size(); i++)
		{
			ship1.lifeList[i]->draw();
		}

		for (int i = 0; i < ship2.lifeList.size(); i++)
		{
			ship2.lifeList[i]->draw();
		}



		//draw blackholes from ship 2
		if (ship2.blackholeList.size() > 0)
		{
			for (int i = 0; i < ship2.blackholeList.size(); i++)
			{
				ship2.blackholeList[i]->draw();
			}
		}

		ship1.draw();							// add the ship to the scene
		ship2.draw();							// add the cooler ship to the scene

		if (explosionList.size() > 0)
		{
			for (int i = 0; i < explosionList.size(); i++)
			{
				explosionList[i]->draw();
			}
		}

		// draw walls
		for (int i = 0; i < (wallListList.size()); i++)
		{
			for (int j = 0; j < (wallListList[i].size()); j++)
			{
				wallListList[i][j]->draw();
			}
		}

		//draw missiles from ship 1
		if (ship1.missileList.size() > 0)
		{
			for (int i = 0; i < ship1.missileList.size(); i++)
			{
				ship1.missileList[i]->draw();
			}
		}
		//draw mines from ship 1
		if (ship1.mineList.size() > 0)
		{
			for (int i = 0; i < ship1.mineList.size(); i++)
			{
				ship1.mineList[i]->draw();
			}
		}

		//draw bullets from ship 2
		if (ship2.bulletList.size() > 0)
		{
			for (int i = 0; i < ship2.bulletList.size(); i++)
			{
				ship2.bulletList[i]->draw();
			}
		}
		//Print Words
		Player1DamagePercent.print("Player 1\n" + ship1.getdamagestring(), spacewarNS::FONT_SIZE, GAME_HEIGHT - spacewarNS::FONT_SIZE * 2);		//Render Player Health Text
		Player1Label.print("Player 1\n     v", ship1.getCenterX() - 67, ship1.getCenterY() - spacewarNS::FONT_SIZE / 2 - spacewarNS::FONT_SIZE * 2);		//Render Player Label Text

		Player2DamagePercent.print("Player 2\n" + ship2.getdamagestring(), GAME_WIDTH - 5 * spacewarNS::FONT_SIZE, GAME_HEIGHT - spacewarNS::FONT_SIZE * 2);		//Render Player Health Text
		Player2Label.print("Player 2\n     v", ship2.getCenterX() - 67, ship2.getCenterY() - spacewarNS::FONT_SIZE / 2 - spacewarNS::FONT_SIZE * 2);		//Render Player Label Text

		if (ship1.lifeList.size() <= 0)
		{
			trigger += 1;
		}
		else if (ship2.lifeList.size() <= 0)
		{
			trigger += 1;
		}

		if (trigger == 1)
		{
			if (ship1.getLifeCount() < ship2.getLifeCount())
			{
				triggeredship = "Player 2";
			}
			else if (ship1.getLifeCount() > ship2.getLifeCount())
			{
				triggeredship = "Player 1";
			}
		}

		if (trigger >= 1)
		{
			gameOverText.print(triggeredship + " won!", GAME_WIDTH / 2, GAME_HEIGHT / 2);		//Render Player Label Text
		}
	}
	

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	//planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	ship1Texture.onLostDevice();
	ship2Texture.onLostDevice();
	wallTexture.onLostDevice();
	missileTexture.onLostDevice();
	explosionTexture.onLostDevice();
	bulletTexture.onLostDevice();
	mineTexture.onLostDevice();
	blackholeTexture.onLostDevice();
	rectTexture.onLostDevice();
	blueHeartTexture.onLostDevice();
	redHeartTexture.onLostDevice();

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
	nebulabackgroundTexture.onResetDevice();
	//planetTexture.onResetDevice();
	ship1Texture.onResetDevice();
	ship2Texture.onResetDevice();
	wallTexture.onResetDevice();
	missileTexture.onResetDevice();
	explosionTexture.onResetDevice();
	bulletTexture.onResetDevice();
	mineTexture.onResetDevice();
	blackholeTexture.onResetDevice();
	rectTexture.onResetDevice();
	blueHeartTexture.onResetDevice();
	redHeartTexture.onResetDevice();

    Game::resetAll();
    return;
}

void Spacewar::resetGame()
{
	for (int i = 0; i < wallListList.size(); i++)
	{
		for (int j = 0; j < wallListList[i].size(); j++)
		{
			if (wallListList[i][j] != NULL)
			{
				SAFE_DELETE(wallListList[i][j]);
				wallListList[i].erase(wallListList[i].begin() + j);
			}
		}
		wallListList[i].clear();
		//wallListList.erase(wallListList.begin() + i);
	}

	for (int i = 0; i < ship1.missileList.size(); i++)
	{
		if (ship1.missileList[i] != NULL)
		{
			SAFE_DELETE(ship1.missileList[i]);
			ship1.missileList.erase(ship1.missileList.begin() + i);
		}

	}
	for (int i = 0; i < ship1.mineList.size(); i++)
	{
		if (ship1.mineList[i] != NULL)
		{
			SAFE_DELETE(ship1.mineList[i]);
			ship1.mineList.erase(ship1.mineList.begin() + i);
		}

	}
	for (int i = 0; i < ship2.bulletList.size(); i++)
	{
		if (ship2.bulletList[i] != NULL)
		{
			SAFE_DELETE(ship2.bulletList[i]);

			ship2.bulletList.erase(ship2.bulletList.begin() + i);
		}

	}
	for (int i = 0; i < ship2.blackholeList.size(); i++)
	{
		if (ship2.blackholeList[i] != NULL)
		{
			SAFE_DELETE(ship2.blackholeList[i]);
			ship2.blackholeList.erase(ship2.blackholeList.begin() + i);
		}
	}
	//ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &ship1Texture);
	ship1.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);
	ship1.setCurrentFrame(shipNS::SHIP_START_FRAME);
	ship1.setLifeCount(shipNS::LIFE_COUNT);
	ship1.setVelocityX(0);
	ship1.setVelocityY(0);
	ship1.setRadians(0);
	ship1.setX(GAME_WIDTH / 4);
	ship1.setY(GAME_HEIGHT / 4);
	ship1.setHP(shipNS::MAX_HP);

	ship1.lifeList.clear();
	for (int i = 0; i < ship1.getLifeCount(); i++)
	{
		ship1.lifeList.push_back(new Image);
		ship1.lifeList[i]->initialize(graphics, 0, 0, 0, &blueHeartTexture);
		ship1.lifeList[i]->setScale(0.1);
		ship1.lifeList[i]->setX((wallNS::WIDTH*wallNS::SCALE) + i * (ship1.lifeList[i]->getWidth()*ship1.lifeList[i]->getScale()));
		ship1.lifeList[i]->setY(GAME_HEIGHT - (wallNS::WIDTH*wallNS::SCALE) - (ship1.lifeList[i]->getHeight()*ship1.lifeList[i]->getScale()));
	}

	//ship2.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &ship2Texture);
	ship2.setFrames(shipNS::SHIP_START_FRAME, shipNS::SHIP_END_FRAME);
	ship2.setCurrentFrame(shipNS::SHIP_START_FRAME);
	ship2.setLifeCount(shipNS::LIFE_COUNT);
	ship2.setVelocityX(0);
	ship2.setVelocityY(0);
	ship2.setRadians(0);
	ship2.setX(3 * GAME_WIDTH / 4);
	ship2.setY(GAME_HEIGHT / 4);
	ship2.setHP(shipNS::MAX_HP);

	ship2.lifeList.clear();
	for (int i = 0; i < ship2.getLifeCount(); i++)
	{
		ship2.lifeList.push_back(new Image);
		ship2.lifeList[i]->initialize(graphics, 0, 0, 0, &redHeartTexture);
		ship2.lifeList[i]->setScale(0.1);
		ship2.lifeList[i]->setX(GAME_WIDTH - (wallNS::WIDTH*wallNS::SCALE) - (i + 1) *(ship2.lifeList[i]->getWidth()*ship2.lifeList[i]->getScale()));
		ship2.lifeList[i]->setY(GAME_HEIGHT - (wallNS::WIDTH*wallNS::SCALE) - (ship2.lifeList[i]->getHeight()*ship2.lifeList[i]->getScale()));
	}

	//the walls on the top and bottom sides of the screen
	for (int i = 0; i < GAME_WIDTH / (wallNS::WIDTH*wallNS::SCALE); i++)
	{
		wallListList[3].push_back(new Wall());

		wallListList[3][wallListList[3].size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListList[3][wallListList[3].size() - 1]->setX(i*(wallNS::WIDTH*wallNS::SCALE));
		wallListList[3][wallListList[3].size() - 1]->setY(0);

		wallListList[3][wallListList[3].size() - 1]->setRadians(wallListList[3][wallListList[3].size() - 1]->getRadians() + PI);
	}

	for (int i = 0; i < GAME_WIDTH / (wallNS::WIDTH*wallNS::SCALE); i++)
	{
		wallListList[2].push_back(new Wall());

		wallListList[2][wallListList[2].size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListList[2][wallListList[2].size() - 1]->setX(i*(wallNS::WIDTH*wallNS::SCALE));
		wallListList[2][wallListList[2].size() - 1]->setY(GAME_HEIGHT - (wallNS::HEIGHT*wallNS::SCALE));
	}

	//the walls on the left and right side of the screen
	for (int i = 0; i < (GAME_HEIGHT - wallNS::HEIGHT) / (wallNS::HEIGHT*wallNS::SCALE); i++)
	{
		wallListList[1].push_back(new Wall());

		wallListList[1][wallListList[1].size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListList[1][wallListList[1].size() - 1]->setX(0);
		wallListList[1][wallListList[1].size() - 1]->setY((i + 1)*(wallNS::HEIGHT*wallNS::SCALE));

		wallListList[0][wallListList[1].size() - 1]->setRadians(wallListList[1][wallListList[1].size() - 1]->getRadians() + (PI / 2));
	}

	for (int i = 0; i < (GAME_HEIGHT - wallNS::HEIGHT) / (wallNS::HEIGHT*wallNS::SCALE); i++)
	{
		wallListList[0].push_back(new Wall());

		wallListList[0][wallListList[0].size() - 1]->initialize(this, wallNS::WIDTH, wallNS::HEIGHT, wallNS::TEXTURE_COLS, &wallTexture);
		wallListList[0][wallListList[0].size() - 1]->setX(GAME_WIDTH - (wallNS::WIDTH*wallNS::SCALE));
		wallListList[0][wallListList[0].size() - 1]->setY((i + 1)*(wallNS::HEIGHT*wallNS::SCALE));
		wallListList[0][wallListList[0].size() - 1]->setRadians(wallListList[0][wallListList[0].size() - 1]->getRadians() + ((3 * PI) / 2));
	}

	wallListList.push_back(wallListTop);		//wallListList[3] = wallListTop
	wallListList.push_back(wallListBottom);		//wallListList[2] = wallListBottom
	wallListList.push_back(wallListLeft);		//wallListList[1] = wallListLeft
	wallListList.push_back(wallListRight);		//wallListList[0] = wallListRight
}
//for (i = 0; i < wall list amount; i++) { wall[i].CollidesWith