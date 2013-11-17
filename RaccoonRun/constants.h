// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine constants.h v2.7
// Last modification: Apr-3-2013

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "RaccoonRun";
const char GAME_TITLE[] = "Raccoon Run";
const bool FULLSCREEN = false;          // windowed or fullscreen
const UINT GAME_WIDTH = 640;			// width of game in pixels
const UINT GAME_HEIGHT = 480;			// height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0;         // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 2000.0f;                  // acceleration of gravity pixels/sec

// graphic images
const char DASHBOARD_TEXTURES[] = "pictures\\dashboard.png";
const char JPO_IMAGE[]   = "pictures\\JPo Sheet.png";
const char RACCOON_IMAGE[] = "pictures\\raccoonSheet1.png";
const char CPSOUP_IMAGE[] = "pictures\\CheeseburgerPizzaSoup.png";
	
//platform images
const char PLATFORM_TEXTURE[]="pictures\\platform1.png";
//background images
const char BACKGROUND1A_TEXTURE[]="pictures\\background1a.png";
const char BACKGROUND1B_TEXTURE[]="pictures\\background1b.png";
const char BACKGROUND2_TEXTURE[]="pictures\\background2.png";

const float JPO_ANIMATION_DELAY = 0.2f;    // time between frames of ship animation
//JPO Cel
const int  JPO_COLS = 4;
const int  JPO_WIDTH = 128;
const int  JPO_HEIGHT = 130;
const int  JPO_HALF_WIDTH = 22;
const int  JPO_HALF_HEIGHT = 48;

//JPO actions
const int JPO_LOOKING_RIGHT_START = 0;			//1st row
const int JPO_LOOKING_RIGHT_END = 3;
const int JPO_LOOKING_LEFT_START = 4;				//2nd row
const int JPO_LOOKING_LEFT_END = 7;
const int JPO_WALKING_RIGHT_START = 8;
const int JPO_WALKING_RIGHT_END = 11;
const int JPO_WALKING_LEFT_START = 12;
const int JPO_WALKING_LEFT_END = 15;

//raccoon cel
const int RACCOON_COLS = 4;
const int RACCOON_WIDTH = 128;
const int RACCOON_HEIGHT = 115;
const int RACCOON_HALF_WIDTH = 43;
const int RACCOON_HALF_HEIGHT = 25;
//const int RACCOON_START_Y = 

//raccoon actions
const int RACCOON_LOOKING_RIGHT_START = 0;			//1st row
const int RACCOON_LOOKING_RIGHT_END = 3;
const int RACCOON_LOOKING_LEFT_START = 4;				//2nd row
const int RACCOON_LOOKING_LEFT_END = 7;
const int RACCOON_WALKING_RIGHT_START = 8;
const int RACCOON_WALKING_RIGHT_END = 11;
const int RACCOON_WALKING_LEFT_START = 12;
const int RACCOON_WALKING_LEFT_END = 15;
const int RACCOON_JUMPING_RIGHT_START = 16;
const int RACCOON_JUMPING_RIGHT_END = 17;
const int RACCOON_JUMPING_RIGHT_DOWN_START = 18;
const int RACCOON_JUMPING_RIGHT_DOWN_END = 19;
const int RACCOON_JUMPING_LEFT_START = 20;
const int RACCOON_JUMPING_LEFT_END = 21;
const int RACCOON_JUMPING_LEFT_DOWN_START = 22;
const int RACCOON_JUMPING_LEFT_DOWN_END = 23;

// cheeseburger pizza soup cels
const int CPSOUP_COLS = 4;
const int CPSOUP_WIDTH = 81;
const int CPSOUP_HEIGHT = 96;
const int CPSOUP_HALF_WIDTH = 40;
const int CPSOUP_HALF_HEIGHT = 48;
const float CPSOUP_ANIMATION_DELAY = 0.5f;

//const float JPO_SPEED = 90.5f;
const float JPO_SPEED=100.0f;
const float RACCOON_SPEED = 200.0f;

//still constants.
const float STILL_SPEED = 100.0f;

//platform Constants
const int PLATFORM_WIDTH = 256;
const int PLATFORM_HEIGHT = 64;
const int PLATFORM_HALF_WIDTH = 128;
const int PLATFORM_HALF_HEIGHT = 32;

//background constants
const int BACKGROUND1A_WIDTH=2048;
const int BACKGROUND1B_WIDTH=1024;
const int BACKGROUND2_WIDTH=2048;
const int BACKGROUND_HEIGHT=512;




// audio files
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

//audio cues
const char LEVEL[] = "raccoonLevel1";

// audio cues

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = VK_OEM_3;    // `~ key for U.S.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key

const UCHAR JPO_LEFT_KEY    = VK_LEFT;     // left arrow
const UCHAR JPO_RIGHT_KEY   = VK_RIGHT;    // right arrow
const UCHAR JPO_UP_KEY      = VK_UP;       // up arrow
const UCHAR JPO_DOWN_KEY    = VK_DOWN;     // down arrow
const UCHAR JPO_JUMP_KEY	= VK_SPACE;	   // spacebar

#endif
