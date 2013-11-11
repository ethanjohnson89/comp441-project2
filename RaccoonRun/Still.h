#ifndef still_h               // Prevent multiple definitions if this 
#define still_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace stillNS
{
    const float MASS = 1.0f;
}

// inherits from Entity class
class Still : public Entity
{
	float worldX;
	float worldY;
public:
    // constructor
	Still();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    void update(float frameTime, bool left, bool right);
	void setWorldX(float x){worldX=x;}
	void setWorldY(float y){worldY=y;}
	void update(bool moveLeft, bool moveRight);
};
#endif