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

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void RaccoonRun::update()
{}

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
    


    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void RaccoonRun::releaseAll()
{
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void RaccoonRun::resetAll()
{
    Game::resetAll();
    return;
}