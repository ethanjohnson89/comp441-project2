
#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
}

void Menu::initialize(Graphics *g, Input *i)
{
	menuHeading ="Test Menu";

	menu.push_back("Start Game");
	menu.push_back("Enable SoundFX");
	menu.push_back("Credits");

	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;
	menuAnchor = D3DXVECTOR2(270,10);
	input = i;
	verticalOffset = 30;
	linePtr = 0;
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
	MenuNumber = 1;

}

void Menu::update()
{
	if (input->isKeyDown(VK_UP)&&input->wasKeyPressed(VK_UP))
	{
		linePtr--;
	}
	if (input->isKeyDown(VK_DOWN)&&input->wasKeyPressed(VK_DOWN))
	{
		linePtr++;
	}
	if(linePtr > menu.size()-1) linePtr = 0;
	if(linePtr < 0) linePtr = menu.size()-1;
	if (input->isKeyDown(VK_RETURN))
		selectedItem = linePtr;
	else selectedItem = -1;
}

void Menu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);
	if(MenuNumber == 1)
	{
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
}