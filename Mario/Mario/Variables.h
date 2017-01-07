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

//se ocupa de lucruri precum coins de deasupra "?" sau floarea(coroana) de deasupra casutei "?"
// struct este folosit pentru ca s-ar putea sa fie nevoie de mai multe animatii
typedef struct extraAnimations
{
	bool busy; // se intampla ceva in elementul curent? daca da, treci la urmatorul
	int SetImage; //utilizat sa decida care imagine urmeaza, de exemplu 100 score, 200 score
	int frames; //ID-ul imaginii din sprite
	int timer; //ID-ul sprite-ului
	int id; // utilizat sa stocheze elementele 1d si 2d
	int typeOf; // utilizat sa decida daca animatia face parte dintr-un sprite sau imagine
				//y si x sunt utilizate pentru animatiile sprite-ului
	int y;
	int x;
	int HighestFrame; //pentru ca animatiile au diferite limite de marime
					  //utilizat ca sa calculeze distanta din timpul in care Mario a inceput animatia
					  //si unde a mers/ajuns, asta ne ajuta sa mentinem animatia in locul corect, chiar si dupa ce se misca mapX
	int OriginalMapX;
	int FinalFrame; //utilizat pentru animatii care necesita o schimbare dupa, precum 1up mashroom
	int animDelay; //utilizat pentru delay-ul animatiilor pentru fiecare imagine
} extraAnimations;

//utilizat pentru toate actiunile plantei
typedef struct piranhaAI
{
	int id;//id-ul imaginii si sprite-ului
	int typeOf; //utilizat sa decida care jumatate este, right or left
	bool tooClose; //daca da, planta trebuie sa se opreasca din a creste
	bool isAlive; // decide daca planta este in viata sau nu
	int plantTimer; //se ocupa de viteza animatiei pentru planta
	int plantLoopTimer; //cat timp asteapta pana va iesi din nou
	int plantAnim; //stocheaza animatia curenta a plantei
	int distance;  //cat de departe este planta de Mario
				   //aceste variabile ajuta sa aflam exact unde pe map[][]
				   //sunt plantele localizate, astfel putem afla care planta este numita pe harta de fapt
				   //si sa utilizam animatia si sprite-ul corespunzator
				   //pe scurt, ajuta planta sa functioneze independent, de exemplu se pot gasi animatii diferite in flori diferite
	int ReferenceJ;
	int ReferenceI;

} piranhaAI;


piranhaAI piranhaPlants[maxPiranhas * 2]; //pentru ca fiecare stocheaza o planta, de exemplu partea left sau right

extraAnimations anims[maxAnimations]; //ruleaza pana la X animatii in acelasi timp

