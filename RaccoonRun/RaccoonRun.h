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
#include "cpsoup.h"
#include "raccoon.h"
#include "menu.h"
#include "walkingGuard.h"
#include "phillips.h"
#include "cheeseburger.h"
#include "pizza.h";

using std::string;
using std::endl;
using std::stringstream;

class RaccoonRun : public Game
{
private:
	// game variables
	TextureManager blackTexture;
	Image blackBar;

	TextureManager livesTexture;
	Image lives[5];

    TextureManager jpoTexture;
	Raccoon jpo;
	
	TextureManager csTexture;
	WalkingGuard cs;

	TextureManager cpsoupTexture;
	CPSoup cpsoup[3];

	TextureManager cheeseburgerTexture;
	Cheeseburger cheeseburger[3];

	TextureManager pizzaTexture;
	Pizza pizza[3];

	TextureManager platformTexture;
	Platform platform[15];

	TextureManager raccoonTexture;

		//background textures
	TextureManager backgroundTexture[3];
	Still background[3];

	TextureManager menuBackgroundTexture;
	Image menuBackground;

	TextureManager checkpointTexture;
	Checkpoint checkPoint;

	enum LastDirection {left, right} lastDirection;
	bool keyDownLastFrame;
	bool keyDownThisFrame;
	bool jumpedLastFrame;
	bool moveScreenRight;
	bool moveScreenLeft;

	//game over?
	bool gameOver;
	bool win;

	//should JPO be able to jump
	bool onLand;

	//preemptive Easter Egg Bool
	bool fly;

	TextDX *debugFont; // for debugging

	Menu* menu;
	int gameState;
	bool audioOn;

	int score;
	int level;

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
	void setStillData();
	void setPlatformData(int level);
	void setSoupData();
	void setCheeseburgerData();
	void setPizzaData();
	void setBgData();
	void levelSet();
	void statusSet();
};

#endif
