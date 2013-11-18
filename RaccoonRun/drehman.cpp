
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

	creditHeading = "Thanks to:";
	credit.push_back("Christy Phillips");
	credit.push_back("Ethan Johnson");
	credit.push_back("Thomas Drehman");

	instructionHeading = "Instructions";
	instruction.push_back("Space to have raccoon jump");
	instruction.push_back("Left arrow to move raccon left");
	instruction.push_back("Right arrow to move raccoon right");
	instruction.push_back("Escape to quit to menu");

	cheatHeading = "These options are cheats";
	cheat.push_back("Spacebar for flight, but beware of the fate of Icarus");
	cheat.push_back("Immortality, but you may start feeling like Sisyphus");
	cheat.push_back("Level 1 skip, but you are sleeping in the bed of Procrustes");

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
	if(linePtr > menu.size()-1) linePtr = 0;
	if(linePtr < 0) linePtr = menu.size()-1;
	if (input->isKeyDown(VK_RETURN))
		selectedItem = linePtr;
	else selectedItem = -1;
	if(linePtr2 > cheat.size()-1) linePtr2 = 0;
	if(linePtr2 < 0) linePtr2 = cheat.size()-1;
}

void Menu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);
	for(int j=0;j<menu.size();++j)
	{
		if(linePtr==j)
		{
			menuItemFontHighlight->print(menu[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset);
		}
		else
		{
			menuItemFont->print(menu[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset);
		}
	}
}

void Menu::displayCredits()
{
	menuHeadingFont->print(creditHeading, menuAnchor.x, menuAnchor.y);
	for(int j=0;j<credit.size();++j)
	{
		menuItemFont->print(credit[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset);
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
		menuItemFont->print(instruction[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset);
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
			menuItemFontHighlight->print(cheat[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset);
		else
			menuItemFont->print(cheat[j], menuAnchor.x, menuAnchor.y + (j+1)*verticalOffset);
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
