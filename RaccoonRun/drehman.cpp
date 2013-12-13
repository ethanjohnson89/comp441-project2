
#include "drehman.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
}

void Menu::initialize(Graphics *g, Input *i)
{
	menuHeading ="Raccoon Run";

	menu.push_back("Start Game");
	menu.push_back("Instructions");
	menu.push_back("Credits");
	menu.push_back("Quit");
	menu.push_back("Totally not cheating");
	menu.push_back("High Scores");

	creditHeading = "Thanks to:";
	credit.push_back("Christy Phillips");
	credit.push_back("Ethan Johnson");
	credit.push_back("Thomas Drehman");

	instructionHeading = "Instructions";
	instruction.push_back("Space to have raccoon jump");
	instruction.push_back("Left arrow to move raccon left");
	instruction.push_back("Right arrow to move raccoon right");
	instruction.push_back("Escape to return to menu");

	cheatHeading = "These options are cheats";
	cheat.push_back("Spacebar for flight, but beware of the fate of Icarus");
	cheat.push_back("Immortality, but you may start feeling like Sisyphus");
//	cheat.push_back("Level 1 skip, but you are sleeping in the bed of Procrustes");

	scoreHeading = "High Scores";

	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;
	menuAnchor = D3DXVECTOR2(270,10);
	input = i;
	verticalOffset = 30;
	linePtr = 0;
	linePtr2 = 0;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 15, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 18, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 25, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
	credits = false;
	instructions = false;
	cheats = false;
	score = false;
	for(int i=0;i<cheat.size();++i)
	{
		cheatCodes.push_back(false);
	}
}

void Menu::update()
{
	if (input->isKeyDown(VK_UP)&&input->wasKeyPressed(VK_UP))
	{
		if(cheats)
			linePtr2--;
		else
			linePtr--;
	}
	if (input->isKeyDown(VK_DOWN)&&input->wasKeyPressed(VK_DOWN))
	{
		if(cheats)
			linePtr2++;
		else
			linePtr++;
	}
	if(linePtr == menu.size()) linePtr = 0;
	if(linePtr < 0) linePtr = menu.size()-1;
	if (input->isKeyDown(VK_RETURN))
		selectedItem = linePtr;
	else selectedItem = -1;
	if(linePtr2 == cheat.size()) linePtr2 = 0;
	if(linePtr2 < 0) linePtr2 = cheat.size()-1;
}

void Menu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);
	for(int j=0;j<menu.size();++j)
	{
		if(linePtr==j)
		{
			menuItemFontHighlight->print(menu[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset/1.2);
		}
		else
		{
			menuItemFont->print(menu[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset/1.2);
		}
	}
}

void Menu::displayCredits()
{
	menuHeadingFont->print(creditHeading, menuAnchor.x, menuAnchor.y);
	for(int j=0;j<credit.size();++j)
	{
		menuItemFont->print(credit[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset/1.2);
	}
	if(input->isKeyDown(VK_ESCAPE))
	{
		credits = false;
	}
	return;
}
void Menu::displayInstructions()
{
	menuHeadingFont->print(instructionHeading, menuAnchor.x, menuAnchor.y);
	for(int j=0;j<instruction.size();++j)
	{
		menuItemFont->print(instruction[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset/1.2);
	}
	if(input->isKeyDown(VK_ESCAPE))
	{
		instructions = false;
	}
	return;
}

void Menu::displayCheats()
{
	menuHeadingFont->print(cheatHeading, menuAnchor.x, menuAnchor.y);
	for(int j=0;j<cheat.size();++j)
	{
		if(linePtr2 == j)
			menuItemFontHighlight->print(cheat[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset/1.2);
		else
			menuItemFont->print(cheat[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset/1.2);
	}
	if(input->isKeyDown(VK_ESCAPE))
	{
		cheats = false;
	}
	if(input->isKeyDown(VK_RETURN))
	{
		//cheatCodes[linePtr2] = true;
		selectedItem2 = linePtr2;
	}
	return;
}
void Menu::setHighScoresInfo(std::ifstream& fin1,std::string fileName)
{
	scores.clear();
	fin1.open(fileName);
	int score_number;
	for(int i=1;i<10;++i)
	{
		if(!fin1.eof())
		{
			fin1 >> score_number;
			scores.push_back(score_number);
		}
		else
			scores.push_back(0);
	}
	fin1.close();
}
void Menu::displayHighScores()
{
	std::stringstream foo;
	menuHeadingFont->print(scoreHeading, menuAnchor.x, menuAnchor.y);
	for(int j=0;j<scores.size();++j)
	{
		foo << scores[j];
		std::string stuff;
		foo>>stuff;
		menuItemFont->print(stuff, menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset/1.7);
		foo.clear();
	}
	
	if(input->isKeyDown(VK_ESCAPE))
	{
		score = false;
	}
	return;
}