#ifndef character_h               // Prevent multiple definitions if this 
#define character_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace characterNS
{
    const float MASS = 1.0f;
}

// inherits from Entity class
class Character : public Entity
{
public:
    // constructor
	Character();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    void update(float frameTime);
};
#endif