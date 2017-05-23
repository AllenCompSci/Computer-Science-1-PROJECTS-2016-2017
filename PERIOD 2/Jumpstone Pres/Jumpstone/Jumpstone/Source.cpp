/*
Peter Cardenas, Alex Huang, and Adity
Computer Science I
Start: 4..2017
End: ..2017
Jumpstone: Hearthstone with Mario Characters
*/
#include <iostream>
#include <string>
#include <ctime>
#include <string>
#include <Windows.h>
#include <cmath>
#include "Pixel.h"
#include "Cardback.h"
#include "VirtualKeys.h"
#include <thread>
struct Player;
struct UserBoard;
struct OpponentBoard;
int GrDriver, GrMode, ErrorCode;
const int cardNameOffsetX = 96;
const int cardNameOffsetY = 122;
const int cardDescriptionOffsetX = 96;
const int cardDescriptionOffsetY = 180;
const int cardManaOffsetX = 169;
const int cardManaOffsetY = 23;
const int cardAttackOffsetX = 25;
const int cardAttackOffsetY = 220;
const int cardDefenseOffsetX = 168;
const int cardDefenseOffsetY = 220;
const int cardOffset = 228;
bool leftClick = false;
#pragma region function prototypes
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
string setName(int ID);
int setAttack(int ID);
int setDefense(int ID);
int setManaCost(int ID);
void ability(int ID, Player player);
void initiateMinion(int ID, Player player);
void playCard(int ID, Player player);
void takeCard(Player player);
void render(int ID, int x, int y);
void attackMinion(UserBoard minion1, OpponentBoard minion2);
void mulligan();
void drawBoard();
void renderCard(int ID, int x, int y);
void drawImage(int ID, int x, int y);
void putMinionStuff(int ID, int x, int y);
void putSpellStuff(int ID, int x, int y);
bool MOUSE(int VirtualKey);
void matchStart();
void gameStart();
void KEY_LISTENER();
#pragma endregion
INPUT_RECORD irInBuf;
struct PASS {

	int VirtualKey;
	POINT p;
	bool press;
}global;
struct UserBoard {
	int ID;
	int attack;
	int maxAttack;
	int defense;
	int maxDefense;
	int xPos;
	int yPos = 598;
	bool isInPlay;
	bool isAttacking = false;
	int turnActivated;
	bool canAttack = false;
	bool hasTaunt = false;
	bool hasDoubleJump = false;
	bool isInvincible = false;
	bool enrage = false;
	int spikyLevel = 0;
	string abilityText;
	void setAbilityText(string abilityText) {
		this->abilityText = abilityText;
	}
	void setIsAttacking(bool isAttacking) {
		this->isAttacking = isAttacking;
	}
	void setIsInPlay(bool isInPlay) {
		this->isInPlay = isInPlay;
	}
	void setID(int ID) {
		this->ID = ID;
	}
	void setAttack(int attack) {
		this->attack = attack;
		maxAttack = attack;
	}
	void setDefense(int defense) {
		this->defense = defense;
		maxDefense = defense;
	}
	void createBorder() {
		rectangle(xPos + 1, yPos + 1, xPos + 192 + 1, yPos + 100 + 1);
	}
	void deleteMinion() {
		setcolor(WHITE);
		bar(xPos + 1, yPos + 1, xPos + 192 + 1, yPos + 100 + 1);
		isInPlay = false;
	}
	void renderMinion() {
		drawImage(ID, xPos, yPos);
	}
	void drawStats() {
		setcolor(WHITE);
		string attack1 = to_string(attack);
		const char* attack2 = attack1.c_str();
		settextjustify(0, 2);
		outtextxy(xPos, yPos + 100, attack2);
		string defense1 = to_string(defense);
		const char* defense2 = defense1.c_str();
		settextjustify(2, 2);
		outtextxy(xPos + 192, yPos + 100, defense2);
	}
}uC1, uC2, uC3, uC4, uC5, uC6, uC7;
struct OpponentBoard {
	int ID;
	int attack;
	int maxAttack;
	int defense;
	int maxDefense;
	bool isInPlay;
	bool isAttacking = false;
	int turnActivated;
	bool canAttack = false;
	bool hasTaunt = false;
	string abilityText;
	int xPos;
	int yPos = 419;
	void setAbilityText(string abilityText) {
		this->abilityText = abilityText;
	}
	void setIsAttacking(bool isAttacking) {
		this->isAttacking = isAttacking;
	}
	void setIsInPlay(bool isInPlay) {
		this->isInPlay = isInPlay;
	}
	void setID(int ID) {
		this->ID = ID;
	}
	void setAttack(int attack) {
		this->attack = attack;
		maxAttack = attack;
	}
	void setDefense(int defense) {
		this->defense = defense;
		maxDefense = defense;
	}
	void createBorder() {
		rectangle(xPos + 1, yPos + 1, xPos + 192 + 1, yPos + 100 + 1);
	}
	void deleteMinion() {
		setcolor(WHITE);
		bar(xPos + 1, yPos + 1, xPos + 192 + 1, yPos + 100 + 1);
	}
	void renderMinion() {
		drawImage(ID, xPos, yPos);
	}
	void drawStats() {
		setcolor(WHITE);
		string attack1 = to_string(attack);
		const char* attack2 = attack1.c_str();
		settextjustify(0, 2);
		outtextxy(xPos, yPos + 100, attack2);
		string defense1 = to_string(defense);
		const char* defense2 = defense1.c_str();
		settextjustify(2, 2);
		outtextxy(xPos + 192, yPos + 100, defense2);
	}
}oC1, oC2, oC3, oC4, oC5, oC6, oC7;
struct Player {
	bool isUser;
	bool isOpponent;
	bool boardFull = false;
	int attack = 0;
	int health = 30;
	int Deck[30];
	int Hand[7];
	int decideF;
	bool isF;
	int turn = 0;
	int mana = 0;
	int manaThisTurn = 0;
	int fatigueTurn = 0;
	int numMinions;
	void drawStats() {
		settextjustify(1, 1);
		setcolor(WHITE);
		if (isUser) {
			if (attack > 0) {
				string attack1 = to_string(attack);
				const char* attack2 = attack1.c_str();
				outtextxy(922, 734, attack2);
			}
			string health1 = to_string(health);
			const char* health2 = health1.c_str();
			outtextxy(938, 734, health2);
		}
		else if (isOpponent) {
			if (attack > 0) {
				string attack1 = to_string(attack);
				const char* attack2 = attack1.c_str();
				outtextxy(922, 296, attack2);
			}
			string health1 = to_string(health);
			const char* health2 = health1.c_str();
			outtextxy(938, 296, health2);
		}
	}
	void findNumMinions() {
		if (isUser) {
			int count = 0;
			if (uC1.isInPlay) {
				count++;
			}
			if (uC2.isInPlay) {
				count++;
			}
			if (uC3.isInPlay) {
				count++;
			}
			if (uC4.isInPlay) {
				count++;
			}
			if (uC5.isInPlay) {
				count++;
			}
			if (uC6.isInPlay) {
				count++;
			}
			if (uC7.isInPlay) {
				count++;
			}
			numMinions = count;
		}
		else if (isOpponent) {
			int count = 0;
			if (oC1.isInPlay) {
				count++;
			}
			if (oC2.isInPlay) {
				count++;
			}
			if (oC3.isInPlay) {
				count++;
			}
			if (oC4.isInPlay) {
				count++;
			}
			if (oC5.isInPlay) {
				count++;
			}
			if (oC6.isInPlay) {
				count++;
			}
			if (oC7.isInPlay) {
				count++;
			}
			numMinions = count;
		}
	}
	void drawHand() {
		int handSize = sizeof(Hand) / sizeof(Hand[0]);
		for (int i = 0; i < handSize; i++) {
			setcolor(WHITE);
			if (isUser) {
				bar(36 + cardOffset * i, 738, 36 + cardOffset * i - 192, 738 + 246);
			}
		}
		for (int i = 0; i < cardsInHand(Hand); i++) {
			if (isUser) {
				renderCard(Hand[i], 36 + cardOffset * i, 738);
			}
		}
	}
	void setMana(int mana) {
		this->mana = mana;
		return;
	}
	void isFirst() {
		decideF = rand() % 2 + 1;
		if (decideF == 1) {
			bool isF = true;
		}
		else {
			bool isF = false;
		}
	}
	void createDeck() {
		bool isDup[65];
		for (int i = 0; i < 65; i++) {
			isDup[i] = false;
		}
		Deck[0] = 3;
		Deck[1] = 4;
		Deck[2] = 5;
		Deck[3] = 8;
		Deck[4] = 11;
		Deck[5] = 16;
		Deck[6] = 20;
		Deck[7] = 28;
		Deck[8] = 34;
		Deck[9] = 41;
		Deck[10] = 42;
		Deck[11] = 43;
		Deck[12] = 53;
		Deck[13] = 55;
		Deck[14] = 58;
		for (int i = 15; i < 30; i++) {
			Deck[i] = rand() % 65 + 1;
			for (int j = 0; j < i; j++) {
				if (isDup[Deck[i]] == true) {
					j = i;
					i--;
				}
				else if (Deck[i] == Deck[j]) {
					isDup[Deck[i]] = true;
				}
			}
		}
	}
	void resetHand(int hand[]) {
		int handSize = sizeof(Hand) / sizeof(Hand[0]);
		for (int i = 0; i < handSize; i++) {
			if (hand[i] == -1) {
				for (int j = i; j < handSize; j++) {
					if (j == handSize - 1) {}
					else {
						hand[j] = hand[j + 1];
					}
				}
			}
		}
	}
	int cardsInHand(int Hand[]) {
		int handSize = sizeof(Hand) / sizeof(Hand[0]);
		int count = 0;
		for (int i = 0; i < handSize; i++) {
			if (Hand[i] > 0) {
				count++;
			}
		}
		return count;
	}
	int cardsinDeck(int Deck[]) {
		int deckSize = sizeof(Deck) / sizeof(Deck[0]);
		int count = 0;
		for (int i = 0; i < deckSize; i++) {
			if (Deck[i] > 0) {
				count++;
			}
		}
		return count;
	}
	void isDrawn(int location) {
		Deck[location] = -1;
	}
}Opponent, User;
void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	drawBoard();
	system("pause");
	return;
}
void drawBoard() {
	cleardevice();

	//rect 1: full rectangle
	int top1 = 0;
	int left1 = 0;
	int right1 = 1919;
	int bottom1 = 1017;
	setcolor(WHITE);
	bar(top1, left1, right1, bottom1);
	setcolor(BLACK);
	//rect 2: middle of board
	int top2 = 0;
	int left2 = 289;
	int right2 = 1919;
	int bottom2 = 728;
	rectangle(top2, left2, right2, bottom2);
	setcolor(RED);

	//ellipse idek anymore: end turn button
	int X = 1859;
	int Y = 509;
	int Xr = 60;
	int Yr = 40;
	ellipse(X, Y, 0, 360, 62, 42);

	ellipse(X, Y, 0, 360, Xr, Yr);

	fillellipse(X, Y, Xr, Yr);

	setcolor(0);
	// add asthetics to rect 2

	//rect 3: player 1/2 board
	int t3 = 0;
	int l3 = 0;
	int r3 = 1919;
	int b3 = 289;
	rectangle(t3, l3, r3, b3);

	//rect 4: player 1/2 board
	int t4 = 0;
	int l4 = 728;
	int r4 = 1919;
	int b4 = 1017;
	rectangle(t4, l4, r4, b4);
	setcolor(RED);
	fillellipse(930, 726, 15, 15);
	setcolor(GREEN);
	fillellipse(930, 288, 15, 15);
	setcolor(BLACK);
	circle(930, 726, 15);
	circle(930, 288, 15);
	setcolor(BLUE);
	fillellipse(1889, 708, 30, 20);
	fillellipse(1889, 309, 30, 20);
	setcolor(BLACK);
	ellipse(1889, 708, 0, 360, 30, 20);
	ellipse(1889, 309, 0, 360, 30, 20);
	//rect 5: hand
	int l5 = 36;
	int t5 = 30;
	int r5 = 228;
	int b5 = 276;
	rectangle(l5, t5, r5, b5);
	rectangle(l5 + 1, t5 + 1, r5 + 1, b5 + 1);
	rectangle(l5 + 2, t5 + 2, r5 + 2, b5 + 2);

	//rect 6: hand
	rectangle(l5 + 228, t5, r5 + 228, b5);
	rectangle(l5 + 229, t5 + 1, r5 + 229, b5 + 1);
	rectangle(l5 + 230, t5 + 2, r5 + 230, b5 + 2);

	//rect 7: hand
	rectangle(l5 + 456, t5, r5 + 456, b5);
	rectangle(l5 + 457, t5 + 1, r5 + 457, b5 + 1);
	rectangle(l5 + 458, t5 + 2, r5 + 458, b5 + 2);

	//rect 8: hand
	rectangle(l5 + 684, t5, r5 + 684, b5);
	rectangle(l5 + 685, t5 + 1, r5 + 685, b5 + 1);
	rectangle(l5 + 686, t5 + 2, r5 + 686, b5 + 2);

	//rect 9: hand
	rectangle(l5 + 912, t5, r5 + 912, b5);
	rectangle(l5 + 913, t5 + 1, r5 + 913, b5 + 1);
	rectangle(l5 + 914, t5 + 2, r5 + 914, b5 + 2);

	//rect 10: hand
	rectangle(l5 + 1140, t5, r5 + 1140, b5);
	rectangle(l5 + 1141, t5 + 1, r5 + 1141, b5 + 1);
	rectangle(l5 + 1142, t5 + 2, r5 + 1142, b5 + 2);

	//rect 11: hand
	rectangle(l5 + 1368, t5, r5 + 1368, b5);
	rectangle(l5 + 1369, t5 + 1, r5 + 1369, b5 + 1);
	rectangle(l5 + 1370, t5 + 2, r5 + 1370, b5 + 2);

	//rect 18: Hand
	int l18 = 36;
	int t18 = 738;
	int r18 = 228;
	int b18 = 997;
	rectangle(l18, t18, r18, b18);
	rectangle(l18 + 1, t18 + 1, r18 + 1, b18 + 1);
	rectangle(l18 + 2, t18 + 2, r18 + 2, b18 + 2);
	//rect 19: hand
	rectangle(l18 + 228, t18, r18 + 228, b18);
	rectangle(l18 + 229, t18 + 1, r18 + 229, b18 + 1);
	rectangle(l18 + 230, t18 + 2, r18 + 230, b18 + 2);

	//rect 20: hand
	rectangle(l18 + 456, t18, r18 + 456, b18);
	rectangle(l18 + 457, t18 + 1, r18 + 457, b18 + 1);
	rectangle(l18 + 458, t18 + 2, r18 + 458, b18 + 2);

	//rect 21: hand
	rectangle(l18 + 684, t18, r18 + 684, b18);
	rectangle(l18 + 685, t18 + 1, r18 + 685, b18 + 1);
	rectangle(l18 + 686, t18 + 2, r18 + 686, b18 + 2);

	//rect 22: hand
	rectangle(l18 + 912, t18, r18 + 912, b18);
	rectangle(l18 + 913, t18 + 1, r18 + 913, b18 + 1);
	rectangle(l18 + 914, t18 + 2, r18 + 914, b18 + 1);

	//rect 23: hand
	rectangle(l18 + 1140, t18, r18 + 1140, b18);
	rectangle(l18 + 1141, t18 + 1, r18 + 1141, b18 + 1);
	rectangle(l18 + 1142, t18 + 2, r18 + 1142, b18 + 2);

	//rect 24: hand 
	rectangle(l18 + 1368, t18, r18 + 1368, b18);
	rectangle(l18 + 1369, t18 + 1, r18 + 1369, b18 + 1);
	rectangle(l18 + 1370, t18 + 2, r18 + 1370, b18 + 2);
}
string setName(int ID) {
	string names[84] = { "Micro Goomba","Block", "Goomba", "Shy Guy", "Toad", "Bill Blaster", "Fuzzy", "Luma", "Rocky Wrench", "Cheep Cheep", "Green Koopa", "Paragoomba", "Pipe Piranha Plant",
		"Toadsworth", "Yoshi Egg", "Boo", "Bowser Jr.", "Bowser Statue", "Koopatrol", "Magikoopa", "Pokey", "Red Koopa", "Wiggler", "Boomerang Bro", "Captain Toad", "Dry Bones", "Fawful",
		"Goomba Tower", "Hammer Bro", "Lakitu", "Sledge Bro", "Toadette", "Cataquack", "Fire Bro",	"Antasma", "Goomba King", "Dry Bowser", "Honey Queen", "King Boo", "Fire Flower", "Hammer",
		"Super Mushroom", "1-up Mushroom", "Fused Bomb-omb", "Lightning", "Mario's Cap", "Super Star", "Whomp Plomp", "Castle",	"Dr. Mario Pills", "F.L.U.D.D.", "Metal Cap", "POW Block",
		"Wario's Bike", "? Block", "Damsel In Distress", "Thwomp Stomp",	"Blue Shell", "Fuzzy Madness", "Gotta Go Fast!", "Haunted Mansion", "Koopalings' Mischief",	"Mega Mushroom", "Lava Pool",
		"Wassup Bro!", "Coin", "Ball", "Bat", "Bullet Bill", "Lava Bubble", "Ring", "Spiny", "Green Shell", "Iggy", "Larry Koopa", "Lemmy Koopa", "Ludwig von Koopa", "Morton", "Roy Koopa", "War Toad",
		"Wendy O. Koopa", "Red Shell", "Sonic", "Yoshi" };
	return names[ID - 1];
}
int setAttack(int ID) {
	int attackVals[84] = { 1, 0, 2, 1, 1, 0, 2, 1, 1, 4, 2, 2, 1, 3, 0, 5, 4, 1, 3, 3, 3, 3, 2, 5, 3, 2, 5, 5, 4, 3, 9, 4, 5, 6, 3, 6, 3, 1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 2, 2, 1, 1, -1, 2, 2, 1, 1, 2, 2, 3, 1, -1, 6, 3 };
	return attackVals[ID - 1];
}
int setDefense(int ID) {
	int defenseVals[84] = { 1, 4, 2, 2, 3, 5, 2, 2, 2, 3, 2, 4, 5, 3, 3, 3, 3, 7, 5, 4, 3, 4, 5, 5, 4, 1, 4, 5, 5, 5, 7, 5, 3, 5, 7, 6, 15, 8, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,	1, 1, 1, 1, 1, 1, -1, 2, 3, 2, 2, 3, 2, 1, 3, -1, 2, 4 };
	return defenseVals[ID - 1];
}
int setManaCost(int ID) {
	int costVals[84] = { 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 8, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 5, 5,
		6, 6, 6, 6, 8, 10, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 4 };
	return costVals[ID - 1];
}
string setAbilityText(int ID) {
	string abText[84] = {
		"",
		"Taunt",
		"",
		"Run",
		"",
		"Spawn a 2 / 1 Bullet Bill at the end of each turn",
		"When this attacks, restore 3 health to itself",
		"Draw 1 card",
		"When played, deal one damage",
		"",
		"When this dies, put a green shell to your hand",
		"Double Jump",
		"Taunt, Spiky 2",
		"Summon a Toad",
		"When this dies, summon a Yoshi",
		"This card has Invincible the turn it is played",
		"Summons 1 random Koopaling",
		"Taunt Can't attack. At the end of your turn, deal 2 damage to a random enemy.",
		"Taunt When this dies, put a green shell to your hand",
		"Deal 5 damage randomly accross all enemies",
		"Spiky 1 When this dies, summon a copy of this which has - 1 / -1",
		"When this dies, put a Red Shell into your hand",
		"If this unit takes damage, gain 4 attack and Double Jump.",
		"Deal 1 damage to two random enemy minions at the end of your turn",
		"Summon 2 War Toads",
		"When this dies, summon a Dry Bones",
		"Take control of an enemy minion that has 2 or less attack",
		"When this dies, summon a copy of this which has - 2 / -2",
		"Deal 2 damage",
		"Each turn, summon a Spiny",
		"Deal 5 damage.You can only play this card if you have played all Bros.",
		"Restore 5 Health",
		"Taunt Return a minion to its owner's hand",
		"Deal 3 damage",
		"Whenever this card takes damage, summon a bat",
		"Add 2 / 2 to every Goomba on the board",
		"Draw this card when Lava Pool is played. When played, replace your character with dry bowser. Summon two random Koopalings",
		"Heal all characters to full health",
		"Take control of a enemy minion",
		"Give unit + 2 attack",
		"Deal 2 damage",
		"Give a unit + 3 health",
		"Equip to a minion. When it dies, bring it back with half health",
		"Select a character. Deal 8 damage to it next turn.",
		"Set all minions to 1 health",
		"Give a minion \"Summon a Luma at the beginning of your turn.\"",
		"Give a minion Invincible for this turn only",
		"Destroy a minion with 3 or less attack",
		"Summon 1 random Koopaling and a Lava Bubble",
		"Heal 5 to all friendly characters",
		"Return an enemy minion to your opponent's hand",
		"Give a minion + 5 health",
		"Deal 2 damage to all minions",
		"Give a minion Run",
		"Cast a random Mario Power - up on a friendly minion",
		"Give + 3 Health to Your Minions",
		"Deal 5 damage",
		"Destroy the opponent's strongest minion",
		"Deal 2 damage all enemies and restore 2 health to all friendly characters",
		"Summon Sonic",
		"Return all minions to their owner's hand",
		"Summons 3 random Koopalings",
		"Give unit + 5 health, + 7 attack",
		"Destroy all minions",
		"Summon 3 Bros.that have died this game",
		"Give 1 more Mana this turn only",
		"",
		"",
		"",
		"",
		"",
		"Spiky 1",
		"Deal 4 damage randomly across all enemies",
		"Deal 1 damage",
		"",
		"Summon two 1 / 1 Balls",
		"Add a Fire Flower to your hand",
		"Rage Give + 1 attack",
		"Run",
		"",
		"Summon a 1 / 1 Ring",
		"Deal 3 damage to a minion and 2 damage to the enemy character",
		"Run Cannot be targeted by minions",
		"Double Jump, Run"
	};
	return abText[ID - 1];
}
void cast(int ID, Player player) {

}
void initiateMinion(int ID, Player player) {
	if (player.isUser) {
		if (!uC1.isInPlay) {
			uC1.setID(ID);
			uC1.setAttack(setAttack(ID));
			uC1.setDefense(setDefense(ID));
			uC1.setAbilityText(setAbilityText(ID));
			uC1.isInPlay = true;
			uC1.xPos = 36 + cardOffset * 3;
			uC1.createBorder();
			uC1.renderMinion();
			uC1.drawStats();
			player.boardFull = false;
		}
		else if (!uC2.isInPlay) {
			uC2.setID(ID);
			uC2.setAttack(setAttack(ID));
			uC2.setDefense(setDefense(ID));
			uC2.setAbilityText(setAbilityText(ID));
			uC2.isInPlay = true;
			uC2.xPos = 36 + cardOffset * 2;
			uC2.createBorder();
			uC2.renderMinion();
			uC2.drawStats();
			player.boardFull = false;
		}
		else if (!uC3.isInPlay) {
			uC3.setID(ID);
			uC3.setAttack(setAttack(ID));
			uC3.setDefense(setDefense(ID));
			uC3.setAbilityText(setAbilityText(ID));
			uC3.isInPlay = true;
			uC3.xPos = 36 + cardOffset * 4;
			uC3.createBorder();
			uC3.renderMinion();
			uC3.drawStats();
			player.boardFull = false;
		}
		else if (!uC4.isInPlay) {
			uC4.setID(ID);
			uC4.setAttack(setAttack(ID));
			uC4.setDefense(setDefense(ID));
			uC4.setAbilityText(setAbilityText(ID));
			uC4.isInPlay = true;
			uC4.xPos = 36 + cardOffset * 1;
			uC4.createBorder();
			uC4.renderMinion();
			uC4.drawStats();
			player.boardFull = false;
		}
		else if (!uC5.isInPlay) {
			uC5.setID(ID);
			uC5.setAttack(setAttack(ID));
			uC5.setDefense(setDefense(ID));
			uC5.setAbilityText(setAbilityText(ID));
			uC5.isInPlay = true;
			uC5.xPos = 36 + cardOffset * 5;
			uC5.createBorder();
			uC5.renderMinion();
			uC5.drawStats();
			player.boardFull = false;
		}
		else if (!uC6.isInPlay) {
			uC6.setID(ID);
			uC6.setAttack(setAttack(ID));
			uC6.setDefense(setDefense(ID));
			uC6.setAbilityText(setAbilityText(ID));
			uC6.isInPlay = true;
			uC6.xPos = 36 + cardOffset * 0;
			uC6.createBorder();
			uC6.renderMinion();
			uC6.drawStats();
			player.boardFull = false;
		}
		else if (!uC7.isInPlay) {
			uC7.setID(ID);
			uC7.setAttack(setAttack(ID));
			uC7.setDefense(setDefense(ID));
			uC7.setAbilityText(setAbilityText(ID));
			uC7.isInPlay = true;
			uC7.xPos = 36 + cardOffset * 6;
			uC7.createBorder();
			uC7.renderMinion();
			uC7.drawStats();
			player.boardFull = true;
		}
		else {
			player.boardFull = true;
		}
	}
	else if (player.isOpponent) {
		if (!oC1.isInPlay) {
			oC1.setID(ID);
			oC1.setAttack(setAttack(ID));
			oC1.setDefense(setDefense(ID));
			oC1.setAbilityText(setAbilityText(ID));
			oC1.isInPlay = true;
			oC1.xPos = 36 + cardOffset * 3;
			oC1.createBorder();
			oC1.renderMinion();
			oC1.drawStats();
			player.boardFull = false;
		}
		else if (!oC2.isInPlay) {
			oC2.setID(ID);
			oC2.setAttack(setAttack(ID));
			oC2.setDefense(setDefense(ID));
			oC2.setAbilityText(setAbilityText(ID));
			oC2.isInPlay = true;
			oC2.xPos = 36 + cardOffset * 2;
			oC2.createBorder();
			oC3.renderMinion();
			oC2.drawStats();
			player.boardFull = false;
		}
		else if (!oC3.isInPlay) {
			oC3.setID(ID);
			oC3.setAttack(setAttack(ID));
			oC3.setDefense(setDefense(ID));
			oC3.setAbilityText(setAbilityText(ID));
			oC3.isInPlay = true;
			oC3.xPos = 36 + cardOffset * 4;
			oC3.createBorder();
			oC3.renderMinion();
			oC3.drawStats();
			player.boardFull = false;
		}
		else if (!oC4.isInPlay) {
			oC4.setID(ID);
			oC4.setAttack(setAttack(ID));
			oC4.setDefense(setDefense(ID));
			oC4.setAbilityText(setAbilityText(ID));
			oC4.setAbilityText(setAbilityText(ID));
			oC4.isInPlay = true;
			oC4.xPos = 36 + cardOffset * 1;
			oC4.createBorder();
			oC4.renderMinion();
			oC4.drawStats();
			player.boardFull = false;
		}
		else if (!oC5.isInPlay) {
			oC5.setID(ID);
			oC5.setAttack(setAttack(ID));
			oC5.setDefense(setDefense(ID));
			oC5.setAbilityText(setAbilityText(ID));
			oC5.isInPlay = true;
			oC5.xPos = 36 + cardOffset * 5;
			oC5.createBorder();
			oC5.renderMinion();
			oC5.drawStats();
			player.boardFull = false;
		}
		else if (!oC6.isInPlay) {
			oC6.setID(ID);
			oC6.setAttack(setAttack(ID));
			oC6.setDefense(setDefense(ID));
			oC6.setAbilityText(setAbilityText(ID));
			oC6.isInPlay = true;
			oC6.xPos = 36 + cardOffset * 0;
			oC6.createBorder();
			oC6.renderMinion();
			oC6.drawStats();
			player.boardFull = false;
		}
		else if (!oC7.isInPlay) {
			oC7.setID(ID);
			oC7.setAttack(setAttack(ID));
			oC7.setDefense(setDefense(ID));
			oC7.setAbilityText(setAbilityText(ID));
			oC7.isInPlay = true;
			oC7.xPos = 36 + cardOffset * 6;
			oC7.createBorder();
			oC7.renderMinion();
			oC7.drawStats();
			player.boardFull = true;
		}
		else {
			player.boardFull = true;
		}
	}
}
void playCard(int ID, Player player) {
	if (player.manaThisTurn < setManaCost(ID)) {

	}
	else if ((ID >= 1 && ID <= 39) || (ID >= 67 && ID <= 72) || (ID >= 74 && ID <= 81) || (ID >= 83 && ID <= 84)) {
		initiateMinion(ID, player); \
	}
	else if ((ID >= 40 && ID <= 65) || ID == 66 || ID == 73 || ID == 82) {
		cast(ID, player);
	}
}
void takeCard(Player player) {
	int deckSize = sizeof(player.Deck) / sizeof(player.Deck[0]);
	int handSize = sizeof(player.Hand) / sizeof(player.Hand[0]);
	int cardDrawn;
	int location;
	if (player.cardsinDeck(player.Deck) == 0) {
		if (player.fatigueTurn == 0) {
			player.fatigueTurn = player.turn;
		}
		player.health -= player.turn - (player.fatigueTurn - 1);
	}
	else {
		do {
			location = rand() % deckSize;
			cardDrawn = player.Deck[location];
		} while (cardDrawn == -1);
		if (handSize == player.cardsInHand(player.Hand)) {
			//burn card	
		}
		else {
			player.Hand[player.cardsInHand(player.Hand)] = cardDrawn;
		}
		player.isDrawn(location);
	}
	player.drawHand();
}
void gameStart() {
	matchStart();
}
void matchStart() {
	User.isUser = true;
	Opponent.isOpponent = true;
	Opponent.createDeck();
	User.createDeck();
	mulligan();
}
void decideFOS() {
	User.isFirst();
	if (User.isF) {
		Opponent.isF = false;
	}
	else {
		Opponent.isF = true;
	}
	User.turn, Opponent.turn = 1;
}
void mulligan() {
	//three cards each player, second player gets 2 coins
	int top1 = 0;
	int left1 = 0;
	int right1 = 1919;
	int bottom1 = 1017;
	setcolor(WHITE);
	bar(top1, left1, right1, bottom1);
	decideFOS();
	int location;
	int deckSize = sizeof(User.Deck) / sizeof(User.Deck[0]);
	bool clickedRegion1 = false;
	bool clickedRegion2 = false;
	bool clickedRegion3 = false;
	bool mDone = false;
	if (User.isF) {
		for (int i = 0; i < 3; i++) {
			location = rand() % deckSize;
			User.Hand[i] = User.Deck[location];
			User.isDrawn(location);
			location = rand() % deckSize;
			Opponent.Hand[i] = Opponent.Deck[location];
			Opponent.isDrawn(location);
		}
		Opponent.Hand[3], Opponent.Hand[4] = 66;
	}
	else if (Opponent.isF) {
		for (int i = 0; i < 3; i++) {
			location = rand() % deckSize;
			User.Hand[i] = User.Deck[location];
			User.isDrawn(location);
			location = rand() % deckSize;
			Opponent.Hand[i] = Opponent.Deck[location];
			Opponent.isDrawn(location);
		}
		User.Hand[3], User.Hand[4] = 66;
	}
	renderCard(User.Hand[0], getmaxx() / 2 - 98 - cardOffset, getmaxy() / 2 - 132);
	renderCard(User.Hand[1], getmaxx() / 2 - 98, getmaxy() / 2 - 132);
	renderCard(User.Hand[2], getmaxx() / 2 - 98 + cardOffset, getmaxy() / 2 - 132);
	setcolor(BLUE);
	fillellipse(getmaxx() / 2, 726, 62, 42);
	setcolor(BLACK);
	ellipse(getmaxx() / 2, 726, 0, 360, 62, 42);
	settextjustify(1, 1);
	setcolor(WHITE);
	outtextxy(getmaxx() / 2, 726, "DONE");
	//mulligan for user
	while (!mDone) {
		if (global.press) {
			if (leftClick) {
				if ((global.p.x >= getmaxx() / 2 - 31 && global.p.x <= getmaxx() / 2 + 31) && (global.p.y >= 726 - 21 && global.p.y <= 726 + 21)) {
					mDone = true;
				}
				else if ((global.p.x >= getmaxx() / 2 - 98 - cardOffset && global.p.x <= getmaxx() / 2 - 98 - cardOffset + 192)
					&& (global.p.y >= getmaxy() / 2 - 132 && global.p.y <= getmaxy() / 2 - 132 + 264)) {
					clickedRegion1 = !clickedRegion1;
				}
				else if ((global.p.x >= getmaxx() / 2 - 98 && global.p.x <= getmaxx() / 2 - 98 + 192)
					&& (global.p.y >= getmaxy() / 2 - 132 && global.p.y <= getmaxy() / 2 - 132 + 264)) {
					clickedRegion2 = !clickedRegion2;
				}
				else if ((global.p.x >= getmaxx() / 2 - 98 + cardOffset && global.p.x <= getmaxx() / 2 - 98 + cardOffset + 192)
					&& (global.p.y >= getmaxy() / 2 - 132 && global.p.y <= getmaxy() / 2 - 132 + 264)) {
					clickedRegion3 = !clickedRegion3;
				}
				leftClick = false;
			}
			global.press = false;
		}
	}
	if (mDone) {
		if (clickedRegion1) {
			while (User.Hand[0] != -1) {
				int i = 0;
				if (User.Deck[i] = -1) {
					User.Deck[i] = User.Hand[0];
					User.Hand[0] = -1;
				}
				i++;
			}
			if (clickedRegion2) {
				while (User.Hand[1] != -1) {
					int i = 0;
					if (User.Deck[i] = -1) {
						User.Deck[i] = User.Hand[1];
						User.Hand[1] = -1;
					}
					i++;
				}
				if (clickedRegion3) {
					while (User.Hand[2] != -1) {
						int i = 0;
						if (User.Deck[i] = -1) {
							User.Deck[i] = User.Hand[2];
							User.Hand[2] = -1;
						}
						i++;
					}
				}
			}
			else if (clickedRegion3) {
				while (User.Hand[2] != -1) {
					int i = 0;
					if (User.Deck[i] = -1) {
						User.Deck[i] = User.Hand[2];
						User.Hand[2] = -1;
					}
					i++;
				}
			}
		}
		else if (clickedRegion2) {
			while (User.Hand[1] != -1) {
				int i = 0;
				if (User.Deck[i] = -1) {
					User.Deck[i] = User.Hand[1];
					User.Hand[1] = -1;
				}
				i++;
			}
			if (clickedRegion3) {
				while (User.Hand[2] != -1) {
					int i = 0;
					if (User.Deck[i] = -1) {
						User.Deck[i] = User.Hand[2];
						User.Hand[2] = -1;
					}
					i++;
				}
			}
		}
		else if (clickedRegion3) {
			while (User.Hand[2] != -1) {
				int i = 0;
				if (User.Deck[i] = -1) {
					User.Deck[i] = User.Hand[2];
					User.Hand[2] = -1;
				}
				i++;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (User.Hand[i] == -1) {
				location = rand() % deckSize;
				User.Hand[i] = User.Deck[location];
				User.isDrawn(location);
			}
		}
	}
	User.drawHand();
	//mulligan for computer (opponent)
}
bool MOUSE(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = MOUSE_EVENT;
		GetCursorPos(&global.p);
		global.press = true;

		return true;
	}
	return false;
}
bool KEYBOARD(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = KEY_EVENT;
		global.press = true;
		global.VirtualKey = VirtualKey;
		return true;
	}
	return false;
}
void KEY_LISTENER() {
	while (true) {
		if (MOUSE(VK_LBUTTON)) {
			POINT v;
			GetCursorPos(&v);

		}
		if (KEYBOARD(VK_1)) {

		}
		if (KEYBOARD(VK_2)) {

		}
		if (KEYBOARD(VK_3)) {

		}
		if (KEYBOARD(VK_4)) {

		}
		if (KEYBOARD(VK_5)) {

		}
		if (KEYBOARD(VK_6)) {

		}
		if (KEYBOARD(VK_7)) {

		}
	}
}
void turn() {
	if (User.isF) {
		if (User.turn == Opponent.turn) { // Do User 
			takeCard(User);
			User.setMana(User.turn);
		}
		else if (User.turn > Opponent.turn) { // Do Opponent
			takeCard(Opponent);
			Opponent.setMana(Opponent.turn);
		}
	}
	else if (Opponent.isF) {
		if (Opponent.turn == User.turn) { // Do Opponent 
			takeCard(Opponent);
			Opponent.setMana(Opponent.turn);
		}
		else if (Opponent.turn > User.turn) { // Do User
			takeCard(User);
			User.setMana(User.turn);
		}
	}
}
void renderCard(int ID, int x, int y) {//starts at the top left
	if ((ID >= 1 && ID <= 39) || (ID >= 67 && ID <= 72) || (ID >= 74 && ID <= 81) || (ID >= 83 && ID <= 84)) {
		drawMinionCardback(x, y);
		putMinionStuff(ID, x, y);
	}
	else if ((ID >= 40 && ID <= 65) || ID == 66 || ID == 73 || ID == 82) {
		drawSpellCardback(x, y);
		putSpellStuff(ID, x, y);
	}
}
/*
void triggerAbility() {
//Requires trigger other than playing a card
if (ID == 6) {//triggers at end of turn
initiateMinion(69, User);
}
else if (ID == 7) {//triggers when minion attacks
if (maxDefense - defense >= 3) {
defense += 3;
}
else {
defense = maxDefense;
}
}
else if (ID == 11) {//triggers when minion dies
if (User.cardsInHand(User.Hand) == 7) {
}
else {
User.Hand[User.cardsInHand(User.Hand)] = 73;
User.drawHand();
}
}
else if (ID == 15) {
initiateMinion(84, User);
}
else if (ID == 18) {
// deal 2 damage to a random enemy
}
else if (ID == 19) {
if (User.cardsInHand(User.Hand) == 7) {
}
else {
User.Hand[User.cardsInHand(User.Hand)] = 73;
User.drawHand();
}
}
else if (ID == 21) {
// summon -1/-1 of itself on death
}
else if (ID == 22) {//triggers when minion dies
if (User.cardsInHand(User.Hand) == 7) {
}
else {
User.Hand[User.cardsInHand(User.Hand)] = 82;
User.drawHand();
}
}
else if (ID == 23) {
attack, maxAttack += 4;
hasDoubleJump = true;
}
else if (ID == 24) {
//deal 1 damage to two random enemy mininos at the end of your turn
}
else if (ID == 26) {
initiateMinion(26, User);
}
else if (ID == 28) {
// summon -2/-2 copy of itself on death
}
else if (ID == 30) {
//Each turn
initiateMinion(72, User);
}
}
void activateAbility() {//ones not listed don't have abilities or are triggers
//battlecry, attributes
if (ID == 2) {
hasTaunt = true;
}
else if (ID == 4) {
canAttack = true;
}
else if (ID == 8) {
takeCard(User);
}
else if (ID == 9) {
// find target by deciding which region player clicked, then deal 1 dmg to it
}
else if (ID == 12) {
hasDoubleJump = true;
}
else if (ID == 13) {
hasTaunt = true;
spikyLevel = 2;
}
else if (ID == 14) {
initiateMinion(5, User);
}
else if (ID == 16) {
isInvincible = true;
}
else if (ID == 17) {
int randKoop = (rand() % 7) + 1;
switch (randKoop) {
case 1:
initiateMinion(74, User);
break;
case 2:
initiateMinion(75, User);
break;
case 3:
initiateMinion(76, User);
break;
case 4:
initiateMinion(77, User);
break;
case 5:
initiateMinion(78, User);
break;
case 6:
initiateMinion(79, User);
break;
case 7:
initiateMinion(81, User);
break;
}
}
else if (ID == 18) {
hasTaunt = true;
// Cant attack
}
else if (ID == 19) {
hasTaunt = true;
}
else if (ID == 20) {
for (int i; i < 5; i++) {
// Deal 1 damage to random enemy
}
}
else if (ID == 21) {
spikyLevel = 1;
}
else if (ID == 23) {
enrage = true;
}
else if (ID == 25) {
initiateMinion(80, User);
initiateMinion(80, User);
}
else if (ID == 27) {
//Take control of a minion with 2 or less attack
}
else if (ID == 29) {
// Deal 2 damage
}
}
*/
void putMinionStuff(int ID, int x, int y) {
	settextjustify(1, 1);
	setcolor(WHITE);
	drawImage(ID, x, y);
	int amountAdded = 0;
	int count = 0;
	int len;
	int descYAdjust;
	string descHolder[16];
	string nam = setName(ID);
	const char* name = nam.c_str();
	string desc = setAbilityText(ID);
	const char* description = desc.c_str();
	int mana = setManaCost(ID);
	string mana2 = to_string(mana);
	const char* manaCost = mana2.c_str();
	int att = setAttack(ID);
	string att2 = to_string(att);
	const char* attack = att2.c_str();
	int def = setDefense(ID);
	string def2 = to_string(def);
	const char* defense = def2.c_str();
	outtextxy(x + cardNameOffsetX, y + cardNameOffsetY, name);
	outtextxy(x + cardManaOffsetX, y + cardManaOffsetY, manaCost);
	outtextxy(x + cardAttackOffsetX, y + cardAttackOffsetY, attack);
	outtextxy(x + cardDefenseOffsetX, y + cardDefenseOffsetY, defense);
	if (desc.length() <= 16) {
		outtextxy(x + cardDescriptionOffsetX, y + cardDescriptionOffsetY, description);
	}
	else {
		len = desc.length();
		while (!(amountAdded == len)) {
			if (desc.length() >= 16) {
				for (int i = 0; i < desc.length(); i++) {
					if (desc[15 - i] == ' ') {
						descHolder[count] = desc.substr(0, 16 - i);
						amountAdded += descHolder[count].length();
						desc = desc.substr(16 - i, desc.length() - (16 - i));
						count++;
						i = desc.length();
					}
				}
			}
			else {
				descHolder[count] = desc;
				amountAdded += descHolder[count].length();
				count++;
			}
		}
		if (count % 2 == 1) {
			descYAdjust = (count - 1) / 2 * 11;//11 is text height
		}
		else {
			descYAdjust = (count / 2 - 1) * 11 + 6;//6 is approx half text height
		}
		for (int i = 0; i < count; i++) {
			description = descHolder[i].c_str();
			outtextxy(x + cardDescriptionOffsetX, y + cardDescriptionOffsetY - descYAdjust + 11 * i, description);
		}
	}
}
void putSpellStuff(int ID, int x, int y) {
	settextjustify(1, 1);
	drawImage(ID, x, y);
	int amountAdded = 0;
	int count = 0;
	int len;
	int descYAdjust;
	string descHolder[16];
	string nam = setName(ID);
	const char* name = nam.c_str();
	string desc = setAbilityText(ID);
	const char* description = desc.c_str();
	int mana = setManaCost(ID);
	string mana2 = to_string(mana);
	const char* manaCost = mana2.c_str();
	outtextxy(x + cardNameOffsetX, y + cardNameOffsetY, name);
	outtextxy(x + cardManaOffsetX, y + cardManaOffsetY, manaCost);
	if (desc.length() <= 16) {
		outtextxy(x + cardDescriptionOffsetX, y + cardDescriptionOffsetY, description);
	}
	else {
		len = desc.length();
		while (!(amountAdded == len)) {
			if (desc.length() >= 16) {
				for (int i = 0; i < desc.length(); i++) {
					if (desc[15 - i] == ' ') {
						descHolder[count] = desc.substr(0, 16 - i);
						amountAdded += descHolder[count].length();
						desc = desc.substr(16 - i, desc.length() - (16 - i));
						count++;
						i = desc.length();
					}
				}
			}
			else {
				descHolder[count] = desc;
				amountAdded += descHolder[count].length();
				count++;
			}
		}
		if (count % 2 == 1) {
			descYAdjust = (count - 1) / 2 * 11;//11 is text height
		}
		else {
			descYAdjust = (count / 2 - 1) * 11 + 6;//6 is approx half text height
		}
		for (int i = 0; i < count; i++) {
			description = descHolder[i].c_str();
			outtextxy(x + cardDescriptionOffsetX, y + cardDescriptionOffsetY - descYAdjust + 11 * i, description);
		}
	}
}
void drawImage(int ID, int x, int y) {
	switch (ID) {
	case 1:
		drawMinion(Mini_Goomba, x, y);
		break;
	case 2:
		drawMinion(Block, x, y);
		break;
	case 3:
		drawMinion(Goomba, x, y);
		break;
	case 4:
		drawMinion(Shy_Guy, x, y);
		break;
	case 5:
		drawMinion(Toad, x, y);
		break;
	case 6:
		drawMinion(Bill_Blaster, x, y);
		break;
	case 7:
		drawMinion(Fuzzy, x, y);
		break;
	case 8:
		drawMinion(Luma, x, y);
		break;
	case 9:
		drawMinion(Rocky_Wench, x, y);
		break;
	case 10:
		drawMinion(Cheep_Cheep, x, y);
		break;
	case 11:
		drawMinion(Green_Koopa, x, y);
		break;
	case 12:
		drawMinion(Para_Goomba, x, y);
		break;
	case 13:
		drawMinion(Pipe_Pirahna_Plant, x, y);
		break;
	case 14:
		drawMinion(Toadsworth, x, y);
		break;
	case 15:
		drawMinion(Yoshi_Egg, x, y);
		break;
	case 16:
		drawMinion(Boo, x, y);
		break;
	case 17:
		drawMinion(Bowser_Jr, x, y);
		break;
	case 18:
		drawMinion(Bowser_Statue, x, y);
		break;
	case 19:
		drawMinion(Koopatrol, x, y);
		break;
	case 20:
		drawMinion(Magikoopa, x, y);
		break;
	case 21:
		drawMinion(Pokey, x, y);
		break;
	case 22:
		drawMinion(Red_Koopa, x, y);
		break;
	case 23:
		drawMinion(Wiggler, x, y);
		break;
	case 24:
		drawMinion(Boomarang_Bro, x, y);
		break;
	case 25:
		drawMinion(Captain_Toad, x, y);
		break;
	case 26:
		drawMinion(Dry_Bones, x, y);
		break;
	case 27:
		drawMinion(Fawful, x, y);
		break;
	case 28:
		drawMinion(Goomba_Tower, x, y);
		break;
	case 29:
		drawMinion(Hammer_Bro, x, y);
		break;
	case 30:
		drawMinion(Lakitu, x, y);
		break;
	case 31:
		drawMinion(Sledge_Bro, x, y);
		break;
	case 32:
		drawMinion(Toadette, x, y);
		break;
	case 33:
		drawMinion(Cataquak, x, y);
		break;
	case 34:
		drawMinion(FireBro, x, y);
		break;
	case 35:
		drawMinion(Antasma, x, y);
		break;
	case 36:
		drawMinion(Goomba_King, x, y);
		break;
	case 37:
		drawMinion(Dry_Bowser, x, y);
		break;
	case 38:
		drawMinion(Honey_Queen, x, y);
		break;
	case 39:
		drawMinion(King_Boo, x, y);
		break;
	case 40:
		drawSpell(Fire_Flower, x, y);
		break;
	case 41:
		drawSpell(Hammer, x, y);
		break;
	case 42:
		drawSpell(Super_Mushroom, x, y);
		break;
	case 43:
		drawSpell(OneUp, x, y);
		break;
	case 44:
		drawSpell(Fused_Bombomb, x, y);
		break;
	case 45:
		drawSpell(Lightning, x, y);
		break;
	case 46:
		drawSpell(Marios_Cap, x, y);
		break;
	case 47:
		drawSpell(Super_Star, x, y);
		break;
	case 48:
		drawSpell(Whomp_Plomp, x, y);
		break;
	case 49:
		drawSpell(Castle, x, y);
		break;
	case 50:
		drawSpell(Dr_Mario_Pills, x, y);
		break;
	case 51:
		drawSpell(FLUDD, x, y);
		break;
	case 52:
		drawSpell(Metal_Cap, x, y);
		break;
	case 53:
		drawSpell(POW_Block, x, y);
		break;
	case 54:
		drawSpell(Warios_Bike, x, y);
		break;
	case 55:
		drawSpell(Question_Block, x, y);
		break;
	case 56:
		drawSpell(Damsel_in_Distress, x, y);
		break;
	case 57:
		drawSpell(Thwomp_Stomp, x, y);
		break;
	case 58:
		drawSpell(Blue_Shell, x, y);
		break;
	case 59:
		drawSpell(Fuzzy_Maddness, x, y);
		break;
	case 60:
		drawSpell(Gotta_Go_Fast, x, y);
		break;
	case 61:
		drawSpell(Haunted_Mansion, x, y);
		break;
	case 62:
		drawSpell(Koopalings_Mischief, x, y);
		break;
	case 63:
		drawSpell(Mega_Mushroom, x, y);
		break;
	case 64:
		drawSpell(LavaPool, x, y);
		break;
	case 65:
		drawSpell(Wassup_Bro, x, y);
		break;
	case 66:
		drawToken(Coin, x, y);
		break;
	case 67:
		drawToken(Ball, x, y);
		break;
	case 68:
		drawToken(Bat, x, y);
		break;
	case 69:
		drawToken(Bullet_Bill, x, y);
		break;
	case 70:
		drawToken(Lava_Bubble, x, y);
		break;
	case 71:
		drawToken(Ring, x, y);
		break;
	case 72:
		drawToken(Spiny, x, y);
		break;
	case 73:
		drawToken(Green_Shell, x, y);
		break;
	case 74:
		drawToken(Iggy, x, y);
		break;
	case 75:
		drawToken(Larry, x, y);
		break;
	case 76:
		drawToken(Lemmy, x, y);
		break;
	case 77:
		drawToken(Ludwig_Von_Koopa, x, y);
		break;
	case 78:
		drawToken(Morton, x, y);
		break;
	case 79:
		drawToken(Roy, x, y);
		break;
	case 80:
		drawToken(War_Toad, x, y);
		break;
	case 81:
		drawToken(Wendy, x, y);
		break;
	case 82:
		drawToken(Red_Shell, x, y);
		break;
	case 83:
		drawToken(Sonic, x, y);
		break;
	case 84:
		drawToken(Yoshi, x, y);
		break;
	}
}
void attackHero(Player hero, UserBoard minion1, OpponentBoard minion2) {// taunt, prob move to struct
	if (minion1.isAttacking) {
		hero.health -= minion1.attack;
	}
	else if (minion2.isAttacking) {
		hero.health -= minion2.attack;
	}
}
void attackMinion(UserBoard minion1, OpponentBoard minion2) {//taunt, prob move to struct
															 //hero attack is 0
	if (minion1.isAttacking) {
		minion1.setDefense(minion1.defense - minion2.attack);
		minion2.setDefense(minion2.defense - minion1.attack);
		minion1.setIsAttacking(false);
	}
	else if (minion2.isAttacking) {
		minion1.setDefense(minion1.defense - minion2.attack);
		minion2.setDefense(minion2.defense - minion1.attack);
		minion2.setIsAttacking(false);
	}
}
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode) {
	//set the graphics driver
	GrDriver = VGA; //800x600 by monitor
	GrMode = VGAMAX;//set graphics mode
	initgraph(&GrDriver, &GrMode, "");//start graphics
									  //check for problems
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{
		cout << "Error:" << ErrorCode;
	}
}