#include DarkGDK.h
#include variables.h
#include mapHandling.h
#include Phy and movement.h 
#include globstruct.h USED FOR MESSAGE box 
#include conio.h  pt pauza
#include dinput.h			//DIK_P = tasta P

phyAndMovement phy;

void MarioPhysics()
{
	phy.controlCharacter();
	phy.gravity();
	phy.StaticPlayerCollisions();
	phy.AiPlayerCollisions();
	phy.playerJump();
}

void EnemyPhysics()
{
	enPhy.controlAI();
	enPhy.gravity();
	enPhy.goombaAnim();
}


void MarioEvents()
{
	myEvents.playerAnimations();
	myEvents.tickTock();
	myEvents.handleDeath();
	myEvents.handleDamage();
	myEvents.endLevel();
}

void EnemyAnim()
{
	enemy.AwakeEnemies();
	enemy.piranhaAI();
}

void DarkGDK()
{
	dbSyncOn();
	dbSyncRate(60);
	dbSetDisplayMode(800, 600, 32);
	//dbMaximizeWindow();
	dbBackdropOn();
	dbBackdropColor(dbRGB(0, 255, 0));
	
	
	dbLoadImage(menuButtonsmenu.png, 4444);
	dbLoadImage(menuButtonsstartgame.png, 1000);
	dbLoadImage(menuButtonsleveltype.png, 2000);
	dbLoadImage(menuButtonsquitgame.png, 3000);

	dbLoadImage(menuButtonsstartgamepink.png, 1100);
	dbLoadImage(menuButtonsleveltypepink.png, 2200);
	dbLoadImage(menuButtonsquitgamepink.png, 3300);

	dbLoadImage(menuButtonslevel1pink.png, 2211);
	dbLoadImage(menuButtonslevel2pink.png, 2222);
	dbLoadImage(menuButtonslevel1.png, 2201);
	dbLoadImage(menuButtonslevel2.png, 2202);

	dbLoadImage(menuButtonsMousexxx.png, 9000);

	dbSprite(4444,0,0,4444);							//MENU

	dbSprite(1000, 250, 150, 1000);						//START
	dbSprite(2000, 250, 270, 2000);						//CONTINUE
	dbSprite(3000, 250, 390, 3000);						//QUIT	

	dbSprite(1100, 250, 150, 1100);						//START pink
	dbSprite(2200, 250, 270, 2200);						//CONTINUE pink
	dbSprite(3300, 250, 390, 3300);						//QUIT	pink

	dbSprite(2201, 600, 266 ,2201);						//LEVEL 1
	dbSprite(2211, 600, 266 ,2211);						//LEVEL 1 PINK
	dbSprite(2202, 600, 327, 2202);						//LEVEL 2
	dbSprite(2222, 600, 327 ,2222);						//LEVEL 2 PINK

	
	dbHideSprite(2201);
	dbHideSprite(2211);
	dbHideSprite(2202);
	dbHideSprite(2222);

	

	dbHideSprite(1100);
	dbHideSprite(2200);
	dbHideSprite(3300);
	dbHideMouse();



	int showLevels = 0;
	bool isPaused = false;			//variabile pt pauza
	int timer = 0;
	int startplay = 0;
			while (LoopGDK())
			{	dbSync();

				if(startplay == 0)
				{		dbSprite(9000, dbMouseX(),dbMouseY(), 9000);		//MOUSE
						dbSync();
		

						if(dbSpriteCollision(9000,3000) == 1)
						{
							dbShowSprite(3300);
							if (dbMouseClick() == 1)														QUIT
							{return;}
						}
						else dbHideSprite(3300);
							
	


						if(dbSpriteCollision(9000,2000) == 1)
						{
							
							dbShowSprite(2200);	//pink
							if(dbMouseClick() == 1)
							{
								if(showLevels == 0)
								{
									showLevels = 1;
								}
								else
								{
									showLevels = 0;
								}
								dbSync();
							}
							

							 
						}else dbHideSprite(2200);	//no pink


						if(showLevels == 1)
						{
							dbSync();
							dbShowSprite(2201);
							dbShowSprite(2202);

							if(dbSpriteCollision(9000,2201) == 1)
							{
								dbShowSprite(2211);
								if(dbMouseClick()==1)
									level = 1;
							}
							else dbHideSprite(2211);

							
							if(dbSpriteCollision(9000,2202) == 1)
							{
								dbShowSprite(2222);
								if(dbMouseClick()==1)
									level = 2;
							}
							else dbHideSprite(2222);
						}

						else if(showLevels == 0)
						{
							dbSync();
							dbHideSprite(2201);
							dbHideSprite(2202);

						}




					
					
						if(dbSpriteCollision(9000,1000) == 1)
						{
							dbShowSprite(1100);
							 if(dbMouseClick() == 1)																 START GAME
							{
								
								
								
								dbHideSprite(9000); 
								dbDeleteSprite(9000);
								dbHideSprite(1000); 
								dbDeleteSprite(1000);
								dbHideSprite(2000); 
								dbDeleteSprite(2000);
								dbHideSprite(3000); 
								dbDeleteSprite(3000);
								dbDeleteSprite(2201);
								dbDeleteSprite(2202);
								dbDeleteSprite(2211);
								dbDeleteSprite(2222);
								dbDeleteSprite(4444);
								dbHideSprite(1100);


								startplay = 1;

								load.loadImages();
								load.loadCurrentLevel(level);
								load.loadSounds();
								myEvents.resetEverything();		// in case of gameover  death

							}
						}
						else dbHideSprite(1100);

				}
						
				
						PAUZA
						dbSync();
						if(startplay)
						{

							dbSync();
								if (dbKeyState(DIK_P) == 1 && (dbTimer()  timer + 500) )		//daca tasta P  
								{
									timer = dbTimer();
									if ( !isPaused )
										isPaused = true;
									else
										isPaused = false;
								}

								if (isPaused) 
								{
									 Pause Code
									dbText(dbScreenWidth()  2 - 75, dbScreenHeight()  2, Game Paused);							
									dbText(dbScreenWidth()  2 - 125, dbScreenHeight()  2 + 12, Press P Key to contine.);

								} 
								else 
								{
									mapping.playSounds();main theme + lowerhigher main theme
									mapping.displayLevel();
									mHandling.LevelAnimations();
									EnemyAnim();
									mapping.displayInformation();			//score,level,lifes,etc
									MarioPhysics();
									MarioEvents();
									EnemyPhysics();
									dbSync();
								}
						}
					

		}
		
		return;

	

}
