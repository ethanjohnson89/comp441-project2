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

#include <string>
using std::string;
using std::endl;
#include <sstream>
using std::stringstream;

class RaccoonRun : public Game
{
private:
	// game variables
    TextureManager jpoTexture;
	Character jpo;
	enum LastDirection {left, right} lastDirection;
	bool keyDownLastFrame;
	bool keyDownThisFrame;
	bool jumpedLastFrame;

	TextDX *debugFont; // for debugging

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
};

#endif
