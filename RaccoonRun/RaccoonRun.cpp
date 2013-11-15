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

    if (!jpo.initialize(this,JPO_WIDTH, JPO_HEIGHT, JPO_COLS, &raccoonTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing raccoon"));

	if (!cs.initialize(this,JPO_WIDTH, JPO_HEIGHT, JPO_COLS, &jpoTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CS"));

    jpo.setX(GAME_WIDTH/2);
    jpo.setY(GAME_HEIGHT - (GAME_HEIGHT/3));
    jpo.setFrames(RACCOON_LOOKING_RIGHT_START, RACCOON_LOOKING_RIGHT_END);   // animation frames


	cs.setX(25);
	cs.setY(GAME_HEIGHT-(10+JPO_HEIGHT));
	cs.setVelocity(D3DXVECTOR2(90.0f,0));

	jpo.setFrames(JPO_LOOKING_RIGHT_START, JPO_LOOKING_RIGHT_END);

	if(!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));

	if(!backgroundTexture.initialize(graphics, BACKGROUND_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background.initialize(this,BACKGROUND_WIDTH, BACKGROUND_HEIGHT, 0, &backgroundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	background.setX(-5);
	background.setY(0);

	setPlatformData(1);	//eventually, will need to call it with level data.
	//can just use an arbitrary integer for right now.

	lastDirection = right;
	keyDownLastFrame = false;
	keyDownThisFrame = false;
	jumpedLastFrame = false;

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
		float newX=i*PLATFORM_WIDTH+i*150;
		platform[i].setWorldX(newX); //these should be thought of as constants for each level.
		//platform[i].setWorldY(2*GAME_HEIGHT/3);
		platform[i].setWorldY(350);
		platform[i].setX(newX);
		//platform[i].setY(2*GAME_HEIGHT/3);
		platform[i].setScale(.75);
		platform[i].setY(350);
	}
	
}

//=============================================================================
// Update all game items
//=============================================================================
void RaccoonRun::update()
{
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
		newVelocity = VECTOR2(JPO_SPEED, newVelocity.y);

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
		newVelocity = VECTOR2(-JPO_SPEED, newVelocity.y);

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
		int maxX=BACKGROUND_WIDTH-GAME_WIDTH;
		if(background.getX()>-(maxX))
			moveScreenRight=true;
		else
			moveScreenRight=false;
		//PostQuitMessage(0);
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
		//PostQuitMessage(0);
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


	//if(moveScreenLeft)
	//{
	//	//PostQuitMessage(0);
	//	for(int i=0; i<15; i++)
	//	{
	//		float newX=platform[i].getX()+1;
	//		platform[i].setX(newX);
	//	}
	//}
	//else if(moveScreenRight)
	//{
	//	for(int i=0; i<15; i++)
	//	{
	//		float newX=platform[i].getX()-1;
	//		platform[i].setX(newX);
	//	}
	//}
	for(int i=0; i<15; i++)
	{
		platform[i].update(frameTime, moveScreenLeft, moveScreenRight);
	}
	background.update(frameTime, moveScreenLeft, moveScreenRight);

	cs.update(frameTime);
	if(jpo.collidesWith(frameTime, cs))
	{
		jpo.setVisible(false);
		gameOver=true;
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
	background.draw();
	if(!gameOver)
	{
		for(int i=0; i<15; i++)
		{
			platform[i].draw();
		}

		jpo.draw();
		cs.draw();
	}
	else
	{
		debugFont->print("Game OVER.",0,0);
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
	backgroundTexture.onLostDevice();

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
	backgroundTexture.onResetDevice();

    Game::resetAll();
    return;
}