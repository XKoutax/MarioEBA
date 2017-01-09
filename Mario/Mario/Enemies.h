#pragma once

marioEvents myEvents; // general mario events death, taking damage etc


class Enemies
{
public:
	void Enemies::createEnemy(int initial_X, int initial_Y)
	{

		walkers[currentWalker].id = misc.findFreeSprite();
		dbSprite(walkers[currentWalker].id, initial_X, initial_Y, G);
		//daca M e la jumatatea hartii si vrem sa spawnam inamici, 
		//asta ii va face sa se spawneze la coordonatele  mapX + mapY ( "miscarea" / cat de mult a mers playerul)
		walkers[currentWalker].x = initial_X + mapX; // fixez locul de unde apar inamicii (goomba)
		walkers[currentWalker].y = initial_Y + mapY;
		walkers[currentWalker].ASleep = true;
		currentWalker++;


	}
	//inamicii apar abia atunci cand mario e aproape de pozitia lor pe harta
	//pt a evita incidente precum moarte lor pana Mario ajunge la ei
	void Enemies::AwakeEnemies()
	{
		int distance;
		for (int i = 0; i < maxWalkers; i++)
		{
			if (dbSpriteExist(walkers[i].id))
			{
				//verific daca Mario e aproape de goomba. Daca da acesta apare si incepe sa mearga spre mario
				if (walkers[i].ASleep)
				{
					//cautam distanta dintre Mario si goomba
					distance = misc.get2dDistance(dbSpriteX(mario),
						dbSpriteY(mario), dbSpriteX(walkers[i].id),
						dbSpriteY(walkers[i].id));

					//spawn goomba daca Mario e aproape
					if (distance < 1500)
					{
						walkers[i].ASleep = false;
						walkers[i].isAlive = true;
						walkers[i].walking = true;
						walkers[i].touchingGround = false;
						walkers[i].isDying = false;
						walkers[i].typeOf = GOOMBA;
						walkers[i].walkingDirection = LEFT;
						//goomba vor incepe sa mearga mereu spre stanga
						//atunci cand se lovesc de ceva schimba directia

					}

				}
			}
		}
	}

	void Enemies::piranhaCollision(int arrX, int arrY, int typeOfCollision)
	{
		//Mario primeste damage daca atinge oricare din partea dreapta sau stanga a plantei
		if (map[arrX][arrY] == EPl || map[arrX][arrY] == EPr)
		{
			for (int i = 0; i < maxPiranhas; i++)
			{
				//plasez planta atunci cand gasem locatia potrivita
				if (piranhaPlants[i].ReferenceJ == arrX && piranhaPlants[i].ReferenceI == arrY)
				{
					//damage doar daca planta este iesita la suprafata
					if (piranhaPlants[i].plantAnim > 0 && piranhaPlants[i].plantAnim < 28)
					{
						myEvents.takeDamage();
					}
					break;
				}
			}
		}
	}

	//verifica daca Mario este aproape. Daca nu, planta nu se ridica
	void Enemies::piranhaAI()
	{
		for (int i = 0; i < maxPiranhas; i++)
		{
			if (piranhaPlants[i].isAlive)
			{
				if (piranhaPlants[i].typeOf == EP || piranhaPlants[i].typeOf == EPr)
				{
					piranhaPlants[i].distance = misc.get2dDistance(dbSpriteX(mario), dbSpriteY(mario), dbSpriteX(piranhaPlants[i].id), dbSpriteY(piranhaPlants[i].id));

					if (piranhaPlants[i].distance < 225)
					{
						piranhaPlants[i].tooClose = true;
					}
					else piranhaPlants[i].tooClose = false;
				}
			}
		}
	}
};

