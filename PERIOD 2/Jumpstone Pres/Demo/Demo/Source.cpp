#include <iostream>
#include <string>
#include <ctime>
#include <string>
#include <Windows.h>
#include <cmath>
#include "Pixel.h"
#include "Cardback.h"
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
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
string setName(int ID);
int setAttack(int ID);
int setDefense(int ID);
int setManaCost(int ID);
void putMinionStuff(int ID, int x, int y);
void renderCard();
void putSpellStuff(int ID, int x, int y);
void drawImage(int ID);
const int x = 862;
const int y = 386;
string setAbilityText(int ID);
void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);
	renderCard();
	system("pause");
	return;
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
void renderCard() {
	int ID;
	bool shownCard[84];
	int count = 0;
	for (int i = 0; i < 84; i++) {
		shownCard[i] = false;
	}
	while (true) {
		ID = rand() % 84 + 1;
		if (count == 84) {
			count = 0;
			for (int i = 0; i < 84; i++) {
				shownCard[i] = false;
			}
		}
		else {
			if (shownCard[ID - 1]) {

			}
			else {
				cleardevice();
				setcolor(WHITE);
				bar(0, 0, getmaxx(), getmaxy());
				settextjustify(1, 1);
				if ((ID >= 1 && ID <= 39) || (ID >= 67 && ID <= 72) || (ID >= 74 && ID <= 81) || (ID >= 83 && ID <= 84)) {
					drawMinionCardback(x, y);
					putMinionStuff(ID, x, y);
				}
				else if ((ID >= 40 && ID <= 65) || ID == 66 || ID == 73 || ID == 82) {
					drawSpellCardback(x, y);
					putSpellStuff(ID, x, y);
				}
				shownCard[ID - 1] = true;
				count++;
				Sleep(5000);
			}

		}
	}
}
void putMinionStuff(int ID, int x, int y) {
	drawImage(ID);
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
	drawImage(ID);
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
void drawImage(int ID) {
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