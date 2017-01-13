#pragma once
#include <cstdlib>
#include <ctime>
//Load la toate imaginile + mapa
class loader
{
public:
	void loadCurrentLevel(int level);
	void loadImages();
	void loadSounds();
	void loadGenerator();
};
other misc;

void loader::loadSounds()
{
	dbLoadSound("Sounds//Main Theme.wav", SmainTheme);
	dbLoadSound("Sounds//coin.wav", ScoinPickup);
	dbLoadSound("Sounds//Flower appear.wav", SFlowerAppear);
	dbLoadSound("Sounds//jump.wav", Sjump);
	dbLoadSound("Sounds//Death.wav", Sdeath);
	dbLoadSound("Sounds//break block.wav", Sbrick);
	dbLoadSound("Sounds//bump.wav", Sbump);
	dbLoadSound("Sounds//FlowerPickup.wav", SFlowerPickup);
	dbLoadSound("Sounds//checkpoint 1.wav", ScheckPoint);
	dbLoadSound("Sounds//life.wav", SnewLife);
	dbLoadSound("Sounds//Flag pole.wav", SendLevel);
	dbLoadSound("Sounds//warning.wav", StimeWarning);
	dbLoadSound("Sounds//clear level.wav", SlevelClear);
	dbLoadSound("Sounds//Pick up powerup.wav", Spowerup);
	dbLoadSound("Sounds//plant crunch.wav", SplantCrunch);
	dbLoadSound("Sounds//EnemyStomp.wav", Sstomp);
	dbLoadSound("Sounds//PipeAndDamage.wav", SPipeAndDamage);
}


void loader::loadGenerator()
{
	int i = 0;
	int j = 0;

	srand(time(NULL));

	int maxClouds = rand() % 10 + 20;		//intre 20 - 30
	int maxBrix = rand() % 20 + 40;			//
	int maxQc = rand() % 10 + 20;			//intre 20 si 29
	int maxCoins = rand() % 20 + 20;			//intre 20 si 39
	int maxGP = 4;
	int maxGoomba = rand() % 6 + 5;
	int maxGround = 10;
	int maxCrown = 3;
	int maxOneup = 2;



	//PRE STABILITE
	for (i = 0; i<ROWS; i++)
		for (j = 0; j<COLS; j++)
		{
			if (i == 0 || (j == 0 && i < 9))
				matrix[i][j] = r;
			else if (i == 9)
				matrix[i][j] = g;
			else if (i == 10)
				matrix[i][j] = B;
			else if (i == 11)
				matrix[i][j] = d;
			else
				matrix[i][j] = a;
		}

	matrix[8][100] = fB;
	matrix[7][100] = fT;

	//END PRE STABILITE




	int linie = 0;
	int coloana = 0;



	//CLOUDS
	for (i = 1; i <= maxClouds; i++)
	{
		do
		{
			linie = 1 + rand() % 3;
			coloana = 5 + rand() % 164;
		} while (matrix[linie][coloana] != a &&
			matrix[linie][coloana + 1] != a &&
			matrix[linie][coloana - 1] != a &&
			matrix[linie + 1][coloana] != a &&
			matrix[linie + 1][coloana + 1] != a &&
			matrix[linie + 1][coloana - 1] != a &&
			matrix[linie - 1][coloana] != a &&
			matrix[linie - 1][coloana - 1] != a &&
			matrix[linie - 1][coloana + 1] != a);

		matrix[linie][coloana] = c;

	}




	//BRICKS
	for (i = 1; i <= maxBrix; i++)
	{
		do
		{
			linie = 4 + rand() % 3;
			coloana = 5 + rand() % 155;
		} while (matrix[linie][coloana] != a);


		if (8 - linie >= 3)
		{

			if (linie == 5)
				for (int kk = -3; kk <= 3; kk++)
				{
					int dublu = 0;
					if (kk == 0) continue;
					if (matrix[linie + 1][coloana + kk] == b)
					{
						matrix[linie][coloana] = b; //maxBrix--;
						dublu = rand() % 2;
						if (dublu == 1) { matrix[linie + 1][coloana + kk - 1] = b; maxBrix--; }
						break;
					}

					if (matrix[linie + 2][coloana + k] == b)
					{
						if (kk == -3 || kk == 3) continue;

						matrix[linie][coloana] = b; //maxBrix--;
						dublu = rand() % 2;
						if (dublu == 0) { matrix[linie + 1][coloana + kk - 1] = b; maxBrix--; }

						break;
					}
				}

			if (linie == 4)
			{
				int gasitL6 = 0;
				for (int kk = -2; kk <= 2; kk++)
				{
					if (kk == 0) continue;
					if (matrix[linie + 2][coloana + kk] == b)
					{
						matrix[linie][coloana] = b;
						//maxBrix--;
						gasitL6 = 1;
					}
				}

				if (gasitL6 == 0)
				{
					for (int kk = -3; kk <= 3; kk++)
					{
						if (kk == 0) continue;
						if (matrix[5][coloana + kk] == b)
						{
							break;
						}
					}

					for (int jjj = -2; jjj <= 2; jjj++)
					{
						if (jjj == 0) continue;

						if (matrix[7][coloana + jjj] == b)
						{
							matrix[linie][coloana] = b;
							//maxBrix--;
						}
					}
				}

			}
		}
		else
		{
			matrix[linie][coloana] = b;
			maxBrix--;
		}
		int OK = rand() % 4;
		switch (OK)
		{
		case 0:
		{

			if (matrix[linie][coloana + 1] == a && matrix[linie - 1][coloana + 1] == a && matrix[linie - 1][coloana + 2] == a)
			{
				matrix[linie][coloana + 1] = b;
				matrix[linie - 1][coloana + 1] = b;
				matrix[linie - 1][coloana + 2] = b;
				maxBrix = maxBrix - 3;
			}
			break;
		}

		case 1:
		{

			if (matrix[linie][coloana + 1] == a)
			{
				matrix[linie][coloana + 1] = qC;
				maxQc--;									//de declarat
			}

			if (matrix[linie][coloana + 2] == a)
			{
				matrix[linie][coloana + 2] = b;

			}

			break;
		}

		case 2:
		{
			if (matrix[linie][coloana + 1] == a && matrix[linie][coloana + 2] == a)
			{
				matrix[linie][coloana] = b;
				matrix[linie][coloana + 1] = b;						// b b b 
				matrix[linie][coloana + 2] = b;

				int OKc = rand() % 2;
				switch (OKc)
				{
				case 1:
				{
					if (matrix[linie - 1][coloana] == a && matrix[linie - 1][coloana + 1] == a && matrix[linie - 1][coloana + 2] == a)
					{
						matrix[linie - 1][coloana] = C;				//  C C C
						matrix[linie - 1][coloana + 1] = C;				//	  
						matrix[linie - 1][coloana + 2] = C;				//	    
						maxCoins = maxCoins - 3;
					}
					break;

				}

				case 0:
				{
					if (matrix[linie - 1][coloana + 4] == a && matrix[linie][coloana + 5] == a && matrix[linie + 1][coloana + 6] == a)
					{
						matrix[linie - 1][coloana + 4] = C;			// C
						matrix[linie][coloana + 5] = C;			//   C
						matrix[linie + 1][coloana + 6] = C;			//     C
						maxCoins = maxCoins - 3;
					}


				}


				}



			}



			break;
		}

		}

	}




	//PAMANT IN AER

	do {
		linie = 4 + rand() % 3;
		coloana = 5 + rand() % 150;
	} while (matrix[linie][coloana] != a && matrix[linie][coloana + 1] != a && matrix[linie - 1][coloana + 1] != a);

	for (int i = 1; i <= maxGround; i++)
	{
		int okGround = rand() % 2;
		switch (okGround)
		{
		case 0:
		{
			if (matrix[linie][coloana - 1] == a && matrix[linie - 1][coloana - 1] == a && matrix[linie - 1][coloana] == a && matrix[linie - 2][coloana] == a && matrix[linie][coloana + 1] == a && matrix[linie][coloana + 3] == a && matrix[linie][coloana + 2] == a)
			{
				matrix[linie][coloana] = g;							//      g
				matrix[linie][coloana + 1] = g;						//   g  g  g  
				matrix[linie - 1][coloana + 1] = g;						//
				matrix[linie][coloana + 2] = g;
			}
			break;
		}
		case 1:
		{
			if (matrix[linie][coloana + 2] == a && matrix[linie - 1][coloana + 2] == a && matrix[linie - 1][coloana] == a && matrix[linie][coloana + 3] == a)
			{
				matrix[linie][coloana] = g;
				matrix[linie][coloana + 1] = g;
				matrix[linie][coloana + 2] = g;
				matrix[linie][coloana + 3] = g;
			}
			break;
		}
		}
	}





	//MAX GREEN PIPES ----> CAN HAVE PLANTS, COINS OR NOTHING. 
	for (i = 1; i <= maxGP; i++)
	{

		do
		{
			coloana = 40 + rand() % 116;		//intre 40 si 155

		} while (matrix[8][coloana] != a &&
			matrix[8][coloana + 1] != a &&
			matrix[7][coloana] != a &&
			matrix[7][coloana + 1] != a &&
			matrix[6][coloana] != a &&
			matrix[6][coloana + 1] != a &&
			matrix[8][coloana - 1] != a &&
			matrix[8][coloana + 2] != a &&
			matrix[7][coloana - 1] != a &&
			matrix[7][coloana + 2] != a &&
			matrix[6][coloana - 1] != a &&
			matrix[6][coloana + 2] != a &&
			matrix[5][coloana - 1] != a &&
			matrix[5][coloana] != a &&
			matrix[5][coloana + 1] != a &&
			matrix[5][coloana + 1] != a);


		int okGP = rand() % 2;

		switch (okGP)
		{
		case 0:												// din 4 bucati
		{
			matrix[8][coloana] = p3;
			matrix[8][coloana + 1] = p4;
			matrix[7][coloana] = p1;						//		p1 p2
			matrix[7][coloana + 1] = p2;						//		p3 p4
			int okPlantOrCoin = rand() % 3;					//
			switch (okPlantOrCoin)
			{
			case 1:
			{
				matrix[6][coloana] = EPl;				//	EPL EPR
				matrix[6][coloana + 1] = EPr;				//	p1 p2
				break;									//	p3 p4
			}

			case 2:
			{
				matrix[6][coloana] = C;
				matrix[6][coloana + 1] = C;
				maxCoins = maxCoins - 2;
				break;
			}
			}

			break;

		}

		case 1:												//din 6 bucati
		{
			if (matrix[5][coloana] == a && matrix[5][coloana + 1] == a && matrix[5][coloana - 1] == a && matrix[5][coloana + 2] == a && matrix[4][coloana] == a && matrix[4][coloana + 1] == a && matrix[4][coloana - 1] == a && matrix[4][coloana + 2] == a)
			{


				matrix[8][coloana] = p3;
				matrix[8][coloana + 1] = p4;
				matrix[7][coloana] = p3;
				matrix[7][coloana + 1] = p4;
				matrix[6][coloana] = p1;
				matrix[6][coloana + 1] = p2;

				int okPlantOrCoin = rand() % 3;
				switch (okPlantOrCoin)
				{
				case 1:
				{
					matrix[5][coloana] = EPl;
					matrix[5][coloana + 1] = EPr;
					break;
				}

				case 2:
				{
					matrix[5][coloana] = C;							// C C
					matrix[5][coloana + 1] = C;						//p1 p2
					maxCoins = maxCoins - 2;							//p3 p4
					break;											//p3 p4
				}
				}
			}


			break;
		}
		}
	}


	//COINS

	for (i = 1; i <= maxCoins; i++)
	{
		do
		{
			linie = 4 + rand() % 4;
			coloana = 5 + rand() % 164;
		} while (matrix[linie][coloana] != a);

		int OK = rand() % 3;

		switch (OK)
		{

		case 1:
		{

			if ((matrix[linie + 1][coloana - 1] == b || matrix[linie + 1][coloana] == b || matrix[linie + 1][coloana + 1] == b) && matrix[linie - 1][coloana] == a && matrix[linie - 2][coloana] == a)
			{
				matrix[linie][coloana] = C;										//C
				matrix[linie - 1][coloana] = C;									//C
				matrix[linie - 2][coloana] = C;									//C
				maxCoins = maxCoins - 2;

			}
			break;
		}

		case 2:
		{
			matrix[linie][coloana] = C;											//C
			break;
		}

		}


	}


	for (i = 1; i <= maxGoomba; i++)
	{
		do
		{
			linie = 1 + rand() % 8;
			coloana = 15 + rand() % 140;

		} while (matrix[linie][coloana] != a && matrix[linie][coloana + 1] != a && matrix[linie][coloana - 1] != a &&
			((matrix[linie - 1][coloana] == b && matrix[linie - 1][coloana - 1] == b && matrix[linie - 1][coloana + 1] == b) || (matrix[linie - 1][coloana] == g && matrix[linie - 1][coloana - 1] == g && matrix[linie - 1][coloana + 1] == g)));

		int OKgoomba = rand() % 3;
		switch (OKgoomba)
		{
		case 0:
		{
			matrix[linie][coloana] = G;			//spawneaza pe pamant/brick, NEAPARAT IMEDIAT deasupra acestora.
			break;
		}

		case 1:
		{
			do
			{
				linie = 1 + rand() % 8;
				coloana = 5 + rand() % 155;

			} while (matrix[linie][coloana] != a && (matrix[linie + 1][coloana] != b || matrix[linie + 1][coloana] != b));
			matrix[linie][coloana] = G;
			break;

		}

		case 2:
		{
			do
			{
				linie = 1 + rand() % 8;
				coloana = 5 + rand() % 155;
			} while (matrix[linie][coloana] != a && matrix[linie + 1][coloana] != a && matrix[linie + 2][coloana] != b && matrix[linie + 2][coloana - 1] != b && matrix[linie + 3][coloana - 1] != b);

			matrix[linie][coloana] = G;

			break;
		}


		}


	}



	//SCARI + HOLE + END
	int OKhole = 0;
	int tries = 70;

	do
	{
		tries--;
		OKhole = 1;
		coloana = rand() % 130 + 10;

		for (i = 3; i <= 8; i++)
		{
			for (j = coloana; j <= coloana + 10; j++)
			{
				if (i == 6)
					if ((j == coloana + 10) || (j == coloana))
						continue;

				if (i == 5)
					if ((j < coloana + 2) || (j > coloana + 8))
						continue;

				if (i == 4)
					if ((j < coloana + 3) || (j > coloana + 7))
						continue;

				if (i == 3)
					if ((j < coloana + 4) || (j > coloana + 6))
						continue;

				if (matrix[i][j] != a)
				{
					OKhole = 0;
					break;
				}
			}

			if (OKhole == 0 && tries <0)
				break;
		}

	} while (OKhole != 1);


	matrix[8][coloana] = k;
	matrix[8][coloana + 1] = k;
	matrix[8][coloana + 2] = k;
	matrix[7][coloana + 1] = k;
	matrix[7][coloana + 2] = k;
	matrix[6][coloana + 2] = k;
	matrix[8][coloana + 6] = k;
	matrix[8][coloana + 7] = k;
	matrix[8][coloana + 8] = k;
	matrix[7][coloana + 6] = k;
	matrix[7][coloana + 7] = k;
	matrix[6][coloana + 6] = k;

	matrix[9][coloana + 3] = a;
	matrix[9][coloana + 4] = a;
	matrix[9][coloana + 5] = a;
	matrix[10][coloana + 3] = a;
	matrix[10][coloana + 4] = a;
	matrix[10][coloana + 5] = a;
	// END SCARI + HOLE + SCARI


	//CROWNS
	for (i = 1; i <= maxCrown; i++)
	{
		do
		{
			linie = rand() % 2 + 5;
			coloana = rand() % 110 + 20;
		} while (matrix[linie][coloana] != a && matrix[linie + 1][coloana] != a && matrix[linie + 1][coloana + 1] != a && matrix[linie + 1][coloana - 1] != a &&
			matrix[linie][coloana] != a);

		if (linie == 5)
			if ((matrix[linie + 3][coloana - 1] == a || matrix[linie + 3][coloana - 1] == G) && (matrix[linie + 3][coloana] == a || matrix[linie + 3][coloana] == G) && (matrix[linie + 3][coloana + 1] == a || matrix[linie + 3][coloana + 1] == G))
			{
				matrix[linie + 3][coloana - 1] = g;
				matrix[linie + 3][coloana] = g;
				matrix[linie + 3][coloana + 1] = g;
			}

		matrix[linie][coloana] = qF;

	}


	// INVISIBLE MUSHROOM



	for (i = 1; i <= maxOneup; i++)
	{
		do
		{
			linie = rand() % 2 + 5;
			coloana = rand() % 110 + 20;
		} while (matrix[linie][coloana] != a && matrix[linie + 1][coloana] != a && matrix[linie + 1][coloana + 1] != a && matrix[linie + 1][coloana - 1] != a &&
			matrix[linie][coloana] != a);

		if (linie == 5)
			if ((matrix[linie + 3][coloana - 1] == a || matrix[linie + 3][coloana - 1] == G) && (matrix[linie + 3][coloana] == a || matrix[linie + 3][coloana] == G) && (matrix[linie + 3][coloana + 1] == a || matrix[linie + 3][coloana + 1] == G))
			{
				matrix[linie + 3][coloana - 1] = e;
				matrix[linie + 3][coloana] = e;
				matrix[linie + 3][coloana + 1] = e;
			}

		matrix[linie][coloana] = L;

	}































	matrix[8][163] = fl; // endgame flag
	matrix[8][164] = fr;
	matrix[7][164] = P1;
	matrix[6][164] = P2;
	matrix[5][164] = P3;
	matrix[6][100] = a;

	matrix[6][5] = qF;
	matrix[3][3] = M; //Mario


}

void loader::loadCurrentLevel(int level)
{
	if (level == 1)
	{

		int currentLevel[ROWS][COLS] =
		{

			{ r ,r ,r ,r ,r ,r ,r ,r ,r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, }, //r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r},
			{ r ,a ,a ,a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, }, //a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, r},
			{ r ,a ,c ,a, a, a, a, a, a, e, e, e, a, e, e, a, a, a, e, a, a, a, a, b, b, b, c, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, C, a, a, a, a, a, a, a, c, a, a, a, C, C, C, a, a, a, a, a, a, a, a, a, a, C, C, C, C, a, c, a, a, a, c, a, a, a, a, a, a, c, a, a, a, qF, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, c, C, a, a, a, a, a, a, a, a, qC, a, a, a, a, C, C, C, a, a, a, a, a, a, a, c, a, a, a, a, },// c, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, r},
			{ r ,a ,a ,M, a, a, a, c, a, e, a, a, a, e, a, e, a, e, a, e, a, a, a, b, a, a, a, b, a, a, a, b, a, a, a, a, qC, a, a, a, a, a, a, a, C, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, L, a, a, a, a, C, C, C, C, a, a, a, a, a, a, a, a, a, a, c, a, C, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, C, a, a, a, a, c, a, a, a, a, a, a, a, a, C, C, C, a, a, a, a, c, a, a, a, a, a, a, a, },//a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, r},
			{ r ,a ,a ,a, a, a, a, a, a, e, e, a, a, e, e, a, a, e, e, e, a, a, a, b, a, a, b, b, b, a, b, b, b, a, a, a, a, a, a, a, b, b, a, a, a, C, a, a, a, a, a, a, a, a, a, e, e, e, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, b, e, b, e, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, G, G, a, a, a, a, a, a, a, a, a, a, g, a, C, a, a, a, a, a, a, a, a, a, a, qF, a, a, a, a, a, a, a, a, a, a, a, a, C, a, a, a,a, a, a, a, a, a,a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, },// a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, r},
			{ r ,a ,a ,a, a, a, a, a, a, e, a, a, a, e, a, e, a, e, a, e, a, a, a, b, a, a, a, b, a, a, a, b, a, a, a, a, a, a, a, a, a, a, a, a, a, a, C, a, a, a, a, a, a, a, a, a, a, a, a, a, a, L, a, a, a, a, a, a, qC, b, qC, b, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, g, g, g, a, a, a, a, a, a, a, a, a, a, a, b, b, b, b, a, a, a, EPl, EPr, a, a, a, a, a, a, a, C, a, a, a, a, a, a, a, a, a, a, a,a, a, EPl, EPr, a, a, a, a, a, C, a, a,a, a,a, a, a, b, e, b, a, a, a, a, g, g, g, a, a, a, a, a, a, a, a, P3, a, a,a, a, a, },// a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, r},
			{ r ,a ,a ,a, a, a, a, a, a, e, e, e, a, e, e, a, a, e, a, e, a, qC, a, b, b, b, a, a, a, qC, a, a, a, a, a, a, b, qC, b, a, a, a, a, a, a, a, a, a, a, a, a, a, e, e, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p1, p2, a, a, a, a, a, a, a, a, a, g, g, g, a, a, a, a, a, a, a, e, qC, e, a, a, a, a, a, a, a, a, a, a, p1, p2, a, a, g, a, a, a, a, C, a, a, a, a, a, a, a, C, C, C, a, a, a, p1, p2, a, a, a, a, a, C, k, a, a, a, k, k, a, a, a, a, a, a, a, g, B, B, B, g, a, EPl, EPr, a, a, a, a, P2, a, a, a, a, a, },// a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, r},
			{ r ,a ,a ,a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p1, p2, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, fT, a, a, a, g, g, g, g, a, a, a, p3, p4, a, a, a, C, k, k, k, a, a, a, a, a, a, a, a, a, a, a, C, a, a, a, a, a, a, p1, p2, a, a, a, a, P1, a, a, a, a, a, },// a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, r},
			{ r ,a ,a ,a, a, a, a, a, a, a, a, a, a, a, C, C, C, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, G, a, a, a, a, a, a, a, a, a, G, a, p3, p4, a, a, a, G, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, G, a, G, fB, a, g, g, B, B, B, B, a, a, a, p3, p4, a, a, a, k, k, k, k, a, a, a, a, a, a, a, a, a, a, G, C, a, a, a, a, a, a, p3, p4, a, a,a, fl, fr, a, a, a, a, a, },// a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, r},
			{ g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, a, a, a, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, a, a, a, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, },// g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g},
			{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, a, a, a, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, a, a, B, B, B, a, a, a, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, },// B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
			{ d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, }// d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d}


		};

		int enemyRecorder;
		int x = 0;
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				map[j][i] = currentLevel[i][j];

				
				if (map[j][i] == EPl)
				{
					enemyRecorder = misc.findFreeSprite();
					piranhaPlants[x].id = enemyRecorder;
					

					piranhaPlants[x].ReferenceJ = j;
					piranhaPlants[x].ReferenceI = i;
					dbSprite(piranhaPlants[x].id, 100, 100, EPl);
					dbHideSprite(piranhaPlants[x].id);
					piranhaPlants[x].typeOf = map[j][i];//left side or right side
					piranhaPlants[x].isAlive = true;
					x++;
				}
				else if (map[j][i] == EPr)
				{
					enemyRecorder = misc.findFreeSprite();
					piranhaPlants[x].id = enemyRecorder;
					

					piranhaPlants[x].ReferenceJ = j;
					piranhaPlants[x].ReferenceI = i;
					dbSprite(piranhaPlants[x].id, 100, 100, EPr);
					dbHideSprite(piranhaPlants[x].id);
					piranhaPlants[x].typeOf = map[j][i];//left side or right side
					piranhaPlants[x].isAlive = true;
					x++;
				}
			}
		}
	}
	else
	{

		loadGenerator();


		int enemyRecorder;
		int x = 0;
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				map[j][i] = matrix[i][j];

				//store left piranha as a reference to check distances later
				if (map[j][i] == EPl)
				{
					enemyRecorder = misc.findFreeSprite();
					piranhaPlants[x].id = enemyRecorder;
					//so we know exactly which plant we are handling in the map
					piranhaPlants[x].ReferenceJ = j;
					piranhaPlants[x].ReferenceI = i;
					dbSprite(piranhaPlants[x].id, 100, 100, EPl);
					dbHideSprite(piranhaPlants[x].id);
					piranhaPlants[x].typeOf = map[j][i];//left side or right side
					piranhaPlants[x].isAlive = true;
					x++;
				}
				else if (map[j][i] == EPr)
				{
					enemyRecorder = misc.findFreeSprite();
					piranhaPlants[x].id = enemyRecorder;
					//so we know exactly which plant we are handling in the map
					piranhaPlants[x].ReferenceJ = j;
					piranhaPlants[x].ReferenceI = i;
					dbSprite(piranhaPlants[x].id, 100, 100, EPr);
					dbHideSprite(piranhaPlants[x].id);
					piranhaPlants[x].typeOf = map[j][i];//left side or right side
					piranhaPlants[x].isAlive = true;
					x++;
				}
			}
		}


	}


}
		
}

void loader::loadImages()
{


	// load mario
	dbLoadImage("mario//still.png", mario, 1);
	dbLoadImage("mario//walk.png", marioWalk, 1);
	dbLoadImage("mario//jump.png", marioJump, 1);
	dbLoadImage("mario//stillPrincess.png", PrincessStill, 1);
	dbLoadImage("mario//walkPrincess.png", PrincessWalk, 1);
	dbLoadImage("mario//JumpPrincess.png", PrincessJump, 1);



	//load environmnet tiles
	dbLoadImage("environment//Physics//Brick.png", b);		//b = brick. walkable. near question boxes
	dbLoadImage("environment//airTile.png", a);				//a = air tile
	dbLoadImage("environment//airTile.png", r);				//r = restriction / limita de sus. becomes air tile,dar nu poate sari peste ea sau in ea.
	dbLoadImage("environment//airTile.png", d);				//d = death. cade in groapa, atinge d ---> death
	dbLoadImage("environment//airTile.png", L);				//hidden 1up BOX. daca o loveste de jos, da green mushroom



	dbLoadImage("environment//cloud.png", c);							//c = cloud
	dbLoadImage("environment//Physics//GroundTop.png", g);				//limita de jos. GROUND TOP
	dbLoadImage("environment//Physics//GroundBottom.png", B);			// tot limita de jos. dar GROUND BOTTOM
	dbLoadImage("environment//PipeULeft.png", p1);
	dbLoadImage("environment//PipeURight.png", p2);
	dbLoadImage("environment//PipeDleft.png", p3);						// pipe. formata din 4 bucati.
	dbLoadImage("environment//PipeDright.png", p4);



	//load question blocks and anims
	dbLoadImage("environment//Blocks//Question block frames//Question block001.png", q);
	dbLoadImage("environment//Blocks//Question block frames//Question block003.png", q + 1);
	dbLoadImage("environment//Blocks//Question block frames//Question block005.png", q + 2);
	dbLoadImage("environment//Blocks//Question block frames//Question block007.png", q + 3);
	dbLoadImage("environment//Blocks//Question block frames//Question block009.png", q + 4);
	dbLoadImage("environment//Blocks//Question block frames//Question block011.png", q + 5);
	dbLoadImage("environment//Blocks//Question block frames//Question block013.png", q + 6);
	dbLoadImage("environment//Blocks//Question block frames//Question block015.png", q + 7);
	dbLoadImage("environment//Blocks//Question block frames//Question block017.png", q + 8);
	dbLoadImage("environment//Blocks//Question block frames//Question block019.png", q + 9);
	dbLoadImage("environment//Blocks//Question block frames//Question block021.png", q + 10);
	dbLoadImage("environment//Blocks//Question block frames//Question block023.png", q + 11);
	dbLoadImage("environment//Blocks//Question block frames//Question block025.png", q + 12);					//sprite-urile pt Question Block
	dbLoadImage("environment//Blocks//Question block frames//Question block027.png", q + 13);
	dbLoadImage("environment//Blocks//Question block frames//Question block029.png", q + 14);
	dbLoadImage("environment//Blocks//Question block frames//Question block031.png", q + 15);
	dbLoadImage("environment//Blocks//Question block frames//Question block033.png", q + 16);
	dbLoadImage("environment//Blocks//Question block frames//Question block035.png", q + 17);
	dbLoadImage("environment//Blocks//Question block frames//Question block037.png", q + 18);
	dbLoadImage("environment//Blocks//Question block frames//Question block039.png", q + 19);
	dbLoadImage("environment//Blocks//Question block frames//Question block041.png", q + 20);
	dbLoadImage("environment//Blocks//Question block frames//Question block043.png", q + 21);
	dbLoadImage("environment//Blocks//Question block frames//Question block045.png", q + 22);
	dbLoadImage("environment//Blocks//Question block frames//Question block047.png", q + 23);
	dbLoadImage("environment//Blocks//Question block frames//Question block049.png", q + 24);
	dbLoadImage("environment//Blocks//Question block frames//Question block051.png", q + 25);
	dbLoadImage("environment//Blocks//Question block frames//Question block053.png", q + 26);



	dbLoadImage("environment//Blocks//solid block.png", k);							//alte tipuri de blocks. pur decorative. nu vrem Bricks peste tot nu???
	dbLoadImage("environment//Blocks//empty block.png", e);



	dbLoadImage("environment//Flag pole//FlagBottomRight.png", fr);				//bucatile din flag-ul de la final. flag reached = end level.
	dbLoadImage("environment//Flag pole//FlagBottomLeft.png", fl);
	dbLoadImage("environment//Flag pole//pole1.png", P1);
	dbLoadImage("environment//Flag pole//pole2.png", P2);
	dbLoadImage("environment//Flag pole//pole3.png", P3);
	dbLoadImage("environment//Flag pole//pole4.png", P4);
	dbLoadImage("environment//Flag pole//pole5.png", P5);
	dbLoadImage("environment//Flag pole//pole5Left.png", P5l);
	dbLoadImage("environment//Flag pole//pole6.png", P6);
	dbLoadImage("environment//Flag pole//midwayFlagBottom.png", fB);
	dbLoadImage("environment//Flag pole//midwayFlagTop.png", fT);



	//load coin and anims
	dbLoadImage("environment//Rewards//coin001.png", C);
	dbLoadImage("environment//Rewards//coin002.png", C + 1);
	dbLoadImage("environment//Rewards//coin003.png", C + 2);
	dbLoadImage("environment//Rewards//coin004.png", C + 3);
	dbLoadImage("environment//Rewards//coin005.png", C + 4);
	dbLoadImage("environment//Rewards//coin006.png", C + 5);
	dbLoadImage("environment//Rewards//coin001.png", C + 6);

	//load crown and anims
	dbLoadImage("environment//Rewards//Crown1.png", f);
	dbLoadImage("environment//Rewards//Crown2.png", f + 1);
	dbLoadImage("environment//Rewards//Crown3.png", f + 2);
	dbLoadImage("environment//Rewards//Crown4.png", f + 3);
	dbLoadImage("environment//Rewards//Crown5.png", f + 4);
	dbLoadImage("environment//Rewards//Crown6.png", f + 5);
	dbLoadImage("environment//Rewards//Crown7.png", f + 6);
	dbLoadImage("environment//Rewards//Crown8.png", f + 7);
	dbLoadImage("environment//Rewards//Crown9.png", f + 8);
	dbLoadImage("environment//Rewards//Crown10.png", f + 9);
	dbLoadImage("environment//Rewards//Crown11.png", f + 10);
	dbLoadImage("environment//Rewards//Crown12.png", f + 11);



	//load score images 100
	dbLoadImage("environment//score//100_1.png", score100_1);
	dbLoadImage("environment//score//100_2.png", score100_1 + 1);
	dbLoadImage("environment//score//100_3.png", score100_1 + 2);
	dbLoadImage("environment//score//100_4.png", score100_1 + 3);
	dbLoadImage("environment//score//100_5.png", score100_1 + 4);
	dbLoadImage("environment//score//100_6.png", score100_1 + 5);
	dbLoadImage("environment//score//100_7.png", score100_1 + 6);
	dbLoadImage("environment//score//100_8.png", score100_1 + 7);
	dbLoadImage("environment//score//100_9.png", score100_1 + 8);


	//load score images 200
	dbLoadImage("environment//score//200_1.png", score200_1);
	dbLoadImage("environment//score//200_2.png", score200_1 + 1);
	dbLoadImage("environment//score//200_3.png", score200_1 + 2);
	dbLoadImage("environment//score//200_4.png", score200_1 + 3);
	dbLoadImage("environment//score//200_5.png", score200_1 + 4);
	dbLoadImage("environment//score//200_6.png", score200_1 + 5);
	dbLoadImage("environment//score//200_7.png", score200_1 + 6);
	dbLoadImage("environment//score//200_8.png", score200_1 + 7);
	dbLoadImage("environment//score//200_9.png", score200_1 + 8);
	dbLoadImage("environment//score//200_10.png", score200_1 + 9);
	dbLoadImage("environment//score//200_11.png", score200_1 + 10);


	// load score 1000
	dbLoadImage("environment//score//1000_1.png", score1000_1);
	dbLoadImage("environment//score//1000_2.png", score1000_1 + 1);
	dbLoadImage("environment//score//1000_3.png", score1000_1 + 2);
	dbLoadImage("environment//score//1000_4.png", score1000_1 + 3);
	dbLoadImage("environment//score//1000_5.png", score1000_1 + 4);
	dbLoadImage("environment//score//1000_6.png", score1000_1 + 5);
	dbLoadImage("environment//score//1000_7.png", score1000_1 + 6);
	dbLoadImage("environment//score//1000_8.png", score1000_1 + 7);
	dbLoadImage("environment//score//1000_9.png", score1000_1 + 8);
	dbLoadImage("environment//score//1000_10.png", score1000_1 + 9);
	dbLoadImage("environment//score//1000_11.png", score1000_1 + 10);


	// loads checkpoint anim
	dbLoadImage("environment//score//check_1.png", check_1);
	dbLoadImage("environment//score//check_2.png", check_1 + 1);
	dbLoadImage("environment//score//check_3.png", check_1 + 2);
	dbLoadImage("environment//score//check_4.png", check_1 + 3);
	dbLoadImage("environment//score//check_5.png", check_1 + 4);
	dbLoadImage("environment//score//check_6.png", check_1 + 5);
	dbLoadImage("environment//score//check_7.png", check_1 + 6);
	dbLoadImage("environment//score//check_8.png", check_1 + 7);

	//load dust animations
	dbLoadImage("environment//Blocks//Dust//dust1.png", dust_1);
	dbLoadImage("environment//Blocks//Dust//dust2.png", dust_1 + 1);
	dbLoadImage("environment//Blocks//Dust//dust3.png", dust_1 + 2);
	dbLoadImage("environment//Blocks//Dust//dust4.png", dust_1 + 3);
	dbLoadImage("environment//Blocks//Dust//dust5.png", dust_1 + 4);
	dbLoadImage("environment//Blocks//Dust//dust6.png", dust_1 + 5);
	dbLoadImage("environment//Blocks//Dust//dust7.png", dust_1 + 6);
	dbLoadImage("environment//Blocks//Dust//dust8.png", dust_1 + 7);
	dbLoadImage("environment//Blocks//Dust//dust9.png", dust_1 + 8);

	//load  1up going up anims. for gM = green mushroom
	dbLoadImage("environment//1up//1up_1.png", _1up_1);
	dbLoadImage("environment//1up//1up_2.png", _1up_1 + 1);
	dbLoadImage("environment//1up//1up_3.png", _1up_1 + 2);
	dbLoadImage("environment//1up//1up_4.png", _1up_1 + 3);
	dbLoadImage("environment//1up//1up_5.png", _1up_1 + 4);
	dbLoadImage("environment//1up//1up_6.png", _1up_1 + 5);
	dbLoadImage("environment//1up//1up_7.png", _1up_1 + 6);
	dbLoadImage("environment//1up//1up_8.png", _1up_1 + 7);
	dbLoadImage("environment//1up//1up_9.png", _1up_1 + 8);
	dbLoadImage("environment//1up//1up_10.png", _1up_1 + 9);
	dbLoadImage("environment//1up//1up_11.png", _1up_1 + 10);
	dbLoadImage("environment//1up//1up_12.png", _1up_1 + 11);
	dbLoadImage("environment//1up//1up_13.png", _1up_1 + 12);
	dbLoadImage("environment//1up//1up_14.png", _1up_1 + 13);
	dbLoadImage("environment//1up//1up_15.png", _1up_1 + 14);
	dbLoadImage("environment//1up//1up_16.png", _1up_1 + 15);
	dbLoadImage("environment//1up//1up_17.png", _1up_1 + 16);



	//load 1up TEXT anims
	dbLoadImage("environment//1up//1upText_1.png", _1upText_1);
	dbLoadImage("environment//1up//1upText_2.png", _1upText_1 + 1);
	dbLoadImage("environment//1up//1upText_3.png", _1upText_1 + 2);
	dbLoadImage("environment//1up//1upText_4.png", _1upText_1 + 3);
	dbLoadImage("environment//1up//1upText_5.png", _1upText_1 + 4);
	dbLoadImage("environment//1up//1upText_6.png", _1upText_1 + 5);
	dbLoadImage("environment//1up//1upText_7.png", _1upText_1 + 6);





																						//ENEMY SPRITES



	//Plant left tile
	dbLoadImage("Enemies//plantL1.png", EPl);
	dbLoadImage("Enemies//plantL2.png", EPl + 1);
	dbLoadImage("Enemies//plantL3.png", EPl + 2);
	dbLoadImage("Enemies//plantL4.png", EPl + 3);
	dbLoadImage("Enemies//plantL5.png", EPl + 4);
	dbLoadImage("Enemies//plantL6.png", EPl + 5);
	dbLoadImage("Enemies//plantL7.png", EPl + 6);
	dbLoadImage("Enemies//plantL8.png", EPl + 7);
	dbLoadImage("Enemies//plantL9.png", EPl + 8);
	dbLoadImage("Enemies//plantL10.png", EPl + 9);
	dbLoadImage("Enemies//plantL11.png", EPl + 10);
	dbLoadImage("Enemies//plantL12.png", EPl + 11);
	dbLoadImage("Enemies//plantL12x1.png", EPl + 12);
	dbLoadImage("Enemies//plantL12x2.png", EPl + 13);
	dbLoadImage("Enemies//plantL12x3.png", EPl + 14);
	dbLoadImage("Enemies//plantL12x4.png", EPl + 15);
	dbLoadImage("Enemies//plantL12x5.png", EPl + 16);
	dbLoadImage("Enemies//plantL12x6.png", EPl + 17);
	dbLoadImage("Enemies//plantL12x7.png", EPl + 18);
	dbLoadImage("Enemies//plantL12x8.png", EPl + 19);
	dbLoadImage("Enemies//plantL12x9.png", EPl + 20);
	dbLoadImage("Enemies//plantL13.png", EPl + 21);
	dbLoadImage("Enemies//plantL14.png", EPl + 22);
	dbLoadImage("Enemies//plantL15.png", EPl + 23);
	dbLoadImage("Enemies//plantL16.png", EPl + 24);
	dbLoadImage("Enemies//plantL17.png", EPl + 25);
	dbLoadImage("Enemies//plantL18.png", EPl + 26);
	dbLoadImage("Enemies//plantL19.png", EPl + 27);
	dbLoadImage("Enemies//plantL20.png", EPl + 28);
	dbLoadImage("Enemies//plantL21.png", EPl + 29);
	dbLoadImage("Enemies//plantL22.png", EPl + 30);

	//Plant right tiles
	dbLoadImage("Enemies//plantR1.png", EPr);
	dbLoadImage("Enemies//plantR2.png", EPr + 1);
	dbLoadImage("Enemies//plantR3.png", EPr + 2);
	dbLoadImage("Enemies//plantR4.png", EPr + 3);
	dbLoadImage("Enemies//plantR5.png", EPr + 4);
	dbLoadImage("Enemies//plantR6.png", EPr + 5);
	dbLoadImage("Enemies//plantR7.png", EPr + 6);
	dbLoadImage("Enemies//plantR8.png", EPr + 7);
	dbLoadImage("Enemies//plantR9.png", EPr + 8);
	dbLoadImage("Enemies//plantR10.png", EPr + 9);
	dbLoadImage("Enemies//plantR11.png", EPr + 10);
	dbLoadImage("Enemies//plantR12.png", EPr + 11);
	dbLoadImage("Enemies//plantR12x1.png", EPr + 12);
	dbLoadImage("Enemies//plantR12x2.png", EPr + 13);
	dbLoadImage("Enemies//plantR12x3.png", EPr + 14);
	dbLoadImage("Enemies//plantR12x4.png", EPr + 15);
	dbLoadImage("Enemies//plantR12x5.png", EPr + 16);
	dbLoadImage("Enemies//plantR12x6.png", EPr + 17);
	dbLoadImage("Enemies//plantR12x7.png", EPr + 18);
	dbLoadImage("Enemies//plantR12x8.png", EPr + 19);
	dbLoadImage("Enemies//plantR12x9.png", EPr + 20);
	dbLoadImage("Enemies//plantR13.png", EPr + 21);
	dbLoadImage("Enemies//plantR14.png", EPr + 22);
	dbLoadImage("Enemies//plantR15.png", EPr + 23);
	dbLoadImage("Enemies//plantR16.png", EPr + 24);
	dbLoadImage("Enemies//plantR17.png", EPr + 25);
	dbLoadImage("Enemies//plantR18.png", EPr + 26);
	dbLoadImage("Enemies//plantR19.png", EPr + 27);
	dbLoadImage("Enemies//plantR20.png", EPr + 28);
	dbLoadImage("Enemies//plantR21.png", EPr + 29);
	dbLoadImage("Enemies//plantR22.png", EPr + 30);
	// goomba/walkers 
	dbLoadImage("Enemies//Goomba//goomba1.png", G);
	dbLoadImage("Enemies//Goomba//goomba2.png", G + 1);
	dbLoadImage("Enemies//Goomba//goomba3.png", G + 2);
	dbLoadImage("Enemies//Goomba//goomba4.png", G + 3);
	dbLoadImage("Enemies//Goomba//goomba5.png", G + 4);
	dbLoadImage("Enemies//Goomba//goomba6.png", G + 5);
	dbLoadImage("Enemies//Goomba//goomba7.png", G + 6);
	dbLoadImage("Enemies//Goomba//GoombaDeath1.png", G + 7);
}