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
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void RaccoonRun::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	if (!jpoTexture.initialize(graphics,JPO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

    if (!jpo.initialize(this,JPO_WIDTH, JPO_HEIGHT, JPO_COLS, &jpoTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo"));
    jpo.setX(GAME_WIDTH/4);
    jpo.setY(GAME_HEIGHT - (GAME_HEIGHT/3));
    jpo.setFrames(JPO_LOOKING_RIGHT_START, JPO_LOOKING_RIGHT_END);   // animation frames
    jpo.setCurrentFrame(JPO_LOOKING_RIGHT_START);     // starting frame
    jpo.setFrameDelay(JPO_ANIMATION_DELAY);

	lastDirection = right;
	keyDownLastFrame = false;
	keyDownThisFrame = false;
    return;

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void RaccoonRun::update()
{
	// JPo code imported from class exercise - added jumping to test platform
	if(input->isKeyDown(JPO_JUMP_KEY))
	{
		// make JPo jump (need to implement gravity!)
	}
	if(input->isKeyDown(JPO_RIGHT_KEY))            // if move right
	{
		if(!keyDownLastFrame || lastDirection == left)
		{
			jpo.setFrames(JPO_WALKING_RIGHT_START, JPO_WALKING_RIGHT_END);
			jpo.setCurrentFrame(JPO_WALKING_RIGHT_START);
		}

		jpo.setX(jpo.getX() + frameTime * JPO_SPEED);
		if (jpo.getX() > GAME_WIDTH)               // if off screen right
			jpo.setX((float)-jpo.getWidth());     // position off screen left

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

		jpo.setX(jpo.getX() - frameTime * JPO_SPEED);
		if (jpo.getX() < -jpo.getWidth())         // if off screen left
			jpo.setX((float)GAME_WIDTH);           // position off screen right

		lastDirection = left;
		keyDownLastFrame = keyDownThisFrame;
		keyDownThisFrame = true;
	}
	else
	{
		if(keyDownLastFrame)
		{
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
    
	jpo.draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void RaccoonRun::releaseAll()
{
	jpoTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void RaccoonRun::resetAll()
{
	jpoTexture.onResetDevice();

    Game::resetAll();
    return;
}