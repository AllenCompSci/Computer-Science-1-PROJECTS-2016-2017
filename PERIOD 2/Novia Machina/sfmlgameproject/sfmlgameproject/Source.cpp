/*
THINGS TO CONSIDER (consider the following. haha bill nye)

~NEW STUFF~
(its new becasue its got tildes)
-so uh. i never actually implemented loading files. that would be nice for me to do. or you. or whatever
we should save all the units stats and current stats and positions and level and whos dead
-i was thinkin instead of listing exp and level as a number we can have an exp bar
-that one thing i mentioned where if you click and hold and drag awy from a sprite itll teleport
to the corner
-still a glitch caused by the enemy ai that makes the hero health bars break; only occurs once
on level 2 now

STUFF THAT STILL NEEDS TO BE DONE FROM BEFORE owo
-stat growth is solely based off of base unit stats, not class;
ideally we can implement growth rates for both and average them to
get the actual growth rate
-we just need to balance the stats more, i made a note more about this where class stats are set uwu~
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <SFML/Audio.hpp>
#include <math.h>

using namespace sf;
using namespace std;

#pragma region CONSTANT INTS
//NUMBER OF UNITS
const int unitnumb = 10;
//number of columns, number of rows
const int gridcol = 34, gridrow = 13;
#pragma endregion


#pragma region STRUCTS
enum ItemType { WEAPON, ARMOUR, CHARM, UTILITY, EMPTY };
enum WeaponType { PHYS, AUTO, VEHIC };
enum ClassID { GENERAL, SNIPER, WARRIOR, SOLDIER, SWORDSMAN, KNIGHT, ASSASSIN, ARMOURED, SHAPESHIFTER, DRAGONKIN, ANIMAL };
struct Item {
	ItemType Item_Type;
	string name, type;

	void setStat(ItemType currItem, int atk1, int def1, int spd1, int mov1, int atkRange1, int accuracy1, WeaponType type1, string name1) {
		Item_Type = currItem;
		name = name1;
		switch (Item_Type) {
		case WEAPON:
			weapon.setStat(atk1, def1, spd1, mov1, atkRange1, type1, accuracy1);
			type = "Weapon";
			break;
		case EMPTY:
			type = "";
			break;
		}
	}

	struct Weapon {
		WeaponType type;
		int atk, def, spd, mov, atkRange, accuracy;
		void setStat(int atk1, int def1, int spd1, int mov1, int atkRange1, WeaponType type1, int accuracy1) {
			atk = atk1;
			def = def1;
			spd = spd1;
			mov = mov1;
			atkRange = atkRange1;
			type = type1;
			accuracy = accuracy1;
		}
	}weapon;

	struct Armour {

	}armour;

	struct Charm {

	}charm;

	struct Utility { // anything with one time use

	}utility;

	bool canEquip() {
		if (!(Item_Type == UTILITY)) {
			return true;
		}
	};
}ItemID[5][100];

struct unitClass {
	string name;
	ClassID classid;
	float atkbuff;
	float defbuff;
	float sklbuff;
	float spdbuff;
	float movbuff;
	float hpbuff;

	void setDeets(string name1, ClassID classid1, float atkbuff1, float defbuff1, float sklbuff1, float spdbuff1, float movbuff1, float hpbuff1) {
		name = name1;
		classid = classid1;
		atkbuff = atkbuff1;
		defbuff = defbuff1;
		sklbuff = sklbuff1;
		spdbuff = spdbuff1;
		movbuff = movbuff1;
		hpbuff = hpbuff1;
	}


}classID[30];


struct inventory {
	Item invo[8];
	int actWeapon; int weaponAtk; int weaponDef; int weaponSpd; int weaponMov; int weaponAtkRange; int weaponAcc;
	int actArmour;
	int actCharm;
	bool active[8];

	void init() {
		for (int i = 0; i < 8; i++) {
			invo[i] = ItemID[5][0];
		}
		invo[0] = ItemID[0][0];
	}

	void setInv(int list, int newtype, int newid) {
		invo[list] = ItemID[newtype][newid];
	}

	void equip(ItemType type, int list) {
		switch (type) {
		case WEAPON:
			actWeapon = list;
			weaponAtk = invo[list].weapon.atk;
			weaponDef = invo[list].weapon.def;
			weaponSpd = invo[list].weapon.spd;
			weaponMov = invo[list].weapon.mov;
			weaponAtkRange = invo[list].weapon.atkRange;
			weaponAcc = invo[list].weapon.accuracy;
		}
	}
};

struct NatUnit {
	bool isDead;
	int atk, def, skl, spd, mov, baselvl, exp;
	int ID, type;
	float maxhp, hp, atkgr, defgr, sklgr, spdgr;
	unitClass currClass;
	string name;

	void setStat(bool dead, int atk2, int def2, int skl2, int spd2, int mov2, float maxhp2, float hp2, int lvl2, float atkgr2, float defgr2, float sklgr2, float spdgr2, string name2, int ID2, int type2, unitClass currClass2) {
		isDead = dead;
		atk = atk2;
		def = def2;
		skl = skl2;
		spd = spd2;
		mov = mov2;
		maxhp = maxhp2;
		hp = hp2;
		baselvl = lvl2;
		exp = 9980;
		atkgr = atkgr2;
		defgr = defgr2;
		sklgr = sklgr2;
		spdgr = spdgr2;
		name = name2;
		ID = ID2;
		type = type2;
		currClass = currClass2;
	}
}unitdata[2][50];


struct StoredUnit {
	int ID;
	int atkDif, defDif, sklDif, spdDif, movDif, lvl, exp;
	float maxhp;
	inventory inventory;

	void init(int IDr) {
		ID = IDr;
		atkDif = 0;
		defDif = 0;
		sklDif = 0;
		movDif = 0;
		lvl = unitdata[0][ID].baselvl;
		exp = 0;
	}
}StrUnit[50];

struct LiveUnit {
	bool isDead;
	bool moved = false;
	bool active = false;
	int atk, def, skl, spd, mov, lvl, exp;
	int atkRange;
	int ID;
	int type;
	int x, y;
	bool weaponquip;
	float maxhp, hp, atkgr, defgr, sklgr, spdgr;
	unitClass currClass;
	string name;
	inventory inv;

	void applyClass(unitClass currClass1) {
		atk *= ceil(currClass1.atkbuff);
		def *= ceil(currClass1.defbuff);
		skl *= ceil(currClass1.sklbuff);
		spd *= ceil(currClass1.spdbuff);
		mov *= ceil(currClass1.movbuff);
		maxhp *= ceil(currClass1.hpbuff);
		hp = maxhp;
	}

	void setStat(int type2, int ID2) {
		isDead = 0;
		type = type2;
		if (type2 == 1) { // unit
			atk = unitdata[1][ID2].atk;
			def = unitdata[1][ID2].def;
			skl = unitdata[1][ID2].skl;
			spd = unitdata[1][ID2].spd;
			mov = unitdata[1][ID2].mov;
			maxhp = unitdata[1][ID2].maxhp;
			hp = unitdata[1][ID2].maxhp;
			lvl = unitdata[1][ID2].baselvl;
			name = unitdata[1][ID2].name;
			atkgr = unitdata[1][ID2].atkgr;
			defgr = unitdata[1][ID2].defgr;
			sklgr = unitdata[1][ID2].sklgr;
			spdgr = unitdata[1][ID2].spdgr;
			ID = unitdata[1][ID2].ID;
			currClass = unitdata[1][ID2].currClass;
			applyClass(currClass);
		}
		else { // if player unit
			atk = unitdata[0][ID2].atk + StrUnit[ID2].atkDif;
			def = unitdata[0][ID2].def + StrUnit[ID2].defDif;
			skl = unitdata[0][ID2].skl + StrUnit[ID2].sklDif;
			spd = unitdata[0][ID2].spd + StrUnit[ID2].spdDif;
			mov = unitdata[0][ID2].mov + StrUnit[ID2].movDif;
			maxhp = unitdata[0][ID2].maxhp + StrUnit[ID2].maxhp;
			hp = unitdata[0][ID2].maxhp + StrUnit[ID2].maxhp;
			lvl = unitdata[0][ID2].baselvl + StrUnit[ID2].lvl;
			exp = 9980 + StrUnit[ID2].exp;
			name = unitdata[0][ID2].name;
			atkgr = unitdata[1][ID2].atkgr;
			defgr = unitdata[1][ID2].defgr;
			sklgr = unitdata[1][ID2].sklgr;
			spdgr = unitdata[1][ID2].spdgr;
			ID = unitdata[0][ID2].ID;
			currClass = unitdata[0][ID2].currClass;
			applyClass(currClass);
		}
		x = 0;
		y = 0;


		inv.init();
		weaponquip = false;
		equipUn(WEAPON, 0);
		statMod();
	}

	void equipUn(ItemType type, int list) {
		statDemod();
		inv.equip(type, list);
		statMod();
	}

	void statMod() {
		// FOR WEAPONS ARMOUR CHARMS
		if (!weaponquip) {
			atk += inv.weaponAtk;
			def += inv.weaponDef;
			spd += inv.weaponSpd;
			mov += inv.weaponMov;
			atkRange += inv.weaponAtkRange;
		}
		weaponquip = true;
	}

	void statDemod() {
		if (weaponquip) {
			atk -= inv.weaponAtk;
			def -= inv.weaponDef;
			spd -= inv.weaponSpd;
			mov -= inv.weaponMov;
			atkRange -= inv.weaponAtkRange;
		}
		weaponquip = false;
	}

	void checklevelup(int exp2) {
		exp += exp2;
		statDemod();
		while (exp >= 100) {
			if (lvl < 20) {
				lvl += 1;
				exp -= 100;
				// stuff for leveling up
				StrUnit[ID].atkDif = (lvl - 1)*atkgr;
				StrUnit[ID].defDif = (lvl - 1)*defgr;
				StrUnit[ID].sklDif = (lvl - 1)*sklgr;
				StrUnit[ID].spdDif = (lvl - 1)*spdgr;
				atk = unitdata[0][ID].atk + StrUnit[ID].atkDif;
				def = unitdata[0][ID].def + StrUnit[ID].defDif;
				skl = unitdata[0][ID].skl + StrUnit[ID].sklDif;
				spd = unitdata[0][ID].spd + StrUnit[ID].spdDif;
				maxhp++;
				hp++;
			}
			else {
				exp = 0;
			}
		}
		statMod();
	}

	void die() {
		isDead = true;
		hp = 0;
		x = -30;
		y = -30;
	}

	void setXY(int xx, int yy) {
		x = xx;
		y = yy;
	}
}Unit[2][50];
#pragma endregion

#pragma region VARIABLES

bool useNewBorder = false;
bool useCrits = true;

bool invOpen = false;
int curSelect = 0;

//event and clock
Event event;
Clock sec;

//bounds of sprites
IntRect grassselection(0, 0, 48, 48);
IntRect spriteselection[2][unitnumb] = {
	//HEROES
	{ { 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 } },
	//ENEMIES
	{ { 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 },
	{ 0, 0, 32, 32 }
	}
};
IntRect portraitselection[2][unitnumb] = {
	//HEROES
	{ { 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 } },
	//ENEMIES
	{ { 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 },
	{ 0, 0, 255, 255 }
	}
};
IntRect titlebgselection(0, 0, 750, 500);

IntRect phaseselection[2] = {
	{ 0, 0, 700, 500 },
	{ 0, 0, 700, 500 }
};

//textures
//units
Texture elizial;
Texture kerofor;
Texture adensi;
Texture asdemia;
Texture valdin;
Texture kneas;
Texture zelenir;
Texture kelou;
Texture staluri;
Texture camoria;
//tiles
Texture grass;
Texture water;
Texture mountain;
//portraits
Texture soleilportrait;
Texture vaikeportrait;
Texture elizialportrait;
Texture keroforportrait;
Texture adensiportrait;
//other
Texture titlebg;

Texture herohealth;
Texture enemyhealth;
Texture herohealthsmall;
Texture enemyhealthsmall;

Texture herophase;
Texture enemyphase;


Sprite portraits[2][unitnumb] = {
	//HEROES
	{ { elizialportrait, portraitselection[0][0] },
	{ keroforportrait, portraitselection[0][1] },
	{ adensiportrait, portraitselection[0][2] },
	{ soleilportrait, portraitselection[0][3] },
	{ soleilportrait, portraitselection[0][4] },
	{ soleilportrait, portraitselection[0][5] },
	{ soleilportrait, portraitselection[0][6] },
	{ soleilportrait, portraitselection[0][7] },
	{ soleilportrait, portraitselection[0][8] },
	{ soleilportrait, portraitselection[0][9] } },
	//ENEMIES
	{ { vaikeportrait, portraitselection[1][0] },
	{ vaikeportrait, portraitselection[1][1] },
	{ vaikeportrait, portraitselection[1][2] },
	{ vaikeportrait, portraitselection[1][3] },
	{ vaikeportrait, portraitselection[1][4] },
	{ vaikeportrait, portraitselection[1][5] },
	{ vaikeportrait, portraitselection[1][6] },
	{ vaikeportrait, portraitselection[1][7] },
	{ vaikeportrait, portraitselection[1][8] },
	{ vaikeportrait, portraitselection[1][9] } }

};
//sprites, made with (texture, bounds)
/*
SPRITES
0 = elizial
1 = kerofor
2 = adensi
3 = asdemia
4 = valdin
5 = kneas
6 = zelenir
7 = kelou
8 = staluri
9 = camoria
*/
Sprite sprites[2][unitnumb] = {
	//HEROES
	{ { elizial, spriteselection[0][0] },
	{ kerofor, spriteselection[0][1] },
	{ adensi, spriteselection[0][2] },
	{ asdemia, spriteselection[0][3] },
	{ valdin, spriteselection[0][4] },
	{ kneas, spriteselection[0][5] },
	{ zelenir, spriteselection[0][6] },
	{ kelou, spriteselection[0][7] },
	{ staluri, spriteselection[0][8] },
	{ camoria, spriteselection[0][9] } },
	//ENEMIES
	{ { elizial, spriteselection[1][0] },
	{ kerofor, spriteselection[1][1] },
	{ elizial, spriteselection[1][2] },
	{ elizial, spriteselection[1][3] },
	{ elizial, spriteselection[1][4] },
	{ elizial, spriteselection[1][5] },
	{ elizial, spriteselection[1][6] },
	{ elizial, spriteselection[1][7] },
	{ elizial, spriteselection[1][8] },
	{ elizial, spriteselection[1][9] } }

};

Text turncounttext;
Sprite terrainsprite(grass, grassselection);
Sprite titlebgsprite(titlebg, titlebgselection);
Sprite phasesprite[2] = {
	{ herophase, phaseselection[0] },
	{ enemyphase, phaseselection[1] }
};

//health bars
Sprite currenthealth[2][unitnumb];
Sprite bottomcurrenthealth[2][unitnumb];

bool isForecast[unitnumb] = { false,false,false,false,false,false,false,false,false,false };

bool dontRedraw[2][unitnumb] = {
	//HERO
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//ENEMY	
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


//window dimensions: number of columns/rows times size of grid, plus
//extra border space on both sides
//int rwindowx = gridcol * gridsize + 2 * gridspace;
int rwindowx = VideoMode::getDesktopMode().width;
//int rwindowy = (gridrow * gridsize + 2 * gridspace);
int rwindowy = VideoMode::getDesktopMode().height;

//size of square
int gridsize = 48;
int leftoverspacex = (rwindowx - (gridsize*gridcol)) / 2;
int leftoverspacey = (rwindowy - (rwindowy*.4) - (gridsize*gridrow)) / 2;

//spacing between side of screen
int gridspacex = leftoverspacex;
int gridspacey = leftoverspacey;

//starting position of grid in pixels (2 for the border)
int xgrid = leftoverspacex;
int ygrid = leftoverspacey;



//windows
RenderWindow renderWindow;
RenderWindow titleScreen(VideoMode(750, 500), "Novia Machina");

//views, aka the bottom of the screen and the top of the screen
View view1(FloatRect(0, 0, rwindowx, rwindowy * .6));
View view2(FloatRect(0, 0, rwindowx, rwindowy * .4));

//aaaaall the rectangles
//stuff on the bottom
RectangleShape bottomPortion(Vector2f(rwindowx, (rwindowy*.4) + 24));
RectangleShape bottomPortraitSquare1(Vector2f(256, 256));
RectangleShape bottomPortraitSquare2(Vector2f(256, 256));

RectangleShape backgroundStatBack(Vector2f(rwindowx / 5, rwindowy / 5));
RectangleShape statBox1(Vector2f(rwindowx / 2.5, rwindowy / 3));
RectangleShape statBox2(Vector2f(rwindowx / 2.5, rwindowy / 3));
RectangleShape predictBox(Vector2f(rwindowx / 5, rwindowy / 3));
//grid stuff
RectangleShape grid(Vector2f(gridsize, gridsize));
RectangleShape gridoutline(Vector2f(gridsize*gridcol, gridsize*gridrow));
//title menu stuff
RectangleShape Newrect(Vector2f(150, 100));
RectangleShape Loadrect(Vector2f(150, 100));
RectangleShape Optionsrect(Vector2f(150, 100));
RectangleShape Loadfilerect(Vector2f(750 * .8, 500 * .8));
RectangleShape Loadfile1(Vector2f(Loadfilerect.getGlobalBounds().width*.8, 75));
RectangleShape Loadfile2(Vector2f(Loadfilerect.getGlobalBounds().width*.8, 75));
RectangleShape Loadfile3(Vector2f(Loadfilerect.getGlobalBounds().width*.8, 75));
RectangleShape Optionrect(Vector2f(750 * .8, 500 * .8));
RectangleShape Option1(Vector2f(Optionrect.getGlobalBounds().width*.8, 75));
RectangleShape Option2(Vector2f(Optionrect.getGlobalBounds().width*.8, 75));
RectangleShape Option3(Vector2f(Optionrect.getGlobalBounds().width*.8, 75));
RectangleShape Brexit(Vector2f(Optionrect.getGlobalBounds().width*.2, 45));
RectangleShape invClick[8];
RectangleShape invBack(Vector2f((gridsize*gridcol) - 1, ((gridsize*gridrow) - 1)));
Text invText[2][8];
Text forecastText[3][3];
//health bars
RectangleShape bottombasehealth[2][unitnumb];
RectangleShape basehealth[2][unitnumb];
//and this also
RectangleShape backdrop(Vector2f(rwindowx, rwindowy));
//nya
RectangleShape clickbox[2][unitnumb];
RectangleShape predictle;

//current turn- odd is heroes turn, even is enemys turn
int turn = 1;
int turnchange = 0;
int level = 0;
int loadfile = 1;
int playerUnits = unitnumb; // number of units used by that player
bool titlescreen = true;
bool optionscreen = false;
bool loadscreen = false;
bool cont = true;
bool drawphase[2] = { false, false };
int healthbarcount = 0;
int actUnitID = 0;

bool spritemoved[unitnumb] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
bool spriteIsActive[unitnumb] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

ofstream save;
ifstream load;

int levelData[gridrow][gridcol];

int terrainData1[gridrow][gridcol] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }
};

int terrainData2[gridrow][gridcol] = {
	{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
};

int terrainData3[gridrow][gridcol] = {
	{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }
};

int terrainData4[gridrow][gridcol] = {
	{ 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }
};


Font oxygen;
Text Load;
Text New;
Text Options;
Text Option1text;
Text Option2text;
Text Option3text;
Text Brexittext;


int movRemain;
int atkRange;
int awarenessRange;
Vector2f nearestHeroCoords = (Vector2f(25, 25));


bool readyCollide[gridcol][gridrow]{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

bool readyCollidePreview[gridcol][gridrow]{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


int available[gridcol][gridrow]{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

bool passable[gridcol][gridrow]{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};
/*
Text stat[ENEMY OR NOT ENEMY][# OF UNITS][STATS]
STAT ORDER:
atk, def, skl, spd, mov, lvl, exp, name, maxhp, hp
*/
Text stats[2][unitnumb][15];
Text equip;
int charSize = 25;
Text perbox;

#pragma endregion

#pragma region FNCT
string intToString(int conv) {
	string str;
	if (conv == 0) {
		return "0";
	}
	if (conv < 0) {
		return "0";
	}
	while (conv != 0) {
		str = (char)((conv % 10) + 48) + str;
		conv /= 10;
	}
	return str;
}


void setStatText() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			for (int l = 0; l < 11; l++) {
				stats[i][j][l].setFont(oxygen);
				stats[i][j][l].setCharacterSize(charSize);

				if (i == 0) {
					stats[i][j][l].setPosition(statBox1.getGlobalBounds().left + ((statBox1.getGlobalBounds().width / 2) - (charSize * 3.5)), (25 + statBox1.getGlobalBounds().top) + (30 * l));
				}
				else if (i == 1) {
					stats[i][j][l].setPosition(statBox2.getGlobalBounds().left + ((statBox2.getGlobalBounds().width / 2) - (charSize * 3.5)), (25 + statBox2.getGlobalBounds().top) + (30 * l));
				}

				switch (l) {
				case 0:
					stats[i][j][l].setString("Atk: " + intToString(Unit[i][j].atk));
					break;
				case 1:
					stats[i][j][l].setString("Def: " + intToString(Unit[i][j].def));
					break;
				case 2:
					stats[i][j][l].setString("Skl: " + intToString(Unit[i][j].skl));
					break;
				case 3:
					stats[i][j][l].setString("Spd: " + intToString(Unit[i][j].spd));
					break;
				case 4:
					stats[i][j][l].setString("Mov: " + intToString(Unit[i][j].mov));
					break;
				case 5:
					stats[i][j][l].setString("Lvl: " + intToString(Unit[i][j].lvl));
					break;
				case 6:
					if (i == 0) {
						stats[i][j][l].setString("Exp: " + intToString(Unit[i][j].exp) + "/100");
					}
					break;
				case 7:
					if (i == 0) {
						stats[i][j][l].setPosition(bottomPortraitSquare1.getGlobalBounds().left + 5, bottomPortraitSquare1.getGlobalBounds().top - 65);
					}
					else if (i == 1) {
						stats[i][j][l].setPosition(bottomPortraitSquare2.getGlobalBounds().left + 5, bottomPortraitSquare2.getGlobalBounds().top - 65);
					}
					stats[i][j][l].setString(unitdata[i][j].name);
					break;
				case 8:
					if (i == 0) {
						stats[i][j][l].setPosition(bottomPortraitSquare1.getGlobalBounds().left + 5, bottomPortraitSquare1.getGlobalBounds().top - 30);
					}
					else if (i == 1) {
						stats[i][j][l].setPosition(bottomPortraitSquare2.getGlobalBounds().left + 5, bottomPortraitSquare2.getGlobalBounds().top - 30);
					}
					stats[i][j][l].setString(Unit[i][j].currClass.name);
					break;
				case 9:
					stats[i][j][l].setString(Unit[i][j].inv.invo[Unit[i][j].inv.actWeapon].name);
					break;
				case 10:
					stats[i][j][l].setCharacterSize(15);
					stats[i][j][l].setPosition(bottomcurrenthealth[i][j].getGlobalBounds().left - 50, bottomcurrenthealth[i][j].getGlobalBounds().top);
					stats[i][j][l].setString(intToString(Unit[i][j].hp) + "/" + intToString(Unit[i][j].maxhp));
				}
			}
		}
	}

	//stats[i][j][l].setString(intToString(Unit[i][j].maxhp + "/" + intToString(Unit[i][j].hp));
}

void setLevel() {
	for (int x = 0; x < gridrow; x++) {
		for (int y = 0; y < gridcol; y++) {
			switch (level) {
			case 0:
				levelData[x][y] = terrainData1[x][y];
				break;
			case 1:
				levelData[x][y] = terrainData2[x][y];
				break;
			case 2:
				levelData[x][y] = terrainData3[x][y];
				break;
			case 3:
				levelData[x][y] = terrainData4[x][y];
			}
		}
	}
}

void resetAvailable() {
	for (int i = 0; i < gridrow; i++) {
		for (int c = 0; c < gridcol; c++) {
			available[c][i] = 0;
		}
	}
}

void resetReadyCollide() {
	for (int i = 0; i < gridrow; i++) {
		for (int c = 0; c < gridcol; c++) {
			readyCollide[c][i] = 1;
		}
	}
}

void resetReadyCollidePreview() {
	for (int i = 0; i < gridrow; i++) {
		for (int c = 0; c < gridcol; c++) {
			readyCollidePreview[c][i] = 1;
		}
	}
}

void setPassable(int type, int opptype) {
	for (int i = 0; i < gridrow; i++) {
		for (int c = 0; c < gridcol; c++) {
			passable[c][i] = 1;
		}
	}

	for (int i = 0; i < playerUnits; i++) {
		passable[Unit[opptype][i].x][Unit[opptype][i].y] = 0;

	}

	setLevel();

	for (int i = 0; i < gridrow; i++) {
		for (int c = 0; c < gridcol; c++) {
			switch (levelData[i][c]) {
			case 0:
				break;
			case 1:
				passable[c][i] = 0;
				break;
			case 2:
				passable[c][i] = 0;
			}
		}
	}
}

void walkCheck(int x, int y) {
	if (movRemain == 0) {
		movRemain++;
		return;
	}

	available[(int)x][(int)y] = 1;

	//bottom
	if (passable[x][y - 1] && (y - 1) >= 0) {
		movRemain--;
		walkCheck(x, y - 1);
	}

	//right
	if (passable[x + 1][y] && (x + 1) < gridcol) {
		movRemain--;
		walkCheck(x + 1, y);
	}

	//top
	if (passable[x][y + 1] && (y + 1) < gridrow) {
		movRemain--;
		walkCheck(x, y + 1);
	}

	//left
	if (passable[x - 1][y] && (x - 1) >= 0) {
		movRemain--;
		walkCheck(x - 1, y);
	}

	movRemain++;
}

void enemyAIUnitCheck(int x, int y) {
	//25, 25 is just random coords so i can tell where it got to in the code
	if (awarenessRange == 0) {
		awarenessRange++;
		return;
	}

	for (int i = 0; i < unitnumb; i++) {
		if (x == Unit[0][i].x && y == Unit[0][i].y) {
			nearestHeroCoords = (Vector2f(Unit[0][i].x, Unit[0][i].y));
			return;
		}
	}

	//bottom
	if ((y - 1) >= 0) {
		awarenessRange--;
		enemyAIUnitCheck(x, y - 1);
	}

	//right
	if ((x + 1) < gridcol) {
		awarenessRange--;
		enemyAIUnitCheck(x + 1, y);
	}

	//top
	if ((y + 1) < gridrow) {
		awarenessRange--;
		enemyAIUnitCheck(x, y + 1);
	}

	//left
	if ((x - 1) >= 0) {
		awarenessRange--;
		enemyAIUnitCheck(x - 1, y);
	}

	awarenessRange++;

}

void atkCheck(int x, int y) {
	if (atkRange <= 0) {
		atkRange++;
		return;
	}

	readyCollide[(int)x][(int)y] = false;

	//bottom
	if ((y - 1) >= 0) {
		atkRange--;
		atkCheck(x, y - 1);
	}

	//right
	if ((x + 1) < gridcol) {
		atkRange--;
		atkCheck(x + 1, y);
	}

	//top
	if ((y + 1) < gridrow) {
		atkRange--;
		atkCheck(x, y + 1);
	}

	//left
	if ((x - 1) >= 0) {
		atkRange--;
		atkCheck(x - 1, y);
	}

	atkRange++;

}

void atkCheckPreview(int x, int y) {
	if (atkRange <= 0) {
		atkRange++;
		return;
	}

	readyCollidePreview[(int)x][(int)y] = false;

	//bottom
	if ((y - 1) >= 0) {
		atkRange--;
		atkCheckPreview(x, y - 1);
	}

	//right
	if ((x + 1) < gridcol) {
		atkRange--;
		atkCheckPreview(x + 1, y);
	}

	//top
	if ((y + 1) < gridrow) {
		atkRange--;
		atkCheckPreview(x, y + 1);
	}

	//left
	if ((x - 1) >= 0) {
		atkRange--;
		atkCheckPreview(x - 1, y);
	}

	atkRange++;

}

void atkCheckPreview(int ID) {
	for (int i = 0; i < gridcol; i++) {
		for (int c = 0; c < gridrow; c++) {
			atkRange = Unit[0][ID].atkRange + 1;
			if (available[i][c] == 1) {
				atkCheckPreview(i, c);
			}
		}
	}

	for (int i = 0; i < gridcol; i++) {
		for (int c = 0; c < gridrow; c++) {
			for (int j = 0; j < unitnumb; j++) {
				if (readyCollide[i][c] == false && Unit[0][j].x == i && Unit[0][j].y == c) {
					available[i][c] = 2;
				}
			}
		}
	}
}

void checkAvailable(LiveUnit walker) {
	resetAvailable();
	movRemain = walker.mov + 1;
	int x = walker.x;
	int y = walker.y;
	int type = walker.type;
	int oppType = 0;

	if (type == 0) {
		oppType = 1;
	}

	setPassable(type, oppType);

	available[x][y] = 1;

	//top
	if (passable[x][y + 1] && (y + 1) < gridrow) {
		movRemain--;
		walkCheck(x, y + 1);
	}

	//right
	if (passable[x + 1][y] && (x + 1) < gridcol) {
		movRemain--;
		walkCheck(x + 1, y);
	}

	//bottom
	if (passable[x][y - 1] && (y - 1) >= 0) {
		movRemain--;
		walkCheck(x, y - 1);
	}

	//left
	if (passable[x - 1][y] && (x - 1) >= 0) {
		movRemain--;
		walkCheck(x - 1, y);
	}

	for (int i = 0; i < playerUnits; i++) {
		if (available[Unit[type][i].x][Unit[type][i].y] == 1 || readyCollidePreview[Unit[type][i].x][Unit[type][i].y] == false) {
			available[Unit[type][i].x][Unit[type][i].y] = 2;
		}
	}

	for (int i = 0; i < gridcol; i++) {
		for (int j = 0; j < gridrow; j++) {
			if ((readyCollide[i][j] == false || readyCollidePreview[i][j] == false) && available[i][j] == 0) {
				available[i][j] = 3;
			}
		}
	}

	available[walker.x][walker.y] = 1;
}



void drawgrid() {
	for (int i = 0; i < gridrow; i++) {
		for (int y = 0; y < gridcol; y++) {
			renderWindow.draw(grid);
			grid.setPosition(xgrid, ygrid);
			xgrid += gridsize;
		}
		xgrid = gridspacex;
		ygrid += gridsize;
	}
	xgrid = gridspacex;
	ygrid = gridspacey;
	gridoutline.setPosition(gridspacex, gridspacey);
	renderWindow.draw(gridoutline);
}

void setinvText() {
	for (int i = 0; i < 8; i++) {
		if (Unit[0][actUnitID].inv.invo[i].Item_Type == WEAPON) {
			invText[1][i].setFillColor(Color(20, 150, 20));
		}
		invText[1][i].setString(Unit[0][actUnitID].inv.invo[i].type + "         ");
		invText[0][i].setString(Unit[0][actUnitID].inv.invo[i].name);
		if (Unit[0][actUnitID].inv.actWeapon == i) {
			invClick[i].setOutlineColor(Color(120, 20, 20));
			invClick[i].setFillColor(Color(15, 15, 15));
		}
		else {
			invClick[i].setOutlineColor(Color::Transparent);
			invClick[i].setFillColor(Color(15, 15, 15));
		}
	}
	invClick[curSelect].setFillColor(Color(25, 25, 25));
}

bool isspritehovered(Sprite sprte) {
	if (titleScreen.isOpen()) {
		IntRect bounds(sprte.getPosition().x, sprte.getPosition().y, sprte.getGlobalBounds().width, sprte.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(titleScreen))) {
			return true;
		}
		return false;
	}
	if (renderWindow.isOpen()) {
		IntRect bounds(sprte.getPosition().x, sprte.getPosition().y, sprte.getGlobalBounds().width, sprte.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(renderWindow))) {
			return true;
		}
		return false;
	}
}

bool isrecthovered(RectangleShape rect) {
	if (titleScreen.isOpen()) {
		IntRect bounds(rect.getPosition().x, rect.getPosition().y, rect.getGlobalBounds().width, rect.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(titleScreen))) {
			return true;
		}
		return false;
	}
	if (renderWindow.isOpen()) {
		IntRect bounds(rect.getPosition().x, rect.getPosition().y, rect.getGlobalBounds().width, rect.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(renderWindow))) {
			return true;
		}
		return false;
	}
}

IntRect spriteanimation(Sprite sprite, IntRect selection) {
	//every 1/4 second, move an image right on the sprite sheet- if its at the end
	//of the animation, reset to initial position

	if (isspritehovered(sprite) == true) {
		selection.top += 32;
	}
	while (selection.top > 32) {
		selection.top -= 32;
	}
	if (isspritehovered(sprite) == false) {
		selection.top = 0;
	}
	if (selection.left >= 64) {
		selection.left = 0;
	}
	else {
		selection.left += 32;
	}
	return selection;
}

bool isspriteclicked(Sprite sprte) {
	if (titleScreen.isOpen()) {
		IntRect bounds(sprte.getPosition().x, sprte.getPosition().y, sprte.getGlobalBounds().width, sprte.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(titleScreen)) && (Mouse::isButtonPressed(Mouse::Left))) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (renderWindow.isOpen()) {
		IntRect bounds(sprte.getPosition().x, sprte.getPosition().y, sprte.getGlobalBounds().width, sprte.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(renderWindow))) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
}

bool isrectclicked(RectangleShape rs) {
	if (titleScreen.isOpen()) {
		IntRect bounds(rs.getPosition().x, rs.getPosition().y, rs.getGlobalBounds().width, rs.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(titleScreen)) && (Mouse::isButtonPressed(Mouse::Left))) {
			return true;
		}
		else {
			return false;
		}
	}
	if (renderWindow.isOpen()) {
		IntRect bounds(rs.getPosition().x, rs.getPosition().y, rs.getGlobalBounds().width, rs.getGlobalBounds().height);
		if (bounds.contains(Mouse::getPosition(renderWindow)) && (Mouse::isButtonPressed(Mouse::Left))) {
			return true;
		}
		else {
			return false;
		}
	}


}

bool checkspritecollision(Sprite sprite1, Sprite sprite2) {
	if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds())) {
		return true;
	}
}

void combat(LiveUnit u1, LiveUnit u2, bool crit) {
	//set whether crits exist or not
	int damageTakenu1, damageTakenu2;
	bool u1atktwice = u1.spd >= u2.spd + 5;
	bool u2atktwice = u2.spd >= u1.spd + 5;

	//ATTACKING UNIT ATTACKS DEFENDING UNIT

	damageTakenu2 = u1.atk - (u2.def*.6);
	if (u1.inv.weaponAcc < (rand() % 100)) {
		damageTakenu2 = 0;
	}
	if (damageTakenu2 <= 0) {
		damageTakenu2 = 1;
	}
	if (((u1.skl - u2.skl) + rand() % 100) > 95) {
		damageTakenu2 *= 3;
	}
	Unit[u2.type][u2.ID].hp -= damageTakenu2;
	if (Unit[u2.type][u2.ID].hp <= 0) {
		int expGain;
		if (u2.lvl + 2 - u1.lvl > 0) {
			expGain = ((u2.lvl + 2 - u1.lvl) * 10);
		}
		else {
			expGain = 1;
		}
		Unit[u1.type][u1.ID].checklevelup(expGain);
		Unit[u2.type][u2.ID].die();
	}


	//DEFENDING UNIT COUNTERS ATTACKING UNIT
	if (Unit[u2.type][u2.ID].isDead == false && Unit[u2.type][u2.ID].atkRange >= Unit[u1.type][u1.ID].atkRange) {
		damageTakenu1 = u2.atk - (u1.def*.6);
		if (u2.inv.weaponAcc < (rand() % 100)) {
			damageTakenu1 = 0;
		}
		if (damageTakenu1 <= 0) {
			damageTakenu1 = 1;
		}
		if (((u2.skl - u1.skl) + rand() % 100)>95) {
			damageTakenu1 *= 3;
		}
		Unit[u1.type][u1.ID].hp -= damageTakenu1;
		if (Unit[u1.type][u1.ID].hp <= 0) {
			int expGain;
			if (u1.lvl + 2 - u2.lvl > 0) {
				expGain = (u1.lvl + 2 - u2.lvl) * 10;
			}
			else {
				expGain = 1;
			}
			Unit[u2.type][u2.ID].checklevelup(expGain);
			Unit[u1.type][u1.ID].die();
		}

	}
	if (u1atktwice == true && u1.isDead == false) {
		damageTakenu2 = u1.atk - (u2.def*.6);
		if (damageTakenu2 <= 0) {
			damageTakenu2 = 1;
		}
		if (((u1.skl - u2.skl) + rand() % 100) > 95) {
			damageTakenu2 *= 3;
		}
		Unit[u2.type][u2.ID].hp -= damageTakenu2;
		if (Unit[u2.type][u2.ID].hp <= 0) {
			int expGain;
			if (u2.lvl + 2 - u1.lvl > 0) {
				expGain = ((u2.lvl + 2 - u1.lvl) * 10);
			}
			else {
				expGain = 1;
			}
			Unit[u1.type][u1.ID].checklevelup(expGain);
			Unit[u2.type][u2.ID].die();
		}
	}
	if (u2atktwice == true && u2.isDead == false && Unit[u2.type][u2.ID].atkRange >= Unit[u1.type][u1.ID].atkRange) {
		damageTakenu1 = u2.atk - (u1.def*.6);
		if (damageTakenu1 <= 0) {
			damageTakenu1 = 1;
		}
		if (((u2.skl - u1.skl) + rand() % 100)>95) {
			damageTakenu1 *= 3;
		}
		Unit[u1.type][u1.ID].hp -= damageTakenu1;
		if (Unit[u1.type][u1.ID].hp <= 0) {
			int expGain;
			if (u1.lvl + 2 - u2.lvl > 0) {
				expGain = (u1.lvl + 2 - u2.lvl) * 10;
			}
			else {
				expGain = 1;
			}
			Unit[u2.type][u2.ID].checklevelup(expGain);
			Unit[u1.type][u1.ID].die();
		}
	}
	setStatText();
}




void terrainDraw() {
	int grassx = 0;
	int grassy = 0;
	setLevel();
	for (int i = 0; i < gridrow; i++) {
		for (int c = 0; c < gridcol; c++) {
			if (available[c][i] == 1) {
				terrainsprite.setColor(Color(75, 75, 255));
			}
			else if (available[c][i] == 3) {
				terrainsprite.setColor(Color(255, 75, 75));
			}
			else if (available[c][i] == 2) {
				terrainsprite.setColor(Color(75, 255, 75));
			}
			else {
				terrainsprite.setColor(Color::White);
			}
			terrainsprite.setPosition((grassx * 48) + gridspacex, (grassy * 48) + gridspacey);
			switch (levelData[i][c]) {
			case 0:
				terrainsprite.setTexture(grass);
				renderWindow.draw(terrainsprite);
				break;
			case 1:
				terrainsprite.setTexture(water);
				renderWindow.draw(terrainsprite);
				break;
			case 2:
				terrainsprite.setTexture(mountain);
				renderWindow.draw(terrainsprite);
				break;
			};

			grassx++;
		}
		grassx = 0;
		grassy++;
	}
}

void animation() {
	for (int i = 0; i < unitnumb; i++) {
		for (int j = 0; j < 2; j++) {
			spriteselection[j][i] = spriteanimation(sprites[j][i], spriteselection[j][i]);
			sprites[j][i].setTextureRect(spriteselection[j][i]);
		}
	}
	sec.restart();

}

void draweverything() {
	//update sprites' animation
	if (sec.getElapsedTime().asSeconds() > .25) {
		animation();
	}
	//draw stuff on bottom half of screen
	renderWindow.setView(view2);
	renderWindow.draw(bottomPortion);
	renderWindow.draw(bottomPortraitSquare1);
	renderWindow.draw(bottomPortraitSquare2);
	renderWindow.draw(statBox1);
	renderWindow.draw(statBox2);
	renderWindow.draw(predictBox);

	if (invOpen == true) {
		perbox.setString("Inventory");
	}
	else {
		perbox.setString("");
	}
	for (int i = 0; i < unitnumb; i++) {
		if (isForecast[i] == true) {
			perbox.setString("Forecast");
		}
	}

	int act1 = 0; bool isAct1 = false;
	int act2 = 0; bool isAct2 = false;


	if (useNewBorder == true) {
		grid.setOutlineColor(Color(45, 165, 45, 70));
	}
	else {
		grid.setOutlineColor(Color(255, 255, 255, 125));
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			if (isrecthovered(clickbox[0][j])) {
				act1 = j;
				isAct1 = true;
			}
			if (isrecthovered(clickbox[1][j])) {
				act2 = j;
				isAct2 = true;
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			if (Unit[0][j].active == true) {
				act1 = j;
				isAct1 = true;
			}
			if (Unit[1][j].active == true) {
				act2 = j;
				isAct2 = true;
			}
		}
	}

	for (int k = 0; k < 11; k++) {
		if (isAct1) {
			renderWindow.draw(stats[0][act1][k]);
			renderWindow.draw(bottombasehealth[0][act1]);
			renderWindow.draw(bottomcurrenthealth[0][act1]);
			renderWindow.draw(portraits[0][act1]);
		}
		if (isAct2) {
			for (int n = 0; n < unitnumb; n++) {
				if (isrecthovered(clickbox[1][n]) && !readyCollide[Unit[1][n].x][Unit[1][n].y]) {
					invOpen = false;
				}
			}
			renderWindow.draw(stats[1][act2][k]);
			renderWindow.draw(bottombasehealth[1][act2]);
			renderWindow.draw(bottomcurrenthealth[1][act2]);
			renderWindow.draw(portraits[1][act2]);

		}
	}

	turncounttext.setString("Turn " + intToString((turn + 1) / 2));
	turncounttext.setFont(oxygen);
	renderWindow.draw(turncounttext);
	renderWindow.draw(perbox);

	if (invOpen == true) {
		setinvText();
		for (int i = 0; i < 8; i++) {
			renderWindow.draw(invClick[i]);
			renderWindow.draw(invText[1][i]);
			renderWindow.draw(invText[0][i]);
		}
	}

	for (int m = 0; m < unitnumb; m++) {
		if (isForecast[m] == true) {
			renderWindow.draw(predictle);
			for (int i = 0; i < 3; i++) {
				renderWindow.draw(forecastText[0][i]);
				renderWindow.draw(forecastText[1][i]);
				renderWindow.draw(forecastText[2][i]);
			}
		}
	}
	//draw stuff on top half of screen
	renderWindow.setView(view1);
	terrainDraw();
	drawgrid();
	for (int i = 0; i < unitnumb; i++) {
		for (int j = 0; j < 2; j++) {
			renderWindow.draw(sprites[j][i]);
			renderWindow.draw(basehealth[j][i]);
			renderWindow.draw(currenthealth[j][i]);
		}
	}
	if (drawphase[0] == true) {
		renderWindow.draw(backdrop);
		renderWindow.draw(phasesprite[0]);
	}
	if (drawphase[1] == true) {
		renderWindow.draw(backdrop);
		renderWindow.draw(phasesprite[1]);
	}
	renderWindow.display();
}




void newPhase() {
	bool heroturn = false;
	if (turn % 2 == 0) {
		heroturn = true;
	}
	int max = 256;
	int i = 0;
	int decFactor = -6;
	drawphase[heroturn] = true;

	for (i; i <= max; i -= decFactor) {
		backdrop.setFillColor(Color(25, 25, 25, i - 30));
		phasesprite[heroturn].setColor(Color(255, 255, 255, i));
		draweverything();
	}
	Sleep(330);
	for (int i = 256; i >= 0; i += decFactor) {
		backdrop.setFillColor(Color(25, 25, 25, i - 30));
		phasesprite[heroturn].setColor(Color(255, 255, 255, i));
		draweverything();
	}

	drawphase[heroturn] = false;
}

void enemyTurn() {
	if (turn % 2 == 0) {
		bool enemyInRange = false;
		bool reachedEnd = false;
		Vector2f nearestHero;
		for (int j = 0; j < unitnumb; j++) {
			if (!Unit[1][j].isDead) {
				resetReadyCollidePreview();
				checkAvailable(Unit[1][j]);
				atkRange = Unit[1][j].atkRange + 1;
				atkCheckPreview(Unit[1][j].x, Unit[1][j].y);
				vector<int>unitsInRangeID;

				for (int i = 0; i < unitnumb; i++) {
					if ((readyCollidePreview[Unit[0][i].x][Unit[0][i].y] == false) && Unit[0][i].isDead == false) {
						unitsInRangeID.push_back(Unit[0][i].ID);

					}
				}
				resetReadyCollidePreview();

				if (unitsInRangeID.size() != 0) {
					int lowesthpnumb = unitsInRangeID[0];
					for (int i = 0; i < unitsInRangeID.size(); i++) {
						if (Unit[0][unitsInRangeID[i]].hp < Unit[0][lowesthpnumb].hp) {
							lowesthpnumb = Unit[0][unitsInRangeID[i]].ID;
						}
					}
					int movRemain = Unit[1][j].mov;
					for (int r = Unit[1][j].mov + 1; r >= 0 && movRemain >= 0; r--) {
						if (Unit[1][j].x < Unit[0][lowesthpnumb].x && available[Unit[1][j].x + r][Unit[1][j].y] == 1 && passable[Unit[1][j].x + r][Unit[1][j].y] == true && Unit[1][j].x + r <= gridcol) {
							Unit[1][j].x += r;
							movRemain -= r;
						}
						if (Unit[1][j].x > Unit[0][lowesthpnumb].x && available[Unit[1][j].x - r][Unit[1][j].y] == 1 && passable[Unit[1][j].x - r][Unit[1][j].y] == true && Unit[1][j].x - r > 0) {
							Unit[1][j].x -= r;
							movRemain -= r;
						}
						if (Unit[1][j].y < Unit[0][lowesthpnumb].y && available[Unit[1][j].x][Unit[1][j].y + r] == 1 && passable[Unit[1][j].x][Unit[1][j].y + r] == true && Unit[1][j].y + r <= gridrow) {
							Unit[1][j].y += r;
							movRemain -= r;
						}
						if (Unit[1][j].y > Unit[0][lowesthpnumb].y && available[Unit[1][j].x][Unit[1][j].y - r] == 1 && passable[Unit[1][j].x][Unit[1][j].y - r] == true && Unit[1][j].x - r > 0) {
							Unit[1][j].y -= r;
							movRemain -= r;
						}
					}
					atkCheck(Unit[1][j].x, Unit[1][j].y);
					if (readyCollide[Unit[0][lowesthpnumb].x][Unit[0][lowesthpnumb].y] == false) {
						combat(Unit[1][j], Unit[0][lowesthpnumb], true);
					}
					resetReadyCollide();
				}
				else {
					checkAvailable(Unit[1][j]);
					int movRemain = Unit[1][j].mov;
					awarenessRange = ceil(Unit[1][j].mov * 2);
					enemyAIUnitCheck(Unit[1][j].x, Unit[1][j].y);
					for (int r = Unit[1][j].mov + 1; r >= 0 && movRemain >= 0; r--) {
						if (Unit[1][j].x < nearestHeroCoords.x && available[Unit[1][j].x + r][Unit[1][j].y] == 1 && passable[Unit[1][j].x + r][Unit[1][j].y] == true && Unit[1][j].x + r <= gridcol) {
							Unit[1][j].x += r;
							movRemain -= r;
						}
						if (Unit[1][j].x > nearestHeroCoords.x && available[Unit[1][j].x - r][Unit[1][j].y] == 1 && passable[Unit[1][j].x - r][Unit[1][j].y] == true && Unit[1][j].x - r > 0) {
							Unit[1][j].x -= r;
							movRemain -= r;
						}
						if (Unit[1][j].y < nearestHeroCoords.y && available[Unit[1][j].x][Unit[1][j].y + r] == 1 && passable[Unit[1][j].x][Unit[1][j].y + r] == true && Unit[1][j].y + r <= gridrow) {
							Unit[1][j].y += r;
							movRemain -= r;
						}
						if (Unit[1][j].y > nearestHeroCoords.y && available[Unit[1][j].x][Unit[1][j].y - r] == 1 && passable[Unit[1][j].x][Unit[1][j].y - r] == true && Unit[1][j].x - r > 0) {
							Unit[1][j].y -= r;
							movRemain -= r;
						}

					}
					if (readyCollide[(int)nearestHeroCoords.x][(int)nearestHeroCoords.y] == false) {
						int closestID;
						for (int s = 0; s < unitnumb; s++) {
							if (nearestHeroCoords.x == Unit[0][s].x && nearestHeroCoords.y == Unit[0][s].y) {
								closestID = Unit[0][s].ID;
							}
						}
						combat(Unit[1][j], Unit[0][closestID], true);
					}
				}

			}
		}
		resetAvailable();
		newPhase();
		turn++;
		for (int z = 0; z < playerUnits; z++) {
			sprites[0][z].setColor(Color::White);
		}
	}
}

bool checkallmoved() {
	bool check = true;
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		for (int i = 0; i < unitnumb; i++) {
			Unit[0][i].moved = true;
		}
	}
	for (int i = 0; i < unitnumb; i++) {
		if (Unit[0][i].moved == false && Unit[0][i].isDead == false) {
			check = false;
		}
	}
	//if all units are true, set them all equal to false and increase turn
	if (check == true) {
		turn++;
		for (int i = 0; i < 10; i++) {
			if (Unit[0][i].isDead == false) {
				Unit[0][i].moved = false;
			}
		}
		enemyTurn();
	}
	return check;
}

void combatForecast(LiveUnit u1, LiveUnit u2) {
	int damage[2];
	int hit[2];
	int crit[2];

	damage[0] = u1.atk - (u2.def*.6);
	damage[1] = u2.atk - (u1.def*.6);
	crit[0] = 100 - (95 - (u1.skl - u2.skl));
	crit[1] = 100 - (95 - (u2.skl - u1.skl));
	hit[0] = u1.inv.weaponAcc;
	hit[1] = u2.inv.weaponAcc;

	forecastText[0][1].setString(intToString(damage[0]));
	forecastText[0][2].setString(intToString(damage[1]));
	forecastText[1][1].setString(intToString(hit[0]));
	forecastText[1][2].setString(intToString(hit[1]));
	forecastText[2][1].setString(intToString(crit[0]));
	forecastText[2][2].setString(intToString(crit[1]));
}

void isactive() {

	for (int i = 0; i < unitnumb; i++) {

		if (isrectclicked(clickbox[0][i]) == 1 && Unit[0][i].moved == false) {

			for (int k = 0; k < unitnumb; k++) {
				if (isForecast[k] == false) {
					invOpen = true;
				}
			}

			int originalx = Unit[0][i].x, originaly = Unit[0][i].y;

			do {
				Sleep(12);
				draweverything();
			} while (Mouse::isButtonPressed(Mouse::Left));

			sprites[0][i].setColor(Color::Red);

			Unit[0][i].active = true;

			int nx = 0;
			int ny = 0;
			int ogx = 0;
			int ogy = 0;

			curSelect = Unit[0][i].inv.actWeapon;

			resetReadyCollidePreview();
			checkAvailable(Unit[0][i]);
			atkRange = Unit[0][i].atkRange + 1;
			atkCheckPreview(i);
			int left, top;
			while (!Mouse::isButtonPressed(Mouse::Left) && Unit[0][i].active == true) {
				checkAvailable(Unit[0][i]);

				for (int k = 0; k < unitnumb; k++) {
					if (isForecast[k] == false) {
						invOpen = true;
					}
				}



				/*if (Keyboard::isKeyPressed(Keyboard::Tab)) {
				do {
				draweverything();
				Sleep(10);
				} while (Keyboard::isKeyPressed(Keyboard::Tab));
				invOpen = !invOpen;
				isForecast = false;
				}*/

				if (Keyboard::isKeyPressed(Keyboard::Up) && invOpen) {
					do {
						Sleep(10);
					} while (Keyboard::isKeyPressed(Keyboard::Up));
					do {
						if ((curSelect - 1) < 0) {
							curSelect = 7;
						}
						else {
							curSelect--;
						}
					} while (Unit[0][i].inv.invo[curSelect].Item_Type == EMPTY);
				}

				if (Keyboard::isKeyPressed(Keyboard::Down) && invOpen) {
					do {
						Sleep(10);
					} while (Keyboard::isKeyPressed(Keyboard::Down));
					do {
						if ((curSelect + 1) >= 8) {
							curSelect = 0;
						}
						else {
							curSelect++;
						}
					} while (Unit[0][i].inv.invo[curSelect].Item_Type == EMPTY);
				}

				if (Keyboard::isKeyPressed(Keyboard::Return) && invOpen) {
					if (Unit[0][i].inv.invo[curSelect].Item_Type == WEAPON) {
						Unit[0][i].equipUn(WEAPON, curSelect);
					}
					checkAvailable(Unit[0][i]);
					atkCheckPreview(i);
					setStatText();
					invOpen = false;
					for (int v = 0; v < unitnumb; v++) {
						isForecast[v] = false;
					}
					Unit[0][i].x = originalx;
					Unit[0][i].y = originaly;
					Unit[0][i].active = false;
					sprites[0][i].setColor(Color::White);
					resetAvailable();
				}

				//set sprite position according to mouse
				if (!Keyboard::isKeyPressed(Keyboard::LControl) && !Keyboard::isKeyPressed(Keyboard::RControl)) {
					sprites[0][i].setPosition(Mouse::getPosition(renderWindow).x - leftoverspacex, Mouse::getPosition(renderWindow).y - leftoverspacey);
					left = sprites[0][i].getGlobalBounds().left, top = sprites[0][i].getGlobalBounds().top;
				}
				//snap sprite to grid
				ogx = left - (left % gridsize) + sprites[0][i].getGlobalBounds().width / 4 + gridspacex;
				ogy = top - (top % gridsize) + sprites[0][i].getGlobalBounds().height / 4 + gridspacey;
				int posx = (ogx - gridspacex) / gridsize, posy = (ogy - gridspacey) / gridsize;
				if (available[posx][posy] == 1) {
					nx = ogx;
					ny = ogy;
				}
				sprites[0][i].setPosition(nx, ny);

				actUnitID = i;


				atkRange = Unit[0][i].atkRange + 1;
				atkCheck((nx - gridspacex) / gridsize, (ny - gridspacey) / gridsize);

				for (int n = 0; n < unitnumb; n++) {
					if (isrecthovered(clickbox[1][n]) && !readyCollide[Unit[1][n].x][Unit[1][n].y]) {
						combatForecast(Unit[0][i], Unit[0][n]);
						isForecast[n] = true;
					}
					else {
						isForecast[n] = false;
						invOpen = true;
					}
				}




				//make health bars follow sprite
				basehealth[0][i].setPosition(Vector2f(sprites[0][i].getGlobalBounds().left, sprites[0][i].getGlobalBounds().top + sprites[0][i].getGlobalBounds().height));
				currenthealth[0][i].setPosition(Vector2f(sprites[0][i].getGlobalBounds().left, sprites[0][i].getGlobalBounds().top + sprites[0][i].getGlobalBounds().height));
				draweverything();
				resetReadyCollide();

				if (Mouse::isButtonPressed(Mouse::Right)) {
					Unit[0][i].x = originalx;
					Unit[0][i].y = originaly;
					Unit[0][i].active = false;
					invOpen = false;
					sprites[0][i].setColor(Color::White);
					for (int v = 0; v < unitnumb; v++) {
						isForecast[v] = false;
					}
					resetAvailable();
				}


			}


			if (Mouse::isButtonPressed(Mouse::Left)) {

				Unit[0][i].x = (nx - gridspacex) / gridsize;
				Unit[0][i].y = (ny - gridspacey) / gridsize;

				atkRange = Unit[0][i].atkRange + 1;
				atkCheck(Unit[0][i].x, Unit[0][i].y);


				for (int iv = 0; iv < playerUnits; iv++) {
					if (!readyCollide[Unit[1][iv].x][Unit[1][iv].y] && isrectclicked(clickbox[1][iv]) == 1) {
						combat(Unit[0][i], Unit[1][iv], true);
						isForecast[iv] = false;
					}
				}

				sprites[0][i].setColor(Color(75, 75, 75));
				Unit[0][i].moved = true;
				Unit[0][i].active = false;
				invOpen = false;
				for (int i = 0; i < unitnumb; i++) {
					isForecast[i] = false;
				}
				resetReadyCollide();
				resetAvailable();
			}
		}
	}
}


void savefile(int loadnumb) {
	/*
	FORMAT:
	level
	*/
	switch (loadnumb) {
	case 1:
		save.open("savefile1.dat");
		save << level;
		save.close();
		break;
	case 2:
		save.open("savefile2.dat");
		save << level;
		save.close();
		break;
	case 3:
		save.open("savefile3.dat");
		save << level;
		save.close();
		break;
	}

}

void fileload(int loadnumb) {
	switch (loadnumb) {
	case 1:
		load.open("savefile1.dat");
		load >> level;
		save.close();
		break;
	case 2:
		load.open("savefile2.dat");
		load >> level;
		load.close();
		break;
	case 3:
		load.open("savefile3.dat");
		load >> level;
		load.close();
		break;
	}
}

RectangleShape setHealthBar(Sprite sprite, RectangleShape maxhp) {
	maxhp.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
	return maxhp;
}

Sprite setCurrentHealth(Sprite sprite, Sprite currenthp, int i) {
	IntRect selection(0, 0, sprite.getGlobalBounds().width*(Unit[i][healthbarcount].hp / Unit[i][healthbarcount].maxhp), 5);
	currenthp.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
	currenthp.setTextureRect(selection);
	clickbox[i][healthbarcount].setPosition(sprites[i][healthbarcount].getGlobalBounds().left + ((gridsize / 2) + (sprites[i][healthbarcount].getGlobalBounds().width / 2)) - gridsize, sprites[i][healthbarcount].getGlobalBounds().top + ((gridsize / 2) + (sprites[i][healthbarcount].getGlobalBounds().height / 2)) - gridsize);


	return currenthp;
}

Sprite setBottomHealth(Sprite currenthp, int i) {
	int rw = 150 * (Unit[i][healthbarcount].hp / Unit[i][healthbarcount].maxhp);
	IntRect selection(0, 0, rw, 20);
	currenthp.setTextureRect(selection);

	int rx, ry, rw2, rh;
	if (i == 0) {
		rx = bottomPortraitSquare1.getGlobalBounds().left;
		ry = bottomPortraitSquare1.getGlobalBounds().top;
		rw2 = bottomPortraitSquare1.getGlobalBounds().width / 2;
		rh = bottomPortraitSquare1.getGlobalBounds().height;
	}
	else {
		rx = bottomPortraitSquare2.getGlobalBounds().left;
		ry = bottomPortraitSquare2.getGlobalBounds().top;
		rw2 = bottomPortraitSquare2.getGlobalBounds().width / 2;
		rh = bottomPortraitSquare2.getGlobalBounds().height;
	}
	currenthp.setPosition(rx + (rw2 - (bottombasehealth[0][0].getGlobalBounds().width / 2)), ry + rh + 10);
	return currenthp;
}

void updatexycoords() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			Unit[i][j].x = (int)sprites[0][i].getPosition().x / 48 + gridspacex;
			Unit[i][j].y = (int)sprites[0][i].getPosition().y / 48 + gridspacey;
		}
	}
}

void checkdead() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			if (Unit[i][j].isDead == true && dontRedraw[i][j] == false) {
				for (int t = 0; t < 9; t++) {
					stats[i][j][t].setFillColor(Color::Transparent);
				}
				bottombasehealth[i][j].setFillColor(Color::Transparent);
				bottombasehealth[i][j].setOutlineColor(Color::Transparent);
				bottomcurrenthealth[i][j].setColor(Color::Transparent);
				for (int k = 256; k >= 0; k -= 4) {
					sprites[i][j].setColor(Color(255, 255, 255, k));
					currenthealth[i][j].setColor(Color(255, 255, 255, k));
					basehealth[i][j].setFillColor(Color(50, 50, 50, k));
					basehealth[i][j].setOutlineColor(Color(0, 0, 0, k));
					draweverything();
					if (k == 0) {
						dontRedraw[i][j] = true;
					}
				}
				Unit[i][j].x = gridcol + 1;
				Unit[i][j].y = gridrow + 1;
			}
		}
	}
}

void setUnitPos() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			sprites[i][j].setPosition((Unit[i][j].x * gridsize) + (spriteselection[i][j].width / 4) + gridspacex, (Unit[i][j].y * gridsize) + (spriteselection[i][j].height / 4) + gridspacey);
		}
	}
}

void levelProgression() {
	bool progression = true;
	for (int i = 0; i < unitnumb; i++) {
		if (Unit[1][i].isDead == false) {
			progression = false;
		}
	}
	if (progression == true) {
		level++;
		turn = 1;
		for (int i = 0; i < unitnumb; i++) {
			Unit[1][i].isDead = false;
		}
		setLevel();
	}
}


#pragma endregion


/*
*************
VOID MAIN
*************
*/

void main() {

	/*Item1.Item_Type = WEAPON;
	Item1.GenericWeapon.setStat(0, 0, 0, 0);
	cout << Item1.canEquip();*/
#pragma region HARDCODE DATA
	// CLASSES
	//NOTE: floats are percentages stats are multiplied by (ex: atkbuff of 
	//1.5 means class boosts base atk by 150%)
	//FLOATS MUST ADD TO 6 TO KEEP CLASSES BALANCED
	//side note: maybe should add to 12 or 18 instead? eh idk
	//possible change: HP seems to be much more useful than others, and mov/skl
	//seems to be less useful; should play into balancing
	//                                     ATK, DEF, SKL, SPD, MOV, HP
	classID[0].setDeets("General", GENERAL, 1.5, 2, .2, .3, 1, 1);
	classID[1].setDeets("Sniper", SNIPER, .6, .8, 1.4, 1.2, 1, 1);
	classID[2].setDeets("Warrior", WARRIOR, 2, .5, .2, 1.5, .5, 1.3);
	classID[3].setDeets("Soldier", SOLDIER, 1, 1, 1, 1, 1, 1);
	classID[4].setDeets("Swordsman", SWORDSMAN, .4, .4, 1.5, 2, 1, .7);
	classID[5].setDeets("Knight", KNIGHT, .8, 2, .4, .8, .5, 1.5);
	classID[6].setDeets("Assassin", ASSASSIN, .3, .2, 2, 1.5, 1.5, .5);
	classID[7].setDeets("Armoured", ARMOURED, 1.3, 2.5, .1, .1, .5, 1.5);


	//enemy classes
	classID[8].setDeets("Shapeshifter", SHAPESHIFTER, 1.7, .7, .6, 1, 1, 1);
	classID[9].setDeets("Dragonkin", DRAGONKIN, .8, 1.5, .5, .7, 1, 1.5);
	classID[10].setDeets("Wild Animal", ANIMAL, 2.5, .2, .1, .8, 1, 1);





	// WEAPONS          currItem, atk1, def1, spd1, mov1, atkRange1, type1, name1
	ItemID[0][0].setStat(WEAPON, -4, -4, 6, 3, 1, 70, PHYS, "Stick");
	ItemID[0][1].setStat(WEAPON, 4, 5, 2, 0, 2, 95, PHYS, "Spear");
	ItemID[0][2].setStat(WEAPON, 3, 3, 7, 0, 2, 70, PHYS, "Gun");
	ItemID[0][3].setStat(WEAPON, 7, 4, -2, -1, 1, 50, PHYS, "Axe");
	ItemID[0][4].setStat(WEAPON, 3, 7, 4, 0, 1, 90, PHYS, "Sword");
	ItemID[0][5].setStat(WEAPON, 10, -2, 3, 0, 4, 30, PHYS, "Sniper Rifle");
	ItemID[0][6].setStat(WEAPON, 3, 0, 7, 0, 2, 100, PHYS, "Dagger");
	ItemID[0][7].setStat(WEAPON, 9, -5, -5, -2, 3, 90, PHYS, "Machine Gun");

	ItemID[0][8].setStat(WEAPON, 4, 8, 4, 0, 1, 95, PHYS, "Claws");
	ItemID[0][9].setStat(WEAPON, 8, 3, 8, 0, 1, 100, PHYS, "Fangs");
	ItemID[0][10].setStat(WEAPON, 4, 5, 2, 0, 2, 70, PHYS, "Fire Breath");



	ItemID[4][0].setStat(EMPTY, 0, 0, 0, 0, 1, 0, PHYS, "");

	//                    bool dead, int atk2, int def2, int skl2, int spd2, int mov2, float maxhp2, float hp2, int lvl2, float atkgr2, float defgr2, float sklgr2, float spdgr2, string name2, int ID2, int type2, unitClass currClass2
	// STATS
	unitdata[0][0].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, 2, 3, 4, "Elizial", 0, 0, classID[GENERAL]);
	unitdata[0][1].setStat(0, 5, 5, 12, 10, 5, 15, 15, 1, 1, .5, .7, .5, "Kerofor", 1, 1, classID[SNIPER]);
	unitdata[0][2].setStat(0, 20, 5, 2, 9, 4, 15, 15, 1, 1, .5, .7, .5, "Adensi", 2, 2, classID[WARRIOR]);
	unitdata[0][3].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, .5, .7, .5, "Asdemia", 3, 3, classID[SOLDIER]);
	unitdata[0][4].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, .5, .7, .5, "Valdin", 4, 4, classID[WARRIOR]);
	unitdata[0][5].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, .5, .7, .5, "Kneas", 5, 5, classID[ASSASSIN]);
	unitdata[0][6].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, .5, .7, .5, "Zelenir", 6, 6, classID[SWORDSMAN]);
	unitdata[0][7].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, .5, .7, .5, "Kelou", 7, 7, classID[KNIGHT]);
	unitdata[0][8].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, .5, .7, .5, "Staluri", 8, 8, classID[ARMOURED]);
	unitdata[0][9].setStat(0, 10, 7, 4, 5, 4, 15, 15, 1, 1, .5, .7, .5, "Camoria", 9, 9, classID[SNIPER]);
	// enemies
	unitdata[1][0].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "probably a furyr", 0, 0, classID[DRAGONKIN]);
	unitdata[1][1].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "RAWR xD", 1, 1, classID[SHAPESHIFTER]);
	unitdata[1][2].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "elizial's evil twin", 2, 2, classID[ANIMAL]);
	unitdata[1][3].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "witty witty witty name", 3, 3, classID[ANIMAL]);
	unitdata[1][4].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "im NOT clever", 4, 4, classID[DRAGONKIN]);
	unitdata[1][5].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "anemone (get it)", 5, 5, classID[SHAPESHIFTER]);
	unitdata[1][6].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "mi novia <3 (machina)", 6, 6, classID[SHAPESHIFTER]);
	unitdata[1][7].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "knees on fire", 7, 7, classID[ANIMAL]);
	unitdata[1][8].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "what does that mean", 8, 8, classID[DRAGONKIN]);
	unitdata[1][9].setStat(0, 10, 7, 4, 5, 5, 15, 15, 1, 1, .5, .7, .5, "another furry", 9, 9, classID[ANIMAL]);
#pragma endregion
#pragma region LOAD STUFF



	srand((unsigned int)(time(NULL)));

	titlebg.loadFromFile("titlescreenbg.png");
	oxygen.loadFromFile("oxygenmono.ttf");

	Optionsrect.setFillColor(Color(25, 25, 25));
	Newrect.setFillColor(Color(25, 25, 25));
	Loadrect.setFillColor(Color(25, 25, 25));

	Optionsrect.setOutlineColor(Color(0, 0, 0));
	Newrect.setOutlineColor(Color(0, 0, 0));
	Loadrect.setOutlineColor(Color(0, 0, 0));

	Optionsrect.setOutlineThickness(2);
	Newrect.setOutlineThickness(2);
	Loadrect.setOutlineThickness(2);

	Loadfilerect.setFillColor(Color(15, 15, 15));
	Loadfile1.setFillColor(Color(25, 25, 25));
	Loadfile2.setFillColor(Color(25, 25, 25));
	Loadfile3.setFillColor(Color(25, 25, 25));

	Optionrect.setFillColor(Color(15, 15, 15));
	Option1.setFillColor(Color(170, 25, 25));
	Option2.setFillColor(Color(25, 170, 25));
	Option3.setFillColor(Color(25, 25, 25));

	Brexit.setFillColor(Color(15, 15, 15));

	Loadfilerect.setPosition(titleScreen.getSize().x / 2 - Loadfilerect.getGlobalBounds().width / 2, titleScreen.getSize().y / 2 - Loadfilerect.getGlobalBounds().height / 2);
	Loadfile1.setPosition(titleScreen.getSize().x / 2 - Loadfile1.getGlobalBounds().width / 2, Loadfilerect.getGlobalBounds().top + Loadfile1.getGlobalBounds().height / 2);
	Loadfile2.setPosition(titleScreen.getSize().x / 2 - Loadfile2.getGlobalBounds().width / 2, Loadfilerect.getGlobalBounds().top + Loadfile2.getGlobalBounds().height / 2 * 4);
	Loadfile3.setPosition(titleScreen.getSize().x / 2 - Loadfile3.getGlobalBounds().width / 2, Loadfilerect.getGlobalBounds().top + Loadfile3.getGlobalBounds().height / 2 * 7);

	Optionrect.setPosition(titleScreen.getSize().x / 2 - Loadfilerect.getGlobalBounds().width / 2, titleScreen.getSize().y / 2 - Loadfilerect.getGlobalBounds().height / 2);
	Option1.setPosition(titleScreen.getSize().x / 2 - Loadfile1.getGlobalBounds().width / 2, Loadfilerect.getGlobalBounds().top + Loadfile1.getGlobalBounds().height / 2);
	Option2.setPosition(titleScreen.getSize().x / 2 - Loadfile2.getGlobalBounds().width / 2, Loadfilerect.getGlobalBounds().top + Loadfile2.getGlobalBounds().height / 2 * 4);
	Option3.setPosition(titleScreen.getSize().x / 2 - Loadfile3.getGlobalBounds().width / 2, Loadfilerect.getGlobalBounds().top + Loadfile3.getGlobalBounds().height / 2 * 7);

	Loadfilerect.setOutlineThickness(2);
	Loadfilerect.setOutlineColor(Color(0, 0, 0));
	Loadfile1.setOutlineThickness(2);
	Loadfile1.setOutlineColor(Color(0, 0, 0));
	Loadfile2.setOutlineThickness(2);
	Loadfile2.setOutlineColor(Color(0, 0, 0));
	Loadfile3.setOutlineThickness(2);
	Loadfile3.setOutlineColor(Color(0, 0, 0));

	Optionrect.setOutlineThickness(2);
	Optionrect.setOutlineColor(Color(0, 0, 0));
	Option1.setOutlineThickness(2);
	Option1.setOutlineColor(Color(0, 0, 0));
	Option2.setOutlineThickness(2);
	Option2.setOutlineColor(Color(0, 0, 0));
	Option3.setOutlineThickness(2);
	Option3.setOutlineColor(Color(0, 0, 0));

	Brexit.setOutlineThickness(2);
	Brexit.setOutlineColor(Color(0, 0, 0));

	for (int i = 0; i < 8; i++) {
		invClick[i].setOutlineThickness(2);
		invClick[i].setOutlineColor(Color(0, 0, 0));
	}

	Optionsrect.setPosition(750 * (7.0 / 8.0) - Optionsrect.getGlobalBounds().width / 2, 500 * (7.0 / 8.0) - Optionsrect.getGlobalBounds().height);
	Newrect.setPosition(750 * (4.0 / 8.0) - Newrect.getGlobalBounds().width / 2, 500 * (7.0 / 8.0) - Newrect.getGlobalBounds().height);
	Loadrect.setPosition(750 * (1.0 / 8.0) - Loadrect.getGlobalBounds().width / 2, 500 * (7.0 / 8.0) - Loadrect.getGlobalBounds().height);

	Brexit.setPosition(titleScreen.getSize().x - (Brexit.getGlobalBounds().width + 20), titleScreen.getSize().y - (Brexit.getGlobalBounds().height + 10));
	Brexittext.setPosition(Brexit.getGlobalBounds().left + 13, Brexit.getGlobalBounds().top + 10);

	Options.setString("Options");
	New.setString("New");
	Load.setString("Load");
	Option1text.setString("New Borders");
	Option2text.setString("Crits");
	Option3text.setString("Back");
	Brexittext.setString("Exit");

	Options.setPosition(Optionsrect.getPosition().x + Optionsrect.getLocalBounds().width / 4 - 20, Optionsrect.getPosition().y + Optionsrect.getLocalBounds().height / 4);
	New.setPosition(Newrect.getPosition().x + Newrect.getLocalBounds().width / 4, Newrect.getPosition().y + Newrect.getLocalBounds().height / 4);
	Load.setPosition(Loadrect.getPosition().x + Loadrect.getLocalBounds().width / 4, Loadrect.getPosition().y + Loadrect.getLocalBounds().height / 4);
	Option1text.setPosition(Option1.getPosition().x + Option1.getLocalBounds().width / 4 - 20, Option1.getPosition().y + Option1.getLocalBounds().height / 4);
	Option2text.setPosition(Option2.getPosition().x + Option2.getLocalBounds().width / 4 - 20, Option2.getPosition().y + Option2.getLocalBounds().height / 4);
	Option3text.setPosition(Option3.getPosition().x + Option3.getLocalBounds().width / 4 - 20, Option3.getPosition().y + Option3.getLocalBounds().height / 4);

	Options.setFont(oxygen);
	New.setFont(oxygen);
	Load.setFont(oxygen);
	Option1text.setFont(oxygen);
	Option2text.setFont(oxygen);
	Option3text.setFont(oxygen);
	Brexittext.setFont(oxygen);

	for (int i = 0; i < 8; i++) {
		invText[1][i].setFont(oxygen);
		invText[0][i].setFont(oxygen);
	}

	for (int i = 0; i < 3; i++) {
		forecastText[0][i].setFont(oxygen);
		forecastText[1][i].setFont(oxygen);
		forecastText[2][i].setFont(oxygen);
	}


	//sf::Music music[2];
	//music[0].openFromFile("zanza.wav");
	//music[1].openFromFile("valak.wav");

#pragma endregion
#pragma region TITLESCREEN
	//music[1].play();
	int count = 0;
	int instaClose = false;
	while (titlescreen == true) {
		while (titleScreen.pollEvent(event)) {
			//switch on event type    
			switch (event.type) {
			case Event::EventType::Closed:
				titleScreen.close();
				return;
				break;
				//if a key is pressed, switch on what key was pressed
			case Event::KeyPressed:
				switch (event.key.code) {
				case Keyboard::Escape:
					titleScreen.close();
					return;
					break;

				default:
					break;
				}
			}
		}

		titleScreen.draw(titlebgsprite);
		titleScreen.draw(Newrect);
		titleScreen.draw(New);
		titleScreen.draw(Optionsrect);
		titleScreen.draw(Options);
		titleScreen.draw(Loadrect);
		titleScreen.draw(Load);
		titleScreen.draw(Brexit);
		titleScreen.draw(Brexittext);
		titleScreen.display();

		if (isrectclicked(Brexit) == true) {
			instaClose = true;
			renderWindow.close();
			savefile(loadfile);
			break;
		}

		if (isrectclicked(Optionsrect) == true) {
			Sleep(120);
			optionscreen = true;
			while (optionscreen == true) {
				titleScreen.draw(Optionrect);
				titleScreen.draw(Option1);
				titleScreen.draw(Option1text);
				titleScreen.draw(Option2);
				titleScreen.draw(Option2text);
				titleScreen.draw(Option3);
				titleScreen.draw(Option3text);
				titleScreen.display();

				if (isrectclicked(Option1) == true) {
					do {
						Sleep(10);
					} while (Mouse::isButtonPressed(Mouse::Left));
					if (useNewBorder == true) {
						Option1.setFillColor(Color(170, 25, 25));
						useNewBorder = false;
					}
					else {
						Option1.setFillColor(Color(25, 170, 25));
						useNewBorder = true;
					}
				}

				if (isrectclicked(Option2) == true) {
					do {
						Sleep(10);
					} while (Mouse::isButtonPressed(Mouse::Left));
					if (useCrits == true) {
						Option2.setFillColor(Color(170, 25, 25));
						useCrits = false;
					}
					else {
						Option2.setFillColor(Color(25, 170, 25));
						useCrits = true;
					}
				}

				if (isrectclicked(Option3) == true) {
					optionscreen = false;
				}
			}
		}
		if (isrectclicked(Loadrect) == true) {
			Sleep(120);
			loadscreen = true;
			while (loadscreen == true) {
				titleScreen.draw(Loadfilerect);
				titleScreen.draw(Loadfile1);
				titleScreen.draw(Loadfile2);
				titleScreen.draw(Loadfile3);
				titleScreen.display();

				if (isrectclicked(Loadfile1) == true) {
					loadfile = 1;
					fileload(loadfile);
					loadscreen = false;
					titlescreen = false;
				}
				if (isrectclicked(Loadfile2) == true) {
					loadfile = 2;
					fileload(loadfile);
					loadscreen = false;
					titlescreen = false;
				}
				if (isrectclicked(Loadfile3) == true) {
					loadfile = 3;
					fileload(loadfile);
					loadscreen = false;
					titlescreen = false;
				}
			}
		}
		if (isrectclicked(Newrect) == true) {
			titlescreen = false;
		}
	}
	titleScreen.close();
#pragma endregion
#pragma region MORE LOADING
#pragma region START 

	for (int i = 0; i < playerUnits; i++) {
		Unit[0][i].setStat(0, i);
	}

	for (int i = 0; i < unitnumb; i++) {
		Unit[1][i].setStat(1, i);
	}

	playerUnits = unitnumb;

	for (int i = 0; i < 2; i++) {
		for (int c = 0; c < unitnumb; c++) {
			switch (Unit[i][c].currClass.classid) {
			case GENERAL:
				Unit[i][c].inv.setInv(1, WEAPON, 1);
				Unit[i][c].inv.setInv(2, WEAPON, 3);
				Unit[i][c].inv.setInv(3, WEAPON, 2);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case SNIPER:
				Unit[i][c].inv.setInv(1, WEAPON, 2);
				Unit[i][c].inv.setInv(2, WEAPON, 5);
				Unit[i][c].inv.setInv(3, WEAPON, 7);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case WARRIOR:
				Unit[i][c].inv.setInv(1, WEAPON, 3);
				Unit[i][c].inv.setInv(2, WEAPON, 4);
				Unit[i][c].inv.setInv(3, WEAPON, 1);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case SOLDIER:
				Unit[i][c].inv.setInv(1, WEAPON, 4);
				Unit[i][c].inv.setInv(2, WEAPON, 3);
				Unit[i][c].inv.setInv(3, WEAPON, 1);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case SWORDSMAN:
				Unit[i][c].inv.setInv(1, WEAPON, 4);
				Unit[i][c].inv.setInv(2, WEAPON, 1);
				Unit[i][c].inv.setInv(3, WEAPON, 6);

				Unit[i][c].equipUn(WEAPON, 1);
				break;

			case KNIGHT:
				Unit[i][c].inv.setInv(1, WEAPON, 3);
				Unit[i][c].inv.setInv(2, WEAPON, 4);
				Unit[i][c].inv.setInv(3, WEAPON, 1);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case ASSASSIN:
				Unit[i][c].inv.setInv(1, WEAPON, 6);
				Unit[i][c].inv.setInv(2, WEAPON, 2);
				Unit[i][c].inv.setInv(3, WEAPON, 5);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case ARMOURED:
				Unit[i][c].inv.setInv(1, WEAPON, 7);
				Unit[i][c].inv.setInv(2, WEAPON, 3);
				Unit[i][c].inv.setInv(3, WEAPON, 2);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case SHAPESHIFTER:
				Unit[i][c].inv.setInv(1, WEAPON, 9);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case DRAGONKIN:
				Unit[i][c].inv.setInv(1, WEAPON, 10);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			case ANIMAL:
				Unit[i][c].inv.setInv(1, WEAPON, 8);

				Unit[i][c].equipUn(WEAPON, 1);
				break;
			}
		}
	}

#pragma endregion

	setLevel();

	//load tiles
	grass.loadFromFile("grasstile4.png");
	water.loadFromFile("watertile.png");
	mountain.loadFromFile("mountaintile.png");

	//load sprites
	elizial.loadFromFile("elizialminisprite.png");
	kerofor.loadFromFile("keroforminisprite.png");
	adensi.loadFromFile("adensiminisprite.png");
	asdemia.loadFromFile("asdemiaminisprite.png");
	valdin.loadFromFile("valdinminisprite.png");
	kneas.loadFromFile("elizialminisprite.png");
	zelenir.loadFromFile("elizialminisprite.png");
	kelou.loadFromFile("elizialminisprite.png");
	staluri.loadFromFile("elizialminisprite.png");
	camoria.loadFromFile("elizialminisprite.png");

	//load health sprites
	herohealth.loadFromFile("herohealth.png");
	enemyhealth.loadFromFile("enemyhealth.png");
	herohealthsmall.loadFromFile("herohealthsmall.png");
	enemyhealthsmall.loadFromFile("enemyhealthsmall.png");

	//load portraits
	soleilportrait.loadFromFile("soleilportrait.png");
	vaikeportrait.loadFromFile("vaikeportrait.png");
	elizialportrait.loadFromFile("elizialportraitsprite.png");
	keroforportrait.loadFromFile("keroforportraitsprite.png");
	adensiportrait.loadFromFile("adensiportraitsprite.png");

	//load other textures
	herophase.loadFromFile("herophase.png");
	enemyphase.loadFromFile("enemyphase.png");

	Brexit.setPosition(rwindowx - (Brexit.getGlobalBounds().width + 20), statBox1.getGlobalBounds().top + statBox1.getGlobalBounds().height);
	Brexittext.setPosition(Brexit.getGlobalBounds().left + 13, Brexit.getGlobalBounds().top + 10);

	for (int i = 0; i < unitnumb; i++) {
		for (int j = 0; j < 2; j++) {
			basehealth[j][i].setSize(Vector2f(32, 5));
			basehealth[j][i].setFillColor(Color(50, 50, 50));
			basehealth[j][i].setOutlineColor(Color::Black);
			basehealth[j][i].setOutlineThickness(1);
		}
	}
	for (int i = 0; i < unitnumb; i++) {
		for (int j = 0; j < 2; j++) {
			IntRect selection(0, 0, sprites[0][i].getGlobalBounds().width, 5);
			currenthealth[j][i].setTextureRect(selection);
			if (j == 0) {
				currenthealth[j][i].setTexture(herohealthsmall);
			}
			else {
				currenthealth[j][i].setTexture(enemyhealthsmall);
			}
		}
	}
	for (int i = 0; i < unitnumb; i++) {
		for (int j = 0; j < 2; j++) {
			IntRect selection(0, 0, 150, 20);
			bottomcurrenthealth[j][i].setTextureRect(selection);
			if (j == 0) {
				bottomcurrenthealth[j][i].setTexture(herohealth);
			}
			else {
				bottomcurrenthealth[j][i].setTexture(enemyhealth);
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			sprites[i][j].setPosition((Unit[i][j].x * gridsize) + (spriteselection[i][j].width / 4) + gridspacex, (Unit[i][j].y * gridsize) + (spriteselection[i][j].height / 4) + gridspacey);
		}
	}

	for (int i = 0; i < 2; i++) {
		phasesprite[i].setPosition(rwindowx / 2 - phasesprite[i].getGlobalBounds().width / 2, (rwindowy - (rwindowy*.4)) / 2 - phasesprite[i].getGlobalBounds().height / 2);
	}

	bottomPortion.setFillColor(Color(25, 25, 25));
	bottomPortion.setPosition(bottomPortion.getGlobalBounds().left, bottomPortion.getGlobalBounds().top - 24);

	bottomPortraitSquare1.setFillColor(Color(20, 20, 20));
	bottomPortraitSquare1.setOutlineThickness(2);
	bottomPortraitSquare1.setOutlineColor(Color(15, 15, 15));
	bottomPortraitSquare1.setPosition(rwindowx / 8 - bottomPortraitSquare1.getGlobalBounds().width / 2, bottomPortion.getGlobalBounds().top + bottomPortion.getGlobalBounds().height / 2 - bottomPortraitSquare1.getGlobalBounds().height / 2);

	bottomPortraitSquare2.setFillColor(Color(20, 20, 20));
	bottomPortraitSquare2.setOutlineThickness(2);
	bottomPortraitSquare2.setOutlineColor(Color(15, 15, 15));
	bottomPortraitSquare2.setPosition((rwindowx / 8) * 7 - bottomPortraitSquare1.getGlobalBounds().width / 2, bottomPortion.getGlobalBounds().top + bottomPortion.getGlobalBounds().height / 2 - bottomPortraitSquare1.getGlobalBounds().height / 2);

	for (int i = 0; i < unitnumb; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) {
				portraits[j][i].setPosition(Vector2f(bottomPortraitSquare1.getGlobalBounds().left + 2, bottomPortraitSquare1.getGlobalBounds().top + 2));
			}
			else {
				portraits[j][i].setPosition(Vector2f(bottomPortraitSquare2.getGlobalBounds().left + 2, bottomPortraitSquare2.getGlobalBounds().top + 2));
			}
		}
	}

	for (int i = 0; i < unitnumb; i++) {
		for (int j = 0; j < 2; j++) {
			int rx, ry, rw2, rh;
			if (j == 0) {
				rx = bottomPortraitSquare1.getGlobalBounds().left;
				ry = bottomPortraitSquare1.getGlobalBounds().top;
				rw2 = bottomPortraitSquare1.getGlobalBounds().width / 2;
				rh = bottomPortraitSquare1.getGlobalBounds().height;
			}
			else {
				rx = bottomPortraitSquare2.getGlobalBounds().left;
				ry = bottomPortraitSquare2.getGlobalBounds().top;
				rw2 = bottomPortraitSquare2.getGlobalBounds().width / 2;
				rh = bottomPortraitSquare2.getGlobalBounds().height;
			}
			bottombasehealth[j][i].setPosition(rx + (rw2 - (150 / 2)), ry + rh + 10);
			bottombasehealth[j][i].setSize(Vector2f(150, 20));
			bottombasehealth[j][i].setFillColor(Color(50, 50, 50));
			bottombasehealth[j][i].setOutlineColor(Color::Black);
			bottombasehealth[j][i].setOutlineThickness(1);
		}
	}

	statBox1.setFillColor(Color(20, 20, 20));
	statBox1.setOutlineThickness(2);
	statBox1.setOutlineColor(Color(15, 15, 15));
	statBox1.setSize(Vector2f(bottomPortraitSquare1.getGlobalBounds().width * .8, bottomPortraitSquare1.getGlobalBounds().height + 120));
	statBox1.setPosition(bottomPortraitSquare1.getGlobalBounds().left + bottomPortraitSquare1.getGlobalBounds().width + 50, bottomPortraitSquare1.getGlobalBounds().top - 60);

	statBox2.setFillColor(Color(20, 20, 20));
	statBox2.setOutlineThickness(2);
	statBox2.setOutlineColor(Color(15, 15, 15));
	statBox2.setSize(Vector2f(bottomPortraitSquare1.getGlobalBounds().width * .8, bottomPortraitSquare1.getGlobalBounds().height + 120));
	statBox2.setPosition((bottomPortraitSquare2.getGlobalBounds().left - 50) - statBox2.getGlobalBounds().width, bottomPortraitSquare1.getGlobalBounds().top - 60);

	predictBox.setFillColor(Color(20, 20, 20));
	predictBox.setOutlineThickness(2);
	predictBox.setOutlineColor(Color(15, 15, 15));
	predictBox.setSize(Vector2f(rwindowx - (2 * (statBox1.getGlobalBounds().left + statBox2.getGlobalBounds().width + 20) + 20), bottomPortraitSquare1.getGlobalBounds().height + 120));
	predictBox.setPosition(statBox1.getGlobalBounds().left + statBox2.getGlobalBounds().width + 20, bottomPortraitSquare1.getGlobalBounds().top - 60);

	for (int i = 0; i < 8; i++) {
		invClick[i].setFillColor(Color(15, 15, 15));
	}

	for (int i = 0; i < 8; i++) {
		invClick[i].setSize(Vector2f(predictBox.getGlobalBounds().width * .7, predictBox.getGlobalBounds().height / 12));
	}

	int invGap = invClick[1].getGlobalBounds().height * 1.2;
	invClick[0].setPosition(predictBox.getGlobalBounds().left + (predictBox.getSize().x / 2 - invClick[0].getGlobalBounds().width / 2) - 1, (predictBox.getSize().y / 2 - (invGap * 8) / 2) + invGap);

	for (int i = 1; i < 8; i++) {
		invClick[i].setPosition(invClick[0].getGlobalBounds().left, invClick[i - 1].getGlobalBounds().top + invGap);
	}

	for (int i = 0; i < 8; i++) {
		invText[1][i].setPosition(invClick[i].getGlobalBounds().left + 20, invClick[i].getGlobalBounds().top + 5);
		invText[0][i].setPosition(invText[1][i].getGlobalBounds().left + 150, invClick[i].getGlobalBounds().top + 5);
		invText[0][i].setCharacterSize(invClick[i].getGlobalBounds().height * .7);
		invText[1][i].setCharacterSize(invClick[i].getGlobalBounds().height * .7);
	}

	for (int i = 0; i < 3; i++) {
		forecastText[i][1].setPosition(predictBox.getGlobalBounds().left + (((predictBox.getGlobalBounds().width / 2) - ((predictBox.getGlobalBounds().width * .5) / 2))), predictBox.getGlobalBounds().top + ((predictBox.getGlobalBounds().height / 2) - 100) + (i * 50));
		forecastText[i][1].setCharacterSize(35);
	}
	for (int i = 0; i < 3; i++) {
		forecastText[i][0].setPosition(predictBox.getGlobalBounds().left + (((predictBox.getGlobalBounds().width / 2) - ((predictBox.getGlobalBounds().width * .5) / 2))) + (predictBox.getGlobalBounds().width * .15), predictBox.getGlobalBounds().top + ((predictBox.getGlobalBounds().height / 2) - 100) + (i * 50));
		forecastText[i][0].setCharacterSize(20);
	}
	for (int i = 0; i < 3; i++) {
		forecastText[i][2].setPosition(predictBox.getGlobalBounds().left + (((predictBox.getGlobalBounds().width / 2) - ((predictBox.getGlobalBounds().width * .5) / 2))) + (predictBox.getGlobalBounds().width * .3), predictBox.getGlobalBounds().top + ((predictBox.getGlobalBounds().height / 2) - 100) + (i * 50));
		forecastText[i][2].setCharacterSize(35);
	}

	predictle.setPosition(predictBox.getGlobalBounds().left + (((predictBox.getGlobalBounds().width / 2) - ((predictBox.getGlobalBounds().width * .5) / 2))) + (predictBox.getGlobalBounds().width * .15) - 10, predictBox.getGlobalBounds().top + ((predictBox.getGlobalBounds().height / 2) - 100) - 10);
	predictle.setSize(Vector2f((predictBox.getGlobalBounds().width * .15), 155));
	predictle.setFillColor(Color(25, 25, 25));
	predictle.setOutlineColor(Color(10, 10, 10));

	forecastText[0][0].setString("Dmg");
	forecastText[1][0].setString("Hit");
	forecastText[2][0].setString("Crit");

	perbox.setPosition(predictBox.getGlobalBounds().left + ((predictBox.getGlobalBounds().width / 2) - (7 * 15)), predictBox.getGlobalBounds().top + 10);
	perbox.setFont(oxygen);
	perbox.setString("");

	view1.setViewport(FloatRect(0, 0, 1, 0.6));
	view2.setViewport(FloatRect(0, .6, 1, .4));

	grid.setFillColor(Color::Transparent);
	grid.setOutlineThickness(1);
	grid.setOutlineColor(Color(45, 165, 45, 70));

	gridoutline.setFillColor(Color::Transparent);
	gridoutline.setOutlineThickness(2);
	gridoutline.setOutlineColor(Color(255, 255, 255));

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < unitnumb; j++) {
			clickbox[i][j].setSize(Vector2f(48, 48));
			clickbox[i][j].setFillColor(Color::Transparent);
		}
	}

	turncounttext.setPosition(10, bottomPortion.getGlobalBounds().height - 60);

	Unit[0][0].setXY(3, 4);
	Unit[0][1].setXY(3, 9);
	Unit[0][2].setXY(4, 6);
	Unit[0][3].setXY(4, 8);
	Unit[0][4].setXY(5, 3);
	Unit[0][5].setXY(5, 7);
	Unit[0][6].setXY(7, 1);
	Unit[0][7].setXY(8, 1);
	Unit[0][8].setXY(9, 1);
	Unit[0][9].setXY(10, 1);
	Unit[1][0].setXY(1, 2);
	Unit[1][1].setXY(2, 2);
	Unit[1][2].setXY(3, 2);
	Unit[1][3].setXY(4, 2);
	Unit[1][4].setXY(5, 2);
	Unit[1][5].setXY(6, 2);
	Unit[1][6].setXY(7, 2);
	Unit[1][7].setXY(8, 2);
	Unit[1][8].setXY(9, 2);
	Unit[1][9].setXY(10, 2);

#pragma endregion
#pragma region MAIN LOOP




	if (cont == true && instaClose == false) {
		renderWindow.create(VideoMode(rwindowx, rwindowy), "Novia Machina", Style::Fullscreen);
	}




	while (renderWindow.isOpen()) {

		levelProgression();



		if (count == 0) {
			//music[0].play();
			count++;
		}



		//checks for event
		while (renderWindow.pollEvent(event)) {

			if (Mouse::isButtonPressed(Mouse::Left)) {
				//check whether any of the sprites have become active
				for (int i = 0; i < unitnumb; i++) {
					spriteIsActive[i] = isrectclicked(clickbox[0][i]);

					if (spriteIsActive[i] == true && Unit[0][i].moved == false) {
						isactive();
					}
				}
			}


			Image screencap;
			Texture texture;
			texture.create(rwindowx, rwindowy);

			//switch on event type    
			switch (event.type) {
			case Event::EventType::Closed:
				renderWindow.close();
				savefile(loadfile);
				return;
				break;
				//if a key is pressed, switch on what key was pressed
			case Event::KeyPressed:
				switch (event.key.code) {
				case Keyboard::F10:
					texture.update(renderWindow);
					screencap = texture.copyToImage();
					screencap.saveToFile("screencap.png");
					break;
				case Keyboard::Escape:
					renderWindow.close();
					savefile(loadfile);
					return;
					break;
				}
			}
		}

		//updatexycoords();

		setStatText();

		checkdead();

		setUnitPos();

		//update health bar and health bars' position		
		while (healthbarcount < unitnumb) {
			for (int i = 0; i < 2; i++) {
				basehealth[i][healthbarcount] = setHealthBar(sprites[i][healthbarcount], basehealth[i][healthbarcount]);
				currenthealth[i][healthbarcount] = setCurrentHealth(sprites[i][healthbarcount], currenthealth[i][healthbarcount], i);
				bottomcurrenthealth[i][healthbarcount] = setBottomHealth(bottomcurrenthealth[i][healthbarcount], i);
			}
			healthbarcount++;
		}
		healthbarcount = 0;

		checkallmoved();

		draweverything();

		if (turnchange != turn) {
			turnchange = turn;
			newPhase();
		}

	}

#pragma endregion
}