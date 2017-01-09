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



	//returneaza distanda dintre doua sprite-uri
	float other::get2dDistance(int x1, int y1, int x2, int y2)
	{
		return dbSqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
	}
};