#pragma once
#include "otherStuff.h"


class mapHandling
{
public:

	void playSounds()
	{
		if (IsMarioAlive)
		{
			//daca Sunetul de CheckPoint merge, lower MainTheme Sound
			if (dbSoundPlaying(ScheckPoint))dbSetSoundVolume(SmainTheme, 80);
			else dbSetSoundVolume(SmainTheme, 100);
			//daca MainTheme is not playing   SI   level not over, trebuie sa mearga MainTheme Sound iar
			if (dbSoundPlaying(SmainTheme) == 0 && levelOver == 0)dbPlaySound(SmainTheme);
		}
	}

	void mapHandling::displayInformation()
	{
		dbSetTextSize(25);
		//afiseaza punctele
		char points[100];
		sprintf_s(points, 200, "Score \n %d", score);
		dbText(50, 25, points);                                // dbText( x, y, "string" )    <--- x si y sunt coordonate. scrie din coltul stanga sus.

															   //afizeaza coins
		char coinNum[100];
		sprintf_s(coinNum, 200, "Coins \n %d", coins);
		dbText(150, 25, coinNum);

		//afiseaza nivel
		char levelbeingPlayed[100];
		sprintf_s(levelbeingPlayed, 200, "Level \n %d", level);
		dbText(250, 25, levelbeingPlayed);

		//afiseaza vieti
		char Lifes[100];
		sprintf_s(Lifes, 200, "Lifes \n %d", lifes);
		dbText(400, 25, Lifes);

		//afiseaza timpul ramas
		char timeLeft[100];
		sprintf_s(timeLeft, 200, "Time \n %d", time);
		dbText(500, 25, timeLeft);
	}


	//pune animmatiile pe harta
	void mapHandling::pasteTiles(int x, int tilenumx, int y, int tilenumy, int tempx, int tempy)
	{
		//question box
		if (map[x + tilenumx][y + tilenumy] == qC || map[x + tilenumx][y + tilenumy] == qF)
		{
			if (dbTimer() - questionBoxTimer > 75) //animatiile se schimba la 75 de milisec
			{
				questionBoxTimer = dbTimer();
				qBoxAnim++;
				if (qBoxAnim == 26) qBoxAnim = 0;
			}
			dbPasteImage(q + qBoxAnim, (x * tilesizex) - tempx, (y * tilesizey) - tempy);
		}
		//coins
		else if (map[x + tilenumx][y + tilenumy] == C)
		{
			while (dbTimer() - coinTimer > 100) //animatiile de schimba la 100 milisec
			{
				coinTimer = dbTimer();
				coinAnim++;
				if (coinAnim == 6) coinAnim = 0;
			}
			dbPasteImage(map[x + tilenumx][y + tilenumy] + coinAnim, (x * tilesizex) - tempx, (y * tilesizey) - tempy);
		}
		//planta pirania partea stanga
		else if (map[x + tilenumx][y + tilenumy] == EPl)
		{
			for (int i = 0; i < maxPiranhas; i++)
			{

				if (piranhaPlants[i].ReferenceJ == x + tilenumx && piranhaPlants[i].ReferenceI == y + tilenumy)
				{
					if (dbSpriteVisible(piranhaPlants[i].id) == 0) //initial e ascunsa
					{
						dbShowSprite(piranhaPlants[i].id);
					}
					// dbPasteImage( map[x + tilenumx][y + tilenumy] + piranhaPlants[i+1].plantAnim, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
					dbSprite(piranhaPlants[i].id, (x * tilesizex) - tempx, (y * tilesizey) - tempy, map[x + tilenumx][y + tilenumy] + piranhaPlants[i + 1].plantAnim);
					/*dbSprite e folosit doar pt a vefirica pozitia plantei pentru a putea, ulterior, face ca planta de pe poz respectiva
					sa nu apara decat o data atunci cand mario e aproape de ea*/
					break; //odata ce a gasit coodonatele plantei iese din bucla
				}
			}
		}
		//planta pirania partea dreapta
		else if (map[x + tilenumx][y + tilenumy] == EPr)
		{
			for (int i = 0; i < maxPiranhas; i++)
			{
				if (piranhaPlants[i].ReferenceJ == x + tilenumx && piranhaPlants[i].ReferenceI == y + tilenumy)
				{

					if (dbSpriteVisible(piranhaPlants[i].id) == 0)
					{
						dbShowSprite(piranhaPlants[i].id);
					}
					if (dbTimer() - piranhaPlants[i].plantTimer > 100 && dbTimer() - piranhaPlants[i].plantLoopTimer > 1400) //animation frames change every 100 ms
					{
						piranhaPlants[i].plantTimer = dbTimer();
						//verifica daca mario e aproape de partea dreapta a plantei;
						if (piranhaPlants[i].tooClose == true && piranhaPlants[i].plantAnim == 0)
						{
							piranhaPlants[i].plantLoopTimer = dbTimer();
							//daca e prea aproape, planta nu se mai ridica pana mario nu se indeparteaza de planta cu o anumita distanta
						}
						//verifica daca mario e aproape de partea stanga a plantei
						else if (piranhaPlants[i - 1].tooClose == true && piranhaPlants[i].plantAnim == 0)
						{
							piranhaPlants[i].plantLoopTimer = dbTimer();
						}
						else
						{
							piranhaPlants[i].plantAnim++;
							//sunet atunci cand planta deschide si inchide gura;
							if (piranhaPlants[i].plantAnim == 5 || piranhaPlants[i].plantAnim == 10 || piranhaPlants[i].plantAnim == 15 || piranhaPlants[i].plantAnim == 25)
							{
								//doar daca mario este aproape de planta
								if (piranhaPlants[i].distance < 500)
								{
									dbPlaySound(SplantCrunch);
								}
							}
						}
						if (piranhaPlants[i].plantAnim == 30)
						{
							piranhaPlants[i].plantAnim = 0;
							piranhaPlants[i].plantLoopTimer = dbTimer();
						}
					}
					// dbPasteImage( map[x + tilenumx][y + tilenumy] + piranhaPlants[i].plantAnim, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
					dbSprite(piranhaPlants[i].id, (x * tilesizex) - tempx, (y * tilesizey) - tempy, map[x + tilenumx][y + tilenumy] + piranhaPlants[i].plantAnim);
					/*dbSprite e folosit doar pt a vefirica pozitia plantei pentru a putea, ulterior, face ca planta de pe poz respectiva
					sa nu apara decat o data atunci cand mario e aproape de ea*/
					break;
				}

			}
		}
		//floarea
		else if (map[x + tilenumx][y + tilenumy] == f)
		{
			dbPasteImage(map[x + tilenumx][y + tilenumy], (x * tilesizex) - tempx, (y * tilesizey) - tempy);
		}
		//tile based anims ex: animatia '1000 score' , '1 up'
        else if(map[x + tilenumx][y + tilenumy] == SA) //score animation
        {
            bool foundRightElement = false; // iese din array o data ce a gasit id-ul elementului
            // verifica daca este anim
            for(int i = 0; i < maxAnimations && foundRightElement == false; i++)
            {
                if(anims[i].busy == true)
                {
                    if(anims[i].typeOf == IMAGE)    //IMAGE or Sprite
                    {
                        //daca gasim animatia
                        if(anims[i].id == map[x + tilenumx][y + tilenumy] && anims[i].x == x + tilenumx && anims[i].y == y + tilenumy)
                        {
                            foundRightElement = true;
                            //1000 score animation
                            if(dbTimer() - anims[i].timer > 80) //frame-urile se schimba la 75 milisec
                            {
                                anims[i].timer = dbTimer();
                                anims[i].frames++;

                                if(anims[i].frames == anims[i].HighestFrame)
                                {
                                    anims[i].busy = false;
                                    //devine o 'patratica' de  aer sau 1up mushroom
                                    map[x + tilenumx][y + tilenumy] = anims[i].FinalFrame;
                                }
                            }
                            dbPasteImage( anims[i].SetImage + anims[i].frames, ( x * tilesizex ) - tempx,  ( y * tilesizey ) - tempy );
                        }
                    }
                }
            }

        }
        //GOOMBA inainte de primul spawn
        else if(map[x + tilenumx][y + tilenumy] == G)
        {
            map[x + tilenumx][y + tilenumy] = a; //patratica de aer
            enemy.createEnemy((( x * tilesizex ) - tempx),  (y * tilesizey ) - tempy);
        }
		//mario spawn spot
		else if (map[x + tilenumx][y + tilenumy] == M)
		{
			map[x + tilenumx][y + tilenumy] = a;
			if (marioSpawned == false)
			{
				marioSpawned = true;
				myEvents.createPlayer(((x * tilesizex) - tempx), (y * tilesizey) - tempy);
			}
		}
		//1up box inainte sa fie descoperita
		else if (map[x + tilenumx][y + tilenumy] == L)
		{
			dbPasteImage(map[x + tilenumx][y + tilenumy], (x * tilesizex) - tempx, (y * tilesizey) - tempy);
		}
		//Green mushroom +1 life
		else if (map[x + tilenumx][y + tilenumy] == gM)
		{
			dbPasteImage(_1up_1 + 16, (x * tilesizex) - tempx, (y * tilesizey) - tempy);
		}
		//imaginile care au ramas de pus pe harta
		else
		{
			dbPasteImage(map[x + tilenumx][y + tilenumy], (x * tilesizex) - tempx, (y * tilesizey) - tempy);
		}
	}

	void mapHandling::displayLevel()
	{
	
		int tilenumx = mapX / numoftilesx;
		int tilenumy = mapY / numoftilesy;

		//this calculation works out how many pixels to offset the position where the tile
		//images should be plaaced.
		int tempx = mapX - (tilenumx * tilesizex);
		int tempy = mapY - (tilenumy * tilesizey);

		//afiseaza imaginile pe ecran in ordinea corecta, foolosind coordonatele potrivite
		for (int y = 0; y <= 12; y++) //12 linii
		{
			for (int x = 0; x <= 15; x++)//15 colonane afisate pe ecran de fiecare data
			{
				pasteTiles(x, tilenumx, y, tilenumy, tempx, tempy);
			}
		}
	}
};
#pragma once
