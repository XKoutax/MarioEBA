//Handles physics movement and certain events functions
#pragma once

#include "Enemies.h" //includes  a number of events such as death taking damage and so on
#include "enemyPhy and Movement.h"
#include "mapHandlingDetails.h"
#include <conio.h>


Enemies enemies;
EnemyPhyAndMovement enPhy; //			//			// for the enemy
mapHandling mapping;

class phyAndMovement
{
public:

	
	void phyAndMovement::playerJump()
	{
		if (dbSpaceKey() && spaceKeyPressed == false)
		{
			if (!jumping && touchingGround)
			{
				dbPlaySound(Sjump);
				spaceKeyPressed = true;
				touchingGround = false;
				jumpStartTimer = dbTimer(); 
				jumping = true;
			}
		}
		if (jumping)
		{
			if (dbTimer() - jumpStartTimer < 1050)
			{
				playerY = playerY - speedy;
			}
			if (dbTimer() - jumpStartTimer > 720)
			{
				jumping = false;
			}
		}
		if (dbSpaceKey() == 0)spaceKeyPressed = false;

	}

	void phyAndMovement::gravity()							//CADEREA
	{
		if (IaMarioAlive == true /* && stopMovement == false*/)
		{
			if (!touchingGround)					//nu atince pamantul. si nu sare. deci e in cadere
			{
				if (jumping == false)
				{
					if (dbTimer() - touchingGroundTimer > 150)
					{
						falling = true;
					}
					playerY = playerY + speedy;
				}
			}
			if (touchingGround)
			{
				if (jumping)jumping = false;
				if (falling)falling = false;
			}
		}
	}

	int phyAndMovement::MarioWalkerCollision()
	{
		//verific daca mario collided cu un Goomba
		for (int i = 0; i < maxWalkers; i++)
		{
			if (dbSpriteExist(walkers[i].id))
			{
				if (walkers[i].isAlive)
				{
					if (dbSpriteCollision(mario, walkers[i].id))
					{
						return i; //Goomba-ul de care s-a lovit
					}
				}
			}
		}
		//return -1 daca goomba-ul nu exista inca sau daca no collision
		return -1;
	}



	void phyAndMovement::AiPlayerCollisions()					//Mario collide with Goomba de sus? --> Gooma damage. Mario collide with Goomba stanga/dreapta? --> Mario damage.
	{
		int didMarioCollide = MarioWalkerCollision();

		if (didMarioCollide != -1 && IsMarioAlive == true)// pt a evita cazul : Goomba kill Mario si apoi Mario(dead) kill Goomba 
		{
			// Daca mario e deasupra Goomba-ului la o anumita distanta, kill Goomba. Altfel, damage Mario.

			//enemies height minus Mario height  >=  60
			//atunci mario este chiar deasupra. trebuia sa verific daca exact deasupra,sau deasupra dar prea la stanga/dreapta
			if (dbSpriteY(walkers[didMarioCollide].id) - dbSpriteY(mario) >= 55 && !walkers[didMarioCollide].isDying) // pt a evita cazul : Mario kill Goomba si apoi Goomba(dead) kill Mario
			{

				//deasupra dar prea la marginea din stanga/dreapta, ==> mario dmg
				if (dbSpriteX(mario) > dbSpriteX(walkers[didMarioCollide].id) + 55 || dbSpriteX(mario) < dbSpriteX(walkers[didMarioCollide].id) - 55)
				{
					myEvents.takeDamage();
				}
				//altfel, mario e asezat bine. Mario kills Goomba.
				else
				{
					// if(walkers[didMarioCollide].typeOf == GOOMBA)
					//{
					playerY = playerY - (speedy * 5); //dupa ce omoara un Goomba, sare putin putin putin in sus. un mini-bump
					dbPlaySound(Sstomp);

					// omoara Goomba-ul cu care a collide-uit.
					enPhy.KillMe(didMarioCollide);
					//animatia de scor deasupra Goomba-ului.
					mHandling.startAnimation(score100_1, SPRITE, dbSpriteX(walkers[didMarioCollide].id), dbSpriteY(walkers[didMarioCollide].id) - 65, 9, a, 80); //-65 pt ca vream cu o patratica deasupra Goomba-ului mort.
																																								 // }
				}
			}
			//mario a atins altceva decat partea de sus/top, deci Mario takes dmg.
			else
			{
				myEvents.takeDamage();
			}
		}
	}


	void phyAndMovement::StaticPlayerCollisions()
	{


		
		int lefttilenum = int(playerX / tilesizex);
		int righttilenum = int((playerX + (tilesizex - 1)) / tilesizex);

		
		int toptilenum = int(playerY / tilesizey);
		int bottomtilenum = int((playerY + (tilesizey - 1)) / (tilesizey));

	
		int oldlefttilenum = int(oldx1 / tilesizex);
		int oldrighttilenum = int((oldx1 + (tilesizex - 1)) / tilesizex);
		//gets which tiles the old top and bottom co-ordinates of the player are on
		int oldtoptilenum = int(oldy1 / tilesizey);
		int oldbottomtilenum = int((oldy1 + (tilesizey - 1)) / (tilesizey));


		

		bool collidedWithSomething = false;//was there a collision?
		int typeOfCollision = 0;

		
		int collidedWithX = 0; 
		int collidedWithY = 0; 

							   // collision cu partea din STANGA SUS
		if (map[lefttilenum][oldtoptilenum] >= 10)
		{
			if (map[lefttilenum][oldtoptilenum] < 100)
			{
				playerX = oldx1;
				mapX = oldmapX;
			}
			collidedWithSomething = true;
			collidedWithX = lefttilenum;
			collidedWithY = oldtoptilenum;
		}

		if (map[oldlefttilenum][toptilenum] >= 10)
		{
			if (map[oldlefttilenum][toptilenum] < 100)
			{
				playerY = oldy1;
				//  mapY = oldmapY;
				if (jumping == true)jumping = false; // if player was jumping he hit his head on something meaning the jump is over
													 //colliding below something 1/2
			}
			typeOfCollision = bottom;
			collidedWithSomething = true;
			collidedWithX = oldlefttilenum;
			collidedWithY = toptilenum;
		}
		// collision cu partea DREAPTA SUS
		if (map[righttilenum][oldtoptilenum] >= 10)
		{
			if (map[righttilenum][oldtoptilenum] < 100)
			{
				playerX = oldx1;
				mapX = oldmapX;
			}
			collidedWithSomething = true;
			collidedWithX = righttilenum;
			collidedWithY = oldtoptilenum;
		}

		if (map[oldrighttilenum][toptilenum] >= 10)
		{
			if (map[oldrighttilenum][toptilenum] < 100)
			{
				playerY = oldy1;
				//  mapY = oldmapY;
				if (jumping == true)jumping = false; // if player was jumping he hit his head on something meaning the jump is over
			}
			typeOfCollision = bottom;
			collidedWithSomething = true;
			collidedWithX = oldrighttilenum;
			collidedWithY = toptilenum;
			//colliding below something 2/2
		}

		//collision cu partea STANGA JOS
		if (map[lefttilenum][oldbottomtilenum] >= 10)
		{
			if (map[lefttilenum][oldbottomtilenum] < 100)
			{
				playerX = oldx1;
				mapX = oldmapX;
			}
			collidedWithSomething = true;
			collidedWithX = lefttilenum;
			collidedWithY = oldbottomtilenum;
		}

		if (map[oldlefttilenum][bottomtilenum] >= 10)
		{
			if (map[oldlefttilenum][bottomtilenum] < 100)
			{
				//STANDING ABOVE TILE 1/2
				if (jumping == true)jumping = false;
				touchingGround = true;
				touchingGroundTimer = dbTimer(); // used so falling animation only trigger after 150ms
				playerY = oldy1;
				// mapY = oldmapY;
			}
			typeOfCollision = top;
			collidedWithSomething = true;
			collidedWithX = oldlefttilenum;
			collidedWithY = bottomtilenum;
		}


		//collision cu partea DREAPTA JOS
		if (map[righttilenum][oldbottomtilenum] >= 10)
		{
			if (map[righttilenum][oldbottomtilenum] < 100)
			{
				playerX = oldx1;
				mapX = oldmapX;
			}
			collidedWithSomething = true;
			collidedWithX = righttilenum;
			collidedWithY = oldbottomtilenum;
		}

		if (map[oldrighttilenum][bottomtilenum] >= 10)
		{
			if (map[oldrighttilenum][bottomtilenum] < 100)
			{
				//STANDING ABOVE TILE 2/2
				touchingGround = true;
				touchingGroundTimer = dbTimer(); // used so falling animation only trigger after 150ms
				if (jumping == true)jumping = false;
				playerY = oldy1;
				//  mapY = oldmapY;
			}
			typeOfCollision = top;
			collidedWithSomething = true;
			collidedWithX = oldrighttilenum;
			collidedWithY = bottomtilenum;
		}

		//keeps the map in place
		if (mapX < 60)
		{
			mapX = 60;
		}

		//check if player is touching the ground or NOT, if hes colliding with an air tile then hes not touching the ground
		if (map[oldrighttilenum][bottomtilenum] < 10 && map[oldlefttilenum][bottomtilenum] < 10)
		{
			touchingGround = false;
		}


		// Extra colisions: coins, mushrooms question boxes, hittin below.

		//handles items pickup and specific animations
		myEvents.pickupItems(collidedWithX, collidedWithY, typeOfCollision);

		enemies.piranhaCollision(collidedWithX, collidedWithY, typeOfCollision);
	}



	void phyAndMovement::controlCharacter()
	{

		if (IsMarioAlive == true)
		{
			// in case moving mario causes a goomba to collide with something
			//we can move them back
			for (int i = 0; i < maxWalkers; i++)
			{
				if (walkers[i].isAlive)
				{
					if (IsMarioAlive == true)
					{
						//store the map's x and y coordinates into the variables OldmapX and OldmapY

						//store the x and y coordinates of the player into the variables walkers[i].oldx and walkers[i].oldy
						walkers[i].oldx = walkers[i].x;
						walkers[i].oldy = walkers[i].y;
					}
				}
			}

			
			oldmapX = mapX;
			oldmapY = mapY;

			//store the x and y coordinates of  MARIO in oldX1 and oldY1
			oldx1 = playerX;
			oldy1 = playerY;

			//makes the player move by altering the sprites coordinates, if MARIO in cea mai stanga parte a hartii 
			//makes map move by altering the maps coordinates, if MARIO in centre
			if (stopMovement == false)
			{
				if (dbLeftKey() == 1)
				{
					//slows the player down before moving to a new direction
					if (walkingRight == true && speedx > 0)
					{
						speedx = 0;
						walkingRight = false;
					}
					else if (dbTimer() - speedTimer > 150)
					{
						speedTimer = dbTimer();
						if (speedx < 5)
							speedx++;
						walkingLeft = true;
					}
				}

				if (dbRightKey() == 1)
				{
					//incetinesc MArio inainte sa-si schimbe directia
					if (walkingLeft == true && speedx > 0)
					{
						speedx = 0;
						walkingLeft = false;
					}
					else if (dbTimer() - speedTimer > 150)
					{
						speedTimer = dbTimer();
						if (speedx < 5)speedx++;
						walkingRight = true;
					}
				}
				if (walkingRight == true)
				{
					if (mapX < playerX - (screenCenterX - 5) && mapX > playerX - (screenCenterX + 5))
					{
						mapX = mapX + speedx;
					}
					playerX = playerX + speedx;
				}

				if (walkingLeft == true)
				{
					if (mapX < playerX - (screenCenterX - 5) && mapX > playerX - (screenCenterX + 5))
					{
						mapX = mapX - speedx;
					}
					playerX = playerX - speedx;
				}

				//daca mergea left dar nu mai tine apasat left, il incetinim putin cate putin.
				if (dbLeftKey() == 0)
				{
					if (walkingLeft == true && speedx > 0)
					{
						if (dbTimer() - speedTimer > 150)
						{
							speedTimer = dbTimer();
							if (speedx > 0)speedx--;
						}
						if (speedx == 0) walkingLeft = false;
					}
				}
				//daca mergea right dar nu mai tine apasat right, il incetinim putin cate putin.
				if (dbRightKey() == 0)
				{
					if (walkingRight == true && speedx > 0)
					{
						if (dbTimer() - speedTimer > 150)
						{
							speedTimer = dbTimer();
							if (speedx > 0)speedx--;
						}
						if (speedx == 0) walkingRight = false;
					}
				}
				//daca nu e prea destept si apasa ambele butoane left & right (:
				if (dbRightKey() && dbLeftKey())
				{
					walkingRight = false;
					walkingLeft = false;
				}

				//increase speed if shift is pressed
				if (dbShiftKey())
				{
					//only start sprinting once speed has developed
					if (speedx > 4)
					{
						if (dbRightKey() || dbLeftKey())
						{
							//only allow him to sprint if hes touching the ground
							if (touchingGround)
							{
								speedx += 3;
							}
						}
					}
				}
				else						//nu mai tine apasat pe Shift. deci stopping sprint.
				{
					if (speedx > 4)speedx -= 1;
				}
				if (speedx > 9)speedx = 9;// limits the sprint speed
			}
		}

	}

};