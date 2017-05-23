
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iomanip>
#include <ctime>
#include <string>
#include <winbgi.cpp>
#include <graphics.h>
#include <Windows.h> // Sleep()
#include <thread>
#include "VirtualKeys.h"
using namespace std;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);

int GrDriver, GrMode, ErrorCode;
int maxX, maxY, penColor; // max X and Y as well as penColor

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
int midx, midy;

bool isRunning = true;

int rCard;
int pHand;
int fpcard;
int spcard;
int tpcard;
int bHand;
int fbcard;
int sbcard;
int tbcard;
string realhand;
string realhand2;
string realhand3;
string realhand4;
string realhand5;
string realhand6;
int m, b, v;
int q,a, w, e, r;
int n = 200;

//char suit[] = { 3, 4, 5,6};
string facevalue[] = { "2", "3", "4", "5", "6", "7", "8",
"9", "10", "Jack", "Queen", "King", "Ace" };

int getcard() {

	int card=0;
	int cardvalue = rand() % 13;
	//int cardsuit = rand() % 4;

	facevalue[cardvalue];
	if (facevalue[cardvalue] == "2") {
		card = 2;
	}
	else if(facevalue[cardvalue] == "3") {
		card = 3;
	}
	else if (facevalue[cardvalue] == "4") {
		card = 4;
	}
	else if (facevalue[cardvalue] == "5") {
		card = 5;
	}
	else if (facevalue[cardvalue] == "6") {
		card = 6;
	}
	else if (facevalue[cardvalue] == "7") {
		card = 7;
	}
	else if (facevalue[cardvalue] == "8") {
		card = 8;
	}
	else if (facevalue[cardvalue] == "9") {
		card = 9;
	}
	else if (facevalue[cardvalue] == "10") {
		card = 0;
	}
	else if (facevalue[cardvalue] == "Jack") {
		card = 0;
	}
	else if (facevalue[cardvalue] == "Queen") {
		card = 0;
	}
	else if (facevalue[cardvalue] == "King") {
		card = 0;
	}
	else if (facevalue[cardvalue] == "Ace") {
		card = 1;
	}
	//card += suit[cardsuit];
	return card;
}

int startmenu(void)
{

	/* fill in bounded region */
	setfillstyle(1, 1);
	floodfill(2, 2, getmaxcolor());
	
	setbkcolor(1);
	setcolor(4);
	string t = "Baccarat";
	settextstyle(9, 0, 10);
	outtextxy(midx - 400, 100, t.c_str());
	putpixel(0, 0, 1);

	setbkcolor(0);
	setcolor(4);
	string s = "START";
	settextstyle(9, 0, 10);
	outtextxy(midx - 350, midy, s.c_str());
	putpixel(0, 0, 1);

	/* clean up */
	getch();
	cleardevice();
	return 0;

}
int colornumber() {
	//Gives number to card
	setcolor(4);
	setbkcolor(15);
	settextstyle(9, 0, 10);
	outtextxy(midx - 700, 200, realhand.c_str());
	Sleep(1000);
	outtextxy(midx + 200, 200, realhand3.c_str());
	Sleep(1000);
	outtextxy(midx - 400, 200, realhand2.c_str());
	Sleep(1000);
	outtextxy(midx + 500, 200, realhand4.c_str());
	Sleep(1000);
	outtextxy(midx + 500, 200, realhand4.c_str());
	return 0;
}
int thirdpcard() {
	a = midx - 550;
	w = 450;
	e = 650;
	r = 250;
	//Player third card
	setcolor(15);
	setbkcolor(0);
	bar(a, w, a + r, n + e);
	setcolor(15);
	rectangle(a, w, a + r, n + e);
	setcolor(15);
	bar(a, w, a + r, n + e);
	setcolor(0);
	rectangle(a, w, a + r, n + e);
	setcolor(0);
	rectangle(a, w, a + r, n + e);
	setcolor(0);
	rectangle(a, w, a + r, n + e);
	Sleep(500);
	if (realhand5 == "0") {
		realhand5 = "X";
	}
	setcolor(4);
	setbkcolor(15);
	settextstyle(9, 0, 10);
	outtextxy(midx - 550+10, 450+10, realhand5.c_str());
	return 0;
}
int thirdbcard() {
	a = midx - 550;
	w = 450;
	e = 650;
	r = 250;
	//banker third card
	a = a + 900;
	setcolor(15);
	setbkcolor(0);
	bar(a, w, a + r, n + e);
	setcolor(15);
	rectangle(a, w, a + r, n + e);
	setcolor(15);
	bar(a, w, a + r, n + e);
	setcolor(0);
	rectangle(a, w, a + r, n + e);
	setcolor(0);
	rectangle(a, w, a + r, n + e);
	setcolor(0);
	rectangle(a, w, a + r, n + e);
	Sleep(500);
	if (realhand6 == "0") {
		realhand6 = "X";
	}
	setcolor(4);
	setbkcolor(15);
	settextstyle(9, 0, 10);
	outtextxy(a+ 10, 450+ 10, realhand6.c_str());
	return 0;
}
int cardlayout() {

	//Player First Card
	a = midx - 700;
	w = 200;
	e = 350;
	r = 250;
	setcolor(15);
	bar(a, w, a + r, n + e);
	setcolor(15);
	rectangle(a, w, a + r, n + e);
	setcolor(15);
	bar(a, w, a + r, n + e);
	setcolor(15);
	rectangle(a, w, a + r, n + e);
	Sleep(500);
	//Player Second card
	int j;
	j = midx - 400;
	w = 200;
	e = 350;
	r = 250;
	setcolor(15);
	bar(j, w, j + r, n + e);
	setcolor(15);
	rectangle(j, w, j + r, n + e);
	Sleep(500);
	//Banker First Card

	m = midx + 200;

	b = 350;
	v = 250;
	setcolor(15);
	bar(m, n, m + v, n + b);
	setcolor(15);
	rectangle(m, n, m + v, n + b);

	Sleep(500);

	//Banker Second Card

	q = midx + 500;
	w = 200;
	e = 350;
	r = 250;
	setcolor(15);
	bar(q, w, q + r, n + e);
	setcolor(15);
	rectangle(q, w, q + r, n + e);

	Sleep(500);
	colornumber();
	return 0;
}

int gamestuff(void)
{

	/* fill in bounded region */

	floodfill(2, 2, getmaxcolor());

	setbkcolor(1);
	cleardevice();
	setcolor(4);
	string x = "Banker";
	settextstyle(9, 0, 10);
	outtextxy(midx + 200, 50, x.c_str());
	
	string q = "Player";
	settextstyle(9, 0, 10);
	outtextxy(midx - 700, 50, q.c_str());

	//Cardlayout


	//Chips
	setbkcolor(0);
	for (int i = 1; i < 50; i++) {
		//1
		setcolor(15);
		if (i > 2 && i < 35) {
			setcolor(15);
		}
		circle(midx + 800, maxY - 350, i);
		//5
		setcolor(4);
		if (i > 2 && i < 35) {
			setcolor(15);
		}
		circle((midx + 720),(maxY - (250)), i);
		//25
		setcolor(2);
		if (i > 2 && i < 35) {
			setcolor(15);
		}
		circle((midx + 650), (maxY - (135)), i);
		//100
		setcolor(0);
		
		if (i > 2 && i < 35) {
			setcolor(15);
		}
		circle((midx + 570), (maxY - 50), i);

	}
		//1
		setcolor(1);
		setbkcolor(15);
		string onec = "$1";
		settextstyle(9, 0, 4);
		outtextxy(midx + 780, maxY - 370, onec.c_str());
		
		//5
		setcolor(1);
		setbkcolor(15);
		string fivec = "$5";
		settextstyle(9, 0, 4);
		outtextxy(midx + 695, maxY - 270, fivec.c_str());

		//25
		setcolor(1);
		setbkcolor(15);
		string tfivec = "$25";
		settextstyle(9, 0, 3);
		outtextxy(midx + 625, maxY - 150, tfivec.c_str());
		//hundo
		setcolor(1);
		setbkcolor(15);
		string tfivecc = "$100";
		settextstyle(9, 0, 3);
		outtextxy(midx + 540, maxY - 60, tfivecc.c_str());

		//Buttons

		setcolor(2);
		setbkcolor(0);
		settextstyle(9, 0, 7);
		string bankertext = " Banker ";
		outtextxy(midx-140, midy, bankertext.c_str());
		outtextxy(midx-140, midy, bankertext.c_str());
		string playertext = " Player  ";
		outtextxy(midx - 140, midy +100, playertext.c_str());
		outtextxy(midx - 140, midy +100, playertext.c_str());
		string ttext = "    Tie    ";
		outtextxy(midx - 140, midy - 100, ttext.c_str());
		outtextxy(midx - 140, midy - 100, ttext.c_str());
	/* clean up 
	getch();
	cleardevice();
	*/
	return 0;

}


int main() {
	srand((unsigned int)time(NULL));
	//WINGBI

		gr_Start(GrDriver, GrMode, ErrorCode);
		maxX = getmaxx(); // From Graphics
		maxY = getmaxy(); // From Graphics
	
		midx = getmaxx() / 2;
		midy = getmaxy() / 2;
		startmenu();
		
	
	int numberofcards = 312;
	char choice;
	int bet;
	int bankroll = 1000;
	char winner;
start:

	gamestuff();
	cout << "Who do you think is going to win?(b/p/t)";
	cin >> choice;
	bett:
	cout << endl <<"How much would you like to bet?(Minimum $5 bet):         Bankroll: $"<< bankroll << endl;
	cin >> bet;
	if (bet < 5) {
		cout << "The minimum bet is $5" << endl;
		goto bett;
	}
	if (bet > bankroll) {
		cout << "You don't have enough money for that bet." << endl << "How about you win some?" << endl;
		goto bett;
	}
	bankroll = bankroll - bet;
	//PLAYER HAND
	pHand = 0;
	fpcard = getcard();
	spcard = getcard();
	
	//cout << "Player first card: " << fpcard << " " << "Player second card: " << spcard << endl;
	pHand = fpcard + spcard;
	if (pHand >= 10) {
		pHand = pHand - 10;
	}
	//cout << "PLAYER HAND" << "=" << pHand << endl;
	realhand = "";
	realhand =(fpcard) + '0';
	realhand2 = "";
	realhand2 = (spcard)+'0';
		
	//BANKER HAND
	bHand = 0;
	fbcard = getcard();
	sbcard = getcard();
	//cout << "Banker first card: " << fbcard << " " <<"Banker second card: " << sbcard << endl;
	bHand = fbcard + sbcard;

	if (bHand >= 10) {
		bHand = bHand - 10;
	}
	if (bHand >= 10) {
		bHand = bHand - 10;
	}
	//cout << "BANKER HAND" << "=" << bHand << endl;
	realhand3 = "";
	realhand3 = (fbcard)+'0';
	realhand4 = "";
	realhand4 = (sbcard)+'0';
	if (realhand == "0") {
		realhand = "X";
	}
	if (realhand2 == "0") {
		realhand2 = "X";
	}
	if (realhand3 == "0") {
		realhand3 = "X";
	}
	if (realhand4 == "0") {
		realhand4 = "X";
	}

	cardlayout();
	//NATURAL 8 OR 9
	bool natural = false;
	if (pHand == 8 || pHand == 9) {
		goto winner;
	}
	if (bHand == 8 || bHand == 9) {
		goto winner;
	}
	do {
		//PLAYER DRAW
		if (pHand == 1 || pHand == 2 || pHand == 3 || pHand == 4 || pHand == 5 || pHand == 10 && bHand != 8 || bHand != 9) {
		//	cout << "Player draws..." << endl;
			tpcard = getcard();
		//	cout << "Player third card: " << tpcard << endl;
			pHand = pHand + tpcard;
		}
		else if (pHand == 7) {
			goto bank;
		}
		if (pHand >= 10) {
			pHand = pHand - 10;
		}
		if (pHand >= 10) {
			pHand = pHand - 10;
		}
		//cout << "Player has: " << pHand << endl;
		realhand5 = "";
		realhand5 = (tpcard)+'0';
		thirdpcard();
		//BANKER DRAW
		bank:
		if (bHand == 3 && pHand != 8 || pHand != 9) {
			//cout << "Banker draws..." << endl;
			tbcard = getcard();
			//cout << "Banker third card: " << tbcard << endl;
			bHand = bHand + tbcard;
		}
		else if (bHand == 4 && pHand != 8 || pHand != 9 || pHand != 1 || pHand != 0) {
			//cout << "Banker draws..." << endl;
			tbcard = getcard();
			//cout << "Banker third card: " << tbcard << endl;
			bHand = bHand + tbcard;
		}
		else if (bHand == 5 && pHand != 8 || pHand != 9 || pHand != 1 || pHand != 0 || pHand != 2 || pHand != 3) {
			//cout << "Banker draws..." << endl;
			tbcard = getcard();
			//cout << "Banker third card: " << tbcard << endl;
			bHand = bHand + tbcard;
		}
		else if (bHand == 6 && pHand == 7 || pHand == 6) {
			//cout << "Banker draws..." << endl;
			tbcard = getcard();
			//cout << "Banker third card: " << tbcard << endl;
			bHand = bHand + tbcard;
		}
		else if (bHand == 0 || bHand == 1 || bHand == 2) {
			//cout << "Banker draws..." << endl;
			tbcard = getcard();
			//cout << "Banker third card: " << tbcard << endl;
			bHand = bHand + tbcard;
		}
		if (bHand >= 10) {
			bHand = bHand - 10;
		}
		if (realhand6 == "0") {
			realhand6 = "X";
		}
		realhand6 = "";
		realhand6 = (tbcard)+'0';
		//cout << "Banker has: " << bHand << endl;
		thirdbcard();
	} while (natural = false);
	//WINNER
	winner:
	if (pHand > bHand) {
		winner = 'p';
	//	cout << "Player WINS with " << pHand << endl;
		string qw = "Winner";
		settextstyle(9, 0, 10);
		outtextxy(midx - 700, 50, qw.c_str());
		Sleep(2000);
	}
	if (pHand < bHand) {
		winner = 'b';
		//cout << "Banker WINS with " << bHand << endl;
		string xw = "Winner";
		settextstyle(9, 0, 10);
		outtextxy(midx + 200, 50, xw.c_str());
		Sleep(2000);
	}
	if (pHand == bHand) {
		winner = 't';
		//cout << "TIE " << pHand << endl;
		string xt = " Tie ";
		settextstyle(9, 0, 10);
		outtextxy(midx + 200, 50, xt.c_str());
		string qt = " Tie ";
		settextstyle(9, 0, 10);
		outtextxy(midx - 700, 50, qt.c_str());
		Sleep(2000);
	}
	system("pause");
	//PAYOUT
	if (winner == 't' && choice == 't')
	{
		bankroll = bankroll + (bet * 9);
		cout << "You Won: $" << (bet * 9) << "                   Bankroll:  $" << bankroll << endl;
	}
	else if(winner == 't' && choice != 't') {
		cout << "Tie, No money won or lost" << endl;
	}
	if (choice == winner) {
		bankroll = bankroll + (bet *2);
		cout << "You Won: $" << (bet * 2) <<"	                 Bankroll:  $"<< bankroll << endl;
	}

	if(choice != winner) {
		cout << "You Lost: $" << (bet) << "                      Bankroll:  $" << bankroll << endl;

	}
	else if(winner == 't' && choice != 't') {

	}

	//LOOSE
	if (bankroll <= 4) {
		cout << "You do not have enough money!" << endl;
		return 0;
	}

	goto start;



	/*
	for (int i = 0; i < numberofcards; i++) {
		cout << "You drew a " << getcard() << endl;
	}
	*/
	system("pause");
}