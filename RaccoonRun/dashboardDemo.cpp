// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 9 dashboardDemo.cpp v1.0

#include "dashboardDemo.h"

//=============================================================================
// Constructor
//=============================================================================
DashboardDemo::DashboardDemo()
{
    horizontal = 100;
    vertical = 100;
    dial = 0;
    vu = 100;
}

//=============================================================================
// Destructor
//=============================================================================
DashboardDemo::~DashboardDemo()
{
    releaseAll();				// call deviceLost() for every graphics item
}


//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void DashboardDemo::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // gauge textures
    if (!dashboardTextures.initialize(graphics, DASHBOARD_TEXTURES))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard textures"));

    horizontalBar.initialize(graphics, &dashboardTextures, HBAR_X, HBAR_Y, 1.0f, graphicsNS::LIME);

    verticalBar.initialize(graphics, &dashboardTextures, VBAR_X, VBAR_Y, 1.0f, graphicsNS::YELLOW);
    verticalBar.setDegrees(270);

    dial180.initialize(graphics, &dashboardTextures, DIAL180_X, DIAL180_Y, 1.0f, dashboardNS::DIAL180, 0.0f, graphicsNS::BLUE, graphicsNS::YELLOW);
    dial270.initialize(graphics, &dashboardTextures, DIAL270_X, DIAL270_Y, 1.0f, dashboardNS::DIAL270, 0.0f, graphicsNS::BLUE, graphicsNS::YELLOW);
    dial360.initialize(graphics, &dashboardTextures, DIAL360_X, DIAL360_Y, 1.0f, dashboardNS::DIAL360, 0.0f, graphicsNS::BLUE, graphicsNS::YELLOW);

    light.initialize(graphics, &dashboardTextures, LIGHT_X, LIGHT_Y, 0.5f, 1.0f, graphicsNS::LIME, graphicsNS::GREEN);

    sevenSegment.initialize(graphics, &dashboardTextures, DIGITS_X, DIGITS_Y, 0.5f, 8, graphicsNS::RED);

    toggleSwitch.initialize(graphics, &dashboardTextures, input, hwnd, TOGGLE_X, TOGGLE_Y, 1.0f);

    pushButton.initialize(graphics, &dashboardTextures, input, hwnd, PUSH_X, PUSH_Y, 0.5f, true);

    barGraph.initialize(graphics, &dashboardTextures, BAR_GRAPH_X, BAR_GRAPH_Y, 1.0f, 10, graphicsNS::ORANGE);
}


//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void DashboardDemo::reset()
{
    return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void DashboardDemo::update()
{
    if(toggleSwitch.getSwitchOn())  // if toggle switch on
    {
        horizontal += frameTime*20; // increase horizontal
        vertical += frameTime*30;   // increase vertical
        dial += frameTime*10;       // increase dial
    }
    if(horizontal > 100)            // reset when 100 is reached
        horizontal -= 100;
    if(vertical > 100)
        vertical -= 100;
    if(dial > 100)
        dial -= 100;
    horizontalBar.set(horizontal);  // set horizontal bar size
    verticalBar.set(vertical);      // set vertical bar size
    dial180.set(dial);              // set dial positions
    dial270.set(dial);
    dial360.set(dial);
    light.update(frameTime);        // update the controls
    toggleSwitch.update(frameTime);
    pushButton.update(frameTime);
    sevenSegment.set(fps);          // display fps in seven segment
    if(pushButton.getSwitchOn())    // if push button switch on
        vu += frameTime*100;        // increase vu
    if(vu > 100)
        vu -= 100;
    barGraph.set(vu);               // set bar graph with vu
}

//=============================================================================
// render game items and do end of round logic
//=============================================================================
void DashboardDemo::render()
{
    graphics->spriteBegin();                // begin drawing sprites
    horizontalBar.draw(graphicsNS::FILTER);
    verticalBar.draw(graphicsNS::FILTER);
    dial180.draw(graphicsNS::FILTER);
    dial270.draw(graphicsNS::FILTER);
    dial360.draw(graphicsNS::FILTER);
    light.draw(graphicsNS::FILTER);
    sevenSegment.draw(graphicsNS::FILTER);
    toggleSwitch.draw();
    pushButton.draw();
    barGraph.draw(graphicsNS::FILTER);
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void DashboardDemo::releaseAll()
{
    dashboardTextures.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void DashboardDemo::resetAll()
{
    dashboardTextures.onResetDevice();

    Game::resetAll();
    return;
}
