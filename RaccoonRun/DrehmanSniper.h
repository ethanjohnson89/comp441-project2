#ifndef DrehmanSniper_h               // Prevent multiple definitions if this 
#define DrehmanSniper_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Still.h"
#include "constants.h"

namespace sniperNS
{
    const float MASS = 1.0f;
}

// inherits from Entity class
class Sniper : public Still
{
public:
    // constructor
	Sniper();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    void update(float frameTime, bool left, bool right);
	bool collidesWithRaccoon(float frameTime, Entity object);
	void ai(Entity *player);
private:
	bool turnLeft, turnRight;
};
#endif