#pragma once

#include "loader.h"
#include "mapHandlingDetails.h"
loader load;
mapHandlingDetails mHandling;

class marioEvents
{
public:
	void marioEvents::resetEverything()
	{
		checkPlayerX = playerX;
		checkPlayerY = playerY;
		Ttime = 400;
		lifes = 3;
		score = 0;
		IsMarioAlive = true;
	}
	//cronometreaza timpul in care ar trebui sa termine jocul
	void marioEvents::tickTock()
	{
		if (levelOver == 0)
		{
			if (dbTimer() - gameTimer > 1000)
			{
				gameTimer = dbTimer();
				if (Ttime > 0) Ttime--;
				else killMario();

				if (Ttime == 200)            //daca se scurge timpul, killMario. daca a trecut jumate din timp, alert
				{
					dbPlaySound(StimeWarning);
				}
			}
		}
	}

	void marioEvents::endLevel()
	{
		//daca mario a atins steagul, melodia de pe fundal nu se mai aude
		if (levelOver != 0)
		{
			if (dbSoundPlaying(SmainTheme)) dbStopSound(SmainTheme);//stop main theme
		}
		if (levelOver == 1)
		{
			//daca a ajuns,dar e in aer, intai asteapta pana atinge pamantul,apoi sunetul de endgame
			if (touchingGround)
			{
				levelOver = 2;
			}
		}
		if (levelOver == 2)
		{
			dbPlaySound(SlevelClear);
			levelOver = 3;
		}
		if (levelOver == 3)
		{
			//merge automat spre dreapta
			walkingRight = true;
			playerX = playerX + speedx / 2;
			EndGame = true;
			dbSetTextSize(30);
		}

		//s-a sfarsit jocul
		if (EndGame)
		{
			dbText(screenCenterX / 2, screenCenterY, "Game demo is over,\n Press any key to exit");
			if (dbScanCode() > 0)
			{
				exit(0);
			}
		}
	}


	void marioEvents::coinPickedUp()
	{
		coins++;
		dbPlaySound(ScoinPickup);
		score += 200;
		if (coins >= 10)
		{
			coins = 0;
			lifes++;
			dbPlaySound(SnewLife);
		}
	}


	void marioEvents::pickupItems(int arrX, int arrY, int typeOfCollision)
	{
		//culege banutii
		if (map[arrX][arrY] == C)
		{
			//banutul se transforma intr-o patratica de aer
			map[arrX][arrY] = a;
			coinPickedUp();
		}
		//planta care il face pe mario sa se transformare in printesa (ultimul frame)
		else if (map[arrX][arrY] == f + 11)
		{
			if (currentMario == normalMario)currentMario = Princess;
			score += 1000;
			// daca mario e deja printesa, se adauga 1000 puncte
			dbPlaySound(SFlowerPickup);
			mHandling.startAnimation(score1000_1, IMAGE, arrX, arrY - 1, 10, a, 80);

			//devine patratica de aer
			map[arrX][arrY] = a;
		}

		//caramida
		else if (map[arrX][arrY] == b)
		{
			if (typeOfCollision == bottom)
			{
				//devine praf, apoi dispare
				dbPlaySound(Sbrick);
				mHandling.startAnimation(dust_1, IMAGE, arrX, arrY, 8, a, 80);
			}
		}
		//1UP box -> cub
		else if (map[arrX][arrY] == L)
		{
			if (typeOfCollision == bottom)
			{
				dbPlaySound(SFlowerAppear);//melodia specifica atunci cand apare coronita
				mHandling.startAnimation(_1up_1, IMAGE, arrX, arrY - 1, 16, gM, 100);
				//cub
				map[arrX][arrY] = e;
			}
		}
		//loveste o caramida goala
		else if (map[arrX][arrY] == e || map[arrX][arrY] == k)
		{
			if (typeOfCollision == bottom)
			{
				dbPlaySound(Sbump);
			}
		}
		//loveste question Coin
		else if (map[arrX][arrY] == qC)
		{
			if (typeOfCollision == bottom)
			{
				mHandling.startAnimation(C, IMAGE, arrX, arrY - 1, 6, a, 120);
				// cutiile cu ? -> caramida
				map[arrX][arrY] = e;
				coinPickedUp();
			}
		}

		//loveste question Flower unde de fapt se afla coronita
		else if (map[arrX][arrY] == qF)
		{
			if (typeOfCollision == bottom)
			{
				//se transforma intr-o caramida
				map[arrX][arrY] = e;

				dbPlaySound(SFlowerAppear);
				mHandling.startAnimation(f, IMAGE, arrX, arrY - 1, 11, f + 11, 100);
			}
		}

		else if (map[arrX][arrY] == d)
		{
			killMario();
		}
		//steagul checkpoint
		else if (map[arrX][arrY] == fB || map[arrX][arrY] == fT)
		{
			//daca nu s-a ajuns la checkpoint, adauga-l in joc
			if (CheckPointReached == false)
			{
				CheckPointReached = true;
				checkPointX = mapX;
				checkPointY = mapY;
				checkPlayerX = playerX;
				checkPlayerY = playerY;

				score += 500;
				dbPlaySound(ScheckPoint);

				//afiseaza textul checkpoint
				mHandling.startAnimation(check_1, SPRITE, dbSpriteX(mario), dbSpriteY(mario) - 100/*o patratica si jum*/, 8, a, 150);
			}
		}
		//Green mushroom +1 viata
		else if (map[arrX][arrY] == gM)
		{
			map[arrX][arrY] = a;
			lifes++;
			dbPlaySound(Spowerup);
			//animatia "1 up"
			mHandling.startAnimation(_1upText_1, IMAGE, arrX, arrY - 1, 6, a, 100);
		}

		//atinge steagul de sfarsit
		//steagul e format din mai multe patratele
		else if (map[arrX][arrY] == fl || map[arrX][arrY] == P1 || map[arrX][arrY] == P2 || map[arrX][arrY] == P3 || map[arrX][arrY] == P4 || map[arrX][arrY] == P5 || map[arrX][arrY] == P5l || map[arrX][arrY] == P6)
		{

			if (levelOver == 0)
			{
				stopMovement = true;
				dbPlaySound(SendLevel);
				levelOver = 1;
			}

		}

	}


	//animatia corecta in functie de butoanele apasate
	void marioEvents::playerAnimations()
	{
		//in cazul in care Mario nu este adaugat
		if (dbSpriteExist(mario))
		{
			if (marioSpawned) //animatiile apar doar daca apare si Mario
			{
				if (IsMarioAlive == true)
				{
					if (misc.noEssentialKeyBeingPressed() && dbTimer() - walkingTimer > 120 && jumping == false && falling == false) //daca nu apasa nimic, mario nu face nimic. frameul STILL
					{
						walkingTimer = dbTimer();
						if (currentMario == normalMario)
						{
							dbSprite(mario, playerX - mapX, playerY - mapY, mario); //pt ca harta este updatata in functie de player,pt care playerX si playerY se schimba mereu
						}
						else if (currentMario == Princess)
						{
							dbSprite(mario, playerX - mapX, playerY - mapY, PrincessStill);
						}
					}
					else if (jumping == true || falling == true)
					{
						if (currentMario == normalMario)
						{
							dbSprite(mario, playerX - mapX, playerY - mapY, marioJump);
						}
						else if (currentMario == Princess)
						{
							dbSprite(mario, playerX - mapX, playerY - mapY, PrincessJump);
						}
					}
					if (walkingRight == true)
					{
						if (dbSpriteMirrored(mario))
						{
							dbMirrorSprite(mario); //este inversat fata de cum e original? ( original = fata la dreapta ) daca da, il readuc la dreapta
						}
						if (dbTimer() - walkingTimer > 100)
						{
							walkingTimer = dbTimer();
							if (currentMario == normalMario && jumping == false && falling == false)
							{
								//animatia in care merge
								if (dbSpriteImage(mario) == mario)
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, marioWalk);
								}
								else
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, mario);
								}
							}
							else if (currentMario == Princess && jumping == false && falling == false)
							{
								//animatia in care merge
								if (dbSpriteImage(mario) == PrincessStill)
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, PrincessWalk);
								}
								else
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, PrincessStill);
								}
							}
						}
					}
					if (walkingLeft == true)
					{
						if (dbSpriteMirrored(mario) == 0)
						{
							dbMirrorSprite(mario);
						}
						if (dbTimer() - walkingTimer > 100)
						{
							walkingTimer = dbTimer();
							if (currentMario == normalMario && jumping == false && falling == false)
							{
								if (dbSpriteImage(mario) == mario)
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, marioWalk);
								}
								else
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, mario);
								}
							}
							else if (currentMario == Princess && jumping == false && falling == false)
							{
								if (dbSpriteImage(mario) == PrincessStill)
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, PrincessWalk);
								}
								else
								{
									dbSprite(mario, playerX - mapX, playerY - mapY, PrincessStill);
								}
							}
						}
					}
				}
			}
		}
	}

	void marioEvents::createPlayer(int initial_X, int initial_Y)
	{
		playerX = initial_X;                             //playerX = screenCenterX = 380
		playerY = initial_Y;                             //playerY = screenCenterY = 280
		currentMario = normalMario;
		dbSprite(mario, playerX, playerY, mario);
		dbSetSpritePriority(mario, 1);				//mario este MEREU in primplan. si cand este lovit/damageflashing, sau cazut=mort, sprite-ul goomba-ului care l-a omorat nu va fi creat peste animatia de DeadMario(zburat in sus)
	}


	void marioEvents::takeDamage()
	{
		if (currentMario == Princess)
		{
			takingDamage = true;
			currentMario = normalMario;
			dbPlaySound(SPipeAndDamage);
		}
		else killMario();

	}


	void marioEvents::respawnMario()
	{

		misc.cleanupEnemies();
		load.loadCurrentLevel(level);
		currentMario = normalMario; //daca e respawn apare ca Mario daca era Printesa
		dying = false;
		IsMarioAlive = true;
		damageFlashes = 0;
		playerX = checkPlayerX;
		playerY = checkPlayerY;
		mapX = checkPointX;
		mapY = 0;
		Ttime = 400; //reset time

	}

	void marioEvents::handleDamage()
	{
		if (dying == false && IsMarioAlive == true && takingDamage == true)
		{
			//flash cand ia damage
			if (dbTimer() - flashTimer > 40)
			{
				damageFlashes++;
				flashTimer = dbTimer();

				if (deathFlash == 1)
				{
					dbHideSprite(mario);
					deathFlash = 0;
				}
				else
				{
					dbShowSprite(mario);
					deathFlash = 1;
				}
				if (damageFlashes == 25)
				{
					damageFlashes = 0;
					takingDamage = false, dbShowSprite(mario);
				}
			}
		}
	}

	void marioEvents::handleDeath()
	{
		if (dying == true && IsMarioAlive == false)
		{
			//flash cand moare
			if (dbTimer() - flashTimer > 40)
			{
				playerY = playerY - 3.0;          // se ridica / scade apa axa  oY
				damageFlashes++;
				flashTimer = dbTimer();

				if (deathFlash == 1)					// si apoi se "invarte" / clipeste ca mai sus.
				{
					dbHideSprite(mario);
					deathFlash = 0;
				}
				else
				{
					dbShowSprite(mario);
					deathFlash = 1;
				}
				if (damageFlashes == 50)
				{
					//reapare dupa damage
					dbShowSprite(mario);
					if (lifes > 0)
					{
						respawnMario();
					}
					//ramane fara vieti
					else
					{
						dying = false;
						EndGame = true;
					}


				}
			}
			//update la pozitia sprite-ului mario. pt a tot scadea playerY-ul
			//cu 3,si sa ramana asa. altfel redeseneaza sprite-ul pe acelasi loc pana damageFlashes = 50
			dbSprite(mario, playerX - mapX, playerY - mapY, mario);
		}
	}

	//pt cazurile in care cade in gaura sau TimeUp
	void marioEvents::killMario()
	{
		if (IsMarioAlive == true && dying == false && takingDamage == false)
		{
			dying = true;
			lifes--;
			IsMarioAlive = false;
			dbPlaySound(Sdeath);
			deathFlash = dbRnd(1); //returneaza un nr random intre 0 si 1
			if (dbSoundPlaying(SmainTheme)) dbStopSound(SmainTheme);
		}
	}
};
