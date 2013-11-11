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
	if (!platform.initialize(this,PLATFORM_WIDTH, PLATFORM_HEIGHT, 0, &platformTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));

	platform.setX(25);
	platform.setY(25);

	lastDirection = right;
	keyDownLastFrame = false;
	keyDownThisFrame = false;
	jumpedLastFrame = false;

    return;
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

	jpo.update(frameTime);
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
    
	platform.draw();
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