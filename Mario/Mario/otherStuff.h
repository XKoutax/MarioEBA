#pragma once
class other
{
public:

	int other::findFreeSprite()
	{
		//incepem de la 10 pt a ne asigura ca sprite-urile nu sunt overwritten
		int i = 10;
		while (dbSpriteExist(i))
		{
			i++;
		}
		return i;
	}

	bool other::noEssentialKeyBeingPressed()
	{
		if (!dbUpKey() && !dbLeftKey() && !dbRightKey() && !dbSpaceKey())
		{
			return true;
		}
		return false;
	}

	//cautam sprite-urile, animatiile etc libere
	int other::findFreeAnimation()
	{
		for (int i = 0; i < maxAnimations; i++)
		{
			if (anims[i].busy == false)
			{
				return i;
			}
		}
		return 0;
	}


	//scap de inamici pentru a nu se suprapune pe alte patratele
	//cand mario e respawned
	// cand Mario moare si este respawnat => enemies respawn------------------
	void other::cleanupEnemies()
	{
		for (int i = 0; i < maxPiranhas; i++)         //altfel vor ramane pe ecran si for fi erori cu memoryasdf
		{
			if (dbSpriteExist(piranhaPlants[i].id))      //resetez TOATE variabilele structurii, mai bine decat sa uit una.
			{
				dbDeleteSprite(piranhaPlants[i].id);    //important sa deleteSprite INAINTE de id = 0. altfel sterg altceva
				piranhaPlants[i].isAlive = false;
				piranhaPlants[i].tooClose = false;
				piranhaPlants[i].ReferenceI = 0;
				piranhaPlants[i].ReferenceJ = 0;
				piranhaPlants[i].plantAnim = 0;
				piranhaPlants[i].id = 0;
			}
		}
		//dispar Goomba
		for (int i = 0; i < maxWalkers; i++)
		{
			if (dbSpriteExist(walkers[i].id))
			{
				dbDeleteSprite(walkers[i].id);
				//devine o patratica de aer. Spawn goomba here 
				walkers[i].isAlive = false;
				walkers[i].walking = false;
				walkers[i].touchingGround = false;
				walkers[i].x = 0; //locul din care goomba apareau (spawn) 
				walkers[i].y = 0;
				walkers[i].typeOf = 0;
				//reset any death
				walkers[i].isDying = false;
				walkers[i].id = 0;
			}
		}
		currentWalker = 1; //urmatorul Goomba creat vi fi #1 , apoi currentWalker++
	}

	//returneaza distanda dintre doua sprite-uri
	float other::get2dDistance(int x1, int y1, int x2, int y2)
	{
		return dbSqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
	}
};