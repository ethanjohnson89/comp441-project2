#ifndef raccoon_h               // Prevent multiple definitions if this 
#define raccoon_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Johnson.h"
#include "constants.h"

namespace raccoonNS
{
    const float MASS = 1.0f;
}

// inherits from Entity class
class Raccoon : public Character
{
private:
	int lives;
	bool onLand;
public:
    // constructor
	Raccoon();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    void update(float frameTime);
	//bool collidesWith(float frameTime, Entity object);
	void incrementLivesBy(int x){lives+=x;}
	void setLives(int x) { lives = x; }
	int getLives(){return lives;}
	void setOnLand(bool on){onLand=on;}
	bool getOnLand(){return onLand;}
};
#endif