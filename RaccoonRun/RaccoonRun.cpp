#include "RaccoonRun.h"

//=============================================================================
// Constructor
//=============================================================================
RaccoonRun::RaccoonRun()
{}

//=============================================================================
// Destructor
//=============================================================================
RaccoonRun::~RaccoonRun()
{
    releaseAll();           // call onLostDevice() for every graphics item
	delete debugFont;
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void RaccoonRun::initialize(HWND hwnd)
{

    Game::initialize(hwnd); // throws GameError
	//game does not start finished
	gameOver=false;

	//score init
	score=0;
	//level init
	level=1;

	//set boolean for no easter egg.
	fly=false;
	//JPO starts on ground.
	onLand=true;
	// Initialize fonts
	debugFont = new TextDX();
    if(debugFont->initialize(graphics, 30, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	debugFont->setFontColor(graphicsNS::RED);

	// Initialize textures and images
	if (!jpoTexture.initialize(graphics,JPO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

	if(!raccoonTexture.initialize(graphics, RACCOON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing raccoon texture"));

	if(!cpsoupTexture.initialize(graphics, CPSOUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheeseburger pizza soup texture"));

	//setSoupData();

    if (!jpo.initialize(this,JPO_WIDTH, JPO_HEIGHT, JPO_COLS, &raccoonTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing raccoon"));

	if (!cs.initialize(this,JPO_WIDTH, JPO_HEIGHT, JPO_COLS, &jpoTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CS"));


	//if (!cpsoup.initialize(this,CPSOUP_WIDTH, CPSOUP_HEIGHT, CPSOUP_COLS, &cpsoupTexture))
 //       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheeseburger pizza soup"));

 //   jpo.setX(30);
 //   jpo.setY(175-RACCOON_HEIGHT);
 //   jpo.setFrames(RACCOON_LOOKING_RIGHT_START, RACCOON_LOOKING_RIGHT_END);   // animation frames


	//cs.setX(25);
	//cs.setY(GAME_HEIGHT-(10+JPO_HEIGHT));
	//cs.setVelocity(D3DXVECTOR2(90.0f,0));

	levelSet();

	jpo.setFrames(JPO_LOOKING_RIGHT_START, JPO_LOOKING_RIGHT_END);
	cs.setFrames(JPO_WALKING_RIGHT_START, JPO_WALKING_RIGHT_END);

	//cpsoup.set(30, GAME_HEIGHT - (10+CPSOUP_HEIGHT));
	//cpsoup.setVisible(true);

	if(!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));

	

	//setPlatformData(1);	//eventually, will need to call it with level data.
	//can just use an arbitrary integer for right now.

	lastDirection = right;
	keyDownLastFrame = false;
	keyDownThisFrame = false;
	jumpedLastFrame = false;

	menu = new Menu();
	menu->initialize(graphics, input);

	gameState = 0;
	audioOn = true;
	//audio->playCue(LEVEL);

    return;
}

//=========================================================================
// Set by Christy. This initializes the platform data, based on what level we're at. 
// Supposedly. Not functional quite yet.
//=========================================================================
void RaccoonRun::setPlatformData(int level)
{
	//this will set the world coordinates of the platform positions.
	//will eventually be based on what level we are currently on.
	for(int i=0; i<15; i++)
	{
		if (!platform[i].initialize(this,PLATFORM_WIDTH, PLATFORM_HEIGHT, 0, &platformTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));
			//float newX=i*PLATFORM_WIDTH+i*150;
			//platform[i].setWorldX(newX); //these should be thought of as constants for each level.
			////platform[i].setWorldY(2*GAME_HEIGHT/3);
			//platform[i].setWorldY(350);
			//platform[i].setX(newX);
			//platform[i].setY(2*GAME_HEIGHT/3);
			platform[i].setScale(.75);
		platform[i].setVisible(false);
		platform[i].set(-500,-500); //gets unused platforms out of the way.
		
	}
	switch(level)
	{
	case 1:
		//audio->playCue(LEVEL);
		for(int i=0; i<9; i++)
		{
			
			platform[i].setVisible(true);
			//platform[i].setY(350);
		}
		platform[0].set(29,176);
		platform[1].set(350,135);
		platform[2].set(405,232);
		platform[3].set(636,310);
		platform[4].set(686,164);
		platform[5].set(964,222);
		platform[6].set(1225,130);
		platform[7].set(1494,222);
		platform[8].set(1705,130);
		break;
	case 2:
		for(int i=0; i<7; i++)
		{
			platform[i].setVisible(true);
			platform[i].setScale(.65);
		}
		platform[0].set(17,123);
		platform[1].set(170,253);
		platform[2].set(331,172);
		platform[3].set(325,354);
		platform[4].set(625,141);
		platform[5].set(638,412);
		platform[6].set(948,147);
	}

	audio->playCue(LEVEL);
}

//=============================================================================
// Update all game items
//=============================================================================
void RaccoonRun::update()
{
	switch(gameState)
	{
		case 0:
			menu->update();
			if(menu->getSelectedItem() == 0)
			{
				if(!gameOver)
					gameState = 1;
				
//				else
			}
			else if(menu->getSelectedItem() == 1)
			{
				if(audioOn)
					audioOn = false;
				else
					audioOn = true;
			}
			else if(menu->getSelectedItem() == 2)
			{
				menu->setInstructions(true);
			}
			else if(menu->getSelectedItem() == 3)
			{
				menu->setCredits(true);
			}
			else if(menu->getSelectedItem() == 4)
			{
				PostQuitMessage(0);
			}
			break;
		case 1:
		// JPo code imported from class exercise - added jumping to test platform
			VECTOR2 newVelocity = jpo.getVelocity();

			if(input->isKeyDown(JPO_JUMP_KEY) && onLand)
			{
				// make JPo jump!
				if(!jumpedLastFrame)
					newVelocity = VECTOR2(newVelocity.x, -750);
				jumpedLastFrame = true;
			}
			else
				jumpedLastFrame = false;
				
			if(input->isKeyDown(JPO_RIGHT_KEY))            // if move right
			{
				if(!keyDownLastFrame || lastDirection == left)
				{
					jpo.setFrames(JPO_WALKING_RIGHT_START, JPO_WALKING_RIGHT_END);
					jpo.setCurrentFrame(JPO_WALKING_RIGHT_START);
				}
	
				//jpo.setX(jpo.getX() + frameTime * JPO_SPEED);
				newVelocity = VECTOR2(RACCOON_SPEED, newVelocity.y);
	
				lastDirection = right;
				keyDownLastFrame = keyDownThisFrame;
				keyDownThisFrame = true;
			}
			else if(input->isKeyDown(JPO_LEFT_KEY))             // if move left
			{
				if(!keyDownLastFrame || lastDirection == right)
				{
					jpo.setCurrentFrame(JPO_WALKING_LEFT_START);
					jpo.setFrames(JPO_WALKING_LEFT_START, JPO_WALKING_LEFT_END);
				}

				//jpo.setX(jpo.getX() - frameTime * JPO_SPEED);
				newVelocity = VECTOR2(-RACCOON_SPEED, newVelocity.y);

				lastDirection = left;
				keyDownLastFrame = keyDownThisFrame;
				keyDownThisFrame = true;
			}
			else
			{
				if(keyDownLastFrame)
				{
					newVelocity = VECTOR2(0, newVelocity.y);
					if(lastDirection == right)
					{
						jpo.setFrames(JPO_LOOKING_RIGHT_START, JPO_LOOKING_RIGHT_END);
						jpo.setCurrentFrame(JPO_LOOKING_RIGHT_START);
					}
					else // lastDirection == left
					{
						jpo.setFrames(JPO_LOOKING_LEFT_START, JPO_LOOKING_LEFT_END);
						jpo.setCurrentFrame(JPO_LOOKING_LEFT_START);
					}
				}

				keyDownLastFrame = keyDownThisFrame;
				keyDownThisFrame = false;
			}

			jpo.setVelocity(newVelocity);
			int jpoX=jpo.getX(); //to create a test for updating platform screen coords.
			jpo.update(frameTime);

			//Platform Updates. Checks to see if they need to move.
			if(jpoX==jpo.getX() && input->isKeyDown(JPO_RIGHT_KEY))
			{
				//if(platform[14].getX()>GAME_WIDTH-platform[14].getWidth()*platform[14].getScale())
				int maxX=background[level-1].getWidth()-GAME_WIDTH;
				if(background[level-1].getX()>-(maxX))
					moveScreenRight=true;
				else
					moveScreenRight=false;
			}
			else
			{
				moveScreenRight=false;
			}
			if(jpoX==jpo.getX() && input->isKeyDown(JPO_LEFT_KEY))
			{
				if(platform[0].getX()<5)//arbitrarily cannot move if more than 5px away.
					moveScreenLeft=true;
				else
					moveScreenLeft=false;
			}
			else{
				moveScreenLeft=false;
			}
			//checks if JPO is on a surface
			if(jpo.getY()>=GAME_HEIGHT-JPO_HEIGHT)
			{
				onLand=true;
			}
			else
			{
				onLand=false;
			}

			for(int i=0; i<15; i++)
			{
				platform[i].update(frameTime, moveScreenLeft, moveScreenRight);
			}
			background[level-1].update(frameTime, moveScreenLeft, moveScreenRight);

			cs.update(frameTime);
			checkPoint.update(frameTime, moveScreenLeft, moveScreenRight);
			if(cs.collidesWithRaccoon(frameTime, jpo))
			{
				jpo.setVisible(false);
				/*gameOver=true;*/
				paused = true;
			}

			for(int i=0; i<3; i++)
			{
				cpsoup[i].update(frameTime, moveScreenLeft, moveScreenRight);
			}

			break;
		}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void RaccoonRun::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void RaccoonRun::collisions()
{

	for(int i=0; i<15 && onLand!=true; i++)
	{
		if(jpo.collidesWith(frameTime,platform[i]) && jpo.getVelocity().y>=0)
		{
			onLand=true;
			jpo.setY(platform[i].getY()-(jpo.getHeight()*jpo.getScale()-10)-1);
			jpo.setVelocity(D3DXVECTOR2(0,0));
			break;
		}
	}
}

//=============================================================================
// Render game items
//=============================================================================
void RaccoonRun::render()
{
	graphics->spriteBegin();                // begin drawing sprites
	switch(gameState)
	{
	case 0:
		if(menu->getCredits())
			menu->displayCredits();
		else if(menu->getInstructions())
			menu->displayInstructions();
		else
			menu->displayMenu();
		break;
	case 1:
		background[level-1].draw();
		if(!gameOver)
		{
			for(int i=0; platform[i].getVisible(); i++)//this keeps track of which platforms are visible.
			{
				//throw(GameError(gameErrorNS::FATAL_ERROR, "Made it to "));
				platform[i].draw();
			}
			for(int i=0; i<3; i++)
			{
				cpsoup[i].draw();
			}
			checkPoint.draw();
			jpo.draw();
			cs.draw();
			
		}
		else
		{
			debugFont->print("Game OVER.",0,0);
			if(input->isKeyDown(VK_ESCAPE))
				gameState=0;
		}
		break;
		}
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void RaccoonRun::releaseAll()
{
	debugFont->onLostDevice();
	
	jpoTexture.onLostDevice();
	platformTexture.onLostDevice();
	cpsoupTexture.onLostDevice();
	backgroundTexture[0].onLostDevice();
	backgroundTexture[1].onLostDevice();
	backgroundTexture[2].onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void RaccoonRun::resetAll()
{
	debugFont->onLostDevice();

	jpoTexture.onResetDevice();
	platformTexture.onResetDevice();
	cpsoupTexture.onResetDevice();
	backgroundTexture[0].onResetDevice();
	backgroundTexture[1].onResetDevice();
	backgroundTexture[2].onResetDevice();

    Game::resetAll();
    return;
}
void RaccoonRun::levelSet()
{
	switch (level)
	{
	case 1:
		jpo.setX(30);
		jpo.setY(175-RACCOON_HEIGHT);
		jpo.setFrames(RACCOON_LOOKING_RIGHT_START, RACCOON_LOOKING_RIGHT_END);   // animation frames
		jpo.setVisible(true);

		cs.setX(25);
		cs.setY(GAME_HEIGHT-(10+JPO_HEIGHT));
		cs.setVelocity(D3DXVECTOR2(90.0f,0));

		setStillData();

		break;
	case 2:
		jpo.setX(17);
		jpo.setY(163-RACCOON_HEIGHT);
		jpo.setFrames(RACCOON_LOOKING_RIGHT_START, RACCOON_LOOKING_RIGHT_END);   // animation frames
		jpo.setVisible(true);

		cs.setX(25);
		cs.setY(GAME_HEIGHT-(10+JPO_HEIGHT));
		cs.setVelocity(D3DXVECTOR2(90.0f,0));

		setStillData();

		break;
	}
}
void RaccoonRun::setStillData()
{
	setBgData();
	setPlatformData(level);
	setSoupData();
	//checkpoint stuff
	if(!checkpointTexture.initialize(graphics, CHECKPOINT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing checkpoint texture"));
	if (!checkPoint.initialize(this,CHECKPOINT_WIDTH, CHECKPOINT_HEIGHT, 0, &checkpointTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing checkpoint"));
	checkPoint.set(1930,76);
}
void RaccoonRun::setSoupData()
{
	for(int i=0; i<3; i++)
	{
		if (!cpsoup[i].initialize(this,CPSOUP_WIDTH, CPSOUP_HEIGHT, CPSOUP_COLS, &cpsoupTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheeseburger pizza soup"));
		cpsoup[i].setScale(.5);
	}
	switch(level)
	{
	case 1:
		cpsoup[0].set(277,400);
		cpsoup[1].set(685,400);
		cpsoup[2].set(964,110);
		break;
	case 2:
		cpsoup[0].set(149,423);
		cpsoup[1].set(400,310);
		cpsoup[2].set(863,400);
		break;
	}
}
void RaccoonRun::setBgData()
{
	if(!backgroundTexture[0].initialize(graphics, BACKGROUND1A_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background[0].initialize(this,BACKGROUND1A_WIDTH, BACKGROUND_HEIGHT, 0, &backgroundTexture[0]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if(!backgroundTexture[1].initialize(graphics, BACKGROUND1B_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background[1].initialize(this,BACKGROUND1B_WIDTH, BACKGROUND_HEIGHT, 0, &backgroundTexture[1]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if(!backgroundTexture[2].initialize(graphics, BACKGROUND2_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background[2].initialize(this,BACKGROUND2_WIDTH, BACKGROUND_HEIGHT, 0, &backgroundTexture[2]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	for(int i=0; i<3; i++)
	{
		background[i].set(-5,0);
	}
}
void RaccoonRun::reset()
{
	if(level<3)
		level++;
	setStillData();
}