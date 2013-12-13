#include "RaccoonRun.h"

//=============================================================================
// Constructor
//=============================================================================
RaccoonRun::RaccoonRun()
{}

//=============================================================================
// Destructor
//=============================================================================
RaccoonRun::~RaccoonRun()
{
    releaseAll();           // call onLostDevice() for every graphics item
	delete debugFont;
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
//void RaccoonRun::reinit()
//{
//
//}
void RaccoonRun::initialize(HWND hwnd)
{

    Game::initialize(hwnd); // throws GameError
	//game does not start finished
	gameOver=false;
	win=false;

	//figure out high scores.
	fin.open("highScores.txt");
	int s;
	for(int i=0; i<MAX_SCORES; i++)
	{
		if(!fin.fail())
			fin>>s;
		if(fin.fail() || fin.eof())
		{
			for(i; i<MAX_SCORES; i++)
			{highScores[i]=0;}
			break;
		}
		highScores[i]=s;
		
	}
	fin.close();

	//score init
	score=0;
	oldScore=0;
	//level init
	level=1;

	statusSet();

	//set boolean for no easter egg.
	fly=false;
	immortal=false; 
	//JPO starts on ground.
	jpo.setOnLand(true);
	// Initialize fonts
	debugFont = new TextDX();
    if(debugFont->initialize(graphics, 30, true, false, "Times New Roman") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	debugFont->setFontColor(graphicsNS::WHITE);

	// Initialize textures and images
	if(!backgroundTexture[0].initialize(graphics, BACKGROUND1A_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background[0].initialize(this,BACKGROUND1A_WIDTH, BACKGROUND_HEIGHT, 0, &backgroundTexture[0]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if(!backgroundTexture[1].initialize(graphics, BACKGROUND1B_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background[1].initialize(this,BACKGROUND1B_WIDTH, BACKGROUND_HEIGHT, 0, &backgroundTexture[1]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if(!backgroundTexture[2].initialize(graphics, BACKGROUND2_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!background[2].initialize(this,BACKGROUND2_WIDTH, BACKGROUND_HEIGHT, 0, &backgroundTexture[2]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));


	//level transition textures
	if(!l1EndTexture.initialize(graphics, LEVEL1_END))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing l1end texture"));
	if (!l1End.initialize(graphics,BACKGROUND1A_WIDTH, BACKGROUND_HEIGHT, 0, &l1EndTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error l1end"));
	if(!l2EndTexture.initialize(graphics, LEVEL2_END))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing l2end texture"));
	if (!l2End.initialize(graphics,BACKGROUND1A_WIDTH, BACKGROUND_HEIGHT, 0, &l2EndTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error l2end"));
	l1End.setX(0);
	l2End.setX(0);
	l1End.setY(0);
	l2End.setY(0);

	//between screen stuff
	between[0]=l1End;
	between[1]=l2End;

	if(!checkpointTexture.initialize(graphics, CHECKPOINT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing checkpoint texture"));
	if (!checkPoint.initialize(this,CHECKPOINT_WIDTH, CHECKPOINT_HEIGHT, 0, &checkpointTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing checkpoint"));

	if(!blackTexture.initialize(graphics, BLACK_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!blackBar.initialize(graphics,0, 0, 0, &blackTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing black bar"));

	if(!livesTexture.initialize(graphics, LIVES_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	for(int i=0; i<5; i++)	
	{
		if (!lives[i].initialize(graphics,256, 256, 0, &livesTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lives image"));
	}

	if (!jpoTexture.initialize(graphics,JPO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

	if (!menuBackgroundTexture.initialize(graphics,MENU_TEXTURE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if(!menuBackground.initialize(graphics, 800,512,0,&menuBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu background"));
	menuBackground.setX(0);
	menuBackground.setY(0);

	if (!menuBackgroundTexture2.initialize(graphics,MENU_TEXTURE2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if(!menuBackground2.initialize(graphics, 800,512,0,&menuBackgroundTexture2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu background"));
	menuBackground2.setX(0);
	menuBackground2.setY(0);

	//Frisbee initialization
	if(!frisbeeTexture.initialize(graphics, FRISBEE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing frisbee texture"));
	if (!frisbee.initialize(this,FRISBEE_WIDTH, FRISBEE_HEIGHT, 0, &frisbeeTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing frisbee"));
	frisbee.setX(-25);
	frisbee.setY(-250);
	frisbee.setScale(.75);

	if (!splashTexture.initialize(graphics,SPLASH_TEXTURE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!splash.initialize(graphics, 800,512,0,&splashTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu background"));

	if (!winTexture.initialize(graphics,WIN_TEXTURE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!winScreen.initialize(graphics, 800,512,0,&winTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu background"));

	if (!loseTexture.initialize(graphics,LOSE_TEXTURE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!lose.initialize(graphics, 800,512,0,&loseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu background"));


	if(!raccoonTexture.initialize(graphics, RACCOON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing raccoon texture"));

	if(!cpsoupTexture.initialize(graphics, CPSOUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheeseburger pizza soup texture"));
	for(int i = 0; i < 3; i++)
		if (!cpsoup[i].initialize(this,CPSOUP_WIDTH, CPSOUP_HEIGHT, CPSOUP_COLS, &cpsoupTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheeseburger pizza soup"));

	if (!cheeseburgerTexture.initialize(graphics,CHEESEBURGER_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheeseburger texture"));
	for(int i = 0; i < 3; i++)
		if (!cheeseburger[i].initialize(this,CHEESEBURGER_WIDTH, CHEESEBURGER_HEIGHT, 0, &cheeseburgerTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheeseburger"));

	if (!pizzaTexture.initialize(graphics,PIZZA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pizza texture"));
	for(int i = 0; i < 3; i++)
		if (!pizza[i].initialize(this,PIZZA_WIDTH, PIZZA_HEIGHT, 0, &pizzaTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pizza"));

	if(!sniperTexture.initialize(graphics, SNIPER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sniper texture"));
	if (!sniper.initialize(this,SNIPER_WIDTH, SNIPER_HEIGHT, SNIPER_COLS, &sniperTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sniper"));

	if(!laserTexture.initialize(graphics, LASER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing laser texture"));
	if (!laser.initialize(this,LASER_WIDTH, LASER_HEIGHT, 1, &laserTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing laser"));
	//change laser size.
	laser.setScale(.75);
	//laser data
	laser.xInit=1000;
	laser.yInit=LASER_Y_INIT;
	laser.setX(1000);
	//setSoupData();

    if (!jpo.initialize(this,RACCOON_WIDTH, RACCOON_HEIGHT, RACCOON_COLS, &raccoonTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing raccoon"));

	if (!cs.initialize(this,JPO_WIDTH, JPO_HEIGHT, JPO_COLS, &jpoTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CS"));

	levelSet();

	jpo.setFrames(JPO_LOOKING_RIGHT_START, JPO_LOOKING_RIGHT_END);
	jpo.setEdge(COLLISION_BOX_RACCOON); //Added by Christy 11/30
	cs.setFrames(JPO_WALKING_RIGHT_START, JPO_WALKING_RIGHT_END);


	if(!platformTexture.initialize(graphics, PLATFORM_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform texture"));
	for(int i = 0; i < 15; i++)
		if (!platform[i].initialize(this,PLATFORM_WIDTH, PLATFORM_HEIGHT, 0, &platformTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing platform"));

	lastDirection = right;
	keyDownLastFrame = false;
	keyDownThisFrame = false;
	jumpedLastFrame = false;

	menu = new Menu();
	menu->initialize(graphics, input);

	menu2=false;

	gameState = 0;
	audioOn = true;
	//audio->playCue(LEVEL);

	debouncer = false;

	audio->playCue(MENU);

    return;
}

//=========================================================================
// Set by Christy. This initializes the platform data, based on what level we're at. 
// Supposedly. Not functional quite yet.
//=========================================================================
void RaccoonRun::setPlatformData(int level)
{
	//this will set the world coordinates of the platform positions.
	//will eventually be based on what level we are currently on.
	for(int i=0; i<15; i++)
	{
		platform[i].setScale(.75);
		platform[i].setVisible(false);
		platform[i].set(-2000,-500); //gets unused platforms out of the way.
		
	}
	switch(level)
	{
	case 1:
		for(int i=0; i<14; i++)
		{
			
			platform[i].setVisible(true);
			//platform[i].set(2000,0);
			//platform[i].setY(350);
		}
		/*platform[0].set(29,176);
		platform[1].set(375,135);
		platform[2].set(506,315);
		platform[3].set(686,164);
		platform[4].set(964,222);
		platform[5].set(1225,130);
		platform[6].set(1494,222);
		platform[7].set(1805,130);
		platform[8].set(1300,320);*/
		//platform[0].set(650,147);
		platform[0].set(570,352);
		platform[1].set(300,241);
		platform[2].set(31,325);
		platform[3].set(-275,172);
		platform[7].set(-675,320);
		platform[8].set(-1050,200);
		platform[9].set(-1350,350);
		platform[10].set(-1550,162);
		platform[11].set(-1880,330);
		platform[12].set(-2180,220);
		platform[13].set(-2400,100);
		break;
	case 2:
		for(int i=0; i<8; i++)
		{
			platform[i].setVisible(true);
			platform[i].setScale(.75);
		}
		//platform[0].set(17,123);
		//platform[1].set(170,253);
		//platform[2].set(380,172);
		//platform[3].set(325,354);
		platform[3].set(275,324);
		//platform[4].set(625,141);
		platform[5].set(690,372);
//		platform[6].set(948,147);
		platform[7].set(1205,357);
		break;
	case 3:
		for(int i=0; i<7; i++)
		{
			platform[i].setVisible(true);
			platform[i].setScale(.75);
		}
		platform[0].set(67,260);
		platform[1].set(475,232);
		platform[2].set(806,188);
		platform[3].set(1076,279);
		platform[4].set(1486,265);
		platform[5].set(1701,291);
		platform[6].set(175,350);
		break;
	}

	//audio->playCue(LEVEL);
}

//=============================================================================
// Update all game items
//=============================================================================
void RaccoonRun::update()
{
	int jpoX=jpo.getX(); //to create a test for updating platform screen coords.
	VECTOR2 newVelocity = jpo.getVelocity();
	VECTOR2 collisionVector;
	float tracking_x,tracking_y,absolute;
	switch(gameState)
	{
		case 0:
			menu->update();
			if(menu->getSelectedItem() == 0)
			{
				debouncer = true;
				if(debouncer && !input->isKeyDown(VK_RETURN))
				{
					debouncer = false;
				}
				if(!gameOver)
					gameState = 1;
				menu2 = true;
			}
			else if(menu->getSelectedItem() == 1)
			{
				menu->setInstructions(true);
			}
			else if(menu->getSelectedItem() == 2)
			{
				menu->setCredits(true);
			}
			else if(menu->getSelectedItem() == 3)
			{
				PostQuitMessage(0);
			}
			else if(menu->getSelectedItem() == 4)
			{
				menu->setCheats(true);
				switch(menu->getSelectedItem2())
				{
				case 0:
					fly = true;
					break;
				case 1:
					//jpo.incrementLivesBy(1000000);
					immortal=true;
					break;
				case 2:
					level = 3;
					break;
				}
				//fly=1;
				//lives=10000000
				//level=2;
			}
			break;
		case 1:
			if(debouncer && !input->isKeyDown(VK_RETURN))
			{
				debouncer = false;
			}
			if(!debouncer && input->isKeyDown(VK_SPACE))	// formerly SPACE
			{
				debouncer = true;
				gameState=2;
			}

			break;
		case 2:
			if(debouncer && !input->isKeyDown(VK_SPACE))
			{
				debouncer = false;
			}
			if(!debouncer && input->isKeyDown(VK_SPACE))	// formerly ESCAPE
			{
				debouncer = true;
				audio->stopCue(MENU);
				audio->playCue(LEVEL);
				gameState = 5;
			}
			break;
		case 3:
		case 4:
			break; 
		case 5:
			if(debouncer)
			{
				debouncer = input->isKeyDown(VK_SPACE);
				jumpedLastFrame = debouncer;
			}
			if(level==2)
			{
				frisbee.setVisible(true);
				frisbee.setVelocity(D3DXVECTOR2(1.5,frisbee.getVelocity().y));
				frisbee.update(frameTime);
				//laser.setVisible(true);
				laser.update(frameTime,moveScreenLeft, moveScreenRight);
			}
			else
			{
				frisbee.setVisible(false);
			}
			if(input->isKeyDown(JPO_JUMP_KEY) && jpo.getOnLand() && !fly)
			{
				// make JPo jump!
				if(!jumpedLastFrame)
						newVelocity = VECTOR2(newVelocity.x, -750);
				jumpedLastFrame = true;
				audio->playCue(BOING);
				//added 11/23
				//onLand=false;
				jpo.setOnLand(false);
			}
			else if(fly && input->isKeyDown(JPO_JUMP_KEY))
			{
				if(!jumpedLastFrame)
					newVelocity = VECTOR2(newVelocity.x, -750);
				jumpedLastFrame = true;
			}
			else
				jumpedLastFrame = false;
				
			if(input->isKeyDown(JPO_RIGHT_KEY))            // if move right
			{
				if(!keyDownLastFrame || lastDirection == left)
				{
					jpo.setFrames(JPO_WALKING_RIGHT_START, JPO_WALKING_RIGHT_END);
					jpo.setCurrentFrame(JPO_WALKING_RIGHT_START);
				}
	
				//jpo.setX(jpo.getX() + frameTime * JPO_SPEED);
				newVelocity = VECTOR2(RACCOON_SPEED, newVelocity.y);
	
				lastDirection = right;
				keyDownLastFrame = keyDownThisFrame;
				keyDownThisFrame = true;
			}
			else if(input->isKeyDown(JPO_LEFT_KEY))             // if move left
			{
				if(!keyDownLastFrame || lastDirection == right)
				{
					jpo.setCurrentFrame(JPO_WALKING_LEFT_START);
					jpo.setFrames(JPO_WALKING_LEFT_START, JPO_WALKING_LEFT_END);
				}

				//jpo.setX(jpo.getX() - frameTime * JPO_SPEED);
				newVelocity = VECTOR2(-RACCOON_SPEED, newVelocity.y);

				lastDirection = left;
				keyDownLastFrame = keyDownThisFrame;
				keyDownThisFrame = true;
			}
			else
			{
				if(keyDownLastFrame)
				{
					//PostQuitMessage(0);
					
					if(!jpo.getOnLand())
					{
						
						newVelocity = VECTOR2(0, newVelocity.y);
					}
					else
					{
						//paused=true;
						newVelocity = VECTOR2(0,0);
					}
					if(lastDirection == right)
					{
						jpo.setFrames(JPO_LOOKING_RIGHT_START, JPO_LOOKING_RIGHT_END);
						jpo.setCurrentFrame(JPO_LOOKING_RIGHT_START);
					}
					else // lastDirection == left
					{
						jpo.setFrames(JPO_LOOKING_LEFT_START, JPO_LOOKING_LEFT_END);
						jpo.setCurrentFrame(JPO_LOOKING_LEFT_START);
					}
				}

				keyDownLastFrame = keyDownThisFrame;
				keyDownThisFrame = false;
			}

			jpo.setVelocity(newVelocity);
			
			jpo.update(frameTime);

			//Platform Updates. Checks to see if they need to move.
			if(jpoX>=jpo.getX() && input->isKeyDown(JPO_RIGHT_KEY))
			{
				//if(platform[14].getX()>GAME_WIDTH-platform[14].getWidth()*platform[14].getScale())
				int maxX=background[level-1].getWidth()-GAME_WIDTH;
				if(background[level-1].getX()>-(maxX))
					moveScreenRight=true;
				else
					moveScreenRight=false;
			}
			else
			{
				moveScreenRight=false;
			}
			if(jpoX==jpo.getX() && input->isKeyDown(JPO_LEFT_KEY))
			{
				//if(platform[0].getX()<5)//arbitrarily cannot move if more than 5px away.
				if(background[level-1].getX()<0)
					moveScreenLeft=true;
				else
					moveScreenLeft=false;
				//jpo.setX(jpo.getX()-1);
			}
			else if(jpo.collidesWith(frisbee,collisionVector) && jpo.getX()>=30+jpo.getWidth()*jpo.getScale())
			{
				int maxX=background[level-1].getWidth()-GAME_WIDTH;
				//onLand=true;
				jpo.setOnLand(true);
				if(background[level-1].getX()>-(maxX))
					moveScreenRight=true;
				else
					moveScreenRight=false;
			}
			else{
				moveScreenLeft=false;
			}
			//checks if JPO is on a surface
			if(jpo.getY()>=GAME_HEIGHT-JPO_HEIGHT || jpo.getOnLand())//added onLand- if he's on land, he's safe.
			{
				jpo.setOnLand(true);
			}
			else
			{
				if(!jpo.collidesWith(frisbee,collisionVector))
					jpo.setOnLand(false);
				//onLand=false;
			}
			for(int i=0; i<15; i++)
			{
				platform[i].update(frameTime, moveScreenLeft, moveScreenRight);
			}
			background[level-1].update(frameTime, moveScreenLeft, moveScreenRight);

			cs.update(frameTime, moveScreenLeft, moveScreenRight);
			checkPoint.update(frameTime, moveScreenLeft, moveScreenRight);
			//
//			VECTOR2 collisionVector;
//			laser.setRight(jpo.getCenterX()>laser.getCenterX());		// sets velocity right if Raccoon's center is right of sniper.
			if(laser.getActive()&&laser.incrementCounter())
			{
				laser.setVisible(true);
				
				//laser.setX(LASER_X_INIT);
				laser.setX(laser.xInit);
				laser.setY(LASER_Y_INIT);
				tracking_x = jpo.getCenterX() - laser.getCenterX();
				tracking_y = jpo.getCenterY() - laser.getCenterY();
				absolute = sqrt(tracking_x*tracking_x + tracking_y*tracking_y);
				laser.setRadians(atan(tracking_y/tracking_x));
				laser.setVelocity(D3DXVECTOR2(LASER_SPEED*tracking_x/absolute,LASER_SPEED*tracking_y/absolute));
			}
			
			if(cs.collidesWithRaccoon(frameTime, jpo) || (laser.collidesWith(jpo,collisionVector)) && laser.getVisible())
			{
				//Sleep(1000);
				if(laser.collidesWith(jpo,collisionVector))
				{ 
					laser.setVisible(false);
				}
				if(jpo.getVisible())
				{
					audio->playCue(CAUGHT);
					if(!immortal)
					{
						jpo.incrementLivesBy(-1);
						if(jpo.getLives()<3)
							lives[jpo.getLives()].setVisible(false);
					}
//					Sleep(500);
				}
				jpo.setVisible(false);
				
				/*gameOver=true;*/
				//paused = true;
				if(jpo.getLives()>0)
				{
					jpo.setY(-10);
					jpo.setVisible(true);
					jpo.setVelocity(D3DXVECTOR2(0,0));
					//levelSet();
				}
				else
				{
					gameOver=true;
					writeHighScores();
					gameState=7;

				}
			}
			//check frisbee collision

			if(level==2)
			{
				sniper.update(frameTime, moveScreenLeft, moveScreenRight);
			}

			for(int i=0; i<3; i++)
			{
				cpsoup[i].update(frameTime, moveScreenLeft, moveScreenRight);
			}
//			laser.update(frameTime, moveScreenLeft, moveScreenRight);
			//if(checkPoint.collidesWith(frameTime, jpo))
			if(jpo.collidesWith(checkPoint,collisionVector))
			{
				audio->playCue(YAY);
				score+=level*50;
				oldScore=score;
				//jpo.setLives(jpo.getLives()+1);
				if(!immortal)
					jpo.incrementLivesBy(1);
				
				//paused=true;
				if(level<3)
					gameState=8;
					/*reset();*/
				else
				{
					gameOver=true;
					win=true;
					jpo.setX(-500);
					gameState=6;
					audio->playCue(YAY);
				}
			}

			for(int i=0; i<3; i++)
			{
				cheeseburger[i].update(frameTime, moveScreenLeft, moveScreenRight);
			}

			for(int i=0; i<3; i++)
			{
				pizza[i].update(frameTime, moveScreenLeft, moveScreenRight);
			}

			//if(level==3)
			//{
			//	int maxX=background[level-1].getWidth()-GAME_WIDTH;
			//	if(jpo.getX()>=checkPoint.getX())
			//	{
			//		paused=true;
			//		gameOver=true;
			//		

			//	}
			//}

			break;
		case 6:
			if(input->wasKeyPressed(VK_ESCAPE))
				{
					audio->stopCue(LEVEL);
					audio->playCue(MENU);
					gameState=0;
					gameOver=false;
					jpo.setLives(3);
					score=0;
					level=1;
					levelSet();
					setStillData();
					statusSet();
				}
			break;
		case 7:
			if(input->wasKeyPressed(VK_SPACE))		// formerly ESCAPE
				{
					audio->stopCue(LEVEL);
					audio->playCue(MENU);
					gameState=0;
					gameOver=false;
					jpo.setLives(3);
					score=0;
					level=1;
					// This was actually working fine without the calls to levelSet() and setStillData(), but "theoretically" they
					// should be needed here, for the same reason as above in case 6.
					levelSet();
					setStillData();
					statusSet();
				}
			break;
		case 8:
			if(level<3)
			{
 				between[level-1].setVisible(true);
				if(input->wasKeyPressed(VK_SPACE))
				{
				
					//resetLevel();
					gameState=5;
					between[level-1].setVisible(false);
					if(level<3)
						level++;
					reset();
					debouncer = true;
				}
			}
			break;

		/*	default:
				if(input->wasKeyPressed(VK_RETURN))
				{
					gameState=0;
				}
				break;*/
		}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void RaccoonRun::ai()
{
	cs.ai(&jpo);
}

//=============================================================================
// Handle collisions
//=============================================================================
void RaccoonRun::collisions()
{
	VECTOR2 collisionVector;

	if(jpo.getY()<GAME_HEIGHT-jpo.getHeight()*jpo.getScale())
		jpo.setOnLand(false);

	
	for(int i=0; i<15 && jpo.getOnLand()!=true; i++)
	{
		//if(jpo.collideBox(platform[i],collisionVector));s
		if(jpo.collidesWith(platform[i],collisionVector) && jpo.getVelocity().y>=0) 
			//checking velocity sets him on platform when he comes down.
		{
			jpo.setOnLand(true);
			jpo.setY((platform[i].getY()-platform[i].getHeight()*platform[i].getScale())
				-(jpo.getHeight()*jpo.getScale())+85);
			jpo.setVelocity(D3DXVECTOR2(0,0));
			break;
			//paused=true;
		}			
		
		/*if(jpo.collidesWith(frameTime,platform[i]) && jpo.getVelocity().y>=0)
		{
			onLand=true;
			jpo.setY(platform[i].getY()-(jpo.getHeight()*jpo.getScale()-10)-1);
			jpo.setVelocity(D3DXVECTOR2(0,0));
			break;
		}*/
	}
		if(frisbee.getVisible())
	{
		
		if(jpo.collidesWith(frisbee, collisionVector))
		{
			//paused=true;
			jpo.setX(frisbee.getX());
			jpo.setY(frisbee.getY()-jpo.getHeight()*jpo.getScale()+20);//some magic number.
			//but it works.
			//paused=true;
			if(jpo.getX()+jpo.getWidth()*jpo.getScale()>=GAME_WIDTH)
				moveScreenRight=true;
			frisbee.setVelocity(D3DXVECTOR2(frisbee.getVelocity().x,1));
			//onLand=true;
			jpo.setOnLand(true);
		}
		else
			frisbee.setVelocity(D3DXVECTOR2(frisbee.getVelocity().x,0));
	}
	for(int i=0; i<3; ++i)
	{
		if(jpo.collidesWith(cpsoup[i],collisionVector))
		{
			cpsoup[i].setActive(false);
			cpsoup[i].setVisible(false);
			//paused=true;
			score-=5;
		}
		/*if(cpsoup[i].collidesWith(jpo, collisionVector) && cpsoup[i].getActive())
		{
     		cpsoup[i].setActive(false);
			cpsoup[i].setVisible(false);
			score-=5;
		}*/
	}
	for(int i=0; i<3; ++i)
	{
		if(cheeseburger[i].collidesWith(jpo, collisionVector) && cheeseburger[i].getActive())
		{
			if(cheeseburger[i].getVisible())
				score+=10;
			cheeseburger[i].setActive(false);
			cheeseburger[i].setVisible(false);
		}
			//paused=true;
		//if(jpo.collidesWith(frameTime,cheeseburger[i])&&cheeseburger[i].getActive())
		//{
  //   		cheeseburger[i].setActive(false);
		//	cheeseburger[i].setVisible(false);
		//	//paused = true;
		//}
	}
	for(int i=0; i<3; ++i)
	{
		if(pizza[i].collidesWith(jpo, collisionVector) && pizza[i].getActive())
		{
			if(pizza[i].getVisible())
				score+=5;
			pizza[i].setActive(false);
			pizza[i].setVisible(false);
		}
		//if(jpo.collidesWith(frameTime,pizza[i])&&pizza[i].getActive())
		//{
  //   		pizza[i].setActive(false);
		//	pizza[i].setVisible(false);
		//	//paused = true;
		//}
	}

}

//=============================================================================
// Render game items
//=============================================================================
void RaccoonRun::render()
{
	std::string message;
	std::stringstream stuff;
	graphics->spriteBegin();                // begin drawing sprites
	switch(gameState)
	{
	case 0:
		menuBackground.draw();
		if(menu->getCredits())
			menu->displayCredits();
		else if(menu->getInstructions())
			menu->displayInstructions();
		else if(menu->getCheats())
			menu->displayCheats();
		else
			menu->displayMenu();
		break;
	case 1:
		splash.draw();
		break;
	case 2:
		menuBackground2.draw();
		break;
	case 5:
		background[level-1].draw();
		blackBar.draw();
		if(!gameOver)
		{
			for(int i=0; platform[i].getVisible(); i++)//this keeps track of which platforms are visible.
			{
				//throw(GameError(gameErrorNS::FATAL_ERROR, "Made it to "));
				platform[i].draw();
			}
			for(int i=0; i<3; i++)
			{
				cpsoup[i].draw();
			}
			for(int i=0; i<3; i++)
			{
				cheeseburger[i].draw();
			}
			for(int i=0; i<3; i++)
			{
				pizza[i].draw();
			}
			checkPoint.draw();
			frisbee.draw();
			jpo.draw();
			cs.draw();
			laser.draw();
			if(level == 2)
				sniper.draw();
		}
		else
		{
			debugFont->setFontColor(graphicsNS::BLACK);
			debugFont->print("Game OVER.",0,0);
			
			if(input->isKeyDown(VK_ESCAPE))
				gameState=0;
		}
		
		for(int i=0; lives[i].getVisible(); i++)
		{
			lives[i].draw();
		}
		/*std::string message;,
		std::stringstream stuff;*/
		message="Score: ";
		stuff<<score;
		stuff>>message;
		debugFont->print("score: "+message,600,0);
		break;
	case 6:
		winScreen.draw();
		//you won. Increased score.
		//score+=150;
		debugFont->setFontColor(graphicsNS::BLACK);

		message="Score: ";
		stuff<<score;
		stuff>>message;
		debugFont->print("score: "+message,350,380);
		break;
	case 7:
		lose.draw();
		break;
	case 8: //between state.
		if(level<3)
			between[level-1].draw();
		//if(level==1)
		//{
		//	between[0].setVisible(true);
		//	between[0].draw();
		//}
		//else if(level==2)
		//{
		//	/*between[1].setVisible(true);
		//	between[1].draw();*/
		//	l2End.setVisible(true);
		//	l2End.draw();
		//}
		break;
		}

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void RaccoonRun::releaseAll()
{
	debugFont->onLostDevice();
	
	jpoTexture.onLostDevice();
	platformTexture.onLostDevice();
	cpsoupTexture.onLostDevice();
	backgroundTexture[0].onLostDevice();
	backgroundTexture[1].onLostDevice();
	backgroundTexture[2].onLostDevice();
	livesTexture.onLostDevice();
	blackTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void RaccoonRun::resetAll()
{
	debugFont->onLostDevice();

	jpoTexture.onResetDevice();
	platformTexture.onResetDevice();
	cpsoupTexture.onResetDevice();
	backgroundTexture[0].onResetDevice();
	backgroundTexture[1].onResetDevice();
	backgroundTexture[2].onResetDevice();
	livesTexture.onResetDevice();
	blackTexture.onResetDevice();

    Game::resetAll();
    return;
}
void RaccoonRun::chkPtReset(int cpIndex, int pIndex, int cIndex)
{
	/*jpo.setX();*/
	jpo.setX(raccoonStart[level][pastCheckpoint].X);
	jpo.setY(raccoonStart[level][pastCheckpoint].Y);
}
void RaccoonRun::levelSet()
{
	switch (level)
	{
	case 1:
		//audio->stopCue(LEVEL);
		//audio->playCue(LEVEL);
		
		//jpo.setX(30); // old start coordinates - save for future if we want to put him back in the tree
		//jpo.setY(175-RACCOON_HEIGHT);
		
		//no cumulative scoring for level 1.
		score=0;
		oldScore=0;

		jpo.setX(400);
		jpo.setY(GAME_HEIGHT-(10+RACCOON_HEIGHT));
		jpo.setFrames(RACCOON_LOOKING_RIGHT_START, RACCOON_LOOKING_RIGHT_END);   // animation frames
		jpo.setVisible(true);

		cs.setX(25);
		cs.setY(GAME_HEIGHT-(10+JPO_HEIGHT));
		cs.setVelocity(D3DXVECTOR2(JPO_SPEED,0));
		//make him bigger...
		cs.setScale(1.25);

		//laser.setX(-100);
		//laser.setY(-100);
		laser.setActive(false);
		laser.setVisible(false);

		setStillData();

		break;
	case 2:
		score=oldScore;
		//yay level 2!
		//score+=50;

		frisbee.setVisible(true);
		frisbee.setX(10);
		frisbee.setY(130);

		//jpo.setX(17);
		//jpo.setY(163-RACCOON_HEIGHT);
		jpo.setX(frisbee.getX());
		jpo.setY(frisbee.getY()-jpo.getHeight()*jpo.getScale()+20);
		jpo.setFrames(RACCOON_LOOKING_RIGHT_START, RACCOON_LOOKING_RIGHT_END);   // animation frames
		jpo.setVisible(true);

		cs.setX(25);
		cs.setY(GAME_HEIGHT-(10+JPO_HEIGHT));
		cs.setVelocity(D3DXVECTOR2(JPO_SPEED,0));

		laser.setActive(true);
		laser.setVisible(true);

		setStillData();

		break;
	case 3:
		frisbee.setVisible(false);
		//yay level 3!
		score=oldScore;
		//score+=100;

		jpo.setX(17);
		jpo.setY(67-RACCOON_HEIGHT);
		jpo.setFrames(RACCOON_LOOKING_RIGHT_START, RACCOON_LOOKING_RIGHT_END);   // animation frames
		jpo.setVisible(true);

		cs.setX(25);
		cs.setY(GAME_HEIGHT-(10+JPO_HEIGHT));
		cs.setVelocity(D3DXVECTOR2(90.0f,0));

		//laser.setX(-100);
		//laser.setY(-100);
		laser.setActive(false);
		laser.setVisible(false);

		setStillData();

		break;
	}
}
void RaccoonRun::setStillData()
{
	setBgData();
	setPlatformData(level);
	setSoupData();
	setCheeseburgerData();
	setPizzaData();
	if(level==2)
		//sniper.set(700,100);
		sniper.set(LASER_X_INIT,LASER_Y_INIT);

	//checkpoint stuff
	switch(level)
	{
	case 1:
		//checkPoint.set(1930,76);
		checkPoint.set(-2300,175);
		break;
	case 2:
		checkPoint.set(1470,190);
		break;
	case 3:
		checkPoint.set(1821,240);
	}
	
}
void RaccoonRun::setSoupData()
{
	for(int i=0; i<3; i++)
	{
		cpsoup[i].setScale(.5);
		cpsoup[i].setActive(true);
		cpsoup[i].setVisible(true);
	}
	switch(level)
	{
	case 1:
		cpsoup[0].set(377,410);
		cpsoup[1].set(785,400);
		cpsoup[2].set(1064,175);
		break;
	case 2:
		cpsoup[0].set(249,423);
		cpsoup[1].set(500,310);
		cpsoup[2].set(963,400);
		break;
	case 3:
		cpsoup[0].set(249,423);
		cpsoup[1].set(500,310);
		cpsoup[2].set(963,400);
		break;
	}
}

void RaccoonRun::setCheeseburgerData()
{
	for(int i=0; i<3; i++)
	{
		cheeseburger[i].setScale(.5);
		cheeseburger[i].setActive(true);
		cheeseburger[i].setVisible(true);
	}
	switch(level)
	{
	case 1:
		cheeseburger[0].set(177,430);
		cheeseburger[1].set(585,380);
		cheeseburger[2].set(850,130);
		break;
	case 2:
		cheeseburger[0].set(49,423);
		cheeseburger[1].set(300,310);
		cheeseburger[2].set(763,380);
		break;
	case 3:
		cheeseburger[0].set(65,423);
		cheeseburger[1].set(300,310);
		cheeseburger[2].set(763,400);
		break;
	}
}

void RaccoonRun::setPizzaData()
{
	for(int i=0; i<3; i++)
	{
		pizza[i].setScale(.5);
		pizza[i].setActive(true);
		pizza[i].setVisible(true);
	}
	switch(level)
	{
	case 1:
		pizza[0].set(-277,400);
		pizza[1].set(685,400);
		pizza[2].set(-2100,110);
		break;
	case 2:
		pizza[0].set(149,423);
		pizza[1].set(400,310);
		pizza[2].set(863,400);
		break;
	case 3:
		pizza[0].set(149,423);
		pizza[1].set(400,310);
		pizza[2].set(863,400);
		break;
	}
}


void RaccoonRun::setBgData()
{
	background[0].set(LVL1_BKGRND_START_PRE,0);
	//background[0].getWidth();
	for(int i=1; i<3; i++)
	{
		background[i].set(-5,0);
	}
}

void RaccoonRun::reset()
{/*
	if(level<3)
		level++;*/
	levelSet();
	setStillData();
	statusSet();
}
void RaccoonRun::statusSet()
{
	blackBar.setX(0);
	blackBar.setY(-20);
	
	int xOffset=65;
	for(int i=0; i<5; i++)
	{
		lives[i].setX(5+i*xOffset);
		lives[i].setY(0);
		lives[i].setVisible(false);
		lives[i].setScale(.2);
	}
	for(int i=0; i<jpo.getLives(); i++)
	{
		lives[i].setVisible(true);
	}
}

void RaccoonRun::writeHighScores()
{
	//fin.open(SCORES);
	fout.open(SCORES);
	int j=0;
	for(int i=0; i<MAX_SCORES; i++)
	{
		if(highScores[j]>score)
		{
			fout<<highScores[j]<<endl;
			j++;
		}
		else
		{
			fout<<score<<endl;
			for(i; i<10; i++)
			{
				fout<<highScores[j]<<endl;
				j++;
			}
		}
	}
	fout.close();
	//PostQuitMessage(0);
}
