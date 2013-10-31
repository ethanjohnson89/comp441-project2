// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 9 dashboardDemo.h v1.0

#ifndef _DASHBOARDDEMO_H       // Prevent multiple definitions if this 
#define _DASHBOARDDEMO_H       // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "constants.h"
#include "textureManager.h"
#include "image.h"
#include "dashboard.h"

// screen locations
const int HBAR_X = 10;
const int HBAR_Y = 80;
const int VBAR_X = 100;
const int VBAR_Y = 80;
const int DIAL180_X = 170;
const int DIAL180_Y = 80;
const int DIAL270_X = 250;
const int DIAL270_Y = 80;
const int DIAL360_X = 330;
const int DIAL360_Y = 80;
const int LIGHT_X = 10;
const int LIGHT_Y = 150;
const int DIGITS_X = 10;
const int DIGITS_Y = 10;
const int TOGGLE_X = 100;
const int TOGGLE_Y = 150;
const int BAR_GRAPH_X = 280;
const int BAR_GRAPH_Y = 150;
const int PUSH_X = 250;
const int PUSH_Y = 170;

class DashboardDemo : public Game
{
private:
	// game variables
    TextureManager  dashboardTextures;
    Bar             horizontalBar;
    Bar             verticalBar;
    DialGauge       dial180, dial270, dial360;
    Light           light;
    SevenSegment    sevenSegment;
    ToggleSwitch    toggleSwitch;
    PushButton      pushButton;
    BarGraph        barGraph;
    float horizontal, vertical, dial, vu;

public:
    DashboardDemo();
    virtual ~DashboardDemo();
    void initialize(HWND hwnd);
	void reset();
    void update();
    void ai() {};
    void collisions() {};
    void render();
	void releaseAll();
	void resetAll();
};

#endif
