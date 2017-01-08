#pragma once

class mapHandlingDetails
{
public:

	//anim pt scor
	void mapHandlingDetails::startAnimation(int scoreToDisplay, int typeOfScore, int x, int y, int topFrame, int solidFrame, int delay)
	{
		//solid frame pt animatii care trebuie pozitionate pe un tile ("checkpoint reached" urca pe un tile si jumatate)
		if (typeOfScore == IMAGE)
			map[x][y] = SA;

		int i = misc.findFreeAnimation();

		if (anims[i].busy == false)
		{
			if (typeOfScore == IMAGE)
				anims[i].id = map[x][y];

			anims[i].animDelay = delay;
			anims[i].SetImage = scoreToDisplay;
			anims[i].HighestFrame = topFrame;
			anims[i].x = x;
			anims[i].y = y;
			anims[i].busy = true;
			anims[i].timer = dbTimer();
			anims[i].frames = 0;
			anims[i].typeOf = typeOfScore;
			anims[i].OriginalMapX = mapX;				//memoreaza map X ca sa putem mentine imaginea in aceeasi pozitie in timpul animatiei
			anims[i].FinalFrame = solidFrame;
		}
	}


	void mapHandlingDetails::LevelAnimations()
	{
		for (int i = 0; i < maxAnimations; i++)
		{
			if (anims[i].busy == true)
			{
				if (dbTimer() - anims[i].timer > anims[i].animDelay)			 //animation frames change every 80 ms
				{
					anims[i].timer = dbTimer();
					anims[i].frames++;

					if (anims[i].frames == anims[i].HighestFrame)
					{
						anims[i].busy = false;

					}
				}


				if (anims[i].typeOf == SPRITE)			//checkpoint reached / scores+100 / etc. are sprite
				{
					dbPasteImage(anims[i].SetImage + anims[i].frames, anims[i].x + (anims[i].OriginalMapX - mapX), anims[i].y);//Keeps animation still, din cauza miscarii mapei
				}

			}
		}
	}


};

