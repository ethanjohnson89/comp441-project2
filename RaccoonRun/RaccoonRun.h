#ifndef _RACCOONRUN_H       // Prevent multiple definitions if this 
#define _RACCOONRUN_H       // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "constants.h"
#include "textureManager.h"
#include "image.h"
#include "entity.h"
#include "dashboard.h"
#include "Character.h"
#include "Still.h"
#include "platform.h"
#include "raccoon.h"
#include "menu.h"

using std::string;
using std::endl;
using std::stringstream;

class RaccoonRun : public Game
{
private:
	// game variables
    TextureManager jpoTexture;
	Raccoon jpo;
	
	TextureManager csTexture;
	Character cs;

	TextureManager platformTexture;
	Platform platform[15];

	TextureManager raccoonTexture;

		//background textures
	TextureManager backgroundTexture;
	Still background;

	enum LastDirection {left, right} lastDirection;
	bool keyDownLastFrame;
	bool keyDownThisFrame;
	bool jumpedLastFrame;
	bool moveScreenRight;
	bool moveScreenLeft;

	//game over?
	bool gameOver;

	//should JPO be able to jump
	bool onLand;

	//preemptive Easter Egg Bool
	bool fly;

	TextDX *debugFont; // for debugging

	Menu* menu;
	int gameState;
	bool audioOn;


public:
    RaccoonRun();
    virtual ~RaccoonRun();
    void initialize(HWND hwnd);
	void reset();
    void update();
    void ai();
    void collisions();
    void render();
	void releaseAll();
	void resetAll();
	void setPlatformData(int level);
};

#endif
