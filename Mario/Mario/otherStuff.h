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
};