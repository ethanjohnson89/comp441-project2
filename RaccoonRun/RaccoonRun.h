#ifndef _RACCOONRUN_H       // Prevent multiple definitions if this 
#define _RACCOONRUN_H       // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "constants.h"
#include "textureManager.h"
#include "image.h"
#include "entity.h"
#include "dashboard.h"
#include "Johnson.h"
#include "Still.h"
#include "platform.h"
#include "cpsoup.h"
#include "raccoon.h"
#include "drehman.h"
#include "walkingGuard.h"
#include "phillips.h"
#include "cheeseburger.h"
#include "pizza.h";
#include "DrehmanLaser.h"
#include "DrehmanSniper.h"
#include <sstream>
#include <fstream>

using std::string;
using std::endl;
using std::stringstream;
using std::ifstream;
using std::ofstream;

class RaccoonRun : public Game
{
private:
	//high scores
	ifstream fin;
	ofstream fout; //sorry, just my default name for them.
	//blame Dr. Adams, if you wish...
	int highScores[MAX_SCORES];

	// game variables
	TextureManager blackTexture;
	Image blackBar;

	TextureManager livesTexture;
	Image lives[6];

	TextureManager raccoonTexture;
    TextureManager jpoTexture;
	TextureManager jpoDownTexture;
	Raccoon jpo;
	
	WalkingGuard cs;
	WalkingGuard shorty;
	Still officerDown;
	Still shortyDown;

	TextureManager cpsoupTexture;
	CPSoup cpsoup[3];

	TextureManager cheeseburgerTexture;
	Cheeseburger cheeseburger[3];

	TextureManager pizzaTexture;
	Pizza pizza[3];

	TextureManager laserTexture;
	Laser laser;

	TextureManager sniperTexture;
	Sniper sniper;

	TextureManager platformTexture;
	Platform platform[15];

	TextureManager l1EndTexture;
	Image l1End;

	TextureManager l2EndTexture;
	Image l2End;

	Image between[2];

		//background textures
	TextureManager backgroundTexture[3];
	Still background[3];

	TextureManager menuBackgroundTexture;
	Image menuBackground;

	TextureManager menuBackgroundTexture2;
	Image menuBackground2;

	TextureManager splashTexture;
	Image splash;

	TextureManager winTexture;
	Image winScreen;
	
	TextureManager loseTexture;
	Image lose;

	TextureManager checkpointTexture;
	Checkpoint checkPoint;

	enum LastDirection {left, right} lastDirection;
	bool keyDownLastFrame;
	bool keyDownThisFrame;
	bool jumpedLastFrame;
	bool moveScreenRight;
	bool moveScreenLeft;

	TextureManager frisbeeTexture;
	Frisbee frisbee;	

	//game over?
	bool gameOver;
	bool win;

	//should JPO be able to jump
	bool onLand;
	bool grassAudio;

	//preemptive Easter Egg Bool
	bool fly;
	bool immortal;

	TextDX *debugFont; // for debugging

	Menu* menu;
	int gameState;
	bool audioOn;

	int oldScore;
	int score;
	int level;
	bool menu2;
	bool debouncer;

	int pastCheckpoint;

	//Raccoon Starting Positions; includes checkpoints.
	COORD raccoonStart[3][2]; //3 levels, 2 states: precheckpoint & postcheckpoint.
	//raccoonStart[2][1] will be empty.
	COORD backgroundSet[3][2];//this is for the purpose of setting background image position.

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
	//void reinit();
	void writeHighScores();
	void chkPtReset(int cpIndex, int pIndex, int cIndex);
	void setCheckpoint(bool set){
		if(set==false)
			pastCheckpoint=0;
		else
			pastCheckpoint=1;
	}
};

#endif
