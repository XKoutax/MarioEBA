
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