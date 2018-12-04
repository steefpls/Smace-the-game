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
	
		// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

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

	//blackhole object
	//if (!blackhole1.initialize(this, blackholeNS::WIDTH, blackholeNS::HEIGHT, blackholeNS::TEXTURE_COLS, &blackholeTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing black hole"));
	//blackhole1.setFrames(blackholeNS::BLACKHOLE_START_FRAME, blackholeNS::BLACKHOLE_END_FRAME);
	//blackhole1.setX(3 * GAME_WIDTH / 4);
	//blackhole1.setY(3 * GAME_HEIGHT / 4);

	//blackholeList.push_back(blackhole1);
	//ship1.setVelocity(VECTOR2(shipNS::SPEED, -shipNS::SPEED)); // VECTOR2(X, Y)

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//Scale Nebula to fullscreen
	nebula.setScale(GAME_WIDTH / nebula.getWidth());

	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	return;
}

//==========================================================================================================================================================================================================================
// Update all game items
//==========================================================================================================================================================================================================================
void Spacewar::update()
{
	//bullet1.update(frameTime); //update bullet frames

	ship1.update(frameTime);	//update ship frames
	ship2.update(frameTime);
	
	for (int i = 0; i < explosionList.size(); i++)
	{
		explosionList[i]->update(frameTime);
		if (explosionList[i]->getCurrentFrame() == explosionList[i]->getEndFrame())
		{
			SAFE_DELETE(explosionList[i]);
			explosionList.erase(explosionList.begin() + i);
		}
	}
	
	

	for (int i = 0; i < wallListList.size(); i++)
	{
		for (int j = 0; j < wallListList[i].size(); j++)
		{
			wallListList[i][j]->update(frameTime);	//update top wall frames
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

	for (int i = 0; i < ship1.missileList.size(); i++)									//Update all ship1 missile objects
	{
		ship1.missileList[i]->update(frameTime);
	}

	if (input->isKeyDown(player1Secondary) && ship1.getmissiletimer()<0)				//If player is pressing X, shoot missiles
	{
		ship1.spawnmissile();
		ship1.missileList[ship1.missileList.size() - 1]->initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture);
		ship1.setMissileXY();
	}

	for (int i = 0; i < ship1.missileList.size(); i++)				//check if missile is out of bounds
	{
		if (ship1.missileList[i]->getX() > GAME_WIDTH || ship1.missileList[i]->getX() < 0 - ship1.missileList[i]->getHeight())
		{
			SAFE_DELETE(ship1.missileList[i]);
			ship1.missileList.erase(ship1.missileList.begin() + i);
		}
		else if (ship1.missileList[i]->getY() > GAME_HEIGHT || ship1.missileList[i]->getY() < 0 - ship1.missileList[i]->getHeight())
		{
			SAFE_DELETE(ship1.missileList[i]);
			ship1.missileList.erase(ship1.missileList.begin() + i);	
		}
	}

	//MINE
	if (input->isKeyDown(player1Primary) && ship1.getminetimer() < 0)				//If player is pressing X, shoot mines
	{
		ship1.spawnmine();
		ship1.mineList[ship1.mineList.size() - 1]->initialize(this, mineNS::WIDTH, mineNS::HEIGHT, mineNS::TEXTURE_COLS, &mineTexture);
		if (ship1.mineList.size() > ship1.getmaxmines())
		{
			SAFE_DELETE(ship1.mineList[0]);
			ship1.mineList.erase(ship1.mineList.begin() + 0);
		}
		ship1.setMineXY();
	}

	for (int i = 0; i < ship1.mineList.size(); i++)								//Update all ship1 mine objects
	{
		ship1.mineList[i]->update(frameTime);
	}

	for (int i = 0; i < ship1.mineList.size(); i++)				//check if mine is out of bounds
	{
		if (ship1.mineList[i]->getX() > GAME_WIDTH || ship1.mineList[i]->getX() < 0 - ship1.mineList[i]->getHeight())
		{
			SAFE_DELETE(ship1.mineList[i]);
			ship1.mineList.erase(ship1.mineList.begin() + i);
		}
		else if (ship1.mineList[i]->getY() > GAME_HEIGHT || ship1.mineList[i]->getY() < 0 - ship1.mineList[i]->getHeight())
		{
			SAFE_DELETE(ship1.mineList[i]);
			ship1.mineList.erase(ship1.mineList.begin() + i);
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
		double degdiff = ship2.getdegreespread() / (ship2.getnoofbullets() - 1);

		for (int i = 0; i < (ship2.getnoofbullets()); i++)
		{
			ship2.spawnbullet();
			ship2.bulletList[ship2.bulletList.size() - 1]->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
			ship2.setBulletXY((-ship2.getdegreespread() / 2) + i * degdiff);
		}
	}

	for (int i = 0; i < ship2.bulletList.size(); i++)	//Bullet Deletion when exits boundaries
	{
		if (ship2.bulletList[i]->getX() > GAME_WIDTH || ship2.bulletList[i]->getX() < 0 - ship2.bulletList[i]->getHeight())
		{
			SAFE_DELETE(ship2.bulletList[i]);
			ship2.bulletList.erase(ship2.bulletList.begin() + i);
		}
		else if (ship2.bulletList[i]->getY() > GAME_HEIGHT || ship2.bulletList[i]->getY() < 0 - ship2.bulletList[i]->getHeight())
		{
			SAFE_DELETE(ship2.bulletList[i]);
			ship2.bulletList.erase(ship2.bulletList.begin() + i);
		}
	}

	if (input->isKeyDown(player2Secondary) && ship2.getblackholetimer()<=0)			//Update black hole
	{
		ship2.spawnblackhole();
		ship2.blackholeList[ship2.blackholeList.size() - 1]->initialize(this, blackholeNS::WIDTH, blackholeNS::HEIGHT, blackholeNS::TEXTURE_COLS, &blackholeTexture);
		ship2.blackholeList[ship2.blackholeList.size() - 1]->setScale(0.3);
		ship2.setBlackholeXY();
		
	}

	for (int i = 0; i < ship2.blackholeList.size(); i++)								//Update all ship2 blackhole objects
	{
		ship2.blackholeList[i]->update(frameTime);
	}


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
					ship1.setDamage(ship1.getDamage() + 0.1);
				}
				else if (check == 2 || check == 4)
				{
					wallListList[i][j]->setHP(wallListList[i][j]->getHP() - abs(ship1.getVelocityX()));
					ship1.leftrightrotatebounce();
					ship1.setDamage(ship1.getDamage() + 0.1);
				}				
			}

			for (int x = 0; x < (ship1.missileList.size()); x++)													//If missile collides with wall
			{
				if (ship1.missileList[x]->collidesWith(*wallListList[i][j], collisionVector))
				{
					wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship1.missileList[x]->getDamage());
					SAFE_DELETE(ship1.missileList[x]);
					ship1.missileList.erase(ship1.missileList.begin() + x);		
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

			if (wallListList[i][j]->getHP() <= 0)
			{
				SAFE_DELETE(wallListList[i][j]);
				wallListList[i].erase(wallListList[i].begin() + j);
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
					ship2.setDamage(ship2.getDamage() + 0.1);
				}
				else if (check == 2 || check == 4)
				{
				wallListList[i][j]->setHP(wallListList[i][j]->getHP() - abs(ship2.getVelocityX()));
				ship2.leftrightrotatebounce();
				ship2.setDamage(ship2.getDamage() + 0.1);
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
						wallListList[i][j]->setHP(wallListList[i][j]->getHP() - ship2.bulletList[x]->getDamage());
						SAFE_DELETE(ship2.bulletList[x]);
						ship2.bulletList.erase(ship2.bulletList.begin() + x);
					}
				}
			}

			if (wallListList[i][j]->getHP() <= 0)
			{
				SAFE_DELETE(wallListList[i][j]);
				wallListList[i].erase(wallListList[i].begin() + j);
			}
		}
	}

	//MINE COLLISION
	for (int i = 0; i < (ship1.mineList.size()); i++)
	{
		for (int j = 0; j < (ship2.bulletList.size()); j++)
		{
			if (ship1.mineList[i]->collidesWith(*ship2.bulletList[j], collisionVector))
			{
				ship1.mineList[i]->bounce(collisionVector, *ship2.bulletList[j]);
				ship1.mineList[i]->setHP(ship1.mineList[i]->getHP() - ship2.bulletList[j]->getDamage());

				SAFE_DELETE(ship2.bulletList[j]);
				ship2.bulletList.erase(ship2.bulletList.begin() + j);
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
			if (ship1.mineList[i]->collidesWith(*ship1.missileList[j], collisionVector))
			{
				ship1.mineList[i]->setHP(ship1.mineList[i]->getHP() - ship1.missileList[j]->getDamage());
				SAFE_DELETE(ship1.missileList[j]);
				ship1.missileList.erase(ship1.missileList.begin() + j);
			}
		}

		if (ship1.mineList[i]->collidesWith(ship2,collisionVector))
		{
			ship1.mineList[i]->setHP(0);
		}

		if (ship1.mineList[i]->getHP() <= 0)
		{
			explosionList.push_back(new Explosion);
			explosionList[explosionList.size() - 1]->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
			explosionList[explosionList.size() - 1]->setFrames(explosionNS::EXPLOSION_START_FRAME, explosionNS::EXPLOSION_END_FRAME);
			explosionList[explosionList.size() - 1]->setX(ship1.mineList[i]->getCenterX());
			explosionList[explosionList.size() - 1]->setY(ship1.mineList[i]->getCenterY());
			SAFE_DELETE(ship1.mineList[i]);
			ship1.mineList.erase(ship1.mineList.begin() + i);
		}		
	}

	//BULLET COLLISION
	for (int i = 0; i < (ship2.bulletList.size()); i++)
	{
		if (ship2.bulletList[i]->collidesWith(ship1, collisionVector))
		{
			ship1.setDamage(ship1.getDamage() + (ship2.bulletList[i]->getDamage()/ship1.getDamageResistance()));
			ship1.bounce(collisionVector,*ship2.bulletList[i]);
		}
	}
	//if (ship1.collidesWith(missile1, collisionVector))
	//{
	//	ship1.setX(600);
	//	ship1.setY(600);
	//}

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
	for (int i = 0; i<(wallListList.size());i++)
	{
		for(int j = 0; j<(wallListList[i].size());j++)
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