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

	// Initialize fonts
	debugFont = new TextDX();
    if(debugFont->initialize(graphics, 30, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	debugFont->setFontColor(graphicsNS::RED);

	// Initialize textures and images
	if (!jpoTexture.initialize(graphics,JPO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

    if (!jpo.initialize(this,JPO_WIDTH, JPO_HEIGHT, JPO_COLS, &jpoTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo"));
    jpo.setX(GAME_WIDTH/4);
    jpo.setY(GAME_HEIGHT - (GAME_HEIGHT/3));
    jpo.setFrames(JPO_LOOKING_RIGHT_START, JPO_LOOKING_RIGHT_END);   // animation frames


	if(!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));

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
		float newX=i*PLATFORM_WIDTH+i*5;
		platform[i].setWorldX(newX); //these should be thought of as constants for each level.
		platform[i].setWorldY(GAME_HEIGHT/2);
		platform[i].setX(newX);
		platform[i].setY(GAME_HEIGHT/2);
		platform[i].setScale(.75);
	}
	
}

//=============================================================================
// Update all game items
//=============================================================================
void RaccoonRun::update()
{
	// JPo code imported from class exercise - added jumping to test platform
	VECTOR2 newVelocity = jpo.getVelocity();

	if(input->isKeyDown(JPO_JUMP_KEY))
	{
		// make JPo jump!
		if(!jumpedLastFrame)
			newVelocity = VECTOR2(newVelocity.x, -500);
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
	if(jpoX==jpo.getX() && input->isKeyDown(JPO_RIGHT_KEY))
	{
		if(platform[14].getX()>GAME_WIDTH-platform[14].getWidth()*platform[14].getScale())
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
{}

//=============================================================================
// Render game items
//=============================================================================
void RaccoonRun::render()
{
	graphics->spriteBegin();                // begin drawing sprites
    for(int i=0; i<15; i++)
	{
		platform[i].draw();
	}

	jpo.draw();

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
	platformTexture.onLostDevice();

    Game::resetAll();
    return;
}