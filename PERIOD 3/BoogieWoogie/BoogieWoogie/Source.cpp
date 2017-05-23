//GROUP MEMBERS: Zahra Husrieh, Sarah Timinsky and Rhesa Sundar Singh
//3rd Period 
#include <iostream>
#include<iomanip>
#include<chrono>
#include <winbgi.cpp>
#include <graphics.h>
#include <ctime>
#include <vector>
#include <thread>
#include <Windows.h>
#include <string>
#include "VirtualKeys.h"//file made by us 
#pragma region Function
using namespace std;
bool KEYBOARD(int);
INPUT_RECORD irInBuf;
int maxX, maxY, ErrorCode, GrDriver, GrMode;
void drawpoly(int num, int *polypoints);
void fillpoly(int num, int *polypoints);
enum Direction { LEFT, DOWN, RIGHT, UP };
enum COLUMN { RED_COL, YELLOW_COL, GREEN_COL, BLUE_COL };
const int UNIT = 20;
int COLUMNSHIFT = UNIT * 33;
int colcolor = 0;

	bool UPhit = false;
	bool DOWNhit = false;
	bool RIGHThit = false;
	bool LEFThit = false;
	int y = 0; 


struct ARROW {
	Direction points;
	int X;
	int Y;
	int dXCoors[7];
	int dYCoors[7];
	int color;
	int colcolor;
	void init(Direction arrow, COLUMN col) {
		points = arrow;
		color = 15;
		Y = 0;
		X = 0;
		switch (col) {
		case BLUE_COL:
			colcolor = BLUE;
			break;
		case GREEN_COL:
			colcolor = GREEN;
			break;
		case YELLOW_COL:
			colcolor = YELLOW;
			break;
		case RED_COL:
			colcolor = RED;
			break;
		}
		switch (col) {
		case BLUE_COL:
			X += 8 * UNIT;
		case GREEN_COL:
			X += 8 * UNIT;
		case YELLOW_COL:
			X += 8 * UNIT;
		case RED_COL:
			X += COLUMNSHIFT;
		}
		// creates a list of the change in the X and Y as an array
		for (int i = 0; i < 7; i++) {
			dXCoors[i] = dYCoors[i] = UNIT;
			// BASELINE REFERENCE EVERYTHING IN TERMS OF UNIT
		}
		switch (arrow) {
			/// EVERY dXCoor[0] is one unit shifted so any one unit shifts are unnecessary to express
		case LEFT:
#pragma region LEFT
			// skipped
			dYCoors[0] *= 4;
			dXCoors[1] *= 3;
			// skipped
			dXCoors[2] *= 3;
			dYCoors[2] *= 3;
			dXCoors[3] *= 7;
			dYCoors[3] *= 3;
			dXCoors[4] *= 7;
			dYCoors[4] *= 5;
			dXCoors[5] *= 3;
			dYCoors[5] *= 5;
			dXCoors[6] *= 3;
			dYCoors[6] *= 7;
#pragma endregion
			break;
		case DOWN:
#pragma region DOWN
			// skipped
			dYCoors[0] *= 5;
			dXCoors[1] *= 3;
			dYCoors[1] *= 5;
			dXCoors[2] *= 3;
			dYCoors[2] *= 2;
			dXCoors[3] *= 5;
			dYCoors[3] *= 2;
			dXCoors[4] *= 5;
			dYCoors[4] *= 5;
			dXCoors[5] *= 7;
			dYCoors[5] *= 5;
			dXCoors[6] *= 4;
			dYCoors[6] *= 7;
#pragma endregion
			break;
		case RIGHT:
#pragma region RIGHT
			// skipped
			dYCoors[0] *= 3;
			dXCoors[1] *= 5;
			dYCoors[1] *= 3;
			dXCoors[2] *= 5;
			// skipped
			dXCoors[3] *= 7;
			dYCoors[3] *= 4;
			dXCoors[4] *= 5;
			dYCoors[4] *= 7;
			dXCoors[5] *= 5;
			dYCoors[5] *= 5;
			// skipped
			dYCoors[6] *= 5;
#pragma endregion
			break;
		case UP:
#pragma region UP
			// skipped
			dYCoors[0] *= 3;
			dXCoors[1] *= 4;
			// skipped
			dXCoors[2] *= 7;
			dYCoors[2] *= 3;
			dXCoors[3] *= 5;
			dYCoors[3] *= 3;
			dXCoors[4] *= 5;
			dYCoors[4] *= 7;
			dXCoors[5] *= 3;
			dYCoors[5] *= 7;
			dXCoors[6] *= 3;
			dYCoors[6] *= 3;
#pragma endregion
			break;
		}
		render();
	}
	void render() {
		setcolor(color);
		for (int i = 0; i < 7; i++) {
			line(X + dXCoors[i], Y + dYCoors[i], X + dXCoors[(i + 1) % 7], Y + dYCoors[(i + 1) % 7]);

		}
		//putpixel(X + 4*UNIT, Y + 4*UNIT, color);
		floodfill(X + 4 * UNIT, Y + 4 * UNIT, color);
	}
	void remove() {
		if ((Y + 7 * UNIT + 1) < 850) {
			setcolor(BLACK);
			bar(X - 1, Y - 1, X + 7 * UNIT + 1, Y + 7 * UNIT + 1);
		}
		else {
			setcolor(BLACK);
			for (int i = 0; i < 7; i++) {
				line(X + dXCoors[i], Y + dYCoors[i], X + dXCoors[(i + 1) % 7], Y + dYCoors[(i + 1) % 7]);

			}
			floodfill(X + 4 * UNIT, Y + 4 * UNIT, BLACK);
		}
	}
	void tick() {
		remove();
		Y += 8;
	}
	bool onScreen() {
		return Y + (4*UNIT) < (maxY -100);
	}

}curr;

struct LINE{
	int x1 = 550;
	int x2 = 1400;
	int y1 = 850;
	int y2 = 850;
	int linecolor = 15;
	void render(){
		setcolor(linecolor);
		line(x1, y1, x2, y2);
	}
}line1;
struct CIRCLE {
	bool POINTLOSS; 
	bool POINTGAIN; 
	int x; 
	int y; 
	int radius; 
	int circolor; 
	void circdraw1() {
		x = 750;
		y = 925;
		radius = 70; 
		circolor = 4; 
		setcolor(circolor);
		fillellipse(x, y, radius,radius);  
	}
	void circdraw2() {
		radius = 70;
		x = 900;
		y = 925;
		circolor = 14;
		setcolor(circolor);
		fillellipse(x, y, radius, radius);
	}
	void circdraw3() {
		radius = 70;
		x = 1050;
		y = 925; 
		circolor = 2;
		setcolor(circolor);
		fillellipse(x, y, radius, radius);
	}
	void circdraw4() {
		radius = 70;
		x = 1200; 
		y = 925; 
		circolor = 1;
		setcolor(circolor);
		fillellipse(x, y, radius, radius);
	}
}circ1, circ2, circ3, circ4;

struct KEYS
{
	int VirtualKey;
	bool press;
	bool hold;
	POINT p;
}global;
struct DESIGNarrow {
	int x1;
	int y1;
	int x2;
	int y2;
	int ARROWcol; 

	void ARROW1() {//UP
		ARROWcol = RED; 
		setcolor(ARROWcol);
		bar(1560, 150, 1640, 290);
		int points[] = { 1600, 60, 1660, 150, 1540, 150, 1600, 60 };
		drawpoly(4, points);
		fillpoly(4, points);
	}
	void ARROW2() {//RIGHT
		ARROWcol = BLUE;
		setcolor(ARROWcol);
		bar(1659, 390, 1799, 310);
		int points[] = { 1890, 350, 1799, 410, 1799, 290, 1890, 350 };
		drawpoly(4, points);
		fillpoly(4, points);
	}
	void ARROW3() {//LEFT
		ARROWcol = YELLOW;
		setcolor(ARROWcol);
		bar(1400, 390, 1540, 310);
		int points[] = { 1310, 350, 1400, 410, 1400, 290, 1310, 350 };
		drawpoly(4, points);
		fillpoly(4, points);
	}
	void ARROW4() {//DOWN
		ARROWcol = GREEN; 
		setcolor(ARROWcol);
		bar(1560, 409, 1640, 543);
		int points[] = { 1600, 640, 1540, 543, 1660, 543, 1600, 640 };
		drawpoly(4, points);
		fillpoly(4, points);
	
	
	}
	
	






}AUP,ARIGHT,ALEFT,ADOWN;
struct DESIGNCIRC {
	int x;
	int y;
	int radius;
	int circolor;
	void designCIRC() {
		x = 1600;
		y = 350;
		radius = 52.5;
		circolor = 15;
		setcolor(circolor);
		fillellipse(x, y, radius, radius);
	}
}circleDES;
bool KEYBOARD(int VirtualKeys) {
	if ((GetAsyncKeyState(VirtualKeys) & 0x8000) != 0)
	{
		irInBuf.EventType = KEY_EVENT;
		global.press = true;
		global.VirtualKey = VirtualKeys;
		int count = 0;
		do {
			if (count++ > 200) { 
				global.hold = true;
			}
		} while ((GetAsyncKeyState(VirtualKeys) & 0x8000) != 0);
		return true;
	}
	return false;
}


 
	
void gr_Start(int &GrDriver, int &GrMode, int &ErrorCode) {
	GrDriver = VGA; //1920 x 1080
	GrMode = VGAMAX;//set graphics mode
	initgraph(&GrDriver, &GrMode, "");//start graphics
									  //check for problems
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{
		cout << "Error:" << ErrorCode;
	}
	else {
		maxX = getmaxx();
		maxY = getmaxy();
	}
}
vector<ARROW> visual;
void KEYLISTENER();
void game();
void main() {
	srand((unsigned int)time(NULL));
	gr_Start(GrDriver, GrMode, ErrorCode);

	//////////////////////////////////////////////TITLE SCREEN\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	//Design
	circleDES.designCIRC();
	AUP.ARROW1(); 
	ADOWN.ARROW4();
	ARIGHT.ARROW2();
	ALEFT.ARROW3();
	//////
	
	settextstyle(3, 0, 20);
	//B
	setcolor(15);
	moveto(535, 350);
	outtext("B");
	//O
	setcolor(15);
	moveto(650, 350);
	outtext("O");
	//P
	setcolor(15);
	moveto(780, 350);
	outtext("P");


	//B
	setcolor(5);
	moveto(620, 520);
	outtext("B");
	//E
	setcolor(4);
	moveto(730, 520);
	outtext("E");
	//B
	setcolor(14);
	moveto(835, 520);
	outtext("B");
	//O
	setcolor(2);
	moveto(950, 520);
	outtext("O");
	//P
	setcolor(3);
	moveto(1080, 520);
	outtext("P");

	settextstyle(8, 0, 4);
	setcolor(15);
	moveto(400, 850);
	outtext("Press the corresponding arrows when they move to the circle");
	moveto(275, 900);
	outtext("Pressing the arrow before it reaches the circle will cause a loss of points");
	moveto(700, 950);
	outtext("Please wait 5 seconds...");
	moveto(700, 800);
	outtext("PRESS ENTER TO EXIT GAME");

	Sleep(5000);
	cleardevice();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	thread listener(KEYLISTENER);
	thread ddr(game);
	listener.join();
	ddr.join();
}


void game() {
	int CURRENTscore = 0;
	int NEWscore = 0;
	int GREATpoint = 10;
	int LOSEpoint = 10;
	while (true) {
		int percent = rand() % 8934;
		if (percent % 4 == 0) {
			percent = rand() % 4;
			Direction point;
			percent = rand() % 50;
			switch (percent) {
			case 0:
				point = LEFT;
				curr.init(point, RED_COL);
				visual.push_back(curr);
				break;
			case 1:
				point = UP;
				curr.init(point, YELLOW_COL);
				visual.push_back(curr);
				break;
			case 2:
				point = DOWN;
				curr.init(point, GREEN_COL);
				visual.push_back(curr);
				break;
			case 3:
				point = RIGHT;
				curr.init(point, BLUE_COL);
				visual.push_back(curr);
				break;
			}
			line1.render();
			circ1.circdraw1();
			circ2.circdraw2();
			circ3.circdraw3();
			circ4.circdraw4();
			
		}
		/*bool ArrowFill;
		if (ArrowFill = true) {
			setfillstyle(1, GREEN);
			floodfill(curr.X + 4 * UNIT, curr.Y + 4 * UNIT, color);
		}
		bool ArrowFillR;
		if (ArrowFillR = true) {
			setfillstyle(1, RED);
			floodfill(curr.X + 4 * UNIT, curr.Y + 4 * UNIT, color);
		}*/

		for (int i = 0; i < (int)visual.size(); i++) {
			visual.at(i).tick();
			if (!visual.at(i).onScreen()) {
				visual.erase(visual.begin() + i);
				i--;
			}
			else {
				visual.at(i).render();
			}
		}
		if (global.press && (int)visual.size() > 0) {


			if (visual.at(0).points == UP && global.VirtualKey == VK_UP && visual.at(0).Y > 800) {
				visual.at(0).color = GREEN;
				
				visual.at(0).render();
				visual.erase(visual.begin() + 0, visual.begin() + 1);
				CURRENTscore = GREATpoint + CURRENTscore;
				NEWscore = CURRENTscore; 
				cout << "GREAT!..." << "New Score: " << NEWscore << endl;
				

			}
			else if (visual.at(0).points == DOWN && global.VirtualKey == VK_DOWN  && visual.at(0).Y > 800) {
				visual.at(0).color = GREEN;
				;
				visual.at(0).render();
				visual.erase(visual.begin() + 0, visual.begin() + 1);
				CURRENTscore = GREATpoint + CURRENTscore;
				NEWscore = CURRENTscore;
				cout << "GREAT!..." << "New Score: " << NEWscore  << endl;

			}
			else if (visual.at(0).points == LEFT && global.VirtualKey == VK_LEFT && visual.at(0).Y > 800) {
				visual.at(0).color = GREEN;
				;
				visual.at(0).render();
				visual.erase(visual.begin() + 0, visual.begin() + 1);
				CURRENTscore = GREATpoint + CURRENTscore;
				NEWscore = CURRENTscore;
				cout << "GREAT!..." << "New Score: " << NEWscore  << endl;

			}
			else if (visual.at(0).points == RIGHT && global.VirtualKey == VK_RIGHT && visual.at(0).Y > 800) {
				visual.at(0).color = GREEN;
				;
				visual.at(0).render(); 
				visual.erase(visual.begin() + 0, visual.begin() + 1);
				CURRENTscore = GREATpoint + CURRENTscore;
				NEWscore = CURRENTscore;
				cout << "GREAT!..." << "New Score: " << NEWscore << endl;

			}
			else if (visual.at(0).points == UP && global.VirtualKey == VK_UP &&visual.at(0).Y < 799) {
					visual.at(0).color = RED;
					;
					CURRENTscore = CURRENTscore-LOSEpoint;
					NEWscore = CURRENTscore;
					cout << "MISSED!..." << "New Score: " << NEWscore << endl;
				}
			 else if (visual.at(0).points == DOWN && global.VirtualKey == VK_DOWN &&visual.at(0).Y < 799) {
					visual.at(0).color = RED;
					;
					CURRENTscore = CURRENTscore - LOSEpoint;
					NEWscore = CURRENTscore;
					cout << "MISSED!..." << "New Score: " << NEWscore<< endl;

				}
			 else if (visual.at(0).points == LEFT && global.VirtualKey == VK_LEFT &&visual.at(0).Y < 799) {
					visual.at(0).color = RED;
					;
					CURRENTscore = CURRENTscore - LOSEpoint;
					NEWscore = CURRENTscore;
					cout << "MISSED!..." << "New Score: " << NEWscore  << endl;

				}
			 else if (visual.at(0).points == RIGHT && global.VirtualKey == VK_RIGHT &&visual.at(0).Y < 799) {
					visual.at(0).color = RED;
					;
					CURRENTscore = CURRENTscore - LOSEpoint;
					NEWscore = CURRENTscore;
					cout << "MISSED!..." << "New Score: " << NEWscore << endl;
				}
			 
	
			 //////////////////////////////////////////////////////////////

			 
			 rectangle(100, 250, 450, 450);
			 settextstyle(8, 0, 8);
			 string CSCORE = to_string(NEWscore);
			 outtextxy(150, 300, CSCORE.c_str());
			 int RECW = WHITE;
			 int RECG = GREEN;
			 int RECR = RED; 			 													//SCOREBOX
			 if (NEWscore = CURRENTscore) {
				 setcolor(RECW);
			 }
			 if (CURRENTscore = CURRENTscore + GREATpoint) {
				 setcolor(RECG);
			 }
			 if (CURRENTscore = CURRENTscore - LOSEpoint) {
				 setcolor(RECR);
			 }
			 if (NEWscore > -100 && NEWscore < 100) {
				 setcolor(BLACK);
				 bar(290, 300, 350, 375);
			 }
			 ////////////////////////////////////////////////////////
			 while (CURRENTscore <= -1000 || CURRENTscore >= 100) {
				 cleardevice();
				 if (CURRENTscore < 0) {
					 setbkcolor(BROWN);
					 cleardevice();
					 setcolor(WHITE);
					 settextstyle(3, 0, 100);
					 moveto(435, 440);
					 outtext("YOU LOSE :( ");
					 settextstyle(2, 0, 50);
					 moveto(475, 650);
					 outtext("YOUR FINAL SCORE: ");
					 outtextxy(1025, 650, CSCORE.c_str());
					 moveto(475, 950);
					 outtext("GAME WILL RESTART IN 5 SECONDS");
					 Sleep(5000);
					 cleardevice();
					 setbkcolor(BLACK);
					 cleardevice();
					 cout << "RESTART" << endl;
					 return game();
				 }
				 if (CURRENTscore >= 0) {
					 setbkcolor(LIGHTBLUE);
					 cleardevice();
					 setcolor(DARKGRAY);
					 settextstyle(3, 0, 100);
					 moveto(445, 440);
					 outtext("YOU WIN :) ");
					 settextstyle(2, 0, 50);
					 moveto(475, 650);
					 outtext("YOUR FINAL SCORE: ");
					 outtextxy(1025, 650, CSCORE.c_str());
					 moveto(475, 950);
					 outtext("GAME WILL RESTART IN 5 SECONDS");
					 Sleep(5000);
					 cleardevice();
					 setbkcolor(BLACK);
					 cleardevice();
					 cout << "RESTART" << endl;
					 return game();
				 }
			 }
			 while (KEYBOARD(VK_RETURN)) {
				 if (global.VirtualKey == VK_RETURN && CURRENTscore < 0) {
					 setbkcolor(BROWN);
					 cleardevice();
					 setcolor(WHITE);
					 settextstyle(3, 0, 100);
					 moveto(435, 440);
					 outtext("YOU LOSE :( ");
					 settextstyle(2, 0, 50);
					 moveto(475, 650);
					 outtext("YOUR FINAL SCORE: ");
					 outtextxy(1025, 650, CSCORE.c_str());
					 moveto(475, 950);
					 outtext("GAME WILL RESTART IN 5 SECONDS");
					 Sleep(5000);
					 cleardevice();
					 setbkcolor(BLACK);
					 cleardevice();
					 cout << "RESTART" << endl;
					 return game();
				 }
				 if (global.VirtualKey == VK_RETURN && CURRENTscore >= 0) {
					 setbkcolor(LIGHTBLUE);
					 cleardevice();
					 setcolor(DARKGRAY);
					 settextstyle(3, 0, 100);
					 moveto(445, 440);
					 outtext("YOU WIN :) ");
					 settextstyle(2, 0, 50);
					 moveto(475, 650);
					 outtext("YOUR FINAL SCORE: ");
					 outtextxy(1025, 650, CSCORE.c_str());
					 moveto(475, 950);
					 outtext("GAME WILL RESTART IN 5 SECONDS");
					 Sleep(5000);
					 cleardevice();
					 setbkcolor(BLACK);
					 cleardevice();
					 cout << "RESTART" << endl;
					 return game();
				 }
			 }
			global.press = false;
		}
		Sleep(23);
	}
	}

	/*void RESTART() {
		if (CURRENTscore <= -500 || CURRENTscore >= 70) {
			return game();
		}
	}
	*/

void KEYLISTENER() {
	while (true) {
		if (KEYBOARD(VK_UP)) {
			cout << "UP Key Pressed \n";
			global.press = true;
			global.VirtualKey = VK_UP;
		}
		if (KEYBOARD(VK_DOWN)) {
				cout << "DOWN Key Pressed \n";
				global.press = true;
				global.VirtualKey = VK_DOWN;
		}
		if (KEYBOARD(VK_LEFT)) {
				cout << "LEFT Key Pressed \n";
				global.press = true;
				global.VirtualKey = VK_LEFT;
		}
		if (KEYBOARD(VK_RIGHT)) {
				cout << "RIGHT Key Pressed \n";
				global.press = true;
				global.VirtualKey = VK_RIGHT;
		}
		if (KEYBOARD(VK_RETURN)) {
			cout << "ENTER Key Pressed \n";
			global.press = true;
			global.VirtualKey = VK_RETURN; 
		}
		Sleep(10);
	}
				}






