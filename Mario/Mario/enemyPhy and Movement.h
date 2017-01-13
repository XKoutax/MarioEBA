
#pragma once

class EnemyPhyAndMovement
{
public:
	void EnemyPhyAndMovement::changeDirection(int element)
	{
		if (walkers[element].walkingDirection == LEFT)
		{
			walkers[element].walkingDirection = RIGHT;
		}
		else
		{
			walkers[element].walkingDirection = LEFT;
		}
	}

	int EnemyPhyAndMovement::collidingWithWalker(int element)
	{
		//verific daca un goomba s-a lovit de altul
		//daca da, le schimbam directia
		for (int i = 0; i < maxWalkers; i++)
		{
			//am grija ca nu cumva sa verific coliziunea dintre dintre acelas sprite
			//v-a returna true => goomba nu o sa se mai miste
			if (dbSpriteExist(walkers[i].id) && walkers[i].id != walkers[element].id)
			{
				if (walkers[i].isAlive)
				{
					if (dbSpriteCollision(walkers[element].id, walkers[i].id))
					{
						return i; //goomba-ul de care s-a lovit
					}
				}
			}
		}
		return -1;
	}

	void EnemyPhyAndMovement::FlashMe(int TimeToFlash, int CharacterToFlash)
	{
		if (TimeToFlash > 200 && TimeToFlash < 300)
		{
			dbHideSprite(CharacterToFlash); // ii ascund
		}
		else if (TimeToFlash > 300 && TimeToFlash < 400)
		{
			dbShowSprite(CharacterToFlash); //reapar
		}
		else if (TimeToFlash > 400 && TimeToFlash < 500)
		{
			dbHideSprite(CharacterToFlash);
		}
		else if (TimeToFlash > 500 && TimeToFlash < 600)
		{
			dbShowSprite(CharacterToFlash);
		}
		else if (TimeToFlash > 600 && TimeToFlash < 700)
		{
			dbHideSprite(CharacterToFlash);
		}
		else if (TimeToFlash > 700 && TimeToFlash < 800)
		{
			dbShowSprite(CharacterToFlash);
		}
		else if (TimeToFlash > 800 && TimeToFlash < 900)
		{
			dbHideSprite(CharacterToFlash);
		}
		else if (TimeToFlash > 900 && TimeToFlash < 1000)
		{
			dbShowSprite(CharacterToFlash);
		}
	}
	void EnemyPhyAndMovement::goombaAnim()
	{
		for (int i = 0; i < maxWalkers; i++)
		{
			if (dbSpriteExist(walkers[i].id))
			{
				if (walkers[i].isAlive)
				{
					dbSprite(walkers[i].id, walkers[i].x - mapX, walkers[i].y, G + walkers[i].currentFrame);
					if (walkers[i].walking)
					{
						if (dbTimer() - walkers[i].walkingTimer > 90)
						{
							walkers[i].walkingTimer = dbTimer();

							//cand ajunge la ultimul frame, reset it
							if (walkers[i].currentFrame > 5)
							{
								walkers[i].currentFrame = 0;
							}
							walkers[i].currentFrame++;
						}
					}
				}
				//daca inamicul moare, afisez o imagine corespunzatoare
				else if (walkers[i].isDying)
				{
					dbSprite(walkers[i].id, walkers[i].x - mapX, walkers[i].y - mapY, G + 7);
					//il afisam mort pt cateva milisec, apoi dispare 
					int TimeToFlash = dbTimer() - walkers[i].walkingTimer;

					//imaginea inamicului are flash-uri pana moare de tot
					FlashMe(TimeToFlash, walkers[i].id);

					if (TimeToFlash > 1150)
					{
						walkers[i].isDying = false;
						dbHideSprite(walkers[i].id); // dispar
					}

				}
			}
		}
	}




	void EnemyPhyAndMovement::gravity()
	{

		for (int i = 0; i < maxWalkers; i++)
		{
			if (walkers[i].isAlive)
			{
				if (!walkers[i].touchingGround)
				{
					walkers[i].oldy = walkers[i].y;
					//memoreaza viteza in caz ca se loveste de ceva in timp ce cade 
					walkers[i].y = walkers[i].y + speedy;
					wasThereAnEnCollision(i);
				}
			}
		}
	}

	bool EnemyPhyAndMovement::wasThereAnEnCollision(int element)
	{
		int collidedWithX = 0;
		int collidedWithY = 0; //pentru a verifica de cine s-a lovit goomba

							   //memorez vechile si noile margini ale sprite-urilor din variabilele respective: left, right,top, buttom
							   //coordonatele stanga dreapta actuale
		int lefttilenum = int(walkers[element].x / tilesizex);
		int righttilenum = int((walkers[element].x + (tilesizex - 1)) / tilesizex);
		//coordonatele sus jos actuale
		int toptilenum = int(walkers[element].y / tilesizey);
		int bottomtilenum = int((walkers[element].y + (tilesizey - 1)) / (tilesizey));

		//coordonatele stanga dreapta dinainte
		int oldlefttilenum = int(walkers[element].oldx / tilesizex);
		int oldrighttilenum = int((walkers[element].oldx + (tilesizex - 1)) / tilesizex);
		//coordonatele sus jos dinainte
		int oldtoptilenum = int(walkers[element].oldy / tilesizey);
		int oldbottomtilenum = int((walkers[element].oldy + (tilesizey - 1)) / (tilesizey));

		//verific cele 4 puncte de coliziune
		//Daca punctul de coliziune este o patratica peste care nu pot sa trec( in cazul de fata daca numarul imaginii >10)
		//memoram  vechile coordonatele ale sprite-ului.
		bool wasThereACollision = false;

		//top-left collision point
		if (map[lefttilenum][oldtoptilenum] >= 10)
		{
			if (map[lefttilenum][oldtoptilenum] < 100)
			{
				walkers[element].x = walkers[element].oldx;
				wasThereACollision = true;
			}
			collidedWithX = lefttilenum;
			collidedWithY = oldtoptilenum;
		}

		if (map[oldlefttilenum][toptilenum] >= 10)
		{
			if (map[oldlefttilenum][toptilenum] < 100)
			{
				walkers[element].y = walkers[element].oldy;
				wasThereACollision = true;
			}
			collidedWithX = oldlefttilenum;
			collidedWithY = toptilenum;
		}
		// top-right collision point
		if (map[righttilenum][oldtoptilenum] >= 10)
		{
			if (map[righttilenum][oldtoptilenum] < 100)
			{
				walkers[element].x = walkers[element].oldx;
				wasThereACollision = true;

			}
			collidedWithX = righttilenum;
			collidedWithY = oldtoptilenum;
		}

		if (map[oldrighttilenum][toptilenum] >= 10)
		{
			if (map[oldrighttilenum][toptilenum] < 100)
			{
				walkers[element].y = walkers[element].oldy;
				wasThereACollision = true;
			}
			collidedWithX = oldrighttilenum;
			collidedWithY = toptilenum;
		}

		// bottom-left collision point
		if (map[lefttilenum][oldbottomtilenum] >= 10)
		{
			if (map[lefttilenum][oldbottomtilenum] < 100)
			{
				walkers[element].x = walkers[element].oldx;
				wasThereACollision = true;
			}
			collidedWithX = lefttilenum;
			collidedWithY = oldbottomtilenum;
		}

		if (map[oldlefttilenum][bottomtilenum] >= 10)
		{
			if (map[oldlefttilenum][bottomtilenum] < 100)
			{
				walkers[element].touchingGround = true;
				walkers[element].y = walkers[element].oldy;
				wasThereACollision = true;
			}
			collidedWithX = oldlefttilenum;
			collidedWithY = bottomtilenum;
		}

		// bottom-right collision point
		if (map[righttilenum][oldbottomtilenum] >= 10)
		{
			if (map[righttilenum][oldbottomtilenum] < 100)
			{
				walkers[element].x = walkers[element].oldx;
				wasThereACollision = true;
			}
			collidedWithX = righttilenum;
			collidedWithY = oldbottomtilenum;
		}

		if (map[oldrighttilenum][bottomtilenum] >= 10)
		{
			if (map[oldrighttilenum][bottomtilenum] < 100)
			{
				walkers[element].touchingGround = true;
				walkers[element].y = walkers[element].oldy;
				wasThereACollision = true;
			}
			collidedWithX = oldrighttilenum;
			collidedWithY = bottomtilenum;
		}

		//verific daca atinge pamantul sau nu, daca se loveste de o 'patratica' de aer, atunci el nu atinge pamantul
		if (map[oldrighttilenum][bottomtilenum] < 10 && map[oldlefttilenum][bottomtilenum] < 10)
		{
			walkers[element].touchingGround = false;
		}

		if (wasThereACollision)
		{
			collisionEvents(collidedWithX, collidedWithY, element);
			return true;
		}
		return false; //daca nu este nicio coliziune
	}

	void EnemyPhyAndMovement::controlAI()
	{
		bool thereWasACollision = false;
		for (int i = 0; i < maxWalkers; i++)
		{
			if (dbSpriteExist(walkers[i].id))
			{
				if (walkers[i].isAlive)
				{
					//se misca doar daca atinge pamantul
					if (walkers[i].touchingGround)
					{
						//memoram coord x si y in var walkers[i].oldx si walkers[i].oldy
						//in cazul in care se loveste de ceva
						//dispar si reapar , nu trec prin obiectul respectiv

						walkers[i].oldx = walkers[i].x;

						if (walkers[i].walkingDirection == LEFT)
						{
							//ma asigur ca este cu fata in directia in care merge
							if (dbSpriteMirrored(walkers[i].id) == 0) dbMirrorSprite(walkers[i].id);
							walkers[i].x -= speedxEN;
						}
						else if (walkers[i].walkingDirection == RIGHT)
						{
							//ma asigur ca este cu fata in directia in care merge
							if (dbSpriteMirrored(walkers[i].id) == 1) dbMirrorSprite(walkers[i].id);
							walkers[i].x += speedxEN;
						}

						//verific daca sunt coliziuni, daca da, il intorc din drum
						if (wasThereAnEnCollision(i))
						{
							walkers[i].x = walkers[i].oldx;
							changeDirection(i);
						}

						int collidedAgainstSomeone = collidingWithWalker(i);
						if (collidedAgainstSomeone != -1)
						{
							//20 millisec in care doi goomba se ciocnesc
							if (dbTimer() - walkers[i].CollisionTimer < 20)
							{
								if (walkers[collidedAgainstSomeone].id == walkers[i].LastEnemyCollided)
								{
									thereWasACollision = false;
								}
							}
							else
							{
								thereWasACollision = true;
							}

							if (thereWasACollision)
							{
								//2sprite-uri goomba s-au lovit atunci ii ducem in pozitia anterioara schimbandu-le directia
								//resetez timpul de coliziune/
								walkers[i].x = walkers[i].oldx;
								changeDirection(i);
								changeDirection(collidedAgainstSomeone);
								//memorez ultima coliziune si le dau timp sa se departeze
								walkers[i].LastEnemyCollided = walkers[collidedAgainstSomeone].id;
								walkers[i].CollisionTimer = dbTimer(); //resetez timpul
								walkers[collidedAgainstSomeone].LastEnemyCollided = walkers[i].id;
								walkers[collidedAgainstSomeone].CollisionTimer = dbTimer(); //resetez timpul
							}
						}
					}
				}
			}
		}
	}



	void EnemyPhyAndMovement::collisionEvents(int arrX, int arrY, int id)
	{
		//omor inamicii goomba atunci cand cad in groapa
		if (map[arrX][arrY] == d)
		{
			//if(walkers[id].typeOf == GOOMBA)
			//{
			walkers[id].isAlive = false;
			walkers[id].walking = false;
			dbHideSprite(walkers[id].id);
			//}

		}
	}



	//omor inamicul de pe o anumita pozitie
	void EnemyPhyAndMovement::KillMe(int ElementToKill)
	{
		walkers[ElementToKill].isAlive = false;
		walkers[ElementToKill].walking = false;
		walkers[ElementToKill].isDying = true;
		walkers[ElementToKill].walkingTimer = dbTimer();

	}


};