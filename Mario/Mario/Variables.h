#pragma once

class variables
{
public:
};

#define normalMario 1
#define FireMario 2
#define bottom 1 //utilizat sa defineasca tipul de coloziune
#define top 2
#define M 0 //unde se va gasi M pe harta, acolo va aparea Mario (nu pot fi doi M pe harta)
//Oricare alt M de pe harta se va transforma in Air Tiles
#define a 1 //air tile
//tiles cu valoare peste 10 sunt utilizate pentru coliziune (poti trece prin ele)
#define r 10 //restriction tile
#define g 11 //ground tile TOP
#define B 12 //ground tile Bottom
#define p1 13 //pipe tile top right
#define p2 14 //pipe tile top left
#define p3 15 //pipe tile bottom right
#define p4 16 //pipe tile bottom left
//tiles cu valoare peste 20 sunt utilizate pentru coliziune sau interactiune, exemplu, "?" sau inamici
#define b 20 //brick tile
//over 100 because we dont want collision to push away mario
#define fr 150
#define fl 151
#define P1 152
#define P2 153
#define P3 154
#define P4 155
#define P5 156
#define P5l 157
#define P6 158
#define q 40 //question brick ("?") (animatiile astea merg de la 47 la 60)
#define qC 32 // q coins 
#define qF 33 // q flower 
#define e 34 // empty block, in ce se transforma blocul cu "?"
#define k 35 // alte blocuri
#define d 70 //d de la death, verifica daca Mario a cazut in una din gaurile din harta
#define c 9 //clouds
#define L 99 // utilizat pentru 1up
#define C 100 //coins
#define SA 105 //special tileset based anim
#define f 300  // utilizat pentru "fireFlower12" pentru animatie
#define fB 115 // utilizat pentru checkpoint flag bottom
#define fT 116 // utilizat pentru checkpoint flag top
#define gM 117 // green mushroom
#define maxAnimations 20 // limiteaza nr maxim de animatii speciale gen coin-urile de deasupra "q"

//Inamicii
#define EPl 170 // planta inamica LEFT (pentru ca foloseste doua tiles) 30 imagini
#define EPr 200 // planta inamica RIGHT
#define maxPiranhas 10 // limiteaza nr maxim de flori din harta
#define maxWalkers 30 // limiteaza nr maxim de walkers din harta
#define G 230 //walkers GOOMBA
#define GOOMBA 1
#define LEFT 1 //utilizat sa schimbe directia inamicilor
#define RIGHT 2//bazat pe coliziune


typedef struct piranhaAI
{
	int id;//sprite id
	int typeOf; //jumatate st sau dr
	bool tooClose; //daca = 1, nu se mai ridica
	bool isAlive; 
	int plantTimer; //plants animation speed

	int plantLoopTimer; //how long it waits until it comes back up again
	int plantAnim; 
	
	
	int distance;  
	int ReferenceJ;
	int ReferenceI;

} piranhaAI;




typedef struct extraAnimations
{
	bool busy; 
	int SetImage;
	int frames; 
	int timer;
	int id;
	int typeOf; 
				
	int y;
	int x;
	int HighestFrame; 
					 
	int OriginalMapX;
	int FinalFrame;
	int animDelay; 
} extraAnimations;



piranhaAI piranhaPlants[maxPiranhas * 2];

extraAnimations anims[maxAnimations];




