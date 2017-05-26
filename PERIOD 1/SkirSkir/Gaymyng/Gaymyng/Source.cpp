#include <conio.h>
#include<cmath>
#include<string>
#include<ctime>
#include<vector>
#include<thread> // THREADS
#include<Windows.h>  // CURSOR
#include<stdio.h> 
#include "Pixel.h"
#include<mmsystem.h>  // SOUND
#include <mciapi.h> // SOUND
#include"VirtualKeys.h" // for the keyboard listener
#pragma comment(lib, "winmm.lib") /// WAV also maybe MP3
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;
void gr_Start(int &GrDriver, int&GrMode, int&ErrorCode);
int GrDriver, GrMode, ErrorCode;
int maxX, maxY, penColor; // max X and Y as well as penColor
INPUT_RECORD irInBuf;
HCURSOR visible, hCur1, hCur3;
void playSound(string, int);
void timer(int);
void swiggeroo();
bool playmusic = true;
bool KEYBOARD(int);
bool GameRunning = true; // for now
int Playing = 0; // for now
void PLAYER();
enum DIRECTION { UP, RIGHT, DOWN, LEFT, SELECT};
string b = "";
int xerino = 850;
int yerino = 800;
int logox = (getmaxx()) / 2;
int logoy = (getmaxy()) / 2;
struct texterino {
	int x, y, font, direction, charsize, color, left, top, right, bottom;
	int barx1, barx2, bary1, bary2, varx1, varx2;
	int car = 10;
	int carx, cary;
	void init() {
		color = 15;

	}

	void lanes() {
		barx1 = 833;
		bary1 = -300;
		barx2 = 843;
		bary2 = 0;
		varx1 = barx1 + 233;
		varx2 = barx2 + 233;
	}
	void carGenerator() {
		car = rand() % 5;
		cout << "Car Type: " << car << endl;
		carx = rand() % 579 + 600;
		cary = 0;
		if (car == 1) {
			CARTYPE vehicle = REDCAR;
			draw(carx, cary, REDCAR);
		}
		if (car == 2) {
			CARTYPE vehicle = GREENCAR;
			draw(carx, cary, GREENCAR);
		}if (car == 3) {
			CARTYPE vehicle = REDTRUCK;
			draw(carx, cary, REDTRUCK);
		}if (car == 4) {
			CARTYPE vehicle = BLUETRUCK;
			draw(carx, cary, BLUETRUCK);
		}
	}
	void bkg() {
		left = 600;
		top = 0;
		right = 1300;
		bottom = 1100;
	}
	void menu() {
		x = 850;
		y = 900;
		font = 2;
		direction = 0;
		charsize = 10;
	}
	void fueltext() {
		x = 1500;
		y = 800;
		font = 2;
		direction = 0;
		charsize = 10;

	}
	void drawstartup() {
		setcolor(BLACK);
		draw(logox + 625, logoy + 200, LOGO);

	}
	void drawfuel() {
		setcolor(color);
		settextstyle(font, direction, charsize);
		outtextxy(x, y, b.c_str());
	}
	void drawmenu() {
		string a = "Level 1";
		setcolor(color);
		settextstyle(font, direction, charsize);
		outtextxy(x, y, a.c_str());
	}
	void drawbkg() {
		setcolor(DARKGRAY);
		setbkcolor(DARKGRAY);
		bar(left, top, right, bottom);
	}
	void drawlanes() {
		setcolor(WHITE);
		bar(barx1, bary1, barx2, bary2);
		bar(varx1, bary1, varx2, bary2);
	}
	void drawlanes2() {
		setcolor(DARKGRAY);
		bar(barx1, bary1, barx2, bary2);
		bar(varx1, bary1, varx2, bary2);
	}
	
}kachow;
struct PASS {

	int VirtualKey;
	int move;
	bool press;
	bool hold;
	
	void reset() {
	press = false;
	hold = false;
	}

}playerInput;

struct Point {
	int X;
	int Y;
	void init(int x, int y) {
		X = x;
		Y = y;
	}
};
struct Rect {
	bool overlap;
	int x, y, h, w;
	Point TopLeft, BottomRight;
	int bColor, outline;
	void construct(int xc, int yc, int r) {
		TopLeft.init(xc - r, yc - r);
		BottomRight.init(xc + r, yc + r);
	}
	void init() {
		overlap = false;
		x = kachow.carx;
		y = kachow.cary;
		w = CAR_Width;
		h = CAR_Height;
		bColor = rand() % 15 + 1;
		TopLeft.init(x, y);
		BottomRight.init(x + w, y + h);
		oL();
	}
	void tick() {
		oL();
	}
	void render() {
		setcolor(bColor);
		bar(x, y, x + w, y + h);
		setcolor(outline); 
		rectangle(x, y, x + w, y + h);
	}
	void oL() {
		do {
			outline = rand() % 15 + 1;
		} while (outline != bColor);
	}
	bool intersect(Rect check) {
		/*
		TopLeft(x1,y1)   (x2,y1)
		___________________
		| A				 B|
		|				  |
		|				  |
		|				  |
		|				  |
		|_D______________C|
		(x1,y2)			BottomRight(x2,y2)
		*/
		Point corner[4];
		corner[0] = check.TopLeft;
		corner[1].init(check.BottomRight.X, check.TopLeft.Y);
		corner[2].init(check.TopLeft.X, check.BottomRight.Y);
		corner[3] = check.BottomRight;

		for (int i = 0; i < 4; i++) {
			if (corner[i].X >= TopLeft.X && corner[i].X <= BottomRight.X) {
				if (corner[i].Y >= TopLeft.Y && corner[i].Y <= BottomRight.Y)
					return true;
			}
			if (i % 2 == 0) {
				while (corner[i].X <= corner[i + 1].X) {
					corner[i].X += 1;
					if (corner[i].X >= TopLeft.X && corner[i].X <= BottomRight.X) {
						if (corner[i].Y >= TopLeft.Y && corner[i].Y <= BottomRight.Y)
							return true;
					}
				}
			}
			else if (i == 1) {
				while (corner[i].Y <= corner[i + 1].Y) {
					corner[i].Y += 1;
					if (corner[i].X >= TopLeft.X && corner[i].X <= BottomRight.X) {
						if (corner[i].Y >= TopLeft.Y && corner[i].Y <= BottomRight.Y)
							return true;
					}
				}
			}
		}
		return false;
	}
	bool check(Rect r1, Rect r2) {
		return r1.intersect(r2) || r2.intersect(r1);
	}
}rectcar, recttruck;

int main() {
	gr_Start(GrDriver, GrMode, ErrorCode);
	maxX = getmaxx(); // From Graphics
	maxY = getmaxy(); // From Graphic
	penColor = color;

	cout << "Pen Color: " <<  kachow.color << endl;
	cout << "Max Coords: " << maxX << " " << maxY << endl;
	cout << "Current Pen Points: " << getx() << " " << gety() << endl;
	string backgroundMusic = "90s.mp3";


	thread music(playSound, backgroundMusic, 286000); //90s: 286000 | wort:281000 | leedle:40000);
	thread startup(swiggeroo);



	startup.join();
	music.join();


	system("pause");
}
void timer(int duration) { //duration in seconds
	int count = 0;
	int left, top, right, bottom;
	left = top = right = bottom = 2000;
	kachow.init();
	kachow.fueltext();
	int x = 2;
	
	for (int i = duration;i >= 1;i--) {
		count = i;
		cout << count << endl;
		string b = to_string(count);
		setcolor(BLACK);
		bar(left, top, right, bottom);
		setcolor(WHITE);
		left = 1600;
		right = left + textwidth(b.c_str());
		top = 800;                                      
		outtextxy(left, top, b.c_str());
		setcolor(BLACK);
		if (i % 5 == 0) {
			kachow.carGenerator();

		}

		cout << "Kachow.car: " << kachow.car << endl;
		Sleep(1000); //we have to figure out the length necessary

	}
}
void swiggeroo() {
	kachow.init();
		kachow.drawstartup();
		cout << kachow.x << " " << kachow.y << endl;
		Sleep(3000);
		cleardevice();
		kachow.bkg();
		kachow.drawbkg();
		setcolor(GREEN);
		bar(580, 0, 0, 1100);
		bar(1320, 0, 1550, 1100);
		setcolor(BLACK);
		bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
		draw(xerino, yerino, BLUECAR);
		Playing = 1;
		kachow.lanes();
		thread fuel(timer, 60); //not neccessary
		thread player(PLAYER);
		player.join();
		fuel.join();

	}


void playSound(string kek, int duration) {
	string thingy = "open " + kek + " type mpegvideo alias MP3_Device";
	LPCSTR a = thingy.c_str();
	cout << "Starting music file " << kek << " for " << duration << " milliseconds..." << endl;
	while (playmusic=true) {

		mciSendString(a, NULL, 0, NULL);
		mciSendString("play MP3_Device from 0", NULL, 0, NULL);
		Sleep(duration);
		mciSendString("stop MP3_Device", NULL, 0, 0);


	}
}
void PLAYER() {
	while (Playing = 1) {
		rectcar.init();
		recttruck.init();
		kachow.drawlanes2();
		kachow.bary1 = kachow.bary1 + 20;
		kachow.bary2 = kachow.bary2 + 20;
		kachow.drawlanes();
		if (kachow.bary1 >= 1080) {
			kachow.lanes();
		}
		if (kachow.car <= 4) {
			
			if (kachow.car == 1) {
				setcolor(BLACK);
				bar(kachow.carx, kachow.cary, kachow.carx + CAR_Width, kachow.cary + CAR_Height);
				kachow.cary = kachow.cary + 20;
				setcolor(DARKGRAY);
				bar(kachow.carx, kachow.cary, kachow.carx + CAR_Width, kachow.cary + CAR_Height);
				draw(kachow.carx, kachow.cary, REDCAR);
			}
			if (kachow.car == 2) {
				setcolor(BLACK);
				bar(kachow.carx, kachow.cary, kachow.carx + CAR_Width, kachow.cary + CAR_Height);
				kachow.cary = kachow.cary + 20;
				setcolor(DARKGRAY);
				bar(kachow.carx, kachow.cary, kachow.carx + CAR_Width, kachow.cary + CAR_Height);
				draw(kachow.carx, kachow.cary, GREENCAR);
			}
			if (kachow.car == 3) {
				setcolor(BLACK);
				bar(kachow.carx, kachow.cary, kachow.carx + TRUCK_Width, kachow.cary + TRUCK_Height);
				kachow.cary = kachow.cary + 20;
				setcolor(DARKGRAY);
				bar(kachow.carx, kachow.cary, kachow.carx + TRUCK_Width, kachow.cary + TRUCK_Height);
				draw(kachow.carx, kachow.cary, REDCAR);
			}
			if (kachow.car == 4) {
				setcolor(BLACK);
				bar(kachow.carx, kachow.cary, kachow.carx + TRUCK_Width, kachow.cary + TRUCK_Height);
				kachow.cary = kachow.cary + 20;
				setcolor(DARKGRAY);
				bar(kachow.carx, kachow.cary, kachow.carx + TRUCK_Width, kachow.cary + TRUCK_Height);
				draw(kachow.carx, kachow.cary, BLUETRUCK);
			}
			
		}
		if (KEYBOARD(VK_A)) { //car movements
			playerInput.move = LEFT;
			cout << "a pressed" << endl;
			if (xerino - 10 >= 600) {
				setcolor(BLACK);
				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				xerino = xerino - 15;
				setcolor(DARKGRAY);
				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				draw(xerino, yerino, BLUECAR);
			}
			playerInput.reset();
		}
		if (KEYBOARD(VK_D)) { // car movements
			playerInput.move = RIGHT;
			cout << "a pressed" << endl;
			if (xerino + CAR_Width + 10 <= 1300) {
				setcolor(BLACK);
				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				xerino = xerino + 15;
				setcolor(DARKGRAY);
				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				draw(xerino, yerino, BLUECAR);
			}
			playerInput.reset();
		}
		if (KEYBOARD(VK_W)) { //level selection
			playerInput.move = UP;
			cout << "w pressed" << endl;
			if (yerino + 15 <= 0) {
				setcolor(BLACK);

				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				yerino = yerino - 15;
				setcolor(DARKGRAY);
				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				draw(xerino, yerino, BLUECAR);
			}
			playerInput.reset();
		}
		if (KEYBOARD(VK_S)) { //level selection
			playerInput.move = DOWN;
			cout << "s pressed" << endl;
			if (yerino - CAR_Height - 10 >= 1080) {
				setcolor(BLACK);
				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				yerino = yerino + 10;
				setcolor(DARKGRAY);
				bar(xerino, yerino, xerino + CAR_Width, yerino + CAR_Height);
				draw(xerino, yerino, BLUECAR);
			}
			playerInput.reset();
		}

		rectcar.init();
		recttruck.init();
		cout << "Overlap: " << rectcar.overlap << endl;
		rectcar.intersect(recttruck);
		recttruck.intersect(rectcar);
		rectcar.overlap = rectcar.check(rectcar, recttruck);
		recttruck.overlap = recttruck.check(recttruck, rectcar);
		if (rectcar.overlap || recttruck.overlap) {
			cout << "VEHICLES HAVE HIT" << endl << "Overlap: " << rectcar.overlap << endl;

			Sleep(2000);
		}
		Sleep(15);
	}
}
bool KEYBOARD(int VirtualKey) {
	if ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0)
	{
		irInBuf.EventType = KEY_EVENT;
		playerInput.VirtualKey = VirtualKey;
		playerInput.press = true;
		int count = 0;
		do {
			if (count++ > 200) {
				
				playerInput.hold = true;
				return true;
			}
		} while ((GetAsyncKeyState(VirtualKey) & 0x8000) != 0);
		return true;
	}
	return false;
}
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