/*Sunny Kim
Cal Garcia
Hersh Patel
Dots and Boxes
4/6/2017*/
#include<iostream>
#include<cmath>
#include<string>
#include<ctime>
#include<thread> // THREADS
#include<graphics.h>
#include<winbgi.cpp>
#include <vector>
#include<Windows.h>  // CURSOR
#include <stdio.h> 
#include<mmsystem.h>  // SOUND
#include <mciapi.h> // SOUND
#pragma comment(lib, "winmm.lib") // SOUND
using namespace std;
#pragma region GLOBALVARs
enum Player {P1, P2};
enum GAMESTATE {
	INTRO, GAME, CLOSING
};
int GrDriver, GrMode, ErrorCode;
int maxX, maxY, penColor; // max X and Y as well as penColor
bool isRunning = true;
bool changingStates = true;
bool cursorVisible;
int centerX, centerY;
BOOL curVis;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HCURSOR visible, hCur1, hCur3;
#pragma region Function_Prototypes
void gr_Start(int&, int&, int&); // Starts the graphics window
void getCursor(POINT &p); // uses struct POINT
bool MOUSE(int); // if mouse pressed
bool KEYBOARD(int); // if keyboard hit
void KEY_LISTENER(); // mouse/keyboard listner
void playSound(string, int);  // sound effect
void gameThread();
void drawGrid();
void switchPLAYER();
Player Turn = P1;
int SquaresLeft = 16;
#pragma endregion
INPUT_RECORD irInBuf;
GAMESTATE DotAndBoxes = INTRO;
struct PASS {

	int VirtualKey;
	POINT p;
	bool press;
	bool hold;
	void reset() {
		VirtualKey = NULL;
		p.x = NULL;
		p.y = NULL;
		press = false;
		hold = false;
	}
}global;
struct Rect{
	int top, left, right, bottom;
	int adjust;
	int color;
	bool isline;
	bool clicked;
	int check;
	void init(int x, int y) {
		left = x;
		top = y;
		right = left + 15;
		bottom = top + 15;
		isline = false;
		clicked = false;
		color = WHITE;
		draw();
		adjust = 0;
	}
	void initLine(int x, int y, int x2, int y2, int numberLine) {
		left = x; 
		right = x2;
		top = y;
		bottom = y2;
		isline = true;
		clicked = false;
		color = WHITE;
		draw();
		adjust = 0;
		check = numberLine;
		if (right - left == 80) {
			adjust = -15;
		}
	}
	void draw() {
		setcolor(color);
		if (!isline) {
			bar(left, top, right, bottom);
		}
		else {
			if (bottom - top == 80)
				line(left + 7, top, left + 7, bottom);
			else
				line(left, top + 7, right, top + 7);
		}
	}
	void drawWHITE() {
		setcolor(WHITE);
		if (bottom - top == 80)
			line(left + 7, top, left + 7, bottom);
		else
			line(left, top + 7, right, top + 7);
	}
	bool click(int i) {
		if (!clicked) {
			
				if (global.p.x >= left && global.p.x <= right) {
					if ((global.p.y + adjust) >= top && (global.p.y + adjust) <= bottom) {
						clicked = true;
						if (Turn == P1) {
							color = YELLOW;
						}
						else {
							color = MAGENTA;
						}
						cout << "HIT " << check << "@ " << i <<  endl;
						draw();
						
						return true;
					}

				}
		}
		return false;
	}
}corner, basic;

vector<Rect>drawnLines;
struct GAME {
	int left, top, right, bottom;
	int color;

	bool clicked[4];
	void init(int l, int t, int r, int b) {
		color = BLACK;
		clicked[0] = false; // left
		clicked[1] = false; // top 
		clicked[2] = false; // right 
		clicked[3] = false; // bottom
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
	bool contains(int i) {
		if (i == left) {
			clicked[0] = true;
			return true;
		}
		else if(i == top) {
			clicked[1] = true;
			return true;
		}
		else if (i == right){
			clicked[2] = true;
			return true;
		}
		else if (i == bottom) {
			clicked[3] = true;
			return true;
		}
		return false;
	}
	bool tick() {
		bool WIN = true;
		for (int i = 0; WIN && i < 4; i++)
			if (clicked[i] == false)
				WIN = false;

		if (WIN) {
			render();
		}

		return WIN;
	}
	void render() {
		if (Turn == P1) {
			color = YELLOW;
		}
		else {
			color = MAGENTA;
		}
		drawnLines[left].drawWHITE();
		drawnLines[top].drawWHITE();
		drawnLines[right].drawWHITE();
		drawnLines[bottom].drawWHITE();
		setcolor(color);
		SquaresLeft--;
		floodfill(drawnLines[left].right + (drawnLines[right].left - drawnLines[left].right) / 2, drawnLines[top].bottom + (drawnLines[bottom].top - drawnLines[top].bottom) / 2, WHITE);
	}
}sqr[16];
#pragma endregion
void main()
{

	srand(time(NULL));


	thread g(gameThread); // Thread definiton
	thread t(KEY_LISTENER);
	
	global.press = global.hold = false;
	t.join(); // thread t start
	g.join();
	
	return;
}

#pragma region Functions
void gr_Start(int&GrDriver, int&GrMode, int&ErrorCode)
{
	//set the graphics driver
	GrDriver = VGA; //800x600
					//set graphics mode
	GrMode = VGAMAX;
	//start graphics
	initgraph(&GrDriver, &GrMode, "");
	//check for problems
	ErrorCode = graphresult();
	if (ErrorCode != grOk)
	{
		cout << "Error:" << ErrorCode;
		//getch();
		//exit(1);
	}
}
void getCursor(POINT & p) {
	while (true)
		if (GetCursorPos(&p)) {
			if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
			{
				do {} while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0);
				return;
			}

			Sleep(45);
		}
}
bool MOUSE(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = MOUSE_EVENT;
		GetCursorPos(&global.p);
		global.press = true;
		int count = 0;
		do {
			if (count++ > 1400) {
				global.hold = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
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
		int count = 0;
		do {
			if (count++ > 200) {
				global.hold = true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		return true;
	}
	return false;
}
void KEY_LISTENER() {

	while (true) {
		if (MOUSE(VK_LBUTTON)) {
			cout << "Left Button\n";
			global.VirtualKey = VK_LBUTTON;
			global.press = true;
		}
		
		if (KEYBOARD(VK_LEFT)) {
			cout << "Left Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_RIGHT)) {
			cout << "Right Arrow\n";
			SetCursor(hCur3);
		}
		if (KEYBOARD(VK_UP)) {
			cout << "Up Arrow\n";
		
		}
		if (KEYBOARD(VK_DOWN)) {
			cout << "Down Arrow\n";
		
		}
	
		if (KEYBOARD(VK_ESCAPE)) {
			cout << "Escape Pressed\n";
			Sleep(1000);

			Sleep(500);
			return;
		}
		if (KEYBOARD(VK_RETURN))
		{
			cout << "Return Pressed\n";
		}
		if (KEYBOARD(VK_F1))
		{
			cout << "F1 Pressed \n";
			SetCursor(hCur1);

		}
		if (KEYBOARD(VK_SPACE)) {
			cout << "Spacebar Pressed \n";
		}
	
		// Room For More Ifs specified keys act in a specific way.
		// look through the VirtualKeys.h list to have other specific keys
	}

}
void playSound(string fileName, int duration) {
	if (fileName.substr(fileName.length() - 2) == "v") {
		PlaySound(TEXT(fileName.c_str()), NULL, SND_ASYNC);
		Sleep(duration);
		PlaySound(TEXT(fileName.c_str()), 0, 0);
		return;
	}
	string concat = "open " + fileName + " type mpegvideo alias MP3_Device";
	LPCSTR a = concat.c_str();
	mciSendString(a, NULL, 0, 0);

	mciSendString("play MP3_Device", NULL, 0, 0);
	Sleep(duration);
	mciSendString("stop MP3_Device", NULL, 0, 0);
	mciSendString("close MP3_Device", NULL, 0, 0);
}
struct Rules {
	int x;
	int	y;
	string rules = "***              Rules             ***";
	string line1 = "Take more boxes than your ";
	string line2 = "opponent. You move by     ";
	string line3 = "connecting two dots with a";
	string line4 = "line. When you place the  ";
	string line5 = "last 'wall' of a single   ";
	string line6 = "square  (box), the box is ";
	string line7 = "yours. The players move in";
	string line8 = "turn, but whenever a     ";
	string line9 = "player takes a box (s)he  ";
	string lineA = "must move again.         ";
	void init() {
		generaterules();
		draw();
	}
	void generaterules() {

		settextstyle(4, 0, 3);
		x = 180;
		y = 305;
		setcolor(WHITE);
	}

	void draw() {
		outtextxy(x, y, rules.c_str());
		outtextxy(x, y + 50, line1.c_str());
		outtextxy(x, y + 100, line2.c_str());
		outtextxy(x, y + 150, line3.c_str());
		outtextxy(x, y + 200, line4.c_str());
		outtextxy(x, y + 250, line5.c_str());
		outtextxy(x, y + 300, line6.c_str());
		outtextxy(x, y + 350, line7.c_str());
		outtextxy(x, y + 400, line8.c_str());
		outtextxy(x, y + 450, line9.c_str());
		outtextxy(x, y + 500, lineA.c_str());
	}
}rules;
struct textbox {
	int x, y;
	int width, length;
	void init() {
		generatebox();
		draw();
	}
	void generatebox() {

		x = 175;
		y = 300;
		width = 470;
		length = 550;
	}
	void draw() {
		rectangle(x, y, x + width, y + length);
	}
}txtbox;
struct Scoreboard {
	// SCOREBOARD
	//SCORE P1
	int x = 650;
	int y = 100;
	//SCORE P2
	int x2 = 1150;
	int y2 = 100;
	//P1
	int x3 = 620;
	int y3 = 40;
	//TURN
	int x4 = 805;
	int y4 = 40;
	//P2
	int x5 = 1120;
	int y5 = 40;
	//TURN ARROWS
	int x6 = 790;
	int y6 = 130;
	int x7 = 990;
	int y7 = 130;

	int score = 0;
	string player1 = "P1";
	string player2 = "P2";
	string turn = "TURN";
	string arrowL = "<<<";
	string arrowR = ">>>";
	string display = to_string(score);
	void init() {
		generateboard();
		draw();
	}

	void generateboard() {
		settextstyle(4, 0, 6);
		setcolor(WHITE);
	}
	void draw() {
		rectangle(440, 30, 1400, 200);
		rectangle(780, 120, 850, 160);
		rectangle(980, 120, 1050, 160);

		setcolor(WHITE);
		outtextxy(x, y, display.c_str());
		outtextxy(x2, y2, display.c_str());
		outtextxy(x4, y4, turn.c_str());;
		setcolor(14);
		outtextxy(x3, y3, player1.c_str());
		
		setcolor(5);
		settextstyle(4, 0, 6);
		outtextxy(x5, y5, player2.c_str());
		
		setcolor(15);
		settextstyle(4, 0, 6);
		putpixel(0, 0, 1);
		
		if (Turn == P1) {
			setcolor(BLACK);
			settextstyle(0, 0, 2);
			outtextxy(x7, y7, arrowR.c_str());
			setcolor(YELLOW);
			outtextxy(x6, y6, arrowL.c_str());
			
		}
		else {
			setcolor(BLACK);
			settextstyle(0, 0, 2);
			outtextxy(x6, y6, arrowL.c_str());
			setcolor(MAGENTA);
			outtextxy(x7, y7, arrowR.c_str());
		}
		setcolor(WHITE);
	}

}score;
void gameThread() {
	gr_Start(GrDriver, GrMode, ErrorCode); // initi of graphics window 
	centerX = getmaxx() / 2;
	centerY = getmaxy() / 2;
	maxX = getmaxx(); // From Graphics
	maxY = getmaxy(); // From Graphics

	//Sleep(300);

	while (isRunning) {
		switch (DotAndBoxes) {
		case INTRO:
			if (changingStates) {
				//Intro Page
				setbkcolor(0);
				cleardevice();
				int x = maxX;
				int y = 650;
				setcolor(5);
				string start = "Start: Press Spacebar";
				settextstyle(1, 0, 7);
				textheight(start.c_str());
				x = (x - textwidth(start.c_str())) / 2;
				outtextxy(x, y, start.c_str());

				string console = "(Created by Sunny Kim, Hersh Patel, Cal Garcia)";
				int cx = maxX;
				int cy = 850;
				setcolor(5);
				settextstyle(1, 0, 4);
				textheight(console.c_str());
				cx = (cx - textwidth(console.c_str())) / 2;
				outtextxy(cx, cy, console.c_str());

				string title = "DOTS & BOXES";
				int sx = maxX;
				int sy = 350;
				setcolor(14);
				settextstyle(1, 0, 8);
				textheight(title.c_str());
				sx = (sx - textwidth(title.c_str())) / 2;
				outtextxy(sx, sy, title.c_str());
				changingStates = false;
			}
			// WHEN SPACEBAR IS PRESSED
			if (global.press && global.VirtualKey == VK_SPACE) {
				DotAndBoxes = GAME;
				changingStates = true;
			}
			break;
		case GAME:
			if (changingStates) {
				cleardevice();


				while (!global.press);

				global.press = global.hold = false;
				cleardevice();

				rules.init();
				txtbox.init();
				score.init();



				drawGrid();

				while (true) {
					if (global.press == true && global.VirtualKey == VK_LBUTTON) {
						for (int i = 0; i < (int)drawnLines.size(); i++) {
							if (!drawnLines[i].clicked)
								if (drawnLines[i].click(i)) {
									/// CHECK TO SEE IF drawnLines[(the other three values)].clicked == true
									bool skip = false;
									for (int j = 0; j < 16; j++)
										if (sqr[j].contains(i)) {
											skip = sqr[j].tick();

										}
									if (!skip)
										switchPLAYER();
								}
						}
						global.reset();
					}
					if (SquaresLeft == 0) {
						cleardevice();
						drawGrid();
					}
					Sleep(134);
				}

				closegraph();
			}
		}
	}
}
void switchPLAYER() {
	if (Turn == P1)
		Turn = P2;
	else
		Turn = P1;
}
void drawGrid() {
	int sideways = 0;
	
	///sqr has to get value i.e. sqr[0].init(
		sqr[0].init(1, 0, 3, 9);
		sqr[1].init(3, 2, 5, 11);
		sqr[2].init(5, 4, 7, 13);
		sqr[3].init(7, 6, 8, 15);
		sqr[4].init(10, 9, 12, 18);
		sqr[5].init(12, 11, 14, 20);
		sqr[6].init(14, 13, 16, 22);
		sqr[7].init(16, 15, 17, 24);
		sqr[8].init(19, 18, 21, 27);
		sqr[9].init(21, 20, 23, 29);
		sqr[10].init(23, 22, 25, 31);
		sqr[11].init(25, 24, 26, 33);
		sqr[12].init(28, 27, 30, 36);
		sqr[13].init(30, 29, 32, 37);
		sqr[14].init(32, 31, 34, 38);
		sqr[15].init(34, 33, 35, 39);
		SquaresLeft = 16;
		drawnLines.clear();
		for (int j = 0; j < 5; j++)
			for (int i = 0; i < 5; i++)
		{
			corner.init(800 + (i * 95), 400 + (j * 95));
			if (i < 4) { // ALL SIDEWAYS LINES
				basic.initLine(815 + (i * 95), 400 + (j * 95), 800 + ((i + 1) * 95), 400 + 15 + (j * 95), sideways++);
				drawnLines.push_back(basic);
			}
			if (j < 4)
			{
				basic.initLine(800 + (i * 95), 400 + 15 + (j * 95), 815 + (i * 95), +400 + ((j + 1) * 95), sideways++);
				drawnLines.push_back(basic);
			}
		}
		

}

#pragma endregion
/// PROJECT