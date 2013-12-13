
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef DREHMAN_H                 // Prevent multiple definitions if this 
#define DREHMAN_H 

class Menu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include <vector>
#include "input.h"
#include <fstream>
#include <sstream>

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
   int selectedItem2;
   std::string menuHeading;
   std::string creditHeading;
   std::string instructionHeading;
   std::string cheatHeading;
   D3DXVECTOR2 menuAnchor;
   std::vector<std::string> menu;
   std::vector<std::string> credit;
   std::vector<std::string> instruction;
   std::vector<std::string> cheat;
   int verticalOffset;
   int linePtr;
   int linePtr2;
   COLOR_ARGB highlightColor ;
   COLOR_ARGB normalColor;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;
   bool credits;
   bool instructions;
   bool cheats;
   bool score;
   std::vector<bool> cheatCodes;
   std::string scoreHeading;
   std::vector<int> scores;

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
	void displayCredits();
	bool getCredits(){return credits;}
	void setCredits(bool Credits){credits=Credits;}
	void displayInstructions();
	bool getInstructions(){return instructions;}
	void setInstructions(bool Instructions){instructions=Instructions;}
	void Menu::displayCheats();
	bool getCheats(){return cheats;}
	void setCheats(bool Cheats){cheats=Cheats;}
	int getSelectedItem2() {return selectedItem2;}
	void setSelectedItem2(int number) {selectedItem2=number;}
	void setHighScoresInfo(std::ifstream& fin1, std::string fileName);
	void setHighScores(bool scoring){score=scoring;}
	bool getHighScores(){return score;}
	void displayHighScores();
	std::vector<bool> getCheatCodes(){return cheatCodes;}
};
#endif
