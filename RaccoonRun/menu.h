
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef MENU_H                 // Prevent multiple definitions if this 
#define MENU_H 

class Menu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include <vector>
#include "input.h"

namespace menuNS
{ }

// inherits from Entity class
class Menu 
{
private:
   TextDX *menuItemFont;
   TextDX *menuItemFontHighlight;
   TextDX *menuHeadingFont;
   Input   *input;         // pointer to the input system
   Graphics *graphics;
   int selectedItem;
   std::string menuHeading;
   D3DXVECTOR2 menuAnchor;
   std::vector<std::string> menu;
   int MenuNumber;
   int verticalOffset;
   int linePtr;
   COLOR_ARGB highlightColor ;
   COLOR_ARGB normalColor;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;

public:
    // constructor
    Menu();
	void initialize(Graphics *g, Input *i);
	void update();
	int getSelectedItem() {return selectedItem;}
	void displayMenu();
	void setLinePtr(int LinePtr) {linePtr=LinePtr;}
	int getLinePtr() {return linePtr;}
	int getMenuSize() {return menu.size();}
	void setSelectedItem(int number) {selectedItem=number;}
};
#endif
